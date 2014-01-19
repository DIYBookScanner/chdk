#include "stubs_asm.h"
#define NULL_SUB 0xFFD5B3B0

// Override stubs_entry.S

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFCE0928)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFCE0940)
NHSTUB(SetScriptMode,               0xFFD4736C)
NHSTUB(TurnOffMic,                  0xffc1ec78)
NHSTUB(TurnOnMic,                   0xffc1ec30)
NHSTUB(WriteSDCard,                 0xFFC6B188)
