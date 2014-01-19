#include "stubs_asm.h"
#define NULL_SUB 0xFF9EA4EC

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xff99afd0)
NHSTUB(ExitFromCompensationEVF,     0xff99b244)
NHSTUB(GetDrive_ClusterSize,        0xff87c338)
NHSTUB(GetDrive_FreeClusters,       0xff87c3b0)
NHSTUB(Restart,                     0xFF823ABC)
NHSTUB(UnlockAF,                    0xff99b044)
NHSTUB(WriteSDCard,                 0xFF88BE6C)
NHSTUB(free,                        0xFFB9EBF4)
NHSTUB(kbd_read_keys_r2,            0xFF828E70)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF925F0C)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFF925F3C)
NHSTUB(GiveSemaphore,               0xFF82218C)
NHSTUB(SetScriptMode,               0xFF9B398C)
NHSTUB(platformsub_kbd_fetch_data,  0xFF8293AC)

NHSTUB(taskNameToId,                0xFFBAB72C)
NHSTUB(GetVRAMHPixelsSize,0xFFB567E4) // by find_eventproc name @ 0xFFBBBFC0
NHSTUB(GetVRAMVPixelsSize,0xFFB567F0) // by find_eventproc name @ 0xFFBBBFC8
