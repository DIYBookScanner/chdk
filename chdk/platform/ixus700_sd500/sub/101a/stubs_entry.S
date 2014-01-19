// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Version GM1.01A   // Found @ 0xff81a454, "GM1.01A" @ 0xff81a465
//   Firmware build timestamp: Mar 10 2005 15:46:48
//   Canon DIGITAL IXUS 700

// Values for makefile.inc
//   PLATFORMID = 12530 (0x30f2) // Found @ 0xffd70130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0007c2b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff951a88) //  1 66%    *** != 0x00000000
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951abc) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951af0) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951b24) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951b58) // 1 20/10
//NHSTUB(GetCurrentAvValue                    ,0xffa6f23c) //120        *** != 0xffa4f304
//NHSTUB(GetFocusLensSubjectDistance          ,0xffa55f3c) //  1 51%    *** != 0xffa64c48
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa651c8) //  2 88%
NHSTUB(GetParameterData                       ,0xff96b7c4) //  1 86%
//NHSTUB(GetPropertyCase                      ,0xff825ca0) //  2 71%    *** != 0xff825ca4
NHSTUB(GetSystemTime                          ,0xff814248) //  1 96%
//NHSTUB(PT_PlaySound                         ,0xff960948) //  1        *** != 0xff960080
NHSTUB(PutInNdFilter                          ,0xffa6f3c4) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa70ef8) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa70f40) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa70ef8) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa70f40) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa6f40c) //  1 94%
//NHSTUB(Remove                               ,0xff8c70c4) //  3 52%    *** != 0xff86a950
//NHSTUB(Restart                              ,0xff82339c) //  1 84%    *** != 0xff8233a0
NHSTUB(SetCurrentCaptureModeType              ,0xff98fe2c) //  1 73%
NHSTUB(SetFileAttributes                      ,0xff86aa9c) //  1 58%
NHSTUB(SetParameterData                       ,0xff96b6e4) //  1 86%
// ERROR: SetPropertyCase is not found.                    //--- ---    *** != 0xff825b9c
NHSTUB(UpdateMBROnFlash                       ,0xff869e8c) //  1 96%
// ERROR: VbattGet is not found.                           //--- ---    *** != 0xffa60a4c
// ERROR: WriteSDCard is not found.                        //--- ---    *** != 0xff87cacc
NHSTUB(add_ptp_handler                        ,0xffa1918c) //  1 96%
NHSTUB(exmem_alloc                            ,0xff812954) //  1 92%
// ERROR: free is not found.                               //--- ---    *** != 0xffabcc28
// ERROR: kbd_p1_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_p1_f_cont is not found.                      //--- ---    *** != 0xff828fec
// ERROR: kbd_p2_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0x00000000
//NHSTUB(kbd_pwr_off                          ,0xffa478fc) //  1 83%    *** != 0xffa476ac
// ALT: NHSTUB(kbd_pwr_off, 0xffa47918) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa476ac) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa476c8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa47798) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa477b4) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xffa5c468) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xffa5c494) // 1 5/4
NHSTUB(malloc                                 ,0xffabcc1c) //  1 53%
NHSTUB(mkdir                                  ,0xff86aacc) //  1 61%
// ALT: NHSTUB(mkdir, 0xff86ab8c) // 1 19/12
NHSTUB(taskIdListGet                          ,0xffac7d80) //  1 82%
NHSTUB(localtime                              ,0xffab4370) //  1 93%
// ERROR: Mount_FileSystem is not found.                   //--- ---    *** != 0xff869cd4
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xff94ef7c

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff967c0c -> ff967c0c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff962594) // Found @0xff962594,          stubs_min = 0xff962594 (0xFF962594)
//DEF(FlashParamsTable                        ,0xff969790) // Found @0xff969790,          stubs_min = 0xff969790 (0xFF969790)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x53; }                          // Found @0xff96b830

// Misc stuff
// LED table init @ 0xffa688dc
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xfface9c0, canon_data_len: 0xd340

