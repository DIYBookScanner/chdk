// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R47 (DRYOS version 2.3, release #0047)
//   Firmware Ver GM1.00C   // Found @ 0xff894ef0, "GM1.00C" @ 0xff894efd
//   Firmware build timestamp: Dec 13 2010 11:33:27
//   Canon IXUS 220 HS

// Values for makefile.inc
//   PLATFORMOSVER = 47
//   PLATFORMID = 12841 (0x3229) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x07ffffff
//   MEMISOSTART = 0x001774ec
//   KEYSYS = d4c                // Found @ 0xffff3620
//   NEED_ENCODED_DISKBOOT = 6   // Found @ 0xffff3630
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff994958
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff994918

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffb041e4 -> ffc4ee40
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0003418c) // Found @0xff834e18
DEF(physw_run                               ,0x00001c3c) // Found @0xff8349bc
DEF(physw_sleep_delay                       ,0x00001c44) // Found @0xff8349bc
DEF(levent_table                            ,0xffbeb208) // Found @0xffbeb208
DEF(FlashParamsTable                        ,0xffc4f080) // Found @0xffc4f080
DEF(movie_status                            ,0x00006dcc) // Found @0xff984bd0
DEF(video_compression_rate                  ,0x00006e0c) // Found @0xff98568c
DEF(full_screen_refresh                     ,0x00009d00) // Found @0xffa32dfc
DEF(canon_menu_active                       ,0x00003210) // Found @0xff896910
DEF(canon_shoot_menu_active                 ,0x000083d9) // Found @0xff9c8c1c
DEF(playrec_mode                            ,0x00002f38) // Found @0xff888774
DEF(zoom_status                             ,0x0000ded8) // Found @0xffb078a0
DEF(some_flag_for_af_scan                   ,0x000071cc) // Found @0xff989240
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfffea288) // Found @0xfffea288
DEF(zoom_busy                               ,0x00006cf4) // Found @0xff97fd74
DEF(focus_busy                              ,0x00006b68) // Found @0xff97af60
DEF(recreview_hold                          ,0x00003828) // Found @0xff8a6510
// Palette colour tables  found @ 0xffc07ea4
DEF(palette_control                         ,0x00009d00) // Found @0xffa32d78
DEF(active_palette_buffer                   ,0x00009d08) // Found @0xffa32d7c
DEF(palette_buffer_ptr                      ,0x00009d0c) // Found @0xffa33244
DEF(palette_buffer                          ,0x000bb254) // Found @0xffa33254
// Offset from start of palette_buffer to color data = 8 (Found @0xffb3a9d8)
DEF(bitmap_buffer                           ,0x00009d40) // Found @0xffa36ca0
DEF(active_bitmap_buffer                    ,0x00009d38) // Found @0xffa36ca4
DEF(viewport_buffers                        ,0xffba1bc4) // Found @0xff853d4c
DEF(active_viewport_buffer                  ,0x00002168) // Found @0xff853a20
// Camera has 2 RAW buffers @ 0x413391a0 & 0x46000000
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffba3140) // Found @0xffba3140
DEF(active_raw_buffer                       ,0x00002e94) // Found @0xff884c64

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff85fd1c
//void *vid_get_viewport_fb()      { return (void*)0x405c6b80; }             // Found @0xffb5e11c
DEF(viewport_fb_d                           ,0x00002c60) // Found 0x2c08 (@0xff878880) + 0x58 (@0xff8788b8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2c08+0x58)); } // Found @0xff878880 & 0xff8788b8
DEF(jpeg_count_str                          ,0x000babac) // Found @0xffa2a298
//char *camera_jpeg_count_str()    { return (char*)0x000babac; }             // Found @0xffa2a298
//long hook_raw_size()             { return 0x0123eaf0; }                    // Found @0xffb61614
//int get_flash_params_count(void) { return 0xa0; }                          // Found @0xff9b23d4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffba2bb8, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xffba2bd8, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_MENU            ,0x00000001 }, // Found @0xffba2b38, levent 0x09
//    { 2, KEY_SET             ,0x00000002 }, // Found @0xffba2b40, levent 0x08
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffba2b48, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffba2b50, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffba2b58, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffba2b60, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffba2b68, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffba2b70, levent 0x04
//    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffba2b80, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffba2b80, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffba2b78, levent 0x00
//    { 2, KEY_POWER           ,0x00000400 }, // Found @0xffba2b88, levent 0x600
//    { 2, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffba2b90, levent 0x601
//    { 2, KEY_VIDEO           ,0x00004000 }, // Found @0xffba2ba0, levent 0x12
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4168 // Found @0xff952bb4
//#define CAM_RAW_ROWS      3060 // Found @0xff952bc0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83c0f0

