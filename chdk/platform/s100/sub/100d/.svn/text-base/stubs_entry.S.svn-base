// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R49 (DRYOS version 2.3, release #0049)
//   Firmware Ver GM1.00D   // Found @ 0xff0908ac, "GM1.00D" @ 0xff0908b9
//   Firmware build timestamp: Sep 14 2011 16:23:43
//   Canon PowerShot S100

// Values for makefile.inc
//   PLATFORMOSVER = 49
//   PLATFORMID = 12854 (0x3236) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x00195d34
//   KEYSYS = d4c                // Found @ 0xffff3b28
//   NEED_ENCODED_DISKBOOT = 7   // Found @ 0xffff3b38
//   ARAM_HEAP_START = 0x5de000  // Found @ 0xff1dd024
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1dcfe4

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff3877bc -> ff626540
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000386bc) // Found @0xff024db0
DEF(physw_run                               ,0x00001c3c) // Found @0xff02493c
DEF(physw_sleep_delay                       ,0x00001c44) // Found @0xff02493c
DEF(levent_table                            ,0xff5905bc) // Found @0xff5905bc
DEF(FlashParamsTable                        ,0xff6267a4) // Found @0xff6267a4
DEF(movie_status                            ,0x00009bfc) // Found @0xff1ca41c
DEF(video_compression_rate                  ,0x00009c3c) // Found @0xff1cbc80
DEF(full_screen_refresh                     ,0x0000ca28) // Found @0xff297af0
DEF(canon_menu_active                       ,0x00004484) // Found @0xff0924cc
DEF(canon_shoot_menu_active                 ,0x0000b291) // Found @0xff22ca24
DEF(playrec_mode                            ,0x000041a4) // Found @0xff083ca8
DEF(zoom_status                             ,0x0000ad6c) // Found @0xff213958
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 121 entries in the table - set NUM_FL to 121
DEF(focus_len_table                         ,0xfff4a4f8) // Found @0xfff4a4f8
DEF(zoom_busy                               ,0x00009b24) // Found @0xff1c6118
DEF(focus_busy                              ,0x00009940) // Found @0xff1bef10
DEF(recreview_hold                          ,0x00005008) // Found @0xff0a51b0
// Palette colour tables  found @ 0xff5adb58
DEF(palette_control                         ,0x0000ca28) // Found @0xff297a6c
DEF(active_palette_buffer                   ,0x0000ca30) // Found @0xff297a70
DEF(palette_buffer_ptr                      ,0x0000ca34) // Found @0xff297f28
DEF(palette_buffer                          ,0x000cf8d4) // Found @0xff297f38
// Offset from start of palette_buffer to color data = 4 (Found @0xff3c758c)
DEF(bitmap_buffer                           ,0x0000ca6c) // Found @0xff29c9b0
DEF(active_bitmap_buffer                    ,0x0000ca64) // Found @0xff29c9b4
DEF(viewport_buffers                        ,0xff4531e8) // Found @0xff0466bc
DEF(active_viewport_buffer                  ,0x00002194) // Found @0xff046390
// Camera has 2 RAW buffers @ 0x44000000 & 0x4ad65bc0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff467f68) // Found @0xff467f68
DEF(active_raw_buffer                       ,0x000040ec) // Found @0xff07f6e0

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40685000; }             // Found @0xff051fbc
//void *vid_get_viewport_fb()      { return (void*)0x407dab80; }             // Found @0xff3fc0c8
DEF(viewport_fb_d                           ,0x00003df8) // Found 0x3da0 (@0xff07007c) + 0x58 (@0xff0700b4)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3da0+0x58)); } // Found @0xff07007c & 0xff0700b4
DEF(jpeg_count_str                          ,0x000cf0cc) // Found @0xff289050
//char *camera_jpeg_count_str()    { return (char*)0x000cf0cc; }             // Found @0xff289050
//long hook_raw_size()             { return 0x01297380; }                    // Found @0xff3feed0
//int get_flash_params_count(void) { return 0x9f; }                          // Found @0xff206d58

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00000800 // Found @0xff4537fc, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xff45383c, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_DOWN            ,0x00000002 }, // Found @0xff45373c, levent 0x05
//    { 0, KEY_LEFT            ,0x00000004 }, // Found @0xff453744, levent 0x06
//    { 0, KEY_MENU            ,0x00000008 }, // Found @0xff45374c, levent 0x09
//    { 0, KEY_SET             ,0x00000020 }, // Found @0xff45375c, levent 0x08
//    { 0, KEY_UP              ,0x00000040 }, // Found @0xff453764, levent 0x04
//    { 0, KEY_RIGHT           ,0x00000080 }, // Found @0xff45376c, levent 0x07
//    { 0, KEY_VIDEO           ,0x00000100 }, // Found @0xff453774, levent 0x19
//    { 0, KEY_ZOOM_OUT        ,0x00008000 }, // Found @0xff4537ac, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00010000 }, // Found @0xff4537b4, levent 0x02
//    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xff4537dc, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xff4537dc, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xff4537d4, levent 0x00
//    { 1, KEY_POWER           ,0x00400000 }, // Found @0xff4537e4, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x00800000 }, // Found @0xff4537ec, levent 0x101
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4160 // Found @0xff190f44
//#define CAM_RAW_ROWS      3124 // Found @0xff190f4c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02bd84

