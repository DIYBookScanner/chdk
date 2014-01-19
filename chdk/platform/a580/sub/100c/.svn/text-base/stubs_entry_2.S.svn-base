#include "stubs_asm.h"
#define NULL_SUB 0xFFC00948

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(GetCurrentTargetDistance,    0xFFD04C7C)
NHSTUB(MakeAFScan,                  0xFFDE1C50)
NHSTUB(PostLEDMessage,              0xFFC30AFC)
NHSTUB(TurnOffMic,                  0xFFC31FAC)
NHSTUB(TurnOnMic,                   0xFFC31F80)
NHSTUB(dumpMemoryToFile,            0xFFC141F4) // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(ints_disable,                0xFFC00578)
NHSTUB(ints_enable,                 0xFFC005A0)
