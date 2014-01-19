// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00A   // Found @ 0xff81a540, "GM1.00A" @ 0xff81a54d
//   Firmware build timestamp: Dec  8 2005 15:39:30
//   Canon DIGITAL IXUS 60

// Values for makefile.inc
//   PLATFORMID = 12572 (0x311c) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009c430

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff95d96c) //  1 73%    *** != 0x00000000
//NHSTUB(GetDrive_FreeClusters                ,0xff86eef0) //1103        *** != 0xff867c04
NHSTUB(GetFocusLensSubjectDistance            ,0xffab585c) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffab5dfc) //  3 92%
NHSTUB(GetParameterData                       ,0xff9771e0) //  1 86%
NHSTUB(GetSystemTime                          ,0xff814e64) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffac15b4) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffac3144) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac318c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac3144) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac318c) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffac15fc) //  1 94%
//NHSTUB(Remove                               ,0xff8caf98) //  3 52%
NHSTUB(SetParameterData                       ,0xff977100) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff9ae498) //  1 89%
NHSTUB(WriteSDCard                            ,0xff87e128) //  3 64%
NHSTUB(add_ptp_handler                        ,0xffa7509c) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81282c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffb0b858
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
NHSTUB(malloc                                 ,0xffb0b84c) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb18e94) //  1 82%
NHSTUB(localtime                              ,0xffb04488) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86e940) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff972614 -> ff972614
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff96b4fc) // Found @0xff96b4fc,          stubs_min = 0xff96b4fc (0xFF96B4FC)
//DEF(FlashParamsTable                        ,0xff9749f0) // Found @0xff9749f0,          stubs_min = 0xff9749f0 (0xFF9749F0)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xff97724c

