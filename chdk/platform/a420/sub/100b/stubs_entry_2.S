#include "stubs_asm.h"
#define NULL_SUB 0xFFC017E8

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xFFD22BA0) //ok a420
NHSTUB(EnterToCompensationEVF,      0xFFD24990) //ok a420
NHSTUB(ExitFromCompensationEVF,     0xFFD249EC) //ok a420
NHSTUB(GetDrive_ClusterSize,        0xFFC59C04) //may be ok a420
NHSTUB(GetDrive_TotalClusters,      0xFFC59C40) //may be ok a420
NHSTUB(MakeAFScan,                  0xFFD2737C) //ok a420 i guess
NHSTUB(UnlockAF,                    0xFFD22BE4) //ok a420
NHSTUB(VbattGet,                    0xFFC1B014) //ok a420
NHSTUB(WriteSDCard,                 0xFFC69060) //ok i guess a420
NHSTUB(free,                        0xFFEA2A7C) //ok a420
NHSTUB(kbd_pwr_off,                 NULL_SUB)   //wrong, null stub
NHSTUB(kbd_pwr_on,                  NULL_SUB)   //wrong, null stub

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)   //ok, null stub, a420 also
NHSTUB(TurnOffMic,                  NULL_SUB)   //useless on a420, null stub
NHSTUB(TurnOnMic,                   NULL_SUB)   //useless on a420, null stub

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFCD8498) //ok a420
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFCD84C8) //ok a420
NHSTUB(MFOff,                       0xffd2369c)
NHSTUB(MFOn,                        0xffd2366c)
NHSTUB(SetScriptMode,               0xFFD36850) // ok a420
NHSTUB(GetVRAMHPixelsSize,0xFFE62850) // by find_eventproc name @ 0xFFEBFFC0
NHSTUB(GetVRAMVPixelsSize,0xFFE6285C) // by find_eventproc name @ 0xFFEBFFC8
