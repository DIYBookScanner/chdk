// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00E   // Found @ 0xff81a738, "GM1.00E" @ 0xff81a745
//   Firmware build timestamp: Aug  9 2006 10:53:01
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 3.94MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000a7910

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(EnterToCompensationEVF               ,0xff99b188) //  2 87%    *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff99f044) //  2 66%    *** != 0x00000000
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff99f0a0) // 2 20/10
// ALT: NHSTUB(ExitFromCompensationEVF, 0xff99f15c) // 2 20/10
NHSTUB(GetFocusLensSubjectDistance            ,0xffb3d81c) //  1 83%
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffb3dd88) //  2 92%
NHSTUB(GetPropertyCase                        ,0xff8258d4) //  2 92%
NHSTUB(GetSystemTime                          ,0xff8150d8) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffb50450) //  1 92%
NHSTUB(PutOutNdFilter                         ,0xffb50498) //  1 94%
//NHSTUB(Remove                               ,0xff8e7ac8) //  3 52%
//NHSTUB(Restart                              ,0xff823ac0) //  1 92%    *** != 0xff823abc
NHSTUB(UnsetZoomForMovie                      ,0xff9f6ba4) //  1 89%
//NHSTUB(WriteSDCard                          ,0xff88bcd0) //  2 93%    *** != 0xff88be6c
NHSTUB(add_ptp_handler                        ,0xffaef02c) //  1 96%
// ERROR: free is not found.                               //--- ---    *** != 0xffb9ea6c
// ERROR: kbd_read_keys_r2 is not found.                   //--- ---    *** != 0xff828e70
NHSTUB(kbd_pwr_off                            ,0xff82ab3c) //  1 83%
// ALT: NHSTUB(kbd_pwr_off, 0xff82ab58) // 1 5/1
NHSTUB(kbd_pwr_on                             ,0xff9670e0) //  1 55%
// ALT: NHSTUB(kbd_pwr_on, 0xff96710c) // 1 5/4
NHSTUB(malloc                                 ,0xffb9ea60) //  1 53%
NHSTUB(taskIdListGet                          ,0xffbab688) //  1 82%
NHSTUB(localtime                              ,0xffb9769c) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xff87be74) //  1 90%
NHSTUB(MakeAFScan                             ,0xff9a04e0) //  2 79%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff9b62b0 -> ff9b62b0
// Mode  8222 in firmware but not in current modemap
// Mode  8223 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xff9ae7d4) // Found @0xff9ae7d4,          stubs_min = 0xff9ae7d4 (0xFF9AE7D4)
//DEF(FlashParamsTable                        ,0xff9b8d0c) // Found @0xff9b8d0c,          stubs_min = 0xff9b8d0c (0xFF9B8D0C)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6e; }                          // Found @0xff9bbdcc

// Misc stuff
// LED table init @ 0xff82f464
// LED #1: 0xc0220068, offset 0xc4
// LED #2: 0xc022006c, offset 0x204
// LED #3: 0xc0220094, offset 0x244
// LED #4: 0xc02200b0, offset 0x384

