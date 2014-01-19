#include "stubs_asm.h"
#define NULL_SUB 0xFF810950

// Override stubs_entry.S
NHSTUB(GetSystemTime,               0xFF8606AC)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(TurnOffMic,                  NULL_SUB)
NHSTUB(TurnOnMic,                   NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFF93B538)
NHSTUB(PostLEDMessage,              0xFF847470)
NHSTUB(platformsub_kbd_fetch_data,  0xFF848340)

// Palette
NHSTUB(ScreenLock,                0xFF9D4F28)
