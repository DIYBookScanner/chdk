// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.01A   // Found @ 0xff81ac34, "GM1.01A" @ 0xff81ac41
//   Firmware build timestamp: Mar 10 2005 16:01:15
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 2.80MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0007c410

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xff959074
//NHSTUB(ExitFromCompensationEVF              ,0xff95baf4) //  1 66%    *** != 0xff9590c8
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff95bb28) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff95bb5c) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff95bb90) // 1 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff95bbc4) // 1 20/10
//NHSTUB(GetCurrentAvValue                    ,0xffa708f4) //120        *** != 0xffa5168c
//NHSTUB(GetFocusLensSubjectDistance          ,0xffa58340) //  1 51%    *** != 0xffa66f2c
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa674ac) //  2 88%
NHSTUB(GetParameterData                       ,0xff975fe0) //  1 76%
//NHSTUB(GetPropertyCase                      ,0xff825aa4) //  2 71%    *** != 0xff825aa8
NHSTUB(GetSystemTime                          ,0xff814a28) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa70a7c) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa725b0) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa725f8) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa725b0) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa725f8) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa70ac4) //  1 94%
//NHSTUB(Remove                               ,0xff8cf2f8) //  3 52%    *** != 0xff874ba8
//NHSTUB(Restart                              ,0xff823b8c) //  1 84%    *** != 0xff823b90
NHSTUB(SetCurrentCaptureModeType              ,0xff99ab34) //  1 73%
NHSTUB(SetFileAttributes                      ,0xff874cf4) //  1 58%
NHSTUB(SetParameterData                       ,0xff975fdc) //  1 66%
// ERROR: SetPropertyCase is not found.                    //--- ---    *** != 0xff8259a0
NHSTUB(UpdateMBROnFlash                       ,0xff8740f8) //  1 96%
// ERROR: VbattGet is not found.                           //--- ---    *** != 0xffa62d30
// ERROR: WriteSDCard is not found.                        //--- ---    *** != 0x00000000
NHSTUB(add_ptp_handler                        ,0xffa24f64) //  1 96%
NHSTUB(exmem_alloc                            ,0xff812954) //  1 92%
// ERROR: free is not found.                               //--- ---    *** != 0xffabebec
// ERROR: kbd_p1_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_p1_f_cont is not found.                      //--- ---    *** != 0xff828de0
// ERROR: kbd_p2_f is not found.                           //--- ---    *** != 0x00000000
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0x00000000
//NHSTUB(kbd_pwr_off                          ,0xff82a370) //  1 83%    *** != 0xff82a120
// ALT: NHSTUB(kbd_pwr_off, 0xff82a38c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a120) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a13c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a20c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82a228) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xff93bd0c) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff93bd38) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa5e76c) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa5e798) // 1 5/4
NHSTUB(malloc                                 ,0xffabebe0) //  1 53%
NHSTUB(mkdir                                  ,0xff874d24) //  1 61%
// ALT: NHSTUB(mkdir, 0xff874de4) // 1 19/12
NHSTUB(taskIdListGet                          ,0xffac9d44) //  1 82%
NHSTUB(localtime                              ,0xffab6334) //  1 93%
// ERROR: Mount_FileSystem is not found.                   //--- ---    *** != 0xff873f40
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff972440 -> ff972440
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff96c750) // Found @0xff96c750,          stubs_min = 0xff96c750 (0xFF96C750)
//DEF(FlashParamsTable                        ,0xff973e0c) // Found @0xff973e0c,          stubs_min = 0xff973e0c (0xFF973E0C)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x52; }                          // Found @0xff97604c

