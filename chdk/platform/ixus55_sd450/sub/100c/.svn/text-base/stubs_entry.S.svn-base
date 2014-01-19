// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00C   // Found @ 0xff81a484, "GM1.00C" @ 0xff81a491
//   Firmware build timestamp: Oct  7 2005 15:41:49
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 4.00MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a87d0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xff94c024) //  1 64%
//NHSTUB(ExitFromCompensationEVF              ,0xff94c0f0) //  1 73%    *** != 0xff94c084
NHSTUB(GetFocusLensSubjectDistance            ,0xffa7ddec) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa7e38c) //  3 92%
NHSTUB(GetSystemTime                          ,0xff814de8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa88aa4) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa8a630) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a678) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a630) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a678) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa88aec) //  1 94%
//NHSTUB(Remove                               ,0xff8c209c) //  3 52%
NHSTUB(UnsetZoomForMovie                      ,0xff996b94) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffa3d19c) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffad6aa4
NHSTUB(kbd_pwr_off                            ,0xff8277c8) //  1 83%
// ALT: NHSTUB(kbd_pwr_off, 0xff8277e4) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8287ac) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8287c8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8277e4) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828454) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828470) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82855c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828578) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828648) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828664) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xff8276dc) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff922694) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff9226c0) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff9227fc) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74374) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa743a0) // 1 5/4
NHSTUB(malloc                                 ,0xffad6a98) //  1 53%
NHSTUB(taskIdListGet                          ,0xffae46dc) //  1 82%
NHSTUB(localtime                              ,0xfface1ec) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86d574) //  1 90%
NHSTUB(MakeAFScan                             ,0xff94e624) //  1 96%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff95fb94 -> ff95fb94
// Mode 7 in firmware but not in current modemap
// Mode 9 in firmware but not in current modemap
// Mode 10 in firmware but not in current modemap
// Mode 11 in firmware but not in current modemap
// Mode 13 in firmware but not in current modemap
// Mode 14 in firmware but not in current modemap
// Strange mode 0x0001000f in firmware, found in modemap as 15 (MODE_VIDEO_STD)
// Strange mode 0x00010010 in firmware but not in current modemap
// Strange mode 0x00010011 in firmware but not in current modemap
// Strange mode 0x00010012 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff958d10) // Found @0xff958d10,          stubs_min = 0xff958d10 (0xFF958D10)
//DEF(FlashParamsTable                        ,0xff961df8) // Found @0xff961df8,          stubs_min = 0xff961df8 (0xFF961DF8)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xff9644b4

// Misc stuff
// LED table init @ 0xff82d0cc
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffaeb320, canon_data_len: 0xea00

