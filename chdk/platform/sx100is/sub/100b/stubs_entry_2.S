#include "stubs_asm.h"
#define NULL_SUB 0xFFC00958

// Override stubs_entry.S
NHSTUB(GetZoomLensCurrentPosition,  0xFFD0E36C)
NHSTUB(MoveFocusLensToDistance,     0xFFDC0C60)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFDEFB38)
NHSTUB(PostLEDMessage,              0xFFC37434)
NHSTUB(TurnOffMic,                  0xFFC3889C)
NHSTUB(TurnOnMic,                   0xFFC38870)
NHSTUB(dumpMemoryToFile,            0xFFC14214) // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
NHSTUB(ints_disable,                0xFFC00578)
NHSTUB(ints_enable,                 0xFFC005A0)
NHSTUB(taskcreate_jogDial,          0xFFC380F4)
