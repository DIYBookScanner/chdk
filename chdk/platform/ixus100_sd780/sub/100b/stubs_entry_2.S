#include "stubs_asm.h"
#define NULL_SUB 0xff858bec

// Override stubs_entry.S
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(EdidDump,                    0xff841be8)
NHSTUB(GetCurrentTargetDistance,    0xff912430)
NHSTUB(HdmiRegDump,                 0xff841cb0)
NHSTUB(MakeAFScan,                  0xff85b170)
NHSTUB(MoveIrisFullClose,           0xffa92360)
NHSTUB(OpLog_Get,                   0xff86c53c)
NHSTUB(ScreenLock,                  0xff99cec4)
NHSTUB(ShowAllTaskInfo,             0xff91ba70)
NHSTUB(blah,                        0xff8462f8)
NHSTUB(drvInfo,                     0xff81e33c)
NHSTUB(open2,                       0xff823c70)
NHSTUB(qprintf,                     0xff8115a8)
NHSTUB(stdioSetup,                  0xff813578)
