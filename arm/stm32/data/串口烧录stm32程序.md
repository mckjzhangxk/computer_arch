## 启动条件

- 1.stm32设置启动引脚

|BOOT0|	BOOT1|	启动源|
|-|-|-|
|0	|*	|Flash（正常跑程序）
|1	|0	|System Memory（串口下载）
|1	|1	|SRAM

- 2.串口接线（以 USART1 为例）

|STM32	|CH304
|-|-|
|PA9 (TX)	|RX
|PA10 (RX)	|TX
|GND	|GND
- <font color=red>3.烧录文件的准备</font>
```sh
# 查看文件的内存布局
arm-none-eabi-readelf -S led.elf
#                                           VMA   OFFSET   SIZE
# [ 1] ER_IROM1          PROGBITS        08000000 000034 001338 00  AX  
# [ 2] RW_IRAM1          PROGBITS        20000000 00136c 000008 00  WA  
# [ 3] RW_IRAM1          NOBITS          20000008 001374 000660 00  WA 

# ER_IROM1是代码区， 写入到 FLASH中，加载到 RAM起始地址是 08000000，大小001338

# RW_IRAM1是全局数据，需要写入 FLASH 中，然后运行时候，初始化到20000000,也就是从 20001338 => 20000000 copy 8个字节
 
# RW_IRAM1 是.bss,不需要存储在 FLASH， 加载到内存的20000008
# 这里 只把 代码段(ER_IROM1) 写入到了 文件
arm-none-eabi-objcopy -O binary -j ER_IROM1 led.elf led_text.bin
# 这里 只把 代码段(RW_IRAM1) 写入到了 文件
arm-none-eabi-objcopy -O binary  -j RW_IRAM1  led.axf led_ram.bin
# 合并生成 flash 镜像
cat led_text.bin led_ram.bin >led.bin
```
- 4.烧录
```sh
# 工具准备
sudo apt install stm32flash

# 识别设备
stm32flash /dev/ttyUSB0

# -w：写入
# -v：校验
# -g 0x08000000：写完后从 Flash 跳转执行
stm32flash -w firmware.bin -v -g 0x08000000 /dev/ttyUSB0

```


### 问题：如何初始化全局变量的
- 编译器会 自动加入下面 的拷贝函数__scatterload_copy。
- 编译器会 准备 自动初始化的 表(scatter table).
- 按照 如下流程执行
```
Reset_Handler
  ↓
SystemInit
  ↓
__main
  ↓
__scatterload_rt2        ←【你正在看的】
  ↓
__scatterload_null 循环 ← 解析 scatter table
  ↓
__scatterload_copy / __scatterload_zi
  ↓
__rt_entry
  ↓
main()

```
```c
void scatterload_copy(void *dst, void *src, size_t len)
{
    while (len >= 16) {
        copy_16_bytes();
        len -= 16;
    }

    if (len & 8)
        copy_8_bytes();

    if (len & 4)
        copy_4_bytes();
}

08000128 <__scatterload_copy>:
 // memcpy(dst,src,cnt)
 //r0:src,r1:dst,r2:cnt
 //r2>16字节, 16字节16字节 拷贝

 8000128:       3a10            subs    r2, #16
 800012a:       bf24            itt     cs
 800012c:       c878            ldmiacs r0!, {r3, r4, r5, r6}
 800012e:       c178            stmiacs r1!, {r3, r4, r5, r6}
 8000130:       d8fa            bhi.n   8000128 <__scatterload_copy>

  //剩余
 8000132:       0752            lsls    r2, r2, #29
 8000134:       bf24            itt     cs
 8000136:       c830            ldmiacs r0!, {r4, r5}
 8000138:       c130            stmiacs r1!, {r4, r5}
 800013a:       bf44            itt     mi
 800013c:       6804            ldrmi   r4, [r0, #0]
 800013e:       600c            strmi   r4, [r1, #0]
 8000140:       4770            bx      lr

```

```c
// scatter table
08001318 <Region$$Table$$Base>:
 8001318:       08001338        .word   0x08001338   // src, LA, load address
 800131c:       20000000        .word   0x20000000   // dst, RA,runtime address
 8001320:       00000008        .word   0x00000008 // cnt
 8001324:       08000128        .word   0x08000128  // scatterload_copy的地址
 8001328:       08001340        .word   0x08001340 // src
 800132c:       20000008        .word   0x20000008 // dst .bss
 8001330:       00000660        .word   0x00000660 // cnt
 8001334:       08000144        .word   0x08000144 // _scatterload_zeroini的地址
```

