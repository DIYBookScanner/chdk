// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00B   // Found @ 0xffc593dc, "GM1.00B" @ 0xffc593e9
//   Firmware build timestamp: Dec  8 2008 08:34:18
//   Canon DIGITAL IXUS 95 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12740 (0x31c4) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0012ad3c
//   KEYSYS = d4                 // Found @ 0xffff1be4
//   NEED_ENCODED_DISKBOOT = 2   // Found @ 0xffff1bf4
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xffd03454
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd03414

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xffc30e1c) //  2 64%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdf72e0 -> ffeb3558
// Mode  2598 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000c338) // Found @0xffc11d70
DEF(physw_run                               ,0x00001c34) // Found @0xffc119e4
DEF(physw_sleep_delay                       ,0x00001c32) // Found @0xffc119e4
DEF(levent_table                            ,0xffe8c744) // Found @0xffe8c744
DEF(FlashParamsTable                        ,0xffeb3728) // Found @0xffeb3728
DEF(movie_status                            ,0x00005680) // Found @0xffcf8060
DEF(canon_menu_active                       ,0x00002bb0) // Found @0xffc5adf8
DEF(canon_shoot_menu_active                 ,0x0000681d) // Found @0xffd2a1ac
DEF(playrec_mode                            ,0x00002924) // Found @0xffc4e4ec
DEF(zoom_status                             ,0x000096b4) // Found @0xffdf8b10
DEF(some_flag_for_af_scan                   ,0x00005b4c) // Found @0xffcfa7ac
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c
DEF(zoom_busy                               ,0x000055b0) // Found @0xffcf475c
DEF(focus_busy                              ,0x000054a8) // Found @0xffcef5cc
DEF(recreview_hold                          ,0x00003110) // Found @0xffc6677c
// Palette colour tables  found @ 0xffe9aaf8
DEF(active_palette_buffer                   ,0x000073e8) // Found @0xffd60078
DEF(palette_buffer_ptr                      ,0x000073fc) // Found @0xffd5ff2c
// Offset from start of palette_buffer to color data = 16 (Found @0xffd5edc0)
// Camera has 2 RAW buffers @ 0x40f30d7c & 0x424b358c
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffe70b98) // Found @0xffe70b98
DEF(active_raw_buffer                       ,0x00002890) // Found @0xffc4b480

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xffc2c9a8
//void *vid_get_viewport_fb()      { return (void*)0x4076f088; }             // Found @0xffe38190
DEF(viewport_fb_d                           ,0x000026b0) // Found 0x2658 (@0xffc40f88) + 0x58 (@0xffc40fc0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2658+0x58)); } // Found @0xffc40f88 & 0xffc40fc0
DEF(jpeg_count_str                          ,0x0002f1d4) // Found @0xffd57dc0
//char *camera_jpeg_count_str()    { return (char*)0x0002f1d4; }             // Found @0xffd57dc0
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe3a720
//int get_flash_params_count(void) { return 0x7a; }                          // Found @0xffd1c038

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe65a50, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe65a5c, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffe6599c, levent 0x600
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffe659b4, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffe659b4, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffe659a8, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe659c0, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe659cc, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffe659d8, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffe659e4, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffe659f0, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffe659fc, levent 0x04
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe65a08, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffe65a14, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffe65a20, levent 0x09
//    { 2, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffe65a2c, levent 0x601
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcc787c
//#define CAM_RAW_ROWS      2772 // Found @0xffcc7884
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xffc172cc

// Misc stuff
DEF(ctypes, 0xffe64876)

