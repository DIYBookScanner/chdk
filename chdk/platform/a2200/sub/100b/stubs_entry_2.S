#include "stubs_asm.h"

#define NULLSUB 0xFF810B24

// Not found
NHSTUB(kbd_pwr_on,          		NULLSUB)

//Additional
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFA9B6C0)
NHSTUB(MakeAFScan,					0xFF8DA094)
NHSTUB(platformsub_kbd_fetch_data,	0xFF8602B4)
NHSTUB(TurnOnMic,                   0xFF860934)
NHSTUB(TurnOffMic,                  0xFF860960)
