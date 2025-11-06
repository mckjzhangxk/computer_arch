#define BASE_ADDR 0X11400000
#define GPA1CON (BASE_ADDR+0x20) //GPA1这组 配置

// 对uart2的配置
#define UART2_ULCON 0X13820000
#define UART2_UCON     (0X13820000+0x0004)
#define UATR2_UTSTAT   (0X13820000+0x0010)
#define UATR2_UBRDDIV  (0X13820000+0x0028)
#define UATR2_UFRACVAL (0X13820000+0x002c)
#define UATR2_UTXH     (0X13820000+0x0020)
#define UATR2_URXH     (0X13820000+0x0024)


static inline unsigned int get_mask(int n){
    unsigned int r=0;
    for(int i=0;i<n;i++){
        r=(r<<1)|1;
    }
    return r;
}
static void set_bits(unsigned int *p,int offset,int bits,int value){
    int mask=get_mask(bits);
    *p=(*p & ~(mask<<offset) ) | (value <<offset);
}


void gpio_setup(){
    unsigned int *p=(unsigned int *)GPA1CON;
    
    //GPA1_0 ->UART_2_RXD, 这里是配置 pa1.0 的复用位 rx
    set_bits(p,0,4,0x02); // 等价于      *p=(*p & ~(0xf<<0) ) | (0x02 <<0);
    //GPA1_1 -> UART_2_TXD, 这里是配置 pa1.1 的复用位 tx
    set_bits(p,4,4,0x02);//等价于     *p=(*p & ~(0xf<<4) ) | (0x02 <<4);

    // *p=*p&(~0xff)|0x22;
}

void uart_setup(){
    unsigned int *p=(unsigned int *)UART2_ULCON;
    //[5:3]:0b000,无校验
    //[2]:0b0,one stop bit
    //[1:0]:0b11 ,wordlength=8bit
    *p=0x03;


    p=(unsigned int *)UART2_UCON;
    //Transmit mode [3:2]: 01-->Interrupt request or polling mode
    //Receive  mode [1:0]: 01-->Interrupt request or polling mode
    //Rx Interrupt Type[8]  0-> 中断模式
    //Tx Interrupt Type[9]  0-> 中断模式
    set_bits(p,0,4,0b0101);//*p=*p& (~0x0f)|0x05;

    //开启loop back,  [tx引角] 连接 [tx引角]
    // *p=*p|(1<<5);

    //波特率 115200
    //DIV_VAL=100*1000000/(115200*16)-1=53.2534
    //DDIV=53
    //FRAC=0.2534*16=4
    p=(unsigned int *)UATR2_UBRDDIV;
    *p=53;
    p=(unsigned int *)UATR2_UFRACVAL;
    *p=4;
}   

void send_one_byte(char c){
    unsigned int *p=(unsigned int *)UATR2_UTXH;
    unsigned int *status=(unsigned int *)UATR2_UTSTAT;
    
    //TX STATUS：[1] 0->full,1->empty
    while (((*status)&(1<<1))==0);    //while not empty
    *p=c;
}

void recv_one_byte(char *c){
    unsigned int *p=(unsigned int *)UATR2_URXH;
    unsigned int *status=(unsigned int *)UATR2_UTSTAT;
    

    //RX STATUS：[0] 0->not ready,1->recv ready
    while (((*status)&(1<<0))==0);    //while empty
    *c= (*p&0x0f);
}

int main(){
    gpio_setup();
    uart_setup();
    char c;
    while (1)
    {
        //echo back
        recv_one_byte(&c);
        send_one_byte(c);

    }
    
     
    return 0;
}


