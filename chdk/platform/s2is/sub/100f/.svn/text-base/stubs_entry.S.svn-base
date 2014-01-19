// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00F   // Found @ 0xff81ada0, "GM1.00F" @ 0xff81adad
//   Firmware build timestamp: Jul 11 2005 16:09:30
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.03MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0006ef50

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xff968128
//NHSTUB(ExitFromCompensationEVF              ,0xff96b6b4) //  1 70%    *** != 0xff96817c
NHSTUB(GetFocusLensSubjectDistance            ,0xffa8e9ec) //  1 87%
// ERROR: GetFocusLensSubjectDistanceFromLens is not found.  //--- ---    *** != 0xffa8ef74
NHSTUB(GetParameterData                       ,0xff987fb8) //  1 76%
//NHSTUB(GetPropertyCase                      ,0xff825d04) //  2 71%    *** != 0xff825d08
NHSTUB(GetSystemTime                          ,0xff814b98) //  1 96%
//NHSTUB(GetZoomLensCurrentPoint              ,0xffa881e0) //120        *** != 0xffaa8824
//NHSTUB(GetZoomLensCurrentPosition           ,0xffa881f4) //102        *** != 0xffaa8838
NHSTUB(PutInNdFilter                          ,0xffaa6d58) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffaa6da0) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa7168) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa88fc) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa8944) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa6da0) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa7168) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa88fc) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffaa8944) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffaa71b0) //  1 94%
//NHSTUB(Remove                               ,0xff8d290c) //  3 52%    *** != 0xff877380
//NHSTUB(Restart                              ,0xff823de4) //  1 84%    *** != 0xff823de8
NHSTUB(SetCurrentCaptureModeType              ,0xff9aed0c) //  1 73%
NHSTUB(SetFileAttributes                      ,0xff8774cc) //  1 58%
//NHSTUB(SetParameterData                     ,0xff987fb4) //  1 66%    *** != 0xff987ee4
// ERROR: SetPropertyCase is not found.                    //--- ---    *** != 0xff825c00
NHSTUB(UpdateMBROnFlash                       ,0xff876480) //  1 96%
// ERROR: WriteSDCard is not found.                        //--- ---    *** != 0x00000000
NHSTUB(add_ptp_handler                        ,0xffa4bc20) //  1 96%
NHSTUB(exmem_alloc                            ,0xff812a74) //  1 92%
// ERROR: free is not found.                               //--- ---    *** != 0xffaf758c
// ERROR: kbd_p1_f is not found.                           //--- ---    *** != 0xff829470
// ERROR: kbd_p1_f_cont is not found.                      //--- ---    *** != 0xff829484
// ERROR: kbd_p2_f is not found.                           //--- ---    *** != 0xff829364
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0xff829e58
//NHSTUB(kbd_pwr_off                          ,0xff82b0d4) //  1 83%    *** != 0xff82ae84
// ALT: NHSTUB(kbd_pwr_off, 0xff82b0f0) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82ae84) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82aea0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82af70) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82af8c) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xff9402b0) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff9402dc) // 1 5/4
NHSTUB(malloc                                 ,0xffaf7580) //  1 53%
NHSTUB(mkdir                                  ,0xff8774fc) //  1 61%
// ALT: NHSTUB(mkdir, 0xff8775bc) // 1 19/12
NHSTUB(taskIdListGet                          ,0xffb026e4) //  1 82%
NHSTUB(localtime                              ,0xffaeecd4) //  1 93%
// ERROR: Mount_FileSystem is not found.                   //--- ---    *** != 0xff876264
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff983750 -> ff983750
// Strange mode 0x00020011 in firmware but not in current modemap
// Strange mode 0x00030012 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff97d904) // Found @0xff97d904,          stubs_min = 0xff97d904 (0xFF97D904)
//DEF(FlashParamsTable                        ,0xff985878) // Found @0xff985878,          stubs_min = 0xff985878 (0xFF985878)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x55; }                          // Found @0xff988024

