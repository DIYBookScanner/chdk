#include "stubs_asm.h"
#define NULL_SUB 0xFF810958

// Override stubs_entry.S
NHSTUB(GetCCDTemperature,           0xFF846E08)
NHSTUB(GetOpticalTemperature,       0xFF846CE4)
NHSTUB(NewTaskShell,                0xFFC596B0)
NHSTUB(PutInNdFilter,               0xFF9E8AC4)
NHSTUB(PutOutNdFilter,              0xFF9E8AFC)
NHSTUB(UIFS_WriteFirmInfoToFile,    0xFFD4A934)
NHSTUB(kbd_pwr_off,                 0xFF844640)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(dumpMemoryToFile,            0xFFC141Fa) // writes a portion of memory into a file (char* filename, 0, (void*) src, int length)
