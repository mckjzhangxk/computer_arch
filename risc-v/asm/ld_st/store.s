# Format:
#	lw RD, imm(Rsi)  RD= Mem[Rsi+imm]
#   lb/lbu  RD, imm(Rsi)   RD[0:8]= Mem[Rsi+imm][0:8]
#   lh/lhu  RD, imm(Rsi)   RD[0:16]= Mem[Rsi+imm][0:16]

	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:					#加载四字节
	la t0, _array		# 使用伪指令，加载_array的位置

	li t1, 0xff
	sb t1,(t0)			
	lbu t1,(t0)			# t1=0xff


	li t1, 0xffff
	sh t1,(t0)			 
	lhu t1,(t0)          # t1=0xffff

	li t1, 0xffffffff
	sw t1,(t0)			
	lw t1,(t0)			# t1=0xffffffff

stop:
	j stop			# Infinite loop to stop execution

_array:	
	.byte 0x00
	.byte 0x00
	.byte 0x00
	.byte 0x00
.end			# End of file