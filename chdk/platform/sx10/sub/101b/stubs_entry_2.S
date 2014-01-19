#include "stubs_asm.h"
#define NULL_SUB 0xFF81093C

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(platformsub_kbd_fetch_data,  0xFF84B660)
