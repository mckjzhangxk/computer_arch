- 准备好uImage(4864120 byte),dtb(4864184 byte),放到tftp的根目录,
- uImage 起始地址 0x60003000,vpress开发本的内存起始地址是0x60000000,见[vexpress-v2p-ca9.dts](设备树demo/vexpress-v2p-ca9.dts)
- dtb 起始地址 0x60003000+4864184=0x604a68b8,我取证0x65000000

- <font color=red>tftp主要用于让uboot下载kernel和dtb
- nfs主要用于kernel加载rootfs</font>
## uboot启动
```sh
# 与uboot原始启动相比，加入的网卡(nic，桥接模式),SD卡，与串口
qemu-system-arm    -M vexpress-a9 \
                     -kernel u-boot \
                     -nographic      \
                     -m 512M \
                     -nic tap,ifname=tap0 \
                     -append "root=/dev/mmcblk0 rw console=ttyAMA0" \
                     -sd rootfs.ext3
#  原始命令
#  qemu-system-arm    -M vexpress-a9 \
#                      -kernel u-boot \
#                      -nograp
```

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
# Boot options —> Enable a default value for bootcmd，
# 输入以下内容
setenv ipaddr 192.168.33.144;setenv serverip 192.168.33.145;tftp 0x60003000 uImage;tftp 0x60500000 vexpress-v2p-ca9.dtb;setenv bootargs "root=/dev/mmcblk0 rw console=ttyAMA0 ip= 192.168.33.144";bootm 0x60003000 - 0x60500000;
```


## nfs挂载文件系统
 
```sh
tftp 0x60003000 uImage
tftp 0x60800000 vexpress-v2p-ca9.dtb
setenv bootargs 'root=/dev/nfs rw nfsroot=192.168.33.145:/home/zhangxk/project/linux/rootfs,proto=tcp,nfsvers=3,nolock init=/linuxrc ip=192.168.33.144 console=ttyAMA0'
bootm 0x60003000 - 0x60800000

# 可以uboot编译的时候设置好bootcmd
# Boot options —> Enable a default value for bootcmd，
# 输入以下内容
tftp 0x60003000 uImage;tftp 0x60800000 vexpress-v2p-ca9.dtb;setenv bootargs 'root=/dev/nfs rw nfsroot=192.168.33.145:/home/zhangxk/project/linux/rootfs,proto=tcp,nfsvers=3,nolock init=/linuxrc ip=192.168.33.144 console=ttyAMA0';bootm 0x60003000 - 0x60800000;

qemu-system-arm    -M vexpress-a9 \
                     -kernel u-boot \
                     -nographic      \
                     -m 512M \
                     -nic tap,ifname=tap0 \
                     -append "console=ttyAMA0"
```