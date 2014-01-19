#include "stubs_asm.h"
#define NULL_SUB 0xFFC00950

// Override stubs_entry.S
NHSTUB(GetDrive_ClusterSize,        0xFFC45918)
NHSTUB(GetDrive_FreeClusters,       0xFFC45978)
NHSTUB(GetDrive_TotalClusters,      0xFFC45948)
NHSTUB(RefreshPhysicalScreen,       0xFFD9098C)
NHSTUB(ScreenUnlock,                0xFFD90B78)
NHSTUB(SetScriptMode,               0xFFC63B40)
NHSTUB(kbd_pwr_off,                 0xFFC36F60)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFFD16FF4)
NHSTUB(TurnOffMic,                  0xFFC37A8C)
NHSTUB(TurnOnMic,                   0xFFC37A60)
NHSTUB(UIFS_GetLastPath,            0xFFD15C48)

// Override for 'stat' found by sig finder - needs old version
NHSTUB(stat,                        0xffc13a9c)
