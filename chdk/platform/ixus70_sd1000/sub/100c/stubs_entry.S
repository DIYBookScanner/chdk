// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00C   // Found @ 0xff818028, "GM1.00C" @ 0xff818035
//   Firmware build timestamp: Jan 24 2007 12:38:14
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.52MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000bef70

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xffafaa6c) //  3 96%
NHSTUB(FreeUncacheableMemory                  ,0xff81e5d8) //  1 90%
//NHSTUB(GetCurrentAvValue                    ,0xffa501f4) //120        *** != 0xffad9e20
//NHSTUB(GetFocusLensSubjectDistance          ,0xffad2f40) //  1 90%    *** != 0xffad2f88
NHSTUB(GetParameterData                       ,0xffb39bec) //  1 86%
NHSTUB(GetPropertyCase                        ,0xff81bc98) //  2 89%
NHSTUB(GetSystemTime                          ,0xff8136ec) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa503d8) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffa50420) //  1 94%
NHSTUB(Restart                                ,0xff81b74c) //  1 96%
NHSTUB(SetParameterData                       ,0xffb39b0c) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xff834a74) //  1 89%
//NHSTUB(WriteSDCard                          ,0xffaac178) //  3 74%    *** != 0xffaac320
// ALT: NHSTUB(WriteSDCard, 0xffaac320) // 3 23/8
NHSTUB(add_ptp_handler                        ,0xff9e4628) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81e2b0) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xff9201cc
NHSTUB(kbd_p2_f                               ,0xffa2f5a8) //  1 56%
//NHSTUB(kbd_pwr_off                          ,0xffa2e490) //  1 83%    *** != 0xffa30be4
// ALT: NHSTUB(kbd_pwr_off, 0xffa2e4ac) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30c2c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30c48) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30c2c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa30c48) // 3 5/1
//NHSTUB(kbd_pwr_on                           ,0xffa275d4) //  1 55%    *** != 0xffa30ba4
// ALT: NHSTUB(kbd_pwr_on, 0xffa27600) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa27b00) // 1 5/4
NHSTUB(malloc                                 ,0xff9201c0) //  1 53%
NHSTUB(mkdir                                  ,0xffa9a1fc) //  1 51%
// ALT: NHSTUB(mkdir, 0xffa9a2d0) // 1 16/15
NHSTUB(taskIdListGet                          ,0xff92a308) //  1 82%
NHSTUB(utime                                  ,0xffb52728) //  1 57%
NHSTUB(localtime                              ,0xff918fd8) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffa992b8) //  3 93%
NHSTUB(MakeAFScan                             ,0xffafffdc) //  2 79%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffb3bd34 -> ffb3bd34
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffb2f1c4) // Found @0xffb2f1c4,          stubs_min = 0xffb2f1c4 (0xFFB2F1C4)
//DEF(FlashParamsTable                        ,0xffb3e3c8) // Found @0xffb3e3c8,          stubs_min = 0xffb3e3c8 (0xFFB3E3C8)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6f; }                          // Found @0xffb39c58

// Misc stuff
// LED table init @ 0xffa2eeac
// LED #1: 0xc02200cc, offset 0x4
// LED #2: 0xc02200c8, offset 0x44
// LED #3: 0xc02200d0, offset 0x84
// LED #4: 0xc02200d4, offset 0xc4
// LED #5: 0xc02200c4, offset 0x204
// LED #6: 0xc02200c0, offset 0x244

