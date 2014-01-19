// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00A   // Found @ 0xff81a5c4, "GM1.00A" @ 0xff81a5d1
//   Firmware build timestamp: Jan 23 2006 19:44:50
//   Canon DIGITAL IXUS 65

// Values for makefile.inc
//   PLATFORMID = 12542 (0x30fe) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009c6b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff95ebd0) //  1 70%    *** != 0x00000000
//NHSTUB(GetDrive_FreeClusters                ,0xff86fdd0) //1103        *** != 0xff868ad4
NHSTUB(GetFocusLensSubjectDistance            ,0xffabed90) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffabf330) //  3 92%
NHSTUB(GetParameterData                       ,0xff9786ac) //  1 86%
NHSTUB(GetSystemTime                          ,0xff814ee8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffacaac4) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffacc654) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffacc69c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffacc654) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffacc69c) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffacab0c) //  1 94%
//NHSTUB(Remove                               ,0xff8cbe04) //  3 52%
NHSTUB(SetParameterData                       ,0xff9785cc) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff9b1680) //  1 89%
NHSTUB(WriteSDCard                            ,0xff87ef94) //  3 64%
NHSTUB(add_ptp_handler                        ,0xffa7e780) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81282c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffb1551c
//NHSTUB(kbd_pwr_off                          ,0xff827fdc) //  1 83%    *** != 0xff827ff8
// ALT: NHSTUB(kbd_pwr_off, 0xff827ff8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a1a4) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a1c0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff827ff8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829e4c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829e68) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829f54) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829f70) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a040) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a05c) // 3 5/1
// ERROR: kbd_pwr_on is not found.                         //--- ---    *** != 0xff827fdc
NHSTUB(malloc                                 ,0xffb15510) //  1 53%
//NHSTUB(realloc                              ,0xffafe640) //115        *** != 0xffb1475c
NHSTUB(taskIdListGet                          ,0xffb22b58) //  1 82%
NHSTUB(localtime                              ,0xffb0e14c) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86f89c) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff973ad4 -> ff973ad4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff96c760) // Found @0xff96c760,          stubs_min = 0xff96c760 (0xFF96C760)
//DEF(FlashParamsTable                        ,0xff975eb0) // Found @0xff975eb0,          stubs_min = 0xff975eb0 (0xFF975EB0)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xff978718

// Misc stuff
// LED table init @ 0xff82eb64
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220098, offset 0xc4
// LED #4: 0xc0220084, offset 0x204
// LED #5: 0xc0220080, offset 0x244

