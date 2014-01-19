    .section .entry
	
// looks like idle cycle is required for proper shutdown
	MOV     R3, #0xF0000  
1:
	SUB	R3, R3, #1
	CMP	R3, #0
	BNE	1b

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
