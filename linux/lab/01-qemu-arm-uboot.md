[视频教程](https://www.bilibili.com/video/BV1PJ411m7fs/?spm_id_from=333.788.recommend_more_video.-1&vd_source=ba17c91d27a087001a89289fd2c2af49)

## uboot编译
```sh
# 交叉工具下载地址mac
# https://thinkski.github.io/osx-arm-linux-toolchains/

# 1.下载uboot源码
mkdir uboot
cd uboot
wget https://ftp.denx.de/pub/u-boot/u-boot-2022.07-rc3.tar.bz2
tar -xvf u-boot-2022.07-rc3.tar.bz2
cd u-boot-2022.07-rc3

# 2.设置uboot配置
# gedit Makefile +272,加入以下两行
#ARCH = arm 
# CROSS_COMPILE = arm-unknown-linux-gnueabi-



# 编译
make vexpress_ca9x4_defconfig
make -j 2
# 启动
qemu-system-arm    -M vexpress-a9 \
                     -kernel u-boot \
                     -nographic      \
                     -m 512M

qemu-system-arm    -M vexpress-a9 \
                     -kernel u-boot \
           -nic tap,ifname=tap0    \
                     -nographic      \
                     -m 512M     
```