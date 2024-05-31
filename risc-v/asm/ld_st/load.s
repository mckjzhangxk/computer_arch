# Format:
#	lw RD, imm(Rsi)  RD= Mem[Rsi+imm]
#   lb/lbu  RD, imm(Rsi)   RD[0:8]= Mem[Rsi+imm][0:8]
#   lh/lhu  RD, imm(Rsi)   RD[0:16]= Mem[Rsi+imm][0:16]

	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:					#加载四字节
	la t0, _array		# 使用伪指令，加载_array的位置
	lw t1, (t0)			# 小端序 t1=0xccddeeff

						#加载字节
	lb t1,(t0)			# t1 = -1,  符号扩展,0xffffffff
	lbu t1,(t0)			# t1 = 0xff,零扩展,0x000000ff

						#加载二字节
	lh t1,(t0)			# t1 = -4353,  符号扩展,0xffffeeff
	lhu t1,(t0)			# t1 = 0xeeff,零扩展,0x0000eeff
stop:
	j stop			# Infinite loop to stop execution

_array:	
	.byte 0xff
	.byte 0xee
	.byte 0xdd
	.byte 0xcc
.end			# End of file