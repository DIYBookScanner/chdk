// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00B   // Found @ 0xffc0a208, "GM1.00B" @ 0xffc0a215
//   Firmware build timestamp: Dec  6 2005 09:17:55
//   Canon PowerShot A420

// Values for makefile.inc
//   PLATFORMID = 12559 (0x310f) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x00ffffff
//   MEMISOSTART = 0x0009ef70

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xffd24990
//NHSTUB(ExitFromCompensationEVF              ,0xffd24a54) //  1 76%    *** != 0xffd249ec
NHSTUB(GetFocusLensSubjectDistance            ,0xffe5089c) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffe50e3c) //  3 52%
NHSTUB(GetParameterData                       ,0xffd3d590) //  1 86%
NHSTUB(GetSystemTime                          ,0xffc04b2c) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffe5c0c8) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffe5dc58) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe5dca0) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe5dc58) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe5dca0) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffe5c110) //  1 94%
//NHSTUB(Remove                               ,0xffcab248) //  3 52%
NHSTUB(SetParameterData                       ,0xffd3d4b0) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xffd72590) //  1 89%
//NHSTUB(WriteSDCard                          ,0xffc68eb8) //  3 64%    *** != 0xffc69060
NHSTUB(add_ptp_handler                        ,0xffe10fb4) //  1 96%
NHSTUB(exmem_alloc                            ,0xffc0281c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffea2a7c
//NHSTUB(kbd_pwr_off                          ,0xffc18214) //  1 83%    *** != 0x00000000
// ALT: NHSTUB(kbd_pwr_off, 0xffc18230) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17ebc) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17ed8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17fc4) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17fe0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffc180b0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffc180cc) // 3 5/1
// ERROR: kbd_pwr_on is not found.                         //--- ---    *** != 0x00000000
NHSTUB(malloc                                 ,0xffea2a70) //  1 53%
NHSTUB(taskIdListGet                          ,0xffeaf698) //  1 82%
// ALT: NHSTUB(taskIdListGet, 0xffed347c) // 1 24/5
NHSTUB(localtime                              ,0xffe9b6ac) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffc596cc) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xffd2737c

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd38ba0 -> ffd38ba0
// Mode  3614 in firmware but not in current modemap
// Mode  3615 in firmware but not in current modemap
// Mode  3616 in firmware but not in current modemap
// Mode  3618 in firmware but not in current modemap
// Current modemap entry not found in firmware - MODE_VIDEO_STD            3613

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd31ba0) // Found @0xffd31ba0,          stubs_min = 0xffd31ba0 (0xFFD31BA0)
//DEF(FlashParamsTable                        ,0xffd3adb0) // Found @0xffd3adb0,          stubs_min = 0xffd3adb0 (0xFFD3ADB0)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xffd3d5fc

// Misc stuff
// LED table init @ 0xffc1c988
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220084, offset 0x204
// LED #5: 0xc0220080, offset 0x244

// canon_data_src: 0xffeb60c0, canon_data_len: 0xceb0

