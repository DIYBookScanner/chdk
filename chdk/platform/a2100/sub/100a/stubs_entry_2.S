#include "stubs_asm.h"
#define NULL_SUB 0xFFC00950

// Override stubs_entry.S

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent,     0xFFDECE54)

// Additional
NHSTUB(ScreenLock,                      0xFFD6BDDC)
NHSTUB(ScreenUnlock,                    0xFFD6BE30)







