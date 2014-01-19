#include "stubs_asm.h"
#define NULL_SUB 0xFF810958

// Override stubs_entry.S
NHSTUB(PutInNdFilter,               0xFFA0C550)
NHSTUB(PutOutNdFilter,              0xFFA0C588)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(strcmp,                      0xFF81E7F4)
NHSTUB(write,                       0xff81a3d8)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(TurnOffMic,                  NULL_SUB)
NHSTUB(TurnOnMic,                   NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFA449D0)
NHSTUB(PostLEDMessage,              0xFF848910)
NHSTUB(closefastdir,                0xffa2cc7c)
NHSTUB(ints_disable,                0xFF810578)
NHSTUB(ints_enable,                 0xFF8105A0)
