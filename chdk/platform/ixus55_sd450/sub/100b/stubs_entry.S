// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00B   // Found @ 0xff81a558, "GM1.00B" @ 0xff81a565
//   Firmware build timestamp: Aug  3 2005 13:53:21
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 4.00MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a87d0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xff94c0f8) //  1 64%
//NHSTUB(ExitFromCompensationEVF              ,0xff94c1c4) //  1 73%    *** != 0xff94c158
NHSTUB(GetFocusLensSubjectDistance            ,0xffa7dec0) //  1 96%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffa7e460) //  3 92%
NHSTUB(GetSystemTime                          ,0xff814ebc) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffa88b78) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffa8a704) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a74c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a704) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffa8a74c) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffa88bc0) //  1 94%
//NHSTUB(Remove                               ,0xff8c2170) //  3 52%
NHSTUB(UnsetZoomForMovie                      ,0xff996c68) //  1 89%
NHSTUB(add_ptp_handler                        ,0xffa3d270) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffad6b78
//NHSTUB(kbd_pwr_off                          ,0xff82789c) //  1 83%    *** != 0xff8277f0
// ALT: NHSTUB(kbd_pwr_off, 0xff8278b8) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828880) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82889c) // 1 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff8278b8) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828528) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828544) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828630) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82864c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff82871c) // 3 5/1
// ALT: NHSTUB(kbd_pwr_off, 0xff828738) // 3 5/1
NHSTUB(kbd_pwr_on                             ,0xff8277b0) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff922768) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff922794) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xff9228d0) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74448) // 1 5/4
// ALT: NHSTUB(kbd_pwr_on, 0xffa74474) // 1 5/4
NHSTUB(malloc                                 ,0xffad6b6c) //  1 53%
NHSTUB(taskIdListGet                          ,0xffae47b0) //  1 82%
NHSTUB(localtime                              ,0xfface2c0) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff86d648) //  1 90%
NHSTUB(MakeAFScan                             ,0xff94e6f8) //  1 96%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff95fc68 -> ff95fc68
// Mode 7 in firmware but not in current modemap
// Mode 9 in firmware but not in current modemap
// Mode 10 in firmware but not in current modemap
// Mode 11 in firmware but not in current modemap
// Mode 13 in firmware but not in current modemap
// Mode 14 in firmware but not in current modemap
// Strange mode 0x0001000f in firmware, found in modemap as 15 (MODE_VIDEO_STD)
// Strange mode 0x00010010 in firmware but not in current modemap
// Strange mode 0x00010011 in firmware but not in current modemap
// Strange mode 0x00010012 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff958de4) // Found @0xff958de4,          stubs_min = 0xff958de4 (0xFF958DE4)
//DEF(FlashParamsTable                        ,0xff961ecc) // Found @0xff961ecc,          stubs_min = 0xff961ecc (0xFF961ECC)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x5e; }                          // Found @0xff964588

// Misc stuff
// LED table init @ 0xff82d1a0
// LED #1: 0xc02200d8, offset 0x4
// LED #2: 0xc02200dc, offset 0x44
// LED #3: 0xc02200e0, offset 0x84
// LED #4: 0xc02200e8, offset 0xc4
// LED #5: 0xc02200e4, offset 0x204
// LED #6: 0xc02200ec, offset 0x244

// canon_data_src: 0xffaeb3f0, canon_data_len: 0xea00

