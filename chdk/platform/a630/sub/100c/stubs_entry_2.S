#include "stubs_asm.h"
#define NULL_SUB 0xFFD2CF98

// Override stubs_entry.S
NHSTUB(GetDrive_ClusterSize,        0xffc60cd4)
NHSTUB(GetDrive_FreeClusters,       0xffc60d4c)
NHSTUB(free,                        0xFFEF3284)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFCF6AD0)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFCF6B00)
NHSTUB(SetScriptMode,               0xFFD65C40)
NHSTUB(TurnOffMic,                  0xffc1eee8)
NHSTUB(TurnOnMic,                   0xffc1eeac)
NHSTUB(GetVRAMHPixelsSize,0xFFEAD584) // by find_eventproc name @ 0xFFF0EE28
NHSTUB(GetVRAMVPixelsSize,0xFFEAD590) // by find_eventproc name @ 0xFFF0EE30
