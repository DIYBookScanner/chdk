// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00G   // Found @ 0xff81ada0, "GM1.00G" @ 0xff81adad
//   Firmware build timestamp: Dec 19 2005 18:54:40
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.03MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0006ef70

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xff967eb4
//NHSTUB(ExitFromCompensationEVF              ,0xff96b440) //  1 70%    *** != 0xff967f08
NHSTUB(GetFocusLensSubjectDistance            ,0xffa8e778) //  1 87%
// ERROR: GetFocusLensSubjectDistanceFromLens is not found.  //--- ---    *** != 0xffa8ed00
NHSTUB(GetParameterData                       ,0xff987d44) //  1 76%
//NHSTUB(GetPropertyCase                      ,0xff825d04) //  2 71%    *** != 0xff825d08
NHSTUB(GetSystemTime                          ,0xff814b98) //  1 96%
//NHSTUB(GetZoomLensCurrentPoint              ,0xffa87f6c) //120        *** != 0xffaa85b0
//NHSTUB(GetZoomLensCurrentPosition           ,0xffa87f80) //102        *** != 0xffaa85c4
NHSTUB(PutInNdFilter                          ,0xffaa6ae4) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffaa6b2c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa6ef4) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa8688) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa86d0) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa6b2c) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa6ef4) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa8688) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa86d0) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffaa6f3c) //  1 94%
//NHSTUB(Remove                               ,0xff8d2698) //  3 52%    *** != 0xff87710c
//NHSTUB(Restart                              ,0xff823de4) //  1 84%    *** != 0xff823de8
NHSTUB(SetCurrentCaptureModeType              ,0xff9aea98) //  1 73%
NHSTUB(SetFileAttributes                      ,0xff877258) //  1 58%
//NHSTUB(SetParameterData                     ,0xff987d40) //  1 66%    *** != 0xff987c70
// ERROR: SetPropertyCase is not found.                    //--- ---    *** != 0xff825c00
NHSTUB(UpdateMBROnFlash                       ,0xff87620c) //  1 96%
// ERROR: WriteSDCard is not found.                        //--- ---    *** != 0x00000000
NHSTUB(add_ptp_handler                        ,0xffa4b9ac) //  1 96%
NHSTUB(exmem_alloc                            ,0xff812a74) //  1 92%
// ERROR: free is not found.                               //--- ---    *** != 0xffaf7318
// ERROR: kbd_p1_f is not found.                           //--- ---    *** != 0xff829470
// ERROR: kbd_p1_f_cont is not found.                      //--- ---    *** != 0xff829484
// ERROR: kbd_p2_f is not found.                           //--- ---    *** != 0xff829364
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0xff829e58
//NHSTUB(kbd_pwr_off                          ,0xff82b0d4) //  1 83%    *** != 0xff82ae84
// ALT: NHSTUB(kbd_pwr_off, 0xff82b0f0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82ae84) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82aea0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82af70) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82af8c) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xff94003c) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff940068) // 1 5/4
NHSTUB(malloc                                 ,0xffaf730c) //  1 53%
NHSTUB(mkdir                                  ,0xff877288) //  1 61%
// ALT: NHSTUB(mkdir, 0xff877348) // 1 19/12
NHSTUB(taskIdListGet                          ,0xffb02470) //  1 82%
NHSTUB(localtime                              ,0xffaeea60) //  1 93%
// ERROR: Mount_FileSystem is not found.                   //--- ---    *** != 0xff875ff0
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff9834dc -> ff9834dc
// Strange mode 0x00020011 in firmware but not in current modemap
// Strange mode 0x00030012 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff97d690) // Found @0xff97d690,          stubs_min = 0xff97d690 (0xFF97D690)
//DEF(FlashParamsTable                        ,0xff985604) // Found @0xff985604,          stubs_min = 0xff985604 (0xFF985604)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x55; }                          // Found @0xff987db0

// Misc stuff
// LED table init @ 0xff82ecb0
// LED #1: 0xc022008c, offset 0x104
// LED #2: 0xc0220088, offset 0x144
// LED #3: 0xc02200fc, offset 0x1c4

