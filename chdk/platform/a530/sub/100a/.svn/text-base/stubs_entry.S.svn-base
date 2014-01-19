// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00A   // Found @ 0xffc0a204, "GM1.00A" @ 0xffc0a211
//   Firmware build timestamp: Dec 14 2005 09:32:59
//   Canon PowerShot A530

// Values for makefile.inc
//   PLATFORMID = 12582 (0x3126) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00091c70

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xffd33148
//NHSTUB(ExitFromCompensationEVF              ,0xffd331e0) //  1 73%    *** != 0xffd331a8
NHSTUB(GetFocusLensSubjectDistance            ,0xffe76038) //  1 54%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffe765d4) //  2 92%
NHSTUB(GetParameterData                       ,0xffd4cce4) //  1 86%
NHSTUB(GetSystemTime                          ,0xffc04b28) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffe81ca0) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffe83830) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe83878) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe83830) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe83878) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffe81ce8) //  1 94%
//NHSTUB(Remove                               ,0xffcafce8) //  3 52%
NHSTUB(SetParameterData                       ,0xffd4cc04) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xffd82d00) //  1 89%
//NHSTUB(WriteSDCard                          ,0xffc6cf24) //  3 64%    *** != 0xffc6d0cc
NHSTUB(add_ptp_handler                        ,0xffe35eac) //  1 96%
NHSTUB(exmem_alloc                            ,0xffc02818) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffecb53c
NHSTUB(malloc                                 ,0xffecb530) //  1 53%
NHSTUB(taskIdListGet                          ,0xffed8158) //  1 82%
NHSTUB(localtime                              ,0xffec416c) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffc5d754) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xffd35c10

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd47fc4 -> ffd47fc4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd40eac) // Found @0xffd40eac,          stubs_min = 0xffd40eac (0xFFD40EAC)
//DEF(FlashParamsTable                        ,0xffd4a45c) // Found @0xffd4a45c,          stubs_min = 0xffd4a45c (0xFFD4A45C)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xffd4cd50

