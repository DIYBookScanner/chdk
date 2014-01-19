// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   Firmware Ver GM1.00B   // Found @ 0xffc0a204, "GM1.00B" @ 0xffc0a211
//   Firmware build timestamp: Jan 12 2006 15:31:55
//   Possible corrupt firmware dump - file size too small for start address 0xffc00000
//     file size = 3.03MB, should be 4.00MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009c090

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: EnterToCompensationEVF is not found.             //--- ---    *** != 0xffd4424c
//NHSTUB(ExitFromCompensationEVF              ,0xffd442e4) //  1 73%    *** != 0xffd442ac
//NHSTUB(GetFocusLensSubjectDistance          ,0xffe92c14) //  1 54%        == 0xffe92c14
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffe931b0) //  2 92%
NHSTUB(GetParameterData                       ,0xffd5ded4) //  1 86%
NHSTUB(GetSystemTime                          ,0xffc04b28) //  1 96%
NHSTUB(PutInNdFilter                          ,0xffe9e938) //  1 92%
// ALT: NHSTUB(PutInNdFilter, 0xffe9e980) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe9ed44) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffea08d4) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffea091c) // 1 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe9e980) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffe9ed44) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffea08d4) // 2 25/2
// ALT: NHSTUB(PutInNdFilter, 0xffea091c) // 2 25/2
NHSTUB(PutOutNdFilter                         ,0xffe9ed8c) //  1 94%
//NHSTUB(Remove                               ,0xffcb8394) //  3 52%
NHSTUB(SetParameterData                       ,0xffd5ddf4) //  1 86%
NHSTUB(UnsetZoomForMovie                      ,0xffd95090) //  1 89%
NHSTUB(WriteSDCard                            ,0xffc6c4f0) //  3 64%
NHSTUB(add_ptp_handler                        ,0xffe4e284) //  1 96%
NHSTUB(exmem_alloc                            ,0xffc02818) //  2 93%
// ERROR: free is not found.                               //--- ---    *** != 0xffee84c8
NHSTUB(malloc                                 ,0xffee84bc) //  1 53%
NHSTUB(taskIdListGet                          ,0xffef50e4) //  1 82%
NHSTUB(localtime                              ,0xffee10f8) //  1 93%
NHSTUB(Mount_FileSystem                       ,0xffc5cdf8) //  1 90%
// ERROR: MakeAFScan is not found.                         //--- ---    *** != 0xffd46cf0

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffd5912c -> ffd5912c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
//DEF(levent_table                            ,0xffd51f94) // Found @0xffd51f94,          stubs_min = 0xffd51f94 (0xFFD51F94)
//DEF(FlashParamsTable                        ,0xffd5b6e4) // Found @0xffd5b6e4,          stubs_min = 0xffd5b6e4 (0xFFD5B6E4)

// Values below go in 'lib.c':
//int get_flash_params_count(void) { return 0x6c; }                          // Found @0xffd5df40

// Misc stuff
// LED table init @ 0xffc1d300
// LED #1: 0xc022008c, offset 0x4
// LED #2: 0xc0220088, offset 0x44
// LED #3: 0xc0220090, offset 0x84
// LED #4: 0xc0220094, offset 0xc4
// LED #5: 0xc0220084, offset 0x204
// LED #6: 0xc0220080, offset 0x244

