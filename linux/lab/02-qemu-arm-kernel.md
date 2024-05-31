[视频教程](https://www.bilibili.com/video/BV1PJ411m7fs/?spm_id_from=333.788.recommend_more_video.-1&vd_source=ba17c91d27a087001a89289fd2c2af49)

## 内核编译
- [kernel 下载地址](http://www.kernel.org)
- 默认配置：
- - .config文件包括编译内核的设置，eg: CONFIG_ARM=y...
- - make < soc_name >_defconfig表示导入soc_name的默认配置，soc_name参考arch/arm/configs下的文件。
- 定制化配置
- - make menuconfig最终也是修改.config文件。
- - <font color=pink>编译选项[]对应Y/N，<>对应Y/N/M， Y表示包含，N表示不包含，M表示编译成独立的模块（程序），也就是不会编译到uImage中.</font>
- 编译生成：
- - vmlinux:ELF格式的kernel，不能裸机运行
- - zImage: objcopy vmlinux  会获得 zImage(可用于裸机，但uboot不识别)
- - uImage: mkimage(zImage) 会获得uImage, mkimage需要apt安装或者编译查看uboot的tool目录。
- 编译内核模块
- - 编译menuconfih标注为 M的模块。
- - make modules
- - 会生成.ko(kernel object)的文件。eg:dm9000.ko

- 编译设备树
- - .dts是源码，.dtb是编译的二进制,dtsi是要被包含的文件，相当于.h文件。
- - dts:device tree source
- - 查看目录 arch/arm/dtbs
- - make dtbs:会编译 某个型号的全部设备树

```sh
wget https://mirrors.tuna.tsinghua.edu.cn/kernel/v5.x/linux-5.10.99.tar.xz
tar -xvf linux-5.10.99.tar.xz
cd linux-5.10.99


修改 Makefile
ARCH ?= arm
CROSS_COMPILE = arm-linux-gnueabi-


#编译配置
make vexpress_defconfig
#验证配置
make menuconfig
# 可选，对nfs4的支持
# File System —> Network File Systems—>NFS client support for NFS version 4

# 编译
# zImage为通用内核文件，modules是没有加载进内核的模块(驱动), dtbs为编译的设备树
make zImage  -j 2
make modules -j 2
make dtbs    -j 2
# uImage是专供u-boot引导的内核，这里暂时用不上，但是我们这里先编译，可能会有以下错误
# 0x60003000是kernel加载的起始地址
make LOADADDR=0x60003000 uImage  -j 2
# 编译好的文件在arch/arm/boot目录下

# 启动
qemu-system-arm    -M vexpress-a9 \
                   -kernel arch/arm/boot/zImage \
                   -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
                   -nographic      \
                   -m 512M \
                   -append "console=ttyAMA0"
```