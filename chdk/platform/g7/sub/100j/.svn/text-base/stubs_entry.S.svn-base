// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00J   // Found @ 0xff81a738, "GM1.00J" @ 0xff81a745
//   Firmware build timestamp: Apr 18 2007 17:31:07
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.68MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000a7910

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(EnterToCompensationEVF                 ,0xff99b204) //  2 87%
//NHSTUB(ExitFromCompensationEVF              ,0xff99f0c0) //  2 66%    *** != 0xff99b244
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff99f11c) // 2 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff99f1d8) // 2 20/10
NHSTUB(GetFocusLensSubjectDistance            ,0xffb3d8c4) //  1 83%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffb3de30) //  2 92%
NHSTUB(GetPropertyCase                        ,0xff8258d4) //  2 92%
NHSTUB(GetSystemTime                          ,0xff8150d8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffb50660) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffb506a8) //  1 94%
//NHSTUB(Remove                               ,0xff8e7ac8) //  3 52%
//NHSTUB(Restart                              ,0xff823ac0) //  1 92%    *** != 0xff823abc
NHSTUB(UnsetZoomForMovie                      ,0xff9f6c4c) //  1 89%
//NHSTUB(WriteSDCard                          ,0xff88bcd0) //  2 93%    *** != 0xff88be6c
NHSTUB(add_ptp_handler                        ,0xffaef0d4) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffb9eccc
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0xff828e70
NHSTUB(kbd_pwr_off                            ,0xff82ab3c) //  1 83%
// ALT: NHSTUB(kbd_pwr_off, 0xff82ab58) // 1 5/1
NHSTUB(kbd_pwr_on                             ,0xff96715c) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff967188) // 1 5/4
NHSTUB(malloc                                 ,0xffb9ecc0) //  1 53%
NHSTUB(taskIdListGet                          ,0xffbab8e8) //  1 82%
NHSTUB(localtime                              ,0xffb978fc) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff87be74) //  1 90%
NHSTUB(MakeAFScan                             ,0xff9a0560) //  2 79%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff9b6358 -> ff9b6358
// Mode  8222 in firmware but not in current modemap
// Mode  8223 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9ae87c) // Found @0xff9ae87c,          stubs_min = 0xff9ae87c (0xFF9AE87C)
//DEF(FlashParamsTable                        ,0xff9b8db4) // Found @0xff9b8db4,          stubs_min = 0xff9b8db4 (0xFF9B8DB4)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6e; }                          // Found @0xff9bbe74

// Misc stuff
// LED table init @ 0xff82f464
// LED #1: 0xc0220068, offset 0xc4
// LED #2: 0xc022006c, offset 0x204
// LED #3: 0xc0220094, offset 0x244
// LED #4: 0xc02200b0, offset 0x384

