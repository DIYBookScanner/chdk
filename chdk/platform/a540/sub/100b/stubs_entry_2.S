#include "stubs_asm.h"
#define NULL_SUB 0xFFC017E8

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xffd41c64)
NHSTUB(EnterToCompensationEVF,      0xffd43ac8)
NHSTUB(ExitFromCompensationEVF,     0xffd43b28)
NHSTUB(GetDrive_ClusterSize,        0xFFC5DC9C)
NHSTUB(GetDrive_FreeClusters,       0xFFC5DD14) 
NHSTUB(GetDrive_TotalClusters,      0xFFC5DCD8)
NHSTUB(MakeAFScan,                  0xFFD4656C) 
NHSTUB(UnlockAF,                    0xffd41ca8)
NHSTUB(VbattGet,                    0xFFC1C014)
NHSTUB(WriteSDCard,                 0xFFC6D0E0)
NHSTUB(free,                        0xFFEE0F70) 

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFFCF1190) 
NHSTUB(ExpCtrlTool_StopContiAE,     0xFFCF11C0) 
NHSTUB(SetScriptMode,               0xFFD56460) 
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFE7D824) 
NHSTUB(TurnOffMic,                  0xffc1e788)
NHSTUB(TurnOnMic,                   0xffc1e74c)

// record mode live viewport dimensions
NHSTUB(GetVRAMHPixelsSize,0xFFE9E3A4)
NHSTUB(GetVRAMVPixelsSize,0xFFE9E3B0)

