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
NHSTUB(GPS_UpdateData,              0xFF140C20)     //asm1989 100b FF140BB0 Looks like sx230 FF0554A0
//NHSTUB(LockAndRefresh,              0xFF0A27EC)     //asm1989 Looks like sx230 ff0ad294
NHSTUB(MakeAFScan,                  0xFF1BC964)     //asm1989 100b FF1BC8FC Looks like sx230    ff191018
NHSTUB(ReadSDCard,                  0xFF19D880)     //asm1989 100b FF19D818 Like sx40 FF1AB268
//NHSTUB(UnlockAndRefresh,            0xFF0A2850)     //asm1989 Looks like sx230  ff0ad2f8
NHSTUB(UpdateMBROnFlash,            0xFF06084C)     //asm1989 Like Sx40  FF06A4E4
NHSTUB(closefastdir,                0xFF32FE04)     //asm1989 100b FF32FD9C like sx40  FF33952C
NHSTUB(fclose,                      0xFF021748)     //asm1989 like sx40  FF027078
NHSTUB(fopen,                       0xFF021708)     //asm1989
NHSTUB(fread,                       0xFF0217F4)     //asm1989
NHSTUB(fwrite,                      0xFF021848)     //asm1989
NHSTUB(localtime,                   0x0068F2F4)     //asm1989 Looks like RAm 0x68F2F4 in sx230 was ff085a38
NHSTUB(ufree,                       0xFF02574C)     //asm1989 like sx40  FF02BEA0
