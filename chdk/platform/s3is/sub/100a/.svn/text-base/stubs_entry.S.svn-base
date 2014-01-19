// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00A   // Found @ 0xff81a5c4, "GM1.00A" @ 0xff81a5d1
//   Firmware build timestamp: Feb 22 2006 08:47:32
//   Canon PowerShot S3 IS

// Values for makefile.inc
//   PLATFORMID = 12570 (0x311a) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00096410

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xff978b78
//NHSTUB(ExitFromCompensationEVF              ,0xff97a594) //  2 66%    *** != 0xff978bd8
NHSTUB(GetFocusLensSubjectDistance            ,0xffaf007c) //  1 83%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffaf05f4) //  3 52%
NHSTUB(GetParameterData                       ,0xff994b68) //  1 86%
NHSTUB(GetSystemTime                          ,0xff814ee8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffb0a54c) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffb0a594) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0a958) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0c1cc) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0c214) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0a594) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0a958) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0c1cc) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffb0c214) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffb0a9a0) //  1 94%
//NHSTUB(Remove                               ,0xff8cf9d0) //  3 52%
NHSTUB(SetParameterData                       ,0xff994a88) //  1 86%
//NHSTUB(WriteSDCard                          ,0xff87fe50) //  3 67%    *** != 0xff87fff8
NHSTUB(add_ptp_handler                        ,0xffab0098) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81282c) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffb571e4
//NHSTUB(kbd_read_keys_r2                     ,0xff827bf0) //  1 57%    *** != 0xff827bc0
//NHSTUB(kbd_pwr_off                          ,0xff82956c) //  1 83%    *** != 0xff829214
// ALT: NHSTUB(kbd_pwr_off, 0xff829588) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829214) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829230) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82931c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829338) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829408) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829424) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xff944170) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff94419c) // 1 5/4
NHSTUB(malloc                                 ,0xffb571d8) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb64820) //  1 82%
NHSTUB(localtime                              ,0xffb4fe14) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff870190) //  1 73%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff98f378 -> ff98f378
// Mode  8218 in firmware but not in current modemap
// Mode  4125 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9881e0) // Found @0xff9881e0,          stubs_min = 0xff9881e0 (0xFF9881E0)
//DEF(FlashParamsTable                        ,0xff991894) // Found @0xff991894,          stubs_min = 0xff991894 (0xFF991894)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xff994bd4

// Misc stuff
// LED table init @ 0xff82dce8
// LED #1: 0xc022008c, offset 0x104
// LED #2: 0xc0220088, offset 0x144
// LED #3: 0xc02200fc, offset 0x1c4

