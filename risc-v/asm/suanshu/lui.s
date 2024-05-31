# Add
# Format:
#	LUI RD,  imm, RD=imm<<12
	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:
	lui x6, 0x12345		    # x6 = 0x12345000, 0x12345 占20位
	addi x5, x6, 0x678		# x5 = 0x12345678, 0x678 占12位


	# li x6,0x12345			#这段代码无法编译
	# addi x5,x6,0xfff          


	li x6,0x12346
	addi x5,x6,-1          #答案是0x12345fff
stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
