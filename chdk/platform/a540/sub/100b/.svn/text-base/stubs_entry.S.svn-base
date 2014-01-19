// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00B   // Found @ 0xffc0a204, "GM1.00B" @ 0xffc0a211
//   Firmware build timestamp: Jan 31 2006 11:02:45
//   Canon PowerShot A540

// Values for makefile.inc
//   PLATFORMID = 12571 (0x311b) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000922d0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xffd43ac8
//NHSTUB(ExitFromCompensationEVF              ,0xffd43b60) //  1 73%    *** != 0xffd43b28
NHSTUB(GetFocusLensSubjectDistance            ,0xffe8b798) //  1 54%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffe8bd34) //  2 92%
NHSTUB(GetParameterData                       ,0xffd5d738) //  1 86%
NHSTUB(GetSystemTime                          ,0xffc04b28) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffe972e0) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffe97328) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe976ec) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe9927c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe992c4) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe97328) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe976ec) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe9927c) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe992c4) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffe97734) //  1 94%
//NHSTUB(Remove                               ,0xffcb832c) //  3 52%
NHSTUB(SetParameterData                       ,0xffd5d658) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xffd93bdc) //  1 89%
//NHSTUB(WriteSDCard                          ,0xffc6cf38) //  3 64%    *** != 0xffc6d0e0
NHSTUB(add_ptp_handler                        ,0xffe46ddc) //  1 96%
NHSTUB(exmem_alloc                            ,0xffc02818) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffee0f70
NHSTUB(malloc                                 ,0xffee0f64) //  1 53%
NHSTUB(taskIdListGet                          ,0xffeedb8c) //  1 82%
NHSTUB(localtime                              ,0xffed9ba0) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffc5d768) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xffd4656c

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd588d4 -> ffd588d4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd517bc) // Found @0xffd517bc,          stubs_min = 0xffd517bc (0xFFD517BC)
//DEF(FlashParamsTable                        ,0xffd5af48) // Found @0xffd5af48,          stubs_min = 0xffd5af48 (0xFFD5AF48)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xffd5d7a4