// canon_data_src: 0xffb6b240, canon_data_len: 0xc890

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814cb0) //  1
NHSTUB(Close                                  ,0xff8713c4) //120
NHSTUB(CreateTask                             ,0xff821658) //120
NHSTUB(DebugAssert                            ,0xff813b80) //1100
NHSTUB(DeleteFile_Fut                         ,0xff869fc4) //  1
NHSTUB(DoAELock                               ,0xff97662c) //120
//NHSTUB(DoAFLock                             ,0xff9764ac) //120            == 0xff9764ac
NHSTUB(ExecuteEventProcedure                  ,0xff816bc8) //  1
NHSTUB(ExitTask                               ,0xff821a18) //120
NHSTUB(Fclose_Fut                             ,0xff86a104) //120
NHSTUB(Feof_Fut                               ,0xff86a318) //  1
NHSTUB(Fflush_Fut                             ,0xff86a350) //  1
NHSTUB(Fgets_Fut                              ,0xff86a288) //  1
NHSTUB(Fopen_Fut                              ,0xff86a0c8) //120
NHSTUB(Fread_Fut                              ,0xff86a1e8) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814ce4) //  1
NHSTUB(Fseek_Fut                              ,0xff86a2d0) //120
NHSTUB(Fwrite_Fut                             ,0xff86a238) //120
NHSTUB(GetBatteryTemperature                  ,0xff82d37c) //102
NHSTUB(GetCCDTemperature                      ,0xff82d368) //102
NHSTUB(GetCurrentAvValue                      ,0xffb0a538) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff870710) //119            == 0xff870710
//NHSTUB(GetDrive_FreeClusters                ,0xff8707a8) //1103            == 0xff8707a8
//NHSTUB(GetDrive_TotalClusters               ,0xff87076c) //119            == 0xff87076c
NHSTUB(GetOpticalTemperature                  ,0xff82d354) //120
NHSTUB(GetPropertyCase                        ,0xff82498c) //  1
//NHSTUB(GetZoomLensCurrentPoint              ,0xffae8460) //120            == 0xffae8460
//NHSTUB(GetZoomLensCurrentPosition           ,0xffae8474) //102            == 0xffae8474
NHSTUB(GiveSemaphore                          ,0xff821250) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff91d8c0) //  1
NHSTUB(LEDDrive                               ,0xff82d8d4) //120
NHSTUB(LocalTime                              ,0xff814208) //115
NHSTUB(LockMainPower                          ,0xff98f118) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86a050) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffb0c824) //102
//NHSTUB(MoveZoomLensWithPoint                ,0xffae8280) //120            == 0xffae8280
NHSTUB(Open                                   ,0xff87139c) //120
NHSTUB(PT_PlaySound                           ,0xff986518) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff98b048) //120
NHSTUB(PostLogicalEventToUI                   ,0xff98b0c4) //120
NHSTUB(Read                                   ,0xff871458) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff9a7b10) //120
NHSTUB(RenameFile_Fut                         ,0xff869f44) //  1
NHSTUB(Restart                                ,0xff822bd8) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffb100cc) //102
NHSTUB(SetAutoShutdownTime                    ,0xff98f01c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9c3db8) //120
NHSTUB(SetFileAttributes                      ,0xff87157c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff98ce10) //1104
NHSTUB(SetPropertyCase                        ,0xff824870) //  1
//NHSTUB(SetScriptMode                        ,0xff98ce78) //120            == 0xff98ce78
NHSTUB(SleepTask                              ,0xff82156c) //120
NHSTUB(TakeSemaphore                          ,0xff821068) //1101
NHSTUB(TurnOffBackLight                       ,0xff9e6b2c) //  2
NHSTUB(TurnOnBackLight                        ,0xff9e6afc) //  2
NHSTUB(TurnOnDisplay                          ,0xff941068) //120
NHSTUB(TurnOffDisplay                         ,0xff941078) //120
NHSTUB(UnlockAE                               ,0xff97664c) //120
//NHSTUB(UnlockAF                             ,0xff976518) //120            == 0xff976518
NHSTUB(UnlockMainPower                        ,0xff98f1b0) //120
NHSTUB(UpdateMBROnFlash                       ,0xff8703ec) //  1
//NHSTUB(VbattGet                             ,0xff82c328) //120            == 0xff82c328
NHSTUB(Write                                  ,0xff871464) //120
NHSTUB(_log                                   ,0xffb496c0) //121
NHSTUB(_log10                                 ,0xffb45a60) //121
NHSTUB(_pow                                   ,0xffb45be8) //121
NHSTUB(_sqrt                                  ,0xffb47abc) //  1
NHSTUB(apex2us                                ,0xff8b6348) //  1
NHSTUB(close                                  ,0xffb54198) //109
NHSTUB(kbd_p1_f                               ,0xff826d64) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff826d70) //109
NHSTUB(kbd_p2_f                               ,0xff827140) //  1
NHSTUB(lseek                                  ,0xffb542dc) //  1
NHSTUB(memcmp                                 ,0xffb4f1f4) //120
NHSTUB(memcpy                                 ,0xffb4f230) //120
NHSTUB(memset                                 ,0xffb4f2a8) //120
NHSTUB(mkdir                                  ,0xff8715ac) //  1
NHSTUB(open                                   ,0xffb547dc) //109
NHSTUB(closedir                               ,0xffb51620) //  1
NHSTUB(qsort                                  ,0xffb4ea54) //  1
NHSTUB(rand                                   ,0xffb4ea78) //  1
NHSTUB(realloc                                ,0xffb3eb34) //115
NHSTUB(srand                                  ,0xffb4ea9c) //  1
NHSTUB(stat                                   ,0xffb516e8) //  1
NHSTUB(strcat                                 ,0xffb4f2c8) //  1
NHSTUB(strchr                                 ,0xffb4f2f4) //  1
NHSTUB(strcmp                                 ,0xffb4f318) //120
NHSTUB(strcpy                                 ,0xffb4f4ac) //120
NHSTUB(strftime                               ,0xffb50b34) //  1
NHSTUB(strlen                                 ,0xffb4f610) //120
NHSTUB(strncmp                                ,0xffb4f674) //  1
NHSTUB(strncpy                                ,0xffb4f6b8) //  1
NHSTUB(strrchr                                ,0xffb4f73c) //  1
NHSTUB(strtol                                 ,0xffb4ee90) //  1
NHSTUB(isdigit                                ,0xffb4b6f4) //  1
NHSTUB(isspace                                ,0xffb4b76c) //  1
NHSTUB(isalpha                                ,0xffb4b6c4) //  1
NHSTUB(isupper                                ,0xffb4b784) //  1
NHSTUB(islower                                ,0xffb4b724) //  1
NHSTUB(ispunct                                ,0xffb4b754) //  1
NHSTUB(isxdigit                               ,0xffb4b79c) //  1
NHSTUB(toupper                                ,0xffb4b7c4) //  1
NHSTUB(tolower                                ,0xffb4b7b4) //  1
NHSTUB(taskLock                               ,0xffb64edc) //  1
NHSTUB(taskUnlock                             ,0xffb64f84) //  1
NHSTUB(taskName                               ,0xffb64718) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb51dec) //  1
NHSTUB(readdir                                ,0xffb515ec) //  1
NHSTUB(strtoul                                ,0xffb4f038) //  1
NHSTUB(strpbrk                                ,0xffb4f700) //  1
NHSTUB(utime                                  ,0xffb5177c) //  1
NHSTUB(mktime                                 ,0xffb4ffdc) //  1
NHSTUB(opendir                                ,0xffb51654) //  1
NHSTUB(memchr                                 ,0xffb4f1c0) //  1
NHSTUB(memPartInfoGet                         ,0xffb575f8) //  1
NHSTUB(iosDrvInstall                          ,0xffb5567c) //  1
NHSTUB(iosDevAdd                              ,0xffb553b8) //  1
NHSTUB(iosDevDelete                           ,0xffb55390) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffb0c584) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb5a858) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb5a794) //  1
NHSTUB(Unmount_FileSystem                     ,0xff870244) //  1
NHSTUB(taskSuspend                            ,0xffb64928) //  1
NHSTUB(taskResume                             ,0xffb64afc) //  1
NHSTUB(time                                   ,0xffb50b60) //  1
NHSTUB(vsprintf                               ,0xffb52f40) //115
NHSTUB(EngDrvRead                             ,0xff8824d4) //102
