// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00B   // Found @ 0xff81a5c4, "GM1.00B" @ 0xff81a5d1
//   Firmware build timestamp: Feb  6 2006 21:11:06
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.94MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009c890

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff95d53c) //  1 73%    *** != 0x00000000
NHSTUB(GetFocusLensSubjectDistance            ,0xffab4f50) //  1 54%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffab54ec) //  2 92%
NHSTUB(GetParameterData                       ,0xff976f2c) //  1 86%
NHSTUB(GetSystemTime                          ,0xff814ee8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffac41a0) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffac5d40) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac5d88) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac5d40) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac5d88) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffac41e8) //  1 94%
//NHSTUB(Remove                               ,0xff8cae3c) //  3 52%
NHSTUB(SetParameterData                       ,0xff976e4c) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff9ae16c) //  1 89%
NHSTUB(WriteSDCard                            ,0xff87dfcc) //  3 64%
NHSTUB(add_ptp_handler                        ,0xffa74c74) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81282c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffb0efe4
//NHSTUB(kbd_pwr_off                          ,0xff827f50) //  1 83%    *** != 0xff827f08
// ALT: NHSTUB(kbd_pwr_off, 0xff827f6c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8291b4) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8291d0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff827f6c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828e5c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828e78) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828f64) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828f80) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829050) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82906c) // 3 5/1
// ERROR: kbd_pwr_on is not found.                         //--- ---    *** != 0xff827ec8
NHSTUB(malloc                                 ,0xffb0efd8) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb1c620) //  1 82%
NHSTUB(localtime                              ,0xffb07c14) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86e8d4) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xff95fde8

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff972360 -> ff972360
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff96b1c8) // Found @0xff96b1c8,          stubs_min = 0xff96b1c8 (0xFF96B1C8)
//DEF(FlashParamsTable                        ,0xff97473c) // Found @0xff97473c,          stubs_min = 0xff97473c (0xFF97473C)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xff976f98

