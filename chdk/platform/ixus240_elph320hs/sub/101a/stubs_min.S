#include "stubs_asm.h"

DEF(led_table,                          0x28C0 + 0x04)  // 1.01a sub_FF0652CC (FF0652D0 + FF04D0F0)
DEF(enabled_refresh_physical_screen,    0x4574 + 0x14)  // 1.01a sub_FF0D2B80 (FF0D2B84 + FF0D2BA8)

DEF(touch_screen_x,                     0x00002b9c)     //ixus310 28f0 @ loc_ff059c58 -> ixus240 1.01a 2b9c @ loc_ff069d58
DEF(touch_screen_y,                     0x00002b9e)     //ixus310 28f2 -> ixus240 1.01a 2b9e

//To do: These were taken from ixus310
DEF(touch_screen_active,                0x00002b88)     //ixus310 28c4 @ ixus240.101a 2b88 if touch pressed 0x01, else 0x00
DEF(canon_play_menu_active,             0x0000e790)     //ixus240 e790: 0 - 0x32aae0 <- this is always set when in rec and goes back to 0 on play mode

DEF(cds_gain_value,                     0x0000abd0)     //Check this!!!

