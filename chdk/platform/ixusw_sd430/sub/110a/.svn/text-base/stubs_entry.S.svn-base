// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.10A   // Found @ 0xff81ccbc, "GM1.10A" @ 0xff81ccc9
//   Firmware build timestamp: Apr 24 2006 17:03:09
//   Canon DIGITAL IXUS WIRELESS

// Values for makefile.inc
//   PLATFORMID = 12529 (0x30f1) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000c5d80

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(EnterToCompensationEVF               ,0xff951ab0) //  1 87%        == 0xff951ab0
NHSTUB(ExitFromCompensationEVF                ,0xff95324c) //  2 90%
//NHSTUB(GetDrive_FreeClusters                ,0xff872a08) //1103        *** != 0xff86b75c
NHSTUB(GetFocusLensSubjectDistance            ,0xffb751d8) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffb75778) //  3 92%
NHSTUB(GetParameterData                       ,0xff96a31c) //  1 96%
NHSTUB(GetSystemTime                          ,0xff81761c) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffb7ff84) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffb81b10) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb81b58) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb81b10) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb81b58) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffb7ffcc) //  1 94%
//NHSTUB(Remove                               ,0xff8c6fc4) //  3 52%
//NHSTUB(Restart                              ,0xff8252a4) //  1 96%    *** != 0xff8252a0
//NHSTUB(SetParameterData                     ,0xff96a23c) //  1 96%        == 0xff96a23c
NHSTUB(UnsetZoomForMovie                      ,0xff9a7ce0) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffa62090) //  1 96%
NHSTUB(exmem_alloc                            ,0xff814f44) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffc1d8f8
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0xff82aaac
//NHSTUB(kbd_pwr_off                          ,0xff82b05c) //  1 83%    *** != 0xff82b078
// ALT: NHSTUB(kbd_pwr_off, 0xff82b078) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82c050) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82c06c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82b078) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82bcf8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82bd14) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82be00) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82be1c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82beec) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82bf08) // 3 5/1
//NHSTUB(kbd_pwr_on                           ,0xff82af70) //  1 55%    *** != 0xff82b05c
// ALT: NHSTUB(kbd_pwr_on, 0xff927840) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffb6b760) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffb6b78c) // 1 5/4
NHSTUB(malloc                                 ,0xffc1d8ec) //  1 53%
NHSTUB(taskIdListGet                          ,0xffc2c248) //  1 82%
NHSTUB(localtime                              ,0xffc15040) //  1 93%
//NHSTUB(Mount_FileSystem                     ,0xff8724d0) //  1 90%        == 0xff8724d0
NHSTUB(MakeAFScan                             ,0xff9542fc) //  1 96%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff965810 -> ff965810
// Mode 1 in firmware but not in current modemap
// Mode 4 in firmware but not in current modemap
// Strange mode 0x0001000e in firmware, found in modemap as 14 (MODE_VIDEO_STD)
// Strange mode 0x0001000f in firmware but not in current modemap
// Strange mode 0x00010010 in firmware but not in current modemap
// Strange mode 0x00010011 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff95ec74) // Found @0xff95ec74,          stubs_min = 0xff95ec74 (0xff95ec74)
//DEF(FlashParamsTable                        ,0xff967a54) // Found @0xff967a54, ** != ** stubs_min = 0xff9670d0 (0xff9670d0)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x63; }                          // Found @0xff96a388

// Misc stuff
// LED table init @ 0xff830bf4
// LED #1: 0xc0220088, offset 0x344
// LED #2: 0xc0220018, offset 0x4
// LED #3: 0xc022001c, offset 0x44
// LED #4: 0xc02200b0, offset 0x84
// LED #5: 0xc02200b8, offset 0xc4
// LED #6: 0xc02200b4, offset 0x204
// LED #7: 0xc02200bc, offset 0x244

// canon_data_src: 0xffc33020, canon_data_len: 0x17370

