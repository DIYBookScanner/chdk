#include "stubs_asm.h"
#define NULL_SUB 0xFFDC4AD4

// Override stubs_entry.S
NHSTUB(DisplayImagePhysicalScreen,  0xFFDBA0B8)
NHSTUB(GetBatteryTemperature,       0xFFDC7D94)
NHSTUB(free,                        0xFFCCC768)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFD0DCB0)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFD0DCE0)
NHSTUB(SetScriptMode,               0xFFEA416C)
NHSTUB(TurnOffMic,                  0xFFDC5854)
NHSTUB(TurnOnMic,                   0xFFDC5818)
NHSTUB(GetVRAMHPixelsSize,0xFFDE29D4) // by find_eventproc name @ 0xFFEF7594
NHSTUB(GetVRAMVPixelsSize,0xFFDE29E0) // by find_eventproc name @ 0xFFEF759C
