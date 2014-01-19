// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.00E   // Found @ 0xff07a344, "GM1.00E" @ 0xff07a351
//   Firmware build timestamp: Mar 19 2012 09:56:16
//   Canon IXUS 125 HS

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12865 (0x3241) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x00180998
//   KEYSYS = d4c                // Found @ 0xffff3cbc
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff3ccc

// Note, ROM copied to RAM :- from 0xff63cdf8, to 0x00685000, len 15799 words.
//   ARAM_HEAP_START = 0x5ce000  // Found @ 0xff1a4988
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1a494c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DeleteFile_Fut                       ,0xff0208dc) //  1 90%        == 0xff0208dc
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff021480

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff333608 -> ff5e8cb8
// Mode 33326 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00037bdc) // Found @0xff01e84c
DEF(physw_run                               ,0x00001c20) // Found @0xff01e408
DEF(physw_sleep_delay                       ,0x00001c28) // Found @0xff01e408
DEF(levent_table                            ,0xff474db4) // Found @0xff474db4
DEF(FlashParamsTable                        ,0xff5e8f24) // Found @0xff5e8f24
DEF(movie_status                            ,0x0000a1c4) // Found @0xff191b24
DEF(video_compression_rate                  ,0x0000a204) // Found @0xff193518
DEF(full_screen_refresh                     ,0x0000d12c) // Found @0xff243100
DEF(canon_menu_active                       ,0x000031e0) // Found @0xff07be34
DEF(canon_shoot_menu_active                 ,0x0000ba51) // Found @0xff1e4f18
DEF(playrec_mode                            ,0x00002f34) // Found @0xff06fdfc
DEF(zoom_status                             ,0x000109c8) // Found @0xff336dac
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfff4a4c8) // Found @0xfff4a4c8
DEF(zoom_busy                               ,0x0000a05c) // Found @0xff18ca18
DEF(focus_busy                              ,0x00009ef0) // Found @0xff188164
DEF(recreview_hold                          ,0x000037fc) // Found @0xff08c128
// Palette colour tables  found @ 0xff490098
DEF(palette_control                         ,0x0000d12c) // Found @0xff24307c
DEF(active_palette_buffer                   ,0x0000d134) // Found @0xff243080
DEF(palette_buffer_ptr                      ,0x0000d138) // Found @0xff243538
DEF(palette_buffer                          ,0x000c78c8) // Found @0xff243548
// Offset from start of palette_buffer to color data = 4 (Found @0xff377c68)
DEF(bitmap_buffer                           ,0x0000d170) // Found @0xff246c7c
DEF(active_bitmap_buffer                    ,0x0000d168) // Found @0xff246c80
DEF(viewport_buffers                        ,0xff41327c) // Found @0xff03b2d0
DEF(active_viewport_buffer                  ,0x00002138) // Found @0xff03af6c
// Camera has 2 RAW buffers @ 0x44000000 & 0x4a7eca00
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff42793c) // Found @0xff42793c
DEF(active_raw_buffer                       ,0x00002eac) // Found @0xff06c918

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff0448b8
//void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xff3a831c
DEF(viewport_fb_d                           ,0x00002c2c) // Found 0x2bd8 (@0xff05e4c8) + 0x54 (@0xff05e500)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2bd8+0x54)); } // Found @0xff05e4c8 & 0xff05e500
DEF(jpeg_count_str                          ,0x000c7158) // Found @0xff2391e8
//char *camera_jpeg_count_str()    { return (char*)0x000c7158; }             // Found @0xff2391e8
//long hook_raw_size()             { return 0x0180fde0; }                    // Found @0xff3ab130
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff1cb504

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x02000000 // Found @0xff413814, levent 0x20a
//#define SD_READONLY_IDX     1
//#define USB_MASK            0x40000000 // Found @0xff41384c, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_MENU            ,0x00000001 }, // Found @0xff413794, levent 0x09
//    { 0, KEY_SET             ,0x00000002 }, // Found @0xff41379c, levent 0x08
//    { 0, KEY_ZOOM_OUT        ,0x00000004 }, // Found @0xff4137a4, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00000008 }, // Found @0xff4137ac, levent 0x02
//    { 0, KEY_VIDEO           ,0x00000040 }, // Found @0xff4137bc, levent 0x1a
//    { 0, KEY_UP              ,0x00000100 }, // Found @0xff4137c4, levent 0x04
//    { 0, KEY_RIGHT           ,0x00000200 }, // Found @0xff4137cc, levent 0x07
//    { 0, KEY_LEFT            ,0x00000400 }, // Found @0xff4137d4, levent 0x06
//    { 0, KEY_DOWN            ,0x00000800 }, // Found @0xff4137dc, levent 0x05
//    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xff4137f4, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xff4137f4, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xff4137ec, levent 0x00
//    { 1, KEY_POWER           ,0x00400000 }, // Found @0xff4137fc, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x00800000 }, // Found @0xff413804, levent 0x101
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4784 // Found @0xff15d368
//#define CAM_RAW_ROWS      3516 // Found @0xff15d374
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff024684

