#include "stubs_asm.h"
#define NULL_SUB 0xFF000AE4

// Override stubs_entry.S

NHSTUB(kbd_pwr_off,					NULL_SUB)
NHSTUB(kbd_pwr_on,					NULL_SUB)
NHSTUB(SetZoomActuatorSpeedPercent                        ,NULL_SUB)

NHSTUB(MakeDirectory_Fut,           0xFF01CF78)
NHSTUB(GetImageFolder,              0xFF1B8488)
NHSTUB(LocalTime,					0x68F420)