// For capt_seq.c
DEF(_nrflag,0x53ec) // Found @ ff955444 (0x53ec)
//static long *nrflag = (long*)(0x53ec);       // Found @ ff955444

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff813ec0) //  1
//NHSTUB(Close                                ,0xff86a944) //120            == 0xff86a944
NHSTUB(CreateTask                             ,0xff821a10) //120
NHSTUB(DebugAssert                            ,0xff813e68) //1100
NHSTUB(DeleteFile_Fut                         ,0xff8635f0) //  1
NHSTUB(DoAELock                               ,0xff94f1dc) //120
//NHSTUB(DoAFLock                             ,0xff94ef7c) //120            == 0xff94ef7c
NHSTUB(ExecuteEventProcedure                  ,0xff816164) //  1
NHSTUB(ExitTask                               ,0xff821dd0) //120
NHSTUB(Fclose_Fut                             ,0xff863730) //  1
NHSTUB(Feof_Fut                               ,0xff863944) //  1
NHSTUB(Fflush_Fut                             ,0xff86397c) //  1
NHSTUB(Fgets_Fut                              ,0xff8638b4) //  1
NHSTUB(Fopen_Fut                              ,0xff8636f4) //  1
NHSTUB(Fread_Fut                              ,0xff863814) //  1
NHSTUB(FreeUncacheableMemory                  ,0xff813ef4) //  1
NHSTUB(Fseek_Fut                              ,0xff8638fc) //  1
NHSTUB(Fwrite_Fut                             ,0xff863864) //  1
//NHSTUB(GetBatteryTemperature                ,0xffa4da28) //102            == 0xffa4da28
//NHSTUB(GetCCDTemperature                    ,0xffa4da14) //102            == 0xffa4da14
//NHSTUB(GetDrive_ClusterSize                 ,0xff86a150) //119            == 0xff86a150
//NHSTUB(GetDrive_FreeClusters                ,0xff86a1c8) //1103            == 0xff86a1c8
//NHSTUB(GetDrive_TotalClusters               ,0xff86a18c) //119            == 0xff86a18c
//NHSTUB(GetOpticalTemperature                ,0xffa4da00) //120            == 0xffa4da00
//NHSTUB(GetZoomLensCurrentPoint              ,0xffa56f6c) //120            == 0xffa56f6c
//NHSTUB(GetZoomLensCurrentPosition           ,0xffa56f80) //102            == 0xffa56f80
NHSTUB(GiveSemaphore                          ,0xff8213c8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff9086f0) //  1
NHSTUB(LEDDrive                               ,0xffa684cc) //120
NHSTUB(LocalTime                              ,0xff813e2c) //115
NHSTUB(LockMainPower                          ,0xff967984) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86367c) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa71588) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa56de8) //120
//NHSTUB(Open                                 ,0xff86a938) //120            == 0xff86a938
NHSTUB(PostLogicalEventForNotPowerType        ,0xff964d10) //120
NHSTUB(PostLogicalEventToUI                   ,0xff964d9c) //120
//NHSTUB(Read                                 ,0xff86a9a4) //120            == 0xff86a9a4
NHSTUB(RefreshPhysicalScreen                  ,0xff97b578) //120
NHSTUB(RenameFile_Fut                         ,0xff863570) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa738ec) //102
NHSTUB(SetAutoShutdownTime                    ,0xff96787c) //120
NHSTUB(SetLogicalEventActive                  ,0xff96622c) //1104
//NHSTUB(SetScriptMode                        ,0xff966290) //120            == 0xff966290
NHSTUB(SleepTask                              ,0xff821870) //120
NHSTUB(TakeSemaphore                          ,0xff8211e0) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a3614) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a35e8) //  1
NHSTUB(TurnOnDisplay                          ,0xff931c1c) //120
NHSTUB(TurnOffDisplay                         ,0xff931c2c) //120
NHSTUB(UnlockAE                               ,0xff94f230) //120
//NHSTUB(UnlockAF                             ,0xff94eff4) //120            == 0xff94eff4
NHSTUB(UnlockMainPower                        ,0xff967a38) //120
//NHSTUB(Write                                ,0xff86a9b0) //120            == 0xff86a9b0
NHSTUB(_log                                   ,0xffaa615c) //121
NHSTUB(_log10                                 ,0xffaa6804) //121
NHSTUB(_pow                                   ,0xffaa6cf4) //121
NHSTUB(_sqrt                                  ,0xffaab040) //  1
NHSTUB(apex2us                                ,0xff8adbe8) //  1
NHSTUB(close                                  ,0xffab9bdc) //109
NHSTUB(lseek                                  ,0xffab9d20) //  1
NHSTUB(memcmp                                 ,0xffab3750) //120
NHSTUB(memcpy                                 ,0xffab378c) //120
NHSTUB(memset                                 ,0xffab3804) //120
NHSTUB(open                                   ,0xffaba220) //  1
NHSTUB(closedir                               ,0xffab5b7c) //  1
NHSTUB(qsort                                  ,0xffab2fb0) //  1
NHSTUB(rand                                   ,0xffab2fd4) //  1
NHSTUB(realloc                                ,0xffa9d75c) //115
NHSTUB(srand                                  ,0xffab2ff8) //  1
NHSTUB(stat                                   ,0xffab5c44) //  1
NHSTUB(strcat                                 ,0xffab3824) //  1
NHSTUB(strchr                                 ,0xffab3850) //  1
NHSTUB(strcmp                                 ,0xffab3874) //120
NHSTUB(strcpy                                 ,0xffab3a08) //120
NHSTUB(strftime                               ,0xffab5090) //  1
NHSTUB(strlen                                 ,0xffab3b6c) //120
NHSTUB(strncmp                                ,0xffab3bd0) //  1
NHSTUB(strncpy                                ,0xffab3c14) //  1
NHSTUB(strrchr                                ,0xffab3c98) //  1
NHSTUB(strtol                                 ,0xffab33ec) //  1
NHSTUB(isdigit                                ,0xffaafb20) //  1
NHSTUB(isspace                                ,0xffaafb98) //  1
NHSTUB(isalpha                                ,0xffaafaf0) //  1
NHSTUB(isupper                                ,0xffaafbb0) //  1
NHSTUB(islower                                ,0xffaafb50) //  1
NHSTUB(ispunct                                ,0xffaafb80) //  1
NHSTUB(isxdigit                               ,0xffaafbc8) //  1
NHSTUB(toupper                                ,0xffaafbf0) //  1
NHSTUB(tolower                                ,0xffaafbe0) //  1
NHSTUB(taskLock                               ,0xffac843c) //  1
NHSTUB(taskUnlock                             ,0xffac84e4) //  1
NHSTUB(taskName                               ,0xffac7c78) //  1
NHSTUB(errnoOfTaskGet                         ,0xffab6348) //  1
NHSTUB(readdir                                ,0xffab5b48) //  1
NHSTUB(strtoul                                ,0xffab3594) //  1
NHSTUB(strpbrk                                ,0xffab3c5c) //  1
NHSTUB(utime                                  ,0xffab5cd8) //  1
NHSTUB(mktime                                 ,0xffab4538) //  1
NHSTUB(opendir                                ,0xffab5bb0) //  1
NHSTUB(memchr                                 ,0xffab371c) //  1
NHSTUB(memPartInfoGet                         ,0xffabd03c) //  1
NHSTUB(iosDrvInstall                          ,0xffabb0c0) //  1
NHSTUB(iosDevAdd                              ,0xffabadfc) //  1
NHSTUB(iosDevDelete                           ,0xffabadd4) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa712f8) //  1
NHSTUB(taskCreateHookAdd                      ,0xffac029c) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffac01d8) //  1
NHSTUB(Unmount_FileSystem                     ,0xff869d34) //  1
NHSTUB(taskSuspend                            ,0xffac7e88) //  1
NHSTUB(taskResume                             ,0xffac805c) //  1
NHSTUB(time                                   ,0xffab50bc) //  1
NHSTUB(vsprintf                               ,0xffab749c) //115
NHSTUB(EngDrvRead                             ,0xff87ee58) //102