// Misc stuff
// LED table init @ 0xffc1d988
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220094, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffef3df0, canon_data_len: 0xb910

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc048f0) //  1
NHSTUB(Close                                  ,0xffc5e4c4) //120
NHSTUB(CreateTask                             ,0xffc1125c) //120
NHSTUB(DebugAssert                            ,0xffc03ae8) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc57634) //  1
NHSTUB(DoAELock                               ,0xffd41dbc) //120
//NHSTUB(DoAFLock                             ,0xffd41c64) //120            == 0xffd41c64
NHSTUB(ExecuteEventProcedure                  ,0xffc06808) //  1
NHSTUB(ExitTask                               ,0xffc1161c) //120
NHSTUB(Fclose_Fut                             ,0xffc57774) //120
NHSTUB(Feof_Fut                               ,0xffc57988) //  1
NHSTUB(Fflush_Fut                             ,0xffc579c0) //  1
NHSTUB(Fgets_Fut                              ,0xffc578f8) //  1
NHSTUB(Fopen_Fut                              ,0xffc57738) //120
NHSTUB(Fread_Fut                              ,0xffc57858) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc04924) //  1
NHSTUB(Fseek_Fut                              ,0xffc57940) //120
NHSTUB(Fwrite_Fut                             ,0xffc578a8) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1d044) //102
NHSTUB(GetCCDTemperature                      ,0xffc1d030) //102
NHSTUB(GetCurrentAvValue                      ,0xffe972cc) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xffc5dc9c) //119            == 0xffc5dc9c
//NHSTUB(GetDrive_FreeClusters                ,0xffc5dd14) //1103            == 0xffc5dd14
//NHSTUB(GetDrive_TotalClusters               ,0xffc5dcd8) //119            == 0xffc5dcd8
NHSTUB(GetOpticalTemperature                  ,0xffc1d01c) //120
NHSTUB(GetPropertyCase                        ,0xffc144f0) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffe781a0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe781b4) //102
NHSTUB(GiveSemaphore                          ,0xffc10e54) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcfe554) //  1
NHSTUB(LEDDrive                               ,0xffc1d59c) //120
NHSTUB(LocalTime                              ,0xffc041b8) //115
NHSTUB(LockMainPower                          ,0xffd58674) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc576c0) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffe9991c) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe78080) //120
NHSTUB(Open                                   ,0xffc5e49c) //120
NHSTUB(PT_PlaySound                           ,0xffd4fb34) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd54630) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd546ac) //120
NHSTUB(Read                                   ,0xffc5e558) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd6f828) //120
NHSTUB(RenameFile_Fut                         ,0xffc575b4) //  1
NHSTUB(Restart                                ,0xffc12774) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffe9d1c4) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd58578) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd88b20) //120
NHSTUB(SetFileAttributes                      ,0xffc5e67c) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd563f8) //1104
NHSTUB(SetPropertyCase                        ,0xffc143d4) //  1
//NHSTUB(SetScriptMode                        ,0xffd56460) //120            == 0xffd56460
NHSTUB(SleepTask                              ,0xffc11170) //120
NHSTUB(TakeSemaphore                          ,0xffc10c6c) //1101
NHSTUB(TurnOffBackLight                       ,0xffda486c) //  2
NHSTUB(TurnOnBackLight                        ,0xffda483c) //  2
NHSTUB(TurnOnDisplay                          ,0xffd218fc) //120
NHSTUB(TurnOffDisplay                         ,0xffd2190c) //120
NHSTUB(UnlockAE                               ,0xffd41ddc) //120
//NHSTUB(UnlockAF                             ,0xffd41ca8) //120            == 0xffd41ca8
NHSTUB(UnlockMainPower                        ,0xffd5870c) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc5d9d4) //  1
//NHSTUB(VbattGet                             ,0xffc1c014) //120            == 0xffc1c014
NHSTUB(Write                                  ,0xffc5e564) //120
NHSTUB(_log                                   ,0xffed331c) //121
NHSTUB(_log10                                 ,0xffecf7f4) //121
NHSTUB(_pow                                   ,0xffecf97c) //121
NHSTUB(_sqrt                                  ,0xffed1718) //  1
NHSTUB(apex2us                                ,0xffc9f288) //  1
NHSTUB(close                                  ,0xffeddf24) //109
NHSTUB(kbd_p1_f                               ,0xffc1692c) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc16938) //109
NHSTUB(kbd_p2_f                               ,0xffc16d10) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc17730) //  1
NHSTUB(kbd_pwr_off                            ,0xffc17ce8) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17d18) // 1 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffc17d34) // 1 6/0
NHSTUB(kbd_pwr_on                             ,0xffc17cc0) //  1
NHSTUB(lseek                                  ,0xffede068) //  1
NHSTUB(memcmp                                 ,0xffed8f80) //120
NHSTUB(memcpy                                 ,0xffed8fbc) //120
NHSTUB(memset                                 ,0xffed9034) //120
NHSTUB(mkdir                                  ,0xffc5e6ac) //  1
NHSTUB(open                                   ,0xffede568) //109
NHSTUB(closedir                               ,0xffedb3ac) //  1
NHSTUB(qsort                                  ,0xffed87e0) //  1
NHSTUB(rand                                   ,0xffed8804) //  1
NHSTUB(realloc                                ,0xffec9fbc) //115
NHSTUB(srand                                  ,0xffed8828) //  1
NHSTUB(stat                                   ,0xffedb474) //  1
NHSTUB(strcat                                 ,0xffed9054) //  1
NHSTUB(strchr                                 ,0xffed9080) //  1
NHSTUB(strcmp                                 ,0xffed90a4) //120
NHSTUB(strcpy                                 ,0xffed9238) //120
NHSTUB(strftime                               ,0xffeda8c0) //  1
NHSTUB(strlen                                 ,0xffed939c) //120
NHSTUB(strncmp                                ,0xffed9400) //  1
NHSTUB(strncpy                                ,0xffed9444) //  1
NHSTUB(strrchr                                ,0xffed94c8) //  1
NHSTUB(strtol                                 ,0xffed8c1c) //  1
NHSTUB(isdigit                                ,0xffed5350) //  1
NHSTUB(isspace                                ,0xffed53c8) //  1
NHSTUB(isalpha                                ,0xffed5320) //  1
NHSTUB(isupper                                ,0xffed53e0) //  1
NHSTUB(islower                                ,0xffed5380) //  1
NHSTUB(ispunct                                ,0xffed53b0) //  1
NHSTUB(isxdigit                               ,0xffed53f8) //  1
NHSTUB(toupper                                ,0xffed5420) //  1
NHSTUB(tolower                                ,0xffed5410) //  1
NHSTUB(taskLock                               ,0xffeee248) //  1
NHSTUB(taskUnlock                             ,0xffeee2f0) //  1
NHSTUB(taskName                               ,0xffeeda84) //  1
NHSTUB(errnoOfTaskGet                         ,0xffedbb78) //  1
NHSTUB(readdir                                ,0xffedb378) //  1
NHSTUB(strtoul                                ,0xffed8dc4) //  1
NHSTUB(strpbrk                                ,0xffed948c) //  1
NHSTUB(utime                                  ,0xffedb508) //  1
NHSTUB(mktime                                 ,0xffed9d68) //  1
NHSTUB(opendir                                ,0xffedb3e0) //  1
NHSTUB(memchr                                 ,0xffed8f4c) //  1
NHSTUB(memPartInfoGet                         ,0xffee1384) //  1
NHSTUB(iosDrvInstall                          ,0xffedf408) //  1
NHSTUB(iosDevAdd                              ,0xffedf144) //  1
NHSTUB(iosDevDelete                           ,0xffedf11c) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffe9967c) //  1
NHSTUB(taskCreateHookAdd                      ,0xffee3bc4) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffee3b00) //  1
NHSTUB(Unmount_FileSystem                     ,0xffc5d880) //  1
NHSTUB(taskSuspend                            ,0xffeedc94) //  1
NHSTUB(taskResume                             ,0xffeede68) //  1
NHSTUB(time                                   ,0xffeda8ec) //  1
NHSTUB(vsprintf                               ,0xffedcccc) //115
NHSTUB(EngDrvRead                             ,0xffc6f478) //102
