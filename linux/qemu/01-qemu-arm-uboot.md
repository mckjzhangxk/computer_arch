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

## uboot的使用
```sh
setenv ipaddr   192.168.33.144      # 设置u-boot这边的地址(和br0同一网段即可)
setenv serverip 192.168.33.145       # 设置服务器地址(br0网桥的地址)
tftp 0x60003000 uImage              # 从tftp下载uImage
tftp 0x60500000 vexpress-v2p-ca9.dtb   

# 让kernel知道，/dev/mmcblk0挂载rootfs
setenv bootargs "root=/dev/mmcblk0 rw console=ttyAMA0 ip= 192.168.33.144"
# 依次是kernel rootfs dtb
bootm 0x60003000 - 0x60500000


# 可以uboot编译的时候设置好bootcmd
make menuconfig
# Boot options —> Enable a default value for bootcmd，
# 输入以下内容
setenv ipaddr 192.168.33.144;setenv serverip 192.168.33.145;tftp 0x60003000 uImage;tftp 0x60500000 vexpress-v2p-ca9.dtb;setenv bootargs 'root=/dev/mmcblk0 rw console=ttyAMA0 init=/linuxrc ip= 192.168.33.144';bootm 0x60003000 - 0x60500000;

# 从 nfs 挂载 rootfs
setenv bootargs 'root=/dev/nfs rw nfsroot=192.168.33.145:/home/zhangxk/project/linux/rootfs,proto=tcp,nfsvers=3,nolock init=/linuxrc ip=192.168.33.144 console=ttyAMA0';bootm 0x60003000 - 0x60800000;
```
