// x86 16550 UART 简单驱动示例
#include <stdint.h>

// COM1 基地址
#define UART_BASE 0x3F8

// 寄存器偏移
#define UART_RBR  (UART_BASE + 0)  // 接收缓冲寄存器 (读)
#define UART_THR  (UART_BASE + 0)  // 发送保持寄存器 (写)
#define UART_DLL  (UART_BASE + 0)  // 除数锁存器低字节 (DLAB=1)
#define UART_DLH  (UART_BASE + 1)  // 除数锁存器高字节 (DLAB=1)
#define UART_IER  (UART_BASE + 1)  // 中断使能寄存器
#define UART_IIR  (UART_BASE + 2)  // 中断标识寄存器 (读)
#define UART_FCR  (UART_BASE + 2)  // FIFO控制寄存器 (写)
#define UART_LCR  (UART_BASE + 3)  // 线路控制寄存器
#define UART_MCR  (UART_BASE + 4)  // Modem控制寄存器
#define UART_LSR  (UART_BASE + 5)  // 线路状态寄存器
#define UART_MSR  (UART_BASE + 6)  // Modem状态寄存器
#define UART_SCR  (UART_BASE + 7)  // 暂存寄存器

// LCR 位定义
#define LCR_DLAB  0x80  // 除数锁存访问位
#define LCR_8BIT  0x03  // 8位数据
#define LCR_1STOP 0x00  // 1个停止位
#define LCR_NPAR  0x00  // 无校验

// LSR 位定义
#define LSR_DATA_READY 0x01  // 数据就绪
#define LSR_THR_EMPTY  0x20  // 发送保持寄存器空

// FCR 位定义
#define FCR_ENABLE_FIFO 0x01  // 使能FIFO
#define FCR_CLEAR_RX    0x02  // 清除接收FIFO
#define FCR_CLEAR_TX    0x04  // 清除发送FIFO

// I/O端口操作（需要实现或使用内联汇编）
static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t val;
    __asm__ volatile ("inb %1, %0" : "=a"(val) : "Nd"(port));
    return val;
}

// 初始化串口
void uart_init(uint32_t baud_rate) {
    // 1. 禁用中断
    outb(UART_IER, 0x00);
    
    // 2. 设置波特率
    // 波特率除数 = 115200 / baud_rate
    uint16_t divisor = 115200 / baud_rate;
    
    // 设置 DLAB=1 以访问除数寄存器
    outb(UART_LCR, LCR_DLAB);
    outb(UART_DLL, divisor & 0xFF);        // 低字节
    outb(UART_DLH, (divisor >> 8) & 0xFF); // 高字节
    
    // 3. 配置数据格式：8位数据，1个停止位，无校验
    outb(UART_LCR, LCR_8BIT | LCR_1STOP | LCR_NPAR);
    
    // 4. 启用并清空FIFO，设置14字节触发阈值
    outb(UART_FCR, FCR_ENABLE_FIFO | FCR_CLEAR_RX | FCR_CLEAR_TX | 0xC0);
    
    // 5. 设置 Modem 控制：RTS、DTR
    outb(UART_MCR, 0x03);
    
    // 6. 可选：启用中断
    // outb(UART_IER, 0x01); // 启用接收中断
}

// 检查是否可以发送
int uart_can_send() {
    return inb(UART_LSR) & LSR_THR_EMPTY;
}

// 发送一个字节（轮询方式）
void uart_putc(char c) {
    // 等待发送缓冲区空
    while (!uart_can_send());
    outb(UART_THR, c);
}

// 发送字符串
void uart_puts(const char *str) {
    while (*str) {
        uart_putc(*str++);
    }
}

// 检查是否有数据可读
int uart_can_recv() {
    return inb(UART_LSR) & LSR_DATA_READY;
}

// 接收一个字节（轮询方式）
char uart_getc() {
    // 等待数据就绪
    while (!uart_can_recv());
    return inb(UART_RBR);
}

// 使用示例
void demo() {
    // 初始化串口，波特率 9600
    uart_init(9600);
    
    // 发送字符串
    uart_puts("Hello, UART!\r\n");
    
    // 发送单个字符
    uart_putc('A');
    uart_putc('\n');
    
    // 接收并回显
    char c = uart_getc();
    uart_putc(c);
    
    // 循环回显
    while (1) {
        if (uart_can_recv()) {
            char ch = uart_getc();
            uart_putc(ch); // 回显
        }
    }
}

// 中断方式接收示例（需要配置中断处理）
void uart_irq_handler() {
    // 读取中断标识寄存器
    uint8_t iir = inb(UART_IIR);
    
    // 检查是否是接收数据中断
    if ((iir & 0x0F) == 0x04) {
        // 读取数据
        while (uart_can_recv()) {
            char c = uart_getc();
            // 处理接收到的数据
            // ...
        }
    }
}

int main() {
    demo();
    return 0;
}