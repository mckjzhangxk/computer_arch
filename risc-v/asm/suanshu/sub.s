# Add
# Format:
#	Sub RD, RS1, RS2

	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:
	li x6, 1		# x6 = 11
	li x7, 2		# x7 = 2
	sub x5, x6, x7		# x5 = x6 - x7

stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
