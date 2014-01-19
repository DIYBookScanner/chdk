    .section .entry

//a3200is LEDs
//0xC02200D4 = Flash
//0xC02200F0 = Green Power rear
//0xC02200F4 = AF LED front

/*
// for testing, blink LED at 0xC02200F4 4 times
	LDR R3, =0xC02200F4
	MOV	R1,#4
2:
	MOV R2, #0x46
	STR R2, [R3]
	MOV R0, #0x80000
1:
	SUB R0,R0,#1
	CMP R0,#0
	BNE 1b
	MOV R2, #0x44
	STR R2, [R3]
	MOV R0, #0x80000
1:
	SUB R0,R0,#1
	CMP R0,#0
	BNE 1b

	SUB R1,R1,#1
	CMP R1,#0
	BNE 2b
// End of LED testing
*/
	
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
