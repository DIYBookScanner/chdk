#include "stubs_asm.h"
#define NULL_SUB 0xFF858BEC

// Override stubs_entry.S
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(EdidDump,                    0xFF841BE8)
NHSTUB(GetCurrentTargetDistance,    0xFF912430)
NHSTUB(HdmiRegDump,                 0xFF841CB0)
NHSTUB(MakeAFScan,                  0xFF85B170)
NHSTUB(MoveIrisFullClose,           0xFFA9237C)
NHSTUB(OpLog_Get,                   0xFF86C53C)
NHSTUB(ScreenLock,                  0xFF99CEC4)
NHSTUB(ShowAllTaskInfo,             0xFF91BA70)
NHSTUB(blah,                        0xFF8462F8);
NHSTUB(drvInfo,                     0xFF81E33C);
NHSTUB(open2,                       0xFF823C70);
NHSTUB(qprintf,                     0xFF8115A8)
NHSTUB(stdioSetup,                  0xFF813578)
