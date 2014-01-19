#include "stubs_asm.h"
#define NULL_SUB 0xFF8118C0

// Override stubs_entry.S
NHSTUB(ExitFromCompensationEVF,     0xff94c158)
NHSTUB(VbattGet,                    0xFF82B7D8)
NHSTUB(free,                        0xFFAD6B78)
NHSTUB(kbd_pwr_off,                 0xFF8277F0)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF8F2AE4)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFF8F2AFC)
NHSTUB(SetScriptMode,               0xFF95DAE8)
NHSTUB(UniqueLedOff,                0xFF82D160)
NHSTUB(UniqueLedOn,                 0xFF82D11C)
