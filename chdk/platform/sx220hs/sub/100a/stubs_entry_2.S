#include "stubs_asm.h"
#define NULL_SUB 0xFF02D4BC

// Override stubs_entry.S
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)
NHSTUB(write,                       0xff00adb8)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(LockAndRefresh,              0xFF0AB250)
NHSTUB(MakeAFScan,                  0xFF18B938)
NHSTUB(MakeDirectory,               0xFF026A10)
NHSTUB(ReadSDCard,                  0xFF16C62C)
NHSTUB(UnlockAndRefresh,            0xFF0AB2B4)
NHSTUB(UnsetZoomForMovie,           0xFF1BB954)
NHSTUB(UpdateMBROnFlash,            0xFF06AC94)
NHSTUB(closefastdir,                0xFF2DD260)
NHSTUB(fclose,                      0xff026b18)
NHSTUB(fopen,                       0xff026ad8)
NHSTUB(fread,                       0xFF026BC4)
NHSTUB(fwrite,                      0xFF026C18)
NHSTUB(localtime,                   0xFF08446C)
NHSTUB(readdir,                     0xFF2DD404)
NHSTUB(ufree,                       0xFF02B884)
