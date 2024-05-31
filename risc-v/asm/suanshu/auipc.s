# Add
# Format:
#	auipc RD,  imm, RD=pc+imm<<12
	.text			# Define beginning of text section
	.global	_start		# Define entry _start

_start:	     
	auipc t0, 4	#to =0x80000000+ 4<<12= 0x80004000

stop:
	j stop			# Infinite loop to stop execution

	.end			# End of file
