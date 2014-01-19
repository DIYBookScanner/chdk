// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00G   // Found @ 0xff81b270, "GM1.00G" @ 0xff81b27d
//   Firmware build timestamp: Sep 26 2005 18:48:25
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 2.90MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a85f0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(EnterToCompensationEVF               ,0xff94a9c0) //  1 64%    *** != 0xff948c84
//NHSTUB(ExitFromCompensationEVF              ,0xff94aac0) //  1 73%    *** != 0xff948c94
NHSTUB(GetFocusLensSubjectDistance            ,0xffa7a8b0) //  1 90%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa7ae50) //  3 52%
NHSTUB(GetSystemTime                          ,0xff815094) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa854cc) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa87058) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa870a0) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa87058) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa870a0) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa85514) //  1 94%
//NHSTUB(Remove                               ,0xff8c26cc) //  3 52%
NHSTUB(UnsetZoomForMovie                      ,0xff995220) //  1 89%
NHSTUB(UpdateMBROnFlash                       ,0xff86fb3c) //  1 96%
NHSTUB(WriteSDCard                            ,0xff87f694) //  1 93%
// ALT: NHSTUB(WriteSDCard, 0xff87f86c) // 1 29/2
NHSTUB(add_ptp_handler                        ,0xffa3990c) //  1 96%
NHSTUB(exmem_alloc                            ,0xff81293c) //  1 92%
// ERROR: free is not found.                               //--- ---    *** != 0xffad366c
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0xff828950
//NHSTUB(kbd_pwr_off                          ,0xff828f30) //  1 83%    *** != 0xff828f4c
// ALT: NHSTUB(kbd_pwr_off, 0xff828f4c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829f24) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829f40) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828f4c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829bcc) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829be8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829cd4) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829cf0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829dc0) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff829ddc) // 3 5/1
//NHSTUB(kbd_pwr_on                           ,0xff921148) //  1 55%    *** != 0xff828f30
// ALT: NHSTUB(kbd_pwr_on, 0xff921174) // 1 5/4
NHSTUB(malloc                                 ,0xffad3660) //  1 53%
NHSTUB(taskIdListGet                          ,0xffae12a4) //  1 82%
NHSTUB(localtime                              ,0xffacadb4) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86f8dc) //  1 90%
NHSTUB(MakeAFScan                             ,0xff94cf90) //  1 89%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff95e37c -> ff95e37c
// Strange mode 0x00010010 in firmware, found in modemap as 16 (MODE_SCN_KIDS_PETS)
// Strange mode 0x00010011 in firmware, found in modemap as 17 (MODE_SCN_FIREWORK)
// Strange mode 0x00010012 in firmware, found in modemap as 18 (MODE_VIDEO_STD)

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9575f8) // Found @0xff9575f8,          stubs_min = 0xff9575f8 (0xFF9575F8)
//DEF(FlashParamsTable                        ,0xff9604bc) // Found @0xff9604bc, ** != ** stubs_min = 0xff958138 (0xFF958138)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xff962c0c

// Misc stuff
// LED table init @ 0xff82e8c0
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220084, offset 0x204
// LED #4: 0xc0220080, offset 0x244

// canon_data_src: 0xffae7ee0, canon_data_len: 0xe7d0

