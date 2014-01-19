#include "stubs_asm.h"

DEF(focus_busy,                         0xDD7C) //0xDD68 + 0x14 ??? to double check
DEF(recreview_hold,                     0xEBFC) // 0xEB50+0xAC
DEF(some_f_for_dng,                     0xC720)
DEF(second_ext_for_dng,                 0xC740)
// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
 DEF(touch_keys_angle,                  0x46464)
// Semaphore address to disable Feather processing
 DEF(touch_keys_sema,                   0xD2A0) // 0xD284 + 0x1C
