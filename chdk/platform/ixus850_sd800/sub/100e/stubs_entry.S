// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00E   // Found @ 0xff81a84c, "GM1.00E" @ 0xff81a859
//   Firmware build timestamp: Oct  4 2006 10:07:45
//   Canon DIGITAL IXUS 850 IS

// Values for makefile.inc
//   PLATFORMID = 12598 (0x3136) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000ba7b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xff9954ec) //  2 90%
//NHSTUB(ExitFromCompensationEVF              ,0xff998b8c) //  2 66%    *** != 0xff99552c
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff998be8) // 2 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff998ca4) // 2 20/10
NHSTUB(GetFocusLensSubjectDistance            ,0xffb021e8) //  1 83%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffb02754) //  2 92%
NHSTUB(GetPropertyCase                        ,0xff825a14) //  2 92%
NHSTUB(GetSystemTime                          ,0xff8151ec) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffb134a4) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffb134ec) //  1 94%
//NHSTUB(Remove                               ,0xff8e6314) //  3 52%
NHSTUB(Restart                                ,0xff823c00) //  1 96%
NHSTUB(UnsetZoomForMovie                      ,0xff9e9470) //  1 89%
//NHSTUB(WriteSDCard                          ,0xff889560) //  2 93%    *** != 0xff8896fc
NHSTUB(add_ptp_handler                        ,0xffabd06c) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffb617c0
//NHSTUB(kbd_pwr_off                          ,0xff829354) //  1 83%    *** != 0xff82930c
// ALT: NHSTUB(kbd_pwr_off, 0xff829370) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a4e8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a504) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829370) // 3 5/1
//NHSTUB(kbd_pwr_on                           ,0xff961d24) //  1 55%    *** != 0xff8292cc
// ALT: NHSTUB(kbd_pwr_on, 0xff961d50) // 1 5/4
NHSTUB(malloc                                 ,0xffb617b4) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb6e3dc) //  1 82%
NHSTUB(localtime                              ,0xffb5a3f0) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff879734) //  1 90%
NHSTUB(MakeAFScan                             ,0xff999cf8) //  2 79%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff9ae2e0 -> ff9ae2e0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9a6cec) // Found @0xff9a6cec,          stubs_min = 0xff9a6cec (0xFF9A6CEC)
//DEF(FlashParamsTable                        ,0xff9b0860) // Found @0xff9b0860,          stubs_min = 0xff9b0860 (0xFF9B0860)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6e; }                          // Found @0xff9b2f00

// Misc stuff
// LED table init @ 0xff82ee34
// LED #1: 0xc02200cc, offset 0x4
// LED #2: 0xc02200c8, offset 0x44
// LED #3: 0xc02200d0, offset 0x84
// LED #4: 0xc02200d8, offset 0xc4
// LED #5: 0xc02200c4, offset 0x204
// LED #6: 0xc02200c0, offset 0x244

