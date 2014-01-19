#include "stubs_asm.h"
#define NULL_SUB 0xFF04D3E0

// Override stubs_entry.S
NHSTUB(LEDDrive,                    0xFF04D06C)
NHSTUB(DeleteFile_Fut,              0xFF02163C)
NHSTUB(MakeDirectory_Fut,           0xFF02214C)     //mkdir
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(UnsetZoomForMovie,           NULL_SUB)

// Additional
NHSTUB(GPS_UpdateData,              0xFF140C20)
NHSTUB(LockAndRefresh,              0xFF0A27EC)
NHSTUB(MakeAFScan,                  0xFF1BC964)
NHSTUB(ReadSDCard,                  0xFF19D880)
NHSTUB(UnlockAndRefresh,            0xFF0A2850)
NHSTUB(UpdateMBROnFlash,            0xFF06084C)
NHSTUB(closefastdir,                0xFF32FE3C)
NHSTUB(fclose,                      0xFF021748)
NHSTUB(fopen,                       0xFF021708)
NHSTUB(fread,                       0xFF0217F4)
NHSTUB(fwrite,                      0xFF021848)
//NHSTUB(ufree,                       0xFF02574C) //not sure
