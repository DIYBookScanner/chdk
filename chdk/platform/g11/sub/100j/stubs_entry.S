// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R39 (DRYOS version 2.3, release #0039)
//   Firmware Ver GM1.00J   // Found @ 0xff88c79c, "GM1.00J" @ 0xff88c7a9
//   Firmware build timestamp: Sep 28 2009 08:48:15
//   Canon PowerShot G11

// Values for makefile.inc
//   PLATFORMOSVER = 39
//   PLATFORMID = 12767 (0x31df) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x001411e8
//   KEYSYS = d4                 // Found @ 0xffff35a8
//   NEED_ENCODED_DISKBOOT = 3   // Found @ 0xffff35b8
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff971b60
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff971b20

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(SetScriptMode                        ,0xff8950e4) //120        *** != 0xff810f4c
NHSTUB(kbd_pwr_off                            ,0xff86043c) //  2 64%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffab487c -> ffbe7010
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032578) // Found @0xff833584
DEF(physw_run                               ,0x00001c44) // Found @0xff8331f4
DEF(physw_sleep_delay                       ,0x00001c42) // Found @0xff8331f4
DEF(levent_table                            ,0xffb95e24) // Found @0xffb95e24
DEF(FlashParamsTable                        ,0xffbe7204) // Found @0xffbe7204
DEF(movie_status                            ,0x00006d90) // Found @0xff9628bc
DEF(video_compression_rate                  ,0x00006dbc) // Found @0xff962a78
DEF(full_screen_refresh                     ,0x00009840) // Found @0xffa0ecdc
DEF(canon_menu_active                       ,0x0000303c) // Found @0xff88e27c
DEF(canon_shoot_menu_active                 ,0x00008259) // Found @0xff9af938
DEF(playrec_mode                            ,0x00002d64) // Found @0xff880558
DEF(zoom_status                             ,0x0000c868) // Found @0xffab7768
DEF(some_flag_for_af_scan                   ,0x000072b4) // Found @0xff965f34
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 14 entries in the table - set NUM_FL to 14
DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c
DEF(zoom_busy                               ,0x00006cc0) // Found @0xff95ea98
DEF(focus_busy                              ,0x00006bb4) // Found @0xff959a8c
//DEF(recreview_hold                          ,0x00003be4) // Found @0xff89fafc, ** != ** stubs_min = 0x00007dd8 (0x7D00+0xD8)
// Palette colour tables  found @ 0xffbb0b04
DEF(active_palette_buffer                   ,0x00009848) // Found @0xffa0ec18
DEF(palette_buffer_ptr                      ,0x00009854) // Found @0xffa0e8ec
// Offset from start of palette_buffer to color data = 8 (Found @0xffaedc18)
// Camera appears to have only 1 RAW buffer @ 0x41c0f460 (Found @0xffb09a0c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff85a4c0
//void *vid_get_viewport_fb()      { return (void*)0x40587700; }             // Found @0xffb067b0
DEF(viewport_fb_d                           ,0x00002aa8) // Found 0x2a50 (@0xff8712f8) + 0x58 (@0xff871330)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2a50+0x58)); } // Found @0xff8712f8 & 0xff871330
DEF(jpeg_count_str                          ,0x00097234) // Found @0xffa010f0
//char *camera_jpeg_count_str()    { return (char*)0x00097234; }             // Found @0xffa010f0
//long hook_raw_size()             { return 0x00ee9200; }                    // Found @0xffb09a68
//int get_flash_params_count(void) { return 0x84; }                          // Found @0xff9968bc

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb475f0, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00100000 // Found @0xffb47614, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffb4747c, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffb47488, levent 0x02
//    { 0, KEY_LEFT            ,0x00000400 }, // Found @0xffb474d0, levent 0x06
//    { 0, KEY_SET             ,0x00000800 }, // Found @0xffb474dc, levent 0x08
//    { 0, KEY_RIGHT           ,0x00001000 }, // Found @0xffb474e8, levent 0x07
//    { 0, KEY_DOWN            ,0x00002000 }, // Found @0xffb474f4, levent 0x05
//    { 0, KEY_UP              ,0x00004000 }, // Found @0xffb47500, levent 0x04
//    { 0, KEY_DISPLAY         ,0x00020000 }, // Found @0xffb47524, levent 0x0a
//    { 0, KEY_MENU            ,0x00040000 }, // Found @0xffb47530, levent 0x09
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb475b4, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb475b4, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb475a8, levent 0x00
//    { 2, KEY_POWER           ,0x00000004 }, // Found @0xffb475c0, levent 0x600 (uses inverted logic in physw_status)
//    { 2, KEY_PLAYBACK        ,0x00000008 }, // Found @0xffb475cc, levent 0x601 (uses inverted logic in physw_status)
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3744 // Found @0xff9357c8
//#define CAM_RAW_ROWS      2784 // Found @0xff9357d0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff839460