// Misc stuff
DEF(ctypes, 0xffba00ea)

// For capt_seq.c
DEF(_nrflag,0x7208) // Found @ ff98db88 (0x7200) & ff98dbc4 (+0x08)
//static long *nrflag = (long*)(0x7200+0x08);  // Found @ ff98db88 & ff98dbc4
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83c0a8) //112
NHSTUB(Close                                  ,0xff8383e8) //120
NHSTUB(CreateTask                             ,0xff81e9b0) //120
NHSTUB(DebugAssert                            ,0xff81ec88) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff837de4) //116
NHSTUB(DeleteFile_Fut                         ,0xff837d00) //112
NHSTUB(DoAELock                               ,0xff839f1c) //120
NHSTUB(DoAFLock                               ,0xff839c28) //120
NHSTUB(EnterToCompensationEVF                 ,0xff839e84) //104
NHSTUB(ExecuteEventProcedure                  ,0xff8920f8) //104
NHSTUB(ExitFromCompensationEVF                ,0xff839ec8) //104
NHSTUB(ExitTask                               ,0xff81ec40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff848730) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff848808) //104
NHSTUB(Fclose_Fut                             ,0xff837e7c) //120
NHSTUB(Feof_Fut                               ,0xff838068) //  1
NHSTUB(Fflush_Fut                             ,0xff8380a4) //  1
NHSTUB(Fgets_Fut                              ,0xff837fd0) //  6
NHSTUB(Fopen_Fut                              ,0xff837e3c) //120
NHSTUB(Fread_Fut                              ,0xff837f28) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83c0e8) //112
NHSTUB(Fseek_Fut                              ,0xff83801c) //120
NHSTUB(Fwrite_Fut                             ,0xff837f7c) //120
NHSTUB(GetBatteryTemperature                  ,0xff868d7c) //102
NHSTUB(GetCCDTemperature                      ,0xff868d08) //102
NHSTUB(GetCurrentAvValue                      ,0xff97cb48) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff87630c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff876364) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff87633c) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff97bbe4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff97c044) //  3
NHSTUB(GetImageFolder                         ,0xff959b4c) //122
NHSTUB(GetKbdState                            ,0xff865558) //109
NHSTUB(GetMemInfo                             ,0xff81a29c) //115
NHSTUB(GetOpticalTemperature                  ,0xff868df0) //120
NHSTUB(GetParameterData                       ,0xff9b2394) //101
NHSTUB(GetPropertyCase                        ,0xff895e60) //102
NHSTUB(GetSystemTime                          ,0xffaf2534) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff856300) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff85630c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff9801ec) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffadcc9c) //102
NHSTUB(GiveSemaphore                          ,0xff83baa0) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8e8b94) //102
NHSTUB(LEDDrive                               ,0xff864a7c) //120
NHSTUB(LocalTime                              ,0xff88f988) //115
NHSTUB(LockMainPower                          ,0xff89ad84) //120
NHSTUB(MakeDirectory_Fut                      ,0xff837d74) //116
NHSTUB(MakeSDCardBootable                     ,0xff87659c) //105
NHSTUB(MoveFocusLensToDistance                ,0xffb5a418) //102
NHSTUB(MoveIrisWithAv                         ,0xffaeecac) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffaef364) //120
NHSTUB(Open                                   ,0xff838320) //120
NHSTUB(PB2Rec                                 ,0xff89dd28) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff87fbcc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff87fba4) //120
NHSTUB(PT_PlaySound                           ,0xff88a774) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff89a540) //120
NHSTUB(PostLogicalEventToUI                   ,0xff89a58c) //120
NHSTUB(PutInNdFilter                          ,0xffaef1ac) //102
NHSTUB(PutOutNdFilter                         ,0xffaef1d0) //102
NHSTUB(Read                                   ,0xff81ad58) //120
NHSTUB(ReadFastDir                            ,0xffaca2bc) //  6
NHSTUB(Rec2PB                                 ,0xff89dd68) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8b1da0) //104
NHSTUB(RenameFile_Fut                         ,0xff837c6c) //116
NHSTUB(Restart                                ,0xff83d8bc) //106
NHSTUB(ScreenLock                             ,0xff8b2f98) //117
NHSTUB(ScreenUnlock                           ,0xff8b2ffc) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb5d294) //102
NHSTUB(SetAutoShutdownTime                    ,0xff89adf8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff8a3510) //120
NHSTUB(SetFileAttributes                      ,0xff8387ec) //  6
NHSTUB(SetFileTimeStamp                       ,0xff838774) //  6
NHSTUB(SetLogicalEventActive                  ,0xff89aaec) //101
NHSTUB(SetParameterData                       ,0xff9b2304) //101
NHSTUB(SetPropertyCase                        ,0xff895d44) //102
NHSTUB(SetScriptMode                          ,0xff89ab3c) //120
NHSTUB(SleepTask                              ,0xff83bd4c) //120
NHSTUB(TakeSemaphore                          ,0xff83b9d0) //120
NHSTUB(TurnOffBackLight                       ,0xff8aa31c) //104
NHSTUB(TurnOnBackLight                        ,0xff8aa304) //104
NHSTUB(TurnOnDisplay                          ,0xff860178) //120
NHSTUB(TurnOffDisplay                         ,0xff860188) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff9a2184) //120
NHSTUB(UnlockAE                               ,0xff839f40) //120
NHSTUB(UnlockAF                               ,0xff839c60) //120
NHSTUB(UnlockMainPower                        ,0xff89acd8) //120
NHSTUB(VbattGet                               ,0xff833050) //120
NHSTUB(Write                                  ,0xff83843c) //120
NHSTUB(WriteSDCard                            ,0xff96b024) //108
NHSTUB(_log                                   ,0xffb9cc10) //111
NHSTUB(_log10                                 ,0xffb9d150) //112
NHSTUB(_pow                                   ,0xffb9d2c8) //121
NHSTUB(_sqrt                                  ,0xffb9eeec) //  6
NHSTUB(add_ptp_handler                        ,0xffa7be20) //121
NHSTUB(apex2us                                ,0xffa3b18c) //121
NHSTUB(close                                  ,0xff81abb4) //109
NHSTUB(err_init_task                          ,0xff815fd4) //111
NHSTUB(exmem_alloc                            ,0xff890950) //101
NHSTUB(exmem_free                             ,0xff8909c8) //101
NHSTUB(free                                   ,0xff814244) //112
NHSTUB(kbd_p1_f                               ,0xff834e94) //109
NHSTUB(kbd_p1_f_cont                          ,0xff834ea0) //109
NHSTUB(kbd_p2_f                               ,0xff83468c) //109
NHSTUB(kbd_read_keys                          ,0xff834e18) //109
NHSTUB(kbd_read_keys_r2                       ,0xff864f74) //109
NHSTUB(lseek                                  ,0xff838604) //120
NHSTUB(malloc                                 ,0xff8141ec) //112
NHSTUB(memcmp                                 ,0xff820934) //120
NHSTUB(memcpy                                 ,0xff84179c) //120
NHSTUB(memset                                 ,0xffa3a18c) //120
NHSTUB(mkdir                                  ,0xff838884) //109
NHSTUB(mktime_ext                             ,0xff8b3e10) //  1
NHSTUB(open                                   ,0xff81ab04) //109
NHSTUB(OpenFastDir                            ,0xffaca168) //  6
NHSTUB(closedir                               ,0xffaca118) //121
NHSTUB(qsort                                  ,0xffb3d66c) //  6
NHSTUB(rand                                   ,0xffa3a2cc) //121
NHSTUB(realloc                                ,0xffa3a208) //115
NHSTUB(reboot_fw_update                       ,0xffacf758) //106
NHSTUB(set_control_event                      ,0xff89a7b0) //111
NHSTUB(srand                                  ,0xffa3a2c0) //122
NHSTUB(stat                                   ,0xff83864c) //109
NHSTUB(strcat                                 ,0xff8b35c8) //  1
NHSTUB(strchr                                 ,0xff8140b8) //  1
NHSTUB(strcmp                                 ,0xff8208f0) //120
NHSTUB(strcpy                                 ,0xff8208d8) //120
NHSTUB(strftime                               ,0xff8b3810) //113
NHSTUB(strlen                                 ,0xff814104) //120
NHSTUB(strncmp                                ,0xff81406c) //  1
NHSTUB(strncpy                                ,0xff814030) //  1
NHSTUB(strrchr                                ,0xff8140dc) //  1
NHSTUB(strtol                                 ,0xff841a9c) //101
NHSTUB(strtolx                                ,0xff8418a0) //109
   DEF(task_CaptSeq                           ,0xff882920) //120
   DEF(task_ExpDrv                            ,0xff8cbcbc) //120
   DEF(task_FileWrite                         ,0xffac816c) //120
   DEF(task_InitFileModules                   ,0xff89e66c) //120
   DEF(task_MovieRecord                       ,0xff985e5c) //120
   DEF(task_PhySw                             ,0xff8349b8) //120
NHSTUB(time                                   ,0xff88ff64) //109
NHSTUB(vsprintf                               ,0xff820898) //115
NHSTUB(EngDrvRead                             ,0xff835d5c) //102
