#include "stubs_asm.h"
#define NULL_SUB 0xFF9B7BA8

// Override stubs_entry.S
NHSTUB(AllocateMemory,              0xFF818678)
NHSTUB(DisplayImagePhysicalScreen,  0xFFA2F454)
NHSTUB(FreeMemory,                  0xFF818664)
NHSTUB(GetBatteryTemperature,       0xFFA3FC48)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAE0988)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAE0954)
NHSTUB(MoveFocusLensToDistance,     0xFFAE0144)
NHSTUB(free,                        0xFF92A5B0)
NHSTUB(kbd_pwr_off,                 0xFFA3B1BC)
NHSTUB(kbd_pwr_on,                  0xFFA3B17C)
NHSTUB(kbd_read_keys_r2,            0xFFA3AC4C)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(SetScriptMode,               0xFFB401BC)
NHSTUB(fprintf,                     0xff91f49c)
NHSTUB(fputs,                       0xff91f5bc)
NHSTUB(puts,                        0xFF9208B4)
NHSTUB(GetVRAMHPixelsSize,0xFFA625E4) // by find_eventproc name @ 0xFFB9D31C
NHSTUB(GetVRAMVPixelsSize,0xFFA625F0) // by find_eventproc name @ 0xFFB9D324
