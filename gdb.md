
```shell
si #逐指令,对汇编很重要
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
```