// canon_data_src: 0xffb090b0, canon_data_len: 0xdbe0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814810) //  1
//NHSTUB(Close                                ,0xff877100) //120            == 0xff877100
NHSTUB(CreateTask                             ,0xff82239c) //120
NHSTUB(DebugAssert                            ,0xff813d58) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86f980) //  1
NHSTUB(DoAELock                               ,0xff967fd0) //120
//NHSTUB(DoAFLock                             ,0xff967cd4) //120            == 0xff967cd4
NHSTUB(ExecuteEventProcedure                  ,0xff816ab4) //  1
NHSTUB(ExitTask                               ,0xff82275c) //120
NHSTUB(Fclose_Fut                             ,0xff86fac0) //  1
NHSTUB(Feof_Fut                               ,0xff86fcd4) //  1
NHSTUB(Fflush_Fut                             ,0xff86fd0c) //  1
NHSTUB(Fgets_Fut                              ,0xff86fc44) //  1
NHSTUB(Fopen_Fut                              ,0xff86fa84) //  1
NHSTUB(Fread_Fut                              ,0xff86fba4) //  1
NHSTUB(FreeUncacheableMemory                  ,0xff814844) //  1
NHSTUB(Fseek_Fut                              ,0xff86fc8c) //  1
NHSTUB(Fwrite_Fut                             ,0xff86fbf4) //  1
//NHSTUB(GetBatteryTemperature                ,0xff82e368) //102            == 0xff82e368
//NHSTUB(GetCCDTemperature                    ,0xff82e354) //102            == 0xff82e354
NHSTUB(GetCurrentAvValue                      ,0xffaa6ad0) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff87652c) //119            == 0xff87652c
//NHSTUB(GetDrive_FreeClusters                ,0xff8765c4) //1103            == 0xff8765c4
//NHSTUB(GetDrive_TotalClusters               ,0xff876588) //119            == 0xff876588
//NHSTUB(GetOpticalTemperature                ,0xff82e340) //120            == 0xff82e340
NHSTUB(GiveSemaphore                          ,0xff821d54) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff912c6c) //  1
NHSTUB(LEDDrive                               ,0xff82e880) //120
NHSTUB(LocalTime                              ,0xff8144d8) //115
NHSTUB(LockMainPower                          ,0xff983254) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86fa0c) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffaa8cbc) //102
//NHSTUB(MoveZoomLensWithPoint                ,0xffa87d8c) //120            == 0xffa87d8c
//NHSTUB(Open                                 ,0xff8770f4) //120            == 0xff8770f4
NHSTUB(PT_PlaySound                           ,0xff97baa4) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff97fee4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff97ff70) //120
//NHSTUB(Read                                 ,0xff877160) //120            == 0xff877160
NHSTUB(RefreshPhysicalScreen                  ,0xff998640) //120
NHSTUB(RenameFile_Fut                         ,0xff86f900) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffaabb98) //102
NHSTUB(SetAutoShutdownTime                    ,0xff98314c) //120
NHSTUB(SetLogicalEventActive                  ,0xff9816f4) //1104
//NHSTUB(SetScriptMode                        ,0xff981758) //120            == 0xff981758
NHSTUB(SleepTask                              ,0xff8221fc) //120
NHSTUB(TakeSemaphore                          ,0xff821b6c) //1101
NHSTUB(TurnOffBackLight                       ,0xff9cbc64) //  1
NHSTUB(TurnOnBackLight                        ,0xff9cbc38) //  1
NHSTUB(TurnOnDisplay                          ,0xff93cddc) //120
NHSTUB(TurnOffDisplay                         ,0xff93cdec) //120
NHSTUB(UnlockAE                               ,0xff968024) //120
//NHSTUB(UnlockAF                             ,0xff967db0) //120            == 0xff967db0
NHSTUB(UnlockMainPower                        ,0xff983308) //120
//NHSTUB(VbattGet                             ,0xff82d570) //120            == 0xff82d570
//NHSTUB(Write                                ,0xff87716c) //120            == 0xff87716c
NHSTUB(_log                                   ,0xffae084c) //121
NHSTUB(_log10                                 ,0xffae0ef4) //121
NHSTUB(_pow                                   ,0xffae13e4) //121
NHSTUB(_sqrt                                  ,0xffae5730) //  1
NHSTUB(apex2us                                ,0xff8bbbb4) //  1
NHSTUB(close                                  ,0xffaf42cc) //109
NHSTUB(lseek                                  ,0xffaf4410) //  1
NHSTUB(memcmp                                 ,0xffaede40) //120
NHSTUB(memcpy                                 ,0xffaede7c) //120
NHSTUB(memset                                 ,0xffaedef4) //120
NHSTUB(open                                   ,0xffaf4910) //  1
NHSTUB(closedir                               ,0xffaf026c) //  1
NHSTUB(qsort                                  ,0xffaed6a0) //  1
NHSTUB(rand                                   ,0xffaed6c4) //  1
NHSTUB(realloc                                ,0xffad7340) //115
NHSTUB(srand                                  ,0xffaed6e8) //  1
NHSTUB(stat                                   ,0xffaf0334) //  1
NHSTUB(strcat                                 ,0xffaedf14) //  1
NHSTUB(strchr                                 ,0xffaedf40) //  1
NHSTUB(strcmp                                 ,0xffaedf64) //120
NHSTUB(strcpy                                 ,0xffaee0f8) //120
NHSTUB(strftime                               ,0xffaef780) //  1
NHSTUB(strlen                                 ,0xffaee25c) //120
NHSTUB(strncmp                                ,0xffaee2c0) //  1
NHSTUB(strncpy                                ,0xffaee304) //  1
NHSTUB(strrchr                                ,0xffaee388) //  1
NHSTUB(strtol                                 ,0xffaedadc) //  1
NHSTUB(isdigit                                ,0xffaea210) //  1
NHSTUB(isspace                                ,0xffaea288) //  1
NHSTUB(isalpha                                ,0xffaea1e0) //  1
NHSTUB(isupper                                ,0xffaea2a0) //  1
NHSTUB(islower                                ,0xffaea240) //  1
NHSTUB(ispunct                                ,0xffaea270) //  1
NHSTUB(isxdigit                               ,0xffaea2b8) //  1
NHSTUB(toupper                                ,0xffaea2e0) //  1
NHSTUB(tolower                                ,0xffaea2d0) //  1
NHSTUB(taskLock                               ,0xffb02b2c) //  1
NHSTUB(taskUnlock                             ,0xffb02bd4) //  1
NHSTUB(taskName                               ,0xffb02368) //  1
NHSTUB(errnoOfTaskGet                         ,0xffaf0a38) //  1
NHSTUB(readdir                                ,0xffaf0238) //  1
NHSTUB(strtoul                                ,0xffaedc84) //  1
NHSTUB(strpbrk                                ,0xffaee34c) //  1
NHSTUB(utime                                  ,0xffaf03c8) //  1
NHSTUB(mktime                                 ,0xffaeec28) //  1
NHSTUB(opendir                                ,0xffaf02a0) //  1
NHSTUB(memchr                                 ,0xffaede0c) //  1
NHSTUB(memPartInfoGet                         ,0xffaf772c) //  1
NHSTUB(iosDrvInstall                          ,0xffaf57b0) //  1
NHSTUB(iosDevAdd                              ,0xffaf54ec) //  1
NHSTUB(iosDevDelete                           ,0xffaf54c4) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffaa8a2c) //  1
NHSTUB(taskCreateHookAdd                      ,0xffafa98c) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffafa8c8) //  1
NHSTUB(Unmount_FileSystem                     ,0xff876060) //  1
NHSTUB(taskSuspend                            ,0xffb02578) //  1
NHSTUB(taskResume                             ,0xffb0274c) //  1
NHSTUB(time                                   ,0xffaef7ac) //  1
NHSTUB(vsprintf                               ,0xffaf1b8c) //115
NHSTUB(EngDrvRead                             ,0xff88b2a4) //102
