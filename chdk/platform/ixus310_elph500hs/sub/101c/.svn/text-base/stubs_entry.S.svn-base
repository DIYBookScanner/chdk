// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R47 (DRYOS version 2.3, release #0047)
//   Firmware Ver GM1.01C   // Found @ 0xff086dd8, "GM1.01C" @ 0xff086de5
//   Firmware build timestamp: Jul 28 2011 10:19:24
//   Canon PowerShot ELPH 500 HS

// Values for makefile.inc
//   PLATFORMOSVER = 47
//   PLATFORMID = 12837 (0x3225) // Found @ 0xfff40040
//   MAXRAMADDR = 0x07ffffff
//   MEMISOSTART = 0x0018b834
//   KEYSYS = d4c                // Found @ 0xffff3610
//   NEED_ENCODED_DISKBOOT = 6   // Found @ 0xffff3620
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff18ea74
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff18ea34

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff320acc -> ff4ce700
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00034d4c) // Found @0xff024e2c
DEF(physw_run                               ,0x00001c3c) // Found @0xff0249cc
DEF(physw_sleep_delay                       ,0x00001c44) // Found @0xff0249cc
DEF(levent_table                            ,0xff4214e0) // Found @0xff4214e0
DEF(FlashParamsTable                        ,0xff4ce940) // Found @0xff4ce940
DEF(movie_status                            ,0x000070dc) // Found @0xff17e974
DEF(video_compression_rate                  ,0x0000711c) // Found @0xff17f430
DEF(full_screen_refresh                     ,0x0000a424) // Found @0xff244a14
DEF(canon_menu_active                       ,0x000032f8) // Found @0xff0887f4
DEF(canon_shoot_menu_active                 ,0x000087c9) // Found @0xff1c867c
DEF(playrec_mode                            ,0x00003030) // Found @0xff07abf4
DEF(zoom_status                             ,0x0000e7c0) // Found @0xff324484
DEF(some_flag_for_af_scan                   ,0x000074e0) // Found @0xff183040
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfff4a30c) // Found @0xfff4a30c
DEF(zoom_busy                               ,0x00007000) // Found @0xff179af8
DEF(focus_busy                              ,0x00006e70) // Found @0xff173e9c
DEF(recreview_hold                          ,0x0000391c) // Found @0xff098530
// Palette colour tables  found @ 0xff46e160
DEF(palette_control                         ,0x0000a424) // Found @0xff244990
DEF(active_palette_buffer                   ,0x0000a42c) // Found @0xff244994
DEF(palette_buffer_ptr                      ,0x0000a430) // Found @0xff244e5c
DEF(palette_buffer                          ,0x000c7dec) // Found @0xff244e6c
// Offset from start of palette_buffer to color data = 8 (Found @0xff366f84)
DEF(bitmap_buffer                           ,0x0000a464) // Found @0xff249aec
DEF(active_bitmap_buffer                    ,0x0000a45c) // Found @0xff249af0
DEF(viewport_buffers                        ,0xff3d0428) // Found @0xff043404
DEF(active_viewport_buffer                  ,0x00002104) // Found @0xff043138
// Camera has 2 RAW buffers @ 0x413591f0 & 0x46000000
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xff3d1bd8) // Found @0xff3d1bd8
DEF(active_raw_buffer                       ,0x00002f8c) // Found @0xff0771a4

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff04f54c
//void *vid_get_viewport_fb()      { return (void*)0x405d7980; }             // Found @0xff38b5d8
DEF(viewport_fb_d                           ,0x00002d40) // Found 0x2ce8 (@0xff06a728) + 0x58 (@0xff06a760)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2ce8+0x58)); } // Found @0xff06a728 & 0xff06a760
DEF(jpeg_count_str                          ,0x000c75f4) // Found @0xff236e4c
//char *camera_jpeg_count_str()    { return (char*)0x000c75f4; }             // Found @0xff236e4c
//long hook_raw_size()             { return 0x0123eaf0; }                    // Found @0xff38eaec
//int get_flash_params_count(void) { return 0xa0; }                          // Found @0xff1b03a0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xff3d14a4, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xff3d14c4, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_ZOOM_IN         ,0x00001000 }, // Found @0xff3d145c, levent 0x02
//    { 1, KEY_ZOOM_OUT        ,0x00008000 }, // Found @0xff3d1464, levent 0x03
//    { 2, KEY_SHOOT_FULL      ,0x00000a00 }, // Found @0xff3d147c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000800 }, // Found @0xff3d147c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000200 }, // Found @0xff3d1474, levent 0x00
//    { 2, KEY_POWER           ,0x00001000 }, // Found @0xff3d1484, levent 0x600
//    { 2, KEY_PLAYBACK        ,0x00004000 }, // Found @0xff3d148c, levent 0x601
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4168 // Found @0xff14a154
//#define CAM_RAW_ROWS      3060 // Found @0xff14a160
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02b914