// Misc stuff
DEF(ctypes, 0xff4524b6)

// For capt_seq.c
DEF(_nrflag,0xcb38) // Found @ ff2a57b4 (0xcb38) & ff2a57f0 (+0x00)
//static long *nrflag = (long*)(0xcb38+0x00);  // Found @ ff2a57b4 & ff2a57f0
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff02bd3c) //112
NHSTUB(Close                                  ,0xff0275bc) //120
NHSTUB(CreateTask                             ,0xff00eaf0) //120
NHSTUB(DebugAssert                            ,0xff00edc8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff026fb8) //116
NHSTUB(DeleteFile_Fut                         ,0xff026ed4) //112
NHSTUB(DoAELock                               ,0xff029680) //120
NHSTUB(DoAFLock                               ,0xff029208) //120
NHSTUB(EnterToCompensationEVF                 ,0xff0295dc) //104
NHSTUB(ExecuteEventProcedure                  ,0xff08d868) //104
NHSTUB(ExitFromCompensationEVF                ,0xff029620) //104
NHSTUB(ExitTask                               ,0xff00ed80) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff037d9c) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff037e7c) //104
NHSTUB(Fclose_Fut                             ,0xff027050) //120
NHSTUB(Feof_Fut                               ,0xff02723c) //  1
NHSTUB(Fflush_Fut                             ,0xff027278) //  1
NHSTUB(Fgets_Fut                              ,0xff0271a4) //  6
NHSTUB(Fopen_Fut                              ,0xff027010) //120
NHSTUB(Fread_Fut                              ,0xff0270fc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff02bd7c) //112
NHSTUB(Fseek_Fut                              ,0xff0271f0) //120
NHSTUB(Fwrite_Fut                             ,0xff027150) //120
NHSTUB(GetBatteryTemperature                  ,0xff05faac) //102
NHSTUB(GetCCDTemperature                      ,0xff05fa38) //102
NHSTUB(GetCurrentAvValue                      ,0xff1c1e48) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff06e744) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff06e79c) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff06e774) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1bfc8c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1c00dc) //  3
NHSTUB(GetImageFolder                         ,0xff19a600) //122
NHSTUB(GetKbdState                            ,0xff058f58) //109
NHSTUB(GetMemInfo                             ,0xff00a2b8) //115
NHSTUB(GetOpticalTemperature                  ,0xff05fb20) //120
NHSTUB(GetParameterData                       ,0xff206d18) //101
NHSTUB(GetPropertyCase                        ,0xff091950) //102
NHSTUB(GetSystemTime                          ,0xff37445c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff048f34) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff048f40) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1c6590) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff35f990) //102
NHSTUB(GiveSemaphore                          ,0xff02b4bc) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0f2e64) //102
NHSTUB(LEDDrive                               ,0xff0582f8) //120
NHSTUB(LocalTime                              ,0xff08b22c) //115
NHSTUB(LockMainPower                          ,0xff098e00) //120
NHSTUB(MakeDirectory_Fut                      ,0xff026f48) //116
NHSTUB(MakeSDCardBootable                     ,0xff06e9c4) //105
NHSTUB(MoveFocusLensToDistance                ,0xff3f82f8) //102
NHSTUB(MoveIrisWithAv                         ,0xff370ca4) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff371658) //120
NHSTUB(Open                                   ,0xff0274f4) //120
NHSTUB(PB2Rec                                 ,0xff09c3f4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff079a78) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff079a50) //120
NHSTUB(PT_PlaySound                           ,0xff085c9c) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff09671c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff096768) //120
NHSTUB(PutInNdFilter                          ,0xff371430) //102
NHSTUB(PutOutNdFilter                         ,0xff371454) //102
NHSTUB(Read                                   ,0xff00ad74) //120
NHSTUB(ReadFastDir                            ,0xff3498ec) //115
NHSTUB(Rec2PB                                 ,0xff09c434) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0b5954) //104
NHSTUB(RenameFile_Fut                         ,0xff026e40) //116
NHSTUB(Restart                                ,0xff02d59c) //106
NHSTUB(ScreenLock                             ,0xff0b6b4c) //117
NHSTUB(ScreenUnlock                           ,0xff0b6bb0) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff3fb240) //102
NHSTUB(SetAutoShutdownTime                    ,0xff098e74) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0a24e0) //120
NHSTUB(SetFileAttributes                      ,0xff0279c0) //  6
NHSTUB(SetFileTimeStamp                       ,0xff027948) //  6
NHSTUB(SetLogicalEventActive                  ,0xff098b4c) //101
NHSTUB(SetParameterData                       ,0xff206bf4) //101
NHSTUB(SetPropertyCase                        ,0xff0917b4) //102
NHSTUB(SetScriptMode                          ,0xff098b9c) //120
NHSTUB(SleepTask                              ,0xff02b768) //120
NHSTUB(TakeSemaphore                          ,0xff02b3ec) //120
NHSTUB(TurnOffBackLight                       ,0xff0ad6b8) //104
NHSTUB(TurnOnBackLight                        ,0xff0ad6a0) //104
NHSTUB(TurnOnDisplay                          ,0xff0523d8) //120
NHSTUB(TurnOffDisplay                         ,0xff0523e8) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1f07bc) //120
NHSTUB(UnlockAE                               ,0xff0296a4) //120
NHSTUB(UnlockAF                               ,0xff029240) //120
NHSTUB(UnlockMainPower                        ,0xff098d54) //120
NHSTUB(VbattGet                               ,0xff02237c) //120
NHSTUB(Write                                  ,0xff027610) //120
NHSTUB(WriteSDCard                            ,0xff1b0930) //108
NHSTUB(_log                                   ,0xff44ef38) //111
NHSTUB(_log10                                 ,0xff44f400) //112
NHSTUB(_pow                                   ,0xff44f564) //121
NHSTUB(_sqrt                                  ,0xff4512cc) //  6
NHSTUB(add_ptp_handler                        ,0xff2e69a8) //121
NHSTUB(apex2us                                ,0xff29f17c) //121
NHSTUB(close                                  ,0xff00abd0) //109
NHSTUB(err_init_task                          ,0xff00602c) //111
NHSTUB(exmem_alloc                            ,0xff08c1ec) //101
NHSTUB(exmem_free                             ,0xff08c264) //101
NHSTUB(free                                   ,0xff004264) //112
NHSTUB(kbd_p1_f                               ,0xff024e00) //109
NHSTUB(kbd_p1_f_cont                          ,0xff024e0c) //109
NHSTUB(kbd_p2_f                               ,0xff0245d4) //109
NHSTUB(kbd_read_keys                          ,0xff024db0) //109
NHSTUB(kbd_read_keys_r2                       ,0xff0587c8) //109
NHSTUB(lseek                                  ,0xff0277d8) //120
NHSTUB(malloc                                 ,0xff00420c) //112
NHSTUB(memcmp                                 ,0xff010a60) //120
NHSTUB(memcpy                                 ,0xff0316c0) //120
NHSTUB(memset                                 ,0xff29d1a0) //120
NHSTUB(mkdir                                  ,0xff027a58) //109
NHSTUB(mktime_ext                             ,0xff0b79a0) //  1
NHSTUB(open                                   ,0xff00ab20) //109
NHSTUB(OpenFastDir                            ,0xff349798) //115
NHSTUB(closedir                               ,0xff349748) //121
NHSTUB(qsort                                  ,0xff3c8150) //  6
NHSTUB(rand                                   ,0xff29d2dc) //121
NHSTUB(realloc                                ,0xff29d21c) //115
NHSTUB(reboot_fw_update                       ,0xff34f040) //106
NHSTUB(set_control_event                      ,0xff098740) //111
NHSTUB(srand                                  ,0xff29d2d0) //122
NHSTUB(stat                                   ,0xff027820) //109
NHSTUB(strcat                                 ,0xff0b7158) //  1
NHSTUB(strchr                                 ,0xff0040d8) //  1
NHSTUB(strcmp                                 ,0xff010a1c) //120
NHSTUB(strcpy                                 ,0xff010a04) //120
NHSTUB(strftime                               ,0xff0b73a0) //113
NHSTUB(strlen                                 ,0xff004124) //120
NHSTUB(strncmp                                ,0xff00408c) //  1
NHSTUB(strncpy                                ,0xff004050) //  1
NHSTUB(strrchr                                ,0xff0040fc) //  1
NHSTUB(strtol                                 ,0xff0319c0) //101
NHSTUB(strtolx                                ,0xff0317c4) //109
   DEF(task_CaptSeq                           ,0xff07ccdc) //120
   DEF(task_ExpDrv                            ,0xff0cfb78) //120
   DEF(task_FileWrite                         ,0xff3476d8) //120
   DEF(task_InitFileModules                   ,0xff09cdf8) //120
   DEF(task_MovieRecord                       ,0xff1cc43c) //120
   DEF(task_PhySw                             ,0xff024938) //120
   DEF(task_RotaryEncoder                     ,0xff05927c) //120
NHSTUB(time                                   ,0xff08b808) //109
NHSTUB(vsprintf                               ,0xff0109c4) //115
NHSTUB(EngDrvRead                             ,0xff025c2c) //102
