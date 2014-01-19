// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00C   // Found @ 0xff81a738, "GM1.00C" @ 0xff81a745
//   Firmware build timestamp: Jul 24 2006 18:57:34
//   Canon DIGITAL IXUS 900Ti

// Values for makefile.inc
//   PLATFORMID = 12565 (0x3115) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000a4d10

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xff98f004) //  2 90%
//NHSTUB(ExitFromCompensationEVF              ,0xff992894) //  2 66%    *** != 0xff98f044
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff9928f0) // 2 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff9929ac) // 2 20/10
NHSTUB(GetFocusLensSubjectDistance            ,0xffb01594) //  2 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffb01b48) //  2 57%
NHSTUB(GetPropertyCase                        ,0xff8258c8) //  2 92%
NHSTUB(GetSystemTime                          ,0xff8150d8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffb0d140) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffb0d188) //  1 94%
//NHSTUB(Remove                               ,0xff8e53d4) //  3 52%
NHSTUB(Restart                                ,0xff823ab4) //  1 96%
NHSTUB(UnsetZoomForMovie                      ,0xff9e59f8) //  1 89%
//NHSTUB(WriteSDCard                          ,0xff88a708) //  2 93%    *** != 0xff88a8a4
NHSTUB(add_ptp_handler                        ,0xffabc9c4) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffb5abc8
//NHSTUB(kbd_pwr_off                          ,0xff829280) //  1 83%    *** != 0xff829238
// ALT: NHSTUB(kbd_pwr_off, 0xff82929c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82b484) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82b4a0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82929c) // 3 5/1
//NHSTUB(kbd_pwr_on                           ,0xff95b7c4) //  1 55%    *** != 0xff8291f8
// ALT: NHSTUB(kbd_pwr_on, 0xff95b7f0) // 1 5/4
NHSTUB(malloc                                 ,0xffb5abbc) //  1 53%
NHSTUB(taskIdListGet                          ,0xffb677e4) //  1 82%
NHSTUB(localtime                              ,0xffb537f8) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff87a8ac) //  1 90%
NHSTUB(MakeAFScan                             ,0xff993be4) //  2 96%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff9a8a74 -> ff9a8a74
// Mode 32774 in firmware but not in current modemap
// Mode 32772 in firmware but not in current modemap (MODE_P)
// Current modemap entry not found in firmware - MODE_M                   33772

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9a1124) // Found @0xff9a1124,          stubs_min = 0xff9a1124 (0xFF9A1124)
//DEF(FlashParamsTable                        ,0xff9ab04c) // Found @0xff9ab04c,          stubs_min = 0xff9ab04c (0xFF9AB04C)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6e; }                          // Found @0xff9ad6e8

// Misc stuff
// LED table init @ 0xff82fec8
// LED #1: 0xc02200cc, offset 0x4
// LED #2: 0xc02200c8, offset 0x44
// LED #3: 0xc02200d0, offset 0x84
// LED #4: 0xc02200d8, offset 0xc4
// LED #5: 0xc02200c4, offset 0x204
// LED #6: 0xc02200c0, offset 0x244

