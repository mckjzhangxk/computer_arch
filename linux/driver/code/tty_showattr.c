#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>

static int baud_to_value(speed_t speed) {
    switch (speed) {
        case B0: return 0;
        case B50: return 50;
        case B75: return 75;
        case B110: return 110;
        case B134: return 134;
        case B150: return 150;
        case B200: return 200;
        case B300: return 300;
        case B600: return 600;
        case B1200: return 1200;
        case B1800: return 1800;
        case B2400: return 2400;
        case B4800: return 4800;
        case B9600: return 9600;
        case B19200: return 19200;
        case B38400: return 38400;
        case B57600: return 57600;
        case B115200: return 115200;
        case B230400: return 230400;
        default: return -1; // unknown
    }
}

int main(int argc,char* argv[]) {
    int fd = open(argv[1], O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("open");
        return 1;
    }

    struct termios tty;

    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        close(fd);
        return 1;
    }

    // 波特率
    speed_t ispeed = cfgetispeed(&tty);
    speed_t ospeed = cfgetospeed(&tty);

    printf("Input speed: %d\n", baud_to_value(ispeed));
    printf("Output speed: %d\n", baud_to_value(ospeed));

    // 数据位
    printf("Data bits: ");
    switch (tty.c_cflag & CSIZE) {
        case CS5: printf("5\n"); break;
        case CS6: printf("6\n"); break;
        case CS7: printf("7\n"); break;
        case CS8: printf("8\n"); break;
    }

    // 校验位
    if (tty.c_cflag & PARENB) {
        if (tty.c_cflag & PARODD)
            printf("Parity: Odd\n");
        else
            printf("Parity: Even\n");
    } else {
        printf("Parity: None\n");
    }

    // 停止位
    printf("Stop bits: %d\n", (tty.c_cflag & CSTOPB) ? 2 : 1);

    // 流控
    printf("Hardware flow control (RTS/CTS): %s\n",
           (tty.c_cflag & CRTSCTS) ? "Yes" : "No");

    printf("Software flow control (XON/XOFF): %s\n",
           (tty.c_iflag & (IXON | IXOFF)) ? "Yes" : "No");

    close(fd);
    return 0;
}