// Misc stuff
// LED table init @ 0xff82dbb4
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220098, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffb1f8c0, canon_data_len: 0xbc60

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814c2c) //  1
NHSTUB(Close                                  ,0xff86f6a0) //120
NHSTUB(CreateTask                             ,0xff821598) //120
NHSTUB(DebugAssert                            ,0xff813afc) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86883c) //  1
NHSTUB(DoAELock                               ,0xff95ba38) //120
//NHSTUB(DoAFLock                             ,0xff95b8e8) //120            == 0xff95b8e8
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
NHSTUB(GetCurrentAvValue                      ,0xffac1430) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff86ee78) //119            == 0xff86ee78
//NHSTUB(GetDrive_TotalClusters               ,0xff86eeb4) //119            == 0xff86eeb4
NHSTUB(GetOpticalTemperature                  ,0xff82d248) //120
NHSTUB(GetPropertyCase                        ,0xff82487c) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffaa64d4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaa64e8) //102
NHSTUB(GiveSemaphore                          ,0xff821190) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff91053c) //  1
NHSTUB(LEDDrive                               ,0xff82d7c8) //120
NHSTUB(LocalTime                              ,0xff814184) //115
NHSTUB(LockMainPower                          ,0xff9723b4) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8688c8) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffac37e0) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaa63b4) //120
NHSTUB(Open                                   ,0xff86f678) //120
NHSTUB(PT_PlaySound                           ,0xff969874) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff96e370) //120
NHSTUB(PostLogicalEventToUI                   ,0xff96e3ec) //120
NHSTUB(Read                                   ,0xff86f734) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff989170) //120
NHSTUB(RenameFile_Fut                         ,0xff8687bc) //  1
NHSTUB(Restart                                ,0xff822ab0) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffac7088) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9722b8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9a34b0) //120
NHSTUB(SetFileAttributes                      ,0xff86f858) //  1
NHSTUB(SetLogicalEventActive                  ,0xff970138) //1104
NHSTUB(SetPropertyCase                        ,0xff824750) //  1
//NHSTUB(SetScriptMode                        ,0xff9701a0) //120            == 0xff9701a0
NHSTUB(SleepTask                              ,0xff8214ac) //120
NHSTUB(TakeSemaphore                          ,0xff820fa8) //1101
NHSTUB(TurnOffBackLight                       ,0xff9bb174) //  2
NHSTUB(TurnOnBackLight                        ,0xff9bb144) //  2
NHSTUB(TurnOnDisplay                          ,0xff933b40) //120
NHSTUB(TurnOffDisplay                         ,0xff933b50) //120
NHSTUB(UnlockAE                               ,0xff95ba58) //120
//NHSTUB(UnlockAF                             ,0xff95b92c) //120            == 0xff95b92c
NHSTUB(UnlockMainPower                        ,0xff97244c) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86ebac) //  1
//NHSTUB(VbattGet                             ,0xff82c1a0) //120            == 0xff82c1a0
NHSTUB(Write                                  ,0xff86f740) //120
NHSTUB(_log                                   ,0xffafe3a8) //121
NHSTUB(_log10                                 ,0xffafa748) //121
NHSTUB(_pow                                   ,0xffafa8d0) //121
NHSTUB(_sqrt                                  ,0xffafc7a4) //  1
NHSTUB(apex2us                                ,0xff8b1f04) //  1
NHSTUB(close                                  ,0xffb0880c) //109
NHSTUB(kbd_p1_f                               ,0xff826c64) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826c70) //109
NHSTUB(kbd_p2_f                               ,0xff827048) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff8279b0) //  1
NHSTUB(lseek                                  ,0xffb08950) //  1
NHSTUB(memcmp                                 ,0xffb03868) //120
NHSTUB(memcpy                                 ,0xffb038a4) //120
NHSTUB(memset                                 ,0xffb0391c) //120
NHSTUB(mkdir                                  ,0xff86f888) //  1
NHSTUB(open                                   ,0xffb08e50) //109
NHSTUB(closedir                               ,0xffb05c94) //  1
NHSTUB(qsort                                  ,0xffb030c8) //  1
NHSTUB(rand                                   ,0xffb030ec) //  1
NHSTUB(realloc                                ,0xffaf4ff0) //115
NHSTUB(srand                                  ,0xffb03110) //  1
NHSTUB(stat                                   ,0xffb05d5c) //  1
NHSTUB(strcat                                 ,0xffb0393c) //  1
NHSTUB(strchr                                 ,0xffb03968) //  1
NHSTUB(strcmp                                 ,0xffb0398c) //120
NHSTUB(strcpy                                 ,0xffb03b20) //120
NHSTUB(strftime                               ,0xffb051a8) //  1
NHSTUB(strlen                                 ,0xffb03c84) //120
NHSTUB(strncmp                                ,0xffb03ce8) //  1
NHSTUB(strncpy                                ,0xffb03d2c) //  1
NHSTUB(strrchr                                ,0xffb03db0) //  1
NHSTUB(strtol                                 ,0xffb03504) //  1
NHSTUB(isdigit                                ,0xffaffd68) //  1
NHSTUB(isspace                                ,0xffaffde0) //  1
NHSTUB(isalpha                                ,0xffaffd38) //  1
NHSTUB(isupper                                ,0xffaffdf8) //  1
NHSTUB(islower                                ,0xffaffd98) //  1
NHSTUB(ispunct                                ,0xffaffdc8) //  1
NHSTUB(isxdigit                               ,0xffaffe10) //  1
NHSTUB(toupper                                ,0xffaffe38) //  1
NHSTUB(tolower                                ,0xffaffe28) //  1
NHSTUB(taskLock                               ,0xffb19550) //  1
NHSTUB(taskUnlock                             ,0xffb195f8) //  1
NHSTUB(taskName                               ,0xffb18d8c) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb06460) //  1
NHSTUB(readdir                                ,0xffb05c60) //  1
NHSTUB(strtoul                                ,0xffb036ac) //  1
NHSTUB(strpbrk                                ,0xffb03d74) //  1
NHSTUB(utime                                  ,0xffb05df0) //  1
NHSTUB(mktime                                 ,0xffb04650) //  1
NHSTUB(opendir                                ,0xffb05cc8) //  1
NHSTUB(memchr                                 ,0xffb03834) //  1
NHSTUB(memPartInfoGet                         ,0xffb0bc6c) //  1
NHSTUB(iosDrvInstall                          ,0xffb09cf0) //  1
NHSTUB(iosDevAdd                              ,0xffb09a2c) //  1
NHSTUB(iosDevDelete                           ,0xffb09a04) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffac3540) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb0eecc) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb0ee08) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86ea58) //  1
NHSTUB(taskSuspend                            ,0xffb18f9c) //  1
NHSTUB(taskResume                             ,0xffb19170) //  1
NHSTUB(time                                   ,0xffb051d4) //  1
NHSTUB(vsprintf                               ,0xffb075b4) //115
NHSTUB(EngDrvRead                             ,0xff880668) //102
