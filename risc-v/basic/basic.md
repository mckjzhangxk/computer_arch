## 使用模拟器,运行我的程序

- 编译一个risc-v 32位的程序add.elf
```shell
 # qemu的程序入口是0x80000000,所以我们需要把程序的text设置到这里地址
 riscv64-unknown-elf-gcc -nostdlib \
                    -fno-builtin \
                    -march=rv32g \
                    -mabi=ilp32 \
                    -Ttext=0x80000000 \
                    -g add.s -o add.elf 
                   
```

- 使用模拟器，来启动这个程序
```shell
# -s 表示在qemu中，开启gdbserver,默认端口1234
# -S 表示stop在add.elf的入口点
qemu-system-riscv32 -nographic \
                    -smp 1 \
                    -machine virt \
                    -bios none \
                    -kernel add.elf \
                    -s -S
                    
```


- 使用gdb来远程调试一个程序
```shell

#把调试信息设置到全局
#vim ~/.gdbinit
#添加如下一行
# add-auto-load-safe-path /Users/zhanggxk/project/cs15213/risc-v/basic/.gdbinit

#启动调试
riscv64-unknown-elf-gdb add.elf -x .gdbinit
```