// For capt_seq.c
DEF(_nrflag,0x6fe0) // Found @ ff956104 (0x6fe0)
//static long *nrflag = (long*)(0x6fe0);       // Found @ ff956104

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8173e4) //  1
NHSTUB(Close                                  ,0xff8731a4) //120
NHSTUB(CreateTask                             ,0xff823d64) //120
NHSTUB(DebugAssert                            ,0xff8162b4) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86c394) //  1
NHSTUB(DoAELock                               ,0xff94fb28) //120
//NHSTUB(DoAFLock                             ,0xff94f9b8) //120            == 0xff94f9b8
NHSTUB(ExecuteEventProcedure                  ,0xff8192fc) //  1
NHSTUB(ExitTask                               ,0xff824124) //120
NHSTUB(Fclose_Fut                             ,0xff86c4d4) //120
NHSTUB(Feof_Fut                               ,0xff86c6e8) //  1
NHSTUB(Fflush_Fut                             ,0xff86c720) //  1
NHSTUB(Fgets_Fut                              ,0xff86c658) //  1
NHSTUB(Fopen_Fut                              ,0xff86c498) //120
NHSTUB(Fread_Fut                              ,0xff86c5b8) //120
NHSTUB(FreeUncacheableMemory                  ,0xff817418) //  1
NHSTUB(Fseek_Fut                              ,0xff86c6a0) //120
NHSTUB(Fwrite_Fut                             ,0xff86c608) //120
NHSTUB(GetBatteryTemperature                  ,0xff8300c4) //102
NHSTUB(GetCCDTemperature                      ,0xff8300b0) //102
NHSTUB(GetCurrentAvValue                      ,0xffb7fe00) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff872990) //119            == 0xff872990
//NHSTUB(GetDrive_TotalClusters               ,0xff8729cc) //119            == 0xff8729cc
NHSTUB(GetOpticalTemperature                  ,0xff83009c) //120
NHSTUB(GetPropertyCase                        ,0xff827c9c) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffb66078) //120
//NHSTUB(GetZoomLensCurrentPosition           ,0xffb6608c) //102            == 0xffb6608c
//NHSTUB(GiveSemaphore                        ,0xff82395c) //120            == 0xff82395c
NHSTUB(IsStrobeChargeCompleted                ,0xff902ca0) //  1
NHSTUB(LEDDrive                               ,0xff830658) //120
NHSTUB(LocalTime                              ,0xff81693c) //115
NHSTUB(LockMainPower                          ,0xff965588) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86c420) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffb8219c) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffb65f58) //120
NHSTUB(Open                                   ,0xff87317c) //120
NHSTUB(PT_PlaySound                           ,0xff95d118) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff9615f8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff961684) //120
NHSTUB(Read                                   ,0xff873238) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff9846d8) //120
NHSTUB(RenameFile_Fut                         ,0xff86c314) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffb85250) //102
NHSTUB(SetAutoShutdownTime                    ,0xff965480) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff99caf0) //120
NHSTUB(SetFileAttributes                      ,0xff87335c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff963624) //1104
NHSTUB(SetPropertyCase                        ,0xff827b80) //  1
//NHSTUB(SetScriptMode                        ,0xff96368c) //120            == 0xff96368c
NHSTUB(SleepTask                              ,0xff823c78) //120
NHSTUB(TakeSemaphore                          ,0xff823774) //1101
NHSTUB(TurnOffBackLight                       ,0xff9b3df4) //  1
NHSTUB(TurnOnBackLight                        ,0xff9b3dc8) //  1
NHSTUB(TurnOnDisplay                          ,0xff927490) //120
NHSTUB(TurnOffDisplay                         ,0xff9274a0) //120
NHSTUB(UnlockAE                               ,0xff94fb48) //120
//NHSTUB(UnlockAF                             ,0xff94fa20) //120            == 0xff94fa20
NHSTUB(UnlockMainPower                        ,0xff96563c) //120
NHSTUB(UpdateMBROnFlash                       ,0xff8726c8) //  1
//NHSTUB(VbattGet                             ,0xff82f0f4) //120            == 0xff82f0f4
NHSTUB(Write                                  ,0xff873244) //120
NHSTUB(WriteSDCard                            ,0xff881a84) //  1
NHSTUB(_log                                   ,0xffac932c) //111
NHSTUB(_log10                                 ,0xffbb98c0) //121
NHSTUB(_pow                                   ,0xffbb9db0) //121
NHSTUB(_sqrt                                  ,0xffacb378) //  1
// ALT: NHSTUB(_sqrt, 0xffbbe0fc) // 1 24/0
NHSTUB(apex2us                                ,0xff8b02a8) //  1
NHSTUB(close                                  ,0xffc1a8ac) //109
//NHSTUB(kbd_p1_f                             ,0xff829c94) //  1            == 0xff829c94
//NHSTUB(kbd_p1_f_cont                        ,0xff829ca0) //109            == 0xff829ca0
//NHSTUB(kbd_p2_f                             ,0xff82a078) //  1            == 0xff82a078
NHSTUB(lseek                                  ,0xffc1a9f0) //  1
NHSTUB(memcmp                                 ,0xffc14420) //120
NHSTUB(memcpy                                 ,0xffc1445c) //120
NHSTUB(memset                                 ,0xffc144d4) //120
NHSTUB(mkdir                                  ,0xff87338c) //  1
NHSTUB(open                                   ,0xffc1aef0) //109
NHSTUB(closedir                               ,0xffc1684c) //  1
NHSTUB(qsort                                  ,0xffc13c80) //  1
NHSTUB(rand                                   ,0xffc13ca4) //  1
NHSTUB(realloc                                ,0xffbb0c18) //115
NHSTUB(srand                                  ,0xffc13cc8) //  1
NHSTUB(stat                                   ,0xffc16914) //  1
NHSTUB(strcat                                 ,0xffc144f4) //  1
NHSTUB(strchr                                 ,0xffc14520) //  1
NHSTUB(strcmp                                 ,0xffc14544) //120
NHSTUB(strcpy                                 ,0xffc146d8) //120
NHSTUB(strftime                               ,0xffc15d60) //  1
NHSTUB(strlen                                 ,0xffc1483c) //120
NHSTUB(strncmp                                ,0xffc148a0) //  1
NHSTUB(strncpy                                ,0xffc148e4) //  1
NHSTUB(strrchr                                ,0xffc14968) //  1
NHSTUB(strtol                                 ,0xffc140bc) //  1
NHSTUB(isdigit                                ,0xffc107f0) //  1
NHSTUB(isspace                                ,0xffc10868) //  1
NHSTUB(isalpha                                ,0xffc107c0) //  1
NHSTUB(isupper                                ,0xffc10880) //  1
NHSTUB(islower                                ,0xffc10820) //  1
NHSTUB(ispunct                                ,0xffc10850) //  1
NHSTUB(isxdigit                               ,0xffc10898) //  1
NHSTUB(toupper                                ,0xffc108c0) //  1
NHSTUB(tolower                                ,0xffc108b0) //  1
NHSTUB(taskLock                               ,0xffc2c904) //  1
NHSTUB(taskUnlock                             ,0xffc2c9ac) //  1
NHSTUB(taskName                               ,0xffc2c140) //  1
NHSTUB(errnoOfTaskGet                         ,0xffc17018) //  1
NHSTUB(readdir                                ,0xffc16818) //  1
NHSTUB(strtoul                                ,0xffc14264) //  1
NHSTUB(strpbrk                                ,0xffc1492c) //  1
NHSTUB(utime                                  ,0xffc169a8) //  1
NHSTUB(mktime                                 ,0xffc15208) //  1
NHSTUB(opendir                                ,0xffc16880) //  1
NHSTUB(memchr                                 ,0xffc143ec) //  1
NHSTUB(memPartInfoGet                         ,0xffc1dd0c) //  1
NHSTUB(iosDrvInstall                          ,0xffc1bd90) //  1
NHSTUB(iosDevAdd                              ,0xffc1bacc) //  1
NHSTUB(iosDevDelete                           ,0xffc1baa4) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffb81f0c) //  1
NHSTUB(taskCreateHookAdd                      ,0xffc2154c) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffc21488) //  1
NHSTUB(Unmount_FileSystem                     ,0xff872574) //  1
NHSTUB(taskSuspend                            ,0xffc2c350) //  1
NHSTUB(taskResume                             ,0xffc2c524) //  1
NHSTUB(time                                   ,0xffc15d8c) //  1
NHSTUB(vsprintf                               ,0xffc1816c) //115
NHSTUB(EngDrvRead                             ,0xff883d10) //102
