#include "stubs_asm.h"

NHSTUB(LockAndRefresh,		0xFF8B18F4)
NHSTUB(UnlockAndRefresh, 	0xFF8B1958)
NHSTUB(MakeAFScan, makeafscan_hack)

//All pointed to nullsub_20 (NULL)
NHSTUB(Unmount_FileSystem 						,0xFF907390) //fake
NHSTUB(Mount_FileSystem 						,0xFF907390) //fake
NHSTUB(SetZoomActuatorSpeedPercent 				,0xFF907390) //fake
NHSTUB(rewinddir 								,0xFF907390) //fake
NHSTUB(kbd_pwr_on 								,0xFF907390) //fake


