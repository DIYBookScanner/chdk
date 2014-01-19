#include "stubs_asm.h"
#define NULL_SUB 0xFFC43E0C

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xFFC59F28)
NHSTUB(GetDrive_FreeClusters,       0xFFC524A0)
NHSTUB(LEDDrive,                    0xFFC43ACC)
NHSTUB(ScreenLock,                  0xFFD86EF4)
NHSTUB(ScreenUnlock,                0xFFD85BA4)
NHSTUB(SetScriptMode,               0xFFC00F70)
NHSTUB(UnlockAF,                    0xFFC59F38)
NHSTUB(kbd_pwr_off,                 NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(GetLogToFile,                0xFFD1A568)
NHSTUB(LockAndRefresh,              0xFFD86CEC)
NHSTUB(MakeAFScan,                  0xFFD16108)
NHSTUB(UnlockAndRefresh,            0xFFD86D30)
NHSTUB(closefastdir,                0xFFDF61C0)
NHSTUB(readfastdir,                 0xFFDF6364)