// canon_data_src: 0xffb6da40, canon_data_len: 0xcc00

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814ea0) //  1
NHSTUB(Close                                  ,0xff87b584) //120
NHSTUB(CreateTask                             ,0xff822594) //120
NHSTUB(DebugAssert                            ,0xff813d70) //1100
NHSTUB(DeleteFile_Fut                         ,0xff874444) //  1
NHSTUB(DoAELock                               ,0xff98f09c) //120
NHSTUB(DoAFLock                               ,0xff98ee30) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816d3c) //  1
NHSTUB(ExitTask                               ,0xff822954) //120
NHSTUB(Fclose_Fut                             ,0xff8745b8) //120
NHSTUB(Feof_Fut                               ,0xff8747b4) //  3
NHSTUB(Fflush_Fut                             ,0xff8747f0) //  3
NHSTUB(Fgets_Fut                              ,0xff87471c) //  3
NHSTUB(Fopen_Fut                              ,0xff874578) //120
NHSTUB(Fread_Fut                              ,0xff874674) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814ed4) //  1
NHSTUB(Fseek_Fut                              ,0xff874768) //120
NHSTUB(Fwrite_Fut                             ,0xff8746c8) //120
NHSTUB(GetBatteryTemperature                  ,0xff82f584) //102
NHSTUB(GetCCDTemperature                      ,0xff82f570) //102
NHSTUB(GetCurrentAvValue                      ,0xffb0cf4c) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff87ad70) //119            == 0xff87ad70
//NHSTUB(GetDrive_FreeClusters                ,0xff87ade8) //1103            == 0xff87ade8
NHSTUB(GetDrive_TotalClusters                 ,0xff87adac) //119
NHSTUB(GetOpticalTemperature                  ,0xff82f55c) //120
NHSTUB(GetParameterData                       ,0xff9ad67c) //  2
NHSTUB(GetZoomLensCurrentPoint                ,0xffaf1c64) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaf1c78) //102
NHSTUB(GiveSemaphore                          ,0xff82218c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff93033c) //  2
NHSTUB(LEDDrive                               ,0xff82fadc) //120
NHSTUB(LocalTime                              ,0xff8143f8) //115
NHSTUB(LockMainPower                          ,0xff9a8814) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8744f8) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffb0f458) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffaf1b44) //120
NHSTUB(Open                                   ,0xff87b55c) //120
NHSTUB(PT_PlaySound                           ,0xff99f320) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff9a4230) //120
NHSTUB(PostLogicalEventToUI                   ,0xff9a42ac) //120
NHSTUB(Read                                   ,0xff87b618) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff9be650) //120
NHSTUB(RenameFile_Fut                         ,0xff87439c) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffb1212c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9a8718) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9d9b48) //120
NHSTUB(SetFileAttributes                      ,0xff87b7ac) //  1
NHSTUB(SetLogicalEventActive                  ,0xff9a632c) //1104
NHSTUB(SetParameterData                       ,0xff9ad59c) //  2
NHSTUB(SetPropertyCase                        ,0xff825778) //  2
//NHSTUB(SetScriptMode                        ,0xff9a6394) //120            == 0xff9a6394
NHSTUB(SleepTask                              ,0xff8224a8) //120
NHSTUB(TakeSemaphore                          ,0xff821fa4) //1101
NHSTUB(TurnOffBackLight                       ,0xff9f5338) //  2
NHSTUB(TurnOnBackLight                        ,0xff9f5308) //  2
NHSTUB(TurnOnDisplay                          ,0xff959058) //120
NHSTUB(TurnOffDisplay                         ,0xff959068) //120
NHSTUB(UnlockAE                               ,0xff98f0bc) //120
//NHSTUB(UnlockAF                             ,0xff98ee7c) //120            == 0xff98ee7c
NHSTUB(UnlockMainPower                        ,0xff9a88ac) //120
NHSTUB(UpdateMBROnFlash                       ,0xff87aaa4) //  1
NHSTUB(VbattGet                               ,0xff82e420) //120
NHSTUB(Write                                  ,0xff87b624) //120
NHSTUB(_log                                   ,0xffb4cfc0) //121
NHSTUB(_log10                                 ,0xffb49044) //121
NHSTUB(_pow                                   ,0xffb491cc) //121
NHSTUB(_sqrt                                  ,0xffb4b3bc) //  1
NHSTUB(apex2us                                ,0xff8c6560) //  1
NHSTUB(close                                  ,0xffb57b7c) //109
NHSTUB(exmem_alloc                            ,0xff812834) //  2
NHSTUB(kbd_p1_f                               ,0xff827f58) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff827f64) //109
NHSTUB(kbd_p2_f                               ,0xff82833c) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff828d40) //  3
NHSTUB(lseek                                  ,0xffb57cc0) //  1
NHSTUB(memcmp                                 ,0xffb52bd8) //120
NHSTUB(memcpy                                 ,0xffb52c14) //120
NHSTUB(memset                                 ,0xffb52c8c) //120
NHSTUB(mkdir                                  ,0xff87b7dc) //  1
NHSTUB(open                                   ,0xffb581c0) //109
NHSTUB(closedir                               ,0xffb55004) //  1
NHSTUB(qsort                                  ,0xffb52438) //  1
NHSTUB(rand                                   ,0xffb5245c) //  1
NHSTUB(realloc                                ,0xffb431fc) //115
NHSTUB(srand                                  ,0xffb52480) //  1
NHSTUB(stat                                   ,0xffb550cc) //  1
NHSTUB(strcat                                 ,0xffb52cac) //  1
NHSTUB(strchr                                 ,0xffb52cd8) //  1
NHSTUB(strcmp                                 ,0xffb52cfc) //120
NHSTUB(strcpy                                 ,0xffb52e90) //120
NHSTUB(strftime                               ,0xffb54518) //  1
NHSTUB(strlen                                 ,0xffb52ff4) //120
NHSTUB(strncmp                                ,0xffb53058) //  1
NHSTUB(strncpy                                ,0xffb5309c) //  1
NHSTUB(strrchr                                ,0xffb53120) //  1
NHSTUB(strtol                                 ,0xffb52874) //  1
NHSTUB(isdigit                                ,0xffb4efa8) //  1
NHSTUB(isspace                                ,0xffb4f020) //  1
NHSTUB(isalpha                                ,0xffb4ef78) //  1
NHSTUB(isupper                                ,0xffb4f038) //  1
NHSTUB(islower                                ,0xffb4efd8) //  1
NHSTUB(ispunct                                ,0xffb4f008) //  1
NHSTUB(isxdigit                               ,0xffb4f050) //  1
NHSTUB(toupper                                ,0xffb4f078) //  1
NHSTUB(tolower                                ,0xffb4f068) //  1
NHSTUB(taskLock                               ,0xffb67ea0) //  1
NHSTUB(taskUnlock                             ,0xffb67f48) //  1
NHSTUB(taskName                               ,0xffb676dc) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb557d0) //  1
NHSTUB(readdir                                ,0xffb54fd0) //  1
NHSTUB(strtoul                                ,0xffb52a1c) //  1
NHSTUB(strpbrk                                ,0xffb530e4) //  1
NHSTUB(utime                                  ,0xffb55160) //  1
NHSTUB(mktime                                 ,0xffb539c0) //  1
NHSTUB(opendir                                ,0xffb55038) //  1
NHSTUB(memchr                                 ,0xffb52ba4) //  1
NHSTUB(memPartInfoGet                         ,0xffb5afdc) //  1
NHSTUB(iosDrvInstall                          ,0xffb59060) //  1
NHSTUB(iosDevAdd                              ,0xffb58d9c) //  1
NHSTUB(iosDevDelete                           ,0xffb58d74) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffb0f1b8) //  1
NHSTUB(taskCreateHookAdd                      ,0xffb5d81c) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffb5d758) //  1
NHSTUB(Unmount_FileSystem                     ,0xff87a950) //  1
NHSTUB(taskSuspend                            ,0xffb678ec) //  1
NHSTUB(taskResume                             ,0xffb67ac0) //  1
NHSTUB(time                                   ,0xffb54544) //  1
NHSTUB(vsprintf                               ,0xffb56924) //115
NHSTUB(EngDrvRead                             ,0xff88cf94) //102
