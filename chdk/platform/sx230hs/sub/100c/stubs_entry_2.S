#include "stubs_asm.h"
#define NULL_SUB 0xFF09D6EC

// Override stubs_entry.S
NHSTUB(Restart,                     0xFF02D3D0)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(UnsetZoomForMovie,           NULL_SUB)

// Additional
NHSTUB(GPS_UpdateData,              0xFF055488)
NHSTUB(LockAndRefresh,              0xFF0AD1B4)
NHSTUB(MakeAFScan,                  0xFF190E5C)
NHSTUB(MakeDirectory,               0xFF026DE0)
NHSTUB(ReadSDCard,                  0xFF171B28)
NHSTUB(UnlockAndRefresh,            0xFF0AD218)
NHSTUB(UpdateMBROnFlash,            0xff06c1b4)
NHSTUB(closefastdir,                0xFF2E6DB8)
NHSTUB(fclose,                      0xFF026EE8)
NHSTUB(fopen,                       0xFF026EA8)
NHSTUB(fread,                       0xFF026F94)
NHSTUB(fwrite,                      0xFF026FE8)
NHSTUB(localtime,                   0xFF085A08)
NHSTUB(ufree,                       0xFF02BCB0)
