// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00C   // Found @ 0xffc5819c, "GM1.00C" @ 0xffc581a9
//   Firmware build timestamp: Nov 13 2008 17:08:37
//   Canon PowerShot A2000 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12689 (0x3191) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000d4f38
//   KEYSYS = d4                 // Found @ 0xffff1a98
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff1aa8
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd15f40
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd15f00

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(ExecuteEventProcedure                ,0xffc553c4) //104        *** != 0xffc5543c
//NHSTUB(GetBatteryTemperature                ,0xffc33504) //102        *** != 0xffc33494
//NHSTUB(Lseek                                ,0xffc13484) //120        *** != 0xffc1354c
//NHSTUB(Read                                 ,0xffc0a138) //120        *** != 0xffc133ec
//NHSTUB(kbd_pwr_off                          ,0xffc31408) //  2 64%    *** != 0xffc31418
NHSTUB(kbd_pwr_on                             ,0xffc313c8) //  2 82%
//NHSTUB(write                                ,0xffc133f0) //120        *** != 0xffc0a198

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdfbf48 -> ffeb9b10
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000f418) // Found @0xffc113ec
DEF(physw_run                               ,0x00001be4) // Found @0xffc11064
DEF(physw_sleep_delay                       ,0x00001be2) // Found @0xffc11064
DEF(levent_table                            ,0xffe9ac78) // Found @0xffe9ac78
DEF(FlashParamsTable                        ,0xffeb9cdc) // Found @0xffeb9cdc
DEF(movie_status                            ,0x00005080) // Found @0xffc47950
DEF(canon_menu_active                       ,0x00005460) // Found @0xffc59b98
DEF(canon_shoot_menu_active                 ,0x00009735) // Found @0xffd3bcf4
DEF(playrec_mode                            ,0x00005208) // Found @0xffc4e8ac
DEF(zoom_status                             ,0x0000c0cc) // Found @0xffdfd75c
DEF(some_flag_for_af_scan                   ,0x000085a0) // Found @0xffd0a758
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 15 entries in the table - set NUM_FL to 15
DEF(focus_len_table                         ,0xfffe297c) // Found @0xfffe297c
DEF(zoom_busy                               ,0x00007ff8) // Found @0xffd0312c
DEF(focus_busy                              ,0x00007ee4) // Found @0xffcfe824
//DEF(recreview_hold                          ,0x000059c0) // Found @0xffc65674, ** != ** stubs_min = 0x000094c0 (0x9408+0xB8)
// Camera has 2 RAW buffers @ 0x107d58e0 & 0x11b96b80
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffe7d734) // Found @0xffe7d734
DEF(active_raw_buffer                       ,0x000051b8) // Found @0xffc4c220

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc2cea0
//void *vid_get_viewport_fb()      { return (void*)0x10659de0; }             // Found @0xffe44918
DEF(viewport_fb_d                           ,0x00004f20) // Found 0x4ecc (@0xffc413c0) + 0x54 (@0xffc413ec)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x4ecc+0x54)); } // Found @0xffc413c0 & 0xffc413ec
DEF(jpeg_count_str                          ,0x00045100) // Found @0xffd71398
//char *camera_jpeg_count_str()    { return (char*)0x00045100; }             // Found @0xffd71398
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe46cbc
//int get_flash_params_count(void) { return 0x77; }                          // Found @0xffd2d52c

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe75da0, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe75dac, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00004000 }, // Found @0xffe75c5c, levent 0x600 (uses inverted logic in physw_status)
//    { 1, KEY_PLAYBACK        ,0x02000000 }, // Found @0xffe75c80, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_SHOOT_FULL      ,0xc0000000 }, // Found @0xffe75cc8, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x80000000 }, // Found @0xffe75cc8, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x40000000 }, // Found @0xffe75cbc, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe75cec, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe75cf8, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe75d04, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe75d10, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe75d1c, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe75d28, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe75d34, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffe75d40, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffe75d4c, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffe3db80
//#define CAM_RAW_ROWS      2772 // Found @0xffe3db88
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc171b8

// Misc stuff
DEF(ctypes, 0xffe75886)

