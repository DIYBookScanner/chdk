// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.01A   // Found @ 0xff0b56fc, "GM1.01A" @ 0xff0b5709
//   Firmware build timestamp: Apr 10 2012 14:00:03
//   Canon PowerShot ELPH 320 HS

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12864 (0x3240) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x00281d28
//   KEYSYS = d4c                // Found @ 0xffff3cf4
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff3d04

// Note, ROM copied to RAM :- from 0xff887958, to 0x00685000, len 47143 words.
//   ARAM_HEAP_START = 0x5ce000  // Found @ 0xff223cbc
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff223c80

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff027bbc) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff0286cc

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff403bb4 -> ff826638
// Mode 33324 in firmware but not in current modemap
// Mode 33326 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0003e8fc) // Found @0xff025a8c
DEF(physw_run                               ,0x00001d34) // Found @0xff025648
DEF(physw_sleep_delay                       ,0x00001d3c) // Found @0xff025648
DEF(levent_table                            ,0xff614488) // Found @0xff614488
DEF(FlashParamsTable                        ,0xff8268a0) // Found @0xff8268a0
DEF(movie_status                            ,0x0000aca4) // Found @0xff1e7ec8
DEF(video_compression_rate                  ,0x0000ace4) // Found @0xff1e98bc
DEF(full_screen_refresh                     ,0x0000ea2c) // Found @0xff2dd970
DEF(canon_menu_active                       ,0x000038fc) // Found @0xff0b71e8
DEF(canon_shoot_menu_active                 ,0x0000ceb1) // Found @0xff2693c8
DEF(playrec_mode                            ,0x00003644) // Found @0xff0aa1fc
DEF(zoom_status                             ,0x00012f20) // Found @0xff407644
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfff4a4c8) // Found @0xfff4a4c8
DEF(zoom_busy                               ,0x0000ab3c) // Found @0xff1e2e34
DEF(focus_busy                              ,0x0000a9d0) // Found @0xff1de580
DEF(recreview_hold                          ,0x00003f30) // Found @0xff0c7b14
// Palette colour tables  found @ 0xff65ec0c
DEF(palette_control                         ,0x0000ea2c) // Found @0xff2dd8ec
DEF(active_palette_buffer                   ,0x0000ea34) // Found @0xff2dd8f0
DEF(palette_buffer_ptr                      ,0x0000ea38) // Found @0xff2ddda8
DEF(palette_buffer                          ,0x00194b88) // Found @0xff2dddb8
// Offset from start of palette_buffer to color data = 4 (Found @0xff45465c)
DEF(bitmap_buffer                           ,0x0000ea70) // Found @0xff2e272c
DEF(active_bitmap_buffer                    ,0x0000ea68) // Found @0xff2e2730
DEF(viewport_buffers                        ,0xff5abae4) // Found @0xff053f60
DEF(active_viewport_buffer                  ,0x000023e8) // Found @0xff053bfc
// Camera has 2 RAW buffers @ 0x44000000 & 0x4a7eca00
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff5c05c0) // Found @0xff5c05c0
DEF(active_raw_buffer                       ,0x000035bc) // Found @0xff0a6bf0

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff05f184
//void *vid_get_viewport_fb()      { return (void*)0x4082b980; }             // Found @0xff489540
DEF(viewport_fb_d                           ,0x00002fcc) // Found 0x2f78 (@0xff07ac88) + 0x54 (@0xff07acc0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2f78+0x54)); } // Found @0xff07ac88 & 0xff07acc0
DEF(jpeg_count_str                          ,0x00194220) // Found @0xff2cf054
//char *camera_jpeg_count_str()    { return (char*)0x00194220; }             // Found @0xff2cf054
//long hook_raw_size()             { return 0x0180fde0; }                    // Found @0xff48c354
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff24dffc

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00008000 // Found @0xff5ac2d8, levent 0x20a
//#define SD_READONLY_IDX     0
//#define USB_MASK            0x40000000 // Found @0xff5ac358, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00800000 }, // Found @0xff5ac2f0, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x01000000 }, // Found @0xff5ac2f8, levent 0x101
//    { 1, KEY_SHOOT_FULL      ,0x06000000 }, // Found @0xff5ac308, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x04000000 }, // Found @0xff5ac308, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x02000000 }, // Found @0xff5ac300, levent 0x00
//    { 1, KEY_ZOOM_OUT        ,0x08000000 }, // Found @0xff5ac310, levent 0x03
//    { 1, KEY_ZOOM_IN         ,0x20000000 }, // Found @0xff5ac318, levent 0x02
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4784 // Found @0xff1b1290
//#define CAM_RAW_ROWS      3516 // Found @0xff1b129c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff03b324

