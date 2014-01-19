#include "stubs_asm.h"
#define NULL_SUB 0xFFE97EB0

// Override stubs_entry.S
NHSTUB(GetDrive_ClusterSize,        0xffc607b0)
NHSTUB(GetDrive_FreeClusters,       0xffc60828)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFD0015C)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFD0018C)
NHSTUB(PostLEDMessage,              0xFFC1D7C4)
NHSTUB(SetScriptMode,               0xFFD6EB18)
NHSTUB(TurnOffMic,                  0xFFC1E944)
NHSTUB(TurnOnMic,                   0xFFC1E908)
NHSTUB(GetVRAMHPixelsSize,0xFFEBA354) // by find_eventproc name @ 0xFFF1C650
NHSTUB(GetVRAMVPixelsSize,0xFFEBA360) // by find_eventproc name @ 0xFFF1C658
