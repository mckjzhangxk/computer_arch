	.file	"sum.c"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16
	.text
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align	3
.LC0:
	.string	"%d %d %d\n"
	.text
	.align	1
	.globl	EntityParam
	.type	EntityParam, @function
EntityParam:
	addi	sp,sp,-16
	sd	ra,8(sp)
	lh	a3,16(a0)
	ld	a2,8(a0)
	lw	a1,0(a0)
	lui	a0,%hi(.LC0)
	addi	a0,a0,%lo(.LC0)
	call	printf
	li	a0,0
	ld	ra,8(sp)
	addi	sp,sp,16
	jr	ra
	.size	EntityParam, .-EntityParam
	.align	1
	.globl	EntityParamCaller
	.type	EntityParamCaller, @function
EntityParamCaller:
	addi	sp,sp,-80
	sd	ra,72(sp)
	li	a5,100
	sw	a5,40(sp)
	li	a5,10
	sd	a5,48(sp)
	li	a4,1
	sh	a4,56(sp)

	ld	a4,40(sp)
	sd	a4,0(sp)
	sd	a5,8(sp)
	ld	a5,56(sp)
	sd	a5,16(sp)
	
	mv	a0,sp
	call	EntityParam
	ld	ra,72(sp)
	addi	sp,sp,80
	jr	ra
	.size	EntityParamCaller, .-EntityParamCaller
	.ident	"GCC: (GNU) 10.2.0"