// Misc stuff
DEF(ctypes, 0xff5a9f14)

// For capt_seq.c
DEF(_nrflag,0xebc4) // Found @ ff2ebfe0 (0xebc4) & ff2ec01c (+0x00)
//static long *nrflag = (long*)(0xebc4+0x00);  // Found @ ff2ebfe0 & ff2ec01c
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff03b2dc) //112
NHSTUB(Close                                  ,0xff028230) //120
NHSTUB(CreateTask                             ,0x0068ab00) //120
NHSTUB(DebugAssert                            ,0x0068afd8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff027c30) //116
NHSTUB(DoAELock                               ,0xff039a58) //120
NHSTUB(DoAFLock                               ,0xff0397a4) //120
NHSTUB(EnterToCompensationEVF                 ,0xff0399c0) //104
NHSTUB(ExecuteEventProcedure                  ,0xff0b26bc) //104
NHSTUB(ExitFromCompensationEVF                ,0xff039a04) //104
NHSTUB(ExitTask                               ,0x0068ad90) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff047084) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff0471d4) //104
NHSTUB(Fclose_Fut                             ,0xff027cc8) //120
NHSTUB(Feof_Fut                               ,0xff027eb4) //  1
NHSTUB(Fflush_Fut                             ,0xff027ef0) //  1
NHSTUB(Fgets_Fut                              ,0xff027e1c) //  6
NHSTUB(Fopen_Fut                              ,0xff027c88) //120
NHSTUB(Fread_Fut                              ,0xff027d74) //120
NHSTUB(FreeUncacheableMemory                  ,0xff03b31c) //112
NHSTUB(Fseek_Fut                              ,0xff027e68) //120
NHSTUB(Fwrite_Fut                             ,0xff027dc8) //120
NHSTUB(GetBatteryTemperature                  ,0xff0697cc) //102
NHSTUB(GetCCDTemperature                      ,0xff069758) //102
NHSTUB(GetCurrentAvValue                      ,0xff1e0130) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff0787c8) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff078820) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff0787f8) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1df340) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1df790) //  3
NHSTUB(GetImageFolder                         ,0xff1baa08) //122
NHSTUB(GetKbdState                            ,0xff065dcc) //109
NHSTUB(GetMemInfo                             ,0xff0053d8) //115
NHSTUB(GetOpticalTemperature                  ,0xff069840) //120
NHSTUB(GetParameterData                       ,0xff24dfbc) //101
NHSTUB(GetPropertyCase                        ,0xff0b6730) //102
NHSTUB(GetSystemTime                          ,0xff3e7d6c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff056198) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff0561a4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1e32ac) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff3b6694) //102
NHSTUB(GiveSemaphore                          ,0x0068aa60) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff1129b8) //102
NHSTUB(LEDDrive                               ,0xff2143cc) //120
NHSTUB(LocalTime                              ,0x006992d0) //115
NHSTUB(LockMainPower                          ,0xff0bc244) //120
NHSTUB(MakeSDCardBootable                     ,0xff078a58) //105
NHSTUB(MoveFocusLensToDistance                ,0xff485598) //102
NHSTUB(MoveIrisWithAv                         ,0xff3e4800) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff3e4f34) //120
NHSTUB(Open                                   ,0xff028168) //120
NHSTUB(PB2Rec                                 ,0xff0bf084) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff09fd10) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff09fce8) //120
NHSTUB(PT_PlaySound                           ,0xff0ac158) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff0bb898) //120
NHSTUB(PostLogicalEventToUI                   ,0xff0bb8e4) //120
NHSTUB(PutInNdFilter                          ,0xff3e4d0c) //102
NHSTUB(PutOutNdFilter                         ,0xff3e4d30) //102
NHSTUB(Read                                   ,0xff005e94) //120
NHSTUB(ReadFastDir                            ,0xff3a274c) //115
NHSTUB(Rec2PB                                 ,0xff0bf0c4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0d321c) //104
NHSTUB(RenameFile_Fut                         ,0xff027b28) //116
NHSTUB(Restart                                ,0xff03cb00) //106
NHSTUB(ScreenLock                             ,0xff0d41fc) //117
NHSTUB(ScreenUnlock                           ,0xff0d4260) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff4886b8) //102
NHSTUB(SetAutoShutdownTime                    ,0xff0bc2b8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0c2ef0) //120
NHSTUB(SetFileAttributes                      ,0xff028634) //  6
NHSTUB(SetFileTimeStamp                       ,0xff0285bc) //  6
NHSTUB(SetLogicalEventActive                  ,0xff0bbfb0) //101
NHSTUB(SetParameterData                       ,0xff24df2c) //101
NHSTUB(SetPropertyCase                        ,0xff0b65a8) //102
NHSTUB(SetScriptMode                          ,0xff0bc040) //120
NHSTUB(SleepTask                              ,0x0068f670) //120
NHSTUB(TakeSemaphore                          ,0x0068a990) //120
NHSTUB(TurnOffBackLight                       ,0xff0caf40) //104
NHSTUB(TurnOnBackLight                        ,0xff0caf28) //104
NHSTUB(TurnOnDisplay                          ,0xff05f5e4) //120
NHSTUB(TurnOffDisplay                         ,0xff05f5f4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff231a2c) //120
NHSTUB(UnlockAE                               ,0xff039a7c) //120
NHSTUB(UnlockAF                               ,0xff0397dc) //120
NHSTUB(UnlockMainPower                        ,0xff0bc198) //120
NHSTUB(VbattGet                               ,0xff024258) //120
NHSTUB(Write                                  ,0xff028284) //120
NHSTUB(WriteSDCard                            ,0xff1d1a8c) //108
NHSTUB(_log                                   ,0x006ae618) //111
NHSTUB(_log10                                 ,0x006aeb58) //112
NHSTUB(_pow                                   ,0x006aecd0) //121
NHSTUB(_sqrt                                  ,0x006b0da8) //  6
// ALT: NHSTUB(_sqrt, 0xffdb43a8) // 6 27/0
NHSTUB(add_ptp_handler                        ,0xff1487c8) //121
NHSTUB(apex2us                                ,0xff2e5dec) //121
NHSTUB(close                                  ,0xff005cf0) //109
NHSTUB(err_init_task                          ,0xff00442c) //111
NHSTUB(exmem_alloc                            ,0xff0b1090) //101
NHSTUB(exmem_free                             ,0xff0b1108) //101
NHSTUB(free                                   ,0xff002fcc) //112
NHSTUB(kbd_p1_f                               ,0xff025adc) //109
NHSTUB(kbd_p1_f_cont                          ,0xff025ae8) //109
NHSTUB(kbd_p2_f                               ,0xff0252e0) //109
NHSTUB(kbd_read_keys                          ,0xff025a8c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff0657e0) //109
NHSTUB(lseek                                  ,0xff02844c) //120
NHSTUB(malloc                                 ,0xff002f74) //112
NHSTUB(memcmp                                 ,0xff00d820) //120
NHSTUB(memcpy                                 ,0xff03eb28) //120
NHSTUB(memset                                 ,0xff0d5184) //120
NHSTUB(mkdir                                  ,0xff0286cc) //121
NHSTUB(mktime_ext                             ,0xff0d475c) //  1
NHSTUB(open                                   ,0xff005c40) //109
NHSTUB(OpenFastDir                            ,0xff3a25f8) //115
NHSTUB(closedir                               ,0xff3a25a8) //121
NHSTUB(qsort                                  ,0xff2e34cc) //  6
NHSTUB(rand                                   ,0xff03eaf8) //121
NHSTUB(realloc                                ,0xff2e352c) //115
NHSTUB(reboot_fw_update                       ,0xff3a7d44) //106
NHSTUB(set_control_event                      ,0xff0bbc0c) //111
NHSTUB(srand                                  ,0xff03eaec) //122
NHSTUB(stat                                   ,0xff028494) //109
NHSTUB(strcat                                 ,0xff0d50b8) //  1
NHSTUB(strchr                                 ,0xff002e40) //  1
NHSTUB(strcmp                                 ,0xff00d91c) //120
NHSTUB(strcpy                                 ,0xff00d808) //120
NHSTUB(strftime                               ,0xff0d47a8) //113
NHSTUB(strlen                                 ,0xff002e8c) //120
NHSTUB(strncmp                                ,0xff002df4) //  1
NHSTUB(strncpy                                ,0xff002db8) //  1
NHSTUB(strrchr                                ,0xff002e64) //  1
NHSTUB(strtol                                 ,0xff03ead8) //101
NHSTUB(strtolx                                ,0xff03e8dc) //109
   DEF(task_CaptSeq                           ,0xff0a2ff4) //120
   DEF(task_ExpDrv                            ,0xff0f05bc) //120
   DEF(task_FileWrite                         ,0xff3a0fac) //120
   DEF(task_InitFileModules                   ,0xff0bf930) //120
   DEF(task_MovieRecord                       ,0xff1ea0f0) //120
   DEF(task_PhySw                             ,0xff025644) //120
   DEF(task_TouchPanel                        ,0xff069ff8) //120
NHSTUB(time                                   ,0x006998ac) //  6
NHSTUB(vsprintf                               ,0xff00d6b8) //115
NHSTUB(EngDrvRead                             ,0xff0269b8) //102
