// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00D   // Found @ 0xff88e6bc, "GM1.00D" @ 0xff88e6c9
//   Firmware build timestamp: Apr 13 2010 20:05:14
//   Canon IXUS 300 HS

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12791 (0x31f7) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x07ffffff
//   MEMISOSTART = 0x0014b394
//   KEYSYS = d4a                // Found @ 0xffff366c
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff367c
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff97a508
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff97a4c8

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DoAFLock                             ,0xff8382e4) //120        *** != 0xff87a910
//NHSTUB(GetImageFolder                       ,0xff94345c) //122        *** != 0xff94337c
//NHSTUB(MoveFocusLensToDistance              ,0xffb228b0) //102        *** != 0xffb2289c
//NHSTUB(PutInNdFilter                        ,0xffab69c8) //102        *** != 0xffb2056c
//NHSTUB(PutOutNdFilter                       ,0xffab69ec) //102        *** != 0xffb205a4
//NHSTUB(ScreenLock                           ,0xffa13354) //117        *** != 0xffa1356c
//NHSTUB(SetScriptMode                        ,0xff895904) //120        *** != 0xff810f6c
//NHSTUB(UnlockAF                             ,0xff83831c) //120        *** != 0xff87a920
//NHSTUB(kbd_pwr_off                          ,0xff861a14) //  2 60%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffac969c -> ffc0041c
// Mode 33324 in firmware but not in current modemap
// Mode 33323 in firmware but not in current modemap
// Mode 33320 in firmware but not in current modemap
// Mode 33322 in firmware but not in current modemap
// Mode 33321 in firmware but not in current modemap
// Mode 33288 in firmware but not in current modemap
// Mode 33289 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032e94) // Found @0xff8347d4
DEF(physw_run                               ,0x00001c34) // Found @0xff834404
DEF(physw_sleep_delay                       ,0x00001c3c) // Found @0xff834404
DEF(levent_table                            ,0xffb9f59c) // Found @0xffb9f59c
DEF(FlashParamsTable                        ,0xffc00624) // Found @0xffc00624
DEF(movie_status                            ,0x00006a14) // Found @0xff96b418
DEF(video_compression_rate                  ,0x00006a50) // Found @0xff96b978
DEF(full_screen_refresh                     ,0x0000926c) // Found @0xffa11520
DEF(canon_menu_active                       ,0x00003040) // Found @0xff890234
DEF(canon_shoot_menu_active                 ,0x00007b5d) // Found @0xff9abd94
DEF(playrec_mode                            ,0x00002d78) // Found @0xff882334
//DEF(zoom_status                             ,0x0000cea4) // Found @0xffaccb94, ** != ** stubs_min = 0x0000315b (0x315B)
DEF(some_flag_for_af_scan                   ,0x00006dd8) // Found @0xff96e984
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfffe9718) // Found @0xfffe9718
DEF(zoom_busy                               ,0x00006908) // Found @0xff965a0c
DEF(focus_busy                              ,0x000067f0) // Found @0xff961d44
//DEF(recreview_hold                          ,0x00003a20) // Found @0xff8a10dc, ** != ** stubs_min = 0x0000780e (0x780E)
DEF(viewport_buffers                        ,0xffb5e7b8) // Found @0xff84ff60
DEF(active_viewport_buffer                  ,0x0000204c) // Found @0xff84fcfc
// Camera has 2 RAW buffers @ 0x4132c0a0 & 0x46000000
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffb60e94) // Found @0xffb60e94
DEF(active_raw_buffer                       ,0x00002cd8) // Found @0xff87ee00

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff85b150
//void *vid_get_viewport_fb()      { return (void*)0x40587700; }             // Found @0xffb25ed8
DEF(viewport_fb_d                           ,0x00002aa8) // Found 0x2a50 (@0xff873694) + 0x58 (@0xff8736cc)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2a50+0x58)); } // Found @0xff873694 & 0xff8736cc
DEF(jpeg_count_str                          ,0x000a15b8) // Found @0xffa04f80
//char *camera_jpeg_count_str()    { return (char*)0x000a15b8; }             // Found @0xffa04f80
//long hook_raw_size()             { return 0x00f32880; }                    // Found @0xffb292d0
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xff997634

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb5f77c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffb5f784, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_DOWN            ,0x00000001 }, // Found @0xffb5f6bc, levent 0x05
//    { 0, KEY_RIGHT           ,0x00000002 }, // Found @0xffb5f6c4, levent 0x07
//    { 0, KEY_UP              ,0x00000004 }, // Found @0xffb5f6cc, levent 0x04
//    { 0, KEY_LEFT            ,0x00000008 }, // Found @0xffb5f6d4, levent 0x06
//    { 0, KEY_POWER           ,0x00000010 }, // Found @0xffb5f6dc, levent 0x600
//    { 0, KEY_SHOOT_FULL      ,0x00000900 }, // Found @0xffb5f6ec, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000800 }, // Found @0xffb5f6ec, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffb5f6e4, levent 0x00
//    { 0, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffb5f6f4, levent 0x601
//    { 1, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffb5f734, levent 0x02
//    { 1, KEY_ZOOM_OUT        ,0x00000020 }, // Found @0xffb5f73c, levent 0x03
//    { 1, KEY_SET             ,0x00000040 }, // Found @0xffb5f744, levent 0x08
//    { 1, KEY_MENU            ,0x00000080 }, // Found @0xffb5f74c, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3816 // Found @0xff93c408
//#define CAM_RAW_ROWS      2784 // Found @0xff93c414
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83a460

