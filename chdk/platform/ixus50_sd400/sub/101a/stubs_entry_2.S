#include "stubs_asm.h"
#define NULL_SUB 0xFF8118C0

// Override stubs_entry.S
NHSTUB(Close,                       0xFF874B9C)
NHSTUB(DisplayImagePhysicalScreen,  0xFF93C9EC)
NHSTUB(DoAFLock,                    0xff958ef8)
NHSTUB(EnterToCompensationEVF,      0xff959074)
NHSTUB(ExitFromCompensationEVF,     0xff9590c8)
NHSTUB(GetBatteryTemperature,       0xFF82D754)
NHSTUB(GetCCDTemperature,           0xFF82D740)
NHSTUB(GetCurrentAvValue,           0xFFA5168C)
NHSTUB(GetDrive_ClusterSize,        0xFF8743BC)
NHSTUB(GetDrive_FreeClusters,       0xFF874434)
NHSTUB(GetDrive_TotalClusters,      0xFF8743F8)
NHSTUB(GetFocusLensSubjectDistance, 0xFFA66F2C)
NHSTUB(GetOpticalTemperature,       0xFF82D72C)
NHSTUB(GetPropertyCase,             0xFF825AA8)
NHSTUB(GetZoomLensCurrentPoint,     0xFFA59380)
NHSTUB(GetZoomLensCurrentPosition,  0xFFA59394)
NHSTUB(MakeAFScan,                  NULL_SUB)
NHSTUB(Mount_FileSystem,            0xFF873F40)
NHSTUB(Open,                        0xFF874B90)
NHSTUB(PhySw_testgpio,              NULL_SUB)
NHSTUB(Read,                        0xFF874BFC)
NHSTUB(Remove,                      0xFF874BA8)
NHSTUB(Restart,                     0xFF823B90)
NHSTUB(SetPropertyCase,             0xFF8259A0)
NHSTUB(UnlockAF,                    0xff958f70)
NHSTUB(UnsetZoomForMovie,           0xFF9A4DB0)
NHSTUB(VbattGet,                    0xFFA62D30)
NHSTUB(Write,                       0xFF874C08)
NHSTUB(WriteSDCard,                 NULL_SUB)
NHSTUB(free,                        0xFFABEBEC)
NHSTUB(kbd_p1_f,                    NULL_SUB)
NHSTUB(kbd_p1_f_cont,               0xFF828DE0)
NHSTUB(kbd_p2_f,                    NULL_SUB)
NHSTUB(kbd_read_keys_r2,            NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(SetScriptMode,               0xFF9706BC)
NHSTUB(UniqueLedOff,                0xFF82E024)
NHSTUB(UniqueLedOn,                 0xFF82DFC8)
NHSTUB(kbd_p1_1,                    0xFF8291F0)
NHSTUB(kbd_p1_2,                    0xFF829258)
NHSTUB(kbd_p1_3,                    0xFF82963C)
NHSTUB(platformsub_kbd_fetch_data,  0xFF8297A8)

// New finsig_vxworks differences?
NHSTUB(kbd_pwr_off, 0xff82a120)
