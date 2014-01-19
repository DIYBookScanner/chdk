// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.01B   // Found @ 0xffc5cbc8, "GM1.01B" @ 0xffc5cbd5
//   Firmware build timestamp: Jan 24 2008 20:41:51
//   Canon PowerShot A590 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12662 (0x3176) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a5304
//   KEYSYS = d3enc              // Found @ 0xffff1ad8
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff1ab8
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffdf2574
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffdf2534

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(kbd_pwr_off                            ,0xffc356b8) //  2 67%
NHSTUB(kbd_pwr_on                             ,0xffc35678) //  2 86%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdfe960 -> ffeaed68
// Mode 32791 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000f11c) // Found @0xffc11c30
DEF(physw_run                               ,0x00001bf0) // Found @0xffc118cc
DEF(physw_sleep_delay                       ,0x00001bee) // Found @0xffc118cc
DEF(levent_table                            ,0xffe8de14) // Found @0xffe8de14
DEF(FlashParamsTable                        ,0xffeaef24) // Found @0xffeaef24
DEF(movie_status                            ,0x000053c8) // Found @0xffc4b958
DEF(canon_menu_active                       ,0x00008d20) // Found @0xffd29ef8
DEF(canon_shoot_menu_active                 ,0x00009641) // Found @0xffd444a4
DEF(playrec_mode                            ,0x00005538) // Found @0xffc52108
DEF(zoom_status                             ,0x0000bfbc) // Found @0xffe00160
DEF(some_flag_for_af_scan                   ,0x0000bd3c) // Found @0xffdee824
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe29ac) // Found @0xfffe29ac
DEF(zoom_busy                               ,0x00008050) // Found @0xffd0f95c
//DEF(focus_busy                              ,0x00007f4c) // Found @0xffd0a804, ** != ** stubs_min = 0x00009d50 (0x9D50)
//DEF(recreview_hold                          ,0x00005d34) // Found @0xffc6a6e4, ** != ** stubs_min = 0x000093ec (0x93ec)
// Camera appears to have only 1 RAW buffer @ 0x10f63920 (Found @0xffe44c5c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc31338
//void *vid_get_viewport_fb()      { return (void*)0x10659e80; }             // Found @0xffe42a2c
DEF(viewport_fb_d                           ,0x00005258) // Found 0x520c (@0xffc45330) + 0x4c (@0xffc45368)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x520c+0x4c)); } // Found @0xffc45330 & 0xffc45368
DEF(jpeg_count_str                          ,0x00049344) // Found @0xffd727b0
//char *camera_jpeg_count_str()    { return (char*)0x00049344; }             // Found @0xffd727b0
//long hook_raw_size()             { return 0x009e6fc4; }                    // Found @0xffe44cb8
//int get_flash_params_count(void) { return 0x73; }                          // Found @0xffd352f8

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe6ed9c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe6eda8, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00004000 }, // Found @0xffe6ec58, levent 0x600 (uses inverted logic in physw_status)
//    { 1, KEY_SHOOT_FULL      ,0xc0000000 }, // Found @0xffe6ecc4, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x80000000 }, // Found @0xffe6ecc4, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x40000000 }, // Found @0xffe6ecb8, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe6ece8, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe6ecf4, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe6ed00, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe6ed0c, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe6ed18, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe6ed24, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe6ed30, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffe6ed3c, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffe6ed48, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3336 // Found @0xffe3c23c
//#define CAM_RAW_ROWS      2490 // Found @0xffe3c240
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc18320

// Misc stuff
DEF(ctypes, 0xffe69fd2)

