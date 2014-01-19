#include "stubs_asm.h"
#define NULL_SUB 0xFF810B04

// Override stubs_entry.S
NHSTUB(GetPropertyCase,             0xFF88CA64)
NHSTUB(SetScriptMode,               0xFF810F4C)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(EraseLogSector,              0xFF96B2E8)
NHSTUB(ExportToEventProcedure,      0xFF889734)
NHSTUB(GetLogToFile,                0xFF96B2C0)
NHSTUB(MakeAFScan,                  0xFF9646D4)
NHSTUB(UnRegisterEvntProc,          0xFF888C68)
NHSTUB(closefastdir,                0xFFA7D5D0)

// these are overridden because we don't have a correct full dump for this cam
NHSTUB(GetVRAMHPixelsSize,          0xFF84F110)
NHSTUB(GetVRAMVPixelsSize,          0xFF84F11C)
