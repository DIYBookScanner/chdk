#include "stubs_asm.h"
#define NULL_SUB 0xFF8117EC

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xff95b8e8)
NHSTUB(EnterToCompensationEVF,      NULL_SUB)
NHSTUB(ExitFromCompensationEVF,     NULL_SUB)
NHSTUB(GetDrive_ClusterSize,        0xFF86EE78)
NHSTUB(GetDrive_FreeClusters,       0xFF867C04)
NHSTUB(GetDrive_TotalClusters,      0xFF86EEB4)
NHSTUB(MakeAFScan,                  NULL_SUB)
NHSTUB(UnlockAF,                    0xff95b92c)
NHSTUB(VbattGet,                    0xFF82C1A0)
NHSTUB(free,                        0xFFB0B858)
NHSTUB(kbd_pwr_on,                  0xFF827EE0)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(SetScriptMode,               0xFF9701A0)
NHSTUB(kbd_read_keys,               0xFF826D30)

NHSTUB(printf,                      0xFFB07970)
NHSTUB(taskNameToId,                0xFFB18DB0)
NHSTUB(GetVRAMHPixelsSize,0xFFAC8268) // by find_eventproc name @ 0xFFB28578
NHSTUB(GetVRAMVPixelsSize,0xFFAC8274) // by find_eventproc name @ 0xFFB28580
