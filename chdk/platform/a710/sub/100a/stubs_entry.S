// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00A   // Found @ 0xffc0a398, "GM1.00A" @ 0xffc0a3a5
//   Firmware build timestamp: Jun 20 2006 13:26:27
//   Possible corrupt firmware dump - file size too small for start address 0xffc00000
//     file size = 3.12MB, should be 4.00MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009f9b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(Remove                               ,0xffcc0be4) //  3 52%
NHSTUB(Restart                                ,0xffc12fdc) //  1 96%
NHSTUB(UnsetZoomForMovie                      ,0xffda9138) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffe59fe4) //  1 96%
NHSTUB(taskIdListGet                          ,0xfff0d6e8) //  1 82%
NHSTUB(localtime                              ,0xffef96fc) //  1 93%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd711a8 -> ffd711a8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd69bbc) // Found @0xffd69bbc,          stubs_min = 0xffd69bbc (0xFFD69BBC)
//DEF(FlashParamsTable                        ,0xffd73a14) // Found @0xffd73a14,          stubs_min = 0xffd73a14 (0xFFD73A14)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6e; }                          // Found @0xffd760fc

// Misc stuff
// LED table init @ 0xffc1db44
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220094, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xfff13950, canon_data_len: 0xbd80

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc04b00) //  1
NHSTUB(Close                                  ,0xffc60fc4) //120
NHSTUB(CreateTask                             ,0xffc11abc) //120
NHSTUB(DebugAssert                            ,0xffc03cf8) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc59e74) //  1
NHSTUB(DoAELock                               ,0xffd58fa8) //120
NHSTUB(DoAFLock                               ,0xffd58dbc) //120
NHSTUB(EnterToCompensationEVF                 ,0xffd58f08) //  2
NHSTUB(ExecuteEventProcedure                  ,0xffc0699c) //  1
NHSTUB(ExitFromCompensationEVF                ,0xffd5c524) //  2
NHSTUB(ExitTask                               ,0xffc11e7c) //120
NHSTUB(Fclose_Fut                             ,0xffc59fb4) //120
NHSTUB(Feof_Fut                               ,0xffc5a1c8) //  1
NHSTUB(Fflush_Fut                             ,0xffc5a200) //  1
NHSTUB(Fgets_Fut                              ,0xffc5a138) //  1
NHSTUB(Fopen_Fut                              ,0xffc59f78) //120
NHSTUB(Fread_Fut                              ,0xffc5a098) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc04b34) //  1
NHSTUB(Fseek_Fut                              ,0xffc5a180) //120
NHSTUB(Fwrite_Fut                             ,0xffc5a0e8) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1d200) //102
NHSTUB(GetCCDTemperature                      ,0xffc1d1ec) //102
NHSTUB(GetCurrentAvValue                      ,0xffeb3d50) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xffc607b0) //119            == 0xffc607b0
//NHSTUB(GetDrive_FreeClusters                ,0xffc60828) //1103            == 0xffc60828
NHSTUB(GetDrive_TotalClusters                 ,0xffc607ec) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xffea2f3c) //  2
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffea34f0) //  2
NHSTUB(GetOpticalTemperature                  ,0xffc1d1d8) //120
NHSTUB(GetParameterData                       ,0xffd76090) //  2
NHSTUB(GetPropertyCase                        ,0xffc14dec) //  2
NHSTUB(GetSystemTime                          ,0xffc04d38) //  2
NHSTUB(GetZoomLensCurrentPoint                ,0xffe8f670) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe8f684) //102
NHSTUB(GiveSemaphore                          ,0xffc116b4) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffd11b24) //  2
NHSTUB(LEDDrive                               ,0xffc1d758) //120
NHSTUB(LocalTime                              ,0xffc043c8) //115
NHSTUB(LockMainPower                          ,0xffd70f48) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc59f00) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffeb64d4) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe8f550) //120
NHSTUB(Open                                   ,0xffc60f9c) //120
NHSTUB(PT_PlaySound                           ,0xffd67db8) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd6ccc8) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd6cd44) //120
NHSTUB(PutInNdFilter                          ,0xffeb41d8) //  2
NHSTUB(PutOutNdFilter                         ,0xffeb4220) //  2
NHSTUB(Read                                   ,0xffc61058) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd8752c) //120
NHSTUB(RenameFile_Fut                         ,0xffc59df4) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffeb9144) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd70e4c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd9da1c) //120
NHSTUB(SetFileAttributes                      ,0xffc611ec) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd6eab0) //1104
NHSTUB(SetParameterData                       ,0xffd75fb0) //  2
NHSTUB(SetPropertyCase                        ,0xffc14c9c) //  2
//NHSTUB(SetScriptMode                        ,0xffd6eb18) //120            == 0xffd6eb18
NHSTUB(SleepTask                              ,0xffc119d0) //120
NHSTUB(TakeSemaphore                          ,0xffc114cc) //1101
NHSTUB(TurnOffBackLight                       ,0xffdbd750) //  2
NHSTUB(TurnOnBackLight                        ,0xffdbd720) //  2
NHSTUB(TurnOnDisplay                          ,0xffd36450) //120
NHSTUB(TurnOffDisplay                         ,0xffd36460) //120
NHSTUB(UnlockAE                               ,0xffd58fc8) //120
NHSTUB(UnlockAF                               ,0xffd58e08) //120
NHSTUB(UnlockMainPower                        ,0xffd70fe0) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc604e4) //  1
NHSTUB(VbattGet                               ,0xffc1c12c) //120
NHSTUB(Write                                  ,0xffc61064) //120
NHSTUB(WriteSDCard                            ,0xffc702a4) //  2
NHSTUB(_log                                   ,0xffef34ec) //121
NHSTUB(_log10                                 ,0xffeef88c) //121
NHSTUB(_pow                                   ,0xffeefa14) //121
NHSTUB(_sqrt                                  ,0xffef18e8) //  1
NHSTUB(apex2us                                ,0xffca5104) //  1
NHSTUB(close                                  ,0xffefda80) //109
NHSTUB(exmem_alloc                            ,0xffc02834) //  2
NHSTUB(free                                   ,0xfff00acc) //  2
NHSTUB(kbd_p1_f                               ,0xffc17468) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc17474) //109
NHSTUB(kbd_p2_f                               ,0xffc1784c) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc1829c) //  1
NHSTUB(kbd_pwr_off                            ,0xffc18828) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xffc18858) // 1 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffc18874) // 1 6/0
NHSTUB(kbd_pwr_on                             ,0xffc18800) //  1
NHSTUB(lseek                                  ,0xffefdbc4) //  1
NHSTUB(malloc                                 ,0xfff00ac0) //  2
NHSTUB(memcmp                                 ,0xffef8adc) //120
NHSTUB(memcpy                                 ,0xffef8b18) //120
NHSTUB(memset                                 ,0xffef8b90) //120
NHSTUB(mkdir                                  ,0xffc6121c) //  1
NHSTUB(open                                   ,0xffefe0c4) //109
NHSTUB(closedir                               ,0xffefaf08) //  1
NHSTUB(qsort                                  ,0xffef833c) //  1
NHSTUB(rand                                   ,0xffef8360) //  1
NHSTUB(realloc                                ,0xffee9a6c) //115
NHSTUB(srand                                  ,0xffef8384) //  1
NHSTUB(stat                                   ,0xffefafd0) //  1
NHSTUB(strcat                                 ,0xffef8bb0) //  1
NHSTUB(strchr                                 ,0xffef8bdc) //  1
NHSTUB(strcmp                                 ,0xffef8c00) //120
NHSTUB(strcpy                                 ,0xffef8d94) //120
NHSTUB(strftime                               ,0xffefa41c) //  1
NHSTUB(strlen                                 ,0xffef8ef8) //120
NHSTUB(strncmp                                ,0xffef8f5c) //  1
NHSTUB(strncpy                                ,0xffef8fa0) //  1
NHSTUB(strrchr                                ,0xffef9024) //  1
NHSTUB(strtol                                 ,0xffef8778) //  1
NHSTUB(isdigit                                ,0xffef4eac) //  1
NHSTUB(isspace                                ,0xffef4f24) //  1
NHSTUB(isalpha                                ,0xffef4e7c) //  1
NHSTUB(isupper                                ,0xffef4f3c) //  1
NHSTUB(islower                                ,0xffef4edc) //  1
NHSTUB(ispunct                                ,0xffef4f0c) //  1
NHSTUB(isxdigit                               ,0xffef4f54) //  1
NHSTUB(toupper                                ,0xffef4f7c) //  1
NHSTUB(tolower                                ,0xffef4f6c) //  1
NHSTUB(taskLock                               ,0xfff0dda4) //  1
NHSTUB(taskUnlock                             ,0xfff0de4c) //  1
NHSTUB(taskName                               ,0xfff0d5e0) //  1
NHSTUB(errnoOfTaskGet                         ,0xffefb6d4) //  1
NHSTUB(readdir                                ,0xffefaed4) //  1
NHSTUB(strtoul                                ,0xffef8920) //  1
NHSTUB(strpbrk                                ,0xffef8fe8) //  1
NHSTUB(utime                                  ,0xffefb064) //  1
NHSTUB(mktime                                 ,0xffef98c4) //  1
NHSTUB(opendir                                ,0xffefaf3c) //  1
NHSTUB(memchr                                 ,0xffef8aa8) //  1
NHSTUB(memPartInfoGet                         ,0xfff00ee0) //  1
NHSTUB(iosDrvInstall                          ,0xffefef64) //  1
NHSTUB(iosDevAdd                              ,0xffefeca0) //  1
NHSTUB(iosDevDelete                           ,0xffefec78) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffeb6234) //  1
NHSTUB(taskCreateHookAdd                      ,0xfff03720) //  1
NHSTUB(taskDeleteHookAdd                      ,0xfff0365c) //  1
NHSTUB(Mount_FileSystem                       ,0xffc602ec) //  2
NHSTUB(Unmount_FileSystem                     ,0xffc60390) //  1
NHSTUB(MakeAFScan                             ,0xffd5d538) //  2
NHSTUB(taskSuspend                            ,0xfff0d7f0) //  1
NHSTUB(taskResume                             ,0xfff0d9c4) //  1
NHSTUB(time                                   ,0xffefa448) //  1
NHSTUB(vsprintf                               ,0xffefc828) //115
NHSTUB(EngDrvRead                             ,0xffc72984) //102
