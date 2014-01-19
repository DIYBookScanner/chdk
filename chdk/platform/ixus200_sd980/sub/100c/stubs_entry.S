// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R39 (DRYOS version 2.3, release #0039)
//   Firmware Ver GM1.00C   // Found @ 0xff887c3c, "GM1.00C" @ 0xff887c49
//   Firmware build timestamp: Jul 17 2009 15:49:34
//   Canon DIGITAL IXUS 200 IS

// Values for makefile.inc
//   PLATFORMOSVER = 39
//   PLATFORMID = 12773 (0x31e5) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00153e84
//   KEYSYS = d4                 // Found @ 0xffff3564
//   NEED_ENCODED_DISKBOOT = 3   // Found @ 0xffff3574
//   ARAM_HEAP_START = 0x38e000  // Found @ 0xff958d50
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff958d10

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(kbd_pwr_off                            ,0xff85ae98) //  2 64%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffaab240 -> ffbda99c
// Mode 32774 in firmware but not in current modemap
// Mode 33288 in firmware but not in current modemap
// Mode 33307 in firmware but not in current modemap
// Mode 33308 in firmware but not in current modemap
// Mode 32797 in firmware but not in current modemap
// Mode 32786 in firmware but not in current modemap
// Mode 32788 in firmware but not in current modemap
// Mode 32789 in firmware but not in current modemap
// Mode 32785 in firmware but not in current modemap
// Mode 33295 in firmware but not in current modemap
// Mode 32784 in firmware but not in current modemap
// Mode  2601 in firmware but not in current modemap
// Mode  2602 in firmware but not in current modemap
// Current modemap entry not found in firmware - MODE_SCN_COLOR_SWAP      16924
// Current modemap entry not found in firmware - MODE_SCN_COLOR_ACCENT    16923
// Current modemap entry not found in firmware - MODE_SCN_ISO_3200        16413
// Current modemap entry not found in firmware - MODE_SCN_BEACH           16405
// Current modemap entry not found in firmware - MODE_SCN_SNOW            16404
// Current modemap entry not found in firmware - MODE_SCN_SUNSET          16402
// Current modemap entry not found in firmware - MODE_SCN_INDOOR          16401
// Current modemap entry not found in firmware - MODE_SCN_NIGHT_SCENE     16398
// Current modemap entry not found in firmware - MODE_SPORTS              33287
// Current modemap entry not found in firmware - MODE_VIDEO_STD            3622
// Current modemap entry not found in firmware - MODE_LANDSCAPE           32780
// Current modemap entry not found in firmware - MODE_M                   32769
// Current modemap entry not found in firmware - MODE_AV                  32770
// Current modemap entry not found in firmware - MODE_TV                  32771

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00044558) // Found @0xff8335a8
DEF(physw_run                               ,0x00001c44) // Found @0xff833200
DEF(physw_sleep_delay                       ,0x00001c42) // Found @0xff833200
DEF(levent_table                            ,0xffb7a290) // Found @0xffb7a290
DEF(FlashParamsTable                        ,0xffbdab84) // Found @0xffbdab84
//DEF(movie_status                            ,0x000067e0) // Found @0xff94ac20,          stubs_min = 0x000067e0 (0x000067e0)
DEF(video_compression_rate                  ,0x0000680c) // Found @0xff94ae8c
DEF(full_screen_refresh                     ,0x0001b2dc) // Found @0xff9f751c
DEF(canon_menu_active                       ,0x00002ec8) // Found @0xff889704
DEF(canon_shoot_menu_active                 ,0x00007b09) // Found @0xff98d9ac
DEF(playrec_mode                            ,0x00002bfc) // Found @0xff87bbdc
DEF(zoom_status                             ,0x0001e3d4) // Found @0xffaadccc
DEF(some_flag_for_af_scan                   ,0x00006cd4) // Found @0xff94dc3c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 12 entries in the table - set NUM_FL to 12
DEF(focus_len_table                         ,0xfffe2ac8) // Found @0xfffe2ac8
DEF(zoom_busy                               ,0x0000670c) // Found @0xff946e00
DEF(focus_busy                              ,0x00006608) // Found @0xff941f28
//DEF(recreview_hold                          ,0x00003818) // Found @0xff89a778,          stubs_min = 0x00003818 (0x00003818)
// Palette colour tables  found @ 0xffb93e74
DEF(active_palette_buffer                   ,0x0001b2e4) // Found @0xff9f7458
DEF(palette_buffer_ptr                      ,0x0001b2f0) // Found @0xff9f712c
// Offset from start of palette_buffer to color data = 8 (Found @0xffae531c)
// Camera appears to have only 1 RAW buffer @ 0x421e1120 (Found @0xffb0e6a4)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40431000; }             // Found @0xff853588
//void *vid_get_viewport_fb()      { return (void*)0x408cb700; }             // Found @0xffb0b870
DEF(viewport_fb_d                           ,0x00002948) // Found 0x28f0 (@0xff86d354) + 0x58 (@0xff86d38c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x28f0+0x58)); } // Found @0xff86d354 & 0xff86d38c
DEF(jpeg_count_str                          ,0x00084ca4) // Found @0xff9e8aa8
//char *camera_jpeg_count_str()    { return (char*)0x00084ca4; }             // Found @0xff9e8aa8
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffb0e700
//int get_flash_params_count(void) { return 0x84; }                          // Found @0xff979b5c

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb404d8, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00100000 // Found @0xffb404f0, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_MENU            ,0x00000001 }, // Found @0xffb40430, levent 0x09
//    { 2, KEY_SET             ,0x00000002 }, // Found @0xffb4043c, levent 0x08
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffb40448, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffb40454, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffb40460, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffb4046c, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffb40478, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffb40484, levent 0x04
//    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffb4049c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffb4049c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffb40490, levent 0x00
//    { 2, KEY_POWER           ,0x00000400 }, // Found @0xffb404a8, levent 0x600
//    { 2, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffb404b4, levent 0x601
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4080 // Found @0xff91bfbc
//#define CAM_RAW_ROWS      3048 // Found @0xff91bfc4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff838a1c

