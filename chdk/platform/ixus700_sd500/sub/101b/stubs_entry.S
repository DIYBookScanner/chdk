// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Version GM1.01B   // Found @ 0xff81a454, "GM1.01B" @ 0xff81a465
//   Firmware build timestamp: Mar 29 2005 20:42:05
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 2.80MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0007c2b0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff951ad8) //  1 66%    *** != 0x00000000
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951b0c) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951b40) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951b74) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff951ba8) // 1 20/10
//NHSTUB(GetCurrentAvValue                    ,0xffa6f28c) //120        *** != 0xffa4f354
//NHSTUB(GetFocusLensSubjectDistance          ,0xffa55f8c) //  1 51%    *** != 0xffa64c98
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa65218) //  2 88%
NHSTUB(GetParameterData                       ,0xff96b814) //  1 86%
//NHSTUB(GetPropertyCase                      ,0xff825ca0) //  2 71%    *** != 0xff825ca4
NHSTUB(GetSystemTime                          ,0xff814248) //  1 96%
//NHSTUB(PT_PlaySound                         ,0xff960998) //  1        *** != 0xff9600d0
NHSTUB(PutInNdFilter                          ,0xffa6f414) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa70f48) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa70f90) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa70f48) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa70f90) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa6f45c) //  1 94%
//NHSTUB(Remove                               ,0xff8c70c4) //  3 52%    *** != 0xff86a950
//NHSTUB(Restart                              ,0xff82339c) //  1 84%    *** != 0xff8233a0
NHSTUB(SetCurrentCaptureModeType              ,0xff98fe7c) //  1 73%
NHSTUB(SetFileAttributes                      ,0xff86aa9c) //  1 58%
NHSTUB(SetParameterData                       ,0xff96b734) //  1 86%
// ERROR: SetPropertyCase is not found.                    //--- ---    *** != 0xff825b9c
NHSTUB(UpdateMBROnFlash                       ,0xff869e8c) //  1 96%
// ERROR: VbattGet is not found.                           //--- ---    *** != 0xffa60a9c
// ERROR: WriteSDCard is not found.                        //--- ---    *** != 0xff87cacc
NHSTUB(add_ptp_handler                        ,0xffa191dc) //  1 96%
NHSTUB(exmem_alloc                            ,0xff812954) //  1 92%
// ERROR: free is not found.                               //--- ---    *** != 0xffabcc78
// ERROR: kbd_p1_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_p1_f_cont is not found.                      //--- ---    *** != 0xff828fec
// ERROR: kbd_p2_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0x00000000
//NHSTUB(kbd_pwr_off                          ,0xffa4794c) //  1 83%    *** != 0xffa476fc
// ALT: NHSTUB(kbd_pwr_off, 0xffa47968) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa476fc) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa47718) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa477e8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa47804) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xffa5c4b8) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xffa5c4e4) // 1 5/4
NHSTUB(malloc                                 ,0xffabcc6c) //  1 53%
NHSTUB(mkdir                                  ,0xff86aacc) //  1 61%
// ALT: NHSTUB(mkdir, 0xff86ab8c) // 1 19/12
NHSTUB(taskIdListGet                          ,0xffac7dd0) //  1 82%
NHSTUB(localtime                              ,0xffab43c0) //  1 93%
// ERROR: Mount_FileSystem is not found.                   //--- ---    *** != 0xff869cd4
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xff94efcc

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff967c5c -> ff967c5c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9625e4) // Found @0xff9625e4,          stubs_min = 0xff9625e4 (0xFF9625E4)
//DEF(FlashParamsTable                        ,0xff9697e0) // Found @0xff9697e0,          stubs_min = 0xff9697e0 (0xFF9697E0)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x53; }                          // Found @0xff96b880

// Misc stuff
// LED table init @ 0xffa6892c
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffacea10, canon_data_len: 0xd340

