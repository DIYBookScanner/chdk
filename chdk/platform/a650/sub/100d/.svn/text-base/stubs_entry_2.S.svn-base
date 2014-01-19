#include "stubs_asm.h"
#define NULL_SUB 0xFFC00958

// Override stubs_entry.S
NHSTUB(GetZoomLensCurrentPosition,  0xffd07fc4)
NHSTUB(write,                       0xffc0a3d8)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFDE3A8C)
NHSTUB(TurnOffMic,                  0xFFC382B4)
NHSTUB(TurnOnMic,                   0xFFC38288)
NHSTUB(closefastdir,                0xffdd0710)
NHSTUB(ints_disable,                0xFFC00578)
NHSTUB(ints_enable,                 0xFFC005A0)