// canon_data_src: 0xffbb18f0, canon_data_len: 0xd610

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff814ea0) //  1
NHSTUB(Close                                  ,0xff87cb4c) //120
NHSTUB(CreateTask                             ,0xff822594) //120
NHSTUB(DebugAssert                            ,0xff813d70) //1100
NHSTUB(DeleteFile_Fut                         ,0xff875a0c) //  1
NHSTUB(DoAELock                               ,0xff99b228) //120
//NHSTUB(DoAFLock                             ,0xff99af54) //120            == 0xff99af54
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
NHSTUB(GetCurrentAvValue                      ,0xffb4ffc0) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xff87c338) //119            == 0xff87c338
//NHSTUB(GetDrive_FreeClusters                ,0xff87c3b0) //1103            == 0xff87c3b0
NHSTUB(GetDrive_TotalClusters                 ,0xff87c374) //119
NHSTUB(GetOpticalTemperature                  ,0xff82eaf8) //120
NHSTUB(GetParameterData                       ,0xff9bbd60) //  2
NHSTUB(GetZoomLensCurrentPoint                ,0xffb29c20) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffb29c34) //102
//NHSTUB(GiveSemaphore                        ,0xff82218c) //120            == 0xff82218c
NHSTUB(IsStrobeChargeCompleted                ,0xff939f1c) //  2
NHSTUB(LEDDrive                               ,0xff82f078) //120
NHSTUB(LocalTime                              ,0xff8143f8) //115
NHSTUB(LockMainPower                          ,0xff9b6050) //120
NHSTUB(MakeDirectory_Fut                      ,0xff875ac0) //  3
NHSTUB(MoveFocusLensToDistance                ,0xffb52778) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffb29b00) //120
NHSTUB(Open                                   ,0xff87cb24) //120
NHSTUB(PT_PlaySound                           ,0xff9ac9d0) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xff9b18e0) //120
NHSTUB(PostLogicalEventToUI                   ,0xff9b195c) //120
NHSTUB(Read                                   ,0xff87cbe0) //120
NHSTUB(RefreshPhysicalScreen                  ,0xff9ce274) //120
NHSTUB(RenameFile_Fut                         ,0xff875964) //  3
NHSTUB(SetAE_ShutterSpeed                     ,0xffb5544c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff9b5f54) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff9e9dd8) //120
NHSTUB(SetFileAttributes                      ,0xff87cd74) //  1
NHSTUB(SetLogicalEventActive                  ,0xff9b387c) //1104
NHSTUB(SetParameterData                       ,0xff9bbc80) //  2
NHSTUB(SetPropertyCase                        ,0xff825784) //  2
//NHSTUB(SetScriptMode                        ,0xff9b38e4) //120            == 0xff9b38e4
NHSTUB(SleepTask                              ,0xff8224a8) //120
NHSTUB(TakeSemaphore                          ,0xff821fa4) //1101
NHSTUB(TurnOffBackLight                       ,0xffa12e4c) //  2
NHSTUB(TurnOnBackLight                        ,0xffa12e1c) //  2
NHSTUB(TurnOnDisplay                          ,0xff964860) //120
NHSTUB(TurnOffDisplay                         ,0xff964870) //120
NHSTUB(UnlockAE                               ,0xff99b248) //120
//NHSTUB(UnlockAF                             ,0xff99afc8) //120            == 0xff99afc8
NHSTUB(UnlockMainPower                        ,0xff9b60e8) //120
NHSTUB(UpdateMBROnFlash                       ,0xff87c06c) //  1
NHSTUB(VbattGet                               ,0xff82d9bc) //120
NHSTUB(Write                                  ,0xff87cbec) //120
NHSTUB(_log                                   ,0xffb90e64) //121
NHSTUB(_log10                                 ,0xffb8cd20) //121
NHSTUB(_pow                                   ,0xffb8cea8) //121
NHSTUB(_sqrt                                  ,0xffb8f098) //  1
NHSTUB(apex2us                                ,0xff8c8a28) //  1
NHSTUB(close                                  ,0xffb9ba20) //109
NHSTUB(exmem_alloc                            ,0xff812834) //  2
NHSTUB(kbd_p1_f                               ,0xff828014) //  1
NHSTUB(kbd_p1_f_cont                          ,0xff828020) //109
NHSTUB(kbd_p2_f                               ,0xff8283f0) //  1
NHSTUB(lseek                                  ,0xffb9bb64) //  1
NHSTUB(memcmp                                 ,0xffb96a7c) //120
NHSTUB(memcpy                                 ,0xffb96ab8) //120
NHSTUB(memset                                 ,0xffb96b30) //120
NHSTUB(mkdir                                  ,0xff87cda4) //  1
NHSTUB(open                                   ,0xffb9c064) //109
NHSTUB(closedir                               ,0xffb98ea8) //  1
NHSTUB(qsort                                  ,0xffb962dc) //  1
NHSTUB(rand                                   ,0xffb96300) //  1
NHSTUB(realloc                                ,0xffb86e60) //115
NHSTUB(srand                                  ,0xffb96324) //  1
NHSTUB(stat                                   ,0xffb98f70) //  1
NHSTUB(strcat                                 ,0xffb96b50) //  1
NHSTUB(strchr                                 ,0xffb96b7c) //  1
NHSTUB(strcmp                                 ,0xffb96ba0) //120
NHSTUB(strcpy                                 ,0xffb96d34) //120
NHSTUB(strftime                               ,0xffb983bc) //  1
NHSTUB(strlen                                 ,0xffb96e98) //120
NHSTUB(strncmp                                ,0xffb96efc) //  1
NHSTUB(strncpy                                ,0xffb96f40) //  1
NHSTUB(strrchr                                ,0xffb96fc4) //  1
NHSTUB(strtol                                 ,0xffb96718) //  1
NHSTUB(isdigit                                ,0xffb92e4c) //  1
NHSTUB(isspace                                ,0xffb92ec4) //  1
NHSTUB(isalpha                                ,0xffb92e1c) //  1
NHSTUB(isupper                                ,0xffb92edc) //  1
NHSTUB(islower                                ,0xffb92e7c) //  1
NHSTUB(ispunct                                ,0xffb92eac) //  1
NHSTUB(isxdigit                               ,0xffb92ef4) //  1
NHSTUB(toupper                                ,0xffb92f1c) //  1
NHSTUB(tolower                                ,0xffb92f0c) //  1
NHSTUB(taskLock                               ,0xffbabd44) //  1
NHSTUB(taskUnlock                             ,0xffbabdec) //  1
NHSTUB(taskName                               ,0xffbab580) //  1
NHSTUB(errnoOfTaskGet                         ,0xffb99674) //  1
NHSTUB(readdir                                ,0xffb98e74) //  1
NHSTUB(strtoul                                ,0xffb968c0) //  1
NHSTUB(strpbrk                                ,0xffb96f88) //  1
NHSTUB(utime                                  ,0xffb99004) //  1
NHSTUB(mktime                                 ,0xffb97864) //  1
NHSTUB(opendir                                ,0xffb98edc) //  1
NHSTUB(memchr                                 ,0xffb96a48) //  1
NHSTUB(memPartInfoGet                         ,0xffb9ee80) //  1
NHSTUB(iosDrvInstall                          ,0xffb9cf04) //  1
NHSTUB(iosDevAdd                              ,0xffb9cc40) //  1
NHSTUB(iosDevDelete                           ,0xffb9cc18) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffb524d8) //  1
NHSTUB(taskCreateHookAdd                      ,0xffba16c0) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffba15fc) //  1
NHSTUB(Unmount_FileSystem                     ,0xff87bf18) //  1
NHSTUB(taskSuspend                            ,0xffbab790) //  1
NHSTUB(taskResume                             ,0xffbab964) //  1
NHSTUB(time                                   ,0xffb983e8) //  1
NHSTUB(vsprintf                               ,0xffb9a7c8) //115
NHSTUB(EngDrvRead                             ,0xff88e5bc) //102
