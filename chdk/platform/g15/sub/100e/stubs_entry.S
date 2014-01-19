// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R51 (DRYOS version 2.3, release #0051)
//   Firmware Ver GM1.00E   // Found @ 0xff09871c, "GM1.00E" @ 0xff098729
//   Firmware build timestamp: Oct 19 2012 15:26:54
//   Canon PowerShot G15

// Values for makefile.inc
//   PLATFORMOSVER = 51
//   PLATFORMID = 12888 (0x3258) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x0018b824
//   KEYSYS = d4c                // Found @ 0xffff3c68
//   NEED_ENCODED_DISKBOOT = 9   // Found @ 0xffff3c78

// Note, ROM copied to RAM :- from 0xff746280, to 0x00685000, len 16605 words.
//   ARAM_HEAP_START = 0x5ce000  // Found @ 0xff1f1760
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1f1724

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff01c4f0) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff01d000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff395d74 -> ff6f1674
// Mode 16924 in firmware but not in current modemap
// Mode  8745 in firmware but not in current modemap
// Mode 33295 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0003ac0c) // Found @0xff01a3b8
DEF(physw_run                               ,0x00001d64) // Found @0xff019f14
DEF(physw_sleep_delay                       ,0x00001d6c) // Found @0xff019f14
DEF(levent_table                            ,0xff618968) // Found @0xff618968
DEF(FlashParamsTable                        ,0xff6f18f8) // Found @0xff6f18f8
//DEF(movie_status                            ,0x0000944c) // Found @0xff1ddb38,          stubs_min = 0x0000944c (0x944C)
DEF(video_compression_rate                  ,0x0000947c) // Found @0xff1dedf0
DEF(full_screen_refresh                     ,0x00009d30) // Found @0xff1ff190
DEF(canon_menu_active                       ,0x00004470) // Found @0xff0a1980
DEF(canon_shoot_menu_active                 ,0x0000c18d) // Found @0xff29f914
DEF(playrec_mode                            ,0x00003988) // Found @0xff08df30
DEF(zoom_status                             ,0x000069e0) // Found @0xff159798
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 121 entries in the table - set NUM_FL to 121
DEF(focus_len_table                         ,0xfff4a700) // Found @0xfff4a700
DEF(zoom_busy                               ,0x00009300) // Found @0xff1d8c04
DEF(focus_busy                              ,0x0000907c) // Found @0xff1d1a88
DEF(recreview_hold                          ,0x00002a28) // Found @0xff054378
// Palette colour tables  found @ 0xff61c63c
DEF(palette_control                         ,0x00009d30) // Found @0xff1ff10c
DEF(active_palette_buffer                   ,0x00009d38) // Found @0xff1ff110
DEF(palette_buffer_ptr                      ,0x00009d3c) // Found @0xff1ff5c8
DEF(palette_buffer                          ,0x000e181c) // Found @0xff1ff5d8
// Offset from start of palette_buffer to color data = 4 (Found @0xff3b40bc)
DEF(bitmap_buffer                           ,0x00009d74) // Found @0xff202fbc
DEF(active_bitmap_buffer                    ,0x00009d6c) // Found @0xff202fc0
// Camera has 2 RAW buffers @ 0x44000000 & 0x4ad65bc0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff4ca84c) // Found @0xff4ca84c
DEF(active_raw_buffer                       ,0x00003908) // Found @0xff089cc8

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff057d44
//void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xff430de4
DEF(viewport_fb_d                           ,0x00003584) // Found 0x3530 (@0xff0760cc) + 0x54 (@0xff076104)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3530+0x54)); } // Found @0xff0760cc & 0xff076104
DEF(jpeg_count_str                          ,0x000e7034) // Found @0xff2830a8
//char *camera_jpeg_count_str()    { return (char*)0x000e7034; }             // Found @0xff2830a8
//long hook_raw_size()             { return 0x01297380; }                    // Found @0xff432780
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff1f6800

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00000002 // Found @0xff4a13fc, levent 0x20a
//#define SD_READONLY_IDX     1
//#define USB_MASK            0x10000000 // Found @0xff4a1464, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SET             ,0x00000800 }, // Found @0xff4a1384, levent 0x08
//    { 0, KEY_RIGHT           ,0x00001000 }, // Found @0xff4a138c, levent 0x07
//    { 0, KEY_DOWN            ,0x00002000 }, // Found @0xff4a1394, levent 0x05
//    { 0, KEY_MENU            ,0x00004000 }, // Found @0xff4a139c, levent 0x09
//    { 0, KEY_LEFT            ,0x00008000 }, // Found @0xff4a13a4, levent 0x06
//    { 0, KEY_UP              ,0x00040000 }, // Found @0xff4a13bc, levent 0x04
//    { 0, KEY_ZOOM_IN         ,0x00100000 }, // Found @0xff4a13cc, levent 0x02
//    { 0, KEY_ZOOM_OUT        ,0x00200000 }, // Found @0xff4a13d4, levent 0x03
//    { 2, KEY_POWER           ,0x00000800 }, // Found @0xff4a141c, levent 0x100
//    { 2, KEY_PLAYBACK        ,0x00008000 }, // Found @0xff4a1424, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x000c0000 }, // Found @0xff4a1434, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00080000 }, // Found @0xff4a1434, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00040000 }, // Found @0xff4a142c, levent 0x00
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4160 // Found @0xff1a782c
//#define CAM_RAW_ROWS      3124 // Found @0xff1a7834
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff020880

