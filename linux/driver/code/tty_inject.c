#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

// TTY 伪终端注入测试程序
// 1. 编译：gcc -o tty_inject tty_inject.c
// 2. 运行：./tty_inject
// 3. 在另一个终端中使用 sh < /dev/pts/N （N 是上一步输出的 slave 设备号）
// 4. 在第一个终端输入命令，观察第二个终端的输出
int main(int argc, char *argv[]) {
    // int master = posix_openpt(O_RDWR | O_NOCTTY);//打开系统的“PTMX”

    int master = open("/dev/pts/ptmx", O_RDWR); 

    if (master < 0) {
        perror("posix_openpt");
        return 1;
    }

    grantpt(master);//为 slave 设备节点 /dev/pts/N 设置权限（chown/chmod）
    unlockpt(master);//解锁这个 slave，让其他程序能 open 它

    char *slave_name = ptsname(master);//获取对应 slave 的名字
    printf("master %d,slave: %s\n",master ,slave_name);

    // 测试：往 master 写 -> slave 会收到输入


    while (1)
    {
        char buf[256];
        int n = read(0, buf, sizeof(buf));
        buf[n-1]=0;//去掉换行符，虽然 write，但/dev/pts/N 不会收到，因为 ptty 是行缓冲的
        printf("send cmd %s\n",buf);
        if (n > 0) {
            write(master, buf, n);
        }
    }

    // 保持 master 打开，等待用户观察


    close(master);
    return 0;
}