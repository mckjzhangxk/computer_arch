- qemu模拟会出现商不足的情况，需要完成一轮[商初始化]才可以保证有些程序正确执行.[entropy_init.sh](entropy_init.sh)
```sh
# 查看
cat /proc/sys/kernel/random/entropy_avail
```
- 开启telnet
```sh
telnetd -l/bin/sh -p57561
```