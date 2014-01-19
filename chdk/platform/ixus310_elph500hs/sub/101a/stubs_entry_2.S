#include "stubs_asm.h"
#define NULL_SUB 0xFF055974

// These don´t exist/aren´t found in dryos
NHSTUB(SetZoomActuatorSpeedPercent,		NULL_SUB)

// Additional
NHSTUB(SetCDSGain,						0xFF384A50)
NHSTUB(GetCdsGainValue,					0xFF3849B0)
