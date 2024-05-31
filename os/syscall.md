## 系统调用
- 应用程序调用write/read这样的函数，跳转到kernel的代码，这中间有几个问题
- - CPU模式需要变化，可以执行特权指令
- - pagetable需要切换，这样才能运行kernel的代码
- - 堆栈需要改变，因为pagetable切换了，kernel代码才有自己的栈存储空间
- - 用户的寄存器需要被保护，C语言只会在堆栈上做寄存器的保护，堆都变成kstack，这部分代码需要我们手动来写
## Trampoline
- 这是一段从用户跳转到 kernel的代码
- - 需要进行pagetable的切换
- - 切换前，保存用户寄存器，为进入kernel设置入口点，堆
- - 因为不论在UserAs还是在Kernel As，执行的都是物理地址的同一段代码，所以才可以完成