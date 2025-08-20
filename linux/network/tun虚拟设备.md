## Linux 是如何路由流量的？

- 根据Ip Rule选择使用的 路由表， 优先级高的 Rule先被匹配。
- 如果路由表 匹配【目标】,则路由。否则跳到下一个匹配Rule 对应的路由表。
- [ip-rule](https://man7.org/linux/man-pages/man8/ip-rule.8.html)文档。

```sh
# clash tun模式的配置

0:	from all lookup local   #rule0
# 非53端口，查看main表， 但是main表中的 prefixlength<=0的条目无效
9500:	not from all dport 53 lookup main suppress_prefixlength 0 #rule1 
# 如果入口接口不是lo,查看 1970566510, 1970566510==>tun路由表
# 1.对于出网流量： iff是空， 流量发送给 tun proxy, tunproxy 把流量 从公网发出去。
# 2.对于入网流量： iff如果不是lo,如eth0,   流量也发送给 tun proxy， tunproxy把流量 转发给 本地应用。

9510:	not from all iif lo lookup 1970566510               #rule2
9520:	from 0.0.0.0 iif lo uidrange 0-4294967294 lookup 1970566510 #rule3 
9530:	from 198.18.0.1 iif lo uidrange 0-4294967294 lookup 1970566510 #rule4
32766:	from all lookup main #rule5
32767:	from all lookup default
```

- 1. 当流量被 rule2 匹配， 在app看来，这是一个 (198.18.0.1 ->  dest)的socket。
- 2. tunproxy 通过read(tunfd,buf)获得 【send data】。
- 3. <font color=red>tunproxy 创建一个socket, 使用netlink+SO_BINDTOIFINDEX 设置好socket的出网设备，这样可以防止 rule2 再次匹配。eg: (x.x.x.x-->dest dev=eth0,其实rule2,rule3都被匹配，但是1970566510没有匹配的条目)</font>
- 4. tunproxy代理发出的流量会经过  rule5匹配成功。
- 5. 当dest流量到来的时候， 还是匹配 rule2(iff=eth0,dest->192.x.x.x),流量再次被tunproxy劫持。
- 6. tunproxy 通过 write(tunfd,buf),回复dest->app的【recv data】。

## 防止重复匹配
```c
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main() {
    const char *iface = "wlan0";     // 替换为你机器的出口接口名
    const char *dst_ip = "1.1.1.1";  // Cloudflare
    int dst_port = 80;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        return 1;
    }

    // 绑定 socket 到指定设备
    if (setsockopt(sockfd, SOL_SOCKET, SO_BINDTODEVICE, iface, strlen(iface)) < 0) {
        perror("setsockopt(SO_BINDTODEVICE)");
        return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(dst_port);
    inet_pton(AF_INET, dst_ip, &addr.sin_addr);

    if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect");
        return 1;
    }

    printf("Connected to %s:%d via device %s\n", dst_ip, dst_port, iface);

    // 简单发送 HTTP 请求
    const char *req = "GET / HTTP/1.0\r\nHost: 1.1.1.1\r\n\r\n";
    write(sockfd, req, strlen(req));

    // 接收部分返回
    char buffer[1024];
    int n = read(sockfd, buffer, sizeof(buffer)-1);
    if (n > 0) {
        buffer[n] = '\0';
        printf("Received:\n%s\n", buffer);
    }

    close(sockfd);
    return 0;
}

```