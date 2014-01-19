// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00D   // Found @ 0xff81a540, "GM1.00D" @ 0xff81a54d
//   Firmware build timestamp: Aug 25 2006 09:35:10
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 7.41MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009c4b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff95e464) //  1 73%    *** != 0x00000000
//NHSTUB(GetDrive_FreeClusters                ,0xff86eef0) //1103        *** != 0xff867c04
NHSTUB(GetFocusLensSubjectDistance            ,0xffab6354) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffab68f4) //  3 92%
NHSTUB(GetParameterData                       ,0xff977cd8) //  1 86%
NHSTUB(GetSystemTime                          ,0xff814e64) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffac2194) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffac3d24) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac3d6c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac3d24) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac3d6c) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffac21dc) //  1 94%
//NHSTUB(Remove                               ,0xff8caf98) //  3 52%
NHSTUB(SetParameterData                       ,0xff977bf8) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff9aef90) //  1 89%
NHSTUB(WriteSDCard                            ,0xff87e128) //  3 64%
NHSTUB(add_ptp_handler                        ,0xffa75b94) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81282c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffb0c438
NHSTUB(kbd_pwr_off                            ,0xff827ec4) //  1 83%
// ALT: NHSTUB(kbd_pwr_off, 0xff827ee0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829238) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829254) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff827ee0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828ee0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828efc) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828fe8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829004) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8290d4) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8290f0) // 3 5/1
// ERROR: kbd_pwr_on is not found.                         //--- ---    *** != 0xff827ee0
NHSTUB(malloc                                 ,0xffb0c42c) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb19a74) //  1 82%
NHSTUB(localtime                              ,0xffb05068) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86e940) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff97310c -> ff97310c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff96bff4) // Found @0xff96bff4,          stubs_min = 0xff96bff4 (0xFF96BFF4)
//DEF(FlashParamsTable                        ,0xff9754e8) // Found @0xff9754e8,          stubs_min = 0xff9754e8 (0xFF9754E8)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xff977d44

