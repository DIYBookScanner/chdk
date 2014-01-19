// G10 loader - resetcode\entry.S

	.section .entry

	MOV     SP, #0x1900
	MOV     R11, #0
	B	copy_and_restart

