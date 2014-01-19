#include "stubs_asm.h"
#define NULL_SUB 0xFF810B4C

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(MakeDirectory_Fut,           0xff831940)  //mkdir. This requires #define MKDIR_RETURN_ONE_ON_SUCCESS

//Additional
NHSTUB(TurnOnMic,                   0xff857008)
NHSTUB(TurnOffMic,                  0xff857034)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(srand,                       NULL_SUB)  //overridable function
NHSTUB(rand,                        NULL_SUB)  //overridable function