// Misc stuff
// LED table init @ 0xff82dbb4
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220098, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffb204a0, canon_data_len: 0xbc80

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814c2c) //  1
NHSTUB(Close                                  ,0xff86f6a0) //120
NHSTUB(CreateTask                             ,0xff821598) //120
NHSTUB(DebugAssert                            ,0xff813afc) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86883c) //  1
NHSTUB(DoAELock                               ,0xff95c530) //120
//NHSTUB(DoAFLock                             ,0xff95c3e0) //120            == 0xff95c3e0
NHSTUB(ExecuteEventProcedure                  ,0xff816b44) //  1
NHSTUB(ExitTask                               ,0xff821958) //120
NHSTUB(Fclose_Fut                             ,0xff86897c) //120
NHSTUB(Feof_Fut                               ,0xff868b90) //  1
NHSTUB(Fflush_Fut                             ,0xff868bc8) //  1
NHSTUB(Fgets_Fut                              ,0xff868b00) //  1
NHSTUB(Fopen_Fut                              ,0xff868940) //120
NHSTUB(Fread_Fut                              ,0xff868a60) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814c60) //  1
NHSTUB(Fseek_Fut                              ,0xff868b48) //120
NHSTUB(Fwrite_Fut                             ,0xff868ab0) //120
NHSTUB(GetBatteryTemperature                  ,0xff82d270) //102
NHSTUB(GetCCDTemperature                      ,0xff82d25c) //102
NHSTUB(GetCurrentAvValue                      ,0xffac2010) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff86ee78) //119            == 0xff86ee78
//NHSTUB(GetDrive_TotalClusters               ,0xff86eeb4) //119            == 0xff86eeb4
NHSTUB(GetOpticalTemperature                  ,0xff82d248) //120
NHSTUB(GetPropertyCase                        ,0xff82487c) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffaa6fcc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaa6fe0) //102
NHSTUB(GiveSemaphore                          ,0xff821190) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff91053c) //  1
NHSTUB(LEDDrive                               ,0xff82d7c8) //120
NHSTUB(LocalTime                              ,0xff814184) //115
NHSTUB(LockMainPower                          ,0xff972eac) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8688c8) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffac43c0) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaa6eac) //120
NHSTUB(Open                                   ,0xff86f678) //120
NHSTUB(PT_PlaySound                           ,0xff96a36c) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff96ee68) //120
NHSTUB(PostLogicalEventToUI                   ,0xff96eee4) //120
NHSTUB(Read                                   ,0xff86f734) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff989c68) //120
NHSTUB(RenameFile_Fut                         ,0xff8687bc) //  1
NHSTUB(Restart                                ,0xff822ab0) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffac7c68) //102
NHSTUB(SetAutoShutdownTime                    ,0xff972db0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9a3fa8) //120
NHSTUB(SetFileAttributes                      ,0xff86f858) //  1
NHSTUB(SetLogicalEventActive                  ,0xff970c30) //1104
NHSTUB(SetPropertyCase                        ,0xff824750) //  1
//NHSTUB(SetScriptMode                        ,0xff970c98) //120            == 0xff970c98
NHSTUB(SleepTask                              ,0xff8214ac) //120
NHSTUB(TakeSemaphore                          ,0xff820fa8) //1101
NHSTUB(TurnOffBackLight                       ,0xff9bbc6c) //  2
NHSTUB(TurnOnBackLight                        ,0xff9bbc3c) //  2
NHSTUB(TurnOnDisplay                          ,0xff933e14) //120
NHSTUB(TurnOffDisplay                         ,0xff933e24) //120
NHSTUB(UnlockAE                               ,0xff95c550) //120
//NHSTUB(UnlockAF                             ,0xff95c424) //120            == 0xff95c424
NHSTUB(UnlockMainPower                        ,0xff972f44) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86ebac) //  1
//NHSTUB(VbattGet                             ,0xff82c1a0) //120            == 0xff82c1a0
NHSTUB(Write                                  ,0xff86f740) //120
NHSTUB(_log                                   ,0xffafef88) //121
NHSTUB(_log10                                 ,0xffafb328) //121
NHSTUB(_pow                                   ,0xffafb4b0) //121
NHSTUB(_sqrt                                  ,0xffafd384) //  1
NHSTUB(apex2us                                ,0xff8b1f04) //  1
NHSTUB(close                                  ,0xffb093ec) //109
NHSTUB(kbd_p1_f                               ,0xff826c64) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826c70) //109
NHSTUB(kbd_p2_f                               ,0xff827048) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff8279b0) //  1
NHSTUB(lseek                                  ,0xffb09530) //  1
NHSTUB(memcmp                                 ,0xffb04448) //120
NHSTUB(memcpy                                 ,0xffb04484) //120
NHSTUB(memset                                 ,0xffb044fc) //120
NHSTUB(mkdir                                  ,0xff86f888) //  1
NHSTUB(open                                   ,0xffb09a30) //109
NHSTUB(closedir                               ,0xffb06874) //  1
NHSTUB(qsort                                  ,0xffb03ca8) //  1
NHSTUB(rand                                   ,0xffb03ccc) //  1
NHSTUB(realloc                                ,0xffaf5bd0) //115
NHSTUB(srand                                  ,0xffb03cf0) //  1
NHSTUB(stat                                   ,0xffb0693c) //  1
NHSTUB(strcat                                 ,0xffb0451c) //  1
NHSTUB(strchr                                 ,0xffb04548) //  1
NHSTUB(strcmp                                 ,0xffb0456c) //120
NHSTUB(strcpy                                 ,0xffb04700) //120
NHSTUB(strftime                               ,0xffb05d88) //  1
NHSTUB(strlen                                 ,0xffb04864) //120
NHSTUB(strncmp                                ,0xffb048c8) //  1
NHSTUB(strncpy                                ,0xffb0490c) //  1
NHSTUB(strrchr                                ,0xffb04990) //  1
NHSTUB(strtol                                 ,0xffb040e4) //  1
NHSTUB(isdigit                                ,0xffb00948) //  1
NHSTUB(isspace                                ,0xffb009c0) //  1
NHSTUB(isalpha                                ,0xffb00918) //  1
NHSTUB(isupper                                ,0xffb009d8) //  1
NHSTUB(islower                                ,0xffb00978) //  1
NHSTUB(ispunct                                ,0xffb009a8) //  1
NHSTUB(isxdigit                               ,0xffb009f0) //  1
NHSTUB(toupper                                ,0xffb00a18) //  1
NHSTUB(tolower                                ,0xffb00a08) //  1
NHSTUB(taskLock                               ,0xffb1a130) //  1
NHSTUB(taskUnlock                             ,0xffb1a1d8) //  1
NHSTUB(taskName                               ,0xffb1996c) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb07040) //  1
NHSTUB(readdir                                ,0xffb06840) //  1
NHSTUB(strtoul                                ,0xffb0428c) //  1
NHSTUB(strpbrk                                ,0xffb04954) //  1
NHSTUB(utime                                  ,0xffb069d0) //  1
NHSTUB(mktime                                 ,0xffb05230) //  1
NHSTUB(opendir                                ,0xffb068a8) //  1
NHSTUB(memchr                                 ,0xffb04414) //  1
NHSTUB(memPartInfoGet                         ,0xffb0c84c) //  1
NHSTUB(iosDrvInstall                          ,0xffb0a8d0) //  1
NHSTUB(iosDevAdd                              ,0xffb0a60c) //  1
NHSTUB(iosDevDelete                           ,0xffb0a5e4) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffac4120) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb0faac) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb0f9e8) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86ea58) //  1
NHSTUB(taskSuspend                            ,0xffb19b7c) //  1
NHSTUB(taskResume                             ,0xffb19d50) //  1
NHSTUB(time                                   ,0xffb05db4) //  1
NHSTUB(vsprintf                               ,0xffb08194) //115
NHSTUB(EngDrvRead                             ,0xff880668) //102