// For capt_seq.c
DEF(_nrflag,0x858c) // Found @ ffd0c3cc (0x8590) & ffd0c3e8 (-0x04)
//static long *nrflag = (long*)(0x8590-0x04);  // Found @ ffd0c3cc & ffd0c3e4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc17174) //112
NHSTUB(Close                                  ,0xffc13344) //120
NHSTUB(CreateTask                             ,0xffc0b8c0) //120
NHSTUB(DebugAssert                            ,0xffc0bd98) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc12cd4) //116
NHSTUB(DeleteFile_Fut                         ,0xffc12bf0) //112
NHSTUB(DoAELock                               ,0xffc15084) //120
NHSTUB(DoAFLock                               ,0xffc14d9c) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc14fec) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc15030) //104
NHSTUB(ExitTask                               ,0xffc0bb50) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc1fa68) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc1fbac) //104
NHSTUB(Fclose_Fut                             ,0xffc12d6c) //120
NHSTUB(Feof_Fut                               ,0xffc12f58) //  1
NHSTUB(Fflush_Fut                             ,0xffc12f94) //  1
NHSTUB(Fgets_Fut                              ,0xffc12ec0) //  1
NHSTUB(Fopen_Fut                              ,0xffc12d2c) //120
NHSTUB(Fread_Fut                              ,0xffc12e18) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc171b4) //112
NHSTUB(Fseek_Fut                              ,0xffc12f0c) //120
NHSTUB(Fwrite_Fut                             ,0xffc12e6c) //120
NHSTUB(GetCCDTemperature                      ,0xffc33494) //102
NHSTUB(GetCurrentAvValue                      ,0xffd0025c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc3fc24) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc3fc8c) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc3fc58) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffcff354) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffcff660) //  3
NHSTUB(GetKbdState                            ,0xffc31394) //109
NHSTUB(GetMemInfo                             ,0xffc03c28) //115
NHSTUB(GetOpticalTemperature                  ,0xffc33574) //120
NHSTUB(GetParameterData                       ,0xffd2d4ec) //101
NHSTUB(GetPropertyCase                        ,0xffc590ac) //102
NHSTUB(GetSystemTime                          ,0xffdf0aa8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffca2058) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffca2064) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd0349c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdea9dc) //102
NHSTUB(GiveSemaphore                          ,0xffc0b81c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc8aef4) //102
NHSTUB(LEDDrive                               ,0xffc30a70) //120
NHSTUB(LocalTime                              ,0xffc533c8) //115
NHSTUB(LockMainPower                          ,0xffc5c9b0) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc12c64) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe4135c) //102
NHSTUB(MoveIrisWithAv                         ,0xffded27c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffded808) //120
NHSTUB(Open                                   ,0xffc1331c) //120
NHSTUB(PB2Rec                                 ,0xffc5e3ec) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc48cec) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc48cc4) //120
NHSTUB(PT_PlaySound                           ,0xffc488d4) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5bff0) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5c03c) //120
NHSTUB(PutInNdFilter                          ,0xffded66c) //102
NHSTUB(PutOutNdFilter                         ,0xffded690) //102
NHSTUB(ReadFastDir                            ,0xffddce7c) //  1
NHSTUB(Rec2PB                                 ,0xffc5e440) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd7af58) //104
NHSTUB(RenameFile_Fut                         ,0xffc12b9c) //  1
NHSTUB(Restart                                ,0xffc189ec) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe43b28) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5ca24) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc6301c) //120
NHSTUB(SetFileAttributes                      ,0xffc13670) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13620) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5c72c) //101
NHSTUB(SetParameterData                       ,0xffd2d45c) //101
NHSTUB(SetPropertyCase                        ,0xffc58fa4) //102
NHSTUB(SetScriptMode                          ,0xffc5c77c) //120
NHSTUB(SleepTask                              ,0xffc16ff8) //120
NHSTUB(TakeSemaphore                          ,0xffc0b74c) //120
NHSTUB(TurnOffBackLight                       ,0xffc67b10) //104
NHSTUB(TurnOnBackLight                        ,0xffc67af8) //104
NHSTUB(TurnOnDisplay                          ,0xffc2cf68) //120
NHSTUB(TurnOffDisplay                         ,0xffc2cf78) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd20598) //120
NHSTUB(UnlockAE                               ,0xffc150a8) //120
NHSTUB(UnlockAF                               ,0xffc14dd4) //120
NHSTUB(UnlockMainPower                        ,0xffc5c904) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd32ad8) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3fa64) //105
NHSTUB(VbattGet                               ,0xffc10314) //120
NHSTUB(Write                                  ,0xffc133f0) //120
NHSTUB(WriteSDCard                            ,0xffcf4aa8) //108
NHSTUB(_log                                   ,0xffe7368c) //111
NHSTUB(_log10                                 ,0xffe725d0) //112
NHSTUB(_pow                                   ,0xffe72740) //121
NHSTUB(_sqrt                                  ,0xffe749f4) //  1
NHSTUB(add_ptp_handler                        ,0xffdac444) //121
NHSTUB(apex2us                                ,0xffd7bf74) //121
NHSTUB(close                                  ,0xffc09f50) //109
NHSTUB(err_init_task                          ,0xffc04e84) //111
NHSTUB(exmem_alloc                            ,0xffc53bc8) //103
NHSTUB(exmem_free                             ,0xffc53c40) //103
NHSTUB(free                                   ,0xffc03a80) //112
NHSTUB(kbd_p1_f                               ,0xffc114f0) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc114fc) //109
NHSTUB(kbd_p2_f                               ,0xffc10d04) //109
NHSTUB(kbd_read_keys                          ,0xffc113ec) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc30e84) //109
NHSTUB(lseek                                  ,0xffc13484) //120
NHSTUB(malloc                                 ,0xffc039ac) //112
NHSTUB(memcmp                                 ,0xffc0d8b4) //120
NHSTUB(memcpy                                 ,0xffc6cac8) //120
NHSTUB(memset                                 ,0xffd7b2ac) //120
NHSTUB(mkdir                                  ,0xffc136e8) //109
NHSTUB(mktime_ext                             ,0xffc6d334) //  1
NHSTUB(open                                   ,0xffc09ea0) //109
NHSTUB(OpenFastDir                            ,0xffddcde8) //  1
NHSTUB(closedir                               ,0xffddcf4c) //  1
NHSTUB(qsort                                  ,0xffe2cb98) //  1
NHSTUB(rand                                   ,0xffc0d9bc) //121
NHSTUB(realloc                                ,0xffc03b60) //115
NHSTUB(reboot_fw_update                       ,0xffde1750) //106
NHSTUB(set_control_event                      ,0xffc5c478) //111
NHSTUB(srand                                  ,0xffc0d9b0) //122
NHSTUB(stat                                   ,0xffc13550) //  1
NHSTUB(strcat                                 ,0xffc6c8dc) //  1
NHSTUB(strchr                                 ,0xffc6c964) //  1
NHSTUB(strcmp                                 ,0xffc0d84c) //120
NHSTUB(strcpy                                 ,0xffc0d834) //120
NHSTUB(strftime                               ,0xffc6cd3c) //  1
NHSTUB(strlen                                 ,0xffc0d890) //120
NHSTUB(strncmp                                ,0xffc6c918) //  1
NHSTUB(strncpy                                ,0xffc1cb54) //  1
NHSTUB(strrchr                                ,0xffd7b284) //  1
NHSTUB(strtol                                 ,0xffc1cd8c) //101
NHSTUB(strtolx                                ,0xffc1cb90) //109
   DEF(task_CaptSeq                           ,0xffc4ae84) //120
   DEF(task_ExpDrv                            ,0xffc83eb0) //120
   DEF(task_FileWrite                         ,0xffdd979c) //120
   DEF(task_InitFileModules                   ,0xffc60268) //120
   DEF(task_MovieRecord                       ,0xffc47bb4) //120
   DEF(task_PhySw                             ,0xffc11060) //120
NHSTUB(time                                   ,0xffc5327c) //109
NHSTUB(vsprintf                               ,0xffc0d7f8) //115
NHSTUB(EngDrvRead                             ,0xffc12330) //102