// Misc stuff
DEF(ctypes, 0xff3cea36)

// For capt_seq.c
DEF(_nrflag,0x751c) // Found @ ff1878c8 (0x7514) & ff187904 (+0x08)
//static long *nrflag = (long*)(0x7514+0x08);  // Found @ ff1878c8 & ff187904
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff02b8cc) //112
NHSTUB(Close                                  ,0xff027690) //120
NHSTUB(CreateTask                             ,0xff00e9b0) //120
NHSTUB(DebugAssert                            ,0xff00ec88) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff02708c) //116
NHSTUB(DeleteFile_Fut                         ,0xff026fa8) //112
NHSTUB(DoAELock                               ,0xff0291d0) //120
NHSTUB(DoAFLock                               ,0xff028edc) //120
NHSTUB(EnterToCompensationEVF                 ,0xff029138) //104
NHSTUB(ExecuteEventProcedure                  ,0xff083fe0) //104
NHSTUB(ExitFromCompensationEVF                ,0xff02917c) //104
NHSTUB(ExitTask                               ,0xff00ec40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff037f50) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff038028) //104
NHSTUB(Fclose_Fut                             ,0xff027124) //120
NHSTUB(Feof_Fut                               ,0xff027310) //  1
NHSTUB(Fflush_Fut                             ,0xff02734c) //  1
NHSTUB(Fgets_Fut                              ,0xff027278) //  6
NHSTUB(Fopen_Fut                              ,0xff0270e4) //120
NHSTUB(Fread_Fut                              ,0xff0271d0) //120
NHSTUB(FreeUncacheableMemory                  ,0xff02b90c) //112
NHSTUB(Fseek_Fut                              ,0xff0272c4) //120
NHSTUB(Fwrite_Fut                             ,0xff027224) //120
NHSTUB(GetBatteryTemperature                  ,0xff0597d4) //102
NHSTUB(GetCCDTemperature                      ,0xff059760) //102
NHSTUB(GetCurrentAvValue                      ,0xff17678c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff0680d8) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff068130) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff068108) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff174b20) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff174f80) //  3
NHSTUB(GetImageFolder                         ,0xff1510ec) //122
NHSTUB(GetKbdState                            ,0xff0560b4) //109
NHSTUB(GetMemInfo                             ,0xff00a29c) //115
NHSTUB(GetOpticalTemperature                  ,0xff059848) //120
NHSTUB(GetParameterData                       ,0xff1b0360) //101
NHSTUB(GetPropertyCase                        ,0xff087d48) //102
NHSTUB(GetSystemTime                          ,0xff30fb3c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff045a10) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff045a1c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff179f70) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff2f9ac8) //102
NHSTUB(GiveSemaphore                          ,0xff02b2c4) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0dabe0) //102
NHSTUB(LEDDrive                               ,0xff0555f8) //120
NHSTUB(LocalTime                              ,0xff081870) //115
NHSTUB(LockMainPower                          ,0xff08d454) //120
NHSTUB(MakeDirectory_Fut                      ,0xff02701c) //116
NHSTUB(MakeSDCardBootable                     ,0xff068368) //105
NHSTUB(MoveFocusLensToDistance                ,0xff3878d4) //102
NHSTUB(MoveIrisWithAv                         ,0xff30bc30) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff30c4fc) //120
NHSTUB(Open                                   ,0xff0275c8) //120
NHSTUB(PB2Rec                                 ,0xff090114) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff072364) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff07233c) //120
NHSTUB(PT_PlaySound                           ,0xff07cc4c) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff08cbfc) //120
NHSTUB(PostLogicalEventToUI                   ,0xff08cc48) //120
NHSTUB(PutInNdFilter                          ,0xff30c344) //102
NHSTUB(PutOutNdFilter                         ,0xff30c368) //102
NHSTUB(Read                                   ,0xff00ad58) //120
NHSTUB(ReadFastDir                            ,0xff2e4530) //  6
NHSTUB(Rec2PB                                 ,0xff090154) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0a3f10) //104
NHSTUB(RenameFile_Fut                         ,0xff026f14) //116
NHSTUB(Restart                                ,0xff02d0e0) //106
NHSTUB(ScreenLock                             ,0xff0a5108) //117
NHSTUB(ScreenUnlock                           ,0xff0a516c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff38a750) //102
NHSTUB(SetAutoShutdownTime                    ,0xff08d4c8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff095608) //120
NHSTUB(SetFileAttributes                      ,0xff027a94) //  6
NHSTUB(SetFileTimeStamp                       ,0xff027a1c) //  6
NHSTUB(SetLogicalEventActive                  ,0xff08d1bc) //101
NHSTUB(SetParameterData                       ,0xff1b02d0) //101
NHSTUB(SetPropertyCase                        ,0xff087c2c) //102
NHSTUB(SetScriptMode                          ,0xff08d20c) //120
NHSTUB(SleepTask                              ,0xff02b570) //120
NHSTUB(TakeSemaphore                          ,0xff02b1f4) //120
NHSTUB(TurnOffBackLight                       ,0xff09b938) //104
NHSTUB(TurnOnBackLight                        ,0xff09b920) //104
NHSTUB(TurnOnDisplay                          ,0xff04f9f8) //120
NHSTUB(TurnOffDisplay                         ,0xff04fa08) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff19e09c) //120
NHSTUB(UnlockAE                               ,0xff0291f4) //120
NHSTUB(UnlockAF                               ,0xff028f14) //120
NHSTUB(UnlockMainPower                        ,0xff08d3a8) //120
NHSTUB(VbattGet                               ,0xff023004) //120
NHSTUB(Write                                  ,0xff0276e4) //120
NHSTUB(WriteSDCard                            ,0xff163f5c) //108
NHSTUB(_log                                   ,0xff3cb220) //111
NHSTUB(_log10                                 ,0xff3cb760) //112
NHSTUB(_pow                                   ,0xff3cb8d8) //121
NHSTUB(_sqrt                                  ,0xff3cd838) //  6
NHSTUB(add_ptp_handler                        ,0xff28ee4c) //121
NHSTUB(apex2us                                ,0xff24e4e4) //121
NHSTUB(close                                  ,0xff00abb4) //109
NHSTUB(err_init_task                          ,0xff005fd4) //111
NHSTUB(exmem_alloc                            ,0xff082838) //101
NHSTUB(exmem_free                             ,0xff0828b0) //101
NHSTUB(free                                   ,0xff004244) //112
NHSTUB(kbd_p1_f                               ,0xff024ea8) //109
NHSTUB(kbd_p1_f_cont                          ,0xff024eb4) //109
NHSTUB(kbd_p2_f                               ,0xff02469c) //109
NHSTUB(kbd_read_keys                          ,0xff024e2c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff055ad0) //109
NHSTUB(lseek                                  ,0xff0278ac) //120
NHSTUB(malloc                                 ,0xff0041ec) //112
NHSTUB(memcmp                                 ,0xff0108e8) //120
NHSTUB(memcpy                                 ,0xff030fbc) //120
NHSTUB(memset                                 ,0xff24cfd8) //120
NHSTUB(mkdir                                  ,0xff027b2c) //109
NHSTUB(mktime_ext                             ,0xff0a5f80) //  1
NHSTUB(open                                   ,0xff00ab04) //109
NHSTUB(OpenFastDir                            ,0xff2e43dc) //  6
NHSTUB(closedir                               ,0xff2e438c) //121
NHSTUB(qsort                                  ,0xff24d5e0) //  6
NHSTUB(rand                                   ,0xff24d118) //121
NHSTUB(realloc                                ,0xff24d054) //115
NHSTUB(reboot_fw_update                       ,0xff2e99cc) //106
NHSTUB(set_control_event                      ,0xff08ce6c) //111
NHSTUB(srand                                  ,0xff24d10c) //122
NHSTUB(stat                                   ,0xff0278f4) //109
NHSTUB(strcat                                 ,0xff0a5738) //  1
NHSTUB(strchr                                 ,0xff0040b8) //  1
NHSTUB(strcmp                                 ,0xff0108a4) //120
NHSTUB(strcpy                                 ,0xff01088c) //120
NHSTUB(strftime                               ,0xff0a5980) //113
NHSTUB(strlen                                 ,0xff004104) //120
NHSTUB(strncmp                                ,0xff00406c) //  1
NHSTUB(strncpy                                ,0xff004030) //  1
NHSTUB(strrchr                                ,0xff0040dc) //  1
NHSTUB(strtol                                 ,0xff0312bc) //101
NHSTUB(strtolx                                ,0xff0310c0) //109
   DEF(task_CaptSeq                           ,0xff074f1c) //120
   DEF(task_ExpDrv                            ,0xff0bdd18) //120
   DEF(task_FileWrite                         ,0xff2e250c) //120
   DEF(task_InitFileModules                   ,0xff090ab0) //120
   DEF(task_MovieRecord                       ,0xff17fc00) //120
   DEF(task_PhySw                             ,0xff0249c8) //120
   DEF(task_TouchPanel                        ,0xff059e84) //120
NHSTUB(time                                   ,0xff081e4c) //109
NHSTUB(vsprintf                               ,0xff01084c) //115
NHSTUB(EngDrvRead                             ,0xff025e34) //102
