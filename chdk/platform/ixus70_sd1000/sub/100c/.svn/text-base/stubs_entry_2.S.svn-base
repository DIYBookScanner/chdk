#include "stubs_asm.h"
#define NULL_SUB 0xFF9AD778

// Override stubs_entry.S
NHSTUB(AllocateMemory,              0xFF818664)
NHSTUB(DisplayImagePhysicalScreen,  0xFFA24FF4)
NHSTUB(FreeMemory,                  0xFF818650)
NHSTUB(GetBatteryTemperature,       0xFFA34470)
NHSTUB(GetCurrentAvValue,           0xFFAD9E20)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAD2F88)
NHSTUB(TakeSemaphore,               0xFFB140E0)
NHSTUB(WriteSDCard,                 0xFFAAC320)
NHSTUB(free,                        0xFF9201CC)
NHSTUB(kbd_pwr_off,                 0xFFA30BE4)
NHSTUB(kbd_pwr_on,                  0xFFA30BA4)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF96553C)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFF96556C)
NHSTUB(SetScriptMode,               0xFFB34670)
NHSTUB(GetVRAMHPixelsSize,0xFFA56C50) // by find_eventproc name @ 0xFFB8FD60
NHSTUB(GetVRAMVPixelsSize,0xFFA56C5C) // by find_eventproc name @ 0xFFB8FD68
