// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00C   // Found @ 0xffc584f0, "GM1.00C" @ 0xffc584fd
//   Firmware build timestamp: Apr 24 2009 19:12:45
//   Canon PowerShot A1100 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12739 (0x31c3) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0012ed1c
//   KEYSYS = d4                 // Found @ 0xffff1d04
//   NEED_ENCODED_DISKBOOT = 2   // Found @ 0xffff1d14
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xffd0346c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd0342c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(ExpCtrlTool_StopContiAE              ,0xffc1f9c4) //104        *** != 0xffc1faac
//NHSTUB(SetAE_ShutterSpeed                   ,0xffe425b8) //102        *** != 0xffe3d994
//NHSTUB(kbd_pwr_off                          ,0xffc30b9c) //  2 64%    *** != 0xffc30bac
NHSTUB(kbd_pwr_on                             ,0xffc30b5c) //  2 82%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdfeb44 -> ffebbd0c
// Mode 16398 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000c624) // Found @0xffc11a0c
DEF(physw_run                               ,0x00001c24) // Found @0xffc11680
DEF(physw_sleep_delay                       ,0x00001c22) // Found @0xffc11680
DEF(levent_table                            ,0xffe93cdc) // Found @0xffe93cdc
DEF(FlashParamsTable                        ,0xffebbee0) // Found @0xffebbee0
DEF(movie_status                            ,0x00005630) // Found @0xffcf8080
DEF(canon_menu_active                       ,0x00002b7c) // Found @0xffc59f18
DEF(canon_shoot_menu_active                 ,0x000068c9) // Found @0xffd2bd58
DEF(playrec_mode                            ,0x000028f0) // Found @0xffc4d504
DEF(zoom_status                             ,0x000098d0) // Found @0xffe00374
DEF(some_flag_for_af_scan                   ,0x00005af4) // Found @0xffcfa7a4
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c
DEF(zoom_busy                               ,0x00005560) // Found @0xffcf4788
DEF(focus_busy                              ,0x00005478) // Found @0xffcefa8c
//DEF(recreview_hold                          ,0x000030e0) // Found @0xffc65938, ** != ** stubs_min = 0xffc00414 (0xFFC00414)
// Palette colour tables  found @ 0xffea322c
DEF(active_palette_buffer                   ,0x000075a4) // Found @0xffd67c68
DEF(palette_buffer_ptr                      ,0x000075b8) // Found @0xffd67b1c
// Offset from start of palette_buffer to color data = 16 (Found @0xffd669b0)
// Camera appears to have only 1 RAW buffer @ 0x4139e56c (Found @0xffe458b4)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xffc2c594
//void *vid_get_viewport_fb()      { return (void*)0x4076fcc0; }             // Found @0xffe433a8
DEF(viewport_fb_d                           ,0x00002688) // Found 0x2630 (@0xffc404f0) + 0x58 (@0xffc40528)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2630+0x58)); } // Found @0xffc404f0 & 0xffc40528
DEF(jpeg_count_str                          ,0x0002f4a8) // Found @0xffd60210
//char *camera_jpeg_count_str()    { return (char*)0x0002f4a8; }             // Found @0xffd60210
//long hook_raw_size()             { return 0x011e4ee0; }                    // Found @0xffe45910
//int get_flash_params_count(void) { return 0x7a; }                          // Found @0xffd1cb34

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe70c7c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe70c88, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_UP              ,0x00000100 }, // Found @0xffe70b68, levent 0x04
//    { 1, KEY_DOWN            ,0x00000200 }, // Found @0xffe70b74, levent 0x05
//    { 1, KEY_RIGHT           ,0x00000400 }, // Found @0xffe70b80, levent 0x07
//    { 1, KEY_LEFT            ,0x00000800 }, // Found @0xffe70b8c, levent 0x06
//    { 1, KEY_SET             ,0x00001000 }, // Found @0xffe70b98, levent 0x08
//    { 1, KEY_MENU            ,0x00002000 }, // Found @0xffe70ba4, levent 0x09
//    { 1, KEY_DISPLAY         ,0x00004000 }, // Found @0xffe70bb0, levent 0x0a
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe70c1c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe70c1c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe70c10, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000040 }, // Found @0xffe70c28, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000080 }, // Found @0xffe70c34, levent 0x03
//    { 2, KEY_POWER           ,0x00002000 }, // Found @0xffe70c4c, levent 0x600 (uses inverted logic in physw_status)
//    { 2, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffe70c58, levent 0x601 (uses inverted logic in physw_status)
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4104 // Found @0xffcc7c84
//#define CAM_RAW_ROWS      3048 // Found @0xffcc7c8c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xffc16e84

