    .section .entry

// Turn OFF SD Card power
// to support autostart
	//bx	lr  //tentando abortar o programa não segue
	//LDR     R3, =0xc0220058			// em 0xffc5323c análogo a 0xffc51784 em a495
	//MOV     R2, #0x44
	//STR     R2, [R3]
//	LDR     R3, =0xc0220000
//	MOV		R2, #0x46
//	STR		R2, [R3, #32]
//	MOV		R2, #32
//	STR		R2, [R3, #0x44]
//	MOV     R2, #0x44
//	STR     R2, [R3, #0x58]
//	MOV     R2, #32
//	STR     R2, [R3, #0x5C]
//	STR     R2, [R3, #0x110]
//	STR     R2, [R3, #0x114]
//	STR     R2, [R3, #0x118]
//	STR     R2, [R3, #0x11c]
//	STR     R2, [R3, #0x120]
//	STR     R2, [R3, #0x124]
	

	// looks like idle cycle is required for proper shutdown
	MOV     R3, #0xF0000
m1x:
	SUB	R3, R3, #1
	CMP	R3, #0
	BNE	m1x

// ordinary startup...

	MOV     SP, #0x1900
	MOV     R11, #0
	B	my_restart