// Misc stuff
// LED table init @ 0xff82ecb0
// LED #1: 0xc022008c, offset 0x104
// LED #2: 0xc0220088, offset 0x144
// LED #3: 0xc02200fc, offset 0x1c4

// canon_data_src: 0xffb09320, canon_data_len: 0xdbb0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814810) //  1
//NHSTUB(Close                                ,0xff877374) //120            == 0xff877374
NHSTUB(CreateTask                             ,0xff82239c) //120
NHSTUB(DebugAssert                            ,0xff813d58) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86fbf4) //  1
NHSTUB(DoAELock                               ,0xff968244) //120
//NHSTUB(DoAFLock                             ,0xff967f48) //120            == 0xff967f48
NHSTUB(ExecuteEventProcedure                  ,0xff816ab4) //  1
NHSTUB(ExitTask                               ,0xff82275c) //120
NHSTUB(Fclose_Fut                             ,0xff86fd34) //  1
NHSTUB(Feof_Fut                               ,0xff86ff48) //  1
NHSTUB(Fflush_Fut                             ,0xff86ff80) //  1
NHSTUB(Fgets_Fut                              ,0xff86feb8) //  1
NHSTUB(Fopen_Fut                              ,0xff86fcf8) //  1
NHSTUB(Fread_Fut                              ,0xff86fe18) //  1
NHSTUB(FreeUncacheableMemory                  ,0xff814844) //  1
NHSTUB(Fseek_Fut                              ,0xff86ff00) //  1
NHSTUB(Fwrite_Fut                             ,0xff86fe68) //  1
//NHSTUB(GetBatteryTemperature                ,0xff82e368) //102            == 0xff82e368
//NHSTUB(GetCCDTemperature                    ,0xff82e354) //102            == 0xff82e354
NHSTUB(GetCurrentAvValue                      ,0xffaa6d44) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff8767a0) //119            == 0xff8767a0
//NHSTUB(GetDrive_FreeClusters                ,0xff876838) //1103            == 0xff876838
//NHSTUB(GetDrive_TotalClusters               ,0xff8767fc) //119            == 0xff8767fc
//NHSTUB(GetOpticalTemperature                ,0xff82e340) //120            == 0xff82e340
NHSTUB(GiveSemaphore                          ,0xff821d54) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff912ee0) //  1
NHSTUB(LEDDrive                               ,0xff82e880) //120
NHSTUB(LocalTime                              ,0xff8144d8) //115
NHSTUB(LockMainPower                          ,0xff9834c8) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86fc80) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffaa8f30) //102
//NHSTUB(MoveZoomLensWithPoint                ,0xffa88000) //120            == 0xffa88000
//NHSTUB(Open                                 ,0xff877368) //120            == 0xff877368
NHSTUB(PT_PlaySound                           ,0xff97bd18) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff980158) //120
NHSTUB(PostLogicalEventToUI                   ,0xff9801e4) //120
//NHSTUB(Read                                 ,0xff8773d4) //120            == 0xff8773d4
NHSTUB(RefreshPhysicalScreen                  ,0xff9988b4) //120
NHSTUB(RenameFile_Fut                         ,0xff86fb74) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffaabe0c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9833c0) //120
NHSTUB(SetLogicalEventActive                  ,0xff981968) //1104
//NHSTUB(SetScriptMode                        ,0xff9819cc) //120            == 0xff9819cc
NHSTUB(SleepTask                              ,0xff8221fc) //120
NHSTUB(TakeSemaphore                          ,0xff821b6c) //1101
NHSTUB(TurnOffBackLight                       ,0xff9cbed8) //  1
NHSTUB(TurnOnBackLight                        ,0xff9cbeac) //  1
NHSTUB(TurnOnDisplay                          ,0xff93d050) //120
NHSTUB(TurnOffDisplay                         ,0xff93d060) //120
NHSTUB(UnlockAE                               ,0xff968298) //120
//NHSTUB(UnlockAF                             ,0xff968024) //120            == 0xff968024
NHSTUB(UnlockMainPower                        ,0xff98357c) //120
//NHSTUB(VbattGet                             ,0xff82d570) //120            == 0xff82d570
//NHSTUB(Write                                ,0xff8773e0) //120            == 0xff8773e0
NHSTUB(_log                                   ,0xffae0ac0) //121
NHSTUB(_log10                                 ,0xffae1168) //121
NHSTUB(_pow                                   ,0xffae1658) //121
NHSTUB(_sqrt                                  ,0xffae59a4) //  1
NHSTUB(apex2us                                ,0xff8bbe28) //  1
NHSTUB(close                                  ,0xffaf4540) //109
NHSTUB(lseek                                  ,0xffaf4684) //  1
NHSTUB(memcmp                                 ,0xffaee0b4) //120
NHSTUB(memcpy                                 ,0xffaee0f0) //120
NHSTUB(memset                                 ,0xffaee168) //120
NHSTUB(open                                   ,0xffaf4b84) //  1
NHSTUB(closedir                               ,0xffaf04e0) //  1
NHSTUB(qsort                                  ,0xffaed914) //  1
NHSTUB(rand                                   ,0xffaed938) //  1
NHSTUB(realloc                                ,0xffad75b4) //115
NHSTUB(srand                                  ,0xffaed95c) //  1
NHSTUB(stat                                   ,0xffaf05a8) //  1
NHSTUB(strcat                                 ,0xffaee188) //  1
NHSTUB(strchr                                 ,0xffaee1b4) //  1
NHSTUB(strcmp                                 ,0xffaee1d8) //120
NHSTUB(strcpy                                 ,0xffaee36c) //120
NHSTUB(strftime                               ,0xffaef9f4) //  1
NHSTUB(strlen                                 ,0xffaee4d0) //120
NHSTUB(strncmp                                ,0xffaee534) //  1
NHSTUB(strncpy                                ,0xffaee578) //  1
NHSTUB(strrchr                                ,0xffaee5fc) //  1
NHSTUB(strtol                                 ,0xffaedd50) //  1
NHSTUB(isdigit                                ,0xffaea484) //  1
NHSTUB(isspace                                ,0xffaea4fc) //  1
NHSTUB(isalpha                                ,0xffaea454) //  1
NHSTUB(isupper                                ,0xffaea514) //  1
NHSTUB(islower                                ,0xffaea4b4) //  1
NHSTUB(ispunct                                ,0xffaea4e4) //  1
NHSTUB(isxdigit                               ,0xffaea52c) //  1
NHSTUB(toupper                                ,0xffaea554) //  1
NHSTUB(tolower                                ,0xffaea544) //  1
NHSTUB(taskLock                               ,0xffb02da0) //  1
NHSTUB(taskUnlock                             ,0xffb02e48) //  1
NHSTUB(taskName                               ,0xffb025dc) //  1
NHSTUB(errnoOfTaskGet                         ,0xffaf0cac) //  1
NHSTUB(readdir                                ,0xffaf04ac) //  1
NHSTUB(strtoul                                ,0xffaedef8) //  1
NHSTUB(strpbrk                                ,0xffaee5c0) //  1
NHSTUB(utime                                  ,0xffaf063c) //  1
NHSTUB(mktime                                 ,0xffaeee9c) //  1
NHSTUB(opendir                                ,0xffaf0514) //  1
NHSTUB(memchr                                 ,0xffaee080) //  1
NHSTUB(memPartInfoGet                         ,0xffaf79a0) //  1
NHSTUB(iosDrvInstall                          ,0xffaf5a24) //  1
NHSTUB(iosDevAdd                              ,0xffaf5760) //  1
NHSTUB(iosDevDelete                           ,0xffaf5738) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffaa8ca0) //  1
NHSTUB(taskCreateHookAdd                      ,0xffafac00) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffafab3c) //  1
NHSTUB(Unmount_FileSystem                     ,0xff8762d4) //  1
NHSTUB(taskSuspend                            ,0xffb027ec) //  1
NHSTUB(taskResume                             ,0xffb029c0) //  1
NHSTUB(time                                   ,0xffaefa20) //  1
NHSTUB(vsprintf                               ,0xffaf1e00) //115
NHSTUB(EngDrvRead                             ,0xff88b518) //102
