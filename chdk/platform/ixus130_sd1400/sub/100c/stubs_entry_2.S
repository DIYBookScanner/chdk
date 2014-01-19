#include "stubs_asm.h"

// 0xff811800 is a nullsub (points to a "bx lr" instruction)

NHSTUB(GetDrive_FreeClusters, 0xff86f510) // use the 2nd choice found by the sigfinder

NHSTUB(MakeAFScan, 0xff95d380)				// "SsPrepareSeqBase.c"
NHSTUB(SetZoomActuatorSpeedPercent, 0xff811800)		// 
NHSTUB(kbd_pwr_on, 0xff811800)				//
NHSTUB(kbd_pwr_off, 0xff811800)				//
NHSTUB(LockAndRefresh, 0xff9f8a9c)			// (000005bc) near "Window.c"
NHSTUB(UnlockAndRefresh, 0xff9f8ae0)			// ditto
