#include "stubs_asm.h"
#define NULL_SUB 0xFF810B04

// Override stubs_entry.S
NHSTUB(SetScriptMode,               0xFF810F4C)
NHSTUB(kbd_pwr_off,                 0xFF833350)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(EraseLogSector,              0xFF96B4F8)
NHSTUB(ExportToEventProcedure,      0xFF8897B0)
NHSTUB(GetLogToFile,                0xFF96B4D0)
NHSTUB(MakeAFScan,                  0xFF9648E4)
NHSTUB(UnRegisterEvntProc,          0xFF888CE4)
NHSTUB(closefastdir,                0xFFA7D7E0)
NHSTUB(kbd_p1_sub,                  0xFF8335B4)
