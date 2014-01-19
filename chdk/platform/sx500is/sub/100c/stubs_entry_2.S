#include "stubs_asm.h"
#define NULL_SUB 0xFF055F00

// Override stubs_entry.S
NHSTUB(kbd_pwr_on,                      NULL_SUB)
NHSTUB(kbd_pwr_off,                     NULL_SUB)
NHSTUB(MakeDirectory_Fut,               0xff01c154)  //mkdir. This requires #define MKDIR_RETURN_ONE_ON_SUCCESS

// These do not exist
NHSTUB(SetZoomActuatorSpeedPercent,     NULL_SUB)