// Misc stuff
DEF(ctypes, 0xff49ff98)

// For capt_seq.c
DEF(_nrflag,0xc39c) // Found @ ff2b0890 (0xc39c) & ff2b08cc (+0x00)
//static long *nrflag = (long*)(0xc39c+0x00);  // Found @ ff2b0890 & ff2b08cc
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff020838) //112
NHSTUB(Close                                  ,0xff01cb64) //120
NHSTUB(CreateTask                             ,0x0068ab8c) //120
NHSTUB(DebugAssert                            ,0x0068b104) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff01c564) //116
NHSTUB(DoAELock                               ,0xff01ed40) //120
NHSTUB(DoAFLock                               ,0xff01e8e0) //120
NHSTUB(EnterToCompensationEVF                 ,0xff01ec9c) //104
NHSTUB(ExecuteEventProcedure                  ,0xff095720) //104
NHSTUB(ExitFromCompensationEVF                ,0xff01ece0) //104
NHSTUB(ExitTask                               ,0x0068ae1c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff02e74c) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff02e8b4) //104
NHSTUB(Fclose_Fut                             ,0xff01c5fc) //120
NHSTUB(Feof_Fut                               ,0xff01c7e8) //  1
NHSTUB(Fflush_Fut                             ,0xff01c824) //  1
NHSTUB(Fgets_Fut                              ,0xff01c750) //  6
NHSTUB(Fopen_Fut                              ,0xff01c5bc) //120
NHSTUB(Fread_Fut                              ,0xff01c6a8) //120
NHSTUB(FreeUncacheableMemory                  ,0xff020878) //112
NHSTUB(Fseek_Fut                              ,0xff01c79c) //120
NHSTUB(Fwrite_Fut                             ,0xff01c6fc) //120
NHSTUB(GetBatteryTemperature                  ,0xff0622e8) //102
NHSTUB(GetCCDTemperature                      ,0xff062274) //102
NHSTUB(GetCurrentAvValue                      ,0xff07d4d0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff073d0c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff073d64) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff073d3c) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1d2aa0) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1d2e5c) //  3
NHSTUB(GetImageFolder                         ,0xff1b1544) //122
NHSTUB(GetKbdState                            ,0xff05e860) //109
NHSTUB(GetMemInfo                             ,0xff005280) //115
NHSTUB(GetOpticalTemperature                  ,0xff06235c) //120
NHSTUB(GetParameterData                       ,0xff1f67c0) //101
NHSTUB(GetPropertyCase                        ,0xff099750) //101
NHSTUB(GetSystemTime                          ,0xff39142c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff041770) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff04177c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1d9078) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff37c3ac) //102
NHSTUB(GiveSemaphore                          ,0x0068aaec) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff036f38) //102
NHSTUB(LEDDrive                               ,0xff1e0c50) //120
NHSTUB(LocalTime                              ,0x0068f420) //115
NHSTUB(LockMainPower                          ,0xff09db34) //120
NHSTUB(MakeSDCardBootable                     ,0xff073f9c) //105
NHSTUB(MoveFocusLensToDistance                ,0xff42c928) //102
NHSTUB(MoveIrisWithAv                         ,0xff38d508) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff38dec4) //120
NHSTUB(Open                                   ,0xff01ca9c) //120
NHSTUB(PB2Rec                                 ,0xff049dd0) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff1e1d50) //102
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff1e1d28) //102
NHSTUB(PT_PlaySound                           ,0xff090110) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff09b2ec) //120
NHSTUB(PostLogicalEventToUI                   ,0xff09b338) //120
NHSTUB(PutInNdFilter                          ,0xff38dc94) //102
NHSTUB(PutOutNdFilter                         ,0xff38dcb8) //102
NHSTUB(Read                                   ,0xff005d3c) //120
NHSTUB(ReadFastDir                            ,0xff368fa0) //115
NHSTUB(Rec2PB                                 ,0xff049e10) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0a0370) //104
NHSTUB(RenameFile_Fut                         ,0xff01c45c) //116
NHSTUB(Restart                                ,0xff02204c) //106
NHSTUB(ScreenLock                             ,0xff0a1348) //117
NHSTUB(ScreenUnlock                           ,0xff0a13ac) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff42fc5c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff09dba8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0a9498) //120
NHSTUB(SetFileAttributes                      ,0xff01cf68) //  6
NHSTUB(SetFileTimeStamp                       ,0xff01cef0) //  6
NHSTUB(SetLogicalEventActive                  ,0xff09d880) //101
NHSTUB(SetParameterData                       ,0xff1f669c) //101
NHSTUB(SetPropertyCase                        ,0xff0995c8) //101
NHSTUB(SetScriptMode                          ,0xff09d8d0) //120
NHSTUB(SleepTask                              ,0x0068c4e4) //120
NHSTUB(TakeSemaphore                          ,0x0068aa1c) //120
NHSTUB(TurnOffBackLight                       ,0xff0ad284) //104
NHSTUB(TurnOnBackLight                        ,0xff0ad26c) //104
NHSTUB(TurnOnDisplay                          ,0xff058158) //120
NHSTUB(TurnOffDisplay                         ,0xff058168) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff214af4) //120
NHSTUB(UnlockAE                               ,0xff01ed64) //120
NHSTUB(UnlockAF                               ,0xff01e918) //120
NHSTUB(UnlockMainPower                        ,0xff09da88) //120
NHSTUB(UnsetZoomForMovie                      ,0xff04fea0) //104
NHSTUB(VbattGet                               ,0xff018ad4) //120
NHSTUB(Write                                  ,0xff01cbb8) //120
NHSTUB(WriteSDCard                            ,0xff1c5c34) //108
NHSTUB(_log                                   ,0x006915c0) //111
NHSTUB(_log10                                 ,0x00691b00) //112
NHSTUB(_pow                                   ,0x00691c78) //121
NHSTUB(_sqrt                                  ,0x00693bd8) //  6
NHSTUB(add_ptp_handler                        ,0xff2f7c84) //121
NHSTUB(apex2us                                ,0xff2a9cdc) //121
NHSTUB(close                                  ,0xff005b98) //109
NHSTUB(err_init_task                          ,0xff004310) //111
NHSTUB(exmem_alloc                            ,0xff0940f4) //101
NHSTUB(exmem_free                             ,0xff09416c) //101
NHSTUB(free                                   ,0xff002f0c) //112
NHSTUB(kbd_p1_f                               ,0xff01a408) //109
NHSTUB(kbd_p1_f_cont                          ,0xff01a414) //109
NHSTUB(kbd_p2_f                               ,0xff019bac) //109
NHSTUB(kbd_read_keys                          ,0xff01a3b8) //109
NHSTUB(kbd_read_keys_r2                       ,0xff05e000) //109
NHSTUB(lseek                                  ,0xff01cd80) //120
NHSTUB(malloc                                 ,0xff002eb4) //112
NHSTUB(memcmp                                 ,0xff00b5a4) //120
NHSTUB(memcpy                                 ,0xff02297c) //120
NHSTUB(memset                                 ,0xff2a7c84) //120
NHSTUB(mkdir                                  ,0xff01d000) //121
NHSTUB(mktime_ext                             ,0xff0b0ac0) //  1
NHSTUB(open                                   ,0xff005ae8) //109
NHSTUB(OpenFastDir                            ,0xff368e4c) //115
NHSTUB(closedir                               ,0xff368dfc) //121
NHSTUB(qsort                                  ,0xff3f68d8) //  6
NHSTUB(rand                                   ,0xff2a7c54) //121
NHSTUB(realloc                                ,0xff2a7d00) //115
NHSTUB(reboot_fw_update                       ,0xff3909c4) //106
NHSTUB(set_control_event                      ,0xff09d474) //111
NHSTUB(srand                                  ,0xff2a7c48) //122
NHSTUB(stat                                   ,0xff01cdc8) //109
NHSTUB(strcat                                 ,0xff0b115c) //  1
NHSTUB(strchr                                 ,0xff002d80) //  1
NHSTUB(strcmp                                 ,0xff00b6a0) //120
NHSTUB(strcpy                                 ,0xff00b58c) //120
NHSTUB(strftime                               ,0xff0b0b0c) //113
NHSTUB(strlen                                 ,0xff002dcc) //120
NHSTUB(strncmp                                ,0xff002d34) //  1
NHSTUB(strncpy                                ,0xff002cf8) //  1
NHSTUB(strrchr                                ,0xff002da4) //  1
NHSTUB(strtol                                 ,0xff022968) //101
NHSTUB(strtolx                                ,0xff02276c) //109
   DEF(task_CaptSeq                           ,0xff085738) //120
   DEF(task_ExpDrv                            ,0xff0cb104) //120
   DEF(task_FileWrite                         ,0xff367dc4) //120
   DEF(task_InitFileModules                   ,0xff04a77c) //120
   DEF(task_MovieRecord                       ,0xff1df310) //120
   DEF(task_PhySw                             ,0xff019f10) //120
   DEF(task_RotaryEncoder                     ,0xff05ebb4) //120
   DEF(hook_CreateTask                        ,0x0068ab8c) //105
NHSTUB(time                                   ,0x0068f8c8) //  6
NHSTUB(vsprintf                               ,0xff00b43c) //115
NHSTUB(EngDrvRead                             ,0xff01b244) //102
