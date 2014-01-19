// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.01B   // Found @ 0xff81a5c8, "GM1.01B" @ 0xff81a5d5
//   Firmware build timestamp: Jun 20 2006 09:21:45
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.12MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009c890

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff95d540) //  1 73%    *** != 0x00000000
NHSTUB(GetFocusLensSubjectDistance            ,0xffab4f48) //  1 54%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffab54e4) //  2 92%
NHSTUB(GetParameterData                       ,0xff976f30) //  1 86%
NHSTUB(GetSystemTime                          ,0xff814ee8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffac4198) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffac5d38) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac5d80) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac5d38) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffac5d80) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffac41e0) //  1 94%
//NHSTUB(Remove                               ,0xff8cae40) //  3 52%
NHSTUB(SetParameterData                       ,0xff976e50) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff9ae170) //  1 89%
NHSTUB(WriteSDCard                            ,0xff87dfd0) //  3 64%
NHSTUB(add_ptp_handler                        ,0xffa74c78) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81282c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffb0efdc
//NHSTUB(kbd_pwr_off                          ,0xff827f54) //  1 83%    *** != 0xff827f0c
// ALT: NHSTUB(kbd_pwr_off, 0xff827f70) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8291b8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8291d4) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff827f70) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828e60) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828e7c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828f68) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828f84) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829054) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829070) // 3 5/1
// ERROR: kbd_pwr_on is not found.                         //--- ---    *** != 0xff827ecc
NHSTUB(malloc                                 ,0xffb0efd0) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb1c618) //  1 82%
NHSTUB(localtime                              ,0xffb07c0c) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86e8d8) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xff95fdec

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff972364 -> ff972364
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff96b1cc) // Found @0xff96b1cc,          stubs_min = 0xff96b1cc (0xFF96B1CC)
//DEF(FlashParamsTable                        ,0xff974740) // Found @0xff974740,          stubs_min = 0xff974740 (0xFF974740)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xff976f9c

