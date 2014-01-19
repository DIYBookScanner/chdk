#include "stubs_asm.h"
#define NULL_SUB 0xFF810B04

// Override stubs_entry.S
NHSTUB(SetScriptMode,               0xFF810F4C)
NHSTUB(TurnOffBackLight,            0xFF8A348C)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExportToEventProcedure,      0xFF88A38C)
NHSTUB(GetLogToFile,                0xFF96D2C0)
NHSTUB(MakeAFScan,                  0xFF9662EC)
NHSTUB(UnRegisterEvntProc,          0xFF8898C0)
NHSTUB(closefastdir,                0xFFA842B4)
NHSTUB(kbd_p1_sub,                  0xFF833584)
