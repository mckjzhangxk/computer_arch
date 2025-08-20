.equ Stack_Size, 0x400
.equ Heap_Size, 0x200

# 栈的定义
.section STACK, "aw", %nobits
.align 3

.type Stack_Mem, %object
Stack_Mem:
    .space  Stack_Size  
.type __initial_sp, %object
__initial_sp:
.size Stack_Mem,.-Stack_Mem

# heap的定义
.section HEAP, "aw",%nobits
.align 3
__heap_base:
.type Heap_Mem, %object
Heap_Mem:
    .space  Heap_Size 
__heap_limit:
.size HEAP,.-HEAP
.size Heap_Mem,.-Heap_Mem

# 中断表的定义
.section RESET, "a"
.align 2
.type __Vectors, %object
__Vectors:
                .long      __initial_sp               
                .long     Reset_Handler               
                .long     NMI_Handler                @ NMI Handler
                .long     HardFault_Handler          @ Hard Fault Handler
                .long     MemManage_Handler          @ MPU Fault Handler
                .long     BusFault_Handler           @ Bus Fault Handler
                .long     UsageFault_Handler         @ Usage Fault Handler
                .long     0                          @ Reserved
                .long     0                          @ Reserved
                .long     0                          @ Reserved
                .long     0                          @ Reserved
                .long     SVC_Handler                @ SVCall Handler
                .long     DebugMon_Handler           @ Debug Monitor Handler
                .long     0                          @ Reserved
                .long     PendSV_Handler             @ PendSV Handler
                .long     SysTick_Handler            @ SysTick Handler

                @ External Interrupts
                .long     WWDG_IRQHandler            @ Window Watchdog
                .long     PVD_IRQHandler             @ PVD through EXTI Line detect
                .long     TAMPER_IRQHandler          @ Tamper
                .long     RTC_IRQHandler             @ RTC
                .long     FLASH_IRQHandler           @ Flash
                .long     RCC_IRQHandler             @ RCC
                .long     EXTI0_IRQHandler           @ EXTI Line 0
                .long     EXTI1_IRQHandler           @ EXTI Line 1
                .long     EXTI2_IRQHandler           @ EXTI Line 2
                .long     EXTI3_IRQHandler           @ EXTI Line 3
                .long     EXTI4_IRQHandler           @ EXTI Line 4
                .long     DMA1_Channel1_IRQHandler   @ DMA1 Channel 1
                .long     DMA1_Channel2_IRQHandler   @ DMA1 Channel 2
                .long     DMA1_Channel3_IRQHandler   @ DMA1 Channel 3
                .long     DMA1_Channel4_IRQHandler   @ DMA1 Channel 4
                .long     DMA1_Channel5_IRQHandler   @ DMA1 Channel 5
                .long     DMA1_Channel6_IRQHandler   @ DMA1 Channel 6
                .long     DMA1_Channel7_IRQHandler   @ DMA1 Channel 7
                .long     ADC1_2_IRQHandler          @ ADC1_2
                .long     USB_HP_CAN1_TX_IRQHandler  @ USB High Priority or CAN1 TX
                .long     USB_LP_CAN1_RX0_IRQHandler @ USB Low  Priority or CAN1 RX0
                .long     CAN1_RX1_IRQHandler        @ CAN1 RX1
                .long     CAN1_SCE_IRQHandler        @ CAN1 SCE
                .long     EXTI9_5_IRQHandler         @ EXTI Line 9..5
                .long     TIM1_BRK_IRQHandler        @ TIM1 Break
                .long     TIM1_UP_IRQHandler         @ TIM1 Update
                .long     TIM1_TRG_COM_IRQHandler    @ TIM1 Trigger and Commutation
                .long     TIM1_CC_IRQHandler         @ TIM1 Capture Compare
                .long     TIM2_IRQHandler            @ TIM2
                .long     TIM3_IRQHandler            @ TIM3
                .long     TIM4_IRQHandler            @ TIM4
                .long     I2C1_EV_IRQHandler         @ I2C1 Event
                .long     I2C1_ER_IRQHandler         @ I2C1 Error
                .long     I2C2_EV_IRQHandler         @ I2C2 Event
                .long     I2C2_ER_IRQHandler         @ I2C2 Error
                .long     SPI1_IRQHandler            @ SPI1
                .long     SPI2_IRQHandler            @ SPI2
                .long     USART1_IRQHandler          @ USART1
                .long     USART2_IRQHandler          @ USART2
                .long     USART3_IRQHandler          @ USART3
                .long     EXTI15_10_IRQHandler       @ EXTI Line 15..10
                .long     RTCAlarm_IRQHandler        @ RTC Alarm through EXTI Line
                .long     USBWakeUp_IRQHandler       @ USB Wakeup from suspend

.global __Vectors_End;.type __Vectors_End, %object;.hidden __Vectors_End
__Vectors_End:

# 中断函数的实现
.text
.align  1
.weak   Reset_Handler      @ 将 Reset_Handler 设为弱符号
.hidden Reset_Handler      @ 将 Reset_Handler 设为隐藏符号
.type   Reset_Handler, %function
Reset_Handler:
    ldr     r0, =SystemInit
    blx     r0
    ldr     r0, =main
    bx      r0