// canon_data_src: 0xffb87f30, canon_data_len: 0xca00

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff81e5a4) //  1
NHSTUB(Close                                  ,0xffa99f94) //120
NHSTUB(CreateTask                             ,0xffb1471c) //120
NHSTUB(DebugAssert                            ,0xffb20628) //1100
NHSTUB(DeleteFile_Fut                         ,0xffa95568) //  1
NHSTUB(DoAELock                               ,0xffafabf8) //120
NHSTUB(DoAFLock                               ,0xffafa6c4) //120
NHSTUB(ExecuteEventProcedure                  ,0xff814a58) //  1
NHSTUB(ExitFromCompensationEVF                ,0xffafaaf0) //  3
NHSTUB(ExitTask                               ,0xffb14adc) //120
NHSTUB(Fclose_Fut                             ,0xffa956dc) //120
NHSTUB(Feof_Fut                               ,0xffa958d8) //  3
NHSTUB(Fflush_Fut                             ,0xffa95914) //  3
NHSTUB(Fgets_Fut                              ,0xffa95840) //  3
NHSTUB(Fopen_Fut                              ,0xffa9569c) //120
NHSTUB(Fread_Fut                              ,0xffa95798) //120
NHSTUB(Fseek_Fut                              ,0xffa9588c) //120
NHSTUB(Fwrite_Fut                             ,0xffa957ec) //120
//NHSTUB(GetBatteryTemperature                ,0xffa34470) //102            == 0xffa34470
NHSTUB(GetCCDTemperature                      ,0xffa3445c) //102
NHSTUB(GetDrive_ClusterSize                   ,0xffa99780) //119
NHSTUB(GetDrive_FreeClusters                  ,0xffa997f8) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xffa997bc) //119
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffad3434) //  3
NHSTUB(GetOpticalTemperature                  ,0xffa34448) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffae5e70) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffae5e84) //102
NHSTUB(GiveSemaphore                          ,0xffb142e8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff9a43a8) //  2
NHSTUB(LEDDrive                               ,0xffa2eac0) //120
NHSTUB(LocalTime                              ,0xffb20ef4) //115
NHSTUB(LockMainPower                          ,0xffb36b00) //120
NHSTUB(MakeDirectory_Fut                      ,0xffa9561c) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffa52a04) //102
NHSTUB(MoveIrisWithAv                         ,0xffad9db8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffae5d48) //120
NHSTUB(Open                                   ,0xffa99f6c) //120
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffb0b734) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffb0b6f8) //120
NHSTUB(PT_PlaySound                           ,0xffb0b1f8) //  3
NHSTUB(PostLogicalEventForNotPowerType        ,0xffb32730) //120
NHSTUB(PostLogicalEventToUI                   ,0xffb327ac) //120
NHSTUB(Read                                   ,0xffa9a028) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff90bc18) //120
NHSTUB(RenameFile_Fut                         ,0xffa954c0) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffa55a38) //102
NHSTUB(SetAutoShutdownTime                    ,0xffb36a04) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff828fc4) //120
NHSTUB(SetFileAttributes                      ,0xffa9a17c) //  3
NHSTUB(SetLogicalEventActive                  ,0xffb3460c) //1104
NHSTUB(SetPropertyCase                        ,0xff81bb60) //  3
//NHSTUB(SetScriptMode                        ,0xffb34670) //120            == 0xffb34670
NHSTUB(SleepTask                              ,0xffb14630) //120
//NHSTUB(TakeSemaphore                        ,0xffb140e0) //1101            == 0xffb140e0
NHSTUB(TurnOffBackLight                       ,0xff8462d4) //  2
NHSTUB(TurnOnBackLight                        ,0xff8462a4) //  2
NHSTUB(TurnOnDisplay                          ,0xffa24378) //120
NHSTUB(TurnOffDisplay                         ,0xffa24388) //120
NHSTUB(UnlockAE                               ,0xffafac48) //120
NHSTUB(UnlockAF                               ,0xffafa744) //120
NHSTUB(UnlockMainPower                        ,0xffb36b98) //120
NHSTUB(UpdateMBROnFlash                       ,0xffa994b4) //  1
NHSTUB(VbattGet                               ,0xffa2cc64) //120
NHSTUB(Write                                  ,0xffa9a034) //120
NHSTUB(_log                                   ,0xff912db4) //121
NHSTUB(_log10                                 ,0xff90fb5c) //121
NHSTUB(_pow                                   ,0xff90fcdc) //121
NHSTUB(_sqrt                                  ,0xff911b9c) //  1
NHSTUB(apex2us                                ,0xff931648) //  1
NHSTUB(close                                  ,0xff91d180) //109
NHSTUB(exmem_free                             ,0xff81e500) //102
NHSTUB(kbd_p1_f                               ,0xffa2f178) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffa2f184) //109
NHSTUB(kbd_read_keys_r2                       ,0xffa306b0) //  3
NHSTUB(lseek                                  ,0xff91d2c4) //  1
NHSTUB(memcmp                                 ,0xff9183b8) //120
NHSTUB(memcpy                                 ,0xff9183f4) //120
NHSTUB(memset                                 ,0xff91846c) //120
NHSTUB(open                                   ,0xff91d7c4) //109
NHSTUB(closedir                               ,0xffb525cc) //  1
NHSTUB(qsort                                  ,0xff917c18) //  1
NHSTUB(rand                                   ,0xff917c3c) //  1
NHSTUB(realloc                                ,0xffb20234) //115
NHSTUB(srand                                  ,0xff917c60) //  1
NHSTUB(stat                                   ,0xffb52694) //  1
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
NHSTUB(readdir                                ,0xffb52598) //  1
NHSTUB(strtoul                                ,0xff9181fc) //  1
NHSTUB(strpbrk                                ,0xff9188c4) //  1
NHSTUB(mktime                                 ,0xff9191a0) //  1
NHSTUB(opendir                                ,0xffb52600) //  1
NHSTUB(memchr                                 ,0xff918384) //  1
NHSTUB(memPartInfoGet                         ,0xff9205e0) //  1
NHSTUB(iosDrvInstall                          ,0xff91e664) //  1
NHSTUB(iosDevAdd                              ,0xff91e3a0) //  1
NHSTUB(iosDevDelete                           ,0xff91e378) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa5276c) //  1
NHSTUB(taskCreateHookAdd                      ,0xff922e20) //  1
NHSTUB(taskDeleteHookAdd                      ,0xff922d5c) //  1
NHSTUB(Unmount_FileSystem                     ,0xffa99360) //  1
NHSTUB(taskSuspend                            ,0xff92a410) //  1
NHSTUB(taskResume                             ,0xff92a5e4) //  1
NHSTUB(time                                   ,0xff919d24) //  1
NHSTUB(vsprintf                               ,0xff91bf28) //115
NHSTUB(EngDrvRead                             ,0xffa3da0c) //102
