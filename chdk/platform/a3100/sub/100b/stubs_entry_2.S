#include "stubs_asm.h"
#define NULL_SUB 0xFF869B58

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
//NHSTUB(GetLogToFile,                0xFFD1A618)
NHSTUB(LockAndRefresh,              0xFF9B44C4)
NHSTUB(MakeAFScan,                  0xFF930944)
NHSTUB(GetDrive_FreeClusters, 0xff863190)
NHSTUB(UnlockAndRefresh,            0xFF9B4508)
//NHSTUB(closefastdir,                0xFFDF61C4)
//NHSTUB(readfastdir,                 0xFFDF6368)
