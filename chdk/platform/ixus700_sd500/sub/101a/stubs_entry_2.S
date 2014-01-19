#include "stubs_asm.h"
#define NULL_SUB 0xFF8118C0

// Override stubs_entry.S
NHSTUB(Close,                       0xFF86A944)
NHSTUB(DoAFLock,                    0xff94ef7c)
NHSTUB(EnterToCompensationEVF,      NULL_SUB)
NHSTUB(ExitFromCompensationEVF,     NULL_SUB)
NHSTUB(GetBatteryTemperature,       0xFFA4DA28)
NHSTUB(GetCCDTemperature,           0xFFA4DA14)
NHSTUB(GetCurrentAvValue,           0xFFA4F304)
NHSTUB(GetDrive_ClusterSize,        0xFF86A150)
NHSTUB(GetDrive_FreeClusters,       0xFF86A1C8)
NHSTUB(GetDrive_TotalClusters,      0xFF86A18C)
NHSTUB(GetFocusLensSubjectDistance, 0xFFA64C48)
NHSTUB(GetOpticalTemperature,       0xFFA4DA00)
NHSTUB(GetPropertyCase,             0xFF825CA4)
NHSTUB(GetZoomLensCurrentPoint,     0xFFA56F6C)
NHSTUB(GetZoomLensCurrentPosition,  0xFFA56F80)
NHSTUB(MakeAFScan,                  0xFF94EF7C)
NHSTUB(Mount_FileSystem,            0xFF869CD4)
NHSTUB(Open,                        0xFF86A938)
NHSTUB(PT_PlaySound,                0xFF960080)
NHSTUB(PhySw_testgpio,              NULL_SUB)
NHSTUB(Read,                        0xFF86A9A4)
NHSTUB(Remove,                      0xFF86A950)
NHSTUB(Restart,                     0xFF8233A0)
NHSTUB(SetPropertyCase,             0xFF825B9C)
NHSTUB(UnlockAF,                    0xff94eff4)
NHSTUB(UnsetZoomForMovie,           0xFF999F50)
NHSTUB(VbattGet,                    0xFFA60A4C)
NHSTUB(Write,                       0xFF86A9B0)
NHSTUB(WriteSDCard,                 0xFF87CACC)
NHSTUB(free,                        0xFFABCC28)
NHSTUB(kbd_p1_f,                    NULL_SUB)
NHSTUB(kbd_p1_f_cont,               0xFF828FEC)
NHSTUB(kbd_p2_f,                    NULL_SUB)
NHSTUB(kbd_read_keys_r2,            NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF8F94B8)
NHSTUB(SetScriptMode,               0xFF966290)
NHSTUB(UniqueLedOff,                0xFFA68888)
NHSTUB(UniqueLedOn,                 0xFFA6882C)
NHSTUB(kbd_p1_1,                    0xFF8293FC)
NHSTUB(kbd_p1_2,                    0xFF829464)
NHSTUB(kbd_p1_3,                    0xFF829848)
NHSTUB(platformsub_kbd_fetch_data,  0xFF8299B4)

// New finsig_vxworks differences?
NHSTUB(kbd_pwr_off, 0xffa476ac)
