#include "stubs_asm.h"
#define NULL_SUB 0xFFC0E2E0

// Override stubs_entry.S
NHSTUB(AllocateMemory,              0xffc0b294)
NHSTUB(DisplayImagePhysicalScreen,  0xffd093a0)
NHSTUB(EnterToCompensationEVF,      0xFFD24234)
NHSTUB(ExitFromCompensationEVF,     0xFFD24244)
NHSTUB(FreeMemory,                  0xffc0b280)
NHSTUB(WriteSDCard,                 0xFFC69824)
NHSTUB(free,                        0xFFE75B50)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(TurnOffMic,                  NULL_SUB)
NHSTUB(TurnOnMic,                   NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFCD8898)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFCD88B0)
NHSTUB(MFOff,                       0xffd24c48)
NHSTUB(MFOn,                        0xffd24c18)
NHSTUB(SetScriptMode,               0xFFD3799C)
NHSTUB(exmem_free,                  0xFFC02904)

IGNORE(MoveFocusLensToDistance) // Custom version in focushack.c, ignore firmware version
