#include "stubs_asm.h"
#define NULL_SUB 0xFF000B54

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                   NULL_SUB)
NHSTUB(kbd_pwr_on,                    NULL_SUB)

// These does not exist
NHSTUB(SetZoomActuatorSpeedPercent,   NULL_SUB)
NHSTUB(MakeDirectory_Fut,           0xff0286cc)  //mkdir

// Additional
NHSTUB(SetCDSGain,                  0xff482174)
NHSTUB(GetCdsGainValue,             0xff4820ec)

