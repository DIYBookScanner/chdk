#include "stubs_asm.h"
#define NULL_SUB 0xFF810B04

// Override stubs_entry.S
NHSTUB(SetScriptMode,               0xFF810F4C)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExportToEventProcedure,      0xFF88A33C)
NHSTUB(GetLogToFile,                0xFF96D104)
NHSTUB(MakeAFScan,                  0xFF966130)
NHSTUB(UnRegisterEvntProc,          0xFF889870)
NHSTUB(closefastdir,                0xFFA840F8)
NHSTUB(kbd_p1_sub,                  0xFF833584)
