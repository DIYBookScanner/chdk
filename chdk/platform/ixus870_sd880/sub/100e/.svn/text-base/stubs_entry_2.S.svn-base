#include "stubs_asm.h"
#define NULL_SUB 0xFF81093C

// Override stubs_entry.S
NHSTUB(GetDrive_TotalClusters,      0xff85557c)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(MakeAFScan,                  0xFF933E50)
NHSTUB(ScreenLock,                  0xFF9B83CC)
NHSTUB(platformsub_kbd_fetch_data,  0xFF846248)
