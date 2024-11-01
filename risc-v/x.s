
sum.o:     file format elf64-littleriscv


Disassembly of section .text:

0000000000000000 <EntityParam>:
   0:	1141                	addi	sp,sp,-16
   2:	e406                	sd	ra,8(sp)
   4:	01051683          	lh	a3,16(a0)
   8:	6510                	ld	a2,8(a0)
   a:	410c                	lw	a1,0(a0)
   c:	00000537          	lui	a0,0x0
  10:	00050513          	mv	a0,a0
  14:	00000097          	auipc	ra,0x0
  18:	000080e7          	jalr	ra # 14 <EntityParam+0x14>
  1c:	4501                	li	a0,0
  1e:	60a2                	ld	ra,8(sp)
  20:	0141                	addi	sp,sp,16
  22:	8082                	ret

0000000000000024 <EntityParamCaller>:
  24:	715d                	addi	sp,sp,-80
  26:	e486                	sd	ra,72(sp)
  28:	06400793          	li	a5,100
  2c:	d43e                	sw	a5,40(sp)
  2e:	47a9                	li	a5,10
  30:	f83e                	sd	a5,48(sp)
  32:	4705                	li	a4,1
  34:	02e11c23          	sh	a4,56(sp)
  38:	7722                	ld	a4,40(sp)
  3a:	e03a                	sd	a4,0(sp)
  3c:	e43e                	sd	a5,8(sp)
  3e:	77e2                	ld	a5,56(sp)
  40:	e83e                	sd	a5,16(sp)
  42:	850a                	mv	a0,sp
  44:	00000097          	auipc	ra,0x0
  48:	000080e7          	jalr	ra # 44 <EntityParamCaller+0x20>
  4c:	60a6                	ld	ra,72(sp)
  4e:	6161                	addi	sp,sp,80
  50:	8082                	ret

0000000000000052 <GetLargeObject>:
  52:	8985                	andi	a1,a1,1
  54:	e599                	bnez	a1,62 <.L6>
  56:	47d9                	li	a5,22
  58:	00f51823          	sh	a5,16(a0) # 10 <EntityParam+0x10>
  5c:	e51c                	sd	a5,8(a0)
  5e:	c11c                	sw	a5,0(a0)
  60:	8082                	ret

0000000000000062 <.L6>:
  62:	06300793          	li	a5,99
  66:	00f51823          	sh	a5,16(a0)
  6a:	e51c                	sd	a5,8(a0)
  6c:	c11c                	sw	a5,0(a0)
  6e:	8082                	ret

0000000000000070 <my_GetLargeObject>:
  70:	7179                	addi	sp,sp,-48
  72:	f406                	sd	ra,40(sp)
  74:	85aa                	mv	a1,a0
  76:	0028                	addi	a0,sp,8
  78:	00000097          	auipc	ra,0x0
  7c:	000080e7          	jalr	ra # 78 <my_GetLargeObject+0x8>
  80:	45a2                	lw	a1,8(sp)
  82:	00000537          	lui	a0,0x0
  86:	00050513          	mv	a0,a0
  8a:	00000097          	auipc	ra,0x0
  8e:	000080e7          	jalr	ra # 8a <my_GetLargeObject+0x1a>
  92:	70a2                	ld	ra,40(sp)
  94:	6145                	addi	sp,sp,48
  96:	8082                	ret
