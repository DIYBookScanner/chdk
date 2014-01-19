#include "stubs_asm.h"
#define NULL_SUB 0xFFC00958

// Override stubs_entry.S
NHSTUB(GetZoomLensCurrentPosition,  0xFFD03B5C)
NHSTUB(SetPropertyCase,             0xFFC50CC8)
NHSTUB(write,                       0xFFC0A4A8)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFDD4AA4)
NHSTUB(PostLEDMessage,              0xFFC366B8)
NHSTUB(TurnOffMic,                  0xFFC376F8)
NHSTUB(TurnOnMic,                   0xFFC376CC)
NHSTUB(closefastdir,                0xFFDC1C68)
NHSTUB(dumpMemoryToFile,            0xFFC141Fa) // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(ints_disable,                0xFFC00578)
NHSTUB(ints_enable,                 0xFFC005A0)