// For capt_seq.c
DEF(_nrflag,0x6d6c) // Found @ ff950504 (0x6d6c)
//static long *nrflag = (long*)(0x6d6c);       // Found @ ff950504

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814c84) //  1
NHSTUB(Close                                  ,0xff86e394) //120
NHSTUB(CreateTask                             ,0xff8215dc) //120
NHSTUB(DebugAssert                            ,0xff813b54) //1100
NHSTUB(DeleteFile_Fut                         ,0xff867848) //  1
NHSTUB(DoAELock                               ,0xff94a3ec) //120
NHSTUB(DoAFLock                               ,0xff94a2a4) //120
NHSTUB(ExecuteEventProcedure                  ,0xff816b9c) //  1
NHSTUB(ExitTask                               ,0xff82199c) //120
NHSTUB(Fclose_Fut                             ,0xff867988) //120
NHSTUB(Feof_Fut                               ,0xff867b9c) //  1
NHSTUB(Fflush_Fut                             ,0xff867bd4) //  1
NHSTUB(Fgets_Fut                              ,0xff867b0c) //  1
NHSTUB(Fopen_Fut                              ,0xff86794c) //120
NHSTUB(Fread_Fut                              ,0xff867a6c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814cb8) //  1
NHSTUB(Fseek_Fut                              ,0xff867b54) //120
NHSTUB(Fwrite_Fut                             ,0xff867abc) //120
NHSTUB(GetBatteryTemperature                  ,0xff82c7a8) //102
NHSTUB(GetCCDTemperature                      ,0xff82c794) //102
NHSTUB(GetCurrentAvValue                      ,0xffa889f4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86db70) //119
NHSTUB(GetDrive_FreeClusters                  ,0xff86dbe8) //1103
NHSTUB(GetDrive_TotalClusters                 ,0xff86dbac) //119
NHSTUB(GetOpticalTemperature                  ,0xff82c780) //120
NHSTUB(GetParameterData                       ,0xff96451c) //  1
NHSTUB(GetPropertyCase                        ,0xff824550) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffa6ed60) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa6ed74) //102
NHSTUB(GiveSemaphore                          ,0xff8211d4) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8fde0c) //  1
NHSTUB(LEDDrive                               ,0xff82cd00) //120
NHSTUB(LocalTime                              ,0xff8141dc) //115
NHSTUB(LockMainPower                          ,0xff95f9e0) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8678d4) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffa8ad90) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6ec40) //120
NHSTUB(Open                                   ,0xff86e36c) //120
NHSTUB(PT_PlaySound                           ,0xff9572a0) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff95ba28) //120
NHSTUB(PostLogicalEventToUI                   ,0xff95bab4) //120
NHSTUB(Read                                   ,0xff86e428) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff974ed0) //120
NHSTUB(RenameFile_Fut                         ,0xff8677c8) //  1
NHSTUB(Restart                                ,0xff822b8c) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffa8de44) //102
NHSTUB(SetAutoShutdownTime                    ,0xff95f8d8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff98c0e4) //120
NHSTUB(SetFileAttributes                      ,0xff86e54c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff95da84) //1104
NHSTUB(SetParameterData                       ,0xff96443c) //  1
NHSTUB(SetPropertyCase                        ,0xff824434) //  1
//NHSTUB(SetScriptMode                        ,0xff95dae8) //120            == 0xff95dae8
NHSTUB(SleepTask                              ,0xff8214f0) //120
NHSTUB(TakeSemaphore                          ,0xff820fec) //1101
NHSTUB(TurnOffBackLight                       ,0xff9a24b8) //  1
NHSTUB(TurnOnBackLight                        ,0xff9a248c) //  1
NHSTUB(TurnOnDisplay                          ,0xff922600) //120
NHSTUB(TurnOffDisplay                         ,0xff922610) //120
NHSTUB(UnlockAE                               ,0xff94a40c) //120
NHSTUB(UnlockAF                               ,0xff94a2e4) //120
NHSTUB(UnlockMainPower                        ,0xff95fa94) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86d8a8) //  1
//NHSTUB(VbattGet                             ,0xff82b7d8) //120            == 0xff82b7d8
NHSTUB(Write                                  ,0xff86e434) //120
NHSTUB(WriteSDCard                            ,0xff87cc60) //  1
NHSTUB(_log                                   ,0xffac00ac) //121
NHSTUB(_log10                                 ,0xffac0754) //121
NHSTUB(_pow                                   ,0xffac0c44) //121
NHSTUB(_sqrt                                  ,0xffac4f90) //  1
NHSTUB(apex2us                                ,0xff8ab448) //  1
NHSTUB(close                                  ,0xffad3b2c) //109
NHSTUB(exmem_alloc                            ,0xff8128b4) //  1
NHSTUB(kbd_p1_f                               ,0xff826550) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff82655c) //109
NHSTUB(kbd_p2_f                               ,0xff826934) //  1
NHSTUB(kbd_read_keys_r2                       ,0xff827334) //  1
NHSTUB(lseek                                  ,0xffad3c70) //  1
NHSTUB(memcmp                                 ,0xffacd6a0) //120
NHSTUB(memcpy                                 ,0xffacd6dc) //120
NHSTUB(memset                                 ,0xffacd754) //120
NHSTUB(mkdir                                  ,0xff86e57c) //  1
NHSTUB(open                                   ,0xffad4170) //109
NHSTUB(closedir                               ,0xffacfacc) //  1
NHSTUB(qsort                                  ,0xffaccf00) //  1
NHSTUB(rand                                   ,0xffaccf24) //  1
NHSTUB(realloc                                ,0xffab81e4) //115
NHSTUB(srand                                  ,0xffaccf48) //  1
NHSTUB(stat                                   ,0xffacfb94) //  1
NHSTUB(strcat                                 ,0xffacd774) //  1
NHSTUB(strchr                                 ,0xffacd7a0) //  1
NHSTUB(strcmp                                 ,0xffacd7c4) //120
NHSTUB(strcpy                                 ,0xffacd958) //120
NHSTUB(strftime                               ,0xffacefe0) //  1
NHSTUB(strlen                                 ,0xffacdabc) //120
NHSTUB(strncmp                                ,0xffacdb20) //  1
NHSTUB(strncpy                                ,0xffacdb64) //  1
NHSTUB(strrchr                                ,0xffacdbe8) //  1
NHSTUB(strtol                                 ,0xffacd33c) //  1
NHSTUB(isdigit                                ,0xffac9a70) //  1
NHSTUB(isspace                                ,0xffac9ae8) //  1
NHSTUB(isalpha                                ,0xffac9a40) //  1
NHSTUB(isupper                                ,0xffac9b00) //  1
NHSTUB(islower                                ,0xffac9aa0) //  1
NHSTUB(ispunct                                ,0xffac9ad0) //  1
NHSTUB(isxdigit                               ,0xffac9b18) //  1
NHSTUB(toupper                                ,0xffac9b40) //  1
NHSTUB(tolower                                ,0xffac9b30) //  1
NHSTUB(taskLock                               ,0xffae4e6c) //  1
NHSTUB(taskUnlock                             ,0xffae4f14) //  1
NHSTUB(taskName                               ,0xffae46a8) //  1
NHSTUB(errnoOfTaskGet                         ,0xffad0298) //  1
NHSTUB(readdir                                ,0xffacfa98) //  1
NHSTUB(strtoul                                ,0xffacd4e4) //  1
NHSTUB(strpbrk                                ,0xffacdbac) //  1
NHSTUB(utime                                  ,0xffacfc28) //  1
NHSTUB(mktime                                 ,0xfface488) //  1
NHSTUB(opendir                                ,0xffacfb00) //  1
NHSTUB(memchr                                 ,0xffacd66c) //  1
NHSTUB(memPartInfoGet                         ,0xffad6f8c) //  1
NHSTUB(iosDrvInstall                          ,0xffad5010) //  1
NHSTUB(iosDevAdd                              ,0xffad4d4c) //  1
NHSTUB(iosDevDelete                           ,0xffad4d24) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffa8ab00) //  1
NHSTUB(taskCreateHookAdd                      ,0xffada1ec) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffada128) //  1
NHSTUB(Unmount_FileSystem                     ,0xff86d750) //  1
NHSTUB(taskSuspend                            ,0xffae48b8) //  1
NHSTUB(taskResume                             ,0xffae4a8c) //  1
NHSTUB(time                                   ,0xffacf00c) //  1
NHSTUB(vsprintf                               ,0xffad13ec) //115
NHSTUB(EngDrvRead                             ,0xff87eec0) //102