// Misc stuff
DEF(ctypes, 0xffb3eb2e)

// For capt_seq.c
DEF(_nrflag,0x6cb0) // Found @ ff94ff04 (0x6cb8) & ff94ff24 (-0x08)
//static long *nrflag = (long*)(0x6cb8-0x08);  // Found @ ff94ff04 & ff94ff20

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8389d8) //112
NHSTUB(Close                                  ,0xff835408) //120
NHSTUB(CreateTask                             ,0xff81e5b4) //120
NHSTUB(DebugAssert                            ,0xff81e88c) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff834e78) //116
NHSTUB(DeleteFile_Fut                         ,0xff834d94) //112
NHSTUB(DoAELock                               ,0xff836b78) //120
NHSTUB(DoAFLock                               ,0xff8368f0) //120
NHSTUB(EnterToCompensationEVF                 ,0xff836ae0) //104
NHSTUB(ExecuteEventProcedure                  ,0xff884de0) //104
NHSTUB(ExitFromCompensationEVF                ,0xff836b24) //104
NHSTUB(ExitTask                               ,0xff81e844) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff844254) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff84432c) //104
NHSTUB(Fclose_Fut                             ,0xff834f10) //120
NHSTUB(Feof_Fut                               ,0xff8350fc) //  1
NHSTUB(Fflush_Fut                             ,0xff835138) //  1
NHSTUB(Fgets_Fut                              ,0xff835064) //  1
NHSTUB(Fopen_Fut                              ,0xff834ed0) //120
NHSTUB(Fread_Fut                              ,0xff834fbc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff838a18) //112
NHSTUB(Fseek_Fut                              ,0xff8350b0) //120
NHSTUB(Fwrite_Fut                             ,0xff835010) //120
NHSTUB(GetBatteryTemperature                  ,0xff85e2ac) //102
NHSTUB(GetCCDTemperature                      ,0xff85e238) //102
NHSTUB(GetCurrentAvValue                      ,0xff9446cc) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86bb04) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86bb64) //  3
NHSTUB(GetDrive_TotalClusters                 ,0xff86bb38) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff942ca0) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9430e8) //  3
NHSTUB(GetImageFolder                         ,0xff923de8) //122
NHSTUB(GetKbdState                            ,0xff85ae80) //109
NHSTUB(GetMemInfo                             ,0xff81a070) //115
NHSTUB(GetOpticalTemperature                  ,0xff85e320) //120
NHSTUB(GetParameterData                       ,0xff979b1c) //101
NHSTUB(GetPropertyCase                        ,0xff888b48) //102
NHSTUB(GetSystemTime                          ,0xffa9edf8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8e1e14) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8e1e20) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff947174) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa904e8) //102
NHSTUB(GiveSemaphore                          ,0xff8383f4) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8c3a24) //102
NHSTUB(LEDDrive                               ,0xff85a31c) //120
NHSTUB(LocalTime                              ,0xff882754) //115
NHSTUB(LockMainPower                          ,0xff8909b0) //120
NHSTUB(MakeDirectory_Fut                      ,0xff834e08) //116
NHSTUB(MoveFocusLensToDistance                ,0xffb08258) //102
NHSTUB(MoveIrisWithAv                         ,0xffa9c334) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa9c980) //120
NHSTUB(Open                                   ,0xff8353b0) //120
NHSTUB(PB2Rec                                 ,0xff8939dc) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8747cc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff8747a4) //120
NHSTUB(PT_PlaySound                           ,0xff87d8a8) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff88e7b8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff88e804) //120
NHSTUB(PutInNdFilter                          ,0xffb05eb8) //102
NHSTUB(PutOutNdFilter                         ,0xffb05ef0) //102
NHSTUB(Read                                   ,0xff81ab78) //120
NHSTUB(ReadFastDir                            ,0xffa7e1e4) //  3
NHSTUB(Rec2PB                                 ,0xff893a1c) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9f8694) //104
NHSTUB(RenameFile_Fut                         ,0xff834d00) //116
NHSTUB(Restart                                ,0xff83a130) //106
NHSTUB(ScreenLock                             ,0xff9f98b4) //117
NHSTUB(ScreenUnlock                           ,0xff9f98dc) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb0a9e8) //102
NHSTUB(SetAutoShutdownTime                    ,0xff890a24) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff897d04) //120
NHSTUB(SetFileAttributes                      ,0xff8356d8) //  3
NHSTUB(SetFileTimeStamp                       ,0xff835694) //  3
NHSTUB(SetLogicalEventActive                  ,0xff8906fc) //101
NHSTUB(SetParameterData                       ,0xff979a8c) //101
NHSTUB(SetPropertyCase                        ,0xff888a44) //102
//NHSTUB(SetScriptMode                        ,0xff89074c) //120            == 0xff89074c
NHSTUB(SleepTask                              ,0xff83865c) //120
NHSTUB(TakeSemaphore                          ,0xff838324) //120
NHSTUB(TurnOffBackLight                       ,0xff89e2b8) //104
NHSTUB(TurnOnBackLight                        ,0xff89e2a0) //104
NHSTUB(TurnOnDisplay                          ,0xff8537d0) //120
NHSTUB(TurnOffDisplay                         ,0xff8537e0) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff9642c8) //120
NHSTUB(UnlockAE                               ,0xff836b9c) //120
NHSTUB(UnlockAF                               ,0xff836928) //120
NHSTUB(UnlockMainPower                        ,0xff890904) //120
NHSTUB(UnsetZoomForMovie                      ,0xff97fdd8) //104
NHSTUB(UpdateMBROnFlash                       ,0xff86b984) //105
NHSTUB(VbattGet                               ,0xff831e04) //120
NHSTUB(Write                                  ,0xff835498) //120
NHSTUB(WriteSDCard                            ,0xff933968) //108
NHSTUB(_log                                   ,0xffb3bc5c) //111
NHSTUB(_log10                                 ,0xffb3a8e8) //112
NHSTUB(_pow                                   ,0xffb3aa58) //121
NHSTUB(_sqrt                                  ,0xffb3d8e0) //  1
NHSTUB(add_ptp_handler                        ,0xffa3f97c) //121
NHSTUB(apex2us                                ,0xff9fd42c) //121
NHSTUB(close                                  ,0xff81a990) //109
NHSTUB(err_init_task                          ,0xff815f28) //111
NHSTUB(exmem_alloc                            ,0xff883614) //103
NHSTUB(exmem_free                             ,0xff88368c) //103
NHSTUB(free                                   ,0xff814138) //112
NHSTUB(kbd_p1_f                               ,0xff833624) //109
NHSTUB(kbd_p1_f_cont                          ,0xff833630) //109
NHSTUB(kbd_p2_f                               ,0xff832ecc) //109
NHSTUB(kbd_read_keys                          ,0xff8335a8) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85a83c) //109
NHSTUB(lseek                                  ,0xff835524) //120
NHSTUB(malloc                                 ,0xff8140dc) //112
NHSTUB(memcmp                                 ,0xff8203e8) //120
NHSTUB(memcpy                                 ,0xff83df94) //120
NHSTUB(memset                                 ,0xff9fbfa0) //120
NHSTUB(mkdir                                  ,0xff83587c) //109
NHSTUB(mktime_ext                             ,0xff8a5d68) //  1
NHSTUB(open                                   ,0xff81a8e0) //109
NHSTUB(OpenFastDir                            ,0xffa7e0b0) //  3
NHSTUB(closedir                               ,0xffa7e06c) //  3
NHSTUB(qsort                                  ,0xff9fc560) //  1
NHSTUB(rand                                   ,0xff8204f0) //121
NHSTUB(realloc                                ,0xff9fc01c) //115
NHSTUB(reboot_fw_update                       ,0xffa836f4) //106
NHSTUB(set_control_event                      ,0xff89032c) //111
NHSTUB(srand                                  ,0xff8204e4) //122
NHSTUB(stat                                   ,0xff835560) //109
NHSTUB(strcat                                 ,0xff8a5524) //  1
NHSTUB(strchr                                 ,0xff813fc0) //  1
NHSTUB(strcmp                                 ,0xff8203a4) //120
NHSTUB(strcpy                                 ,0xff82038c) //120
NHSTUB(strftime                               ,0xff8a5770) //  1
NHSTUB(strlen                                 ,0xff81400c) //120
NHSTUB(strncmp                                ,0xff813f74) //  1
NHSTUB(strncpy                                ,0xff813f38) //  1
NHSTUB(strrchr                                ,0xff813fe4) //  1
NHSTUB(strtol                                 ,0xff83e274) //101
NHSTUB(strtolx                                ,0xff83e078) //109
   DEF(task_CaptSeq                           ,0xff876e70) //120
   DEF(task_ExpDrv                            ,0xff8ba2d4) //120
   DEF(task_FileWrite                         ,0xffa79a40) //120
   DEF(task_InitFileModules                   ,0xff894500) //120
   DEF(task_MovieRecord                       ,0xff94af08) //120
   DEF(task_PhySw                             ,0xff8331fc) //120
   DEF(task_RotaryEncoder                     ,0xff85afb0) //120
   DEF(task_TouchPanel                        ,0xff85e89c) //120
NHSTUB(time                                   ,0xff882ccc) //109
NHSTUB(vsprintf                               ,0xff820350) //115
NHSTUB(EngDrvRead                             ,0xff83446c) //102
