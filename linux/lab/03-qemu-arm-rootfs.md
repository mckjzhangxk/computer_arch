[视频教程](https://www.bilibili.com/video/BV1PJ411m7fs/?spm_id_from=333.788.recommend_more_video.-1&vd_source=ba17c91d27a087001a89289fd2c2af49)


## 制作[rootfs](https://www.zhaixue.cc/qemu/qemu-build_busybox_rootfs.html)
[最终rootfs镜像](rootfs/rootfs.ext3)
- bin普通二进制，sbin:super bin
- /initrc: kernel启动后第一个进程。
- /dev,/sys: kernel把设备文件，设备信息写入到这里。
- /proc: kernel把进程进行写入到这里。

### busybox
- 用于编译常用的工具集，例如ls,cp...
```sh
wget https://busybox.net/downloads/busybox-1.35.0.tar.bz2
tar -xvf busybox-1.35.0.tar.bz2

# 编辑Makefile +192
ARCH ?= arm
CROSS_COMPILE = arm-linux-gnueabi-


make menuconfig
# (1) 添加vi
# Settings —-> [*] vi-style line editing commands (New)

# (2) 设置安装路径
# Settings —-> Destination path for ‘make install’

# (3) 应该是上面的工具编译不用shared libs
#  这一步的原因是：运行linuxrc时失败，库的版本不兼容等，解决方法是编译busybox时，配置静态编译：
# Settings —->  Build static binary (no shared libs)

# 编译与安装
make  -j 2
make install
```

```sh 
方法2
make distclean
make ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- defconfig
make -j2 ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- 
make CONFIG_PREFIX=/tmp ARCH=arm64 CROSS_COMPILE=aarch64-none-linux-gnu- install

# 查看busybox需要的 动态库
aarch64-none-linux-gnu-readelf -a busybox |grep "program interpreter:"
aarch64-none-linux-gnu-readelf -a busybox |grep "Shared library"
```
### 制作动态库
```sh
# 在ubuntu上，arm的动态库所在位置
cd /usr/arm-linux-gnueabi/lib
# -d表示复制符号Link,而不是inode
cp -d * /home/hack520/project/rootfs/lib
```

### 制作etc

- 设置环境变量/etc/profile
```sh
mkdir etc
cd etc
vi profile

# 内容：
USER="root"
LOGNAME=$USER
export HOSTNAME=`cat /etc/sysconfig/HOSTNAME`
export USER=root
export HOME=/root
export PS1="[$USER@$HOSTNAME \W]\# "
PATH=/bin:/sbin:/usr/bin:/usr/sbin
LD_LIBRARY_PATH=/lib:/usr/lib:$LD_LIBRARY_PATH
export PATH LD_LIBRARY_PATH
```

- 增加主机名/etc/sysconfig/HOSTNAME
- - 注意 这个/etc/sysconfig/HOSTNAME是自定义的，主要是与上面profile脚本那里HOSTNAME变量 对应就行。
```sh
cd etc
mkdir sysconfig
vi sysconfig/HOSTNAME

# 内容：
vexpress
```

- /etc/init.d/rcS
- -问题？为什么是rcS这个名字？
```sh
cd etc
mkdir init.d
vi rcS
chmod 777 rcS
# 内容：

#!/bin/sh
# 关于 mount
#  mount -t type device dir
# type:ramfs,sysfs都是文件系统，如同ext3
# device:none-标识无设备,ramfs-标识内存？

#!/bin/sh
PATH=/bin:/sbin:/usr/bin:/usr/sbin 
export LD_LIBRARY_PATH=/lib:/usr/lib
/bin/mount -n -t ramfs ramfs /var
/bin/mount -n -t ramfs ramfs /tmp
/bin/mount -n -t sysfs none /sys
/bin/mount -n -t proc none /proc
/bin/mount -n -t ramfs none /dev

/bin/mkdir /var/tmp
/bin/mkdir /var/modules
/bin/mkdir /var/run
/bin/mkdir /var/log
/bin/mkdir -p /dev/pts
/bin/mkdir -p /dev/shm
/sbin/mdev -s
/bin/mount -a
echo "-----------------------------------"
echo "*****welcome to vexpress board*****"
echo "-----------------------------------"
```

### 创建设备结点
```sh
mkdir dev
cd dev
# mkdir -m 权限 name 设备类型 主节点号 从节点号
# c-字符设备，比如串口
mknod -m 666 tty1 c 4 1
sudo mknod -m 666 tty2 c 4 2
sudo mknod -m 666 tty3 c 4 3
sudo mknod -m 666 tty4 c 4 4
sudo mknod -m 666 console c 5 1
sudo mknod -m 666 null c 1 3
```

### 设置文件系统/etc/fstab
- /sbin/init会读取这个文件，加载文件系统
- 没有加载的时候，top，proc都无法正常运行
- 对下面配置中的 fs type,device还有疑问？？
```sh
vi /etc/fstab
# device   dir  type option dump pass,见k8s linux

proc    /proc           proc    defaults        0       0
none    /dev/pts        devpts  mode=0622       0       0
mdev    /dev            ramfs   defaults        0       0
sysfs   /sys            sysfs   defaults        0       0
tmpfs   /dev/shm        tmpfs   defaults        0       0
tmpfs   /dev            tmpfs   defaults        0       0
tmpfs   /mnt            tmpfs   defaults        0       0
var     /dev            tmpfs   defaults        0       0
ramfs   /dev            ramfs   defaults        0       0

```
### 设置初始化脚本/etc/inittab
- 貌似没有作用
```sh
vi /etc/inittab

# 内容
::sysinit:/etc/init.d/rcS
::askfirst:-/bin/sh
::ctrlaltdel:/bin/umount -a -r
```
### 必要目录
```sh
mkdir mnt proc root sys tmp var
```

## 制作根系统镜像sd卡
```sh
# 空文件
dd if=/dev/zero of=rootfs.ext3 bs=1M count=32
# 初始化文件系统
mkfs.ext3 rootfs.ext3

# 挂载拷贝
sudo mount -t ext3 rootfs.ext3 /mnt -o loop
sudo cp -r /home/hack520/project/rootfs/* /mnt
sudo umount /mnt
```

### 制作根系统RAMFs
```sh
cd ${OUTDIR}/rootfs
find .|cpio -H newc -ov --owner root:root > ${OUTDIR}/initramfs.cpio
gzip -f initramfs.cpio
```

## 启动kernel
```sh
qemu-system-arm    -M vexpress-a9 \
                   -kernel arch/arm/boot/zImage \
                   -dtb arch/arm/boot/dts/vexpress-v2p-ca9.dtb \
                   -nographic      \
                   -m 512M \
                   -append "root=/dev/mmcblk0 rw console=ttyAMA0" \
                   -sd rootfs.ext3
```


### 补充，编译x86的linux(qemu)内核

```sh
make x86_64_defconfig

make menuconfig
# 1/在 Device Drivers 中启用 Virtio drivers。
# 2/在 Networking support 中启用 Virtio network driver。

# 3.Device Drivers -> Network device support -> Ethernet driver support -> Intel devices
# 确保启用了 Intel(R) PRO/1000 Gigabit Ethernet support（即 e1000 驱动），以及 e1000e 驱动（支持更新型号）。


make -j


qemu-system-x86_64    -M pc \
                      -kernel bzImage \
                      -nographic      \
                      -m 512M \
                      -device virtio-rng-pci \
		              -nic vmnet-shared \
                      -append "root=/dev/sda rw console=ttyS0" \
                      -hda rootfs_busybox.x86.ext3
```



