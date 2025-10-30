#define BASE_ADDR 0X11000000
#define GPX2CON (BASE_ADDR+0xc40) //GPX2这组 配置
#define GPX2DAT (BASE_ADDR+0xc44) //GPX2这组 数据
#define GPX2PUD (BASE_ADDR+0xc48) //GPX2这组 上下拉,不使用
#define GPX2DRV (BASE_ADDR+0xc4C) //GPX2这组 功率,不使用

//设在 CPX2_7 为输出模式
void setup(){
    // CPX2_7 :GPX2CON[31:28]
    // CPX2_6 :GPX2CON[27:24]
    // ....
    // CPX2_1 :GPX2CON[7:4]
    // CPX2_0 :GPX2CON[3:0]
    unsigned int *p=(unsigned int *)GPX2CON;
    // *p=(*p & ~(0xf<<28) ) | (0x01 <<28);

    int input_mode=(0x01 << 28);
    unsigned int oldvalue = *p& (0x00ffffff);
    *p = oldvalue | input_mode;
}


//GPX2DAT[0] -> GPX_2_0 的输出数据
//GPX2DAT[1] -> GPX_2_1 的输出数据
//GPX2DAT[2] -> GPX_2_2 的输出数据
// ....
//GPX2DAT[7] -> GPX_2_7 的输出数据
void turn_on(){
    unsigned char *p=(unsigned char *)GPX2DAT;
    *p|=(1<<7);
}
void turn_off(){
    unsigned char *p=(unsigned char *)GPX2DAT;
    *p&=0x7f;
}
void delay(){
    for (int i = 0; i < 1e9; i++)
    {
        /* code */
    }

}

int main(){
    setup();

    turn_on();

    while (1)
    {
        turn_on();
        delay();
        turn_off();
        delay();

    }
    return 0;
}