// Misc stuff
// LED table init @ 0xff82db60
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
NHSTUB(Close                                  ,0xff86f5a8) //120
NHSTUB(CreateTask                             ,0xff821620) //120
NHSTUB(DebugAssert                            ,0xff813b80) //1100
NHSTUB(DeleteFile_Fut                         ,0xff868748) //  1
NHSTUB(DoAELock                               ,0xff95b574) //120
//NHSTUB(DoAFLock                             ,0xff95b424) //120            == 0xff95b424
NHSTUB(ExecuteEventProcedure                  ,0xff816bc8) //  1
NHSTUB(ExitTask                               ,0xff8219e0) //120
NHSTUB(Fclose_Fut                             ,0xff868888) //120
NHSTUB(Feof_Fut                               ,0xff868a9c) //  1
NHSTUB(Fflush_Fut                             ,0xff868ad4) //  1
NHSTUB(Fgets_Fut                              ,0xff868a0c) //  1
NHSTUB(Fopen_Fut                              ,0xff86884c) //120
NHSTUB(Fread_Fut                              ,0xff86896c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814ce4) //  1
NHSTUB(Fseek_Fut                              ,0xff868a54) //120
NHSTUB(Fwrite_Fut                             ,0xff8689bc) //120
NHSTUB(GetBatteryTemperature                  ,0xff82d21c) //102
NHSTUB(GetCCDTemperature                      ,0xff82d208) //102
//NHSTUB(GetCurrentAvValue                    ,0xffac4014) //120            == 0xffac4014
//NHSTUB(GetDrive_ClusterSize                 ,0xff86ed94) //119            == 0xff86ed94
//NHSTUB(GetDrive_FreeClusters                ,0xff86ee0c) //1103            == 0xff86ee0c
//NHSTUB(GetDrive_TotalClusters               ,0xff86edd0) //119            == 0xff86edd0
NHSTUB(GetOpticalTemperature                  ,0xff82d1f4) //120
NHSTUB(GetPropertyCase                        ,0xff8248e4) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffaa5f10) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaa5f24) //102
NHSTUB(GiveSemaphore                          ,0xff821218) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff91047c) //  1
NHSTUB(LEDDrive                               ,0xff82d774) //120
NHSTUB(LocalTime                              ,0xff814208) //115
NHSTUB(LockMainPower                          ,0xff972104) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8687d4) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffac63d8) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaa5df0) //120
NHSTUB(Open                                   ,0xff86f580) //120
NHSTUB(PT_PlaySound                           ,0xff969544) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff96e034) //120
NHSTUB(PostLogicalEventToUI                   ,0xff96e0b0) //120
NHSTUB(Read                                   ,0xff86f63c) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff988ef0) //120
NHSTUB(RenameFile_Fut                         ,0xff8686c8) //  1
NHSTUB(Restart                                ,0xff822b38) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffac9c80) //102
NHSTUB(SetAutoShutdownTime                    ,0xff972008) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9a3278) //120
NHSTUB(SetFileAttributes                      ,0xff86f760) //  1
NHSTUB(SetLogicalEventActive                  ,0xff96fdfc) //1104
NHSTUB(SetPropertyCase                        ,0xff8247c8) //  1
//NHSTUB(SetScriptMode                        ,0xff96fe64) //120            == 0xff96fe64
NHSTUB(SleepTask                              ,0xff821534) //120
NHSTUB(TakeSemaphore                          ,0xff821030) //1101
NHSTUB(TurnOffBackLight                       ,0xff9bb0b0) //  2
NHSTUB(TurnOnBackLight                        ,0xff9bb080) //  2
NHSTUB(TurnOnDisplay                          ,0xff933ac4) //120
NHSTUB(TurnOffDisplay                         ,0xff933ad4) //120
NHSTUB(UnlockAE                               ,0xff95b594) //120
//NHSTUB(UnlockAF                             ,0xff95b468) //120            == 0xff95b468
NHSTUB(UnlockMainPower                        ,0xff97219c) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86eacc) //  1
//NHSTUB(VbattGet                             ,0xff82c150) //120            == 0xff82c150
NHSTUB(Write                                  ,0xff86f648) //120
NHSTUB(_log                                   ,0xffb01b2c) //121
NHSTUB(_log10                                 ,0xffafdecc) //121
NHSTUB(_pow                                   ,0xffafe054) //121
NHSTUB(_sqrt                                  ,0xffafff28) //  1
NHSTUB(apex2us                                ,0xff8b1db4) //  1
NHSTUB(close                                  ,0xffb0bf90) //109
NHSTUB(kbd_p1_f                               ,0xff826cf4) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826d00) //109
NHSTUB(kbd_p2_f                               ,0xff8270d8) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff827a40) //  1
NHSTUB(lseek                                  ,0xffb0c0d4) //  1
NHSTUB(memcmp                                 ,0xffb06fec) //120
NHSTUB(memcpy                                 ,0xffb07028) //120
NHSTUB(memset                                 ,0xffb070a0) //120
NHSTUB(mkdir                                  ,0xff86f790) //  1
NHSTUB(open                                   ,0xffb0c5d4) //109
NHSTUB(closedir                               ,0xffb09418) //  1
NHSTUB(qsort                                  ,0xffb0684c) //  1
NHSTUB(rand                                   ,0xffb06870) //  1
NHSTUB(realloc                                ,0xffaf8774) //115
NHSTUB(srand                                  ,0xffb06894) //  1
NHSTUB(stat                                   ,0xffb094e0) //  1
NHSTUB(strcat                                 ,0xffb070c0) //  1
NHSTUB(strchr                                 ,0xffb070ec) //  1
NHSTUB(strcmp                                 ,0xffb07110) //120
NHSTUB(strcpy                                 ,0xffb072a4) //120
NHSTUB(strftime                               ,0xffb0892c) //  1
NHSTUB(strlen                                 ,0xffb07408) //120
NHSTUB(strncmp                                ,0xffb0746c) //  1
NHSTUB(strncpy                                ,0xffb074b0) //  1
NHSTUB(strrchr                                ,0xffb07534) //  1
NHSTUB(strtol                                 ,0xffb06c88) //  1
NHSTUB(isdigit                                ,0xffb034ec) //  1
NHSTUB(isspace                                ,0xffb03564) //  1
NHSTUB(isalpha                                ,0xffb034bc) //  1
NHSTUB(isupper                                ,0xffb0357c) //  1
NHSTUB(islower                                ,0xffb0351c) //  1
NHSTUB(ispunct                                ,0xffb0354c) //  1
NHSTUB(isxdigit                               ,0xffb03594) //  1
NHSTUB(toupper                                ,0xffb035bc) //  1
NHSTUB(tolower                                ,0xffb035ac) //  1
NHSTUB(taskLock                               ,0xffb1ccd4) //  1
NHSTUB(taskUnlock                             ,0xffb1cd7c) //  1
NHSTUB(taskName                               ,0xffb1c510) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb09be4) //  1
NHSTUB(readdir                                ,0xffb093e4) //  1
NHSTUB(strtoul                                ,0xffb06e30) //  1
NHSTUB(strpbrk                                ,0xffb074f8) //  1
NHSTUB(utime                                  ,0xffb09574) //  1
NHSTUB(mktime                                 ,0xffb07dd4) //  1
NHSTUB(opendir                                ,0xffb0944c) //  1
NHSTUB(memchr                                 ,0xffb06fb8) //  1
NHSTUB(memPartInfoGet                         ,0xffb0f3f0) //  1
NHSTUB(iosDrvInstall                          ,0xffb0d474) //  1
NHSTUB(iosDevAdd                              ,0xffb0d1b0) //  1
NHSTUB(iosDevDelete                           ,0xffb0d188) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffac6138) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb12650) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb1258c) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86e97c) //  1
NHSTUB(taskSuspend                            ,0xffb1c720) //  1
NHSTUB(taskResume                             ,0xffb1c8f4) //  1
NHSTUB(time                                   ,0xffb08958) //  1
NHSTUB(vsprintf                               ,0xffb0ad38) //115
NHSTUB(EngDrvRead                             ,0xff880518) //102
