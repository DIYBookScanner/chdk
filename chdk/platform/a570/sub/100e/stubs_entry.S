// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00E   // Found @ 0xffc08024, "GM1.00E" @ 0xffc08031
//   Firmware build timestamp: Jan 12 2007 13:33:40
//   Canon PowerShot A570 IS

// Values for makefile.inc
//   PLATFORMID = 12620 (0x314c) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a6c30

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(FreeUncacheableMemory                  ,0xffc0e5d4) //  1 90%
NHSTUB(GetFocusLensSubjectDistance            ,0xffe71b8c) //  1 90%
NHSTUB(GetParameterData                       ,0xffee3d30) //  1 86%
NHSTUB(GetPropertyCase                        ,0xffc0bc94) //  2 89%
NHSTUB(GetSystemTime                          ,0xffc036e8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffe060f0) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffe06138) //  1 94%
NHSTUB(Restart                                ,0xffc0b748) //  1 96%
NHSTUB(SetParameterData                       ,0xffee3c50) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xffc22c2c) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffd9b9d8) //  1 96%
NHSTUB(exmem_alloc                            ,0xffc0e2ac) //  2 93%
NHSTUB(kbd_p2_f                               ,0xffde6298) //  1 56%
NHSTUB(kbd_pwr_on                             ,0xffde7bac) //  1 88%
NHSTUB(malloc                                 ,0xffcd9b78) //  1 53%
NHSTUB(mkdir                                  ,0xffe46dc0) //  1 51%
// ALT: NHSTUB(mkdir, 0xffe46e94) // 1 16/15
NHSTUB(taskIdListGet                          ,0xffce3cc0) //  1 82%
NHSTUB(utime                                  ,0xffefa040) //  1 57%
NHSTUB(localtime                              ,0xffcd2990) //  1 93%
NHSTUB(MakeAFScan                             ,0xffeaa230) //  2 86%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffee5e94 -> ffee5e94
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffed9260) // Found @0xffed9260,          stubs_min = 0xffed9260 (0xFFED9260)
//DEF(FlashParamsTable                        ,0xffee8478) // Found @0xffee8478,          stubs_min = 0xffee8478 (0xFFEE8478)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6f; }                          // Found @0xffee3d9c

// Misc stuff
// LED table init @ 0xffde5b9c
// LED #1: 0xc02200cc, offset 0x4
// LED #2: 0xc02200c8, offset 0x44
// LED #3: 0xc02200d0, offset 0x84
// LED #4: 0xc02200d4, offset 0xc4
// LED #5: 0xc02200c4, offset 0x204
// LED #6: 0xc02200c0, offset 0x244

