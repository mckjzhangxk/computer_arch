[视频教程](https://www.bilibili.com/video/BV1PJ411m7fs/?spm_id_from=333.788.recommend_more_video.-1&vd_source=ba17c91d27a087001a89289fd2c2af49)

## 内核编译
- [kernel 下载地址](http://www.kernel.org)
- 默认配置：
- - .config文件包括编译内核的设置，eg: CONFIG_ARM=y...
- - make < soc_name >_defconfig表示导入soc_name的默认配置，soc_name参考<font color=pink>arch/arm/configs</font>下的文件。
- 定制化配置
- - make menuconfig最终也是修改.config文件。
- - <font color=pink>编译选项[]对应Y/N，<>对应Y/N/M， Y表示包含，N表示不
包含，M表示编译成独立的模块（程序），也就是不会编译到uImage中.</font>
- - KConfig文件对应Menuconfig的配置菜单，最终以<font color=gree>CONFIG_{KEY}={VAL}的形式写入到.config文件中</font>。KEY对应某个 特性,VAL一般对应 -y(编译进内核),-m(编译成模块)


- 编译生成：
- - vmlinux:ELF格式的kernel，不能裸机运行
- - zImage: objcopy vmlinux  会获得 zImage(可用于裸机，但uboot不识别)
- - uImage: mkimage(zImage) 会获得uImage, <font color=gree>uboot 引导加载时需要的kernel格式</font>,mkimage需要apt安装或者编译查看uboot的tool目录。
- 编译内核模块
- - 编译menuconfig标注为 M的模块。
- - make modules
- - 会生成.ko(kernel object)的文件。eg:dm9000.ko

- 编译设备树
- - .dts是源码，.dtb是编译的二进制,dtsi是要被包含的文件，相当于.h文件。
- - dts:device tree source
- - 查看目录 arch/arm/dtbs
- - make dtbs:会编译 某个型号的全部设备树

```sh
#############64位arm编译步骤########
#也可使用以下命令而不修改 Makefile
# 深度clean
make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- mrproper
# 64位arm只有 defconfig, 这里是默认的virt设备
make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- defconfig
make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- menuconfig

make -j2 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- all
make -j2 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- modules
make -j2 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- dtbs
#######################################

```
```sh
# https://git.kernel.org/
# git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git
# v5.15.163
# git clone ${KERNEL_REPO} --depth 1 --single-branch --branch ${KERNEL_VERSION}
# git clone git://git.kernel.org/pub/scm/linux/kernel/git/stable/linux-stable.git --depth 1 --single-branch --branch v5.15.0

wget https://mirrors.tuna.tsinghua.edu.cn/kernel/v5.x/linux-5.10.99.tar.xz
tar -xvf linux-5.10.99.tar.xz
cd linux-5.10.99


修改 Makefile: 370行
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
                   -append "console=ttyAMA0"  #传递给内核的参数
```


## 内核模块选择


|配置名称|作用|开启|
|-|-|-|
|CONFIG_KALLSYMS|支持kallsyms_lookup_name(查询所有符号地址的函数,/proc/kallsyms),||
|CONFIG_FUNCTION_TRACER|ftrace的支持||
|CONFIG_FUNCTION_GRAPH_TRACER|ftrace的支持||
|CONFIG_FTRACE_SYSCALLS|ftrace的支持||
|CONFIG_DYNAMIC_FTRACE|ftrace的支持||
|CONFIG_DEBUG_FS|查看支持trace的调用:/sys/kernel/debug/tracing/available_filter_functions||




```sh
# 验证是否开启ftrace
zcat /proc/config.gz |grep CONFIG_?
# 是否包含以下
# linux:4.19
CONFIG_FUNCTION_TRACER=y
CONFIG_FUNCTION_GRAPH_TRACER=y
CONFIG_DYNAMIC_FTRACE=y
CONFIG_FTRACE_MCOUNT_RECORD=y

# linux:4.9.118
CONFIG_HAVE_FUNCTION_TRACER=y
CONFIG_HAVE_FUNCTION_GRAPH_TRACER=y
CONFIG_HAVE_DYNAMIC_FTRACE=y
CONFIG_HAVE_FTRACE_MCOUNT_RECORD=y
```


```sh
# 开启 CONFIG_DEBUG_FS：
# Kernel hacking  ---> 
    # [*] Debug Filesystem
#临时挂载 
mount -t debugfs none /sys/kernel/debug
# 将挂载持久化（可选）：在 /etc/fstab 中添加以下行：
debugfs  /sys/kernel/debug  debugfs  defaults  0  0

zcat /proc/config.gz | grep CONFIG_DEBUG_FS
```