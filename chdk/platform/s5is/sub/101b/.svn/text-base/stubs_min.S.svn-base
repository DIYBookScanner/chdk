#include "stubs_asm.h"

// Found in sub_FF9754AC. Again, ewavr found this one, he did supply one pointer
// 'search for LDR R12, =0x3007'. I guess this is the right one then :)
// ROM:FF9754AC 000                 STMFD   SP!, {R4,LR}
// ROM:FF9754B0 008                 LDR     R1, =0xBD60
// ROM:FF9754B4 008                 LDR     R12, =0x3007
// ROM:FF9754B8 008                 LDR     R2, [R1,#0xCC]
DEF(recreview_hold,                     0xBE2C) // 0xBD60 + 0xCC

// found in taskcreate_LEDCon (sub_FF84CCD0)
// ROM:FF84CCD4   LDR     R4, =0x270C     @ Base addr
// ROM:FF84CCD8   LDR     R0, [R4]        @ Load value (dereference)
// ROM:FF84CCDC   CMP     R0, #0          @ If it's not 0, it's already initialized,
// ROM:FF84CCE0   BNE     locret_FF84CDC8 @ so return.
// ROM:FF84CCE4   MOV     R0, #0x3C0      @ Else (if it's 1)
// ROM:FF84CCE8   BL      sub_FF82AC28    @ R0 = malloc(0x3C0); // allocate the LED table
// ..
// ROM:FF84CCFC   STR     R0, [R4,#4]     @ Store the address of the LED table (base+4)
DEF(led_table,                          0x2710) // 0x270C + 4

// found in sub_FF957174 (called from MoveZoomLensWithPoint (sub_FF957B34))
// ROM:FF957178   LDR     R4, =0xB37C
// ..
// ROM:FF9571BC   LDR     R0, [R4,#0x34]
// ROM:FF9571C0   CMP     R0, #0
// ROM:FF9571C4   MOVNE   R1, #0xE0
// ROM:FF9571C8   ADRNE   R0, aZoomlenscontro @ "ZoomLensController.c"
// ROM:FF9571CC   BLNE    assert
DEF(zoom_busy,                          0xB3B0)  //0xB37C + 0x34

DEF(some_f_for_dng,                     0x9B94)
DEF(second_ext_for_dng,                 0x9BB8)