// For capt_seq.c
DEF(_nrflag,0x5b30) // Found @ ffcfc5c8 (0x5b38) & ffcfc5e8 (-0x08)
//static long *nrflag = (long*)(0x5b38-0x08);  // Found @ ffcfc5c8 & ffcfc5e4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc17288) //112
NHSTUB(Close                                  ,0xffc13c3c) //120
NHSTUB(CreateTask                             ,0xffc0afac) //120
NHSTUB(DebugAssert                            ,0xffc0b284) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc135cc) //116
NHSTUB(DeleteFile_Fut                         ,0xffc134e8) //112
NHSTUB(DoAELock                               ,0xffc153e0) //120
NHSTUB(DoAFLock                               ,0xffc15298) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc15348) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc565a8) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc1538c) //104
NHSTUB(ExitTask                               ,0xffc0b23c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc1fcc4) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc1fe08) //104
NHSTUB(Fclose_Fut                             ,0xffc13664) //120
NHSTUB(Feof_Fut                               ,0xffc13850) //  1
NHSTUB(Fflush_Fut                             ,0xffc1388c) //  1
NHSTUB(Fgets_Fut                              ,0xffc137b8) //  1
NHSTUB(Fopen_Fut                              ,0xffc13624) //120
NHSTUB(Fread_Fut                              ,0xffc13710) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc172c8) //112
NHSTUB(Fseek_Fut                              ,0xffc13804) //120
NHSTUB(Fwrite_Fut                             ,0xffc13764) //120
NHSTUB(GetBatteryTemperature                  ,0xffc338cc) //102
NHSTUB(GetCCDTemperature                      ,0xffc33858) //102
NHSTUB(GetCurrentAvValue                      ,0xffcf1384) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc3f81c) //  5
NHSTUB(GetDrive_FreeClusters                  ,0xffc3f874) //  5
NHSTUB(GetDrive_TotalClusters                 ,0xffc3f848) //  5
NHSTUB(GetFocusLensSubjectDistance            ,0xffcf0434) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffcf0810) //  3
NHSTUB(GetKbdState                            ,0xffc30e04) //109
NHSTUB(GetMemInfo                             ,0xffc03be4) //115
NHSTUB(GetOpticalTemperature                  ,0xffc33940) //120
NHSTUB(GetParameterData                       ,0xffd1bff8) //101
NHSTUB(GetPropertyCase                        ,0xffc5a2e8) //102
NHSTUB(GetSystemTime                          ,0xffded8c0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc966a8) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc966b4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffcf4ad4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffde5634) //102
NHSTUB(GiveSemaphore                          ,0xffc16ca4) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc88190) //102
NHSTUB(LEDDrive                               ,0xffc3043c) //120
NHSTUB(LocalTime                              ,0xffc5426c) //115
NHSTUB(LockMainPower                          ,0xffc5dbd0) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc1355c) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe34bc0) //102
NHSTUB(MoveIrisWithAv                         ,0xffdea944) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdeaecc) //120
NHSTUB(Open                                   ,0xffc13c14) //120
NHSTUB(PB2Rec                                 ,0xffc608a0) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc47b54) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc47b2c) //120
NHSTUB(PT_PlaySound                           ,0xffc47764) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5d1f8) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5d244) //120
NHSTUB(PutInNdFilter                          ,0xffdead30) //102
NHSTUB(PutOutNdFilter                         ,0xffdead54) //102
NHSTUB(Read                                   ,0xffc09ae4) //120
NHSTUB(ReadFastDir                            ,0xffdd7998) //  1
NHSTUB(Rec2PB                                 ,0xffc608e0) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd64c80) //104
NHSTUB(RenameFile_Fut                         ,0xffc13494) //  1
NHSTUB(Restart                                ,0xffc189d8) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe373a0) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5dc44) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc6421c) //120
NHSTUB(SetFileAttributes                      ,0xffc13f68) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13f18) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5d94c) //101
NHSTUB(SetParameterData                       ,0xffd1bf68) //101
NHSTUB(SetPropertyCase                        ,0xffc5a1e4) //102
NHSTUB(SetScriptMode                          ,0xffc5d99c) //120
NHSTUB(SleepTask                              ,0xffc16f0c) //120
NHSTUB(TakeSemaphore                          ,0xffc16bd4) //120
NHSTUB(TurnOffBackLight                       ,0xffc68aa8) //104
NHSTUB(TurnOnBackLight                        ,0xffc68a90) //104
NHSTUB(TurnOnDisplay                          ,0xffc2ca70) //120
NHSTUB(TurnOffDisplay                         ,0xffc2ca80) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd0d51c) //120
NHSTUB(UnlockAE                               ,0xffc15404) //120
NHSTUB(UnlockAF                               ,0xffc152d0) //120
NHSTUB(UnlockMainPower                        ,0xffc5db24) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd21b70) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3f674) //105
NHSTUB(VbattGet                               ,0xffc10644) //120
NHSTUB(Write                                  ,0xffc13ce8) //120
NHSTUB(WriteSDCard                            ,0xffce4300) //108
NHSTUB(_log                                   ,0xffe61e40) //111
NHSTUB(_log10                                 ,0xffe60acc) //112
NHSTUB(_pow                                   ,0xffe60c3c) //121
NHSTUB(_sqrt                                  ,0xffe639e4) //  1
NHSTUB(add_ptp_handler                        ,0xffdaa120) //121
NHSTUB(apex2us                                ,0xffd65d38) //121
NHSTUB(close                                  ,0xffc098fc) //109
NHSTUB(err_init_task                          ,0xffc04e2c) //111
NHSTUB(exmem_alloc                            ,0xffc54ea0) //103
NHSTUB(exmem_free                             ,0xffc54f18) //103
NHSTUB(free                                   ,0xffc03a3c) //112
NHSTUB(kbd_p1_f                               ,0xffc11dec) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11df8) //109
NHSTUB(kbd_p2_f                               ,0xffc116b0) //109
NHSTUB(kbd_read_keys                          ,0xffc11d70) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc30824) //109
NHSTUB(lseek                                  ,0xffc13d7c) //120
NHSTUB(malloc                                 ,0xffc03968) //112
NHSTUB(memcmp                                 ,0xffc0cc5c) //120
NHSTUB(memcpy                                 ,0xffc6cc38) //120
NHSTUB(memset                                 ,0xffd65020) //120
NHSTUB(mkdir                                  ,0xffc13fe0) //109
NHSTUB(mktime_ext                             ,0xffc6d4a4) //  1
NHSTUB(open                                   ,0xffc0984c) //109
NHSTUB(OpenFastDir                            ,0xffdd7904) //  1
NHSTUB(closedir                               ,0xffdd7a68) //  1
NHSTUB(qsort                                  ,0xffe1cbf8) //  1
NHSTUB(rand                                   ,0xffc0cd64) //121
NHSTUB(realloc                                ,0xffc03b1c) //115
NHSTUB(reboot_fw_update                       ,0xffddb47c) //106
NHSTUB(set_control_event                      ,0xffc5d680) //111
NHSTUB(srand                                  ,0xffc0cd58) //122
NHSTUB(stat                                   ,0xffc13e48) //  1
NHSTUB(strcat                                 ,0xffc6ca4c) //  1
NHSTUB(strchr                                 ,0xffc6cad4) //  1
NHSTUB(strcmp                                 ,0xffc0cbf4) //120
NHSTUB(strcpy                                 ,0xffc0cbdc) //120
NHSTUB(strftime                               ,0xffc6ceac) //  1
NHSTUB(strlen                                 ,0xffc0cc38) //120
NHSTUB(strncmp                                ,0xffc6ca88) //  1
NHSTUB(strncpy                                ,0xffc1cac0) //  1
NHSTUB(strrchr                                ,0xffd64ff8) //  1
NHSTUB(strtol                                 ,0xffc1ccf8) //101
NHSTUB(strtolx                                ,0xffc1cafc) //109
   DEF(task_CaptSeq                           ,0xffc49fe0) //120
   DEF(task_ExpDrv                            ,0xffc7ee88) //120
   DEF(task_FileWrite                         ,0xffdd34d8) //120
   DEF(task_InitFileModules                   ,0xffc61374) //120
   DEF(task_MovieRecord                       ,0xffcf82b4) //120
   DEF(task_PhySw                             ,0xffc119e0) //120
NHSTUB(time                                   ,0xffc54120) //109
NHSTUB(vsprintf                               ,0xffc0cba0) //115
NHSTUB(EngDrvRead                             ,0xffc12c28) //102
