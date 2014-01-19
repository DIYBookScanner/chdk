#include "stubs_asm.h"
#define NULL_SUB 0xFFC00958

// Override stubs_entry.S
NHSTUB(GetCCDTemperature,           0xFFC3A474)
NHSTUB(GetOpticalTemperature,       0xFFDC4FC4)
NHSTUB(GetZoomLensCurrentPosition,  0xFFD0E3A0)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFDEFB6C)
NHSTUB(PostLEDMessage,              0xFFC37468)
NHSTUB(TurnOffMic,                  0xFFC388D0)
NHSTUB(TurnOnMic,                   0xFFC388A4)
NHSTUB(dumpMemoryToFile,            0xFFC14214) // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(ints_disable,                0xFFC00578)
NHSTUB(ints_enable,                 0xFFC005A0)
NHSTUB(taskcreate_jogDial,          0xFFC38128)
