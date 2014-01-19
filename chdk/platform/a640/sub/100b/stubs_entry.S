// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00B   // Found @ 0xffc0a398, "GM1.00B" @ 0xffc0a3a5
//   Firmware build timestamp: Jul 10 2006 21:16:20
//   Possible corrupt firmware dump - file size too small for start address 0xffc00000
//     file size = 3.11MB, should be 4.00MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00094d10

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xffd5235c) //  2 90%
//NHSTUB(ExitFromCompensationEVF              ,0xffd55af8) //  2 66%    *** != 0xffd55be0
// ALT: NHSTUB(ExitFromCompensationEVF, 0xffd55b54) // 2 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xffd55c10) // 2 20/10
NHSTUB(GetFocusLensSubjectDistance            ,0xffea4e74) //  2 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffea5428) //  2 57%
NHSTUB(GetPropertyCase                        ,0xffc15484) //  2 92%
NHSTUB(PutInNdFilter                          ,0xffeb0e50) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffeb0e98) //  1 94%
//NHSTUB(Remove                               ,0xffcc2470) //  3 52%
NHSTUB(Restart                                ,0xffc13674) //  1 96%
NHSTUB(UnsetZoomForMovie                      ,0xffda5544) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffe57464) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffefd1ac
NHSTUB(malloc                                 ,0xffefd1a0) //  1 53%
NHSTUB(taskIdListGet                          ,0xfff09dc8) //  1 82%
NHSTUB(localtime                              ,0xffef5ddc) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffc618d0) //  1 90%
NHSTUB(MakeAFScan                             ,0xffd56c30) //  2 79%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd6ade8 -> ffd6ade8
// Mode  8221 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd63808) // Found @0xffd63808,          stubs_min = 0xffd63808 (0xFFD63808)
//DEF(FlashParamsTable                        ,0xffd6d590) // Found @0xffd6d590,          stubs_min = 0xffd6d590 (0xFFD6D590)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6e; }                          // Found @0xffd70564

