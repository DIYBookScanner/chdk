// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R45 (DRYOS version 2.3, release #0045)
//   Firmware Ver GM1.01C   // Found @ 0xff88c80c, "GM1.01C" @ 0xff88c819
//   Firmware build timestamp: Sep 14 2010 19:56:23
//   Canon PowerShot SX130 IS

// Values for makefile.inc
//   PLATFORMOSVER = 45
//   PLATFORMID = 12817 (0x3211) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00166210  (*** DOES NOT MATCH MAKEFILE VALUE 0x00f00000***)
//   KEYSYS = d4b                // Found @ 0xffff3618
//   NEED_ENCODED_DISKBOOT = 5   // Found @ 0xffff3628
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff977548
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff977508

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DoAFLock                             ,0xff8384d8) //120        *** != 0xff878eec
//NHSTUB(GetBatteryTemperature                ,0xff863050) //102        *** != 0x00000000
//NHSTUB(UnlockAF                             ,0xff838510) //120        *** != 0xff878efc

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffac1640 -> ffbe80ac
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032b34) // Found @0xff834658
DEF(physw_run                               ,0x00001c3c) // Found @0xff83424c
DEF(physw_sleep_delay                       ,0x00001c44) // Found @0xff83424c
DEF(levent_table                            ,0xffb97a20) // Found @0xffb97a20
DEF(FlashParamsTable                        ,0xffbe82ac) // Found @0xffbe82ac
DEF(movie_status                            ,0x00006bac) // Found @0xff9698bc
DEF(video_compression_rate                  ,0x00006bec) // Found @0xff969b28
DEF(full_screen_refresh                     ,0x00009458) // Found @0xffa09454
DEF(canon_menu_active                       ,0x00003038) // Found @0xff88e340
DEF(canon_shoot_menu_active                 ,0x00007d89) // Found @0xff9a95b8
DEF(playrec_mode                            ,0x00002d64) // Found @0xff880644
DEF(zoom_status                             ,0x0000ce70) // Found @0xffac4bf0
DEF(some_flag_for_af_scan                   ,0x00006f68) // Found @0xff96cc44
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 128 entries in the table - set NUM_FL to 128
DEF(focus_len_table                         ,0xfffe94ec) // Found @0xfffe94ec
DEF(zoom_busy                               ,0x00006a94) // Found @0xff963b60
DEF(focus_busy                              ,0x00006978) // Found @0xff95fd2c
//DEF(recreview_hold                          ,0x00003a50) // Found @0xff89d940, ** != ** stubs_min = 0x000079d0 (0x78E4+0xEC)
// Palette colour tables  found @ 0xffbaf984
DEF(palette_control                         ,0x00009458) // Found @0xffa093d0
DEF(active_palette_buffer                   ,0x00009460) // Found @0xffa093d4
DEF(palette_buffer_ptr                      ,0x00009464) // Found @0xffa0977c
DEF(palette_buffer                          ,0x000b3a58) // Found @0xffa0978c
// Offset from start of palette_buffer to color data = 8 (Found @0xffaf7c20)
DEF(viewport_buffers                        ,0xffb4e474) // Found @0xff8502fc
DEF(active_viewport_buffer                  ,0x00002064) // Found @0xff8500ac
// Camera appears to have only 1 RAW buffer @ 0x41f3b020 (Found @0xffb102f0)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff85b5cc
//void *vid_get_viewport_fb()      { return (void*)0x40507700; }             // Found @0xffb0cec8
DEF(viewport_fb_d                           ,0x00002ac8) // Found 0x2a70 (@0xff872098) + 0x58 (@0xff8720d8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2a70+0x58)); } // Found @0xff872098 & 0xff8720d8
DEF(jpeg_count_str                          ,0x000b33a4) // Found @0xff9ff42c
//char *camera_jpeg_count_str()    { return (char*)0x000b33a4; }             // Found @0xff9ff42c
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffb10350
//int get_flash_params_count(void) { return 0x9a; }                          // Found @0xff993a48

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb4f4e8, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xffb4f508, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xffb4f478, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xffb4f478, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xffb4f470, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffb4f480, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000020 }, // Found @0xffb4f488, levent 0x03
//    { 2, KEY_POWER           ,0x00000040 }, // Found @0xffb4f490, levent 0x600 (uses inverted logic in physw_status)
//    { 2, KEY_PLAYBACK        ,0x00000080 }, // Found @0xffb4f498, levent 0x601 (uses inverted logic in physw_status)
//    { 2, KEY_UP              ,0x00000100 }, // Found @0xffb4f4a0, levent 0x04
//    { 2, KEY_DOWN            ,0x00000200 }, // Found @0xffb4f4a8, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xffb4f4b0, levent 0x07
//    { 2, KEY_LEFT            ,0x00000800 }, // Found @0xffb4f4b8, levent 0x06
//    { 2, KEY_SET             ,0x00001000 }, // Found @0xffb4f4c0, levent 0x08
//    { 2, KEY_MENU            ,0x00002000 }, // Found @0xffb4f4c8, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00004000 }, // Found @0xffb4f4d0, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4080 // Found @0xff93a260
//#define CAM_RAW_ROWS      3048 // Found @0xff93a268
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83a6a0