// For capt_seq.c
DEF(_nrflag,0x53ec) // Found @ ff955494 (0x53ec)
//static long *nrflag = (long*)(0x53ec);       // Found @ ff955494

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff813ec0) //  1
//NHSTUB(Close                                ,0xff86a944) //120            == 0xff86a944
NHSTUB(CreateTask                             ,0xff821a10) //120
NHSTUB(DebugAssert                            ,0xff813e68) //1100
NHSTUB(DeleteFile_Fut                         ,0xff8635f0) //  1
NHSTUB(DoAELock                               ,0xff94f22c) //120
//NHSTUB(DoAFLock                             ,0xff94efcc) //120            == 0xff94efcc
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
//NHSTUB(GetBatteryTemperature                ,0xffa4da78) //102            == 0xffa4da78
//NHSTUB(GetCCDTemperature                    ,0xffa4da64) //102            == 0xffa4da64
//NHSTUB(GetDrive_ClusterSize                 ,0xff86a150) //119            == 0xff86a150
//NHSTUB(GetDrive_FreeClusters                ,0xff86a1c8) //1103            == 0xff86a1c8
//NHSTUB(GetDrive_TotalClusters               ,0xff86a18c) //119            == 0xff86a18c
//NHSTUB(GetOpticalTemperature                ,0xffa4da50) //120            == 0xffa4da50
//NHSTUB(GetZoomLensCurrentPoint              ,0xffa56fbc) //120            == 0xffa56fbc
//NHSTUB(GetZoomLensCurrentPosition           ,0xffa56fd0) //102            == 0xffa56fd0
NHSTUB(GiveSemaphore                          ,0xff8213c8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff9086f0) //  1
NHSTUB(LEDDrive                               ,0xffa6851c) //120
NHSTUB(LocalTime                              ,0xff813e2c) //115
NHSTUB(LockMainPower                          ,0xff9679d4) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86367c) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa715d8) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa56e38) //120
//NHSTUB(Open                                 ,0xff86a938) //120            == 0xff86a938
NHSTUB(PostLogicalEventForNotPowerType        ,0xff964d60) //120
NHSTUB(PostLogicalEventToUI                   ,0xff964dec) //120
//NHSTUB(Read                                 ,0xff86a9a4) //120            == 0xff86a9a4
NHSTUB(RefreshPhysicalScreen                  ,0xff97b5c8) //120
NHSTUB(RenameFile_Fut                         ,0xff863570) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa7393c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9678cc) //120
NHSTUB(SetLogicalEventActive                  ,0xff96627c) //1104
//NHSTUB(SetScriptMode                        ,0xff9662e0) //120            == 0xff9662e0
NHSTUB(SleepTask                              ,0xff821870) //120
NHSTUB(TakeSemaphore                          ,0xff8211e0) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a3664) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a3638) //  1
NHSTUB(TurnOnDisplay                          ,0xff931c1c) //120
NHSTUB(TurnOffDisplay                         ,0xff931c2c) //120
NHSTUB(UnlockAE                               ,0xff94f280) //120
//NHSTUB(UnlockAF                             ,0xff94f044) //120            == 0xff94f044
NHSTUB(UnlockMainPower                        ,0xff967a88) //120
//NHSTUB(Write                                ,0xff86a9b0) //120            == 0xff86a9b0
NHSTUB(_log                                   ,0xffaa61ac) //121
NHSTUB(_log10                                 ,0xffaa6854) //121
NHSTUB(_pow                                   ,0xffaa6d44) //121
NHSTUB(_sqrt                                  ,0xffaab090) //  1
NHSTUB(apex2us                                ,0xff8adbe8) //  1
NHSTUB(close                                  ,0xffab9c2c) //109
NHSTUB(lseek                                  ,0xffab9d70) //  1
NHSTUB(memcmp                                 ,0xffab37a0) //120
NHSTUB(memcpy                                 ,0xffab37dc) //120
NHSTUB(memset                                 ,0xffab3854) //120
NHSTUB(open                                   ,0xffaba270) //  1
NHSTUB(closedir                               ,0xffab5bcc) //  1
NHSTUB(qsort                                  ,0xffab3000) //  1
NHSTUB(rand                                   ,0xffab3024) //  1
NHSTUB(realloc                                ,0xffa9d7ac) //115
NHSTUB(srand                                  ,0xffab3048) //  1
NHSTUB(stat                                   ,0xffab5c94) //  1
NHSTUB(strcat                                 ,0xffab3874) //  1
NHSTUB(strchr                                 ,0xffab38a0) //  1
NHSTUB(strcmp                                 ,0xffab38c4) //120
NHSTUB(strcpy                                 ,0xffab3a58) //120
NHSTUB(strftime                               ,0xffab50e0) //  1
NHSTUB(strlen                                 ,0xffab3bbc) //120
NHSTUB(strncmp                                ,0xffab3c20) //  1
NHSTUB(strncpy                                ,0xffab3c64) //  1
NHSTUB(strrchr                                ,0xffab3ce8) //  1
NHSTUB(strtol                                 ,0xffab343c) //  1
NHSTUB(isdigit                                ,0xffaafb70) //  1
NHSTUB(isspace                                ,0xffaafbe8) //  1
NHSTUB(isalpha                                ,0xffaafb40) //  1
NHSTUB(isupper                                ,0xffaafc00) //  1
NHSTUB(islower                                ,0xffaafba0) //  1
NHSTUB(ispunct                                ,0xffaafbd0) //  1
NHSTUB(isxdigit                               ,0xffaafc18) //  1
NHSTUB(toupper                                ,0xffaafc40) //  1
NHSTUB(tolower                                ,0xffaafc30) //  1
NHSTUB(taskLock                               ,0xffac848c) //  1
NHSTUB(taskUnlock                             ,0xffac8534) //  1
NHSTUB(taskName                               ,0xffac7cc8) //  1
NHSTUB(errnoOfTaskGet                         ,0xffab6398) //  1
NHSTUB(readdir                                ,0xffab5b98) //  1
NHSTUB(strtoul                                ,0xffab35e4) //  1
NHSTUB(strpbrk                                ,0xffab3cac) //  1
NHSTUB(utime                                  ,0xffab5d28) //  1
NHSTUB(mktime                                 ,0xffab4588) //  1
NHSTUB(opendir                                ,0xffab5c00) //  1
NHSTUB(memchr                                 ,0xffab376c) //  1
NHSTUB(memPartInfoGet                         ,0xffabd08c) //  1
NHSTUB(iosDrvInstall                          ,0xffabb110) //  1
NHSTUB(iosDevAdd                              ,0xffabae4c) //  1
NHSTUB(iosDevDelete                           ,0xffabae24) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa71348) //  1
NHSTUB(taskCreateHookAdd                      ,0xffac02ec) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffac0228) //  1
NHSTUB(Unmount_FileSystem                     ,0xff869d34) //  1
NHSTUB(taskSuspend                            ,0xffac7ed8) //  1
NHSTUB(taskResume                             ,0xffac80ac) //  1
NHSTUB(time                                   ,0xffab510c) //  1
NHSTUB(vsprintf                               ,0xffab74ec) //115
NHSTUB(EngDrvRead                             ,0xff87ee58) //102
