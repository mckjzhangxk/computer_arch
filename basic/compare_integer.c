
#include <stdio.h>

//absdiff_unsigned:
//.LFB0:
//.cfi_startproc
//        cmpb	$3, %dil
//        jbe	.L2
//        leal	-3(%rdi), %eax
//        ret
//.L2:
//        movl	$3, %eax
//        subl	%edi, %eax
//        ret
//.cfi_endproc
#include <unistd.h>
unsigned char absdiff_unsigned(unsigned char x) {
    unsigned char result;
    if (x > 3)
        result = x - 3;
    else
        result = 3 - x;
    return result;
}
//.cfi_startproc
//        cmpb	$3, %dil
//        jle	.L5
//        leal	-3(%rdi), %eax
//        ret
//.L5:
//movl	$3, %eax
//        subl	%edi, %eax
//        ret
//.cfi_endproc
char absdiff_sign1(char x) {
    char result;
    if (x > 3)
        result = x - 3;
    else
        result = 3 - x;
    return result;
}

//.cfi_startproc
//        cmpb	$-4, %dil
//        jl	.L2
//        leal	-3(%rdi), %eax
//        ret
//.L2:
//movl	$3, %eax
//        subl	%edi, %eax
//        ret
//.cfi_endproc
char absdiff_sign2(char x) {
    char result;
    if (x > -5)  //等级与 x>=-4
        result = x - 3;
    else //等级与x<-4
        result = 3 - x;
    return result;
}

//条件分支的学习：

// CF:加法的进位或者减法的借位会设置CF=1
// ZF：算术运算=0，被设置
// SF：算术运算结构最高位=1，SF被设置=1
// OF：算术加法(补码) 输入最高位相同，输出最高位变化，被设置为1
// 溢出表示结果从一个整数变成负数，或者从一个负数变成一个整数

//CF 针对 unsigned int
//SF,OF针对 signed  int


//cmp src2 src1 计算 src1-src2
//规则：
//1)src1==src2，ZF=1
//2）如果产生借位，CF=1
//3）SF = （src1-src2计算 结果)的最高位
//4) OF= src+comp(src2)，结果是否发生溢出


//不论对于sign,unsigned的比较，不进行区分，统一使用
//cmp  src2 src1 指令，区别在于对于 结果的判断：

//A.对于unsigned int
//ja(>): CF=0 and ZF=0 => (~CF) & (~ZF)
//jb(<): CF=1  => CF

//B.对于 signed int
//jl(<): (SF=1 and OF=0) or (SF=0 and OF=1)==> SF xor OF
//jle(<=) : (SF xor OF) | ZF
//jg(>) : ~(SF xor OF) & ~ZF, 理解：ZF=0 and (SF=0 and OF=0) or(SF=1 and OF=1)
//jge(>=): ~(SF xor OF)

// gcc  -Og -fno-if-conversion -S compare_integer.c

int main() {

    char a = 5;
    char b = 3;

    if (a > b) {
        printf("a>b");
    }
}