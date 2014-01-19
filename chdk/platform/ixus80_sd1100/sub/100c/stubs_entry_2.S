#include "stubs_asm.h"
#define NULL_SUB 0xffa7b658

// Override stubs_entry.S
NHSTUB(PutInNdFilter,               0xffa7aad0)
NHSTUB(PutOutNdFilter,              0xffa7ab08)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(TurnOffMic,                  NULL_SUB)
NHSTUB(TurnOnMic,                   NULL_SUB)

// Additional
NHSTUB(OpLog_WriteToSD,             0xff86ab44)
NHSTUB(PostLEDMessage,              0xff8420c0)
NHSTUB(dumpMemoryToFile,            0xffc141f4)
