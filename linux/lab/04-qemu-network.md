## [网络的配置](https://www.zhaixue.cc/qemu/qemu-u-boot.html)
- 在使用tftp与nfs的之前，需要先把qemu的网络配置好
- 思路是本机创建一个网桥br,设置好br的ip地址，然后创建一个tap，连接上tap,设置好tap的地址，最后告诉qemu这个tap

```sh
# 1.创建网桥，脚本来自与k8s 
ip link add br0 type bridge
ip addr add 192.168.33.145/24 dev br0
ip link set br0 up
# 查看
brctl show
ip l


# 2.创建tap0,并且接入br0
# ip tuntap add name tap0 mode tap
# sudo ifconfig tap0 0.0.0.0 promisc up
sudo tunctl -u root -t tap0
sudo ifconfig tap0 0.0.0.0 promisc up
sudo brctl addif br0 tap0


# 3.删除操作
sudo tunctl -u root -d tap0
sudo brctl delif br0 tap0
```


## 额外配置
```sh
# 如果需要qemu上网，需要

# 1.开发版linux配置默认网关
ip route add default dev eth0
# 2.主机配置nat转换,注意使用本命令可能导致开发版无法加载kernel
sudo iptables -t nat -A POSTROUTING -s 192.168.33.0/24 -j MASQUERADE

# 3.如何配置域名服务器？？
```