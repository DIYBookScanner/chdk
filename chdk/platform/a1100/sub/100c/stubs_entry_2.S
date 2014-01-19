#include "stubs_asm.h"
#define NULL_SUB 0xFFC00950

// Override stubs_entry.S
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFC1FAAC)
NHSTUB(SetAE_ShutterSpeed,          0xFFE3D994)
NHSTUB(kbd_pwr_off,                 0xFFC30BAC)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFCFA90C)
NHSTUB(TurnOffMic,                  0xFFC31214)
NHSTUB(TurnOnMic,                   0xFFC311E8)
NHSTUB(platformsub_kbd_fetch_data,  0xFFC30B28)
