#include "stubs_asm.h"

// ROM:FFACC8B4, search for "ZoomCon_EnterCaptModeChange"
DEF(zoom_status,                        0x315B) // ?!?

// ROM:FF99D340
DEF(recreview_hold, 0x780E)   // 0x780C + 2 ?!?

// ROM:FF860864                 LDR     R0, =0x24A4 <---
// ROM:FF860868                 STMFD   SP!, {R4,LR}
// ROM:FF86086C                 LDR     R0, [R0,#8] <---
// ROM:FF860870                 BL      sub_FF839B50
// ROM:FF860874                 TST     R0, #1
// ROM:FF860878                 LDMNEFD SP!, {R4,LR}
// ROM:FF86087C                 MOVNE   R1, #0x42
// ROM:FF860880                 ADRNE   R0, aLeddrv_c   ; "LEDDrv.c"
// ROM:FF860884                 BNE     DebugAssert
// ROM:FF860888                 LDMFD   SP!, {R4,PC}
DEF(led_table,                          0x24AC) // R0 -> 0x24A4 + 0x8

// like SX210
// ROM:FFA1356C ScreenLock                              ; CODE XREF: sub_FFA121C0
// ROM:FFA1356C                 STMFD   SP!, {R4,LR}
// ROM:FFA13570                 LDR     R4, =0x92AC <---
// ROM:FFA13574                 LDR     R0, [R4,#0x20] <---
// ROM:FFA13578                 CMP     R0, #0
// ROM:FFA1357C                 BNE     loc_FFA13590
// ROM:FFA13580                 ADR     R1, aScreenlock ; "ScreenLock"
// ROM:FFA13584                 MOV     R0, #0x60
// ROM:FFA13588                 BL      CameraLog       ; LOCATION: CameraLog.c:237
// ROM:FFA1358C                 BL      sub_FF8ABEF8
DEF(enabled_refresh_physical_screen,    0x92CC) // ROM:FFA1339C or ROM:FFA13570, 0x92AC + 0x20 = 0x92CC

DEF(some_f_for_dng,                     0xDEAD) // ??? TODO NOT FOUND!
DEF(second_ext_for_dng,                 0xDEAD) // ??? TODO NOT FOUND!