// canon_data_src: 0xffefb340, canon_data_len: 0xb960

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc048f0) //  1
NHSTUB(Close                                  ,0xffc5dac8) //120
NHSTUB(CreateTask                             ,0xffc1125c) //120
NHSTUB(DebugAssert                            ,0xffc03ae8) //1100
NHSTUB(DeleteFile_Fut                         ,0xffc56cc4) //  1
NHSTUB(DoAELock                               ,0xffd42540) //120
//NHSTUB(DoAFLock                             ,0xffd423e8) //120            == 0xffd423e8
NHSTUB(ExecuteEventProcedure                  ,0xffc06808) //  1
NHSTUB(ExitTask                               ,0xffc1161c) //120
NHSTUB(Fclose_Fut                             ,0xffc56e04) //120
NHSTUB(Feof_Fut                               ,0xffc57018) //  1
NHSTUB(Fflush_Fut                             ,0xffc57050) //  1
NHSTUB(Fgets_Fut                              ,0xffc56f88) //  1
NHSTUB(Fopen_Fut                              ,0xffc56dc8) //120
NHSTUB(Fread_Fut                              ,0xffc56ee8) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc04924) //  1
NHSTUB(Fseek_Fut                              ,0xffc56fd0) //120
NHSTUB(Fwrite_Fut                             ,0xffc56f38) //120
NHSTUB(GetBatteryTemperature                  ,0xffc1c9bc) //102
NHSTUB(GetCCDTemperature                      ,0xffc1c9a8) //102
NHSTUB(GetCurrentAvValue                      ,0xffe9e924) //120
//NHSTUB(GetDrive_ClusterSize                 ,0xffc5d2b4) //119            == 0xffc5d2b4
//NHSTUB(GetDrive_FreeClusters                ,0xffc5d32c) //1103            == 0xffc5d32c
//NHSTUB(GetDrive_TotalClusters               ,0xffc5d2f0) //119            == 0xffc5d2f0
NHSTUB(GetOpticalTemperature                  ,0xffc1c994) //120
NHSTUB(GetPropertyCase                        ,0xffc144f0) //  1
NHSTUB(GetZoomLensCurrentPoint                ,0xffe7f680) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe7f694) //102
NHSTUB(GiveSemaphore                          ,0xffc10e54) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcfed8c) //  1
NHSTUB(LEDDrive                               ,0xffc1cf14) //120
NHSTUB(LocalTime                              ,0xffc041b8) //115
NHSTUB(LockMainPower                          ,0xffd58ecc) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc56d50) //  1
NHSTUB(MoveFocusLensToDistance                ,0xffea0f74) //102
NHSTUB(MoveZoomLensWithPoint                  ,0xffe7f560) //120
NHSTUB(Open                                   ,0xffc5daa0) //120
NHSTUB(PT_PlaySound                           ,0xffd5030c) //  1
NHSTUB(PostLogicalEventForNotPowerType        ,0xffd54dfc) //120
NHSTUB(PostLogicalEventToUI                   ,0xffd54e78) //120
NHSTUB(Read                                   ,0xffc5db5c) //120
NHSTUB(RefreshPhysicalScreen                  ,0xffd703c0) //120
NHSTUB(RenameFile_Fut                         ,0xffc56c44) //  1
NHSTUB(Restart                                ,0xffc12774) //  1
NHSTUB(SetAE_ShutterSpeed                     ,0xffea481c) //102
NHSTUB(SetAutoShutdownTime                    ,0xffd58dd0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffd89ee0) //120
NHSTUB(SetFileAttributes                      ,0xffc5dc80) //  1
NHSTUB(SetLogicalEventActive                  ,0xffd56bc4) //1104
NHSTUB(SetPropertyCase                        ,0xffc143d4) //  1
//NHSTUB(SetScriptMode                        ,0xffd56c2c) //120            == 0xffd56c2c
NHSTUB(SleepTask                              ,0xffc11170) //120
NHSTUB(TakeSemaphore                          ,0xffc10c6c) //1101
NHSTUB(TurnOffBackLight                       ,0xffda7f60) //  2
NHSTUB(TurnOnBackLight                        ,0xffda7f30) //  2
NHSTUB(TurnOnDisplay                          ,0xffd22134) //120
NHSTUB(TurnOffDisplay                         ,0xffd22144) //120
NHSTUB(UnlockAE                               ,0xffd42560) //120
//NHSTUB(UnlockAF                             ,0xffd4242c) //120            == 0xffd4242c
NHSTUB(UnlockMainPower                        ,0xffd58f64) //120
NHSTUB(UpdateMBROnFlash                       ,0xffc5cfec) //  1
//NHSTUB(VbattGet                             ,0xffc1b990) //120            == 0xffc1b990
NHSTUB(Write                                  ,0xffc5db68) //120
NHSTUB(_log                                   ,0xffedaee8) //121
NHSTUB(_log10                                 ,0xffed73c0) //121
NHSTUB(_pow                                   ,0xffed7548) //121
NHSTUB(_sqrt                                  ,0xffed92e4) //  1
NHSTUB(apex2us                                ,0xffc9f300) //  1
NHSTUB(close                                  ,0xffee547c) //109
NHSTUB(kbd_p1_f                               ,0xffc168e8) //  1
NHSTUB(kbd_p1_f_cont                          ,0xffc168f4) //109
NHSTUB(kbd_p2_f                               ,0xffc16ccc) //  1
NHSTUB(kbd_read_keys_r2                       ,0xffc1771c) //  1
NHSTUB(kbd_pwr_off                            ,0xffc17ca8) //  1
// ALT: NHSTUB(kbd_pwr_off, 0xffc17cd8) // 1 6/0
// ALT: NHSTUB(kbd_pwr_off, 0xffc17cf4) // 1 6/0
NHSTUB(kbd_pwr_on                             ,0xffc17c80) //  1
NHSTUB(lseek                                  ,0xffee55c0) //  1
NHSTUB(memcmp                                 ,0xffee04d8) //120
NHSTUB(memcpy                                 ,0xffee0514) //120
NHSTUB(memset                                 ,0xffee058c) //120
NHSTUB(mkdir                                  ,0xffc5dcb0) //  1
NHSTUB(open                                   ,0xffee5ac0) //109
NHSTUB(closedir                               ,0xffee2904) //  1
NHSTUB(qsort                                  ,0xffedfd38) //  1
NHSTUB(rand                                   ,0xffedfd5c) //  1
NHSTUB(realloc                                ,0xffed1c68) //115
NHSTUB(srand                                  ,0xffedfd80) //  1
NHSTUB(stat                                   ,0xffee29cc) //  1
NHSTUB(strcat                                 ,0xffee05ac) //  1
NHSTUB(strchr                                 ,0xffee05d8) //  1
NHSTUB(strcmp                                 ,0xffee05fc) //120
NHSTUB(strcpy                                 ,0xffee0790) //120
NHSTUB(strftime                               ,0xffee1e18) //  1
NHSTUB(strlen                                 ,0xffee08f4) //120
NHSTUB(strncmp                                ,0xffee0958) //  1
NHSTUB(strncpy                                ,0xffee099c) //  1
NHSTUB(strrchr                                ,0xffee0a20) //  1
NHSTUB(strtol                                 ,0xffee0174) //  1
NHSTUB(isdigit                                ,0xffedc8a8) //  1
NHSTUB(isspace                                ,0xffedc920) //  1
NHSTUB(isalpha                                ,0xffedc878) //  1
NHSTUB(isupper                                ,0xffedc938) //  1
NHSTUB(islower                                ,0xffedc8d8) //  1
NHSTUB(ispunct                                ,0xffedc908) //  1
NHSTUB(isxdigit                               ,0xffedc950) //  1
NHSTUB(toupper                                ,0xffedc978) //  1
NHSTUB(tolower                                ,0xffedc968) //  1
NHSTUB(taskLock                               ,0xffef57a0) //  1
NHSTUB(taskUnlock                             ,0xffef5848) //  1
NHSTUB(taskName                               ,0xffef4fdc) //  1
NHSTUB(errnoOfTaskGet                         ,0xffee30d0) //  1
NHSTUB(readdir                                ,0xffee28d0) //  1
NHSTUB(strtoul                                ,0xffee031c) //  1
NHSTUB(strpbrk                                ,0xffee09e4) //  1
NHSTUB(utime                                  ,0xffee2a60) //  1
NHSTUB(mktime                                 ,0xffee12c0) //  1
NHSTUB(opendir                                ,0xffee2938) //  1
NHSTUB(memchr                                 ,0xffee04a4) //  1
NHSTUB(memPartInfoGet                         ,0xffee88dc) //  1
NHSTUB(iosDrvInstall                          ,0xffee6960) //  1
NHSTUB(iosDevAdd                              ,0xffee669c) //  1
NHSTUB(iosDevDelete                           ,0xffee6674) //  1
NHSTUB(GetCurrentTargetDistance               ,0xffea0cd4) //  1
NHSTUB(taskCreateHookAdd                      ,0xffeeb11c) //  1
NHSTUB(taskDeleteHookAdd                      ,0xffeeb058) //  1
NHSTUB(Unmount_FileSystem                     ,0xffc5ce9c) //  1
NHSTUB(taskSuspend                            ,0xffef51ec) //  1
NHSTUB(taskResume                             ,0xffef53c0) //  1
NHSTUB(time                                   ,0xffee1e44) //  1
NHSTUB(vsprintf                               ,0xffee4224) //115
NHSTUB(EngDrvRead                             ,0xffc6ea30) //102
