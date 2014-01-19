// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00H   // Found @ 0xff81add0, "GM1.00H" @ 0xff81addd
//   Firmware build timestamp: Dec 19 2005 19:48:21
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 4.00MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009f5b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(EnterToCompensationEVF               ,0xff94ccb0) //  1 64%    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff94cd7c) //  1 73%    *** != 0x00000000
NHSTUB(GetFocusLensSubjectDistance            ,0xffa7e77c) //  1 90%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa7ed1c) //  3 52%
NHSTUB(GetSystemTime                          ,0xff814f64) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa89174) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa8ad00) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8ad48) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8ad00) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8ad48) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa891bc) //  1 94%
//NHSTUB(Remove                               ,0xff8c3324) //  3 52%
//NHSTUB(WriteSDCard                          ,0xff87eb7c) //  1 93%    *** != 0xff87ed54
// ALT: NHSTUB(WriteSDCard, 0xff87ed54) // 1 29/2
NHSTUB(add_ptp_handler                        ,0xffa3d504) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffad6a08
NHSTUB(kbd_pwr_on                             ,0xff82879c) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff92332c) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff923358) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff923494) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74d64) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74d90) // 1 5/4
NHSTUB(malloc                                 ,0xffad69fc) //  1 53%
NHSTUB(taskIdListGet                          ,0xffae4640) //  1 82%
NHSTUB(localtime                              ,0xfface150) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86edc4) //  1 90%
NHSTUB(MakeAFScan                             ,0xff94f2b0) //  1 89%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff9607bc -> ff9607bc
// Strange mode 0x0001000f in firmware, found in modemap as 15 (MODE_VIDEO_STD)
// Strange mode 0x00010010 in firmware but not in current modemap
// Strange mode 0x00010011 in firmware but not in current modemap
// Strange mode 0x00010012 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff95995c) // Found @0xff95995c,          stubs_min = 0xff95995c (0xFF95995C)
//DEF(FlashParamsTable                        ,0xff962a20) // Found @0xff962a20,          stubs_min = 0xff962a20 (0xFF962A20)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xff9650cc

// Misc stuff
// LED table init @ 0xff82dfa4
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffaeb280, canon_data_len: 0xea00

