// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.02A   // Found @ 0xff818028, "GM1.02A" @ 0xff818035
//   Firmware build timestamp: Oct 15 2007 10:21:39
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.52MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000bef70

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xffafab60) //  3 96%
NHSTUB(FreeUncacheableMemory                  ,0xff81e5d8) //  1 90%
//NHSTUB(GetCurrentAvValue                    ,0xffa50268) //120        *** != 0xffad9e94
NHSTUB(GetFocusLensSubjectDistance            ,0xffad2fb4) //  1 90%
NHSTUB(GetParameterData                       ,0xffb39ce0) //  1 86%
NHSTUB(GetPropertyCase                        ,0xff81bc98) //  2 89%
NHSTUB(GetSystemTime                          ,0xff8136ec) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa5044c) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffa50494) //  1 94%
NHSTUB(Restart                                ,0xff81b74c) //  1 96%
NHSTUB(SetParameterData                       ,0xffb39c00) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff834a74) //  1 89%
//NHSTUB(WriteSDCard                          ,0xffaac1ec) //  3 74%    *** != 0xffaac394
// ALT: NHSTUB(WriteSDCard, 0xffaac394) // 3 23/8
NHSTUB(add_ptp_handler                        ,0xff9e469c) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81e2b0) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xff9201cc
NHSTUB(kbd_p2_f                               ,0xffa2f61c) //  1 56%
//NHSTUB(kbd_pwr_off                          ,0xffa2e504) //  1 83%    *** != 0xffa30c58
// ALT: NHSTUB(kbd_pwr_off, 0xffa2e520) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30ca0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30cbc) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30ca0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30cbc) // 3 5/1
//NHSTUB(kbd_pwr_on                           ,0xffa27648) //  1 55%    *** != 0xffa30c18
// ALT: NHSTUB(kbd_pwr_on, 0xffa27674) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa27b74) // 1 5/4
NHSTUB(malloc                                 ,0xff9201c0) //  1 53%
NHSTUB(mkdir                                  ,0xffa9a270) //  1 51%
// ALT: NHSTUB(mkdir, 0xffa9a344) // 1 16/15
NHSTUB(taskIdListGet                          ,0xff92a308) //  1 82%
NHSTUB(utime                                  ,0xffb5281c) //  1 57%
NHSTUB(localtime                              ,0xff918fd8) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffa9932c) //  3 93%
NHSTUB(MakeAFScan                             ,0xffb000d0) //  2 79%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffb3be28 -> ffb3be28
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffb2f2b8) // Found @0xffb2f2b8,          stubs_min = 0xffb2f2b8 (0xFFB2F2B8)
//DEF(FlashParamsTable                        ,0xffb3e4bc) // Found @0xffb3e4bc,          stubs_min = 0xffb3e4bc (0xFFB3E4BC)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6f; }                          // Found @0xffb39d4c

// Misc stuff
// LED table init @ 0xffa2ef20
// LED #1: 0xc02200cc, offset 0x4
// LED #2: 0xc02200c8, offset 0x44
// LED #3: 0xc02200d0, offset 0x84
// LED #4: 0xc02200d4, offset 0xc4
// LED #5: 0xc02200c4, offset 0x204
// LED #6: 0xc02200c0, offset 0x244

