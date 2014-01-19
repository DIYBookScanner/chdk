#include "stubs_asm.h"
#define NULL_SUB 0xFF810950

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xFF85E914)
NHSTUB(EnterToCompensationEVF,      NULL_SUB)
NHSTUB(ExitFromCompensationEVF,     NULL_SUB)
NHSTUB(UnlockAF,                    0xFF85E924)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(kbd_pwr_off,                 NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(LogPrintf,                   0xFF86EF38)
NHSTUB(MakeAFScan,                  0xFF932820)
NHSTUB(ScreenLock,                  0xFF9B967C)
NHSTUB(exmem_free,                  0xFF86C7B0)