.size Reset_Handler,.-Reset_Handler


.weak   NMI_Handler      
.hidden NMI_Handler      
.type   NMI_Handler, %function
NMI_Handler:
    B .
.size NMI_Handler,.-NMI_Handler


.weak   HardFault_Handler      
.hidden HardFault_Handler      
.type   HardFault_Handler, %function
HardFault_Handler:
    B .
.size HardFault_Handler,.-HardFault_Handler


.weak   MemManage_Handler      
.hidden MemManage_Handler      
.type   MemManage_Handler, %function
MemManage_Handler:
    B .
.size MemManage_Handler,.-MemManage_Handler


.weak   BusFault_Handler      
.hidden BusFault_Handler      
.type   BusFault_Handler, %function
BusFault_Handler:
    B .
.size BusFault_Handler,.-BusFault_Handler



.weak   UsageFault_Handler      
.hidden UsageFault_Handler      
.type   UsageFault_Handler, %function
UsageFault_Handler:
    B .
.size UsageFault_Handler,.-UsageFault_Handler


.weak   SVC_Handler      
.hidden SVC_Handler      
.type   SVC_Handler, %function
SVC_Handler:
    B .
.size SVC_Handler,.-SVC_Handler



.weak   DebugMon_Handler      
.hidden DebugMon_Handler      
.type   DebugMon_Handler, %function
DebugMon_Handler:
    B .
.size DebugMon_Handler,.-DebugMon_Handler



.weak   PendSV_Handler      
.hidden PendSV_Handler      
.type   PendSV_Handler, %function
PendSV_Handler:
    B .
.size PendSV_Handler,.-PendSV_Handler



.weak   SysTick_Handler      
.hidden SysTick_Handler      
.type   SysTick_Handler, %function
SysTick_Handler:
    B .
.size SysTick_Handler,.-SysTick_Handler



@ Default_Handler

.weak   WWDG_IRQHandler;.hidden WWDG_IRQHandler;.type   WWDG_IRQHandler, %function
WWDG_IRQHandler:

.weak   PVD_IRQHandler;.hidden PVD_IRQHandler;.type   PVD_IRQHandler, %function
PVD_IRQHandler:

.weak   TAMPER_IRQHandler;.hidden TAMPER_IRQHandler;.type   TAMPER_IRQHandler, %function
TAMPER_IRQHandler:

.weak   RTC_IRQHandler;.hidden RTC_IRQHandler;.type   RTC_IRQHandler, %function
RTC_IRQHandler:

.weak   FLASH_IRQHandler;.hidden FLASH_IRQHandler;.type   FLASH_IRQHandler, %function
FLASH_IRQHandler:

.weak   RCC_IRQHandler;.hidden RCC_IRQHandler;.type   RCC_IRQHandler, %function
RCC_IRQHandler:


.weak   EXTI0_IRQHandler;.hidden EXTI0_IRQHandler;.type   EXTI0_IRQHandler, %function
EXTI0_IRQHandler:
.weak   EXTI1_IRQHandler;.hidden EXTI1_IRQHandler;.type   EXTI1_IRQHandler, %function
EXTI1_IRQHandler:
.weak   EXTI2_IRQHandler;.hidden EXTI2_IRQHandler;.type   EXTI2_IRQHandler, %function
EXTI2_IRQHandler:
.weak   EXTI3_IRQHandler;.hidden EXTI3_IRQHandler;.type   EXTI3_IRQHandler, %function
EXTI3_IRQHandler:
.weak   EXTI4_IRQHandler;.hidden EXTI4_IRQHandler;.type   EXTI4_IRQHandler, %function
EXTI4_IRQHandler:
.weak   DMA1_Channel1_IRQHandler;.hidden DMA1_Channel1_IRQHandler;.type   DMA1_Channel1_IRQHandler, %function
DMA1_Channel1_IRQHandler:
.weak   DMA1_Channel2_IRQHandler;.hidden DMA1_Channel2_IRQHandler;.type   DMA1_Channel2_IRQHandler, %function
DMA1_Channel2_IRQHandler:
.weak   DMA1_Channel3_IRQHandler;.hidden DMA1_Channel3_IRQHandler;.type   DMA1_Channel3_IRQHandler, %function
DMA1_Channel3_IRQHandler:
.weak   DMA1_Channel4_IRQHandler;.hidden DMA1_Channel4_IRQHandler;.type   DMA1_Channel4_IRQHandler, %function
DMA1_Channel4_IRQHandler:
.weak   DMA1_Channel5_IRQHandler;.hidden DMA1_Channel5_IRQHandler;.type   DMA1_Channel5_IRQHandler, %function
DMA1_Channel5_IRQHandler:
.weak   DMA1_Channel6_IRQHandler;.hidden DMA1_Channel6_IRQHandler;.type   DMA1_Channel6_IRQHandler, %function
DMA1_Channel6_IRQHandler:
.weak   DMA1_Channel7_IRQHandler;.hidden DMA1_Channel7_IRQHandler;.type   DMA1_Channel7_IRQHandler, %function
DMA1_Channel7_IRQHandler:

