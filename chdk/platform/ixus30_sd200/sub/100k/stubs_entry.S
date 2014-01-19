// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Version 1.00K   // Found @ 0xff81e41c, "1.00K" @ 0xff81e42d
//   Firmware build timestamp: Sep  9 2004 21:36:16
//   Canon DIGITAL IXUS 30

// Values for makefile.inc
//   PLATFORMID = 12480 (0x30c0) // Found @ 0xffd7014e
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00072d40

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff815288) //  1 65%
// ERROR: Close is not found.                              //--- ---    *** != 0xffac265c
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xff93df9c
// ERROR: ExecuteEventProcedure is not found.              //--- ---    *** != 0xff81756c
// ERROR: ExitFromCompensationEVF is not found.            //--- ---    *** != 0xff93dfdc
// ERROR: FreeUncacheableMemory is not found.              //--- ---    *** != 0xff8152bc
// ERROR: GetFocusLensSubjectDistance is not found.        //--- ---    *** != 0xffa5f808
// ERROR: GetFocusLensSubjectDistanceFromLens is not found.  //--- ---    *** != 0xffa5fe7c
// ERROR: GetParameterData is not found.                   //--- ---    *** != 0x00000000
// ERROR: GetPropertyCase is not found.                    //--- ---    *** != 0x00000000
NHSTUB(GetSystemTime                          ,0xff815638) //  1 96%
// ALT: NHSTUB(GetSystemTime, 0xfff05c38) // 1 26/1
// ALT: NHSTUB(GetSystemTime, 0xfff05c38) // 2 26/1
//NHSTUB(GetZoomLensCurrentPoint              ,0xffa51f18) //120        *** != 0xffa50fe8
// ERROR: IsStrobeChargeCompleted is not found.            //--- ---    *** != 0x00000000
// ERROR: Open is not found.                               //--- ---    *** != 0xffac2ca0
// ERROR: PT_PlaySound is not found.                       //--- ---    *** != 0xff94f078
NHSTUB(PutInNdFilter                          ,0xffa69184) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa6a834) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa6a87c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa6a834) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa6a87c) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa691cc) //  1 94%
// ERROR: Read is not found.                               //--- ---    *** != 0xffac26bc
//NHSTUB(Remove                               ,0xff8c04cc) //  3 52%    *** != 0xff871694
//NHSTUB(Restart                              ,0xff824f50) //  1 80%    *** != 0xff824f58
// ERROR: SetCurrentCaptureModeType is not found.          //--- ---    *** != 0x00000000
NHSTUB(SetFileAttributes                      ,0xff8717e0) //  1 58%
// ALT: NHSTUB(SetFileAttributes, 0xfff1bc4c) // 1 17/12
//NHSTUB(SetLogicalEventActive                ,0xff955978) //  3 62%    *** != 0x00000000
// ERROR: SetParameterData is not found.                   //--- ---    *** != 0x00000000
// ERROR: SetPropertyCase is not found.                    //--- ---    *** != 0x00000000
// ERROR: SetScriptMode is not found.                      //--- ---    *** != 0xff9559e0
NHSTUB(UpdateMBROnFlash                       ,0xff8704d0) //  1 96%
// ERROR: VbattGet is not found.                           //--- ---    *** != 0xffa5ba68
// ERROR: Write is not found.                              //--- ---    *** != 0xffac272c
// ERROR: WriteSDCard is not found.                        //--- ---    *** != 0x00000000
NHSTUB(add_ptp_handler                        ,0xffa138bc) //  1 96%
NHSTUB(exmem_alloc                            ,0xff813a1c) //  1 92%
// ALT: NHSTUB(exmem_alloc, 0xfff164cc) // 1 23/2
// ERROR: free is not found.                               //--- ---    *** != 0xffac56a8
// ERROR: kbd_p1_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_p1_f_cont is not found.                      //--- ---    *** != 0xff830ab4
// ERROR: kbd_p2_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0x00000000
//NHSTUB(kbd_pwr_off                          ,0xffa4199c) //  1 83%    *** != 0xffa4155c
// ALT: NHSTUB(kbd_pwr_off, 0xffa419b8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30af0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30b0c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30ff8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff31014) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa4155c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa41578) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa41648) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa41664) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa41744) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xffa41760) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30bb8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30bd4) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30ca4) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30cc0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30da0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xfff30dbc) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xffa57374) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xffa573a0) // 1 5/4
NHSTUB(malloc                                 ,0xffac569c) //  1 53%
// ALT: NHSTUB(malloc, 0xfff5997c) // 1 15/13
// ALT: NHSTUB(malloc, 0xfff5997c) // 2 15/13
NHSTUB(mkdir                                  ,0xff871810) //  1 61%
// ALT: NHSTUB(mkdir, 0xff8718d0) // 1 19/12
// ALT: NHSTUB(mkdir, 0xfff1bc7c) // 1 19/12
// ALT: NHSTUB(mkdir, 0xfff1bd3c) // 1 19/12
NHSTUB(taskIdListGet                          ,0xffad0948) //  1 82%
// ALT: NHSTUB(taskIdListGet, 0xfff73b14) // 1 24/5
NHSTUB(localtime                              ,0xffabcc84) //  1 93%
// ALT: NHSTUB(localtime, 0xfff50f64) // 1 27/2
// ERROR: memPartInfoGet is not found.                     //--- ---    *** != 0x00000000
// ERROR: Mount_FileSystem is not found.                   //--- ---    *** != 0xff8702e4
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000
//NHSTUB(time                                 ,0xffabd9d0) //  1        *** != 0x00000000
// ALT: NHSTUB(time, 0xfff51cb0) // 1 25/0