// Misc stuff
DEF(ctypes, 0xffe6fa66)

// For capt_seq.c
DEF(_nrflag,0x5ad8) // Found @ ffcfc4d4 (0x5ae0) & ffcfc4f4 (-0x08)
//static long *nrflag = (long*)(0x5ae0-0x08);  // Found @ ffcfc4d4 & ffcfc4f0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc16e40) //112
NHSTUB(Close                                  ,0xffc138e0) //120
NHSTUB(CreateTask                             ,0xffc0afac) //120
NHSTUB(DebugAssert                            ,0xffc0b284) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc13270) //116
NHSTUB(DeleteFile_Fut                         ,0xffc1318c) //112
NHSTUB(DoAELock                               ,0xffc15088) //120
NHSTUB(DoAFLock                               ,0xffc14f40) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc14ff0) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc555c0) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc15034) //104
NHSTUB(ExitTask                               ,0xffc0b23c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc1f880) //104
NHSTUB(Fclose_Fut                             ,0xffc13308) //120
NHSTUB(Feof_Fut                               ,0xffc134f4) //  1
NHSTUB(Fflush_Fut                             ,0xffc13530) //  1
NHSTUB(Fgets_Fut                              ,0xffc1345c) //  1
NHSTUB(Fopen_Fut                              ,0xffc132c8) //120
NHSTUB(Fread_Fut                              ,0xffc133b4) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc16e80) //112
NHSTUB(Fseek_Fut                              ,0xffc134a8) //120
NHSTUB(Fwrite_Fut                             ,0xffc13408) //120
NHSTUB(GetBatteryTemperature                  ,0xffc32c44) //102
NHSTUB(GetCCDTemperature                      ,0xffc32bd0) //102
NHSTUB(GetCurrentAvValue                      ,0xffcf18a8) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc3ed84) //  5
NHSTUB(GetDrive_FreeClusters                  ,0xffc3eddc) //  5
NHSTUB(GetDrive_TotalClusters                 ,0xffc3edb0) //  5
NHSTUB(GetFocusLensSubjectDistance            ,0xffcf08f4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffcf0cd4) //  3
NHSTUB(GetKbdState                            ,0xffc30b28) //109
NHSTUB(GetMemInfo                             ,0xffc03be4) //115
NHSTUB(GetOpticalTemperature                  ,0xffc32cbc) //120
NHSTUB(GetParameterData                       ,0xffd1caf4) //101
NHSTUB(GetPropertyCase                        ,0xffc593fc) //102
NHSTUB(GetSystemTime                          ,0xffdf5404) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc959f0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc959fc) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffcf4b00) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffded338) //102
NHSTUB(GiveSemaphore                          ,0xffc1685c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc870ec) //102
NHSTUB(LEDDrive                               ,0xffc30088) //120
NHSTUB(LocalTime                              ,0xffc53284) //115
NHSTUB(LockMainPower                          ,0xffc5cce8) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc13200) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe3fdd8) //102
NHSTUB(MoveIrisWithAv                         ,0xffdf2648) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdf2bd4) //120
NHSTUB(Open                                   ,0xffc138b8) //120
NHSTUB(PB2Rec                                 ,0xffc5e760) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc46da8) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc46d80) //120
NHSTUB(PT_PlaySound                           ,0xffc469bc) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5c310) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5c35c) //120
NHSTUB(PutInNdFilter                          ,0xffdf2a38) //102
NHSTUB(PutOutNdFilter                         ,0xffdf2a5c) //102
NHSTUB(Read                                   ,0xffc09ae4) //120
NHSTUB(ReadFastDir                            ,0xffddf844) //  1
NHSTUB(Rec2PB                                 ,0xffc5fb48) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd6b630) //104
NHSTUB(RenameFile_Fut                         ,0xffc13138) //  1
NHSTUB(Restart                                ,0xffc18594) //106
NHSTUB(SetAutoShutdownTime                    ,0xffc5cd5c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc632cc) //120
NHSTUB(SetFileAttributes                      ,0xffc13c0c) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13bbc) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5ca64) //101
NHSTUB(SetParameterData                       ,0xffd1ca64) //101
NHSTUB(SetPropertyCase                        ,0xffc592f8) //102
NHSTUB(SetScriptMode                          ,0xffc5cab4) //120
NHSTUB(SleepTask                              ,0xffc16ac4) //120
NHSTUB(TakeSemaphore                          ,0xffc1678c) //120
NHSTUB(TurnOffBackLight                       ,0xffc67d48) //104
NHSTUB(TurnOnBackLight                        ,0xffc67d30) //104
NHSTUB(TurnOnDisplay                          ,0xffc2c65c) //120
NHSTUB(TurnOffDisplay                         ,0xffc2c66c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd0d490) //120
NHSTUB(UnlockAE                               ,0xffc150ac) //120
NHSTUB(UnlockAF                               ,0xffc14f78) //120
NHSTUB(UnlockMainPower                        ,0xffc5cc3c) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd226ec) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3ebdc) //105
NHSTUB(VbattGet                               ,0xffc10318) //120
NHSTUB(Write                                  ,0xffc1398c) //120
NHSTUB(WriteSDCard                            ,0xffce4748) //108
NHSTUB(_log                                   ,0xffe6d86c) //111
NHSTUB(_log10                                 ,0xffe6c7b0) //112
NHSTUB(_pow                                   ,0xffe6c920) //121
NHSTUB(_sqrt                                  ,0xffe6ebd4) //  1
NHSTUB(add_ptp_handler                        ,0xffdb1584) //121
NHSTUB(apex2us                                ,0xffd6c6e8) //121
NHSTUB(close                                  ,0xffc098fc) //109
NHSTUB(err_init_task                          ,0xffc04e2c) //111
NHSTUB(exmem_alloc                            ,0xffc53eb8) //103
NHSTUB(exmem_free                             ,0xffc53f30) //103
NHSTUB(free                                   ,0xffc03a3c) //112
NHSTUB(kbd_p1_f                               ,0xffc11a90) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11a9c) //109
NHSTUB(kbd_p2_f                               ,0xffc1134c) //109
NHSTUB(kbd_read_keys                          ,0xffc11a0c) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc304a4) //109
NHSTUB(lseek                                  ,0xffc13a20) //120
NHSTUB(malloc                                 ,0xffc03968) //112
NHSTUB(memcmp                                 ,0xffc0cc60) //120
NHSTUB(memcpy                                 ,0xffc6b9dc) //120
NHSTUB(memset                                 ,0xffd6b9d0) //120
NHSTUB(mkdir                                  ,0xffc13c84) //109
NHSTUB(mktime_ext                             ,0xffc6c248) //  1
NHSTUB(open                                   ,0xffc0984c) //109
NHSTUB(OpenFastDir                            ,0xffddf7b0) //  1
NHSTUB(closedir                               ,0xffddf914) //  1
NHSTUB(qsort                                  ,0xffe265e4) //  1
NHSTUB(rand                                   ,0xffc0cd68) //121
NHSTUB(realloc                                ,0xffc03b1c) //115
NHSTUB(reboot_fw_update                       ,0xffde3328) //106
NHSTUB(set_control_event                      ,0xffc5c798) //111
NHSTUB(srand                                  ,0xffc0cd5c) //122
NHSTUB(stat                                   ,0xffc13aec) //  1
NHSTUB(strcat                                 ,0xffc6b7f0) //  1
NHSTUB(strchr                                 ,0xffc6b878) //  1
NHSTUB(strcmp                                 ,0xffc0cbf8) //120
NHSTUB(strcpy                                 ,0xffc0cbe0) //120
NHSTUB(strftime                               ,0xffc6bc50) //  1
NHSTUB(strlen                                 ,0xffc0cc3c) //120
NHSTUB(strncmp                                ,0xffc6b82c) //  1
NHSTUB(strncpy                                ,0xffc1c67c) //  1
NHSTUB(strrchr                                ,0xffd6b9a8) //  1
NHSTUB(strtol                                 ,0xffc1c8b4) //101
NHSTUB(strtolx                                ,0xffc1c6b8) //109
   DEF(task_CaptSeq                           ,0xffc49060) //120
   DEF(task_ExpDrv                            ,0xffc7ddcc) //120
   DEF(task_FileWrite                         ,0xffddb384) //120
   DEF(task_InitFileModules                   ,0xffc60508) //120
   DEF(task_MovieRecord                       ,0xffcf82d4) //120
   DEF(task_PhySw                             ,0xffc1167c) //120
NHSTUB(time                                   ,0xffc53138) //109
NHSTUB(vsprintf                               ,0xffc0cba4) //115
NHSTUB(EngDrvRead                             ,0xffc128cc) //102
