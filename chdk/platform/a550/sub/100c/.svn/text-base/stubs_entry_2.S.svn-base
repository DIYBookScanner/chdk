#include "stubs_asm.h"
#define NULL_SUB 0xFFDCD668

// Override stubs_entry.S
NHSTUB(DisplayImagePhysicalScreen,  0xFFDC0374)
NHSTUB(FreeMemory,                  0xFFC0819C)
NHSTUB(WriteSDCard,                 0xFFE34524)
NHSTUB(free,                        0xFFCC8154)
NHSTUB(kbd_read_keys_r2,            0xFFDCB384)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFD0A6E4)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFD0A714)
NHSTUB(SetScriptMode,               0xFFEA2844)
NHSTUB(TurnOffMic,                  0xffdcc210)
NHSTUB(TurnOnMic,                   0xffdcc1d4)
NHSTUB(GetVRAMHPixelsSize,0xFFDE94CC) // by find_eventproc name @ 0xFFEF20A0
NHSTUB(GetVRAMVPixelsSize,0xFFDE94D8) // by find_eventproc name @ 0xFFEF20A8