// Check of modemap from 'platform/CAMERA/shooting.c':

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9512ac) // Found @0xff9512ac,          stubs_min = 0xff9512ac (0xff9512ac)
//DEF(FlashParamsTable                        ,0xff957ef4) // Found @0xff957ef4,          stubs_min = 0xff957ef4 (0xff957ef4)

// Values below go in 'lib.c':

// Misc stuff
// canon_data_src: 0xffad74a0, canon_data_len: 0xeae0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(CreateTask                             ,0xff823784) //120
NHSTUB(DebugAssert                            ,0xff814c10) //1100
NHSTUB(DeleteFile_Fut                         ,0xff8699b4) //  1
// ALT: NHSTUB(DeleteFile_Fut, 0xfff17058) // 1 10/0
NHSTUB(DoAELock                               ,0xff93e058) //120
//NHSTUB(DoAFLock                             ,0xff93de38) //120            == 0xff93de38
NHSTUB(ExitTask                               ,0xff823b44) //120
NHSTUB(Fclose_Fut                             ,0xff869af4) //  1
//NHSTUB(Feof_Fut                             ,0xff869d08) //  1            == 0xff869d08
// ALT: NHSTUB(Feof_Fut, 0xfff1732c) // 1 10/0
NHSTUB(Fflush_Fut                             ,0xff869d40) //  1
NHSTUB(Fgets_Fut                              ,0xff869c78) //  1
// ALT: NHSTUB(Fgets_Fut, 0xfff1729c) // 1 15/0
NHSTUB(Fopen_Fut                              ,0xff869ab8) //  1
NHSTUB(Fread_Fut                              ,0xff869bd8) //  1
// ALT: NHSTUB(Fread_Fut, 0xfff171fc) // 1 25/0
NHSTUB(Fseek_Fut                              ,0xff869cc0) //  1
// ALT: NHSTUB(Fseek_Fut, 0xfff172e4) // 1 24/0
NHSTUB(Fwrite_Fut                             ,0xff869c28) //  1
// ALT: NHSTUB(Fwrite_Fut, 0xfff1724c) // 1 26/0
//NHSTUB(GetBatteryTemperature                ,0xffa486ac) //102            == 0xffa486ac
//NHSTUB(GetCCDTemperature                    ,0xffa48698) //102            == 0xffa48698
//NHSTUB(GetCurrentAvValue                    ,0xffa690a4) //120            == 0xffa690a4
//NHSTUB(GetDrive_ClusterSize                 ,0xff8707ec) //119            == 0xff8707ec
//NHSTUB(GetDrive_FreeClusters                ,0xff87086c) //1103            == 0xff87086c
//NHSTUB(GetDrive_TotalClusters               ,0xff87082c) //119            == 0xff87082c
//NHSTUB(GetOpticalTemperature                ,0xffa48684) //120            == 0xffa48684
//NHSTUB(GetZoomLensCurrentPosition           ,0xffa51f24) //102            == 0xffa51f24
//NHSTUB(GiveSemaphore                        ,0xff823144) //120            == 0xff823144
NHSTUB(LEDDrive                               ,0xffa62dbc) //120
NHSTUB(LocalTime                              ,0xff814bc4) //115
//NHSTUB(LockMainPower                        ,0xff955f58) //120            == 0xff955f58
NHSTUB(MakeDirectory_Fut                      ,0xff869a40) //  1
// ALT: NHSTUB(MakeDirectory_Fut, 0xfff170e4) // 1 25/0
//NHSTUB(MoveFocusLensToDistance              ,0xffa6ae90) //102            == 0xffa6ae90
NHSTUB(MoveZoomLensWithPoint                  ,0xffa51e1c) //120
NHSTUB(PostLogicalEventForNotPowerType        ,0xff953808) //120
NHSTUB(PostLogicalEventToUI                   ,0xff953894) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff96c30c) //120
NHSTUB(RenameFile_Fut                         ,0xff869934) //  1
// ALT: NHSTUB(RenameFile_Fut, 0xfff16fd8) // 1 27/0
NHSTUB(SetAE_ShutterSpeed                     ,0xffa6d214) //102
//NHSTUB(SetAutoShutdownTime                  ,0xff955e48) //120            == 0xff955e48
NHSTUB(SleepTask                              ,0xff8235e4) //120
NHSTUB(TakeSemaphore                          ,0xff822f5c) //1101
NHSTUB(TurnOffBackLight                       ,0xff99e350) //  1
NHSTUB(TurnOnBackLight                        ,0xff99e324) //  1
NHSTUB(TurnOnDisplay                          ,0xff924fec) //120
NHSTUB(TurnOffDisplay                         ,0xff925014) //120
NHSTUB(UnlockAE                               ,0xff93e0ac) //120
//NHSTUB(UnlockAF                             ,0xff93de98) //120            == 0xff93de98
//NHSTUB(UnlockMainPower                      ,0xff956014) //120            == 0xff956014
NHSTUB(_log                                   ,0xffaae9b0) //121
NHSTUB(_log10                                 ,0xffaaf058) //121
NHSTUB(_pow                                   ,0xffaaf548) //  1
// ALT: NHSTUB(_pow, 0xfff41064) // 1 25/0
NHSTUB(_sqrt                                  ,0xffab3894) //  1
// ALT: NHSTUB(_sqrt, 0xfff45834) // 1 24/0
NHSTUB(apex2us                                ,0xff8a9f58) //  1
NHSTUB(close                                  ,0xffac265c) //  1
// ALT: NHSTUB(close, 0xfff5693c) // 1 29/0
NHSTUB(lseek                                  ,0xffac27a0) //  1
// ALT: NHSTUB(lseek, 0xfff56a80) // 1 28/0
NHSTUB(memcmp                                 ,0xffabc064) //120
NHSTUB(memcpy                                 ,0xffabc0a0) //  1
// ALT: NHSTUB(memcpy, 0xfff50380) // 1 23/0
NHSTUB(memset                                 ,0xffabc118) //120
NHSTUB(open                                   ,0xffac2ca0) //  1
// ALT: NHSTUB(open, 0xfff56f80) // 1 26/0
NHSTUB(closedir                               ,0xffabe490) //  1
// ALT: NHSTUB(closedir, 0xfff52770) // 1 26/0
NHSTUB(qsort                                  ,0xffabb8c4) //  1
// ALT: NHSTUB(qsort, 0xfff4fba4) // 1 13/0
NHSTUB(rand                                   ,0xffabb8e8) //  1
// ALT: NHSTUB(rand, 0xfff4fbc8) // 1 8/0
NHSTUB(srand                                  ,0xffabb90c) //  1
// ALT: NHSTUB(srand, 0xfff4fbec) // 1 4/0
NHSTUB(stat                                   ,0xffabe558) //  1
// ALT: NHSTUB(stat, 0xfff52838) // 1 24/0
NHSTUB(strcat                                 ,0xffabc138) //  1
// ALT: NHSTUB(strcat, 0xfff50418) // 1 8/0
NHSTUB(strchr                                 ,0xffabc164) //  1
// ALT: NHSTUB(strchr, 0xfff50444) // 1 7/0
NHSTUB(strcmp                                 ,0xffabc188) //120
NHSTUB(strcpy                                 ,0xffabc31c) //120
NHSTUB(strftime                               ,0xffabd9a4) //  1
// ALT: NHSTUB(strftime, 0xfff51c84) // 1 6/0
NHSTUB(strlen                                 ,0xffabc480) //120
NHSTUB(strncmp                                ,0xffabc4e4) //  1
// ALT: NHSTUB(strncmp, 0xfff507c4) // 1 11/0
NHSTUB(strncpy                                ,0xffabc528) //  1
// ALT: NHSTUB(strncpy, 0xfff50808) // 1 24/0
NHSTUB(strrchr                                ,0xffabc5ac) //  1
// ALT: NHSTUB(strrchr, 0xfff5088c) // 1 8/0
NHSTUB(strtol                                 ,0xffabbd00) //  1
// ALT: NHSTUB(strtol, 0xfff4ffe0) // 1 26/0
NHSTUB(isdigit                                ,0xffab8374) //  1
// ALT: NHSTUB(isdigit, 0xfff4c654) // 1 4/0
NHSTUB(isspace                                ,0xffab83ec) //  1
// ALT: NHSTUB(isspace, 0xfff4c6cc) // 1 4/0
NHSTUB(isalpha                                ,0xffab8344) //  1
// ALT: NHSTUB(isalpha, 0xfff4c624) // 1 4/0
NHSTUB(isupper                                ,0xffab8404) //  1
// ALT: NHSTUB(isupper, 0xfff4c6e4) // 1 4/0
NHSTUB(islower                                ,0xffab83a4) //  1
// ALT: NHSTUB(islower, 0xfff4c684) // 1 4/0
NHSTUB(ispunct                                ,0xffab83d4) //  1
// ALT: NHSTUB(ispunct, 0xfff4c6b4) // 1 4/0
NHSTUB(isxdigit                               ,0xffab841c) //  1
// ALT: NHSTUB(isxdigit, 0xfff4c6fc) // 1 4/0
NHSTUB(toupper                                ,0xffab8444) //  1
// ALT: NHSTUB(toupper, 0xfff4c724) // 1 4/0
NHSTUB(tolower                                ,0xffab8434) //  1
// ALT: NHSTUB(tolower, 0xfff4c714) // 1 4/0
NHSTUB(taskLock                               ,0xffad1004) //  1
// ALT: NHSTUB(taskLock, 0xfff741d0) // 1 31/0
NHSTUB(taskUnlock                             ,0xffad10ac) //  1
// ALT: NHSTUB(taskUnlock, 0xfff74278) // 1 31/0
NHSTUB(taskName                               ,0xffad0840) //  1
// ALT: NHSTUB(taskName, 0xfff73a0c) // 1 25/0
NHSTUB(errnoOfTaskGet                         ,0xffabec5c) //  1
// ALT: NHSTUB(errnoOfTaskGet, 0xfff52f3c) // 1 15/0
NHSTUB(readdir                                ,0xffabe45c) //  1
// ALT: NHSTUB(readdir, 0xfff5273c) // 1 11/0
NHSTUB(strtoul                                ,0xffabbea8) //  1
// ALT: NHSTUB(strtoul, 0xfff50188) // 1 26/0
NHSTUB(strpbrk                                ,0xffabc570) //  1
// ALT: NHSTUB(strpbrk, 0xfff50850) // 1 19/0
NHSTUB(utime                                  ,0xffabe5ec) //  1
// ALT: NHSTUB(utime, 0xfff528cc) // 1 26/0
NHSTUB(mktime                                 ,0xffabce4c) //  1
// ALT: NHSTUB(mktime, 0xfff5112c) // 1 28/0
NHSTUB(opendir                                ,0xffabe4c4) //  1
// ALT: NHSTUB(opendir, 0xfff527a4) // 1 29/0
NHSTUB(memchr                                 ,0xffabc030) //  1
// ALT: NHSTUB(memchr, 0xfff50310) // 1 19/0
NHSTUB(iosDrvInstall                          ,0xffac3b40) //  1
// ALT: NHSTUB(iosDrvInstall, 0xfff57e20) // 1 30/0
NHSTUB(iosDevAdd                              ,0xffac387c) //  1
// ALT: NHSTUB(iosDevAdd, 0xfff57b5c) // 1 28/0
NHSTUB(iosDevDelete                           ,0xffac3854) //  1
// ALT: NHSTUB(iosDevDelete, 0xfff57b34) // 1 28/0
NHSTUB(GetCurrentTargetDistance               ,0xffa6ac00) //  1
NHSTUB(taskCreateHookAdd                      ,0xffac87e8) //  1
// ALT: NHSTUB(taskCreateHookAdd, 0xfff5df1c) // 1 29/0
NHSTUB(taskDeleteHookAdd                      ,0xffac8724) //  1
// ALT: NHSTUB(taskDeleteHookAdd, 0xfff5de58) // 1 28/0
NHSTUB(Unmount_FileSystem                     ,0xff870344) //  1
// ALT: NHSTUB(Unmount_FileSystem, 0xfff1aab4) // 1 18/0
NHSTUB(taskSuspend                            ,0xffad0a50) //  1
// ALT: NHSTUB(taskSuspend, 0xfff73c1c) // 1 31/0
NHSTUB(taskResume                             ,0xffad0c24) //  1
// ALT: NHSTUB(taskResume, 0xfff73df0) // 1 31/0
NHSTUB(vsprintf                               ,0xffabfdb0) //  1
// ALT: NHSTUB(vsprintf, 0xfff54090) // 1 13/0
NHSTUB(EngDrvRead                             ,0xff885974) //102
