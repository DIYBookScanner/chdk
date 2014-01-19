#include "stubs_asm.h"
#define NULL_SUB 0xFF810B7C

// Override stubs_entry.S
NHSTUB(DeleteFile_Fut,              0xff82cdf8)
NHSTUB(kbd_pwr_off,                   NULL_SUB)
NHSTUB(kbd_pwr_on,                    NULL_SUB)
NHSTUB(MakeDirectory_Fut,           0xff82d908) // mkdir. This requires #define MKDIR_RETURN_ONE_ON_SUCCESS
NHSTUB(GetBatteryTemperature,         NULL_SUB) // Does not work in A1200, SX130, A800 & A810 (included dummy in sub/100c/lib.c)
NHSTUB(Restart,                     0xff831200) // Untested

// Additional
NHSTUB(TurnOffE1,                   0xff830fa4) // for shutdown(), to complicated to emulate
NHSTUB(TurnOffMic,                  0xff861f68)
NHSTUB(TurnOnMic,                   0xff861f3c)



// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(RefreshPhysicalScreen,       NULL_SUB)
