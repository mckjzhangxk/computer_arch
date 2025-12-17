## TTY（终端子系统）是什么？（最重要）

Linux 下，串口就是 TTY 设备：

- /dev/ttyS0 → 板载串口
- /dev/ttyUSB0 → USB 转串口
- /dev/ttyACM0 → CDC ACM 设备（如 STM32 虚拟串口）

TTY 是 Linux 的 终端抽象系统，串口和虚拟终端（ssh/console）都走这套逻辑。

👉 所以 Linux 下串口配置不是直接配置硬件寄存器，而是修改一个名为 termios 的“终端属性结构”。

## [termios 结构体](https://man7.org/linux/man-pages/man3/termios.3.html)
- c_cflag → 控制参数（数据位、校验位等）
- c_lflag → 本地模式（canonical / non-canonical），配置tty 是原生的 uart 还是更像 "键盘"
- c_iflag → 输入处理模式
- c_oflag → 输出处理模式
- c_cc[] → read 行为参数（超时、阻塞控制）
```c
    tcflag_t c_iflag;      /* input modes */
    tcflag_t c_oflag;      /* output modes */
    tcflag_t c_cflag;      /* control modes */
    tcflag_t c_lflag;      /* local modes */
    cc_t     c_cc[NCCS];   /* special characters */
```
## canonical mode vs raw mode（行缓冲模式与原始模式）
串口编程几乎必须使用 原始模式（raw mode）。
```c
// 配置raw mode
struct termios tty;
cfmakeraw(&tty);


// cfmakeraw 相当于执行下面：

// IXON：软件流控制，  
// ICRNL：会把\r 字段转换成\n
// IGNBRK:忽略 BRK 信号,BRK是串口产生的电信号(2个连续0）。
// BRKINT:收到 BRK 信号 发送  sigINT
termios_p->c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP| INLCR | IGNCR | ICRNL | IXON);
termios_p->c_oflag &= ~OPOST;
// ISIG表示收到某个字符，产生相应的中断。  
// ICANON：行缓冲模式。 
// ECHO，ECHONL 会回显，比如收到abc,自动发送 abc
termios_p->c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
// PARENB是 使能校验
// CSIZE 字宽掩码
termios_p->c_cflag &= ~(CSIZE | PARENB);
// CS8：8位 字宽
termios_p->c_cflag |= CS8;
```
这一句就是：

- 关闭行缓冲
- 关闭所有字符处理（如回显、换行转换）
- 让串口的行为像 UART，而不是键盘

### 串口设备的查看
- 方法1
```sh
# 方法1 
stty -F /dev/ttyS0 -a
# 字段含义：

# speed 115200 baud	波特率
# cs8 / cs7	数据位
# -parenb	无校验
# parodd	奇校验
# -cstopb	1 个停止位
# cstopb	2 个停止位
# -ixon -ixoff	不使用软件流控
# -crtscts	不使用硬件流控
```

- [方法2](code/tty_showattr.c)

## 串口设备属性设置
- 方法1
```sh
# 方法1
stty -F /dev/pts/0 intr ^C
stty -F /dev/pts/0 -echo
stty -F /dev/pts/0 raw
stty -F /dev/pts/0 icanon isig echo
```
- [方法2](code/tty_setattr.c)

## 如何给一个 tty “写入输入”
```sh
┌──────────┐          ┌────────────┐
│/dev/pts/X│ <--→-->  │ /dev/ptmx  │
└──────────┘          └────────────┘
     slave                  master

```
- 从机 /dev/pts/0 是“终端侧”
- 当某个进程读取 /dev/pts/0 时，它是在读取“用户输入”
- ✔ 主机 /dev/ptmx 是“控制器”
- 你向 master 写入数据，会作为“键盘输入”出现在 slave
- master 和 slave 是一对一，而不是多对一,虽然只有一个/dev/pts/ptmx
- /dev/pts/ptmx：所有 PTY 的 master 端，都从 /dev/pts/ptmx 这个“总入口”动态创建出来。它是一个“分配器”（multiplexer）。
- [tty_inject](code/tty_inject.c)