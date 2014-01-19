#include "stubs_asm.h"
#define NULL_SUB 0xFFC00950

// Override stubs_entry.S
//NHSTUB(DoAFLock,                    0xFFC47B8C)
//NHSTUB(SetScriptMode,               NULL_SUB)
//NHSTUB(UnlockAF,                    0xFFC47B9C)
//NHSTUB(WriteSDCard,                 0xFFCE4118)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
//NHSTUB(kbd_read_keys,               0xFFC11D80)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(GetCurrentTargetDistance,    0xFFCF0434)
NHSTUB(OpLog_Get,                   0xFFC58590)
NHSTUB(ScreenLock,                  0xFFD64C2C)
NHSTUB(ScreenUnLock,                0xFFD64C80)
NHSTUB(MakeAFScan,                  0xffcfa960)