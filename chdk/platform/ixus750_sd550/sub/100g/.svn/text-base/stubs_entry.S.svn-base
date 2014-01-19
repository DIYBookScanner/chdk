// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00G   // Found @ 0xff81add0, "GM1.00G" @ 0xff81addd
//   Firmware build timestamp: Aug  3 2005 13:58:33
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 7.39MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009f5b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(EnterToCompensationEVF               ,0xff94c928) //  1 64%    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff94c9f4) //  1 73%    *** != 0x00000000
NHSTUB(GetFocusLensSubjectDistance            ,0xffa7e3f4) //  1 90%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa7e994) //  3 52%
NHSTUB(GetSystemTime                          ,0xff814f64) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa88dec) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa8a978) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a9c0) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a978) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a9c0) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa88e34) //  1 94%
//NHSTUB(Remove                               ,0xff8c2f9c) //  3 52%
//NHSTUB(WriteSDCard                          ,0xff87e7f4) //  1 93%    *** != 0xff87e9cc
// ALT: NHSTUB(WriteSDCard, 0xff87e9cc) // 1 29/2
NHSTUB(add_ptp_handler                        ,0xffa3d17c) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffad6680
NHSTUB(kbd_pwr_on                             ,0xff82879c) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff922fa4) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff922fd0) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff92310c) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa749dc) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74a08) // 1 5/4
NHSTUB(malloc                                 ,0xffad6674) //  1 53%
NHSTUB(taskIdListGet                          ,0xffae42b8) //  1 82%
NHSTUB(localtime                              ,0xffacddc8) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86ea3c) //  1 90%
NHSTUB(MakeAFScan                             ,0xff94ef28) //  1 89%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff960434 -> ff960434
// Strange mode 0x0001000f in firmware, found in modemap as 15 (MODE_VIDEO_STD)
// Strange mode 0x00010010 in firmware but not in current modemap
// Strange mode 0x00010011 in firmware but not in current modemap
// Strange mode 0x00010012 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9595d4) // Found @0xff9595d4,          stubs_min = 0xff9595d4 (0xFF9595D4)
//DEF(FlashParamsTable                        ,0xff962698) // Found @0xff962698,          stubs_min = 0xff962698 (0xFF962698)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xff964d44

// Misc stuff
// LED table init @ 0xff82dfa4
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffaeaef0, canon_data_len: 0xea00

