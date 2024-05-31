[berkeley](https://inst.eecs.berkeley.edu/~cs61c/fa22/)

[中文教程](https://www.bilibili.com/video/BV1qH4y1C7oR/?spm_id_from=333.788&vd_source=ba17c91d27a087001a89289fd2c2af49)

[中文教程(汪辰老师)](https://www.bilibili.com/video/BV1Q5411w7z5?p=5&spm_id_from=pageDriver&vd_source=ba17c91d27a087001a89289fd2c2af49)


[指令编程(基础指令)](https://www.bilibili.com/video/BV19g4y1d7HP/?spm_id_from=333.337.search-card.all.click&vd_source=ba17c91d27a087001a89289fd2c2af49
)

## 基本的概念与指令

- RISC-V ISA有很多变种，根据字长有RV32,RV64,RV128.
- 指令是模块画的 I-基础整数，M-支持乘除，F-单精度浮点，D-双精度浮点.
- RISC-V 有X0-X31个寄存器，其中X0表示常量0
- <font color=pink>指令是32位的，字长是{32|64|128}位的，地址认为是4字节对齐的，但是可以访问byte,half word</font>
- 具体指令存储参考[riscv-card.pdf](riscv-card.pdf)，只要支持每个指令长度都是固定(32),但是分不同类的
- <font color=red>ALU指令格式(R类型)  oper dest src1 src2</font>
- <font color=red>ALU指令格式(I类型)  oper dest src1 imm,立即数imm是会符号扩展的</font>
- <font color=yellow>无条件跳转格式(J类型) jmp offset</font>
- <font color=pink>条件跳转格式(B类型)  comp src1 src2 offset</font>
- <font color=gree>地址加载格式(S类型)  lw/sw dest offset(base)</font>
- 每个算术指令都都一个立即数版本，如add->addi
- 伪指令：上面指令的快捷方式
```shell
需要注意的指令

#算术指令
slt rd rs1 rs2  # if rs1<rs2 rd=1 else rd=0
sltu rd rs1 rs2 #同上，但是认为 rs1,rs2是无符号的
sll  rd rs1 rs2 # rd=rs1<<rs2
srl  rd rs1 rs2 # rd=rs1>>rs2
sra  rd rs1 rs2 # rd=rs1>>rs2,但是rs1的最高位不会被移动

#跳转指令,主要针对函数的，把返回地址保存在rd中
#imm长度是20bits,所以只能跳转到-512K-512k的位置，而寄存器可以跳转的范围更大
jal  rd  imm # rd=pc+4, pc+=imm ，短跳转
jalr rd imm(x1)  # rd=pc+4, pc=x1+imm ，长跳转


lw rd imm(rs)   # rd=mem[rs+im][0:32]
sw rd imm(rs)   # mem[rs+im][0:32]=rd

#伪指令
li x4 0x12345678 
#等价于
lui x4 0x12345  #加载高20位，注意lui 是把 右移0x12345位后，再保存到x4中的，换言之给出的imm应该就是高20位
addi x4 x4 0x678 #加载高12位

#构造相对地址
auipc x4 0x12345 #x4=pc+ 0x12345<<12
```
![2.png](imgs%2F2.png)
```shell
#上面代码的解释

x1=mem[100]=base
x2=men[104]=n
sum=0

loop:
x4=base[0]
sum+=x4
base+=4
n-=1
if n!=0 goto loop
```
## 函数

有以下问题需要解决
- 跳转后如何返回？
- 函数的参数，局部变量都是怎么保存的？
- 如果存在函数调用函数的情况，caller的寄存器会被callee破坏，如何避免这样的发生？


### 跳转后如何返回？
把要返回的地址保存在ra(x1)中，这样函数执行完成后就可以返回了
```shell
#调用函数sum,ra=104
-----------main.c------------
100: jal ra  sum
104:
  ...
-----------sum.c------------
sum:
  ...
#返回到104
jal x0 ra
```

### 如何解决寄存器状态被破坏问题？
- 把寄存器保存到stack中(sp=x2）,<font color=pink>stack是向低地址增长的,sp总执行最后push的元素</font>
- C语言Caller与Callee之间的<font color=pink>调用约定</font>
- - <font color=red>如果caller使用了 t0-t6,a0-a7,那么调用函数的时候，caller需要现对这组寄存器保存与恢复。callee可以随意更改这些rd,而不去做现场恢复
- - 如何caller使用了 s0-s11,包括堆栈指针sp,调用函数的时候不需要做现场保护，callee保证这些rd调用前数值不变，换句话说，callee在使用这个si前，会做保护与恢复。</font>
- - ra寄存器应该也是由callee保存，这样才能在需要返回的时候，返回正确的ra
```shell
#push，保存t0
addi sp sp -4
sw   t0 0(sp)

#pop,恢复t0
lw  t0  0(sp)
addi sp sp 4
```


```asm
#demo 1 
- 函数的调用与返回
- 中间寄存器的保存

sum:
	mv	a4,a0 #a4=n
	li	a5,0
	li	a0,0
	j	.L2
.L3:
  #sum+=i
	addw	a0,a0,a5 
  #i++
	addiw	a5,a5,1
.L2:
  #if(i<n) goto L3
	blt	a5,a4,.L3 
	ret

sum_and_double:
  #保存ra
	addi	sp,sp,-16
	sd	ra,8(sp) 

	call	sum
	slliw	a0,a0,1 
	
  #恢复ra
  ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
```


```c
#demo2
- callee对约定寄存器的保护
- argc->a0,argv->a1
int dummymain(int argc,char ** argv){
   int total_sum=0;
   for (int i = 0; i < argc; ++i) {
        // total_sum+=strlen(argv[i]);
        printf("%s\n",argv[i]);
   }
   return total_sum;
}
//
dummymain:
  #使用了s0,s1,s2,callee约定这几个寄存器调用前后不能更改
  #所以这里保存
	addi	sp,sp,-32
	sd	ra,24(sp)
	sd	s0,16(sp)
	sd	s1,8(sp)
	sd	s2,0(sp)

	mv	s1,a0  #argc
	mv	s2,a1  #argv
	li	s0,0   #i
	j	.L2
.L3:
	slli	a5,s0,3 # a5=8*i
	add	a5,s2,a5  # a5=argv+8*i
	ld	a0,0(a5)  # a0=argv[i]
	call	puts
	addiw	s0,s0,1 #i++
.L2:
	blt	s0,s1,.L3 #if i<argc goto L3
	li	a0,0 
	ld	ra,24(sp)

  #对应的还原
	ld	s0,16(sp)
	ld	s1,8(sp)
	ld	s2,0(sp)
	addi	sp,sp,32
	jr	ra
```

```c
- demo3,展示了如何把大数组传递给函数的参数
- 1.先把数组的元素存到堆栈上，
- 2.把与参数对应的【堆栈的指针】赋值给参数寄存器
int dummyexec(){
   int argc=3;
   char * argv[]={
           [0]="ls",
           [1]="-p",
           [2]="-a"
   };
   return dummymain(argc,argv);


}


.LC0:
	.string	"ls"
.LC1:
	.string	"-p"
.LC2:
	.string	"-a"

dummyexec:
	addi	sp,sp,-48
  #存返回地址
  sd	ra,40(sp)
	
  #存'ls'字符串的位置，存到最低地址处
  lui	a5,%hi(.LC0)
	addi	a5,a5,%lo(.LC0)
	sd	a5,8(sp) #argv

  #存'-p'字符串的位置，
	lui	a5,%hi(.LC1)
	addi	a5,a5,%lo(.LC1)
	sd	a5,16(sp)

  #存'-a'字符串的位置，
	lui	a5,%hi(.LC2)
	addi	a5,a5,%lo(.LC2)
	sd	a5,24(sp)

	addi	a1,sp,8 #argv=sp+8
	li	a0,3 #argc
	call	dummymain

  #还原返回地址
	ld	ra,40(sp)
	addi	sp,sp,48
	jr	ra
```

### 参数与局部变量的保存
- a0-a7用于保存函数的参数
- 结构体，数组保存在堆栈上（sp）,通过把sp传递给ai达到传递参数的目的。
```C
#结构体demo
struct Entity
{
    int a;
    long b;
    short c;
};

int EntityParam(struct Entity x){
    printf("%d %d %d\n",x.a,x.b,x.c);
    return 0;
}
//struct Entity x，实际传的是x的一个机制a0,
// 从a0使用寻址,加载a,b,c
.LC0:
	.string	"%d %d %d\n"
EntityParam:
	addi	sp,sp,-16
	sd	ra,8(sp)
  #加载c
	lh	a3,16(a0)
  #加载b
	ld	a2,8(a0)
  #加载a
	lw	a1,0(a0)
	lui	a0,%hi(.LC0)
	addi	a0,a0,%lo(.LC0)
	call	printf
	li	a0,0
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
```


```C
int EntityParamCaller(){
    struct Entity x;
    x.a=100;
    x.b=10;
    x.c=1;
    EntityParam(x);
}

EntityParamCaller:
	addi	sp,sp,-80
	sd	ra,72(sp)
	li	a5,100      
	sw	a5,40(sp)   //x.a=100
	li	a5,10        
	sd	a5,48(sp)   //x.b=10 
	li	a4,1        
	sh	a4,56(sp)  //x.c=1

	ld	a4,40(sp)
	sd	a4,0(sp)  //arg.a=x.a
	sd	a5,8(sp)  //arg.b=x.b
	ld	a5,56(sp)  
	sd	a5,16(sp)  //arg.c=x.c
	
	mv	a0,sp  //arg=$sp
	call	EntityParam
	ld	ra,72(sp)
	addi	sp,sp,80
	jr	ra
___________    
|    ra   | 72
|---------|
|         |
|---------|
|     1   | 56
|---------|
|   10    | 48
|---------|
|  100    | 40
..........
.........

|---------|
|     1   |  16
|---------|
|    10   |  8
|---------|
|   100   |  0
|_________|
```