// For capt_seq.c
DEF(_nrflag,0x6db4) // Found @ ff951098 (0x6db4)
//static long *nrflag = (long*)(0x6db4);       // Found @ ff951098

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814d2c) //  1
NHSTUB(Close                                  ,0xff86fb10) //120
NHSTUB(CreateTask                             ,0xff822274) //120
NHSTUB(DebugAssert                            ,0xff813bfc) //1100
NHSTUB(DeleteFile_Fut                         ,0xff8689f4) //  1
NHSTUB(DoAELock                               ,0xff94af9c) //120
NHSTUB(DoAFLock                               ,0xff94ae54) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816c44) //  1
NHSTUB(ExitTask                               ,0xff822634) //120
NHSTUB(Fclose_Fut                             ,0xff868b34) //120
NHSTUB(Feof_Fut                               ,0xff868d48) //  1
NHSTUB(Fflush_Fut                             ,0xff868d80) //  1
NHSTUB(Fgets_Fut                              ,0xff868cb8) //  1
NHSTUB(Fopen_Fut                              ,0xff868af8) //120
NHSTUB(Fread_Fut                              ,0xff868c18) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814d60) //  1
NHSTUB(Fseek_Fut                              ,0xff868d00) //120
NHSTUB(Fwrite_Fut                             ,0xff868c68) //120
NHSTUB(GetBatteryTemperature                  ,0xff82d5ac) //102
NHSTUB(GetCCDTemperature                      ,0xff82d598) //102
NHSTUB(GetCurrentAvValue                      ,0xffa88ff0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86f2ec) //119
NHSTUB(GetDrive_FreeClusters                  ,0xff86f364) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xff86f328) //119
NHSTUB(GetOpticalTemperature                  ,0xff82d584) //120
NHSTUB(GetParameterData                       ,0xff965060) //  1
NHSTUB(GetPropertyCase                        ,0xff825530) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffa6f500) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa6f514) //102
NHSTUB(GiveSemaphore                          ,0xff821c78) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8fe9b0) //  1
NHSTUB(LEDDrive                               ,0xff82db04) //120
NHSTUB(LocalTime                              ,0xff814284) //115
NHSTUB(LockMainPower                          ,0xff960534) //120
NHSTUB(MakeDirectory_Fut                      ,0xff868a80) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa8b38c) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6f3e0) //120
NHSTUB(Open                                   ,0xff86fae8) //120
NHSTUB(PT_PlaySound                           ,0xff957e18) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff95c57c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff95c608) //120
NHSTUB(Read                                   ,0xff86fba4) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff975be8) //120
NHSTUB(RenameFile_Fut                         ,0xff868974) //  1
NHSTUB(Restart                                ,0xff823ac0) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa8e440) //102
NHSTUB(SetAutoShutdownTime                    ,0xff96042c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff98cdf8) //120
NHSTUB(SetFileAttributes                      ,0xff86fcfc) //  1
NHSTUB(SetLogicalEventActive                  ,0xff95e5d8) //1104
NHSTUB(SetParameterData                       ,0xff964f80) //  1
NHSTUB(SetPropertyCase                        ,0xff825414) //  1
//NHSTUB(SetScriptMode                        ,0xff95e63c) //120            == 0xff95e63c
NHSTUB(SleepTask                              ,0xff8220d4) //120
NHSTUB(TakeSemaphore                          ,0xff821a90) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a3114) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a30e8) //  1
NHSTUB(TurnOnDisplay                          ,0xff9231c4) //120
NHSTUB(TurnOffDisplay                         ,0xff9231d4) //120
NHSTUB(UnlockAE                               ,0xff94afbc) //120
NHSTUB(UnlockAF                               ,0xff94ae94) //120
NHSTUB(UnlockMainPower                        ,0xff9605e8) //120
NHSTUB(UnsetZoomForMovie                      ,0xff9979d4) //  1
NHSTUB(UpdateMBROnFlash                       ,0xff86f024) //  1
//NHSTUB(VbattGet                             ,0xff82c54c) //120            == 0xff82c54c
NHSTUB(Write                                  ,0xff86fbb0) //120
NHSTUB(_log                                   ,0xffabff3c) //121
NHSTUB(_log10                                 ,0xffac05e4) //121
NHSTUB(_pow                                   ,0xffac0ad4) //121
NHSTUB(_sqrt                                  ,0xffac4e20) //  1
NHSTUB(apex2us                                ,0xff8acabc) //  1
NHSTUB(close                                  ,0xffad39bc) //109
NHSTUB(exmem_alloc                            ,0xff81295c) //  1
NHSTUB(kbd_p1_f                               ,0xff82752c) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff827538) //109
NHSTUB(kbd_p2_f                               ,0xff827910) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff828320) //  1
NHSTUB(kbd_pwr_off                            ,0xff828888) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xff8288a4) // 1 6/0
NHSTUB(lseek                                  ,0xffad3b00) //  1
NHSTUB(memcmp                                 ,0xffacd530) //120
NHSTUB(memcpy                                 ,0xffacd56c) //120
NHSTUB(memset                                 ,0xffacd5e4) //120
NHSTUB(mkdir                                  ,0xff86fd2c) //  1
NHSTUB(open                                   ,0xffad4000) //109
NHSTUB(closedir                               ,0xffacf95c) //  1
NHSTUB(qsort                                  ,0xffaccd90) //  1
NHSTUB(rand                                   ,0xffaccdb4) //  1
NHSTUB(realloc                                ,0xffab8070) //115
NHSTUB(srand                                  ,0xffaccdd8) //  1
NHSTUB(stat                                   ,0xffacfa24) //  1
NHSTUB(strcat                                 ,0xffacd604) //  1
NHSTUB(strchr                                 ,0xffacd630) //  1
NHSTUB(strcmp                                 ,0xffacd654) //120
NHSTUB(strcpy                                 ,0xffacd7e8) //120
NHSTUB(strftime                               ,0xffacee70) //  1
NHSTUB(strlen                                 ,0xffacd94c) //120
NHSTUB(strncmp                                ,0xffacd9b0) //  1
NHSTUB(strncpy                                ,0xffacd9f4) //  1
NHSTUB(strrchr                                ,0xffacda78) //  1
NHSTUB(strtol                                 ,0xffacd1cc) //  1
NHSTUB(isdigit                                ,0xffac9900) //  1
NHSTUB(isspace                                ,0xffac9978) //  1
NHSTUB(isalpha                                ,0xffac98d0) //  1
NHSTUB(isupper                                ,0xffac9990) //  1
NHSTUB(islower                                ,0xffac9930) //  1
NHSTUB(ispunct                                ,0xffac9960) //  1
NHSTUB(isxdigit                               ,0xffac99a8) //  1
NHSTUB(toupper                                ,0xffac99d0) //  1
NHSTUB(tolower                                ,0xffac99c0) //  1
NHSTUB(taskLock                               ,0xffae4cfc) //  1
NHSTUB(taskUnlock                             ,0xffae4da4) //  1
NHSTUB(taskName                               ,0xffae4538) //  1
NHSTUB(errnoOfTaskGet                         ,0xffad0128) //  1
NHSTUB(readdir                                ,0xffacf928) //  1
NHSTUB(strtoul                                ,0xffacd374) //  1
NHSTUB(strpbrk                                ,0xffacda3c) //  1
NHSTUB(utime                                  ,0xffacfab8) //  1
NHSTUB(mktime                                 ,0xfface318) //  1
NHSTUB(opendir                                ,0xffacf990) //  1
NHSTUB(memchr                                 ,0xffacd4fc) //  1
NHSTUB(memPartInfoGet                         ,0xffad6e1c) //  1
NHSTUB(iosDrvInstall                          ,0xffad4ea0) //  1
NHSTUB(iosDevAdd                              ,0xffad4bdc) //  1
NHSTUB(iosDevDelete                           ,0xffad4bb4) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa8b0fc) //  1
NHSTUB(taskCreateHookAdd                      ,0xffada07c) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffad9fb8) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86eecc) //  1
NHSTUB(taskSuspend                            ,0xffae4748) //  1
NHSTUB(taskResume                             ,0xffae491c) //  1
NHSTUB(time                                   ,0xffacee9c) //  1
NHSTUB(vsprintf                               ,0xffad127c) //115
NHSTUB(EngDrvRead                             ,0xff881004) //102