// For capt_seq.c
DEF(_nrflag,0x5e64) // Found @ ffd2909c (0x5e64)
//static long *nrflag = (long*)(0x5e64);       // Found @ ffd2909c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc048f4) //  1
NHSTUB(Close                                  ,0xffc5a42c) //120
NHSTUB(CreateTask                             ,0xffc11260) //120
NHSTUB(DebugAssert                            ,0xffc03aec) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc535c8) //  1
NHSTUB(DoAELock                               ,0xffd22cf0) //120
//NHSTUB(DoAFLock                             ,0xffd22ba0) //120            == 0xffd22ba0
NHSTUB(ExecuteEventProcedure                  ,0xffc0680c) //  1
NHSTUB(ExitTask                               ,0xffc11620) //120
NHSTUB(Fclose_Fut                             ,0xffc53708) //120
NHSTUB(Feof_Fut                               ,0xffc5391c) //  1
NHSTUB(Fflush_Fut                             ,0xffc53954) //  1
NHSTUB(Fgets_Fut                              ,0xffc5388c) //  1
NHSTUB(Fopen_Fut                              ,0xffc536cc) //120
NHSTUB(Fread_Fut                              ,0xffc537ec) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc04928) //  1
NHSTUB(Fseek_Fut                              ,0xffc538d4) //120
NHSTUB(Fwrite_Fut                             ,0xffc5383c) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1c044) //102
NHSTUB(GetCCDTemperature                      ,0xffc1c030) //102
NHSTUB(GetCurrentAvValue                      ,0xffe5bf44) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xffc59c04) //119            == 0xffc59c04
NHSTUB(GetDrive_FreeClusters                  ,0xffc59c7c) //1103
//NHSTUB(GetDrive_TotalClusters               ,0xffc59c40) //119            == 0xffc59c40
NHSTUB(GetOpticalTemperature                  ,0xffc1c01c) //120
NHSTUB(GetPropertyCase                        ,0xffc14518) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffe41344) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe41358) //102
NHSTUB(GiveSemaphore                          ,0xffc10e58) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffce4958) //  1
NHSTUB(LEDDrive                               ,0xffc1c59c) //120
NHSTUB(LocalTime                              ,0xffc041bc) //115
NHSTUB(LockMainPower                          ,0xffd38918) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc53654) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffe5e2f4) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe41224) //120
NHSTUB(Open                                   ,0xffc5a404) //120
NHSTUB(PT_PlaySound                           ,0xffd300ac) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd34a10) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd34a8c) //120
NHSTUB(Read                                   ,0xffc5a4c0) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd4eae0) //120
NHSTUB(RenameFile_Fut                         ,0xffc53548) //  1
NHSTUB(Restart                                ,0xffc1277c) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffe617a8) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd38810) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd6750c) //120
NHSTUB(SetFileAttributes                      ,0xffc5a5e4) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd367e8) //1104
NHSTUB(SetPropertyCase                        ,0xffc143ec) //  1
//NHSTUB(SetScriptMode                        ,0xffd36850) //120            == 0xffd36850
NHSTUB(SleepTask                              ,0xffc11174) //120
NHSTUB(TakeSemaphore                          ,0xffc10c70) //1101
NHSTUB(TurnOffBackLight                       ,0xffd7e1f0) //  2
NHSTUB(TurnOnBackLight                        ,0xffd7e1c0) //  2
NHSTUB(TurnOnDisplay                          ,0xffd07964) //120
NHSTUB(TurnOffDisplay                         ,0xffd07974) //120
NHSTUB(UnlockAE                               ,0xffd22d10) //120
//NHSTUB(UnlockAF                             ,0xffd22be4) //120            == 0xffd22be4
NHSTUB(UnlockMainPower                        ,0xffd389cc) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc59938) //  1
//NHSTUB(VbattGet                             ,0xffc1b014) //120            == 0xffc1b014
NHSTUB(Write                                  ,0xffc5a4cc) //120
NHSTUB(_log                                   ,0xffe9381c) //121
NHSTUB(_log10                                 ,0xffe8fcf4) //121
NHSTUB(_pow                                   ,0xffe8fe7c) //121
NHSTUB(_sqrt                                  ,0xffe91c18) //  1
NHSTUB(apex2us                                ,0xffc93b4c) //  1
NHSTUB(close                                  ,0xffe9fa30) //109
NHSTUB(kbd_p1_f                               ,0xffc16910) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc1691c) //109
NHSTUB(kbd_p2_f                               ,0xffc16cec) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc17618) //  1
NHSTUB(lseek                                  ,0xffe9fb74) //  1
NHSTUB(memcmp                                 ,0xffe9aa8c) //120
NHSTUB(memcpy                                 ,0xffe9aac8) //120
NHSTUB(memset                                 ,0xffe9ab40) //120
NHSTUB(mkdir                                  ,0xffc5a614) //  1
NHSTUB(open                                   ,0xffea0074) //109
NHSTUB(closedir                               ,0xffe9ceb8) //  1
NHSTUB(qsort                                  ,0xffe9a2ec) //  1
NHSTUB(rand                                   ,0xffe9a310) //  1
NHSTUB(realloc                                ,0xffe8a5f4) //115
NHSTUB(srand                                  ,0xffe9a334) //  1
NHSTUB(stat                                   ,0xffe9cf80) //  1
NHSTUB(strcat                                 ,0xffe9ab60) //  1
NHSTUB(strchr                                 ,0xffe9ab8c) //  1
NHSTUB(strcmp                                 ,0xffe9abb0) //120
NHSTUB(strcpy                                 ,0xffe9ad44) //120
NHSTUB(strftime                               ,0xffe9c3cc) //  1
NHSTUB(strlen                                 ,0xffe9aea8) //120
NHSTUB(strncmp                                ,0xffe9af0c) //  1
NHSTUB(strncpy                                ,0xffe9af50) //  1
NHSTUB(strrchr                                ,0xffe9afd4) //  1
NHSTUB(strtol                                 ,0xffe9a728) //  1
NHSTUB(isdigit                                ,0xffe96f8c) //  1
NHSTUB(isspace                                ,0xffe97004) //  1
NHSTUB(isalpha                                ,0xffe96f5c) //  1
NHSTUB(isupper                                ,0xffe9701c) //  1
NHSTUB(islower                                ,0xffe96fbc) //  1
NHSTUB(ispunct                                ,0xffe96fec) //  1
NHSTUB(isxdigit                               ,0xffe97034) //  1
NHSTUB(toupper                                ,0xffe9705c) //  1
NHSTUB(tolower                                ,0xffe9704c) //  1
NHSTUB(taskLock                               ,0xffeafd54) //  1
// ALT: NHSTUB(taskLock, 0xffed3b38) // 1 31/0
NHSTUB(taskUnlock                             ,0xffeafdfc) //  1
// ALT: NHSTUB(taskUnlock, 0xffed3be0) // 1 31/0
NHSTUB(taskName                               ,0xffeaf590) //  1
// ALT: NHSTUB(taskName, 0xffed3374) // 1 25/0
NHSTUB(errnoOfTaskGet                         ,0xffe9d684) //  1
NHSTUB(readdir                                ,0xffe9ce84) //  1
NHSTUB(strtoul                                ,0xffe9a8d0) //  1
NHSTUB(strpbrk                                ,0xffe9af98) //  1
NHSTUB(utime                                  ,0xffe9d014) //  1
NHSTUB(mktime                                 ,0xffe9b874) //  1
NHSTUB(opendir                                ,0xffe9ceec) //  1
NHSTUB(memchr                                 ,0xffe9aa58) //  1
NHSTUB(memPartInfoGet                         ,0xffea2e90) //  1
NHSTUB(iosDrvInstall                          ,0xffea0f14) //  1
NHSTUB(iosDevAdd                              ,0xffea0c50) //  1
NHSTUB(iosDevDelete                           ,0xffea0c28) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffe5e054) //  1
NHSTUB(taskCreateHookAdd                      ,0xffea56d0) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffea560c) //  1
NHSTUB(Unmount_FileSystem                     ,0xffc597e4) //  1
NHSTUB(taskSuspend                            ,0xffeaf7a0) //  1
// ALT: NHSTUB(taskSuspend, 0xffed3584) // 1 31/0
NHSTUB(taskResume                             ,0xffeaf974) //  1
// ALT: NHSTUB(taskResume, 0xffed3758) // 1 31/0
NHSTUB(time                                   ,0xffe9c3f8) //  1
NHSTUB(vsprintf                               ,0xffe9e7d8) //115
NHSTUB(EngDrvRead                             ,0xffc6b3f8) //102