// canon_data_src: 0xffb29580, canon_data_len: 0xbde0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814cb0) //  1
NHSTUB(Close                                  ,0xff87056c) //120
NHSTUB(CreateTask                             ,0xff82161c) //120
NHSTUB(DebugAssert                            ,0xff813b80) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86970c) //  1
NHSTUB(DoAELock                               ,0xff95cc0c) //120
//NHSTUB(DoAFLock                             ,0xff95cabc) //120            == 0xff95cabc
NHSTUB(ExecuteEventProcedure                  ,0xff816bc8) //  1
NHSTUB(ExitTask                               ,0xff8219dc) //120
NHSTUB(Fclose_Fut                             ,0xff86984c) //120
NHSTUB(Feof_Fut                               ,0xff869a60) //  1
NHSTUB(Fflush_Fut                             ,0xff869a98) //  1
NHSTUB(Fgets_Fut                              ,0xff8699d0) //  1
NHSTUB(Fopen_Fut                              ,0xff869810) //120
NHSTUB(Fread_Fut                              ,0xff869930) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814ce4) //  1
NHSTUB(Fseek_Fut                              ,0xff869a18) //120
NHSTUB(Fwrite_Fut                             ,0xff869980) //120
NHSTUB(GetBatteryTemperature                  ,0xff82e220) //102
NHSTUB(GetCCDTemperature                      ,0xff82e20c) //102
NHSTUB(GetCurrentAvValue                      ,0xffaca940) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff86fd58) //119            == 0xff86fd58
//NHSTUB(GetDrive_TotalClusters               ,0xff86fd94) //119            == 0xff86fd94
NHSTUB(GetOpticalTemperature                  ,0xff82e1f8) //120
NHSTUB(GetPropertyCase                        ,0xff8248e0) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffaafa08) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaafa1c) //102
NHSTUB(GiveSemaphore                          ,0xff821214) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff9112ec) //  1
NHSTUB(LEDDrive                               ,0xff82e778) //120
NHSTUB(LocalTime                              ,0xff814208) //115
NHSTUB(LockMainPower                          ,0xff973874) //120
NHSTUB(MakeDirectory_Fut                      ,0xff869798) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffacccf0) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaaf8e8) //120
NHSTUB(Open                                   ,0xff870544) //120
NHSTUB(PT_PlaySound                           ,0xff96aa98) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff96f5c8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff96f644) //120
NHSTUB(Read                                   ,0xff870600) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff98a644) //120
NHSTUB(RenameFile_Fut                         ,0xff86968c) //  1
NHSTUB(Restart                                ,0xff822b34) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffad0598) //102
NHSTUB(SetAutoShutdownTime                    ,0xff973778) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9a66a0) //120
NHSTUB(SetFileAttributes                      ,0xff870724) //  1
NHSTUB(SetLogicalEventActive                  ,0xff971544) //1104
NHSTUB(SetPropertyCase                        ,0xff8247c4) //  1
//NHSTUB(SetScriptMode                        ,0xff9715ac) //120            == 0xff9715ac
NHSTUB(SleepTask                              ,0xff821530) //120
NHSTUB(TakeSemaphore                          ,0xff82102c) //1101
NHSTUB(TurnOffBackLight                       ,0xff9be4e8) //  2
NHSTUB(TurnOnBackLight                        ,0xff9be4b8) //  2
NHSTUB(TurnOnDisplay                          ,0xff9348e8) //120
NHSTUB(TurnOffDisplay                         ,0xff9348f8) //120
NHSTUB(UnlockAE                               ,0xff95cc2c) //120
//NHSTUB(UnlockAF                             ,0xff95cb00) //120            == 0xff95cb00
NHSTUB(UnlockMainPower                        ,0xff97390c) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86fa90) //  1
//NHSTUB(VbattGet                             ,0xff82d154) //120            == 0xff82d154
NHSTUB(Write                                  ,0xff87060c) //120
NHSTUB(_log                                   ,0xffb079f8) //121
NHSTUB(_log10                                 ,0xffb03d98) //121
NHSTUB(_pow                                   ,0xffb03f20) //121
NHSTUB(_sqrt                                  ,0xffb05df4) //  1
NHSTUB(apex2us                                ,0xff8b2d78) //  1
NHSTUB(close                                  ,0xffb124d0) //109
NHSTUB(kbd_p1_f                               ,0xff826cec) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826cf8) //109
NHSTUB(kbd_p2_f                               ,0xff8270d0) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff827aac) //  1
NHSTUB(lseek                                  ,0xffb12614) //  1
NHSTUB(memcmp                                 ,0xffb0d52c) //120
NHSTUB(memcpy                                 ,0xffb0d568) //120
NHSTUB(memset                                 ,0xffb0d5e0) //120
NHSTUB(mkdir                                  ,0xff870754) //  1
NHSTUB(open                                   ,0xffb12b14) //109
NHSTUB(closedir                               ,0xffb0f958) //  1
NHSTUB(qsort                                  ,0xffb0cd8c) //  1
NHSTUB(rand                                   ,0xffb0cdb0) //  1
NHSTUB(srand                                  ,0xffb0cdd4) //  1
NHSTUB(stat                                   ,0xffb0fa20) //  1
NHSTUB(strcat                                 ,0xffb0d600) //  1
NHSTUB(strchr                                 ,0xffb0d62c) //  1
NHSTUB(strcmp                                 ,0xffb0d650) //120
NHSTUB(strcpy                                 ,0xffb0d7e4) //120
NHSTUB(strftime                               ,0xffb0ee6c) //  1
NHSTUB(strlen                                 ,0xffb0d948) //120
NHSTUB(strncmp                                ,0xffb0d9ac) //  1
NHSTUB(strncpy                                ,0xffb0d9f0) //  1
NHSTUB(strrchr                                ,0xffb0da74) //  1
NHSTUB(strtol                                 ,0xffb0d1c8) //  1
NHSTUB(isdigit                                ,0xffb09a2c) //  1
NHSTUB(isspace                                ,0xffb09aa4) //  1
NHSTUB(isalpha                                ,0xffb099fc) //  1
NHSTUB(isupper                                ,0xffb09abc) //  1
NHSTUB(islower                                ,0xffb09a5c) //  1
NHSTUB(ispunct                                ,0xffb09a8c) //  1
NHSTUB(isxdigit                               ,0xffb09ad4) //  1
NHSTUB(toupper                                ,0xffb09afc) //  1
NHSTUB(tolower                                ,0xffb09aec) //  1
NHSTUB(taskLock                               ,0xffb23214) //  1
NHSTUB(taskUnlock                             ,0xffb232bc) //  1
NHSTUB(taskName                               ,0xffb22a50) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb10124) //  1
NHSTUB(readdir                                ,0xffb0f924) //  1
NHSTUB(strtoul                                ,0xffb0d370) //  1
NHSTUB(strpbrk                                ,0xffb0da38) //  1
NHSTUB(utime                                  ,0xffb0fab4) //  1
NHSTUB(mktime                                 ,0xffb0e314) //  1
NHSTUB(opendir                                ,0xffb0f98c) //  1
NHSTUB(memchr                                 ,0xffb0d4f8) //  1
NHSTUB(memPartInfoGet                         ,0xffb15930) //  1
NHSTUB(iosDrvInstall                          ,0xffb139b4) //  1
NHSTUB(iosDevAdd                              ,0xffb136f0) //  1
NHSTUB(iosDevDelete                           ,0xffb136c8) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffacca50) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb18b90) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb18acc) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86f940) //  1
NHSTUB(taskSuspend                            ,0xffb22c60) //  1
NHSTUB(taskResume                             ,0xffb22e34) //  1
NHSTUB(time                                   ,0xffb0ee98) //  1
NHSTUB(vsprintf                               ,0xffb11278) //115
NHSTUB(EngDrvRead                             ,0xff8814dc) //102