// Misc stuff
// LED table init @ 0xffc1e788
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220094, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xfff10030, canon_data_len: 0xbdb0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc04b00) //  1
NHSTUB(Close                                  ,0xffc625a8) //120
NHSTUB(CreateTask                             ,0xffc12154) //120
NHSTUB(DebugAssert                            ,0xffc03cf8) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc5b46c) //  1
NHSTUB(DoAELock                               ,0xffd523fc) //120
//NHSTUB(DoAFLock                             ,0xffd521e8) //120            == 0xffd521e8
NHSTUB(ExecuteEventProcedure                  ,0xffc0699c) //  1
NHSTUB(ExitTask                               ,0xffc12514) //120
NHSTUB(Fclose_Fut                             ,0xffc5b5e0) //120
NHSTUB(Feof_Fut                               ,0xffc5b7dc) //  3
NHSTUB(Fflush_Fut                             ,0xffc5b818) //  3
NHSTUB(Fgets_Fut                              ,0xffc5b744) //  3
NHSTUB(Fopen_Fut                              ,0xffc5b5a0) //120
NHSTUB(Fread_Fut                              ,0xffc5b69c) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc04b34) //  1
NHSTUB(Fseek_Fut                              ,0xffc5b790) //120
NHSTUB(Fwrite_Fut                             ,0xffc5b6f0) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1de44) //102
NHSTUB(GetCCDTemperature                      ,0xffc1de30) //102
NHSTUB(GetCurrentAvValue                      ,0xffeb09c8) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xffc61d94) //119            == 0xffc61d94
//NHSTUB(GetDrive_FreeClusters                ,0xffc61e0c) //1103            == 0xffc61e0c
NHSTUB(GetDrive_TotalClusters                 ,0xffc61dd0) //119
NHSTUB(GetOpticalTemperature                  ,0xffc1de1c) //120
NHSTUB(GetParameterData                       ,0xffd704f8) //  2
NHSTUB(GetSystemTime                          ,0xffc04d38) //  2
NHSTUB(GetZoomLensCurrentPoint                ,0xffe912a0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe912b4) //102
NHSTUB(GiveSemaphore                          ,0xffc11d4c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffd0a4a8) //  2
NHSTUB(LEDDrive                               ,0xffc1e39c) //120
NHSTUB(LocalTime                              ,0xffc043c8) //115
NHSTUB(LockMainPower                          ,0xffd6ab88) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc5b520) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffeb3168) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe91180) //120
NHSTUB(Open                                   ,0xffc62580) //120
NHSTUB(PT_PlaySound                           ,0xffd61a04) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd66914) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd66990) //120
NHSTUB(Read                                   ,0xffc6263c) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd822a0) //120
NHSTUB(RenameFile_Fut                         ,0xffc5b3c4) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffeb5e3c) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd6aa8c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd99768) //120
NHSTUB(SetFileAttributes                      ,0xffc627d0) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd686e8) //1104
NHSTUB(SetParameterData                       ,0xffd70418) //  2
NHSTUB(SetPropertyCase                        ,0xffc15334) //  2
//NHSTUB(SetScriptMode                        ,0xffd68750) //120            == 0xffd68750
NHSTUB(SleepTask                              ,0xffc12068) //120
NHSTUB(TakeSemaphore                          ,0xffc11b64) //1101
NHSTUB(TurnOffBackLight                       ,0xffdba500) //  2
NHSTUB(TurnOnBackLight                        ,0xffdba4d0) //  2
NHSTUB(TurnOnDisplay                          ,0xffd2ee4c) //120
NHSTUB(TurnOffDisplay                         ,0xffd2ee5c) //120
NHSTUB(UnlockAE                               ,0xffd5241c) //120
NHSTUB(UnlockAF                               ,0xffd5225c) //120
NHSTUB(UnlockMainPower                        ,0xffd6ac20) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc61ac8) //  1
NHSTUB(VbattGet                               ,0xffc1cd70) //120
NHSTUB(Write                                  ,0xffc62648) //120
NHSTUB(WriteSDCard                            ,0xffc718b8) //  2
NHSTUB(_log                                   ,0xffeefc18) //121
NHSTUB(_log10                                 ,0xffeebfb8) //121
NHSTUB(_pow                                   ,0xffeec140) //121
NHSTUB(_sqrt                                  ,0xffeee014) //  1
NHSTUB(apex2us                                ,0xffca536c) //  1
NHSTUB(close                                  ,0xffefa160) //109
NHSTUB(exmem_alloc                            ,0xffc02834) //  2
NHSTUB(kbd_p1_f                               ,0xffc17b18) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc17b24) //109
NHSTUB(kbd_p2_f                               ,0xffc17efc) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc18914) //  1
NHSTUB(kbd_pwr_off                            ,0xffc18f90) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xffc18fc0) // 1 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffc18fdc) // 1 6/0
NHSTUB(kbd_pwr_on                             ,0xffc18f68) //  1
NHSTUB(lseek                                  ,0xffefa2a4) //  1
NHSTUB(memcmp                                 ,0xffef51bc) //120
NHSTUB(memcpy                                 ,0xffef51f8) //120
NHSTUB(memset                                 ,0xffef5270) //120
NHSTUB(mkdir                                  ,0xffc62800) //  1
NHSTUB(open                                   ,0xffefa7a4) //109
NHSTUB(closedir                               ,0xffef75e8) //  1
NHSTUB(qsort                                  ,0xffef4a1c) //  1
NHSTUB(rand                                   ,0xffef4a40) //  1
NHSTUB(realloc                                ,0xffee616c) //115
NHSTUB(srand                                  ,0xffef4a64) //  1
NHSTUB(stat                                   ,0xffef76b0) //  1
NHSTUB(strcat                                 ,0xffef5290) //  1
NHSTUB(strchr                                 ,0xffef52bc) //  1
NHSTUB(strcmp                                 ,0xffef52e0) //120
NHSTUB(strcpy                                 ,0xffef5474) //120
NHSTUB(strftime                               ,0xffef6afc) //  1
NHSTUB(strlen                                 ,0xffef55d8) //120
NHSTUB(strncmp                                ,0xffef563c) //  1
NHSTUB(strncpy                                ,0xffef5680) //  1
NHSTUB(strrchr                                ,0xffef5704) //  1
NHSTUB(strtol                                 ,0xffef4e58) //  1
NHSTUB(isdigit                                ,0xffef158c) //  1
NHSTUB(isspace                                ,0xffef1604) //  1
NHSTUB(isalpha                                ,0xffef155c) //  1
NHSTUB(isupper                                ,0xffef161c) //  1
NHSTUB(islower                                ,0xffef15bc) //  1
NHSTUB(ispunct                                ,0xffef15ec) //  1
NHSTUB(isxdigit                               ,0xffef1634) //  1
NHSTUB(toupper                                ,0xffef165c) //  1
NHSTUB(tolower                                ,0xffef164c) //  1
NHSTUB(taskLock                               ,0xfff0a484) //  1
NHSTUB(taskUnlock                             ,0xfff0a52c) //  1
NHSTUB(taskName                               ,0xfff09cc0) //  1
NHSTUB(errnoOfTaskGet                         ,0xffef7db4) //  1
NHSTUB(readdir                                ,0xffef75b4) //  1
NHSTUB(strtoul                                ,0xffef5000) //  1
NHSTUB(strpbrk                                ,0xffef56c8) //  1
NHSTUB(utime                                  ,0xffef7744) //  1
NHSTUB(mktime                                 ,0xffef5fa4) //  1
NHSTUB(opendir                                ,0xffef761c) //  1
NHSTUB(memchr                                 ,0xffef5188) //  1
NHSTUB(memPartInfoGet                         ,0xffefd5c0) //  1
NHSTUB(iosDrvInstall                          ,0xffefb644) //  1
NHSTUB(iosDevAdd                              ,0xffefb380) //  1
NHSTUB(iosDevDelete                           ,0xffefb358) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffeb2ec8) //  1
NHSTUB(taskCreateHookAdd                      ,0xffeffe00) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffeffd3c) //  1
NHSTUB(Unmount_FileSystem                     ,0xffc61974) //  1
NHSTUB(taskSuspend                            ,0xfff09ed0) //  1
NHSTUB(taskResume                             ,0xfff0a0a4) //  1
NHSTUB(time                                   ,0xffef6b28) //  1
NHSTUB(vsprintf                               ,0xffef8f08) //115
NHSTUB(EngDrvRead                             ,0xffc73f98) //102