// Misc stuff
DEF(ctypes, 0xffb4dd8a)

// For capt_seq.c
DEF(_nrflag,0x6fac) // Found @ ff970950 (0x6fa4) & ff970984 (+0x08)
//static long *nrflag = (long*)(0x6fa4+0x08);  // Found @ ff970950 & ff970984
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83a65c) //112
NHSTUB(Close                                  ,0xff836cfc) //120
NHSTUB(CreateTask                             ,0xff81e8a0) //120
NHSTUB(DebugAssert                            ,0xff81eb78) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff836758) //116
NHSTUB(DeleteFile_Fut                         ,0xff836674) //112
NHSTUB(DoAELock                               ,0xff838734) //120
NHSTUB(EnterToCompensationEVF                 ,0xff838628) //104
NHSTUB(ExecuteEventProcedure                  ,0xff889a98) //104
NHSTUB(ExitFromCompensationEVF                ,0xff83866c) //104
NHSTUB(ExitTask                               ,0xff81eb30) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff846a84) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff846c14) //104
NHSTUB(Fclose_Fut                             ,0xff8367f0) //120
NHSTUB(Feof_Fut                               ,0xff8369dc) //  1
NHSTUB(Fflush_Fut                             ,0xff836a18) //  1
NHSTUB(Fgets_Fut                              ,0xff836944) //  1
NHSTUB(Fopen_Fut                              ,0xff8367b0) //120
NHSTUB(Fread_Fut                              ,0xff83689c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83a69c) //112
NHSTUB(Fseek_Fut                              ,0xff836990) //120
NHSTUB(Fwrite_Fut                             ,0xff8368f0) //120
NHSTUB(GetCCDTemperature                      ,0xff862fdc) //102
NHSTUB(GetCurrentAvValue                      ,0xff9625c0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff8709b8) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff870a18) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff8709ec) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff9609ac) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff960df8) //  3
NHSTUB(GetImageFolder                         ,0xff9419ac) //122
NHSTUB(GetKbdState                            ,0xff85fc0c) //109
NHSTUB(GetMemInfo                             ,0xff81a264) //115
NHSTUB(GetOpticalTemperature                  ,0xff8630c8) //120
NHSTUB(GetParameterData                       ,0xff993a0c) //101
NHSTUB(GetPropertyCase                        ,0xff88d7a0) //102
NHSTUB(GetSystemTime                          ,0xffab1a34) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8525f4) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff852600) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff963fc8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa9fe7c) //102
NHSTUB(GiveSemaphore                          ,0xff83a078) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8d7004) //102
NHSTUB(LEDDrive                               ,0xff85f0f4) //120
NHSTUB(LocalTime                              ,0xff8873e8) //115
NHSTUB(LockMainPower                          ,0xff893fec) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8366e8) //116
NHSTUB(MoveFocusLensToDistance                ,0xffb0994c) //102
NHSTUB(MoveIrisWithAv                         ,0xffaae374) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffaaea3c) //120
NHSTUB(Open                                   ,0xff836c90) //120
NHSTUB(PB2Rec                                 ,0xff896f88) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff878e9c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff878e74) //120
NHSTUB(PT_PlaySound                           ,0xff8824e4) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff891d90) //120
NHSTUB(PostLogicalEventToUI                   ,0xff891ddc) //120
NHSTUB(PutInNdFilter                          ,0xffb07608) //102
NHSTUB(PutOutNdFilter                         ,0xffb07640) //102
NHSTUB(Read                                   ,0xff81ad74) //120
NHSTUB(ReadFastDir                            ,0xffa8c488) //  4
NHSTUB(Rec2PB                                 ,0xff896fc8) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8a788c) //104
NHSTUB(RenameFile_Fut                         ,0xff8365e0) //116
NHSTUB(Restart                                ,0xff83be44) //106
NHSTUB(ScreenLock                             ,0xff8a8a1c) //117
NHSTUB(ScreenUnlock                           ,0xff8a8a80) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb0c094) //102
NHSTUB(SetAutoShutdownTime                    ,0xff894060) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89abfc) //120
NHSTUB(SetFileAttributes                      ,0xff836ff4) //  3
NHSTUB(SetFileTimeStamp                       ,0xff836f98) //  4
NHSTUB(SetLogicalEventActive                  ,0xff893d38) //101
NHSTUB(SetParameterData                       ,0xff993978) //101
NHSTUB(SetPropertyCase                        ,0xff88d678) //102
NHSTUB(SetScriptMode                          ,0xff893d88) //120
NHSTUB(SleepTask                              ,0xff83a2e0) //120
NHSTUB(TakeSemaphore                          ,0xff839fa8) //120
NHSTUB(TurnOffBackLight                       ,0xff8a0584) //104
NHSTUB(TurnOnBackLight                        ,0xff8a056c) //104
NHSTUB(TurnOnDisplay                          ,0xff85b8a8) //120
NHSTUB(TurnOffDisplay                         ,0xff85b8d4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff98420c) //120
NHSTUB(UnlockAE                               ,0xff838758) //120
NHSTUB(UnlockMainPower                        ,0xff893f40) //120
NHSTUB(UpdateMBROnFlash                       ,0xff870838) //105
NHSTUB(VbattGet                               ,0xff832fb4) //120
NHSTUB(Write                                  ,0xff836d8c) //120
NHSTUB(WriteSDCard                            ,0xff950268) //108
NHSTUB(_log                                   ,0xffb4b6d4) //111
NHSTUB(_log10                                 ,0xffb4a618) //112
NHSTUB(_pow                                   ,0xffb4a788) //121
NHSTUB(_sqrt                                  ,0xffb4caa0) //  1
NHSTUB(add_ptp_handler                        ,0xffa4c81c) //121
NHSTUB(apex2us                                ,0xffa0e804) //121
NHSTUB(close                                  ,0xff81ab8c) //109
NHSTUB(err_init_task                          ,0xff815fd4) //111
NHSTUB(exmem_alloc                            ,0xff888334) //103
NHSTUB(exmem_free                             ,0xff8883ac) //103
NHSTUB(free                                   ,0xff814244) //112
NHSTUB(kbd_p1_f                               ,0xff8346d0) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8346dc) //109
NHSTUB(kbd_p2_f                               ,0xff833f18) //109
NHSTUB(kbd_read_keys                          ,0xff834658) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85f5c4) //109
NHSTUB(lseek                                  ,0xff836e18) //120
NHSTUB(malloc                                 ,0xff8141e8) //112
NHSTUB(memcmp                                 ,0xff8206d0) //120
NHSTUB(memcpy                                 ,0xff83fd04) //120
NHSTUB(memset                                 ,0xffa0d800) //120
NHSTUB(mkdir                                  ,0xff837198) //109
NHSTUB(mktime_ext                             ,0xff8a9824) //  1
NHSTUB(open                                   ,0xff81aadc) //109
NHSTUB(OpenFastDir                            ,0xffa8c334) //  4
NHSTUB(closedir                               ,0xffa8c2e4) //121
NHSTUB(qsort                                  ,0xffaf8800) //  4
NHSTUB(rand                                   ,0xffa0d940) //121
NHSTUB(realloc                                ,0xffa0d87c) //115
NHSTUB(reboot_fw_update                       ,0xffa918a8) //106
NHSTUB(set_control_event                      ,0xff893928) //111
NHSTUB(srand                                  ,0xffa0d934) //122
NHSTUB(stat                                   ,0xff836e60) //109
NHSTUB(strcat                                 ,0xff8a8fe0) //  1
NHSTUB(strchr                                 ,0xff8140b4) //  1
NHSTUB(strcmp                                 ,0xff82068c) //120
NHSTUB(strcpy                                 ,0xff820674) //120
NHSTUB(strftime                               ,0xff8a922c) //113
NHSTUB(strlen                                 ,0xff814100) //120
NHSTUB(strncmp                                ,0xff814068) //  1
NHSTUB(strncpy                                ,0xff81402c) //  1
NHSTUB(strrchr                                ,0xff8140d8) //  1
NHSTUB(strtol                                 ,0xff83ffe4) //101
NHSTUB(strtolx                                ,0xff83fde8) //109
   DEF(task_CaptSeq                           ,0xff87b564) //120
   DEF(task_ExpDrv                            ,0xff8bfa94) //120
   DEF(task_FileWrite                         ,0xffa8a35c) //120
   DEF(task_InitFileModules                   ,0xff897938) //120
   DEF(task_MovieRecord                       ,0xff969bc8) //120
   DEF(task_PhySw                             ,0xff834248) //120
   DEF(task_RotaryEncoder                     ,0xff85fd80) //120
NHSTUB(time                                   ,0xff8879c8) //109
NHSTUB(vsprintf                               ,0xff820638) //115
NHSTUB(EngDrvRead                             ,0xff835528) //102
