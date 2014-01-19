#include "stubs_asm.h"

#define NULL_SUB 0xFF81030C

// org s80 nov 2
NHSTUB(free, 0xFFB05B78)
NHSTUB(GetDrive_ClusterSize,        0xff86f8a4)
NHSTUB(GetDrive_TotalClusters,      0xFF86F900) //david GetDrive_TotalClusters ok
NHSTUB(GetDrive_FreeClusters,       0xff86f93c)

NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

NHSTUB(TurnOffMic,                  NULL_SUB)
NHSTUB(TurnOnMic,                   NULL_SUB)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFF8F87F8)
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF8F87E0)

// find_eventproc
NHSTUB(VbattGet,                    0xFF82C2B4) // by find_eventproc name @ 0xFF82C5F8
NHSTUB(PutInNdFilter,               0xFFAB67C0) // note: there's no ND filter
NHSTUB(DoAFLock,                    0xFF95124C) // by find_eventproc name @ 0xFF94F7D0
NHSTUB(SetScriptMode,               0xFF966160) // by find_eventproc name @ 0xFF98E4DC

NHSTUB(platformsub_kbd_fetch_data, 0xFF82784C) //S80 org
NHSTUB(kbd_read_keys_r2, 0xFF82737C) //s80 org
NHSTUB(taskcreate_JogDial, 0xFF8283b8)
NHSTUB(task_JogDial, 0xFF8287a8)
NHSTUB(taskNameToId, 0xFFB136CC)

NHSTUB(orig_MoveFocusLensToDistance, 0xffab89d8)
NHSTUB(MoveFocusLensToDistance, my_MoveFocusLensToDistance)

NHSTUB(MakeAFScan, my_MakeAFScan)
NHSTUB(orig_MakeAFScan, 0xff955dd8)

NHSTUB(LEDDrive, 0xFF82DBB8)
NHSTUB(PostLEDMessage, 0xFF82D8FC)

// New finsig_vxworks differences?
NHSTUB(kbd_pwr_off, 0xff828fec)