// For capt_seq.c
DEF(_nrflag,0x6b6c) // Found @ ff94ed78 (0x6b6c)
//static long *nrflag = (long*)(0x6b6c);       // Found @ ff94ed78

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814d0c) //  1
NHSTUB(Close                                  ,0xff870628) //120
NHSTUB(CreateTask                             ,0xff8228ac) //120
NHSTUB(DebugAssert                            ,0xff813bdc) //1100
NHSTUB(DeleteFile_Fut                         ,0xff86950c) //  1
NHSTUB(DoAELock                               ,0xff948cbc) //120
NHSTUB(DoAFLock                               ,0xff948b74) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816fac) //  1
NHSTUB(ExitTask                               ,0xff822c6c) //120
NHSTUB(Fclose_Fut                             ,0xff86964c) //120
NHSTUB(Feof_Fut                               ,0xff869860) //  1
NHSTUB(Fflush_Fut                             ,0xff869898) //  1
NHSTUB(Fgets_Fut                              ,0xff8697d0) //  1
NHSTUB(Fopen_Fut                              ,0xff869610) //120
NHSTUB(Fread_Fut                              ,0xff869730) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814d40) //  1
NHSTUB(Fseek_Fut                              ,0xff869818) //120
NHSTUB(Fwrite_Fut                             ,0xff869780) //120
NHSTUB(GetBatteryTemperature                  ,0xff82dec8) //102
NHSTUB(GetCCDTemperature                      ,0xff82deb4) //102
NHSTUB(GetCurrentAvValue                      ,0xffa85348) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86fe04) //119
NHSTUB(GetDrive_FreeClusters                  ,0xff86fe7c) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xff86fe40) //119
NHSTUB(GetOpticalTemperature                  ,0xff82dea0) //120
NHSTUB(GetParameterData                       ,0xff962ba0) //  1
NHSTUB(GetPropertyCase                        ,0xff825bb0) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffa6b7cc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa6b7e0) //102
//NHSTUB(GiveSemaphore                        ,0xff8222b0) //120            == 0xff8222b0
NHSTUB(IsStrobeChargeCompleted                ,0xff8fc68c) //  1
NHSTUB(LEDDrive                               ,0xff82e420) //120
NHSTUB(LocalTime                              ,0xff814264) //115
NHSTUB(LockMainPower                          ,0xff95e0f4) //120
NHSTUB(MakeDirectory_Fut                      ,0xff869598) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa876e4) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6b6ac) //120
NHSTUB(Open                                   ,0xff870600) //120
NHSTUB(PT_PlaySound                           ,0xff955ab4) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff95a1e8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff95a274) //120
NHSTUB(Read                                   ,0xff8706bc) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff97352c) //120
NHSTUB(RenameFile_Fut                         ,0xff86948c) //  1
NHSTUB(Restart                                ,0xff824140) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa8a798) //102
NHSTUB(SetAutoShutdownTime                    ,0xff95dfec) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff98a540) //120
NHSTUB(SetFileAttributes                      ,0xff870814) //  1
NHSTUB(SetLogicalEventActive                  ,0xff95c1a4) //1104
NHSTUB(SetParameterData                       ,0xff962ac0) //  1
NHSTUB(SetPropertyCase                        ,0xff825a94) //  1
//NHSTUB(SetScriptMode                        ,0xff95c208) //120            == 0xff95c208
NHSTUB(SleepTask                              ,0xff82270c) //120
NHSTUB(TakeSemaphore                          ,0xff8220c8) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a013c) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a0110) //  1
NHSTUB(TurnOnDisplay                          ,0xff920ffc) //120
NHSTUB(TurnOffDisplay                         ,0xff92100c) //120
NHSTUB(UnlockAE                               ,0xff948cdc) //120
NHSTUB(UnlockAF                               ,0xff948bb4) //120
NHSTUB(UnlockMainPower                        ,0xff95e1a8) //120
//NHSTUB(VbattGet                             ,0xff82cf1c) //120            == 0xff82cf1c
NHSTUB(Write                                  ,0xff8706c8) //120
NHSTUB(_log                                   ,0xffabcba0) //121
NHSTUB(_log10                                 ,0xffabd248) //121
NHSTUB(_pow                                   ,0xffabd738) //121
NHSTUB(_sqrt                                  ,0xffac1a84) //  1
NHSTUB(apex2us                                ,0xff8aba18) //  1
NHSTUB(close                                  ,0xffad0620) //109
NHSTUB(kbd_p1_f                               ,0xff827bec) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff827bf8) //109
NHSTUB(kbd_p2_f                               ,0xff827fd0) //  1
NHSTUB(lseek                                  ,0xffad0764) //  1
NHSTUB(memcmp                                 ,0xffaca194) //120
NHSTUB(memcpy                                 ,0xffaca1d0) //120
NHSTUB(memset                                 ,0xffaca248) //120
NHSTUB(mkdir                                  ,0xff870844) //  1
NHSTUB(open                                   ,0xffad0c64) //109
NHSTUB(closedir                               ,0xffacc5c0) //  1
NHSTUB(qsort                                  ,0xffac99f4) //  1
NHSTUB(rand                                   ,0xffac9a18) //  1
NHSTUB(realloc                                ,0xffab4cfc) //115
NHSTUB(srand                                  ,0xffac9a3c) //  1
NHSTUB(stat                                   ,0xffacc688) //  1
NHSTUB(strcat                                 ,0xffaca268) //  1
NHSTUB(strchr                                 ,0xffaca294) //  1
NHSTUB(strcmp                                 ,0xffaca2b8) //120
NHSTUB(strcpy                                 ,0xffaca44c) //120
NHSTUB(strftime                               ,0xffacbad4) //  1
NHSTUB(strlen                                 ,0xffaca5b0) //120
NHSTUB(strncmp                                ,0xffaca614) //  1
NHSTUB(strncpy                                ,0xffaca658) //  1
NHSTUB(strrchr                                ,0xffaca6dc) //  1
NHSTUB(strtol                                 ,0xffac9e30) //  1
NHSTUB(isdigit                                ,0xffac6564) //  1
NHSTUB(isspace                                ,0xffac65dc) //  1
NHSTUB(isalpha                                ,0xffac6534) //  1
NHSTUB(isupper                                ,0xffac65f4) //  1
NHSTUB(islower                                ,0xffac6594) //  1
NHSTUB(ispunct                                ,0xffac65c4) //  1
NHSTUB(isxdigit                               ,0xffac660c) //  1
NHSTUB(toupper                                ,0xffac6634) //  1
NHSTUB(tolower                                ,0xffac6624) //  1
NHSTUB(taskLock                               ,0xffae1960) //  1
NHSTUB(taskUnlock                             ,0xffae1a08) //  1
NHSTUB(taskName                               ,0xffae119c) //  1
NHSTUB(errnoOfTaskGet                         ,0xffaccd8c) //  1
NHSTUB(readdir                                ,0xffacc58c) //  1
NHSTUB(strtoul                                ,0xffac9fd8) //  1
NHSTUB(strpbrk                                ,0xffaca6a0) //  1
NHSTUB(utime                                  ,0xffacc71c) //  1
NHSTUB(mktime                                 ,0xffacaf7c) //  1
NHSTUB(opendir                                ,0xffacc5f4) //  1
NHSTUB(memchr                                 ,0xffaca160) //  1
NHSTUB(memPartInfoGet                         ,0xffad3a80) //  1
NHSTUB(iosDrvInstall                          ,0xffad1b04) //  1
NHSTUB(iosDevAdd                              ,0xffad1840) //  1
NHSTUB(iosDevDelete                           ,0xffad1818) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa87454) //  1
NHSTUB(taskCreateHookAdd                      ,0xffad6ce0) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffad6c1c) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86f9e4) //  1
NHSTUB(taskSuspend                            ,0xffae13ac) //  1
NHSTUB(taskResume                             ,0xffae1580) //  1
NHSTUB(time                                   ,0xffacbb00) //  1
NHSTUB(vsprintf                               ,0xffacdee0) //115
NHSTUB(EngDrvRead                             ,0xff881b1c) //102
