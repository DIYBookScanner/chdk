#include "stubs_asm.h"
#define NULL_SUB 0xFF9AD778

// Override stubs_entry.S
NHSTUB(AllocateMemory,              0xFF818664)
NHSTUB(DisplayImagePhysicalScreen,  0xFFA25068)
NHSTUB(FreeMemory,                  0xFF818650)
NHSTUB(GetBatteryTemperature,       0xFFA344E4)
NHSTUB(GetCurrentAvValue,           0xFFAD9E94)
NHSTUB(WriteSDCard,                 0xFFAAC394)
NHSTUB(free,                        0xFF9201CC)
NHSTUB(kbd_pwr_off,                 0xFFA30C58)
NHSTUB(kbd_pwr_on,                  0xFFA30C18)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF96553C)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFF96556C)
NHSTUB(SetScriptMode,               0xFFB346E4)
NHSTUB(GetVRAMHPixelsSize,0xFFA56CC4) // by find_eventproc name @ 0xFFB8FDD0
NHSTUB(GetVRAMVPixelsSize,0xFFA56CD0) // by find_eventproc name @ 0xFFB8FDD8
