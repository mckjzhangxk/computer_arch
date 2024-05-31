## 虚拟内存 
- 在程序中，我们的代码段从0开始，数据端的变量引用，等等使用的都是虚拟内存
- 实现vm的物理基础是cpu的mmu,mmu根据pagetable，把va转换成pa
- 在risc-v中，进程把pagetable的物理地址写到satp中，mmu是根据satp寄存器进行的

## Page Table
- 一个最直接的问题就是 Page Table应该多大？
- 64位cpu 每个进程需要管理2^64个va,这太大了，我们引入了page的概念，page=4k,每次os分配4k的空间
- 这样需要管理的位数就是 64-12=52了，risc-v规定头25位目前不进行使用，那么就有52-25=27bit地址空间需要管理
- 2^27=128M,对于1个进程，需要128M个地址需要管理，如果每个地址管理记录(PTE)占8字节，需要的空间,那么就需要1G的空间
- 所以采用了分层的设计，把27位分成了9+9+9 三层,从第一层的PTE，找到的是第二次的表，从第二层表的PTE找到的是第三层的表，从第三层的PTE找到的是真实的物理地址。
- 2^9=512,如果PTE=8字节，第一层表需要8*512=4k,第三层表可以管理 512x4k=2M的空间，第二层表可以管理2M*512=1G的空间
## PTE
- page table entry
- 10bit保留 +44bit PPN+10bit flag
- PPN是PA的高44为
- flags: U X W R V
```shell
V表示这个PTE是否有效
R表示PTE对应的物理页是否可读
W表示。。。。。。。。。 可写
X表示                可执行
U表示在用户模式 下是否可以访问本PTE对应的物理页
```
## kernel的VA与PA的对应关系
![kernel.png](imgs%2Fkernel.png)
- kernel把自的Kernal base以下的地址与物理地址做了一一映射，这部分物理地址对应这设备IO，使用mmap进行设备编程。
- Kernel text,Kernel data这里也是与物理地址做了一一映射
- - kernel代码执行的时候是在M模式，所以物理地址保存着kernel的代码，以及代码中定义的全局变量
- - kernel data中包括很多重要的数据结果，比如freelist,cpus[4],struct proc proc[NPROC]等
- - 从Kernel data到PHYSTOP这里被kernel认为是 可用的内存，与物理内存一一映射，这样kernel就可以很方便的使用kalloc分配物理内存了
- - kalloc分配的是kernel的虚拟内存，但是这块虚拟内存与PA是一一映射的，所以相当于分配物理内存
- 把Trapoline这段代码映射到了 kernel vm的最高的一个 4k的空间
- - Trapoline代码的物理地址，其实已经被kernel text映射过了，也就是说vm的 kernel text与Trapline映射了相同一段物理都在，这种现象叫做double mapping.
- - Trapoline代码在kernel space,user space映射是完全一致的，完成的是用户code 到kernel code的跳转
- - 在Trapoline代码中，会进行pagetable的切换，切换后跳转到usertrap，切换之前是在用户空间，切换之后是在kernel空间，切换后代码可以正常正常运行就是因为上面的double mapping
- 在Trapoline之后，为每个进程都分配一个kernel stack
- - 进程在用户空间的时候使用用户的栈，在kernel空间的时候使用kstack,这样不会互相干扰
- - 在trapoline代码中，把sp设置成了kstack+4k(我一直认为kernel的stack是往高处增长的，是错误的，C代码一定是让stack往低处增长)
- - 即使kernel想复用user的stack也不是容易的事情，因为trapline 代码已经切换了pagetable，如果不切换kstack，sp也不是指向用户空间的stack.只有拿着用户空间的pagetable，才能找到用户stack的物理地址，
- - kstack有个没有被映射过的guard page是防止堆溢出，这个我能理解，但好像最后一个进程没有这个guard page的保护，而第一个guard page也没有起到过什么保护作用
## user app的VA与PA的对应关系
![user.png](imgs%2Fuser.png)
- 每个进程都有一个sz属性，表示进程分配的vm大小
- 我们知道函数的入口是int main(int argc,char* argv[]),但是不太连接这2参数是怎么被os设置的？
- - 在调用exec(argc,argv)的时候，os根据argv[0]的ELF格式，加载text,bss,data
- - 然后为应用分配一个page大小的栈，把argv[0],...argv[argc-1]都入栈
- - 在把argv[i]加入栈的时候，同时记录压栈时候sp的数值到ustack[i]中，最后把ustack数组也压入栈，把此时的sp赋值给a1寄存器，这就是argv
- - stack下面映射了一个不可以RW的guard page，防止栈溢出
- Trapframe 保存切换空间需要的配置，以及需要保存的寄存器
- - 跳转到kernel 的入口地址
- - kernel 使用的kstack
- - kernel 的pagetable
- - 调回user空间的地址(epc)
- - 32个通用寄存器寄存器