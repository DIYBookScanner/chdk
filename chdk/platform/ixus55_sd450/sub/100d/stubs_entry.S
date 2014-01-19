// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00D   // Found @ 0xff81a484, "GM1.00D" @ 0xff81a491
//   Firmware build timestamp: Dec 19 2005 19:46:17
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 2.91MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a87d0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xff94c3ac) //  1 64%
//NHSTUB(ExitFromCompensationEVF              ,0xff94c478) //  1 73%    *** != 0xff94c40c
NHSTUB(GetFocusLensSubjectDistance            ,0xffa7e174) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa7e714) //  3 92%
NHSTUB(GetSystemTime                          ,0xff814de8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa88e2c) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa8a9b8) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8aa00) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a9b8) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8aa00) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa88e74) //  1 94%
//NHSTUB(Remove                               ,0xff8c2424) //  3 52%
NHSTUB(UnsetZoomForMovie                      ,0xff996f1c) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffa3d524) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffad6e2c
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
// ALT: NHSTUB(kbd_pwr_on, 0xff922a1c) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff922a48) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff922b84) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa746fc) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74728) // 1 5/4
NHSTUB(malloc                                 ,0xffad6e20) //  1 53%
NHSTUB(taskIdListGet                          ,0xffae4a64) //  1 82%
NHSTUB(localtime                              ,0xfface574) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86d8fc) //  1 90%
NHSTUB(MakeAFScan                             ,0xff94e9ac) //  1 96%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff95ff1c -> ff95ff1c
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
//DEF(levent_table                            ,0xff959098) // Found @0xff959098,          stubs_min = 0xff959098 (0xFF959098)
//DEF(FlashParamsTable                        ,0xff962180) // Found @0xff962180,          stubs_min = 0xff962180 (0xFF962180)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xff96483c

// Misc stuff
// LED table init @ 0xff82d0cc
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffaeb6a0, canon_data_len: 0xea00

