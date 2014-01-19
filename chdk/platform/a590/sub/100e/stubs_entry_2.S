#include "stubs_asm.h"
#define NULL_SUB 0xFFC00948

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 0xFFC356C8)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFDEEA0C)
NHSTUB(MuteOffPhysicalScreen,       0xFFC6C5A0)
NHSTUB(MuteOnPhysicalScreen,        0xFFC6C588)
NHSTUB(SetZoomForMovie,             0xFFD3A2C4)
NHSTUB(TurnOffMic,                  0xFFC35D28)
NHSTUB(TurnOnMic,                   0xFFC35CFC)