// Misc stuff
DEF(ctypes, 0xff4126f8)

// For capt_seq.c
DEF(_nrflag,0xd22c) // Found @ ff24fac0 (0xd22c) & ff24fafc (+0x00)
//static long *nrflag = (long*)(0xd22c+0x00);  // Found @ ff24fac0 & ff24fafc
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff02463c) //112
NHSTUB(Close                                  ,0xff020f50) //120
NHSTUB(CreateTask                             ,0x0068ab00) //120
NHSTUB(DebugAssert                            ,0x0068afd8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff020950) //116
NHSTUB(DoAELock                               ,0xff022ce4) //120
NHSTUB(DoAFLock                               ,0xff0229e8) //120
NHSTUB(EnterToCompensationEVF                 ,0xff022c4c) //104
NHSTUB(ExecuteEventProcedure                  ,0xff077304) //104
NHSTUB(ExitFromCompensationEVF                ,0xff022c90) //104
NHSTUB(ExitTask                               ,0x0068ad90) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff02e398) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff02e4e8) //104
NHSTUB(Fclose_Fut                             ,0xff0209e8) //120
NHSTUB(Feof_Fut                               ,0xff020bd4) //  1
NHSTUB(Fflush_Fut                             ,0xff020c10) //  1
NHSTUB(Fgets_Fut                              ,0xff020b3c) //  6
NHSTUB(Fopen_Fut                              ,0xff0209a8) //120
NHSTUB(Fread_Fut                              ,0xff020a94) //120
NHSTUB(FreeUncacheableMemory                  ,0xff02467c) //112
NHSTUB(Fseek_Fut                              ,0xff020b88) //120
NHSTUB(Fwrite_Fut                             ,0xff020ae8) //120
NHSTUB(GetBatteryTemperature                  ,0xff04d97c) //102
NHSTUB(GetCCDTemperature                      ,0xff04d908) //102
NHSTUB(GetCurrentAvValue                      ,0xff189d14) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff05c09c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff05c0f4) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff05c0cc) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff188f24) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff189374) //  3
NHSTUB(GetImageFolder                         ,0xff166a24) //122
NHSTUB(GetKbdState                            ,0xff04a378) //109
NHSTUB(GetMemInfo                             ,0xff0052d0) //115
NHSTUB(GetOpticalTemperature                  ,0xff04d9f0) //120
NHSTUB(GetParameterData                       ,0xff1cb4c4) //101
NHSTUB(GetPropertyCase                        ,0xff07b378) //102
NHSTUB(GetSystemTime                          ,0xff321fb4) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff03d5a0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff03d5ac) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff18ce90) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff30f83c) //102
NHSTUB(GiveSemaphore                          ,0x0068aa60) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0d4ca0) //102
NHSTUB(LEDDrive                               ,0xff195280) //120
NHSTUB(LocalTime                              ,0x0068f2f4) //115
NHSTUB(LockMainPower                          ,0xff0807a8) //120
NHSTUB(MakeSDCardBootable                     ,0xff05c374) //105
NHSTUB(MoveFocusLensToDistance                ,0xff3a43c0) //102
NHSTUB(MoveIrisWithAv                         ,0xff31e97c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff31f0b0) //120
NHSTUB(Open                                   ,0xff020e88) //120
NHSTUB(PB2Rec                                 ,0xff0837e0) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff0659b0) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff065988) //120
NHSTUB(PT_PlaySound                           ,0xff071d64) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff07fe9c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff07fee8) //120
NHSTUB(PutInNdFilter                          ,0xff31ee88) //102
NHSTUB(PutOutNdFilter                         ,0xff31eeac) //102
NHSTUB(Read                                   ,0xff005d8c) //120
NHSTUB(ReadFastDir                            ,0xff2fcba8) //115
NHSTUB(Rec2PB                                 ,0xff083820) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff098024) //104
NHSTUB(RenameFile_Fut                         ,0xff020848) //116
NHSTUB(Restart                                ,0xff025e54) //106
NHSTUB(ScreenLock                             ,0xff099004) //117
NHSTUB(ScreenUnlock                           ,0xff099068) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff3a7494) //102
NHSTUB(SetAutoShutdownTime                    ,0xff08081c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0872d8) //120
NHSTUB(SetFileAttributes                      ,0xff0213e8) //  6
NHSTUB(SetFileTimeStamp                       ,0xff021370) //  6
NHSTUB(SetLogicalEventActive                  ,0xff080524) //101
NHSTUB(SetParameterData                       ,0xff1cb434) //101
NHSTUB(SetPropertyCase                        ,0xff07b1f0) //102
NHSTUB(SetScriptMode                          ,0xff080574) //120
NHSTUB(SleepTask                              ,0x0068c2e8) //120
NHSTUB(TakeSemaphore                          ,0x0068a990) //120
NHSTUB(TurnOffBackLight                       ,0xff090158) //104
NHSTUB(TurnOnBackLight                        ,0xff090140) //104
NHSTUB(TurnOnDisplay                          ,0xff044ccc) //120
NHSTUB(TurnOffDisplay                         ,0xff044cdc) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1b06e8) //120
NHSTUB(UnlockAE                               ,0xff022d08) //120
NHSTUB(UnlockAF                               ,0xff022a20) //120
NHSTUB(UnlockMainPower                        ,0xff0806fc) //120
NHSTUB(VbattGet                               ,0xff01d094) //120
NHSTUB(Write                                  ,0xff020fa4) //120
NHSTUB(WriteSDCard                            ,0xff17b5a4) //108
NHSTUB(_log                                   ,0x00690ce0) //111
NHSTUB(_log10                                 ,0x00691220) //112
NHSTUB(_pow                                   ,0x00691398) //121
NHSTUB(_sqrt                                  ,0x00693038) //  6
NHSTUB(add_ptp_handler                        ,0xff299ffc) //121
NHSTUB(apex2us                                ,0xff2498dc) //121
NHSTUB(close                                  ,0xff005be8) //109
NHSTUB(err_init_task                          ,0xff004378) //111
NHSTUB(exmem_alloc                            ,0xff075cd8) //101
NHSTUB(exmem_free                             ,0xff075d50) //101
NHSTUB(free                                   ,0xff002f74) //112
NHSTUB(kbd_p1_f                               ,0xff01e89c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff01e8a8) //109
NHSTUB(kbd_p2_f                               ,0xff01e0a0) //109
NHSTUB(kbd_read_keys                          ,0xff01e84c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff049d58) //109
NHSTUB(lseek                                  ,0xff0211cc) //120
NHSTUB(malloc                                 ,0xff002f1c) //112
NHSTUB(memcmp                                 ,0xff00b940) //120
NHSTUB(memcpy                                 ,0xff0276e4) //120
NHSTUB(memset                                 ,0xff247a04) //120
NHSTUB(mkdir                                  ,0xff021480) //121
NHSTUB(mktime_ext                             ,0xff099564) //  1
NHSTUB(open                                   ,0xff005b38) //109
NHSTUB(OpenFastDir                            ,0xff2fca44) //115
NHSTUB(closedir                               ,0xff2fc9f4) //121
NHSTUB(qsort                                  ,0xff2479a4) //  6
NHSTUB(rand                                   ,0xff2474dc) //121
NHSTUB(realloc                                ,0xff247a80) //115
NHSTUB(reboot_fw_update                       ,0xff30228c) //106
NHSTUB(set_control_event                      ,0xff0801e4) //111
NHSTUB(srand                                  ,0xff2474d0) //122
NHSTUB(stat                                   ,0xff021214) //109
NHSTUB(strcat                                 ,0xff099be4) //  1
NHSTUB(strchr                                 ,0xff002de8) //  1
NHSTUB(strcmp                                 ,0xff00ba3c) //120
NHSTUB(strcpy                                 ,0xff00b928) //120
NHSTUB(strftime                               ,0xff0995b0) //113
NHSTUB(strlen                                 ,0xff002e34) //120
NHSTUB(strncmp                                ,0xff002d9c) //  1
NHSTUB(strncpy                                ,0xff002d60) //  1
NHSTUB(strrchr                                ,0xff002e0c) //  1
NHSTUB(strtol                                 ,0xff0276d0) //101
NHSTUB(strtolx                                ,0xff0274d4) //109
   DEF(task_CaptSeq                           ,0xff068e64) //120
   DEF(task_ExpDrv                            ,0xff0b2aa8) //120
   DEF(task_FileWrite                         ,0xff2fb3fc) //120
   DEF(task_InitFileModules                   ,0xff084030) //120
   DEF(task_MovieRecord                       ,0xff193d4c) //120
   DEF(task_PhySw                             ,0xff01e404) //120
NHSTUB(time                                   ,0x0068f8d0) //  6
NHSTUB(vsprintf                               ,0xff00b7d8) //115
NHSTUB(EngDrvRead                             ,0xff01f6d8) //102
