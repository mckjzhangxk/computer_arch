## 通信基础 - 并行和串行

## 单工和双工

## 传输数据帧
![Alt text](imgs/uart_frame.png)

-  空闲位：高电平
-  起始位：低电平
- 一次只可以传输： 5-8位
- 先传低位，后传高位
- 停止位：1
- 更多过程需要重复此过程
- 接收端通过沟通好的波特率(bps)，掐时间解析传输bit,
- 以上所有过程都 在UART控制器中 实现了


## 需要配置的选项
- 传输位数
- 波特率
- 是否使用校验
- 停止位多少bit

## 4412中uart工作原理
![Alt text](imgs/uart_4412.png)
```
The Baud-rate generator uses SCLK_UART. The transmitter and the receiver contain FIFOs and data shifters. The data to be transmitted is written to Tx FIFO, and copied to the transmit shifter. The data is then shifted out by the transmit data pin (TxDn). The received data is shifted from the receive data pin (RxDn), and copied to Rx FIFO from the shifter.

```
- SCLK_UART时钟，100M
- transmitter： FIFOs ，data shifters，FIFO->shifter数据拷贝
- receiver FIFOs ，data shifters，shifer->FIFO数据拷贝
- TXDn：发生引脚
- RXDn：接收引脚
![Alt text](imgs/uart_reg.png)




## 补充RISCV的 uart
[参考手册16550](http://byterunner.com/16550.html)

```sh
# 以下都是8位寄存器
地址      寄存器名称         描述
0         RHR               接受数据的寄存器
0         THR               发生数据的寄存器
1         IER               中断使能寄存器      
2         FCR:               中断模式下的FIFO 控制

3         LCR               传输控制寄存器
4         MCR
5         LSR


LCR:
 0,1位 :控制 word length。
   2位："控制" stop bit length
   3位.使能奇偶校验：
   7位：使能内部分频器
FCR:
    0位： 0->中断模式，1->poll 模式
    1位： 重置 receiver FIFO
    2位： 重置 transmit FIFO

IER：
    0位: 使能接收中断,  RX fifo 有数据触发
    1位: 使能传输中断， TX fifo empty 触发

LSR: 
  0位： 接受端有数据
  5位： 发送缓冲区空闲
  6位： transmit shift register 空闲（真正发生数据存放处）
 1-4位： 发送端Error 相关
  7位： 接受端Error
    
```

```c
void
uartinit(void)
{
  // disable interrupts.
  WriteReg(IER, 0x00);

  // 1.设置Baud rate（波特率）=3,对应这38.4K的频率
  WriteReg(LCR, LCR_BAUD_LATCH);  
  // LSB for baud rate of 38.4K.
  WriteReg(0, 0x03);
  // MSB for baud rate of 38.4K.
  WriteReg(1, 0x00);

  //2.数据word length。stop bit length，奇偶校验
  WriteReg(LCR, LCR_EIGHT_BITS);
  
  
  //3.开启并且FIFO 的中断中断模式
  WriteReg(FCR, FCR_FIFO_ENABLE | FCR_FIFO_CLEAR);


  WriteReg(IER, IER_TX_ENABLE | IER_RX_ENABLE);
}
// The 16550 contains a programmable Baud Rate Generator that is capable of tracking any clock input from DC-8 MHz and dividing it by any divisor from 1 to 2^16-1. The output frequency of the Baudout is equal to the 16X of transmission baud rate (Baudout=16 X Baud Rate). Customize Baud Rates can be achieved by selecting proper divisor values for MSB and LSB of baud rate generator.
```


```c

void uartputc_sync(int c)
{

  // wait for Transmit Holding Empty to be set in LSR.
  while((ReadReg(LSR) & LSR_TX_IDLE) == 0)
    ;
  WriteReg(THR, c);
}


int uartgetc(void)
{
  //LSR: LINE STATE REGISTER
  //RHR: RECEIVE HOLDING REGISTER
  if(ReadReg(LSR) & LSR_RX_READY){//表示是否是ready
    // input data is ready.
    return ReadReg(RHR);
  } else {
    return -1;
  }
}
```