# Add
# Format:
#	ADDi RD, RS1, imm
# imm只有12位，范围[-2048 , 2047]
	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:
	li x6, 1		        # x6 = 1
	addi x5, x6, 2047		# x5 = x6 + 2047(7ff)
stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