.weak   ADC1_2_IRQHandler;.hidden ADC1_2_IRQHandler;.type   ADC1_2_IRQHandler, %function
ADC1_2_IRQHandler:
.weak   USB_HP_CAN1_TX_IRQHandler;.hidden USB_HP_CAN1_TX_IRQHandler;.type   USB_HP_CAN1_TX_IRQHandler, %function
USB_HP_CAN1_TX_IRQHandler:
.weak   USB_LP_CAN1_RX0_IRQHandler;.hidden USB_LP_CAN1_RX0_IRQHandler;.type   USB_LP_CAN1_RX0_IRQHandler, %function
USB_LP_CAN1_RX0_IRQHandler:
.weak   CAN1_RX1_IRQHandler;.hidden CAN1_RX1_IRQHandler;.type   CAN1_RX1_IRQHandler, %function
CAN1_RX1_IRQHandler:
.weak   CAN1_SCE_IRQHandler;.hidden CAN1_SCE_IRQHandler;.type   CAN1_SCE_IRQHandler, %function
CAN1_SCE_IRQHandler:
.weak   EXTI9_5_IRQHandler;.hidden EXTI9_5_IRQHandler;.type   EXTI9_5_IRQHandler, %function
EXTI9_5_IRQHandler:


.weak   TIM1_BRK_IRQHandler;.hidden TIM1_BRK_IRQHandler;.type   TIM1_BRK_IRQHandler, %function
TIM1_BRK_IRQHandler:
.weak   TIM1_UP_IRQHandler;.hidden TIM1_UP_IRQHandler;.type   TIM1_UP_IRQHandler, %function
TIM1_UP_IRQHandler:
.weak   TIM1_TRG_COM_IRQHandler;.hidden TIM1_TRG_COM_IRQHandler;.type   TIM1_TRG_COM_IRQHandler, %function
TIM1_BRK_IRQHandler:
.weak   TIM1_CC_IRQHandler;.hidden TIM1_CC_IRQHandler;.type   TIM1_CC_IRQHandler, %function
TIM1_CC_IRQHandler:
.weak   TIM2_IRQHandler;.hidden TIM2_IRQHandler;.type   TIM2_IRQHandler, %function
TIM2_IRQHandler:
.weak   TIM3_IRQHandler;.hidden TIM3_IRQHandler;.type   TIM3_IRQHandler, %function
TIM3_IRQHandler:
.weak   TIM4_IRQHandler;.hidden TIM4_IRQHandler;.type   TIM4_IRQHandler, %function
TIM4_IRQHandler:

.weak   I2C1_EV_IRQHandler;.hidden I2C1_EV_IRQHandler;.type   I2C1_EV_IRQHandler, %function
I2C1_EV_IRQHandler:
.weak   I2C1_ER_IRQHandler;.hidden I2C1_ER_IRQHandler;.type   I2C1_ER_IRQHandler, %function
I2C1_ER_IRQHandler:
.weak   I2C2_EV_IRQHandler;.hidden I2C2_EV_IRQHandler;.type   I2C2_EV_IRQHandler, %function
I2C2_EV_IRQHandler:
.weak   I2C2_ER_IRQHandler;.hidden I2C2_ER_IRQHandler;.type   I2C2_ER_IRQHandler, %function
I2C2_ER_IRQHandler:


.weak   SPI1_IRQHandler;.hidden SPI1_IRQHandler;.type   SPI1_IRQHandler, %function
SPI1_IRQHandler:
.weak   SPI2_IRQHandler;.hidden SPI2_IRQHandler;.type   SPI2_IRQHandler, %function
SPI2_IRQHandler:
.weak   USART1_IRQHandler;.hidden USART1_IRQHandler;.type   USART1_IRQHandler, %function
USART1_IRQHandler:
.weak   USART2_IRQHandler;.hidden USART2_IRQHandler;.type   USART2_IRQHandler, %function
USART2_IRQHandler:
.weak   USART3_IRQHandler;.hidden USART3_IRQHandler;.type   USART3_IRQHandler, %function
USART3_IRQHandler:
.weak   EXTI15_10_IRQHandler;.hidden EXTI15_10_IRQHandler;.type   EXTI15_10_IRQHandler, %function
EXTI15_10_IRQHandler:
.weak   RTCAlarm_IRQHandler;.hidden RTCAlarm_IRQHandler;.type   RTCAlarm_IRQHandler, %function
RTCAlarm_IRQHandler:
.weak   USBWakeUp_IRQHandler;.hidden USBWakeUp_IRQHandler;.type   USBWakeUp_IRQHandler, %function
USBWakeUp_IRQHandler:

b .

# 定义一个 __user_initial_stackheap函数
.global   __user_initial_stackheap;.hidden __user_initial_stackheap;.type   __user_initial_stackheap, %function
__user_initial_stackheap:
                 ldr     r0, =  Heap_Mem
                 ldr     r1, =(Stack_Mem + Stack_Size)
                 ldr     r2, = (Heap_Mem +  Heap_Size)
                 ldr     r3, = Stack_Mem
                 bx      lr