// Misc stuff
DEF(ctypes, 0xffb5e23a)

// For capt_seq.c
DEF(_nrflag,0x6db0) // Found @ ff970b1c (0x6db8) & ff970b3c (-0x08)
//static long *nrflag = (long*)(0x6db8-0x08);  // Found @ ff970b1c & ff970b38

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83a41c) //112
NHSTUB(Close                                  ,0xff836db8) //120
NHSTUB(CreateTask                             ,0xff81e83c) //120
NHSTUB(DebugAssert                            ,0xff81eb14) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff836814) //116
NHSTUB(DeleteFile_Fut                         ,0xff836730) //112
NHSTUB(DoAELock                               ,0xff8384dc) //120
NHSTUB(EnterToCompensationEVF                 ,0xff8383e4) //104
NHSTUB(ExecuteEventProcedure                  ,0xff88b948) //104
NHSTUB(ExitFromCompensationEVF                ,0xff838428) //104
NHSTUB(ExitTask                               ,0xff81eacc) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff8462a0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff846378) //104
NHSTUB(Fclose_Fut                             ,0xff8368ac) //120
NHSTUB(Feof_Fut                               ,0xff836a98) //  1
NHSTUB(Fflush_Fut                             ,0xff836ad4) //  1
NHSTUB(Fgets_Fut                              ,0xff836a00) //  1
NHSTUB(Fopen_Fut                              ,0xff83686c) //120
NHSTUB(Fread_Fut                              ,0xff836958) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83a45c) //112
NHSTUB(Fseek_Fut                              ,0xff836a4c) //120
NHSTUB(Fwrite_Fut                             ,0xff8369ac) //120
NHSTUB(GetBatteryTemperature                  ,0xff8652a0) //102
NHSTUB(GetCCDTemperature                      ,0xff86522c) //102
NHSTUB(GetCurrentAvValue                      ,0xff9644f8) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff871e30) //122
//NHSTUB(GetDrive_FreeClusters                ,0xff871e90) //  4            == 0xff871e90
NHSTUB(GetDrive_TotalClusters                 ,0xff871e64) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff9629b8) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff962d40) //  3
NHSTUB(GetKbdState                            ,0xff861908) //109
NHSTUB(GetMemInfo                             ,0xff81a16c) //115
NHSTUB(GetOpticalTemperature                  ,0xff865314) //120
NHSTUB(GetParameterData                       ,0xff9975f4) //101
NHSTUB(GetPropertyCase                        ,0xff88f660) //102
NHSTUB(GetSystemTime                          ,0xffab8d48) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff851900) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff85190c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff965e54) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaa9298) //102
NHSTUB(GiveSemaphore                          ,0xff839e38) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8da44c) //102
NHSTUB(LEDDrive                               ,0xff860c6c) //120
NHSTUB(LocalTime                              ,0xff88923c) //115
NHSTUB(LockMainPower                          ,0xff895b78) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8367a4) //116
NHSTUB(MoveIrisWithAv                         ,0xffab6408) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffab6b64) //120
NHSTUB(Open                                   ,0xff836d4c) //120
NHSTUB(PB2Rec                                 ,0xff898b40) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff87a8c0) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff87a898) //120
NHSTUB(PT_PlaySound                           ,0xff8840b8) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff893948) //120
NHSTUB(PostLogicalEventToUI                   ,0xff893994) //120
NHSTUB(Read                                   ,0xff81ac7c) //120
NHSTUB(ReadFastDir                            ,0xffa95de4) //  4
NHSTUB(Rec2PB                                 ,0xff897590) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffa12124) //104
NHSTUB(RenameFile_Fut                         ,0xff83669c) //116
NHSTUB(Restart                                ,0xff83bbfc) //106
NHSTUB(ScreenUnlock                           ,0xffa13398) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb2504c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff895bec) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89e550) //120
NHSTUB(SetFileAttributes                      ,0xff8370b0) //  3
NHSTUB(SetFileTimeStamp                       ,0xff837054) //  4
NHSTUB(SetLogicalEventActive                  ,0xff8958b4) //101
NHSTUB(SetParameterData                       ,0xff997564) //101
NHSTUB(SetPropertyCase                        ,0xff88f530) //102
NHSTUB(SleepTask                              ,0xff83a0a0) //120
NHSTUB(TakeSemaphore                          ,0xff839d68) //120
NHSTUB(TurnOffBackLight                       ,0xff8a4980) //104
NHSTUB(TurnOnBackLight                        ,0xff8a4968) //104
NHSTUB(TurnOnDisplay                          ,0xff85b4e8) //120
NHSTUB(TurnOffDisplay                         ,0xff85b4f8) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff984ab4) //120
NHSTUB(UnlockAE                               ,0xff838500) //120
NHSTUB(UnlockMainPower                        ,0xff895acc) //120
NHSTUB(UpdateMBROnFlash                       ,0xff871cb0) //105
NHSTUB(VbattGet                               ,0xff8330d8) //120
NHSTUB(Write                                  ,0xff836e48) //120
NHSTUB(WriteSDCard                            ,0xff952494) //108
NHSTUB(_log                                   ,0xffb5b348) //111
NHSTUB(_log10                                 ,0xffb59fd4) //112
NHSTUB(_pow                                   ,0xffb5a144) //121
NHSTUB(_sqrt                                  ,0xffb5cf50) //  1
NHSTUB(add_ptp_handler                        ,0xffa4eabc) //121
NHSTUB(apex2us                                ,0xffa16da4) //121
NHSTUB(close                                  ,0xff81aa94) //109
NHSTUB(err_init_task                          ,0xff815f4c) //111
NHSTUB(exmem_alloc                            ,0xff88a17c) //103
NHSTUB(exmem_free                             ,0xff88a1f4) //103
NHSTUB(free                                   ,0xff81415c) //112
NHSTUB(kbd_p1_f                               ,0xff83484c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff834858) //109
NHSTUB(kbd_p2_f                               ,0xff8340d0) //109
NHSTUB(kbd_read_keys                          ,0xff8347d4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff86122c) //109
NHSTUB(lseek                                  ,0xff836ed4) //120
NHSTUB(malloc                                 ,0xff814100) //112
NHSTUB(memcmp                                 ,0xff82066c) //120
NHSTUB(memcpy                                 ,0xff83fae8) //120
NHSTUB(memset                                 ,0xffa15ddc) //120
NHSTUB(mkdir                                  ,0xff837254) //109
NHSTUB(mktime_ext                             ,0xff8ac9f0) //  1
NHSTUB(open                                   ,0xff81a9e4) //109
NHSTUB(OpenFastDir                            ,0xffa95c90) //  4
NHSTUB(closedir                               ,0xffa95c40) //121
NHSTUB(qsort                                  ,0xffb0b1f8) //  4
NHSTUB(rand                                   ,0xff820774) //121
NHSTUB(realloc                                ,0xffa15e58) //115
NHSTUB(reboot_fw_update                       ,0xffa9b228) //106
NHSTUB(set_control_event                      ,0xff895504) //111
NHSTUB(srand                                  ,0xff820768) //122
NHSTUB(stat                                   ,0xff836f1c) //109
NHSTUB(strcat                                 ,0xff8ac1ac) //  1
NHSTUB(strchr                                 ,0xff813fe4) //  1
NHSTUB(strcmp                                 ,0xff820628) //120
NHSTUB(strcpy                                 ,0xff820610) //120
NHSTUB(strftime                               ,0xff8ac3f8) //113
NHSTUB(strlen                                 ,0xff814030) //120
NHSTUB(strncmp                                ,0xff813f98) //  1
NHSTUB(strncpy                                ,0xff813f5c) //  1
NHSTUB(strrchr                                ,0xff814008) //  1
NHSTUB(strtol                                 ,0xff83fdc8) //101
NHSTUB(strtolx                                ,0xff83fbcc) //109
   DEF(task_CaptSeq                           ,0xff87d2d8) //120
   DEF(task_ExpDrv                            ,0xff8c25dc) //120
   DEF(task_FileWrite                         ,0xffa908bc) //120
   DEF(task_InitFileModules                   ,0xff8995e0) //120
   DEF(task_MovieRecord                       ,0xff96bd30) //120
   DEF(task_PhySw                             ,0xff834400) //120
   DEF(task_RotaryEncoder                     ,0xff861b68) //120
NHSTUB(time                                   ,0xff88981c) //109
NHSTUB(vsprintf                               ,0xff8205d4) //115
NHSTUB(EngDrvRead                             ,0xff8356a0) //102
