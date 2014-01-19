#include "stubs_asm.h"
#define NULL_SUB 0xFF810B4C

// Override stubs_entry.S
NHSTUB(DeleteFile_Fut,              0xff830fb4)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(MakeDirectory_Fut,           0xff831ac4) //mkdir requires #define MKDIR_RETURN_ONE_ON_SUCCESS 

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(srand,                       NULL_SUB)  //overridable function
NHSTUB(rand,                        NULL_SUB)  //overridable function
