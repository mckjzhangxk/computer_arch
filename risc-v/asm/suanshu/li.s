# Add
# Format:
#	li RD,  imm
	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:
	li t1, 0x12345fff		    # x6 = 0x12345fff

# 编译器 生成以下2条指令
# 	lui     t1,0x12346                                                                       │
# │   addi    t1,t1,-1
stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
