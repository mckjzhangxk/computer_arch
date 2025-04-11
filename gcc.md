[交叉工具链](https://developer.arm.com/downloads/-/gnu-a)
## sysroot
- <font color=gree>编译文件时候，使用的文件系统路径</font>
- 编译器名字：arm-{os}-{vender}-gcc
- /usr/lib 静态库
- /lib 动态库
- /usr/include

```sh
arm-buildroot-linux-uclibcgnueabi-gcc --print-sysroot

arm-none-eabi-gcc --print-sysroot


# 没有成功
arm-none-eabi-gcc --sysroot=/Users/zhanggxk/Downloads/gcc-arm-10.3-2021.07-x86_64-arm-none-linux-gnueabihf/arm-none-linux-gnueabihf/libc/
```

## Makefile
```
all: library.cpp main.cpp

$@ => all
$< => library.cpp
$^ => library.cpp main.cpp
```

## gcc选项
- -nostdlib: 不会自动链接libc,会链接crt0.o
- -nostartfiles: 包含libc，不包含crt0.o
- -ffreestanding:不依赖标准库（ASIN C）环境（不假设 main() 入口）,eg:定义_GCC_WRAP_STDINT_H宏为0
- -ffreestanding -nostdlib:完全裸机模式,libc,crt0都不包含.
- -fvisibility=hidden:让所有符号默认 hidden.