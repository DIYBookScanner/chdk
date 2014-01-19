#include "stubs_asm.h"
#define NULL_SUB 0xFFC00954

// Override stubs_entry.S
NHSTUB(GetBatteryTemperature,       0xFFC2EB38)  // =GetCCDTemperature
NHSTUB(GetCCDTemperature,           0xFFC2EB38)
NHSTUB(PutInNdFilter,               0xFFE01E0C)
NHSTUB(PutOutNdFilter,              0xFFE01E44)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(kbd_read_keys_r2,            0xFFC1138C)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFCE7CC0)
NHSTUB(TurnOffMic,                  0xFFC2CF34)
NHSTUB(TurnOnMic,                   0xFFC2CF08)
NHSTUB(platformsub_kbd_fetch_data,  0xFFC2C8AC)
