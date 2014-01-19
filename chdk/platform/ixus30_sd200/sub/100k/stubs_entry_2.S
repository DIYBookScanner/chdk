#include "stubs_asm.h"

#define NULL_SUB 0xff8101d0

NHSTUB(AllocateMemory, 0xff81eb24) // ixus40 port has something different here, this value should be correct (function found by name!!!)
NHSTUB(Close, 0xFF871688) //
NHSTUB(CreatePhysicalVram, 0xff9278cc) //
NHSTUB(DisplayImagePhysicalScreen, 0xff926e58) //
NHSTUB(DoAFLock, 0xff93de38) //
NHSTUB(EnterToCompensationEVF, 0xff93df9c) //
NHSTUB(ExecuteEventProcedure, 0xFF81756C) // same as in ixus40
NHSTUB(ExitFromCompensationEVF, 0xff93dfdc) //
NHSTUB(Feof_Fut, 0xff869d08)
NHSTUB(FreeMemory, 0xff81eb10) //ixus40: same issue as with allocatememory
NHSTUB(FreeUncacheableMemory, 0xFF8152BC) // same
NHSTUB(GetBatteryTemperature, 0xffa486ac)  //
NHSTUB(GetCCDTemperature, 0xffa48698) //
NHSTUB(GetCurrentAvValue, 0xffa690a4) // ixus40 port different again
NHSTUB(GetCurrentMachineTime, 0xff8209cc) // this is the inner function
NHSTUB(GetDrive_ClusterSize, 0xFF8707EC) //same
NHSTUB(GetDrive_FreeClusters, 0xFF87086C) //same
NHSTUB(GetDrive_TotalClusters, 0xFF87082C) //same
NHSTUB(GetFocusLensSubjectDistance, 0xFFA5F808) // inner function
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xffa5fe7c) // inner function
NHSTUB(GetOpticalTemperature, 0xffa48684) //
NHSTUB(GetParameterData, GetParameterData_my) //needed because of this ancient implementation
NHSTUB(GetParameterData_orig, 0xff958b44) //try this instead of 0xff95a318) //
NHSTUB(GetPropertyCase, GetPropertyCase_my)
NHSTUB(GetPropertyCase_orig, 0xFF82CB54) // same
NHSTUB(GetZoomLensCurrentPoint, 0xffa50fe8) // 0xffa51f18 in the fw table, but that jumps here ! ixus40 port has something different here which may not be ok
NHSTUB(GetZoomLensCurrentPosition, 0xffa51f24) // ixus40 port has something different here again
NHSTUB(GiveSemaphore, 0xFF823144) // same location
NHSTUB(IsStrobeChargeCompleted, IsStrobeChargeCompleted_my)
NHSTUB(LockMainPower, 0xff955f58) //
NHSTUB(MakeAFScan, NULL_SUB) //nullstub
NHSTUB(Mount_FileSystem, 0xFF8702E4) // same
NHSTUB(MoveFocusLensToDistance, 0xffa6ae90) //
NHSTUB(Open,  0xFF87167C) //
NHSTUB(PT_PlaySound, 0xff94f078) //typo in ixus40: should be 0xff94f2bc there
NHSTUB(PhySw_testgpio, 0xFF82FA8C) // same
NHSTUB(Read,  0xFF8716E8) //
NHSTUB(Remove, 0xFF871694) // same
NHSTUB(Restart,0xFF824F58) // same
NHSTUB(SetAFBeamBrightness, 0xffa629d8) //
NHSTUB(SetAFBeamOff, 0xffa62a54) //
NHSTUB(SetAutoShutdownTime, 0xff955e48) //
NHSTUB(SetCurrentCaptureModeType,NULL_SUB) // NOT FOUND, NULLSUB
NHSTUB(SetLogicalEventActive,NULL_SUB) // NOT FOUND, NULLSUB
NHSTUB(SetParameterData, SetParameterData_my) //needed because of this ancient implementation
NHSTUB(SetParameterData_orig, 0xff95a258) //
NHSTUB(SetPropertyCase, SetPropertyCase_my)
NHSTUB(SetPropertyCase_orig, 0xFF82CAD0) // same
NHSTUB(SetScriptMode,0xff9559e0) //
NHSTUB(SetTimerWhen, 0xFF815828) // same
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB) //mov pc, lr
NHSTUB(ShowAllTaskInfo, 0xffa9e68c) //
NHSTUB(ShowCameraLog, 0xFF81A1A8) // same
NHSTUB(UniqueLedOff, NULL_SUB)
NHSTUB(UniqueLedOn, NULL_SUB)
NHSTUB(UnlockAF, 0xff93de98) //
NHSTUB(UnlockMainPower, 0xff956014) //
NHSTUB(UnsetZoomForMovie, NULL_SUB) // trials below
//ActivateZoomController 0xFF9954E0 -> not good
//0xFF9953DC -> not good

NHSTUB(VbattGet, 0xffa5ba68) //
NHSTUB(Write, 0xFF8716F4) //
NHSTUB(WriteSDCard, NULL_SUB) //nullstub
NHSTUB(free, 0xffac56a8) //
NHSTUB(iosDevFind, 0xffac3808) //
NHSTUB(iosInit, 0xffac390c) //
NHSTUB(kbd_p1_f, NULL_SUB)
NHSTUB(kbd_p1_f_cont, 0xFF830AB4) // same
NHSTUB(kbd_p2_f, NULL_SUB)
NHSTUB(kbd_read_keys_r2, NULL_SUB)
NHSTUB(memPartFindMax,0xffac4368) //
NHSTUB(memPartInfoGet,NULL_SUB)
NHSTUB(semBCreate, 0xffacef28) // this is an inside function...
NHSTUB(sub_FF821D04, 0xFF821D04) // same
NHSTUB(time, time_my)
NHSTUB(time_orig, 0xffabd9d0)

// trial
NHSTUB(EnterToPlayFromRec, 0xFF93D600)
NHSTUB(EnterToRecFromPlay, 0xFF93D534)
NHSTUB(tasktcb, 0xFFAD2064)

//don't touch these, old notes

/* looks like these are not equivalent
NHSTUB(Open,  0xffac2ca0) // "open"
NHSTUB(Read,  0xffac26bc) // "read"
NHSTUB(Write, 0xffac272c) // "write"
NHSTUB(Close, 0xffac265c) // "close"
*/

//NHSTUB(time, 0xff8149c8) //Time, but it works equally wrong as time

// New finsig_vxworks differences?
NHSTUB(kbd_pwr_off, 0xffa4155c)
