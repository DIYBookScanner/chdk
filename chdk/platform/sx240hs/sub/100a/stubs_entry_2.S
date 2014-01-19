#include "stubs_asm.h"
#define NULL_SUB 0xFF04D3E0

// Override stubs_entry.S
NHSTUB(LEDDrive,                    0xff04d06c)
NHSTUB(DeleteFile_Fut,              0xff02163c)
NHSTUB(MakeDirectory_Fut,           0xff02214c)
NHSTUB(kbd_pwr_off,                   NULL_SUB)
NHSTUB(kbd_pwr_on,                    NULL_SUB)

// These does not exist
NHSTUB(SetZoomActuatorSpeedPercent,   NULL_SUB)
NHSTUB(UnsetZoomForMovie,             NULL_SUB)

// Additional
NHSTUB(GPS_UpdateData,              0xff140b8c)
NHSTUB(LockAndRefresh,              0xff0a27ec)
NHSTUB(MakeAFScan,                  0xff1bc8d4)
NHSTUB(ReadSDCard,                  0xff19d7f0)
NHSTUB(UnlockAndRefresh,            0xff0a2850)
NHSTUB(UpdateMBROnFlash,            0xff06084c)
NHSTUB(closefastdir,                0xff32fd74)
NHSTUB(fclose,                      0xff021748)
NHSTUB(fopen,                       0xff021708)
NHSTUB(fread,                       0xff0217f4)
NHSTUB(fwrite,                      0xff021848)
NHSTUB(localtime,                   0x0068abf0)
NHSTUB(ufree,                       0xff02574c)
