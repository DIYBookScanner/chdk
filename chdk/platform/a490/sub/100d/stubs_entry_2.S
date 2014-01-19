#include "stubs_asm.h"
#define NULL_SUB 0xFFC00B20

// Override stubs_entry.S
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xffd0f0c8)
NHSTUB(TurnOnMic,                   0xffc43c30)
NHSTUB(TurnOffMic,                  0xffc43c5c)
NHSTUB(closefastdir,                0xffde8c9c)
NHSTUB(platformsub_kbd_fetch_data,  0xffc435d4)
