#include "stubs_asm.h"
#define NULL_SUB 0xFF810B24

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// Additional
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFAA1D88)
NHSTUB(MakeAFScan,                  0xFF8DC610)
NHSTUB(TurnOnMic,                   0xFF860984)
NHSTUB(TurnOffMic,                  0xFF8609B0)
