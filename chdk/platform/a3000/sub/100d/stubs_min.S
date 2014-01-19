#include "stubs_asm.h"

DEF(recreview_hold,                     0x64CC + 0xCC)  // @FFD38410
DEF(led_table,                          0x219C + 0x04)  // @FFC438FC           

/*
ROM:FFD86FA4 ScreenLock 
ROM:FFD86FA4                 STMFD   SP!, {R4,LR}
ROM:FFD86FA8                 LDR     R4, =0x7708
ROM:FFD86FAC                 LDR     R0, [R4,#0x20]
ROM:FFD86FB0                 CMP     R0, #0
ROM:FFD86FB4                 BNE     loc_FFD86FC8
ROM:FFD86FB8                 ADR     R1, aScreenlock
ROM:FFD86FBC                 MOV     R0, #0x60
ROM:FFD86FC0                 BL      CameraLog
ROM:FFD86FC4                 BL      sub_FFC7FD64
*/
DEF(enabled_refresh_physical_screen,    0x7728)         //A3000 @FFD86FA8
