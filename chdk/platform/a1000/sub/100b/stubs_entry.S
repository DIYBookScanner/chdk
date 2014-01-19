// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00B   // Found @ 0xffc5853c, "GM1.00B" @ 0xffc58549
//   Firmware build timestamp: Jul  9 2008 17:52:41
//   Canon PowerShot A1000 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12686 (0x318e) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000d4ec8
//   KEYSYS = d4                 // Found @ 0xffff1a9c
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff1aac
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd15e44
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd15e04

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(PT_PlaySound                         ,0xffc48c7c) //102        *** != 0xffc48fbc
//NHSTUB(SetAE_ShutterSpeed                   ,0xffe42b88) //102        *** != 0xffe3de6c
//NHSTUB(kbd_pwr_off                          ,0xffc3163c) //  2 64%    *** != 0xffc3164c
NHSTUB(kbd_pwr_on                             ,0xffc315fc) //  2 82%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdfaf9c -> ffec9db0
// Current modemap entry not found in firmware - MODE_SCN_AQUARIUM        16407
// Current modemap entry not found in firmware - MODE_STITCH              33290
// Current modemap entry not found in firmware - MODE_M                   32769
// Current modemap entry not found in firmware - MODE_AV                  32770
// Current modemap entry not found in firmware - MODE_TV                  32771

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000f3f8) // Found @0xffc113ec
DEF(physw_run                               ,0x00001be4) // Found @0xffc11064
DEF(physw_sleep_delay                       ,0x00001be2) // Found @0xffc11064
DEF(levent_table                            ,0xffeab474) // Found @0xffeab474
DEF(FlashParamsTable                        ,0xffec9f7c) // Found @0xffec9f7c
DEF(movie_status                            ,0x000050a0) // Found @0xffc47cf8
DEF(canon_menu_active                       ,0x00005480) // Found @0xffc59fb8
DEF(canon_shoot_menu_active                 ,0x00009735) // Found @0xffd3b670
DEF(playrec_mode                            ,0x00005228) // Found @0xffc4ec4c
DEF(zoom_status                             ,0x0000c0a4) // Found @0xffdfc7b0
DEF(some_flag_for_af_scan                   ,0x000085a8) // Found @0xffd0a65c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe297c) // Found @0xfffe297c
DEF(zoom_busy                               ,0x00007fdc) // Found @0xffd03034
DEF(focus_busy                              ,0x00007ee4) // Found @0xffcfebb4
DEF(recreview_hold                          ,0x000059e4) // Found @0xffc65b4c
// Camera has 2 RAW buffers @ 0x107d58e0 & 0x11b96b80
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffe8e6f4) // Found @0xffe8e6f4
DEF(active_raw_buffer                       ,0x000051d8) // Found @0xffc4c5c8

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc2ce78
//void *vid_get_viewport_fb()      { return (void*)0x10659de0; }             // Found @0xffe43978
DEF(viewport_fb_d                           ,0x00004f3c) // Found 0x4ee8 (@0xffc4177c) + 0x54 (@0xffc417a8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x4ee8+0x54)); } // Found @0xffc4177c & 0xffc417a8
DEF(jpeg_count_str                          ,0x0004506c) // Found @0xffd70d44
//char *camera_jpeg_count_str()    { return (char*)0x0004506c; }             // Found @0xffd70d44
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe45d1c
//int get_flash_params_count(void) { return 0x77; }                          // Found @0xffd2d3e4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe75208, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe75214, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00004000 }, // Found @0xffe750c4, levent 0x600 (uses inverted logic in physw_status)
//    { 1, KEY_PLAYBACK        ,0x02000000 }, // Found @0xffe750e8, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_SHOOT_FULL      ,0xc0000000 }, // Found @0xffe75130, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x80000000 }, // Found @0xffe75130, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x40000000 }, // Found @0xffe75124, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe75154, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe75160, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe7516c, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe75178, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe75184, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe75190, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe7519c, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffe751a8, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffe751b4, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffe3cbe0
//#define CAM_RAW_ROWS      2772 // Found @0xffe3cbe8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc171b8

// Misc stuff
DEF(ctypes, 0xffe74cee)

