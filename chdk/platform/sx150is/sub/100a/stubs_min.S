#include "stubs_asm.h"

DEF(enabled_refresh_physical_screen,    0x9458)         // @FFA29FF8
DEF(led_table,                          0x2464 + 0x04)  // @FF85EFEC
DEF(some_flag_for_af_scan,              0x000072F8)     // Found @0xFF98A5FC

DEF(active_bitmap_buffer,               0x9680)         // 0x9670+0x10 (1.00a sub_FFA2DE9C -> FFA2DEA0 + FFA2DEC8)
DEF(bitmap_buffer,                      0x9688)         // FFA2DEC0 & FFA2DECC (1.00a)
DEF(active_palette_buffer,              0x9654)         // sub_FFA29F88 (1.00a)
DEF(palette_buffer,                     0xBAA84)        // sub_FFA2A2FC (1.00a)
