#include "stubs_asm.h"
#define NULL_SUB 0xFF810B1C

// Override stubs_entry.S
NHSTUB(LockAndRefresh,              0xff8b4eec)   
NHSTUB(MakeAFScan,                  0xff989950)   
NHSTUB(UnlockAndRefresh,            0xff8b4f50)   
NHSTUB(strcat,                      0xFF8B54B0) 
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
