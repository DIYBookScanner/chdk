#include "stubs_asm.h"

// found in taskcreate_LEDCon (sub_FF84CCD0)
// ROM:FF84CCD4   LDR     R4, =0x270C     @ Base addr
// ROM:FF84CCD8   LDR     R0, [R4]        @ Load value (dereference)
// ROM:FF84CCDC   CMP     R0, #0          @ If it's not 0, it's already initialized,
// ROM:FF84CCE0   BNE     locret_FF84CDC8 @ so return.
// ROM:FF84CCE4   MOV     R0, #0x3C0      @ Else (if it's 1)
// ROM:FF84CCE8   BL      sub_FF82AC28    @ R0 = malloc(0x3C0); // allocate the LED table
// ..
// ROM:FF84CCFC   STR     R0, [R4,#4]     @ Store the address of the LED table (base+4)
DEF(led_table,                          0x2290) // 0x270C + 4

DEF(mode_magic,                         0x58D4)
DEF(enabled_refresh_physical_screen,    0xa460 + 0x30) // found in sub_ffd7a308
