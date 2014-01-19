// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00F   // Found @ 0xffc0a1ac, "GM1.00F" @ 0xffc0a1b9
//   Firmware build timestamp: Dec 20 2005 10:42:16
//   Possible corrupt firmware dump - file size too small for start address 0xffc00000
//     file size = 2.91MB, should be 4.00MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009f990

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xffd35c44) //  1 70%
//NHSTUB(ExitFromCompensationEVF              ,0xffd37430) //  2 90%    *** != 0xffd35ca4
NHSTUB(GetFocusLensSubjectDistance            ,0xffe6d4ac) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffe6da4c) //  3 52%
NHSTUB(PutInNdFilter                          ,0xffe78004) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffe7804c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe78410) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe79f9c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe79fe4) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe7804c) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe78410) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe79f9c) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe79fe4) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffe78458) //  1 94%
//NHSTUB(Remove                               ,0xffcaf804) //  3 52%
NHSTUB(UnsetZoomForMovie                      ,0xffd833dc) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffe24154) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffec5bcc
NHSTUB(malloc                                 ,0xffec5bc0) //  1 53%
NHSTUB(taskIdListGet                          ,0xffed3804) //  1 82%
NHSTUB(localtime                              ,0xffebd314) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffc5c140) //  1 90%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd4a024 -> ffd4a024
// Strange mode 0x00010012 in firmware, found in modemap as 18 (MODE_VIDEO_STD)
// Strange mode 0x00010013 in firmware but not in current modemap
// Strange mode 0x00010014 in firmware but not in current modemap
// Strange mode 0x00010015 in firmware but not in current modemap
// Strange mode 0x00020016 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd4317c) // Found @0xffd4317c,          stubs_min = 0xffd4317c (0xFFD4317C)
//DEF(FlashParamsTable                        ,0xffd4c4e8) // Found @0xffd4c4e8,          stubs_min = 0xffd4c4e8 (0xFFD4C4E8)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xffd4f3bc

// Misc stuff
// LED table init @ 0xffc1ce60
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220094, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffeda440, canon_data_len: 0xea30

