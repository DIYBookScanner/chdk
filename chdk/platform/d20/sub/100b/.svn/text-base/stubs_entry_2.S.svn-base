#include "stubs_asm.h"
#define NULL_SUB 0xFF000B48

// Override stubs_entry.S
NHSTUB(DeleteFile_Fut,              0xff020a70)
NHSTUB(MakeDirectory_Fut,           0xff021580)     //mkdir. This requires #define MKDIR_RETURN_ONE_ON_SUCCESS
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(LEDDrive,                    0xff04bc04)     //Untested!!

// Additional
NHSTUB(GPS_UpdateData,              0xff11ca4c)     //Untested!!

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