// For capt_seq.c
DEF(_nrflag,0x6db4) // Found @ ff950d10 (0x6db4)
//static long *nrflag = (long*)(0x6db4);       // Found @ ff950d10

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814d2c) //  1
NHSTUB(Close                                  ,0xff86f788) //120
NHSTUB(CreateTask                             ,0xff822274) //120
NHSTUB(DebugAssert                            ,0xff813bfc) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86866c) //  1
NHSTUB(DoAELock                               ,0xff94ac14) //120
NHSTUB(DoAFLock                               ,0xff94aacc) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816c44) //  1
NHSTUB(ExitTask                               ,0xff822634) //120
NHSTUB(Fclose_Fut                             ,0xff8687ac) //120
NHSTUB(Feof_Fut                               ,0xff8689c0) //  1
NHSTUB(Fflush_Fut                             ,0xff8689f8) //  1
NHSTUB(Fgets_Fut                              ,0xff868930) //  1
NHSTUB(Fopen_Fut                              ,0xff868770) //120
NHSTUB(Fread_Fut                              ,0xff868890) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814d60) //  1
NHSTUB(Fseek_Fut                              ,0xff868978) //120
NHSTUB(Fwrite_Fut                             ,0xff8688e0) //120
NHSTUB(GetBatteryTemperature                  ,0xff82d5ac) //102
NHSTUB(GetCCDTemperature                      ,0xff82d598) //102
NHSTUB(GetCurrentAvValue                      ,0xffa88c68) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86ef64) //119
NHSTUB(GetDrive_FreeClusters                  ,0xff86efdc) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xff86efa0) //119
NHSTUB(GetOpticalTemperature                  ,0xff82d584) //120
NHSTUB(GetParameterData                       ,0xff964cd8) //  1
NHSTUB(GetPropertyCase                        ,0xff825530) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffa6f178) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa6f18c) //102
NHSTUB(GiveSemaphore                          ,0xff821c78) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8fe628) //  1
NHSTUB(LEDDrive                               ,0xff82db04) //120
NHSTUB(LocalTime                              ,0xff814284) //115
NHSTUB(LockMainPower                          ,0xff9601ac) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8686f8) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa8b004) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6f058) //120
NHSTUB(Open                                   ,0xff86f760) //120
NHSTUB(PT_PlaySound                           ,0xff957a90) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff95c1f4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff95c280) //120
NHSTUB(Read                                   ,0xff86f81c) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff975860) //120
NHSTUB(RenameFile_Fut                         ,0xff8685ec) //  1
NHSTUB(Restart                                ,0xff823ac0) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa8e0b8) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9600a4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff98ca70) //120
NHSTUB(SetFileAttributes                      ,0xff86f974) //  1
NHSTUB(SetLogicalEventActive                  ,0xff95e250) //1104
NHSTUB(SetParameterData                       ,0xff964bf8) //  1
NHSTUB(SetPropertyCase                        ,0xff825414) //  1
//NHSTUB(SetScriptMode                        ,0xff95e2b4) //120            == 0xff95e2b4
NHSTUB(SleepTask                              ,0xff8220d4) //120
NHSTUB(TakeSemaphore                          ,0xff821a90) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a2d8c) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a2d60) //  1
NHSTUB(TurnOnDisplay                          ,0xff922e3c) //120
NHSTUB(TurnOffDisplay                         ,0xff922e4c) //120
NHSTUB(UnlockAE                               ,0xff94ac34) //120
NHSTUB(UnlockAF                               ,0xff94ab0c) //120
NHSTUB(UnlockMainPower                        ,0xff960260) //120
NHSTUB(UnsetZoomForMovie                      ,0xff99764c) //  1
NHSTUB(UpdateMBROnFlash                       ,0xff86ec9c) //  1
//NHSTUB(VbattGet                             ,0xff82c54c) //120            == 0xff82c54c
NHSTUB(Write                                  ,0xff86f828) //120
NHSTUB(_log                                   ,0xffabfbb4) //121
NHSTUB(_log10                                 ,0xffac025c) //121
NHSTUB(_pow                                   ,0xffac074c) //121
NHSTUB(_sqrt                                  ,0xffac4a98) //  1
NHSTUB(apex2us                                ,0xff8ac734) //  1
NHSTUB(close                                  ,0xffad3634) //109
NHSTUB(exmem_alloc                            ,0xff81295c) //  1
NHSTUB(kbd_p1_f                               ,0xff82752c) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff827538) //109
NHSTUB(kbd_p2_f                               ,0xff827910) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff828320) //  1
NHSTUB(kbd_pwr_off                            ,0xff828888) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xff8288a4) // 1 6/0
NHSTUB(lseek                                  ,0xffad3778) //  1
NHSTUB(memcmp                                 ,0xffacd1a8) //120
NHSTUB(memcpy                                 ,0xffacd1e4) //120
NHSTUB(memset                                 ,0xffacd25c) //120
NHSTUB(mkdir                                  ,0xff86f9a4) //  1
NHSTUB(open                                   ,0xffad3c78) //109
NHSTUB(closedir                               ,0xffacf5d4) //  1
NHSTUB(qsort                                  ,0xffacca08) //  1
NHSTUB(rand                                   ,0xffacca2c) //  1
NHSTUB(realloc                                ,0xffab7ce8) //115
NHSTUB(srand                                  ,0xffacca50) //  1
NHSTUB(stat                                   ,0xffacf69c) //  1
NHSTUB(strcat                                 ,0xffacd27c) //  1
NHSTUB(strchr                                 ,0xffacd2a8) //  1
NHSTUB(strcmp                                 ,0xffacd2cc) //120
NHSTUB(strcpy                                 ,0xffacd460) //120
NHSTUB(strftime                               ,0xffaceae8) //  1
NHSTUB(strlen                                 ,0xffacd5c4) //120
NHSTUB(strncmp                                ,0xffacd628) //  1
NHSTUB(strncpy                                ,0xffacd66c) //  1
NHSTUB(strrchr                                ,0xffacd6f0) //  1
NHSTUB(strtol                                 ,0xffacce44) //  1
NHSTUB(isdigit                                ,0xffac9578) //  1
NHSTUB(isspace                                ,0xffac95f0) //  1
NHSTUB(isalpha                                ,0xffac9548) //  1
NHSTUB(isupper                                ,0xffac9608) //  1
NHSTUB(islower                                ,0xffac95a8) //  1
NHSTUB(ispunct                                ,0xffac95d8) //  1
NHSTUB(isxdigit                               ,0xffac9620) //  1
NHSTUB(toupper                                ,0xffac9648) //  1
NHSTUB(tolower                                ,0xffac9638) //  1
NHSTUB(taskLock                               ,0xffae4974) //  1
NHSTUB(taskUnlock                             ,0xffae4a1c) //  1
NHSTUB(taskName                               ,0xffae41b0) //  1
NHSTUB(errnoOfTaskGet                         ,0xffacfda0) //  1
NHSTUB(readdir                                ,0xffacf5a0) //  1
NHSTUB(strtoul                                ,0xffaccfec) //  1
NHSTUB(strpbrk                                ,0xffacd6b4) //  1
NHSTUB(utime                                  ,0xffacf730) //  1
NHSTUB(mktime                                 ,0xffacdf90) //  1
NHSTUB(opendir                                ,0xffacf608) //  1
NHSTUB(memchr                                 ,0xffacd174) //  1
NHSTUB(memPartInfoGet                         ,0xffad6a94) //  1
NHSTUB(iosDrvInstall                          ,0xffad4b18) //  1
NHSTUB(iosDevAdd                              ,0xffad4854) //  1
NHSTUB(iosDevDelete                           ,0xffad482c) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa8ad74) //  1
NHSTUB(taskCreateHookAdd                      ,0xffad9cf4) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffad9c30) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86eb44) //  1
NHSTUB(taskSuspend                            ,0xffae43c0) //  1
NHSTUB(taskResume                             ,0xffae4594) //  1
NHSTUB(time                                   ,0xffaceb14) //  1
NHSTUB(vsprintf                               ,0xffad0ef4) //115
NHSTUB(EngDrvRead                             ,0xff880c7c) //102
