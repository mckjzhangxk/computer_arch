
```shell
si #逐指令,对汇编很重要
step #逐语句，进入
n #逐语句，不进入
finish #结束当前函数
c #continue

b #打断点
delete $num #删除断点
info b  #查看断点
info reg  #查看寄存器


print /x $var  #打印hex
print /x *p    #打印结构体

x /c $a1    #打印a1所指的字符
x /2c $a1   #
x /s $a1    #打印a1所指的字符串
x /3i $pc   #打印当前pc下的3行指令
x /14xb $sp #打印从sp地址开始，的14个byte,16进制显示

tui enable 
layout asm #汇编   显示窗口
layout src #源码   显示窗口
layout reg #寄存器 显示窗口

focus asm #汇编   显示窗口
focus src #源码   显示窗口
focus reg #寄存器 显示窗口


file $file #切换调试file

#打印数组
p *array@32

#查看 0x5555555551a2的代码
disassemble 0x5555555551a2


backtrace  #打印调用轨迹
```


## qemu调试
```sh
```sh
# 内核编译启用：
# 启用 CONFIG_DEBUG_INFO（生成调试符号）。
# 启用 CONFIG_GDB_SCRIPTS（用于 GDB 脚本支持）。

# 启动 GDB
gdb-multiarch vmlinux
# 连接到 QEMU
target remote :1234
# (1) 加载符号表
symbol-file vmlinux
# (2) 设置断点
break start_kernel
break sys_mkdir
```

## 编译注意
- 加入-g,-O0，不要优化代码。
- 如果使用buildroot,可以安装gdb，gdbserver调试程序
```sh


# target上安装 gdb,gdbserver的步骤：

# make menuconfig
#   ToolChain -> Enable C++ support
#   Target Package ->Debugging, profiling and benchmark
BR2_PACKAGE_GDB =y
BR2_PACKAGE_GDB_SERVER =y

# 编译本机跨平台gdb
#   ToolChain -> enable cross gdb
BR2_PACKAGE_HOST_GDB =y


# Build options –-> build packages with debugging symbols
# Build options –-> 停用 strip target binaries
```