// For capt_seq.c
DEF(_nrflag,0x6d44) // Found @ ffd3a320 (0x6d44)
//static long *nrflag = (long*)(0x6d44);       // Found @ ffd3a320

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc048d8) //  1
NHSTUB(Close                                  ,0xffc5ce8c) //120
NHSTUB(CreateTask                             ,0xffc11230) //120
NHSTUB(DebugAssert                            ,0xffc03ad0) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc56340) //  1
NHSTUB(DoAELock                               ,0xffd33ca4) //120
//NHSTUB(DoAFLock                             ,0xffd33b2c) //120            == 0xffd33b2c
NHSTUB(ExecuteEventProcedure                  ,0xffc067f0) //  1
NHSTUB(ExitTask                               ,0xffc115f0) //120
NHSTUB(Fclose_Fut                             ,0xffc56480) //120
NHSTUB(Feof_Fut                               ,0xffc56694) //  1
NHSTUB(Fflush_Fut                             ,0xffc566cc) //  1
NHSTUB(Fgets_Fut                              ,0xffc56604) //  1
NHSTUB(Fopen_Fut                              ,0xffc56444) //120
NHSTUB(Fread_Fut                              ,0xffc56564) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc0490c) //  1
NHSTUB(Fseek_Fut                              ,0xffc5664c) //120
NHSTUB(Fwrite_Fut                             ,0xffc565b4) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1c468) //102
NHSTUB(GetCCDTemperature                      ,0xffc1c454) //102
NHSTUB(GetCurrentAvValue                      ,0xffe77ff0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc5c668) //119
NHSTUB(GetDrive_FreeClusters                  ,0xffc5c6e0) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xffc5c6a4) //119
NHSTUB(GetOpticalTemperature                  ,0xffc1c440) //120
NHSTUB(GetParameterData                       ,0xffd4f350) //  1
NHSTUB(GetPropertyCase                        ,0xffc14188) //  1
NHSTUB(GetSystemTime                          ,0xffc04b10) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffe59d18) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe59d2c) //102
NHSTUB(GiveSemaphore                          ,0xffc10e28) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcec238) //  1
NHSTUB(LEDDrive                               ,0xffc1c9c0) //120
NHSTUB(LocalTime                              ,0xffc041a0) //115
NHSTUB(LockMainPower                          ,0xffd49d9c) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc563cc) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffe7a628) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe59bf8) //120
NHSTUB(Open                                   ,0xffc5ce64) //120
NHSTUB(PT_PlaySound                           ,0xffd41638) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd45dc0) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd45e4c) //120
NHSTUB(Read                                   ,0xffc5cf20) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd60708) //120
NHSTUB(RenameFile_Fut                         ,0xffc562c0) //  1
NHSTUB(Restart                                ,0xffc127e0) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffe7d6dc) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd49c94) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd78174) //120
NHSTUB(SetFileAttributes                      ,0xffc5d044) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd47e3c) //1104
NHSTUB(SetParameterData                       ,0xffd4f270) //  1
NHSTUB(SetPropertyCase                        ,0xffc1406c) //  1
//NHSTUB(SetScriptMode                        ,0xffd47ea4) //120            == 0xffd47ea4
NHSTUB(SleepTask                              ,0xffc11144) //120
NHSTUB(TakeSemaphore                          ,0xffc10c40) //1101
NHSTUB(TurnOffBackLight                       ,0xffd95314) //  1
NHSTUB(TurnOnBackLight                        ,0xffd952e8) //  1
NHSTUB(TurnOnDisplay                          ,0xffd107d4) //120
NHSTUB(TurnOffDisplay                         ,0xffd107e4) //120
NHSTUB(UnlockAE                               ,0xffd33cc4) //120
NHSTUB(UnlockAF                               ,0xffd33b94) //120
NHSTUB(UnlockMainPower                        ,0xffd49e50) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc5c3a0) //  1
NHSTUB(VbattGet                               ,0xffc1b4ac) //120
NHSTUB(Write                                  ,0xffc5cf2c) //120
NHSTUB(WriteSDCard                            ,0xffc6b758) //  1
NHSTUB(_log                                   ,0xffeaf100) //121
NHSTUB(_log10                                 ,0xffeaf7a8) //121
NHSTUB(_pow                                   ,0xffeafc98) //121
NHSTUB(_sqrt                                  ,0xffeb3fe4) //  1
NHSTUB(apex2us                                ,0xffc98f9c) //  1
NHSTUB(close                                  ,0xffec2b80) //109
NHSTUB(exmem_alloc                            ,0xffc02830) //  1
NHSTUB(kbd_p1_f                               ,0xffc16164) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc16170) //109
NHSTUB(kbd_p2_f                               ,0xffc16548) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc16fb8) //  1
NHSTUB(kbd_pwr_off                            ,0xffc1756c) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17600) // 1 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffc1761c) // 1 6/0
NHSTUB(kbd_pwr_on                             ,0xffc17544) //  1
NHSTUB(lseek                                  ,0xffec2cc4) //  1
NHSTUB(memcmp                                 ,0xffebc6f4) //120
NHSTUB(memcpy                                 ,0xffebc730) //120
NHSTUB(memset                                 ,0xffebc7a8) //120
NHSTUB(mkdir                                  ,0xffc5d074) //  1
NHSTUB(open                                   ,0xffec31c4) //109
NHSTUB(closedir                               ,0xffebeb20) //  1
NHSTUB(qsort                                  ,0xffebbf54) //  1
NHSTUB(rand                                   ,0xffebbf78) //  1
NHSTUB(realloc                                ,0xffea7234) //115
NHSTUB(srand                                  ,0xffebbf9c) //  1
NHSTUB(stat                                   ,0xffebebe8) //  1
NHSTUB(strcat                                 ,0xffebc7c8) //  1
NHSTUB(strchr                                 ,0xffebc7f4) //  1
NHSTUB(strcmp                                 ,0xffebc818) //120
NHSTUB(strcpy                                 ,0xffebc9ac) //120
NHSTUB(strftime                               ,0xffebe034) //  1
NHSTUB(strlen                                 ,0xffebcb10) //120
NHSTUB(strncmp                                ,0xffebcb74) //  1
NHSTUB(strncpy                                ,0xffebcbb8) //  1
NHSTUB(strrchr                                ,0xffebcc3c) //  1
NHSTUB(strtol                                 ,0xffebc390) //  1
NHSTUB(isdigit                                ,0xffeb8ac4) //  1
NHSTUB(isspace                                ,0xffeb8b3c) //  1
NHSTUB(isalpha                                ,0xffeb8a94) //  1
NHSTUB(isupper                                ,0xffeb8b54) //  1
NHSTUB(islower                                ,0xffeb8af4) //  1
NHSTUB(ispunct                                ,0xffeb8b24) //  1
NHSTUB(isxdigit                               ,0xffeb8b6c) //  1
NHSTUB(toupper                                ,0xffeb8b94) //  1
NHSTUB(tolower                                ,0xffeb8b84) //  1
NHSTUB(taskLock                               ,0xffed3ec0) //  1
NHSTUB(taskUnlock                             ,0xffed3f68) //  1
NHSTUB(taskName                               ,0xffed36fc) //  1
NHSTUB(errnoOfTaskGet                         ,0xffebf2ec) //  1
NHSTUB(readdir                                ,0xffebeaec) //  1
NHSTUB(strtoul                                ,0xffebc538) //  1
NHSTUB(strpbrk                                ,0xffebcc00) //  1
NHSTUB(utime                                  ,0xffebec7c) //  1
NHSTUB(mktime                                 ,0xffebd4dc) //  1
NHSTUB(opendir                                ,0xffebeb54) //  1
NHSTUB(memchr                                 ,0xffebc6c0) //  1
NHSTUB(memPartInfoGet                         ,0xffec5fe0) //  1
NHSTUB(iosDrvInstall                          ,0xffec4064) //  1
NHSTUB(iosDevAdd                              ,0xffec3da0) //  1
NHSTUB(iosDevDelete                           ,0xffec3d78) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffe7a398) //  1
NHSTUB(taskCreateHookAdd                      ,0xffec9240) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffec917c) //  1
NHSTUB(Unmount_FileSystem                     ,0xffc5c248) //  1
NHSTUB(MakeAFScan                             ,0xffd384e4) //  1
NHSTUB(taskSuspend                            ,0xffed390c) //  1
NHSTUB(taskResume                             ,0xffed3ae0) //  1
NHSTUB(time                                   ,0xffebe060) //  1
NHSTUB(vsprintf                               ,0xffec0440) //115
NHSTUB(EngDrvRead                             ,0xffc6d9b8) //102
