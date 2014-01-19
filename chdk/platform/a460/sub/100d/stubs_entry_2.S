#include "stubs_asm.h"
#define NULL_SUB 0xFFC017E8

// Override stubs_entry.S
NHSTUB(DisplayImagePhysicalScreen,  0xFFDBA0A8)
NHSTUB(GetBatteryTemperature,       0xFFDC7D84)
NHSTUB(free,                        0xFFCCC760)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFD0DCA8)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFD0DCD8)
NHSTUB(SetScriptMode,               0xFFEA4154)
NHSTUB(TurnOffMic,                  0xFFDC5844)
NHSTUB(TurnOnMic,                   0xFFDC5808)
NHSTUB(GetVRAMHPixelsSize,0xFFDE29C4) // by find_eventproc name @ 0xFFEF7594
NHSTUB(GetVRAMVPixelsSize,0xFFDE29D0) // by find_eventproc name @ 0xFFEF759C
