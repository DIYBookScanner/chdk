    .section .entry

// Turn OFF SD Card power
// to support autostart. A1200 @ ???   (a2200 @ FF8701D0)
    LDR     R3, =0xC0220018
    MOV     R2, #0x44
    STR     R2, [R3]
    
// looks like idle cycle is required for proper shutdown
    MOV     R3, #0xF0000    // increased from 8000 to F0000 for extra delay, could maybe be 10000 ?
1:
    SUB R3, R3, #1
    CMP R3, #0
    BNE 1b

// ordinary startup...

    MOV     SP, #0x1900
    MOV     R11, #0
    B   my_restart