// canon_data_src: 0xffb74640, canon_data_len: 0xcbb0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814fb4) //  1
NHSTUB(Close                                  ,0xff87a40c) //120
NHSTUB(CreateTask                             ,0xff8226e0) //120
NHSTUB(DebugAssert                            ,0xff813e84) //1100
NHSTUB(DeleteFile_Fut                         ,0xff8732cc) //  1
NHSTUB(DoAELock                               ,0xff995584) //120
NHSTUB(DoAFLock                               ,0xff995318) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816e50) //  1
NHSTUB(ExitTask                               ,0xff822aa0) //120
NHSTUB(Fclose_Fut                             ,0xff873440) //120
NHSTUB(Feof_Fut                               ,0xff87363c) //  3
NHSTUB(Fflush_Fut                             ,0xff873678) //  3
NHSTUB(Fgets_Fut                              ,0xff8735a4) //  3
NHSTUB(Fopen_Fut                              ,0xff873400) //120
NHSTUB(Fread_Fut                              ,0xff8734fc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814fe8) //  1
NHSTUB(Fseek_Fut                              ,0xff8735f0) //120
NHSTUB(Fwrite_Fut                             ,0xff873550) //120
NHSTUB(GetBatteryTemperature                  ,0xff82e4f0) //102
NHSTUB(GetCCDTemperature                      ,0xff82e4dc) //102
NHSTUB(GetCurrentAvValue                      ,0xffb132b0) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff879bf8) //119            == 0xff879bf8
//NHSTUB(GetDrive_FreeClusters                ,0xff879c70) //1103            == 0xff879c70
NHSTUB(GetDrive_TotalClusters                 ,0xff879c34) //119
NHSTUB(GetOpticalTemperature                  ,0xff82e4c8) //120
NHSTUB(GetParameterData                       ,0xff9b2e94) //  2
NHSTUB(GetZoomLensCurrentPoint                ,0xffaf30e4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaf30f8) //102
NHSTUB(GiveSemaphore                          ,0xff8222d8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff938088) //  2
NHSTUB(LEDDrive                               ,0xff82ea48) //120
NHSTUB(LocalTime                              ,0xff81450c) //115
NHSTUB(LockMainPower                          ,0xff9ae080) //120
NHSTUB(MakeDirectory_Fut                      ,0xff873380) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffb157a0) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaf2fc4) //120
NHSTUB(Open                                   ,0xff87a3e4) //120
NHSTUB(PT_PlaySound                           ,0xff9a4ee8) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff9a9df8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff9a9e74) //120
NHSTUB(Read                                   ,0xff87a4a0) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff9c3e2c) //120
NHSTUB(RenameFile_Fut                         ,0xff873224) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffb18474) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9adf84) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9dd8b4) //120
NHSTUB(SetFileAttributes                      ,0xff87a634) //  1
NHSTUB(SetLogicalEventActive                  ,0xff9abbe0) //1104
NHSTUB(SetParameterData                       ,0xff9b2db4) //  2
NHSTUB(SetPropertyCase                        ,0xff8258c4) //  2
//NHSTUB(SetScriptMode                        ,0xff9abc48) //120            == 0xff9abc48
NHSTUB(SleepTask                              ,0xff8225f4) //120
NHSTUB(TakeSemaphore                          ,0xff8220f0) //1101
NHSTUB(TurnOffBackLight                       ,0xff9f8d80) //  2
NHSTUB(TurnOnBackLight                        ,0xff9f8d50) //  2
NHSTUB(TurnOnDisplay                          ,0xff95f5d4) //120
NHSTUB(TurnOffDisplay                         ,0xff95f5e4) //120
NHSTUB(UnlockAE                               ,0xff9955a4) //120
//NHSTUB(UnlockAF                             ,0xff995364) //120            == 0xff995364
NHSTUB(UnlockMainPower                        ,0xff9ae118) //120
NHSTUB(UpdateMBROnFlash                       ,0xff87992c) //  1
NHSTUB(VbattGet                               ,0xff82d38c) //120
NHSTUB(Write                                  ,0xff87a4ac) //120
NHSTUB(_log                                   ,0xffb53b6c) //121
NHSTUB(_log10                                 ,0xffb4fbf0) //121
NHSTUB(_pow                                   ,0xffb4fd78) //121
NHSTUB(_sqrt                                  ,0xffb51f68) //  1
NHSTUB(apex2us                                ,0xff8c7eb8) //  1
NHSTUB(close                                  ,0xffb5e774) //109
NHSTUB(exmem_alloc                            ,0xff812834) //  2
NHSTUB(kbd_p1_f                               ,0xff8280bc) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff8280c8) //109
NHSTUB(kbd_p2_f                               ,0xff8284a0) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff828e30) //  3
NHSTUB(lseek                                  ,0xffb5e8b8) //  1
NHSTUB(memcmp                                 ,0xffb597d0) //120
NHSTUB(memcpy                                 ,0xffb5980c) //120
NHSTUB(memset                                 ,0xffb59884) //120
NHSTUB(mkdir                                  ,0xff87a664) //  1
NHSTUB(open                                   ,0xffb5edb8) //109
NHSTUB(closedir                               ,0xffb5bbfc) //  1
NHSTUB(qsort                                  ,0xffb59030) //  1
NHSTUB(rand                                   ,0xffb59054) //  1
NHSTUB(realloc                                ,0xffb49dc8) //115
NHSTUB(srand                                  ,0xffb59078) //  1
NHSTUB(stat                                   ,0xffb5bcc4) //  1
NHSTUB(strcat                                 ,0xffb598a4) //  1
NHSTUB(strchr                                 ,0xffb598d0) //  1
NHSTUB(strcmp                                 ,0xffb598f4) //120
NHSTUB(strcpy                                 ,0xffb59a88) //120
NHSTUB(strftime                               ,0xffb5b110) //  1
NHSTUB(strlen                                 ,0xffb59bec) //120
NHSTUB(strncmp                                ,0xffb59c50) //  1
NHSTUB(strncpy                                ,0xffb59c94) //  1
NHSTUB(strrchr                                ,0xffb59d18) //  1
NHSTUB(strtol                                 ,0xffb5946c) //  1
NHSTUB(isdigit                                ,0xffb55ba0) //  1
NHSTUB(isspace                                ,0xffb55c18) //  1
NHSTUB(isalpha                                ,0xffb55b70) //  1
NHSTUB(isupper                                ,0xffb55c30) //  1
NHSTUB(islower                                ,0xffb55bd0) //  1
NHSTUB(ispunct                                ,0xffb55c00) //  1
NHSTUB(isxdigit                               ,0xffb55c48) //  1
NHSTUB(toupper                                ,0xffb55c70) //  1
NHSTUB(tolower                                ,0xffb55c60) //  1
NHSTUB(taskLock                               ,0xffb6ea98) //  1
NHSTUB(taskUnlock                             ,0xffb6eb40) //  1
NHSTUB(taskName                               ,0xffb6e2d4) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb5c3c8) //  1
NHSTUB(readdir                                ,0xffb5bbc8) //  1
NHSTUB(strtoul                                ,0xffb59614) //  1
NHSTUB(strpbrk                                ,0xffb59cdc) //  1
NHSTUB(utime                                  ,0xffb5bd58) //  1
NHSTUB(mktime                                 ,0xffb5a5b8) //  1
NHSTUB(opendir                                ,0xffb5bc30) //  1
NHSTUB(memchr                                 ,0xffb5979c) //  1
NHSTUB(memPartInfoGet                         ,0xffb61bd4) //  1
NHSTUB(iosDrvInstall                          ,0xffb5fc58) //  1
NHSTUB(iosDevAdd                              ,0xffb5f994) //  1
NHSTUB(iosDevDelete                           ,0xffb5f96c) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffb15500) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb64414) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb64350) //  1
NHSTUB(Unmount_FileSystem                     ,0xff8797d8) //  1
NHSTUB(taskSuspend                            ,0xffb6e4e4) //  1
NHSTUB(taskResume                             ,0xffb6e6b8) //  1
NHSTUB(time                                   ,0xffb5b13c) //  1
NHSTUB(vsprintf                               ,0xffb5d51c) //115
NHSTUB(EngDrvRead                             ,0xff88bdec) //102
