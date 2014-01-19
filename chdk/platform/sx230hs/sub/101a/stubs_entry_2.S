#include "stubs_asm.h"
#define NULL_SUB 0xFF09D6EC

// Override stubs_entry.S
NHSTUB(Restart,                     0xff02d3d8)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(UnsetZoomForMovie,           NULL_SUB)

// Additional
NHSTUB(GPS_UpdateData,              0xFF0554A0)
NHSTUB(LockAndRefresh,              0xff0ad294)
NHSTUB(MakeAFScan,                  0xff191018)
NHSTUB(MakeDirectory,               0xff026e44)
NHSTUB(ReadSDCard,                  0xff171d08)
NHSTUB(UnlockAndRefresh,            0xff0ad2f8)
NHSTUB(UpdateMBROnFlash,            0xff06c264)
NHSTUB(closefastdir,                0xff2e6f38)
NHSTUB(fclose,                      0xff026f4c)
NHSTUB(fopen,                       0xff026f0c)
NHSTUB(fread,                       0xff026ff8)
NHSTUB(fwrite,                      0xff02704c)
NHSTUB(localtime,                   0xff085a38)
NHSTUB(ufree,                       0xff02bcb8)