// canon_data_src: 0xffbb1b50, canon_data_len: 0xd610

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814ea0) //  1
NHSTUB(Close                                  ,0xff87cb4c) //120
NHSTUB(CreateTask                             ,0xff822594) //120
NHSTUB(DebugAssert                            ,0xff813d70) //1100
NHSTUB(DeleteFile_Fut                         ,0xff875a0c) //  1
NHSTUB(DoAELock                               ,0xff99b2a4) //120
//NHSTUB(DoAFLock                             ,0xff99afd0) //120            == 0xff99afd0
NHSTUB(ExecuteEventProcedure                  ,0xff816d3c) //  1
NHSTUB(ExitTask                               ,0xff822954) //120
NHSTUB(Fclose_Fut                             ,0xff875b80) //120
NHSTUB(Feof_Fut                               ,0xff875d7c) //  3
NHSTUB(Fflush_Fut                             ,0xff875db8) //  3
NHSTUB(Fgets_Fut                              ,0xff875ce4) //  3
NHSTUB(Fopen_Fut                              ,0xff875b40) //120
NHSTUB(Fread_Fut                              ,0xff875c3c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff814ed4) //  1
NHSTUB(Fseek_Fut                              ,0xff875d30) //120
NHSTUB(Fwrite_Fut                             ,0xff875c90) //120
NHSTUB(GetBatteryTemperature                  ,0xff82eb20) //102
NHSTUB(GetCCDTemperature                      ,0xff82eb0c) //102
NHSTUB(GetCurrentAvValue                      ,0xffb501d0) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff87c338) //119            == 0xff87c338
//NHSTUB(GetDrive_FreeClusters                ,0xff87c3b0) //1103            == 0xff87c3b0
NHSTUB(GetDrive_TotalClusters                 ,0xff87c374) //119
NHSTUB(GetOpticalTemperature                  ,0xff82eaf8) //120
NHSTUB(GetParameterData                       ,0xff9bbe08) //  2
NHSTUB(GetZoomLensCurrentPoint                ,0xffb29cc8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffb29cdc) //102
//NHSTUB(GiveSemaphore                        ,0xff82218c) //120            == 0xff82218c
NHSTUB(IsStrobeChargeCompleted                ,0xff939f98) //  2
NHSTUB(LEDDrive                               ,0xff82f078) //120
NHSTUB(LocalTime                              ,0xff8143f8) //115
NHSTUB(LockMainPower                          ,0xff9b60f8) //120
NHSTUB(MakeDirectory_Fut                      ,0xff875ac0) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffb52988) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffb29ba8) //120
NHSTUB(Open                                   ,0xff87cb24) //120
NHSTUB(PT_PlaySound                           ,0xff9aca78) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff9b1988) //120
NHSTUB(PostLogicalEventToUI                   ,0xff9b1a04) //120
NHSTUB(Read                                   ,0xff87cbe0) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff9ce31c) //120
NHSTUB(RenameFile_Fut                         ,0xff875964) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffb5565c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9b5ffc) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9e9e80) //120
NHSTUB(SetFileAttributes                      ,0xff87cd74) //  1
NHSTUB(SetLogicalEventActive                  ,0xff9b3924) //1104
NHSTUB(SetParameterData                       ,0xff9bbd28) //  2
NHSTUB(SetPropertyCase                        ,0xff825784) //  2
//NHSTUB(SetScriptMode                        ,0xff9b398c) //120            == 0xff9b398c
NHSTUB(SleepTask                              ,0xff8224a8) //120
NHSTUB(TakeSemaphore                          ,0xff821fa4) //1101
NHSTUB(TurnOffBackLight                       ,0xffa12ef4) //  2
NHSTUB(TurnOnBackLight                        ,0xffa12ec4) //  2
NHSTUB(TurnOnDisplay                          ,0xff9648dc) //120
NHSTUB(TurnOffDisplay                         ,0xff9648ec) //120
NHSTUB(UnlockAE                               ,0xff99b2c4) //120
//NHSTUB(UnlockAF                             ,0xff99b044) //120            == 0xff99b044
NHSTUB(UnlockMainPower                        ,0xff9b6190) //120
NHSTUB(UpdateMBROnFlash                       ,0xff87c06c) //  1
NHSTUB(VbattGet                               ,0xff82d9bc) //120
NHSTUB(Write                                  ,0xff87cbec) //120
NHSTUB(_log                                   ,0xffb910c4) //121
NHSTUB(_log10                                 ,0xffb8cf80) //121
NHSTUB(_pow                                   ,0xffb8d108) //121
NHSTUB(_sqrt                                  ,0xffb8f2f8) //  1
NHSTUB(apex2us                                ,0xff8c8a28) //  1
NHSTUB(close                                  ,0xffb9bc80) //109
NHSTUB(exmem_alloc                            ,0xff812834) //  2
NHSTUB(kbd_p1_f                               ,0xff828014) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff828020) //109
NHSTUB(kbd_p2_f                               ,0xff8283f0) //  1
NHSTUB(lseek                                  ,0xffb9bdc4) //  1
NHSTUB(memcmp                                 ,0xffb96cdc) //120
NHSTUB(memcpy                                 ,0xffb96d18) //120
NHSTUB(memset                                 ,0xffb96d90) //120
NHSTUB(mkdir                                  ,0xff87cda4) //  1
NHSTUB(open                                   ,0xffb9c2c4) //109
NHSTUB(closedir                               ,0xffb99108) //  1
NHSTUB(qsort                                  ,0xffb9653c) //  1
NHSTUB(rand                                   ,0xffb96560) //  1
NHSTUB(realloc                                ,0xffb870c0) //115
NHSTUB(srand                                  ,0xffb96584) //  1
NHSTUB(stat                                   ,0xffb991d0) //  1
NHSTUB(strcat                                 ,0xffb96db0) //  1
NHSTUB(strchr                                 ,0xffb96ddc) //  1
NHSTUB(strcmp                                 ,0xffb96e00) //120
NHSTUB(strcpy                                 ,0xffb96f94) //120
NHSTUB(strftime                               ,0xffb9861c) //  1
NHSTUB(strlen                                 ,0xffb970f8) //120
NHSTUB(strncmp                                ,0xffb9715c) //  1
NHSTUB(strncpy                                ,0xffb971a0) //  1
NHSTUB(strrchr                                ,0xffb97224) //  1
NHSTUB(strtol                                 ,0xffb96978) //  1
NHSTUB(isdigit                                ,0xffb930ac) //  1
NHSTUB(isspace                                ,0xffb93124) //  1
NHSTUB(isalpha                                ,0xffb9307c) //  1
NHSTUB(isupper                                ,0xffb9313c) //  1
NHSTUB(islower                                ,0xffb930dc) //  1
NHSTUB(ispunct                                ,0xffb9310c) //  1
NHSTUB(isxdigit                               ,0xffb93154) //  1
NHSTUB(toupper                                ,0xffb9317c) //  1
NHSTUB(tolower                                ,0xffb9316c) //  1
NHSTUB(taskLock                               ,0xffbabfa4) //  1
NHSTUB(taskUnlock                             ,0xffbac04c) //  1
NHSTUB(taskName                               ,0xffbab7e0) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb998d4) //  1
NHSTUB(readdir                                ,0xffb990d4) //  1
NHSTUB(strtoul                                ,0xffb96b20) //  1
NHSTUB(strpbrk                                ,0xffb971e8) //  1
NHSTUB(utime                                  ,0xffb99264) //  1
NHSTUB(mktime                                 ,0xffb97ac4) //  1
NHSTUB(opendir                                ,0xffb9913c) //  1
NHSTUB(memchr                                 ,0xffb96ca8) //  1
NHSTUB(memPartInfoGet                         ,0xffb9f0e0) //  1
NHSTUB(iosDrvInstall                          ,0xffb9d164) //  1
NHSTUB(iosDevAdd                              ,0xffb9cea0) //  1
NHSTUB(iosDevDelete                           ,0xffb9ce78) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffb526e8) //  1
NHSTUB(taskCreateHookAdd                      ,0xffba1920) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffba185c) //  1
NHSTUB(Unmount_FileSystem                     ,0xff87bf18) //  1
NHSTUB(taskSuspend                            ,0xffbab9f0) //  1
NHSTUB(taskResume                             ,0xffbabbc4) //  1
NHSTUB(time                                   ,0xffb98648) //  1
NHSTUB(vsprintf                               ,0xffb9aa28) //115
NHSTUB(EngDrvRead                             ,0xff88e5bc) //102
