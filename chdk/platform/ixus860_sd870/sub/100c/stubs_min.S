#include "stubs_asm.h"

DEF(focus_busy,                         0xA65C) //0xA648 + 0x14 ??? to double check
DEF(recreview_hold,                     0xB474) // 0xB3C8+0xAC
DEF(some_f_for_dng,                     0x90AC)
DEF(second_ext_for_dng,                 0x90CC)
// Key values for 'Feather' on joystic
// Could be retrieved from 'PhySW' Task function
 DEF(touch_keys_angle,                  0x429F4)
// Semaphore address to disable Feather processing
 DEF(touch_keys_sema,                   0x9C2C) // 0x9C10 + 0x1C
