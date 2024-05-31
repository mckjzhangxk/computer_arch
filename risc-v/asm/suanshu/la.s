# Add
# Format:
#	la RD,  label
# 伪指令，把label的位置 设置给RD
	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:	     
	la t0, stop	 # to=stop

stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
