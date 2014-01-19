#include "stubs_asm.h"
#define NULL_SUB 0xFF04D3E0

// Override stubs_entry.S
NHSTUB(LEDDrive,                    0xFF04D06C)
NHSTUB(MakeDirectory_Fut,           0xFF02214C)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(UnsetZoomForMovie,           NULL_SUB)

// Additional
NHSTUB(GPS_UpdateData,              0xFF140BB0)
//NHSTUB(LockAndRefresh,              0xFF0A27EC) //asm1989 Looks like sx230 ff0ad294
NHSTUB(MakeAFScan,                  0xFF1BC8FC)
NHSTUB(ReadSDCard,                  0xFF19D818)
//NHSTUB(UnlockAndRefresh,            0xFF0A2850) //asm1989 Looks like sx230  ff0ad2f8
NHSTUB(UpdateMBROnFlash,            0xFF06084C)
NHSTUB(closefastdir,                0xFF32FD9C)
NHSTUB(fclose,                      0xFF021748)
NHSTUB(fopen,                       0xFF021708)
NHSTUB(fread,                       0xFF0217F4)
NHSTUB(fwrite,                      0xFF021848)
NHSTUB(localtime,                   0x0068F2F4)
NHSTUB(ufree,                       0xFF02574C)
