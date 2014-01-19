#include "stubs_asm.h"
#define NULL_SUB 0xFFD670E8

// Override stubs_entry.S

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFD1ED50)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFD1ED80)
NHSTUB(SetScriptMode,               0xFFEDE788)
NHSTUB(TurnOffMic,                  0xffde85bc)
NHSTUB(TurnOnMic,                   0xffde8580)
NHSTUB(GetVRAMHPixelsSize,0xFFE0C998) // by find_eventproc name @ 0xFFF34720
NHSTUB(GetVRAMVPixelsSize,0xFFE0C9A4) // by find_eventproc name @ 0xFFF34728