// Misc stuff
// LED table init @ 0xffc1d974
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220094, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffede3c0, canon_data_len: 0xb8d0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc048f0) //  1
NHSTUB(Close                                  ,0xffc5e4b0) //120
NHSTUB(CreateTask                             ,0xffc1125c) //120
NHSTUB(DebugAssert                            ,0xffc03ae8) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc57620) //  1
NHSTUB(DoAELock                               ,0xffd3143c) //120
//NHSTUB(DoAFLock                             ,0xffd312e4) //120            == 0xffd312e4
NHSTUB(ExecuteEventProcedure                  ,0xffc06808) //  1
NHSTUB(ExitTask                               ,0xffc1161c) //120
NHSTUB(Fclose_Fut                             ,0xffc57760) //120
NHSTUB(Feof_Fut                               ,0xffc57974) //  1
NHSTUB(Fflush_Fut                             ,0xffc579ac) //  1
NHSTUB(Fgets_Fut                              ,0xffc578e4) //  1
NHSTUB(Fopen_Fut                              ,0xffc57724) //120
NHSTUB(Fread_Fut                              ,0xffc57844) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc04924) //  1
NHSTUB(Fseek_Fut                              ,0xffc5792c) //120
NHSTUB(Fwrite_Fut                             ,0xffc57894) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1d030) //102
NHSTUB(GetCCDTemperature                      ,0xffc1d01c) //102
NHSTUB(GetCurrentAvValue                      ,0xffe81b1c) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xffc5dc88) //119            == 0xffc5dc88
//NHSTUB(GetDrive_FreeClusters                ,0xffc5dd00) //1103            == 0xffc5dd00
//NHSTUB(GetDrive_TotalClusters               ,0xffc5dcc4) //119            == 0xffc5dcc4
NHSTUB(GetOpticalTemperature                  ,0xffc1d008) //120
NHSTUB(GetPropertyCase                        ,0xffc144f0) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffe6709c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe670b0) //102
NHSTUB(GiveSemaphore                          ,0xffc10e54) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffced918) //  1
NHSTUB(LEDDrive                               ,0xffc1d588) //120
NHSTUB(LocalTime                              ,0xffc041b8) //115
NHSTUB(LockMainPower                          ,0xffd47d64) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc576ac) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffe83ed0) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe66f7c) //120
NHSTUB(Open                                   ,0xffc5e488) //120
NHSTUB(PT_PlaySound                           ,0xffd3f224) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd43d20) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd43d9c) //120
NHSTUB(Read                                   ,0xffc5e544) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd5e944) //120
NHSTUB(RenameFile_Fut                         ,0xffc575a0) //  1
NHSTUB(Restart                                ,0xffc12774) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffe87778) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd47c68) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd77c3c) //120
NHSTUB(SetFileAttributes                      ,0xffc5e668) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd45ae8) //1104
NHSTUB(SetPropertyCase                        ,0xffc143d4) //  1
//NHSTUB(SetScriptMode                        ,0xffd45b50) //120            == 0xffd45b50
NHSTUB(SleepTask                              ,0xffc11170) //120
NHSTUB(TakeSemaphore                          ,0xffc10c6c) //1101
NHSTUB(TurnOffBackLight                       ,0xffd93808) //  2
NHSTUB(TurnOnBackLight                        ,0xffd937d8) //  2
NHSTUB(TurnOnDisplay                          ,0xffd10f48) //120
NHSTUB(TurnOffDisplay                         ,0xffd10f58) //120
NHSTUB(UnlockAE                               ,0xffd3145c) //120
//NHSTUB(UnlockAF                             ,0xffd31328) //120            == 0xffd31328
NHSTUB(UnlockMainPower                        ,0xffd47dfc) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc5d9c0) //  1
//NHSTUB(VbattGet                             ,0xffc1c000) //120            == 0xffc1c000
NHSTUB(Write                                  ,0xffc5e550) //120
NHSTUB(_log                                   ,0xffebd934) //121
NHSTUB(_log10                                 ,0xffeb9e0c) //121
NHSTUB(_pow                                   ,0xffeb9f94) //121
NHSTUB(_sqrt                                  ,0xffebbd30) //  1
NHSTUB(apex2us                                ,0xffc985ec) //  1
NHSTUB(close                                  ,0xffec84f0) //109
NHSTUB(kbd_p1_f                               ,0xffc16918) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc16924) //109
NHSTUB(kbd_p2_f                               ,0xffc16cfc) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc1771c) //  1
NHSTUB(kbd_pwr_off                            ,0xffc17cd4) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17d04) // 1 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffc17d20) // 1 6/0
NHSTUB(kbd_pwr_on                             ,0xffc17cac) //  1
NHSTUB(lseek                                  ,0xffec8634) //  1
NHSTUB(memcmp                                 ,0xffec354c) //120
NHSTUB(memcpy                                 ,0xffec3588) //120
NHSTUB(memset                                 ,0xffec3600) //120
NHSTUB(mkdir                                  ,0xffc5e698) //  1
NHSTUB(open                                   ,0xffec8b34) //109
NHSTUB(closedir                               ,0xffec5978) //  1
NHSTUB(qsort                                  ,0xffec2dac) //  1
NHSTUB(rand                                   ,0xffec2dd0) //  1
NHSTUB(realloc                                ,0xffeb45a8) //115
NHSTUB(srand                                  ,0xffec2df4) //  1
NHSTUB(stat                                   ,0xffec5a40) //  1
NHSTUB(strcat                                 ,0xffec3620) //  1
NHSTUB(strchr                                 ,0xffec364c) //  1
NHSTUB(strcmp                                 ,0xffec3670) //120
NHSTUB(strcpy                                 ,0xffec3804) //120
NHSTUB(strftime                               ,0xffec4e8c) //  1
NHSTUB(strlen                                 ,0xffec3968) //120
NHSTUB(strncmp                                ,0xffec39cc) //  1
NHSTUB(strncpy                                ,0xffec3a10) //  1
NHSTUB(strrchr                                ,0xffec3a94) //  1
NHSTUB(strtol                                 ,0xffec31e8) //  1
NHSTUB(isdigit                                ,0xffebf91c) //  1
NHSTUB(isspace                                ,0xffebf994) //  1
NHSTUB(isalpha                                ,0xffebf8ec) //  1
NHSTUB(isupper                                ,0xffebf9ac) //  1
NHSTUB(islower                                ,0xffebf94c) //  1
NHSTUB(ispunct                                ,0xffebf97c) //  1
NHSTUB(isxdigit                               ,0xffebf9c4) //  1
NHSTUB(toupper                                ,0xffebf9ec) //  1
NHSTUB(tolower                                ,0xffebf9dc) //  1
NHSTUB(taskLock                               ,0xffed8814) //  1
NHSTUB(taskUnlock                             ,0xffed88bc) //  1
NHSTUB(taskName                               ,0xffed8050) //  1
NHSTUB(errnoOfTaskGet                         ,0xffec6144) //  1
NHSTUB(readdir                                ,0xffec5944) //  1
NHSTUB(strtoul                                ,0xffec3390) //  1
NHSTUB(strpbrk                                ,0xffec3a58) //  1
NHSTUB(utime                                  ,0xffec5ad4) //  1
NHSTUB(mktime                                 ,0xffec4334) //  1
NHSTUB(opendir                                ,0xffec59ac) //  1
NHSTUB(memchr                                 ,0xffec3518) //  1
NHSTUB(memPartInfoGet                         ,0xffecb950) //  1
NHSTUB(iosDrvInstall                          ,0xffec99d4) //  1
NHSTUB(iosDevAdd                              ,0xffec9710) //  1
NHSTUB(iosDevDelete                           ,0xffec96e8) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffe83c30) //  1
NHSTUB(taskCreateHookAdd                      ,0xffece190) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffece0cc) //  1
NHSTUB(Unmount_FileSystem                     ,0xffc5d86c) //  1
NHSTUB(taskSuspend                            ,0xffed8260) //  1
NHSTUB(taskResume                             ,0xffed8434) //  1
NHSTUB(time                                   ,0xffec4eb8) //  1
NHSTUB(vsprintf                               ,0xffec7298) //115
NHSTUB(EngDrvRead                             ,0xffc6f464) //102