// Misc stuff
// LED table init @ 0xff82db5c
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220098, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffb23040, canon_data_len: 0xbdb0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814cb0) //  1
NHSTUB(Close                                  ,0xff86f5a4) //120
NHSTUB(CreateTask                             ,0xff82161c) //120
NHSTUB(DebugAssert                            ,0xff813b80) //1100
NHSTUB(DeleteFile_Fut                         ,0xff868744) //  1
NHSTUB(DoAELock                               ,0xff95b570) //120
//NHSTUB(DoAFLock                             ,0xff95b420) //120            == 0xff95b420
NHSTUB(ExecuteEventProcedure                  ,0xff816bc8) //  1
NHSTUB(ExitTask                               ,0xff8219dc) //120
NHSTUB(Fclose_Fut                             ,0xff868884) //120
NHSTUB(Feof_Fut                               ,0xff868a98) //  1
NHSTUB(Fflush_Fut                             ,0xff868ad0) //  1
NHSTUB(Fgets_Fut                              ,0xff868a08) //  1
NHSTUB(Fopen_Fut                              ,0xff868848) //120
NHSTUB(Fread_Fut                              ,0xff868968) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814ce4) //  1
NHSTUB(Fseek_Fut                              ,0xff868a50) //120
NHSTUB(Fwrite_Fut                             ,0xff8689b8) //120
NHSTUB(GetBatteryTemperature                  ,0xff82d218) //102
NHSTUB(GetCCDTemperature                      ,0xff82d204) //102
//NHSTUB(GetCurrentAvValue                    ,0xffac401c) //120            == 0xffac401c
//NHSTUB(GetDrive_ClusterSize                 ,0xff86ed90) //119            == 0xff86ed90
//NHSTUB(GetDrive_FreeClusters                ,0xff86ee08) //1103            == 0xff86ee08
//NHSTUB(GetDrive_TotalClusters               ,0xff86edcc) //119            == 0xff86edcc
NHSTUB(GetOpticalTemperature                  ,0xff82d1f0) //120
NHSTUB(GetPropertyCase                        ,0xff8248e0) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffaa5f18) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaa5f2c) //102
NHSTUB(GiveSemaphore                          ,0xff821214) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff910478) //  1
NHSTUB(LEDDrive                               ,0xff82d770) //120
NHSTUB(LocalTime                              ,0xff814208) //115
NHSTUB(LockMainPower                          ,0xff972100) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8687d0) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffac63e0) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaa5df8) //120
NHSTUB(Open                                   ,0xff86f57c) //120
NHSTUB(PT_PlaySound                           ,0xff969540) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff96e030) //120
NHSTUB(PostLogicalEventToUI                   ,0xff96e0ac) //120
NHSTUB(Read                                   ,0xff86f638) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff988eec) //120
NHSTUB(RenameFile_Fut                         ,0xff8686c4) //  1
NHSTUB(Restart                                ,0xff822b34) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffac9c88) //102
NHSTUB(SetAutoShutdownTime                    ,0xff972004) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9a3274) //120
NHSTUB(SetFileAttributes                      ,0xff86f75c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff96fdf8) //1104
NHSTUB(SetPropertyCase                        ,0xff8247c4) //  1
//NHSTUB(SetScriptMode                        ,0xff96fe60) //120            == 0xff96fe60
NHSTUB(SleepTask                              ,0xff821530) //120
NHSTUB(TakeSemaphore                          ,0xff82102c) //1101
NHSTUB(TurnOffBackLight                       ,0xff9bb0ac) //  2
NHSTUB(TurnOnBackLight                        ,0xff9bb07c) //  2
NHSTUB(TurnOnDisplay                          ,0xff933ac0) //120
NHSTUB(TurnOffDisplay                         ,0xff933ad0) //120
NHSTUB(UnlockAE                               ,0xff95b590) //120
//NHSTUB(UnlockAF                             ,0xff95b464) //120            == 0xff95b464
NHSTUB(UnlockMainPower                        ,0xff972198) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86eac8) //  1
//NHSTUB(VbattGet                             ,0xff82c14c) //120            == 0xff82c14c
NHSTUB(Write                                  ,0xff86f644) //120
NHSTUB(_log                                   ,0xffb01b34) //121
NHSTUB(_log10                                 ,0xffafded4) //121
NHSTUB(_pow                                   ,0xffafe05c) //121
NHSTUB(_sqrt                                  ,0xffafff30) //  1
NHSTUB(apex2us                                ,0xff8b1db0) //  1
NHSTUB(close                                  ,0xffb0bf98) //109
NHSTUB(kbd_p1_f                               ,0xff826cf0) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826cfc) //109
NHSTUB(kbd_p2_f                               ,0xff8270d4) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff827a3c) //  1
NHSTUB(lseek                                  ,0xffb0c0dc) //  1
NHSTUB(memcmp                                 ,0xffb06ff4) //120
NHSTUB(memcpy                                 ,0xffb07030) //120
NHSTUB(memset                                 ,0xffb070a8) //120
NHSTUB(mkdir                                  ,0xff86f78c) //  1
NHSTUB(open                                   ,0xffb0c5dc) //109
NHSTUB(closedir                               ,0xffb09420) //  1
NHSTUB(qsort                                  ,0xffb06854) //  1
NHSTUB(rand                                   ,0xffb06878) //  1
NHSTUB(realloc                                ,0xffaf877c) //115
NHSTUB(srand                                  ,0xffb0689c) //  1
NHSTUB(stat                                   ,0xffb094e8) //  1
NHSTUB(strcat                                 ,0xffb070c8) //  1
NHSTUB(strchr                                 ,0xffb070f4) //  1
NHSTUB(strcmp                                 ,0xffb07118) //120
NHSTUB(strcpy                                 ,0xffb072ac) //120
NHSTUB(strftime                               ,0xffb08934) //  1
NHSTUB(strlen                                 ,0xffb07410) //120
NHSTUB(strncmp                                ,0xffb07474) //  1
NHSTUB(strncpy                                ,0xffb074b8) //  1
NHSTUB(strrchr                                ,0xffb0753c) //  1
NHSTUB(strtol                                 ,0xffb06c90) //  1
NHSTUB(isdigit                                ,0xffb034f4) //  1
NHSTUB(isspace                                ,0xffb0356c) //  1
NHSTUB(isalpha                                ,0xffb034c4) //  1
NHSTUB(isupper                                ,0xffb03584) //  1
NHSTUB(islower                                ,0xffb03524) //  1
NHSTUB(ispunct                                ,0xffb03554) //  1
NHSTUB(isxdigit                               ,0xffb0359c) //  1
NHSTUB(toupper                                ,0xffb035c4) //  1
NHSTUB(tolower                                ,0xffb035b4) //  1
NHSTUB(taskLock                               ,0xffb1ccdc) //  1
NHSTUB(taskUnlock                             ,0xffb1cd84) //  1
NHSTUB(taskName                               ,0xffb1c518) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb09bec) //  1
NHSTUB(readdir                                ,0xffb093ec) //  1
NHSTUB(strtoul                                ,0xffb06e38) //  1
NHSTUB(strpbrk                                ,0xffb07500) //  1
NHSTUB(utime                                  ,0xffb0957c) //  1
NHSTUB(mktime                                 ,0xffb07ddc) //  1
NHSTUB(opendir                                ,0xffb09454) //  1
NHSTUB(memchr                                 ,0xffb06fc0) //  1
NHSTUB(memPartInfoGet                         ,0xffb0f3f8) //  1
NHSTUB(iosDrvInstall                          ,0xffb0d47c) //  1
NHSTUB(iosDevAdd                              ,0xffb0d1b8) //  1
NHSTUB(iosDevDelete                           ,0xffb0d190) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffac6140) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb12658) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb12594) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86e978) //  1
NHSTUB(taskSuspend                            ,0xffb1c728) //  1
NHSTUB(taskResume                             ,0xffb1c8fc) //  1
NHSTUB(time                                   ,0xffb08960) //  1
NHSTUB(vsprintf                               ,0xffb0ad40) //115
NHSTUB(EngDrvRead                             ,0xff880514) //102
