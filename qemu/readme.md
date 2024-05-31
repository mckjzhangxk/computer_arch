[英文教程](https://www.youtube.com/watch?v=yN0hPYrKjqc&t=1018s)

[中文教程](https://space.bilibili.com/382223675/channel/seriesdetail?sid=522660)

```sh
sudo apt install qemu-system


# -boot d表示从cdrom 启动
qume-system-x86_64 --cdrom my.iso -boot d
qume-system-x86_64 --cdrom my.iso -boot d -cpu host -enable-kvm -smp 2 -m 2G

# 创建一个虚拟磁盘
qemu-img create -f qcow2 HDA.img
```