// Misc stuff
// LED table init @ 0xff82e078
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffad0980, canon_data_len: 0xd3e0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8146a0) //  1
//NHSTUB(Close                                ,0xff874b9c) //120            == 0xff874b9c
NHSTUB(CreateTask                             ,0xff8221f4) //120
NHSTUB(DebugAssert                            ,0xff813be8) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86d8d0) //  1
NHSTUB(DoAELock                               ,0xff959158) //120
//NHSTUB(DoAFLock                             ,0xff958ef8) //120            == 0xff958ef8
NHSTUB(ExecuteEventProcedure                  ,0xff816944) //  1
NHSTUB(ExitTask                               ,0xff8225b4) //120
NHSTUB(Fclose_Fut                             ,0xff86da10) //  1
NHSTUB(Feof_Fut                               ,0xff86dc24) //  1
NHSTUB(Fflush_Fut                             ,0xff86dc5c) //  1
NHSTUB(Fgets_Fut                              ,0xff86db94) //  1
NHSTUB(Fopen_Fut                              ,0xff86d9d4) //  1
NHSTUB(Fread_Fut                              ,0xff86daf4) //  1
NHSTUB(FreeUncacheableMemory                  ,0xff8146d4) //  1
NHSTUB(Fseek_Fut                              ,0xff86dbdc) //  1
NHSTUB(Fwrite_Fut                             ,0xff86db44) //  1
//NHSTUB(GetBatteryTemperature                ,0xff82d754) //102            == 0xff82d754
//NHSTUB(GetCCDTemperature                    ,0xff82d740) //102            == 0xff82d740
//NHSTUB(GetDrive_ClusterSize                 ,0xff8743bc) //119            == 0xff8743bc
//NHSTUB(GetDrive_FreeClusters                ,0xff874434) //1103            == 0xff874434
//NHSTUB(GetDrive_TotalClusters               ,0xff8743f8) //119            == 0xff8743f8
//NHSTUB(GetOpticalTemperature                ,0xff82d72c) //120            == 0xff82d72c
//NHSTUB(GetZoomLensCurrentPoint              ,0xffa59380) //120            == 0xffa59380
//NHSTUB(GetZoomLensCurrentPosition           ,0xffa59394) //102            == 0xffa59394
NHSTUB(GiveSemaphore                          ,0xff821bac) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff911ca8) //  1
NHSTUB(LEDDrive                               ,0xff82dc6c) //120
NHSTUB(LocalTime                              ,0xff814368) //115
NHSTUB(LockMainPower                          ,0xff9721b8) //120
NHSTUB(MakeDirectory_Fut                      ,0xff86d95c) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa72c40) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa591fc) //120
//NHSTUB(Open                                 ,0xff874b90) //120            == 0xff874b90
NHSTUB(PT_PlaySound                           ,0xff96ab04) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff96efa4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff96f030) //120
//NHSTUB(Read                                 ,0xff874bfc) //120            == 0xff874bfc
NHSTUB(RefreshPhysicalScreen                  ,0xff985fdc) //120
NHSTUB(RenameFile_Fut                         ,0xff86d850) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa75b1c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9720b0) //120
NHSTUB(SetLogicalEventActive                  ,0xff970658) //1104
//NHSTUB(SetScriptMode                        ,0xff9706bc) //120            == 0xff9706bc
NHSTUB(SleepTask                              ,0xff822054) //120
NHSTUB(TakeSemaphore                          ,0xff8219c4) //1101
NHSTUB(TurnOffBackLight                       ,0xff9aeb2c) //  1
NHSTUB(TurnOnBackLight                        ,0xff9aeb00) //  1
NHSTUB(TurnOnDisplay                          ,0xff93bbb8) //120
NHSTUB(TurnOffDisplay                         ,0xff93bbc8) //120
NHSTUB(UnlockAE                               ,0xff9591ac) //120
//NHSTUB(UnlockAF                             ,0xff958f70) //120            == 0xff958f70
NHSTUB(UnlockMainPower                        ,0xff97226c) //120
//NHSTUB(Write                                ,0xff874c08) //120            == 0xff874c08
NHSTUB(_log                                   ,0xffaa8120) //121
NHSTUB(_log10                                 ,0xffaa87c8) //121
NHSTUB(_pow                                   ,0xffaa8cb8) //121
NHSTUB(_sqrt                                  ,0xffaad004) //  1
NHSTUB(apex2us                                ,0xff8b85c4) //  1
NHSTUB(close                                  ,0xffabbba0) //109
NHSTUB(lseek                                  ,0xffabbce4) //  1
NHSTUB(memcmp                                 ,0xffab5714) //120
NHSTUB(memcpy                                 ,0xffab5750) //120
NHSTUB(memset                                 ,0xffab57c8) //120
NHSTUB(open                                   ,0xffabc1e4) //  1
NHSTUB(closedir                               ,0xffab7b40) //  1
NHSTUB(qsort                                  ,0xffab4f74) //  1
NHSTUB(rand                                   ,0xffab4f98) //  1
NHSTUB(realloc                                ,0xffaa03b0) //115
NHSTUB(srand                                  ,0xffab4fbc) //  1
NHSTUB(stat                                   ,0xffab7c08) //  1
NHSTUB(strcat                                 ,0xffab57e8) //  1
NHSTUB(strchr                                 ,0xffab5814) //  1
NHSTUB(strcmp                                 ,0xffab5838) //120
NHSTUB(strcpy                                 ,0xffab59cc) //120
NHSTUB(strftime                               ,0xffab7054) //  1
NHSTUB(strlen                                 ,0xffab5b30) //120
NHSTUB(strncmp                                ,0xffab5b94) //  1
NHSTUB(strncpy                                ,0xffab5bd8) //  1
NHSTUB(strrchr                                ,0xffab5c5c) //  1
NHSTUB(strtol                                 ,0xffab53b0) //  1
NHSTUB(isdigit                                ,0xffab1ae4) //  1
NHSTUB(isspace                                ,0xffab1b5c) //  1
NHSTUB(isalpha                                ,0xffab1ab4) //  1
NHSTUB(isupper                                ,0xffab1b74) //  1
NHSTUB(islower                                ,0xffab1b14) //  1
NHSTUB(ispunct                                ,0xffab1b44) //  1
NHSTUB(isxdigit                               ,0xffab1b8c) //  1
NHSTUB(toupper                                ,0xffab1bb4) //  1
NHSTUB(tolower                                ,0xffab1ba4) //  1
NHSTUB(taskLock                               ,0xffaca400) //  1
NHSTUB(taskUnlock                             ,0xffaca4a8) //  1
NHSTUB(taskName                               ,0xffac9c3c) //  1
NHSTUB(errnoOfTaskGet                         ,0xffab830c) //  1
NHSTUB(readdir                                ,0xffab7b0c) //  1
NHSTUB(strtoul                                ,0xffab5558) //  1
NHSTUB(strpbrk                                ,0xffab5c20) //  1
NHSTUB(utime                                  ,0xffab7c9c) //  1
NHSTUB(mktime                                 ,0xffab64fc) //  1
NHSTUB(opendir                                ,0xffab7b74) //  1
NHSTUB(memchr                                 ,0xffab56e0) //  1
NHSTUB(memPartInfoGet                         ,0xffabf000) //  1
NHSTUB(iosDrvInstall                          ,0xffabd084) //  1
NHSTUB(iosDevAdd                              ,0xffabcdc0) //  1
NHSTUB(iosDevDelete                           ,0xffabcd98) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa729b0) //  1
NHSTUB(taskCreateHookAdd                      ,0xffac2260) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffac219c) //  1
NHSTUB(Unmount_FileSystem                     ,0xff873fa0) //  1
NHSTUB(taskSuspend                            ,0xffac9e4c) //  1
NHSTUB(taskResume                             ,0xffaca020) //  1
NHSTUB(time                                   ,0xffab7080) //  1
NHSTUB(vsprintf                               ,0xffab9460) //115
NHSTUB(EngDrvRead                             ,0xff888d5c) //102