// canon_data_src: 0xfff2d320, canon_data_len: 0xbf70

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc0e5a0) //  1
NHSTUB(Close                                  ,0xffe46b58) //120
NHSTUB(CreateTask                             ,0xffebe874) //120
NHSTUB(DebugAssert                            ,0xffeca7b0) //1100
NHSTUB(DeleteFile_Fut                         ,0xffe4212c) //  1
NHSTUB(DoAELock                               ,0xffea511c) //120
NHSTUB(DoAFLock                               ,0xffea4bdc) //120
NHSTUB(EnterToCompensationEVF                 ,0xffea4f84) //  3
NHSTUB(ExecuteEventProcedure                  ,0xffc04a54) //  1
NHSTUB(ExitFromCompensationEVF                ,0xffea5008) //  3
NHSTUB(ExitTask                               ,0xffebec34) //120
NHSTUB(Fclose_Fut                             ,0xffe422a0) //120
NHSTUB(Feof_Fut                               ,0xffe4249c) //  3
NHSTUB(Fflush_Fut                             ,0xffe424d8) //  3
NHSTUB(Fgets_Fut                              ,0xffe42404) //  3
NHSTUB(Fopen_Fut                              ,0xffe42260) //120
NHSTUB(Fread_Fut                              ,0xffe4235c) //120
NHSTUB(Fseek_Fut                              ,0xffe42450) //120
NHSTUB(Fwrite_Fut                             ,0xffe423b0) //120
NHSTUB(GetBatteryTemperature                  ,0xffdeac78) //102
NHSTUB(GetCCDTemperature                      ,0xffdeac64) //102
NHSTUB(GetCurrentAvValue                      ,0xffe05c74) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffe46344) //119
NHSTUB(GetDrive_FreeClusters                  ,0xffe463bc) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xffe46380) //119
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffe72080) //  3
NHSTUB(GetOpticalTemperature                  ,0xffdeac50) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffe86db8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe86dcc) //102
NHSTUB(GiveSemaphore                          ,0xffebe440) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffd5e208) //  2
NHSTUB(LEDDrive                               ,0xffde57b0) //120
NHSTUB(LocalTime                              ,0xffecb0c4) //115
NHSTUB(LockMainPower                          ,0xffee0ba4) //120
NHSTUB(MakeDirectory_Fut                      ,0xffe421e0) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffe0860c) //102
NHSTUB(MoveIrisWithAv                         ,0xffe79ab4) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe86c90) //120
NHSTUB(Open                                   ,0xffe46b30) //120
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffeb587c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffeb5840) //120
NHSTUB(PT_PlaySound                           ,0xffeb5340) //  3
NHSTUB(PostLogicalEventForNotPowerType        ,0xffedc7cc) //120
NHSTUB(PostLogicalEventToUI                   ,0xffedc848) //120
NHSTUB(Read                                   ,0xffe46bec) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffcc646c) //120
NHSTUB(RenameFile_Fut                         ,0xffe42084) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffe0b70c) //102
NHSTUB(SetAutoShutdownTime                    ,0xffee0aa8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc17d10) //120
NHSTUB(SetFileAttributes                      ,0xffe46d40) //  3
NHSTUB(SetLogicalEventActive                  ,0xffede6b0) //1104
NHSTUB(SetPropertyCase                        ,0xffc0bb5c) //  3
//NHSTUB(SetScriptMode                        ,0xffede714) //120            == 0xffede714
NHSTUB(SleepTask                              ,0xffebe788) //120
NHSTUB(TakeSemaphore                          ,0xffebe238) //1101
NHSTUB(TurnOffBackLight                       ,0xffc34d70) //  2
NHSTUB(TurnOnBackLight                        ,0xffc34d40) //  2
NHSTUB(TurnOnDisplay                          ,0xffddb0f0) //120
NHSTUB(TurnOffDisplay                         ,0xffddb100) //120
NHSTUB(UnlockAE                               ,0xffea516c) //120
NHSTUB(UnlockAF                               ,0xffea4c5c) //120
NHSTUB(UnlockMainPower                        ,0xffee0c3c) //120
NHSTUB(UpdateMBROnFlash                       ,0xffe46078) //  1
NHSTUB(VbattGet                               ,0xffde398c) //120
NHSTUB(Write                                  ,0xffe46bf8) //120
NHSTUB(WriteSDCard                            ,0xffe58eec) //  3
NHSTUB(_log                                   ,0xffef8824) //121
NHSTUB(_log10                                 ,0xffef7ca4) //121
NHSTUB(_pow                                   ,0xffcca3b0) //121
NHSTUB(_sqrt                                  ,0xffccc270) //  1
NHSTUB(apex2us                                ,0xffceb000) //  1
NHSTUB(close                                  ,0xffcd6b38) //109
NHSTUB(exmem_free                             ,0xffc0e4fc) //102
NHSTUB(free                                   ,0xffcd9b84) //  3
NHSTUB(kbd_p1_f                               ,0xffde5e68) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffde5e74) //109
NHSTUB(kbd_read_keys_r2                       ,0xffde74f0) //  3
NHSTUB(kbd_pwr_off                            ,0xffde7bd4) //  3
// ALT: NHSTUB(kbd_pwr_off, 0xffde7c04) // 3 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffde7c20) // 3 6/0
NHSTUB(lseek                                  ,0xffcd6c7c) //  1
NHSTUB(memcmp                                 ,0xffcd1d70) //120
NHSTUB(memcpy                                 ,0xffcd1dac) //120
NHSTUB(memset                                 ,0xffcd1e24) //120
NHSTUB(open                                   ,0xffcd717c) //109
NHSTUB(closedir                               ,0xffef9ee4) //  1
NHSTUB(qsort                                  ,0xffcd15d0) //  1
NHSTUB(rand                                   ,0xffcd15f4) //  1
NHSTUB(realloc                                ,0xffeca3bc) //115
NHSTUB(srand                                  ,0xffcd1618) //  1
NHSTUB(stat                                   ,0xffef9fac) //  1
NHSTUB(strcat                                 ,0xffcd1e44) //  1
NHSTUB(strchr                                 ,0xffcd1e70) //  1
NHSTUB(strcmp                                 ,0xffcd1e94) //120
NHSTUB(strcpy                                 ,0xffcd2028) //120
NHSTUB(strftime                               ,0xffcd36b0) //  1
NHSTUB(strlen                                 ,0xffcd218c) //120
NHSTUB(strncmp                                ,0xffcd21f0) //  1
NHSTUB(strncpy                                ,0xffcd2234) //  1
NHSTUB(strrchr                                ,0xffcd22b8) //  1
NHSTUB(strtol                                 ,0xffcd1a0c) //  1
NHSTUB(isdigit                                ,0xffcce140) //  1
NHSTUB(isspace                                ,0xffcce1b8) //  1
NHSTUB(isalpha                                ,0xffcce110) //  1
NHSTUB(isupper                                ,0xffcce1d0) //  1
NHSTUB(islower                                ,0xffcce170) //  1
NHSTUB(ispunct                                ,0xffcce1a0) //  1
NHSTUB(isxdigit                               ,0xffcce1e8) //  1
NHSTUB(toupper                                ,0xffcce210) //  1
NHSTUB(tolower                                ,0xffcce200) //  1
NHSTUB(taskLock                               ,0xffce437c) //  1
NHSTUB(taskUnlock                             ,0xffce4424) //  1
NHSTUB(taskName                               ,0xffce3bb8) //  1
NHSTUB(errnoOfTaskGet                         ,0xffcd478c) //  1
NHSTUB(readdir                                ,0xffef9eb0) //  1
NHSTUB(strtoul                                ,0xffcd1bb4) //  1
NHSTUB(strpbrk                                ,0xffcd227c) //  1
NHSTUB(mktime                                 ,0xffcd2b58) //  1
NHSTUB(opendir                                ,0xffef9f18) //  1
NHSTUB(memchr                                 ,0xffcd1d3c) //  1
NHSTUB(memPartInfoGet                         ,0xffcd9f98) //  1
NHSTUB(iosDrvInstall                          ,0xffcd801c) //  1
NHSTUB(iosDevAdd                              ,0xffcd7d58) //  1
NHSTUB(iosDevDelete                           ,0xffcd7d30) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffe08374) //  1
NHSTUB(taskCreateHookAdd                      ,0xffcdc7d8) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffcdc714) //  1
NHSTUB(Mount_FileSystem                       ,0xffe45e7c) //  3
NHSTUB(Unmount_FileSystem                     ,0xffe45f24) //  1
NHSTUB(taskSuspend                            ,0xffce3dc8) //  1
NHSTUB(taskResume                             ,0xffce3f9c) //  1
NHSTUB(time                                   ,0xffcd36dc) //  1
NHSTUB(vsprintf                               ,0xffcd58e0) //115
NHSTUB(EngDrvRead                             ,0xffdf3374) //102
