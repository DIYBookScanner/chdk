#include "stubs_asm.h"

#define NULLSUB 0xFF85F300

// Not found
NHSTUB(kbd_pwr_on, NULLSUB)
NHSTUB(kbd_pwr_off, NULLSUB)
NHSTUB(SetZoomActuatorSpeedPercent, NULLSUB)

// Override stubs_entry.S

NHSTUB(GetBatteryTemperature, NULLSUB)   // Does not work in A1200, SX130 & A800 (included dummy in sub/100c/lib.c)

NHSTUB(MakeAFScan, 0xff8d95ec)
NHSTUB(LockAndRefresh, 0xff8a39a4)
NHSTUB(UnlockAndRefresh, 0xff8a3a08)
NHSTUB(platformsub_kbd_fetch_data, 0xff85f968)

// Additional
NHSTUB(TurnOnMic,                   0xff85ffe4)
NHSTUB(TurnOffMic,                  0xff860010)