// For capt_seq.c
DEF(_nrflag,0x6d6c) // Found @ ff950430 (0x6d6c)
//static long *nrflag = (long*)(0x6d6c);       // Found @ ff950430

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814bb0) //  1
NHSTUB(Close                                  ,0xff86e2c0) //120
NHSTUB(CreateTask                             ,0xff821508) //120
NHSTUB(DebugAssert                            ,0xff813a80) //1100
NHSTUB(DeleteFile_Fut                         ,0xff867774) //  1
NHSTUB(DoAELock                               ,0xff94a318) //120
NHSTUB(DoAFLock                               ,0xff94a1d0) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816ac8) //  1
NHSTUB(ExitTask                               ,0xff8218c8) //120
NHSTUB(Fclose_Fut                             ,0xff8678b4) //120
NHSTUB(Feof_Fut                               ,0xff867ac8) //  1
NHSTUB(Fflush_Fut                             ,0xff867b00) //  1
NHSTUB(Fgets_Fut                              ,0xff867a38) //  1
NHSTUB(Fopen_Fut                              ,0xff867878) //120
NHSTUB(Fread_Fut                              ,0xff867998) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814be4) //  1
NHSTUB(Fseek_Fut                              ,0xff867a80) //120
NHSTUB(Fwrite_Fut                             ,0xff8679e8) //120
NHSTUB(GetBatteryTemperature                  ,0xff82c6d4) //102
NHSTUB(GetCCDTemperature                      ,0xff82c6c0) //102
NHSTUB(GetCurrentAvValue                      ,0xffa88920) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86da9c) //119
NHSTUB(GetDrive_FreeClusters                  ,0xff86db14) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xff86dad8) //119
NHSTUB(GetOpticalTemperature                  ,0xff82c6ac) //120
NHSTUB(GetParameterData                       ,0xff964448) //  1
NHSTUB(GetPropertyCase                        ,0xff82447c) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffa6ec8c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa6eca0) //102
NHSTUB(GiveSemaphore                          ,0xff821100) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8fdd38) //  1
NHSTUB(LEDDrive                               ,0xff82cc2c) //120
NHSTUB(LocalTime                              ,0xff814108) //115
NHSTUB(LockMainPower                          ,0xff95f90c) //120
NHSTUB(MakeDirectory_Fut                      ,0xff867800) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa8acbc) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6eb6c) //120
NHSTUB(Open                                   ,0xff86e298) //120
NHSTUB(PT_PlaySound                           ,0xff9571cc) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff95b954) //120
NHSTUB(PostLogicalEventToUI                   ,0xff95b9e0) //120
NHSTUB(Read                                   ,0xff86e354) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff974dfc) //120
NHSTUB(RenameFile_Fut                         ,0xff8676f4) //  1
NHSTUB(Restart                                ,0xff822ab8) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa8dd70) //102
NHSTUB(SetAutoShutdownTime                    ,0xff95f804) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff98c010) //120
NHSTUB(SetFileAttributes                      ,0xff86e478) //  1
NHSTUB(SetLogicalEventActive                  ,0xff95d9b0) //1104
NHSTUB(SetParameterData                       ,0xff964368) //  1
NHSTUB(SetPropertyCase                        ,0xff824360) //  1
//NHSTUB(SetScriptMode                        ,0xff95da14) //120            == 0xff95da14
NHSTUB(SleepTask                              ,0xff82141c) //120
NHSTUB(TakeSemaphore                          ,0xff820f18) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a23e4) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a23b8) //  1
NHSTUB(TurnOnDisplay                          ,0xff92252c) //120
NHSTUB(TurnOffDisplay                         ,0xff92253c) //120
NHSTUB(UnlockAE                               ,0xff94a338) //120
NHSTUB(UnlockAF                               ,0xff94a210) //120
NHSTUB(UnlockMainPower                        ,0xff95f9c0) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86d7d4) //  1
//NHSTUB(VbattGet                             ,0xff82b704) //120            == 0xff82b704
NHSTUB(Write                                  ,0xff86e360) //120
NHSTUB(WriteSDCard                            ,0xff87cb8c) //  1
NHSTUB(_log                                   ,0xffabffd8) //121
NHSTUB(_log10                                 ,0xffac0680) //121
NHSTUB(_pow                                   ,0xffac0b70) //121
NHSTUB(_sqrt                                  ,0xffac4ebc) //  1
NHSTUB(apex2us                                ,0xff8ab374) //  1
NHSTUB(close                                  ,0xffad3a58) //109
NHSTUB(exmem_alloc                            ,0xff8127e0) //  1
NHSTUB(kbd_p1_f                               ,0xff82647c) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826488) //109
NHSTUB(kbd_p2_f                               ,0xff826860) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff827260) //  1
NHSTUB(lseek                                  ,0xffad3b9c) //  1
NHSTUB(memcmp                                 ,0xffacd5cc) //120
NHSTUB(memcpy                                 ,0xffacd608) //120
NHSTUB(memset                                 ,0xffacd680) //120
NHSTUB(mkdir                                  ,0xff86e4a8) //  1
NHSTUB(open                                   ,0xffad409c) //109
NHSTUB(closedir                               ,0xffacf9f8) //  1
NHSTUB(qsort                                  ,0xffacce2c) //  1
NHSTUB(rand                                   ,0xffacce50) //  1
NHSTUB(realloc                                ,0xffab8110) //115
NHSTUB(srand                                  ,0xffacce74) //  1
NHSTUB(stat                                   ,0xffacfac0) //  1
NHSTUB(strcat                                 ,0xffacd6a0) //  1
NHSTUB(strchr                                 ,0xffacd6cc) //  1
NHSTUB(strcmp                                 ,0xffacd6f0) //120
NHSTUB(strcpy                                 ,0xffacd884) //120
NHSTUB(strftime                               ,0xffacef0c) //  1
NHSTUB(strlen                                 ,0xffacd9e8) //120
NHSTUB(strncmp                                ,0xffacda4c) //  1
NHSTUB(strncpy                                ,0xffacda90) //  1
NHSTUB(strrchr                                ,0xffacdb14) //  1
NHSTUB(strtol                                 ,0xffacd268) //  1
NHSTUB(isdigit                                ,0xffac999c) //  1
NHSTUB(isspace                                ,0xffac9a14) //  1
NHSTUB(isalpha                                ,0xffac996c) //  1
NHSTUB(isupper                                ,0xffac9a2c) //  1
NHSTUB(islower                                ,0xffac99cc) //  1
NHSTUB(ispunct                                ,0xffac99fc) //  1
NHSTUB(isxdigit                               ,0xffac9a44) //  1
NHSTUB(toupper                                ,0xffac9a6c) //  1
NHSTUB(tolower                                ,0xffac9a5c) //  1
NHSTUB(taskLock                               ,0xffae4d98) //  1
NHSTUB(taskUnlock                             ,0xffae4e40) //  1
NHSTUB(taskName                               ,0xffae45d4) //  1
NHSTUB(errnoOfTaskGet                         ,0xffad01c4) //  1
NHSTUB(readdir                                ,0xffacf9c4) //  1
NHSTUB(strtoul                                ,0xffacd410) //  1
NHSTUB(strpbrk                                ,0xffacdad8) //  1
NHSTUB(utime                                  ,0xffacfb54) //  1
NHSTUB(mktime                                 ,0xfface3b4) //  1
NHSTUB(opendir                                ,0xffacfa2c) //  1
NHSTUB(memchr                                 ,0xffacd598) //  1
NHSTUB(memPartInfoGet                         ,0xffad6eb8) //  1
NHSTUB(iosDrvInstall                          ,0xffad4f3c) //  1
NHSTUB(iosDevAdd                              ,0xffad4c78) //  1
NHSTUB(iosDevDelete                           ,0xffad4c50) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa8aa2c) //  1
NHSTUB(taskCreateHookAdd                      ,0xffada118) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffada054) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86d67c) //  1
NHSTUB(taskSuspend                            ,0xffae47e4) //  1
NHSTUB(taskResume                             ,0xffae49b8) //  1
NHSTUB(time                                   ,0xffacef38) //  1
NHSTUB(vsprintf                               ,0xffad1318) //115
NHSTUB(EngDrvRead                             ,0xff87edec) //102