// canon_data_src: 0xffb88020, canon_data_len: 0xca00

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff81e5a4) //  1
NHSTUB(Close                                  ,0xffa9a008) //120
NHSTUB(CreateTask                             ,0xffb14810) //120
NHSTUB(DebugAssert                            ,0xffb2071c) //1100
NHSTUB(DeleteFile_Fut                         ,0xffa955dc) //  1
NHSTUB(DoAELock                               ,0xffafacec) //120
NHSTUB(DoAFLock                               ,0xffafa7b8) //120
NHSTUB(ExecuteEventProcedure                  ,0xff814a58) //  1
NHSTUB(ExitFromCompensationEVF                ,0xffafabe4) //  3
NHSTUB(ExitTask                               ,0xffb14bd0) //120
NHSTUB(Fclose_Fut                             ,0xffa95750) //120
NHSTUB(Feof_Fut                               ,0xffa9594c) //  3
NHSTUB(Fflush_Fut                             ,0xffa95988) //  3
NHSTUB(Fgets_Fut                              ,0xffa958b4) //  3
NHSTUB(Fopen_Fut                              ,0xffa95710) //120
NHSTUB(Fread_Fut                              ,0xffa9580c) //120
NHSTUB(Fseek_Fut                              ,0xffa95900) //120
NHSTUB(Fwrite_Fut                             ,0xffa95860) //120
//NHSTUB(GetBatteryTemperature                ,0xffa344e4) //102            == 0xffa344e4
NHSTUB(GetCCDTemperature                      ,0xffa344d0) //102
NHSTUB(GetDrive_ClusterSize                   ,0xffa997f4) //119
NHSTUB(GetDrive_FreeClusters                  ,0xffa9986c) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xffa99830) //119
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffad34a8) //  3
NHSTUB(GetOpticalTemperature                  ,0xffa344bc) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffae5ef4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffae5f08) //102
NHSTUB(GiveSemaphore                          ,0xffb143dc) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff9a43a8) //  2
NHSTUB(LEDDrive                               ,0xffa2eb34) //120
NHSTUB(LocalTime                              ,0xffb20fe8) //115
NHSTUB(LockMainPower                          ,0xffb36bf4) //120
NHSTUB(MakeDirectory_Fut                      ,0xffa95690) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffa52a78) //102
NHSTUB(MoveIrisWithAv                         ,0xffad9e2c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffae5dcc) //120
NHSTUB(Open                                   ,0xffa99fe0) //120
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffb0b828) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffb0b7ec) //120
NHSTUB(PT_PlaySound                           ,0xffb0b2ec) //  3
NHSTUB(PostLogicalEventForNotPowerType        ,0xffb32824) //120
NHSTUB(PostLogicalEventToUI                   ,0xffb328a0) //120
NHSTUB(Read                                   ,0xffa9a09c) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff90bc18) //120
NHSTUB(RenameFile_Fut                         ,0xffa95534) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffa55aac) //102
NHSTUB(SetAutoShutdownTime                    ,0xffb36af8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff828fc4) //120
NHSTUB(SetFileAttributes                      ,0xffa9a1f0) //  3
NHSTUB(SetLogicalEventActive                  ,0xffb34700) //1104
NHSTUB(SetPropertyCase                        ,0xff81bb60) //  3
//NHSTUB(SetScriptMode                        ,0xffb34764) //120            == 0xffb34764
NHSTUB(SleepTask                              ,0xffb14724) //120
//NHSTUB(TakeSemaphore                        ,0xffb141d4) //1101            == 0xffb141d4
NHSTUB(TurnOffBackLight                       ,0xff8462d4) //  2
NHSTUB(TurnOnBackLight                        ,0xff8462a4) //  2
NHSTUB(TurnOnDisplay                          ,0xffa243ec) //120
NHSTUB(TurnOffDisplay                         ,0xffa243fc) //120
NHSTUB(UnlockAE                               ,0xffafad3c) //120
NHSTUB(UnlockAF                               ,0xffafa838) //120
NHSTUB(UnlockMainPower                        ,0xffb36c8c) //120
NHSTUB(UpdateMBROnFlash                       ,0xffa99528) //  1
NHSTUB(VbattGet                               ,0xffa2ccd8) //120
NHSTUB(Write                                  ,0xffa9a0a8) //120
NHSTUB(_log                                   ,0xff912db4) //121
NHSTUB(_log10                                 ,0xff90fb5c) //121
NHSTUB(_pow                                   ,0xff90fcdc) //121
NHSTUB(_sqrt                                  ,0xff911b9c) //  1
NHSTUB(apex2us                                ,0xff931648) //  1
NHSTUB(close                                  ,0xff91d180) //109
NHSTUB(exmem_free                             ,0xff81e500) //102
NHSTUB(kbd_p1_f                               ,0xffa2f1ec) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffa2f1f8) //109
NHSTUB(kbd_read_keys_r2                       ,0xffa30724) //  3
NHSTUB(lseek                                  ,0xff91d2c4) //  1
NHSTUB(memcmp                                 ,0xff9183b8) //120
NHSTUB(memcpy                                 ,0xff9183f4) //120
NHSTUB(memset                                 ,0xff91846c) //120
NHSTUB(open                                   ,0xff91d7c4) //109
NHSTUB(closedir                               ,0xffb526c0) //  1
NHSTUB(qsort                                  ,0xff917c18) //  1
NHSTUB(rand                                   ,0xff917c3c) //  1
NHSTUB(realloc                                ,0xffb20328) //115
NHSTUB(srand                                  ,0xff917c60) //  1
NHSTUB(stat                                   ,0xffb52788) //  1
NHSTUB(strcat                                 ,0xff91848c) //  1
NHSTUB(strchr                                 ,0xff9184b8) //  1
NHSTUB(strcmp                                 ,0xff9184dc) //120
NHSTUB(strcpy                                 ,0xff918670) //120
NHSTUB(strftime                               ,0xff919cf8) //  1
NHSTUB(strlen                                 ,0xff9187d4) //120
NHSTUB(strncmp                                ,0xff918838) //  1
NHSTUB(strncpy                                ,0xff91887c) //  1
NHSTUB(strrchr                                ,0xff918900) //  1
NHSTUB(strtol                                 ,0xff918054) //  1
NHSTUB(isdigit                                ,0xff914788) //  1
NHSTUB(isspace                                ,0xff914800) //  1
NHSTUB(isalpha                                ,0xff914758) //  1
NHSTUB(isupper                                ,0xff914818) //  1
NHSTUB(islower                                ,0xff9147b8) //  1
NHSTUB(ispunct                                ,0xff9147e8) //  1
NHSTUB(isxdigit                               ,0xff914830) //  1
NHSTUB(toupper                                ,0xff914858) //  1
NHSTUB(tolower                                ,0xff914848) //  1
NHSTUB(taskLock                               ,0xff92a9c4) //  1
NHSTUB(taskUnlock                             ,0xff92aa6c) //  1
NHSTUB(taskName                               ,0xff92a200) //  1
NHSTUB(errnoOfTaskGet                         ,0xff91add4) //  1
NHSTUB(readdir                                ,0xffb5268c) //  1
NHSTUB(strtoul                                ,0xff9181fc) //  1
NHSTUB(strpbrk                                ,0xff9188c4) //  1
NHSTUB(mktime                                 ,0xff9191a0) //  1
NHSTUB(opendir                                ,0xffb526f4) //  1
NHSTUB(memchr                                 ,0xff918384) //  1
NHSTUB(memPartInfoGet                         ,0xff9205e0) //  1
NHSTUB(iosDrvInstall                          ,0xff91e664) //  1
NHSTUB(iosDevAdd                              ,0xff91e3a0) //  1
NHSTUB(iosDevDelete                           ,0xff91e378) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa527e0) //  1
NHSTUB(taskCreateHookAdd                      ,0xff922e20) //  1
NHSTUB(taskDeleteHookAdd                      ,0xff922d5c) //  1
NHSTUB(Unmount_FileSystem                     ,0xffa993d4) //  1
NHSTUB(taskSuspend                            ,0xff92a410) //  1
NHSTUB(taskResume                             ,0xff92a5e4) //  1
NHSTUB(time                                   ,0xff919d24) //  1
NHSTUB(vsprintf                               ,0xff91bf28) //115
NHSTUB(EngDrvRead                             ,0xffa3da80) //102
