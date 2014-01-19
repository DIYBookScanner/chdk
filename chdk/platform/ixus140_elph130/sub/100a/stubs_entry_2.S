#include "stubs_asm.h"
#define NULLSUB 0xFF0017D8
NHSTUB(MakeDirectory_Fut, 0xff034678) //mkdir. This requires #define MKDIR_RETURN_ONE_ON_SUCCESS
NHSTUB(finish_shutdown,0xFF037FE4) // for shutdown(), to complicated to emulate

// Additional
NHSTUB(LogPrintf,0xFF0BF58C) // camera log debugging

// Not needed
NHSTUB(RefreshPhysicalScreen, NULLSUB)
// these don't exist
NHSTUB(kbd_pwr_off, NULLSUB)
NHSTUB(kbd_pwr_on, NULLSUB)
NHSTUB(SetZoomActuatorSpeedPercent,NULLSUB)