// Misc stuff
DEF(ctypes, 0xffb403ca)

// For capt_seq.c
DEF(_nrflag,0x7290) // Found @ ff96881c (0x7298) & ff96883c (-0x08)
//static long *nrflag = (long*)(0x7298-0x08);  // Found @ ff96881c & ff968838

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83941c) //112
NHSTUB(Close                                  ,0xff8359b0) //120
NHSTUB(CreateTask                             ,0xff81e5b4) //120
NHSTUB(DebugAssert                            ,0xff81e88c) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff835420) //116
NHSTUB(DeleteFile_Fut                         ,0xff83533c) //112
NHSTUB(DoAELock                               ,0xff8374e0) //120
NHSTUB(DoAFLock                               ,0xff837158) //120
NHSTUB(EnterToCompensationEVF                 ,0xff8373d8) //104
NHSTUB(ExecuteEventProcedure                  ,0xff889904) //104
NHSTUB(ExitFromCompensationEVF                ,0xff83741c) //104
NHSTUB(ExitTask                               ,0xff81e844) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff844ce0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff844db8) //104
NHSTUB(Fclose_Fut                             ,0xff8354b8) //120
NHSTUB(Feof_Fut                               ,0xff8356a4) //  1
NHSTUB(Fflush_Fut                             ,0xff8356e0) //  1
NHSTUB(Fgets_Fut                              ,0xff83560c) //  1
NHSTUB(Fopen_Fut                              ,0xff835478) //120
NHSTUB(Fread_Fut                              ,0xff835564) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83945c) //112
NHSTUB(Fseek_Fut                              ,0xff835658) //120
NHSTUB(Fwrite_Fut                             ,0xff8355b8) //120
NHSTUB(GetBatteryTemperature                  ,0xff8635d8) //102
NHSTUB(GetCCDTemperature                      ,0xff863564) //102
NHSTUB(GetCurrentAvValue                      ,0xff95c230) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86fc80) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86fce0) //  3
NHSTUB(GetDrive_TotalClusters                 ,0xff86fcb4) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff95a804) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff95ac4c) //  3
NHSTUB(GetImageFolder                         ,0xff93d654) //122
NHSTUB(GetKbdState                            ,0xff860424) //109
NHSTUB(GetMemInfo                             ,0xff81a070) //115
NHSTUB(GetOpticalTemperature                  ,0xff86364c) //120
NHSTUB(GetParameterData                       ,0xff99687c) //101
NHSTUB(GetPropertyCase                        ,0xff88d6b0) //102
NHSTUB(GetSystemTime                          ,0xffaa3594) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff850b08) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff850b14) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff95ee0c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa967a0) //102
NHSTUB(GiveSemaphore                          ,0xff838e38) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8db3f0) //102
NHSTUB(LEDDrive                               ,0xff85f674) //120
NHSTUB(LocalTime                              ,0xff887278) //115
NHSTUB(LockMainPower                          ,0xff895344) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8353b0) //116
NHSTUB(MoveFocusLensToDistance                ,0xffb031cc) //102
NHSTUB(MoveIrisWithAv                         ,0xffaa0448) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffaa0b60) //120
NHSTUB(Open                                   ,0xff835958) //120
NHSTUB(PB2Rec                                 ,0xff898460) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff878178) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff878150) //120
NHSTUB(PT_PlaySound                           ,0xff882414) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff893170) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8931bc) //120
NHSTUB(PutInNdFilter                          ,0xffaa09c4) //102
NHSTUB(PutOutNdFilter                         ,0xffaa09e8) //102
NHSTUB(Read                                   ,0xff81ab78) //120
NHSTUB(ReadFastDir                            ,0xffa84270) //  3
NHSTUB(Rec2PB                                 ,0xff8984a0) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffa0fed8) //104
NHSTUB(RenameFile_Fut                         ,0xff8352a8) //116
NHSTUB(Restart                                ,0xff83ab70) //106
NHSTUB(ScreenLock                             ,0xffa11108) //117
NHSTUB(ScreenUnlock                           ,0xffa11130) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb05970) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8953b8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89cb1c) //120
NHSTUB(SetFileAttributes                      ,0xff835c80) //  3
NHSTUB(SetFileTimeStamp                       ,0xff835c3c) //  3
NHSTUB(SetLogicalEventActive                  ,0xff895094) //101
NHSTUB(SetParameterData                       ,0xff996758) //101
NHSTUB(SetPropertyCase                        ,0xff88d5ac) //102
NHSTUB(SleepTask                              ,0xff8390a0) //120
NHSTUB(TakeSemaphore                          ,0xff838d68) //120
NHSTUB(TurnOffBackLight                       ,0xff8a348c) //104
NHSTUB(TurnOnBackLight                        ,0xff8a3474) //104
NHSTUB(TurnOnDisplay                          ,0xff85a6c4) //120
NHSTUB(TurnOffDisplay                         ,0xff85a6d4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff980560) //120
NHSTUB(UnlockAE                               ,0xff837504) //120
NHSTUB(UnlockAF                               ,0xff837190) //120
NHSTUB(UnlockMainPower                        ,0xff895298) //120
NHSTUB(UnsetZoomForMovie                      ,0xff99ce28) //104
NHSTUB(UpdateMBROnFlash                       ,0xff86fb00) //105
NHSTUB(VbattGet                               ,0xff831e08) //120
NHSTUB(Write                                  ,0xff835a40) //120
NHSTUB(WriteSDCard                            ,0xff94b750) //108
NHSTUB(_log                                   ,0xffb3de8c) //111
NHSTUB(_log10                                 ,0xffb3cdd0) //112
NHSTUB(_pow                                   ,0xffb3cf40) //121
NHSTUB(_sqrt                                  ,0xffb3f1f4) //  1
NHSTUB(add_ptp_handler                        ,0xffa4de90) //121
NHSTUB(apex2us                                ,0xffa148c0) //121
NHSTUB(close                                  ,0xff81a990) //109
NHSTUB(err_init_task                          ,0xff815f28) //111
NHSTUB(exmem_alloc                            ,0xff888138) //103
NHSTUB(exmem_free                             ,0xff8881b0) //103
NHSTUB(free                                   ,0xff814138) //112
NHSTUB(kbd_p1_f                               ,0xff833600) //109
NHSTUB(kbd_p1_f_cont                          ,0xff83360c) //109
NHSTUB(kbd_p2_f                               ,0xff832ec0) //109
NHSTUB(kbd_read_keys                          ,0xff833584) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85fb94) //109
NHSTUB(lseek                                  ,0xff835acc) //120
NHSTUB(malloc                                 ,0xff8140dc) //112
NHSTUB(memcmp                                 ,0xff8203ec) //120
NHSTUB(memcpy                                 ,0xff83ea1c) //120
NHSTUB(memset                                 ,0xffa13910) //120
NHSTUB(mkdir                                  ,0xff835e24) //109
NHSTUB(mktime_ext                             ,0xff8ab050) //  1
NHSTUB(open                                   ,0xff81a8e0) //109
NHSTUB(OpenFastDir                            ,0xffa8413c) //  3
NHSTUB(closedir                               ,0xffa840f8) //  3
NHSTUB(qsort                                  ,0xffaf38dc) //  1
NHSTUB(rand                                   ,0xff8204f4) //121
NHSTUB(realloc                                ,0xffa1398c) //115
NHSTUB(reboot_fw_update                       ,0xffa89780) //106
NHSTUB(set_control_event                      ,0xff894ce8) //111
NHSTUB(srand                                  ,0xff8204e8) //122
NHSTUB(stat                                   ,0xff835b08) //109
NHSTUB(strcat                                 ,0xff8aa80c) //  1
NHSTUB(strchr                                 ,0xff813fc0) //  1
NHSTUB(strcmp                                 ,0xff8203a8) //120
NHSTUB(strcpy                                 ,0xff820390) //120
NHSTUB(strftime                               ,0xff8aaa58) //  1
NHSTUB(strlen                                 ,0xff81400c) //120
NHSTUB(strncmp                                ,0xff813f74) //  1
NHSTUB(strncpy                                ,0xff813f38) //  1
NHSTUB(strrchr                                ,0xff813fe4) //  1
NHSTUB(strtol                                 ,0xff83ecfc) //101
NHSTUB(strtolx                                ,0xff83eb00) //109
   DEF(task_CaptSeq                           ,0xff87b13c) //120
   DEF(task_ExpDrv                            ,0xff8bfba8) //120
   DEF(task_FileWrite                         ,0xffa7fac8) //120
   DEF(task_InitFileModules                   ,0xff898f88) //120
   DEF(task_MovieRecord                       ,0xff962af4) //120
   DEF(task_PhySw                             ,0xff8331f0) //120
   DEF(task_RotaryEncoder                     ,0xff860554) //120
NHSTUB(time                                   ,0xff8877f0) //109
NHSTUB(vsprintf                               ,0xff820354) //115
NHSTUB(EngDrvRead                             ,0xff834448) //102
