#include "stm32f10x.h"
int main(){
    RCC->APB2ENR|=0x10;
    GPIOC->CRH|=0x00300000;//配置PC13 为推挽输出模式,P114

    int led_on=1;
    while (1)
    {
        if(led_on){
            GPIOC->ODR&=~0x00002000;//输出低电平,P115
        }else{
    
            GPIOC->ODR|=0x00002000;//输出高电平,P115		
        }
        led_on=!led_on;
        for(int i=0;i<4000000;i++);
    }
    
}