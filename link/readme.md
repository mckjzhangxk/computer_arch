# 本章节的实际应用
有[addvec.c](lib%2Faddvec.c)，[multvec.c](lib%2Fmultvec.c) 两个我开发的库文件
## 静态库
- 生成库文件
```shell
#先生成.o文件
clang -g  -c  addvec.c multvec.c
#再打包成.a文件
ar rcs libvector.a addvec.o multvec.o
```
- 检查库文件
```shell
# 可以看到 addvec.o 中 addcnt，addvec，multvec.o中 multcnt，multvec，共四个符号
nm libvector.a 
```

- 使用库文件
```shell
clang libvector.a link_call_static.c -o link_call_static
# 可以看到 addcnt，addvec，multcnt，multvec四个符号,说明引用的是静态库
nm link_call_static
```
## 编译动态库
- 编译库文件
```shell
#注意mac下会 libvector.dylib.dSYM文件夹，这是符号表，用于gdb
clang -shared -fpic  -o libvector.dylib  addvec.c multvec.c

# 可以看到 addcnt，addvec，multcnt，multvec四个符号
nm libvector.dylib
```
- 编译时使用库文件
```shell
clang libvector.dylib link_call_shared.c -o link_call_shared

# 只有_addvec,_multvec两个符号，说明没有把函数的实现打包到link_call_shared中
nm link_call_shared
```
- <font color=red>运行时使用动态库</font>
```shell
#先检查下需要的动态库
ldd link_call_shared        #linux
otool -L link_call_shared   #mac

#需要的库路径设置给如下的环境变量,环境变量表示运行时 动态库文件检索目录
LD_LIBRARY_PATH         #linux
DYLD_LIBRARY_PATH       #mac

#执行程序
./link_call_shared
```
## 同时存在 静态动态库，链接器会先选择谁
假设同时存在 libvector.a,libvector.dylib在build目录，使用如下命令
```shell
clang -L build  -lvector main.c  -o main
```
生成的main使用的是libvector.dylib.
## 单步调试库文件
- 保证运行时，可以找到对应的动态库
- - 设置LD_LIBRARY_PATH环境变量
- - 或拷贝动态库到 [cmake-build-debug](..%2Fcmake-build-debug)
- 库源代码必须在工程内部
- 对呀mac,符号表目录dylib.dSYM不要删除


注意以下问题：
- <font color=pink>符号表，源代码，生成的dylib文件版本要一致,不然clion能步入</font>。
- clion会对项目中的文件建立索引，所以【源代码，符号表】放在任何目录下都不影响clion能步入
## 级联调用
库[linear.c](lib%2Flinear.c)的函数调用libvector的函数，把linear.c也做成共享库，由
[link_call_linear.c](link_call_linear.c)来调用。

```
link_call_linear->liblinear(shared lib)->libvector(shared lib)
```
按照上面的步骤，可以看出 调试 是完全没有问题的。

## PIC
- position independ code：与位置无关的代码
- PIC对全局数据的 引用
- - <font color=red>全局变量 进程是不共享的</font>
- - <font color=red>对全局变量的引用需要 动态连接器 重定向</font>
- - GOT: 数据段的开头保存这张表，表每个入口都是对全局数据的引用
- - 代码段与数据段的偏移是常数，
- - 生成的对全局变量的引用，利用了上面的特性，引用的是GOT表中定义的地址。

libvector.so
```C
int addcnt = 0;
void addvec(int *x, int *y,int *z, int n) 
{
    addcnt++;

}
```

```shell
数据段
GOT[0]
GOT[1]
GOT[2]=&addcnt  #&addcnt的地址,动态连接器会 重定向这个数值！

代码段
mov 1234(%rip) %ax #GOT[2]相对于当前位置rip的偏移是 1234
                  # 把这个地址的数值&addcnt，赋值给ax
add 1 (%ax)         # 等价于 
```
## 符号表/调试信息
- 符号表是记录程序中 函数的名字，全局变量，局部变量等等。
- 在符号表的基础上，可以加入关于调试的信息，才可以使用gdb来进行调试。
- <font color=red>nm,strip工具是用于查看符号表和删除符号表的工具</font>
```shell
#T表示text,D-全局变量，S-未初始化全局变量，U-没有定义的符号(.o文件出现)
nm libc.a |grep memset|grep T

#仅剥离调试信息，保留符号表
strip -g a.out
#剥离所有符号表和调试信息
strip -s a.out
```

## libc
- glibc是gnu library C,其中包括许多系统调用和对posix的支持
- uClibc是嵌入设备用的C库，体积很小
```sh
# 以下方法可以查看libc的版本
# 1
ldd --version
# 2
/lib64/libc.so.6
```
## 调试ffmpeg源码
- 编译的时候加入了--extra-cflags=-g,【非必须】
- 手动创建了符号表 [symbol.sh](symbol.sh)

## mac下生成符号表

```shell
dsymutil aa.dylib
```