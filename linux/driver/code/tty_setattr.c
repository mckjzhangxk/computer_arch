#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int uart_set(int fd, int speed)
{
    struct termios tty;
    tcgetattr(fd, &tty);

    cfmakeraw(&tty);

    // 设置波特率
    cfsetispeed(&tty, speed);
    cfsetospeed(&tty, speed);

    tty.c_cflag |= (CLOCAL | CREAD);     // 忽略调制解调器&&打开接收(CREAD)
    tty.c_cflag &= ~CSIZE;               // 数据位设置 mask,清空
    tty.c_cflag |= CS8;                  // 8数据位
    tty.c_cflag &= ~PARENB;              // 无校验
    tty.c_cflag &= ~CSTOPB;              // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;             // no hardware flow ctrl

    tty.c_cc[VTIME] = 1;   // read timeout 0.1s
    tty.c_cc[VMIN]  = 0;   // 非阻塞 read

    tcflush(fd, TCIFLUSH);                
    return tcsetattr(fd, TCSANOW, &tty);  //立即生效
}

int main(int argc,char* argv[])
{
    const char *dev =argv[1];
    int fd = open(dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    uart_set(fd, B115200);

    const char *msg = "Hello STM32!\n";
    write(fd, msg, strlen(msg));

    char buf[256];
    while (1) {
        int n = read(fd, buf, sizeof(buf));
        if (n > 0) {
            write(STDOUT_FILENO, buf, n);
        }
        usleep(1000);
    }

    close(fd);
    return 0;
}