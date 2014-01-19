#include "stubs_asm.h"

DEF(recreview_hold,                     0x7434 + 0xD4)  // found at FF964C10 was + 0xDC
DEF(enabled_refresh_physical_screen,    0x8e04 + 0x30)  //found at FF9D4918 and FF9D4F38
DEF(led_table,                          0x24AC + 0x04)  // found at FF847374
DEF(palette_buffer_ptr,               0x8D9C) // points to 0x15B5A0, sub_FF9CFC10
DEF(active_palette_buffer,            0x8D8C) // sub_FF9CFE34
DEF(palette_control,                  0x8D88) // sub_FF9CFE34