// For capt_seq.c
DEF(_nrflag,0x6d6c) // Found @ ff9507b8 (0x6d6c)
//static long *nrflag = (long*)(0x6d6c);       // Found @ ff9507b8

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814bb0) //  1
NHSTUB(Close                                  ,0xff86e648) //120
NHSTUB(CreateTask                             ,0xff821508) //120
NHSTUB(DebugAssert                            ,0xff813a80) //1100
NHSTUB(DeleteFile_Fut                         ,0xff867afc) //  1
NHSTUB(DoAELock                               ,0xff94a6a0) //120
NHSTUB(DoAFLock                               ,0xff94a558) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816ac8) //  1
NHSTUB(ExitTask                               ,0xff8218c8) //120
NHSTUB(Fclose_Fut                             ,0xff867c3c) //120
NHSTUB(Feof_Fut                               ,0xff867e50) //  1
NHSTUB(Fflush_Fut                             ,0xff867e88) //  1
NHSTUB(Fgets_Fut                              ,0xff867dc0) //  1
NHSTUB(Fopen_Fut                              ,0xff867c00) //120
NHSTUB(Fread_Fut                              ,0xff867d20) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814be4) //  1
NHSTUB(Fseek_Fut                              ,0xff867e08) //120
NHSTUB(Fwrite_Fut                             ,0xff867d70) //120
NHSTUB(GetBatteryTemperature                  ,0xff82c6d4) //102
NHSTUB(GetCCDTemperature                      ,0xff82c6c0) //102
NHSTUB(GetCurrentAvValue                      ,0xffa88ca8) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86de24) //119
NHSTUB(GetDrive_FreeClusters                  ,0xff86de9c) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xff86de60) //119
NHSTUB(GetOpticalTemperature                  ,0xff82c6ac) //120
NHSTUB(GetParameterData                       ,0xff9647d0) //  1
NHSTUB(GetPropertyCase                        ,0xff82447c) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffa6f014) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa6f028) //102
NHSTUB(GiveSemaphore                          ,0xff821100) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8fe0c0) //  1
NHSTUB(LEDDrive                               ,0xff82cc2c) //120
NHSTUB(LocalTime                              ,0xff814108) //115
NHSTUB(LockMainPower                          ,0xff95fc94) //120
NHSTUB(MakeDirectory_Fut                      ,0xff867b88) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa8b044) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6eef4) //120
NHSTUB(Open                                   ,0xff86e620) //120
NHSTUB(PT_PlaySound                           ,0xff957554) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff95bcdc) //120
NHSTUB(PostLogicalEventToUI                   ,0xff95bd68) //120
NHSTUB(Read                                   ,0xff86e6dc) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff975184) //120
NHSTUB(RenameFile_Fut                         ,0xff867a7c) //  1
NHSTUB(Restart                                ,0xff822ab8) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa8e0f8) //102
NHSTUB(SetAutoShutdownTime                    ,0xff95fb8c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff98c398) //120
NHSTUB(SetFileAttributes                      ,0xff86e800) //  1
NHSTUB(SetLogicalEventActive                  ,0xff95dd38) //1104
NHSTUB(SetParameterData                       ,0xff9646f0) //  1
NHSTUB(SetPropertyCase                        ,0xff824360) //  1
//NHSTUB(SetScriptMode                        ,0xff95dd9c) //120            == 0xff95dd9c
NHSTUB(SleepTask                              ,0xff82141c) //120
NHSTUB(TakeSemaphore                          ,0xff820f18) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a276c) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a2740) //  1
NHSTUB(TurnOnDisplay                          ,0xff9228b4) //120
NHSTUB(TurnOffDisplay                         ,0xff9228c4) //120
NHSTUB(UnlockAE                               ,0xff94a6c0) //120
NHSTUB(UnlockAF                               ,0xff94a598) //120
NHSTUB(UnlockMainPower                        ,0xff95fd48) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86db5c) //  1
//NHSTUB(VbattGet                             ,0xff82b704) //120            == 0xff82b704
NHSTUB(Write                                  ,0xff86e6e8) //120
NHSTUB(WriteSDCard                            ,0xff87cf14) //  1
NHSTUB(_log                                   ,0xffac0360) //121
NHSTUB(_log10                                 ,0xffac0a08) //121
NHSTUB(_pow                                   ,0xffac0ef8) //121
NHSTUB(_sqrt                                  ,0xffac5244) //  1
NHSTUB(apex2us                                ,0xff8ab6fc) //  1
NHSTUB(close                                  ,0xffad3de0) //109
NHSTUB(exmem_alloc                            ,0xff8127e0) //  1
NHSTUB(kbd_p1_f                               ,0xff82647c) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826488) //109
NHSTUB(kbd_p2_f                               ,0xff826860) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff827260) //  1
NHSTUB(lseek                                  ,0xffad3f24) //  1
NHSTUB(memcmp                                 ,0xffacd954) //120
NHSTUB(memcpy                                 ,0xffacd990) //120
NHSTUB(memset                                 ,0xffacda08) //120
NHSTUB(mkdir                                  ,0xff86e830) //  1
NHSTUB(open                                   ,0xffad4424) //109
NHSTUB(closedir                               ,0xffacfd80) //  1
NHSTUB(qsort                                  ,0xffacd1b4) //  1
NHSTUB(rand                                   ,0xffacd1d8) //  1
NHSTUB(realloc                                ,0xffab8498) //115
NHSTUB(srand                                  ,0xffacd1fc) //  1
NHSTUB(stat                                   ,0xffacfe48) //  1
NHSTUB(strcat                                 ,0xffacda28) //  1
NHSTUB(strchr                                 ,0xffacda54) //  1
NHSTUB(strcmp                                 ,0xffacda78) //120
NHSTUB(strcpy                                 ,0xffacdc0c) //120
NHSTUB(strftime                               ,0xffacf294) //  1
NHSTUB(strlen                                 ,0xffacdd70) //120
NHSTUB(strncmp                                ,0xffacddd4) //  1
NHSTUB(strncpy                                ,0xffacde18) //  1
NHSTUB(strrchr                                ,0xffacde9c) //  1
NHSTUB(strtol                                 ,0xffacd5f0) //  1
NHSTUB(isdigit                                ,0xffac9d24) //  1
NHSTUB(isspace                                ,0xffac9d9c) //  1
NHSTUB(isalpha                                ,0xffac9cf4) //  1
NHSTUB(isupper                                ,0xffac9db4) //  1
NHSTUB(islower                                ,0xffac9d54) //  1
NHSTUB(ispunct                                ,0xffac9d84) //  1
NHSTUB(isxdigit                               ,0xffac9dcc) //  1
NHSTUB(toupper                                ,0xffac9df4) //  1
NHSTUB(tolower                                ,0xffac9de4) //  1
NHSTUB(taskLock                               ,0xffae5120) //  1
NHSTUB(taskUnlock                             ,0xffae51c8) //  1
NHSTUB(taskName                               ,0xffae495c) //  1
NHSTUB(errnoOfTaskGet                         ,0xffad054c) //  1
NHSTUB(readdir                                ,0xffacfd4c) //  1
NHSTUB(strtoul                                ,0xffacd798) //  1
NHSTUB(strpbrk                                ,0xffacde60) //  1
NHSTUB(utime                                  ,0xffacfedc) //  1
NHSTUB(mktime                                 ,0xfface73c) //  1
NHSTUB(opendir                                ,0xffacfdb4) //  1
NHSTUB(memchr                                 ,0xffacd920) //  1
NHSTUB(memPartInfoGet                         ,0xffad7240) //  1
NHSTUB(iosDrvInstall                          ,0xffad52c4) //  1
NHSTUB(iosDevAdd                              ,0xffad5000) //  1
NHSTUB(iosDevDelete                           ,0xffad4fd8) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa8adb4) //  1
NHSTUB(taskCreateHookAdd                      ,0xffada4a0) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffada3dc) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86da04) //  1
NHSTUB(taskSuspend                            ,0xffae4b6c) //  1
NHSTUB(taskResume                             ,0xffae4d40) //  1
NHSTUB(time                                   ,0xffacf2c0) //  1
NHSTUB(vsprintf                               ,0xffad16a0) //115
NHSTUB(EngDrvRead                             ,0xff87f174) //102