// For capt_seq.c
DEF(_nrflag,0x8594) // Found @ ffd0c2d0 (0x8598) & ffd0c2ec (-0x04)
//static long *nrflag = (long*)(0x8598-0x04);  // Found @ ffd0c2d0 & ffd0c2e8

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
NHSTUB(ExecuteEventProcedure                  ,0xffc55764) //104
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
NHSTUB(GetBatteryTemperature                  ,0xffc33738) //102
NHSTUB(GetCCDTemperature                      ,0xffc336c8) //102
NHSTUB(GetCurrentAvValue                      ,0xffd005ec) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc3ffe0) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc40048) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc40014) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffcff6e4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffcff9f0) //  3
NHSTUB(GetKbdState                            ,0xffc315c8) //109
NHSTUB(GetMemInfo                             ,0xffc03c28) //115
NHSTUB(GetOpticalTemperature                  ,0xffc337a8) //120
NHSTUB(GetParameterData                       ,0xffd2d3a4) //101
NHSTUB(GetPropertyCase                        ,0xffc594cc) //102
NHSTUB(GetSystemTime                          ,0xffdefe78) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffca2420) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffca242c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd033a4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffde9db0) //102
NHSTUB(GiveSemaphore                          ,0xffc0b81c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc8b28c) //102
NHSTUB(LEDDrive                               ,0xffc30c9c) //120
NHSTUB(LocalTime                              ,0xffc53768) //115
NHSTUB(LockMainPower                          ,0xffc5cdd0) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc12c64) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe403bc) //102
NHSTUB(MoveIrisWithAv                         ,0xffdec64c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdecbd8) //120
NHSTUB(Open                                   ,0xffc1331c) //120
NHSTUB(PB2Rec                                 ,0xffc5e804) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc49094) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc4906c) //120
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5c410) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5c45c) //120
NHSTUB(PutInNdFilter                          ,0xffdeca3c) //102
NHSTUB(PutOutNdFilter                         ,0xffdeca60) //102
NHSTUB(Read                                   ,0xffc0a138) //120
NHSTUB(ReadFastDir                            ,0xffddc2b4) //  1
NHSTUB(Rec2PB                                 ,0xffc5e858) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd7a3c0) //104
NHSTUB(RenameFile_Fut                         ,0xffc12b9c) //  1
NHSTUB(Restart                                ,0xffc189ec) //106
NHSTUB(SetAutoShutdownTime                    ,0xffc5ce44) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc634f8) //120
NHSTUB(SetFileAttributes                      ,0xffc13670) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13620) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5cb4c) //101
NHSTUB(SetParameterData                       ,0xffd2d314) //101
NHSTUB(SetPropertyCase                        ,0xffc593c4) //102
NHSTUB(SetScriptMode                          ,0xffc5cb9c) //120
NHSTUB(SleepTask                              ,0xffc16ff8) //120
NHSTUB(TakeSemaphore                          ,0xffc0b74c) //120
NHSTUB(TurnOffBackLight                       ,0xffc67e6c) //104
NHSTUB(TurnOnBackLight                        ,0xffc67e54) //104
NHSTUB(TurnOnDisplay                          ,0xffc2cf40) //120
NHSTUB(TurnOffDisplay                         ,0xffc2cf50) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd2048c) //120
NHSTUB(UnlockAE                               ,0xffc150a8) //120
NHSTUB(UnlockAF                               ,0xffc14dd4) //120
NHSTUB(UnlockMainPower                        ,0xffc5cd24) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd32980) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3fe20) //105
NHSTUB(VbattGet                               ,0xffc10314) //120
NHSTUB(Write                                  ,0xffc133f0) //120
NHSTUB(WriteSDCard                            ,0xffcf4e38) //108
NHSTUB(_log                                   ,0xffe72af4) //111
NHSTUB(_log10                                 ,0xffe71a38) //112
NHSTUB(_pow                                   ,0xffe71ba8) //121
NHSTUB(_sqrt                                  ,0xffe73e5c) //  1
NHSTUB(add_ptp_handler                        ,0xffdab87c) //121
NHSTUB(apex2us                                ,0xffd7b3dc) //121
NHSTUB(close                                  ,0xffc09f50) //109
NHSTUB(err_init_task                          ,0xffc04e84) //111
NHSTUB(exmem_alloc                            ,0xffc53f68) //103
NHSTUB(exmem_free                             ,0xffc53fe0) //103
NHSTUB(free                                   ,0xffc03a80) //112
NHSTUB(kbd_p1_f                               ,0xffc114f0) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc114fc) //109
NHSTUB(kbd_p2_f                               ,0xffc10d04) //109
NHSTUB(kbd_read_keys                          ,0xffc113ec) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc310b4) //109
NHSTUB(lseek                                  ,0xffc13484) //120
NHSTUB(malloc                                 ,0xffc039ac) //112
NHSTUB(memcmp                                 ,0xffc0d8b4) //120
NHSTUB(memcpy                                 ,0xffc6ce5c) //120
NHSTUB(memset                                 ,0xffd7a714) //120
NHSTUB(mkdir                                  ,0xffc136e8) //109
NHSTUB(mktime_ext                             ,0xffc6d6c8) //  1
NHSTUB(open                                   ,0xffc09ea0) //109
NHSTUB(OpenFastDir                            ,0xffddc220) //  1
NHSTUB(closedir                               ,0xffddc384) //  1
NHSTUB(qsort                                  ,0xffe2bbec) //  1
NHSTUB(rand                                   ,0xffc0d9bc) //121
NHSTUB(realloc                                ,0xffc03b60) //115
NHSTUB(reboot_fw_update                       ,0xffde0b88) //106
NHSTUB(set_control_event                      ,0xffc5c898) //111
NHSTUB(srand                                  ,0xffc0d9b0) //122
NHSTUB(stat                                   ,0xffc13550) //  1
NHSTUB(strcat                                 ,0xffc6cc70) //  1
NHSTUB(strchr                                 ,0xffc6ccf8) //  1
NHSTUB(strcmp                                 ,0xffc0d84c) //120
NHSTUB(strcpy                                 ,0xffc0d834) //120
NHSTUB(strftime                               ,0xffc6d0d0) //  1
NHSTUB(strlen                                 ,0xffc0d890) //120
NHSTUB(strncmp                                ,0xffc6ccac) //  1
NHSTUB(strncpy                                ,0xffc1cb54) //  1
NHSTUB(strrchr                                ,0xffd7a6ec) //  1
NHSTUB(strtol                                 ,0xffc1cd8c) //101
NHSTUB(strtolx                                ,0xffc1cb90) //109
   DEF(task_CaptSeq                           ,0xffc4b22c) //120
   DEF(task_ExpDrv                            ,0xffc84248) //120
   DEF(task_FileWrite                         ,0xffdd8bd4) //120
   DEF(task_InitFileModules                   ,0xffc60680) //120
   DEF(task_MovieRecord                       ,0xffc47f5c) //120
   DEF(task_PhySw                             ,0xffc11060) //120
NHSTUB(time                                   ,0xffc5361c) //109
NHSTUB(vsprintf                               ,0xffc0d7f8) //115
NHSTUB(EngDrvRead                             ,0xffc12330) //102
