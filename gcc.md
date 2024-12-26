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