// For capt_seq.c
DEF(_nrflag,0x85c0) // Found @ ffd18680 (0x85c0)
//static long *nrflag = (long*)(0x85c0);       // Found @ ffd18680

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc182e4) //112
NHSTUB(Close                                  ,0xffc13b88) //120
NHSTUB(CreateTask                             ,0xffc0b8e0) //120
NHSTUB(DebugAssert                            ,0xffc0bdb8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc13518) //116
NHSTUB(DeleteFile_Fut                         ,0xffc13434) //112
NHSTUB(DoAELock                               ,0xffc16054) //120
NHSTUB(DoAFLock                               ,0xffc15b04) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc15f54) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc59eb4) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc15fa4) //104
NHSTUB(ExitTask                               ,0xffc0bb70) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc21f10) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc22054) //104
NHSTUB(Fclose_Fut                             ,0xffc135b0) //120
NHSTUB(Feof_Fut                               ,0xffc1379c) //  1
NHSTUB(Fflush_Fut                             ,0xffc137d8) //  1
NHSTUB(Fgets_Fut                              ,0xffc13704) //  1
NHSTUB(Fopen_Fut                              ,0xffc13570) //120
NHSTUB(Fread_Fut                              ,0xffc1365c) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc18318) //112
NHSTUB(Fseek_Fut                              ,0xffc13750) //120
NHSTUB(Fwrite_Fut                             ,0xffc136b0) //120
NHSTUB(GetBatteryTemperature                  ,0xffc377b4) //102
NHSTUB(GetCCDTemperature                      ,0xffc37744) //102
NHSTUB(GetCurrentAvValue                      ,0xffd0ce14) //102
NHSTUB(GetDrive_ClusterSize                   ,0xffc41688) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc416f0) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc416bc) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffd0b310) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd0b61c) //  1
NHSTUB(GetKbdState                            ,0xffc35644) //109
NHSTUB(GetMemInfo                             ,0xffc03c40) //115
NHSTUB(GetOpticalTemperature                  ,0xffc37824) //120
NHSTUB(GetParameterData                       ,0xffd352b8) //101
NHSTUB(GetPropertyCase                        ,0xffc5dab4) //102
NHSTUB(GetSystemTime                          ,0xffdf1dc8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc2a77c) //102
NHSTUB(GetVRAMVPixelsSize                     ,0xffc2a788) //102
NHSTUB(GetZoomLensCurrentPoint                ,0xffd0fcc0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffde89dc) //102
NHSTUB(GiveSemaphore                          ,0xffc0b844) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc9e3f0) //102
NHSTUB(LEDDrive                               ,0xffc34ce0) //120
NHSTUB(LocalTime                              ,0xffc57bd4) //115
NHSTUB(LockMainPower                          ,0xffc6211c) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc134a8) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe3f558) //102
NHSTUB(MoveIrisWithAv                         ,0xffded980) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdedfc8) //120
NHSTUB(Open                                   ,0xffc13b60) //120
NHSTUB(PB2Rec                                 ,0xffc64d3c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc4cfcc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc4cfa4) //120
NHSTUB(PT_PlaySound                           ,0xffc4c8b8) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6178c) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc617d8) //120
NHSTUB(PutInNdFilter                          ,0xffe3d8d4) //102
NHSTUB(PutOutNdFilter                         ,0xffe3d90c) //102
NHSTUB(Read                                   ,0xffc0a15c) //120
NHSTUB(ReadFastDir                            ,0xffdd96bc) //  1
NHSTUB(Rec2PB                                 ,0xffc64d6c) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd7c830) //104
NHSTUB(RenameFile_Fut                         ,0xffc133e0) //  1
NHSTUB(Restart                                ,0xffc19b5c) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe41c3c) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc62190) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc68210) //120
NHSTUB(SetFileAttributes                      ,0xffc13eb4) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13e64) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc61eb8) //  1
NHSTUB(SetParameterData                       ,0xffd35228) //101
NHSTUB(SetPropertyCase                        ,0xffc5d9b4) //102
NHSTUB(SetScriptMode                          ,0xffc61f08) //120
NHSTUB(SleepTask                              ,0xffc18168) //120
NHSTUB(TakeSemaphore                          ,0xffc0b774) //120
NHSTUB(TurnOffBackLight                       ,0xffc6c570) //104
NHSTUB(TurnOnBackLight                        ,0xffc6c558) //104
NHSTUB(TurnOnDisplay                          ,0xffc313e8) //120
NHSTUB(TurnOffDisplay                         ,0xffc313f8) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd2aa58) //120
NHSTUB(UnlockAE                               ,0xffc16084) //120
NHSTUB(UnlockAF                               ,0xffc15c1c) //120
NHSTUB(UnlockMainPower                        ,0xffc62070) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3a34c) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc414c8) //105
NHSTUB(VbattGet                               ,0xffc105f4) //120
NHSTUB(Write                                  ,0xffc13c34) //120
NHSTUB(WriteSDCard                            ,0xffd01548) //108
NHSTUB(_log                                   ,0xffe67dd8) //111
NHSTUB(_log10                                 ,0xffe66d1c) //112
NHSTUB(_pow                                   ,0xffe66e8c) //121
NHSTUB(_sqrt                                  ,0xffe69140) //  1
NHSTUB(add_ptp_handler                        ,0xffdaa4e4) //121
NHSTUB(apex2us                                ,0xffd7dd6c) //121
NHSTUB(close                                  ,0xffc09f74) //109
NHSTUB(err_init_task                          ,0xffc04e98) //111
NHSTUB(exmem_alloc                            ,0xffc5869c) //103
NHSTUB(exmem_free                             ,0xffc58714) //103
NHSTUB(free                                   ,0xffc03a98) //112
NHSTUB(kbd_p1_f                               ,0xffc11d34) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11d40) //109
NHSTUB(kbd_p2_f                               ,0xffc1156c) //109
NHSTUB(kbd_read_keys                          ,0xffc11c30) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc35104) //109
NHSTUB(lseek                                  ,0xffc13cc8) //120
NHSTUB(malloc                                 ,0xffc039c4) //112
NHSTUB(memcmp                                 ,0xffc0d90c) //120
NHSTUB(memcpy                                 ,0xffc74f88) //120
NHSTUB(memset                                 ,0xffd7cbe4) //120
NHSTUB(mkdir                                  ,0xffc13f2c) //109
NHSTUB(mktime_ext                             ,0xffc757f4) //  1
NHSTUB(open                                   ,0xffc09ec4) //109
NHSTUB(OpenFastDir                            ,0xffdd9628) //  1
NHSTUB(closedir                               ,0xffdd978c) //  1
NHSTUB(qsort                                  ,0xffd7d0ec) //  1
NHSTUB(rand                                   ,0xffc0da14) //121
NHSTUB(realloc                                ,0xffc03b78) //115
NHSTUB(reboot_fw_update                       ,0xffdddf90) //106
NHSTUB(set_control_event                      ,0xffc61c0c) //  1
NHSTUB(srand                                  ,0xffc0da08) //122
NHSTUB(stat                                   ,0xffc13d94) //  1
NHSTUB(strcat                                 ,0xffc74d74) //  1
NHSTUB(strchr                                 ,0xffc74dfc) //  1
NHSTUB(strcmp                                 ,0xffc0d8a4) //120
NHSTUB(strcpy                                 ,0xffc0d88c) //120
NHSTUB(strftime                               ,0xffc751fc) //  1
NHSTUB(strlen                                 ,0xffc0d8e8) //120
NHSTUB(strncmp                                ,0xffc74db0) //  1
NHSTUB(strncpy                                ,0xffc1dcc8) //  1
NHSTUB(strrchr                                ,0xffc74e20) //  1
NHSTUB(strtol                                 ,0xffc1df00) //101
NHSTUB(strtolx                                ,0xffc1dd04) //109
   DEF(task_CaptSeq                           ,0xffc4f0f8) //120
   DEF(task_ExpDrv                            ,0xffc973e4) //120
   DEF(task_FileWrite                         ,0xffdd6404) //120
   DEF(task_InitFileModules                   ,0xffc657b4) //120
   DEF(task_MovieRecord                       ,0xffc4bbbc) //120
   DEF(task_PhySw                             ,0xffc118c8) //120
NHSTUB(time                                   ,0xffc57a88) //109
NHSTUB(vsprintf                               ,0xffc0d80c) //115
NHSTUB(EngDrvRead                             ,0xffc12b74) //102
