#include "stubs_asm.h"
#define NULL_SUB 0xFFDD3094

// Override stubs_entry.S
NHSTUB(FreeMemory,                  0xFFC08670)
NHSTUB(GetFocusLensSubjectDistance, 0xFFE685A0)
NHSTUB(free,                        0xFFCD1704)
NHSTUB(kbd_read_keys_r2,            0xFFDDD0C0)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFD15CB8)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFD15CE8)
NHSTUB(SetScriptMode,               0xFFEC9A14)
NHSTUB(TurnOffMic,                  0xffdde07c)
NHSTUB(TurnOnMic,                   0xffdde040)
NHSTUB(GetVRAMHPixelsSize,0xFFE020D8) // by find_eventproc name @ 0xFFF1F528
NHSTUB(GetVRAMVPixelsSize,0xFFE020E4) // by find_eventproc name @ 0xFFF1F530
