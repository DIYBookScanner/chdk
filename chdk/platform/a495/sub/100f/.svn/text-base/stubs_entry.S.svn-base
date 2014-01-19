// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00F   // Found @ 0xffc685d8, "GM1.00F" @ 0xffc685e5
//   Firmware build timestamp: Mar 26 2010 15:04:27
//   Canon PowerShot A495

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12783 (0x31ef) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00128e90
//   KEYSYS = d4a                // Found @ 0xffff1a2c
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff1a3c
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd1834c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd1830c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(SetScriptMode                        ,0xffc6cc58) //120        *** != 0xffc00f70
NHSTUB(kbd_pwr_off                            ,0xffc435e4) //  2 64%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe0aa64 -> ffecf6a0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002e7f4) // Found @0xffc23b2c
DEF(physw_run                               ,0x00001bf0) // Found @0xffc23790
DEF(physw_sleep_delay                       ,0x00001bf8) // Found @0xffc23790
DEF(levent_table                            ,0xffea2d14) // Found @0xffea2d14
DEF(FlashParamsTable                        ,0xffecf894) // Found @0xffecf894
DEF(movie_status                            ,0x000054a0) // Found @0xffd0c7d8
DEF(full_screen_refresh                     ,0x00007370) // Found @0xffd7aa20
DEF(canon_menu_active                       ,0x00002a3c) // Found @0xffc6a11c
DEF(canon_shoot_menu_active                 ,0x000065b5) // Found @0xffd40144
DEF(playrec_mode                            ,0x00002798) // Found @0xffc5d900
DEF(zoom_status                             ,0x00009648) // Found @0xffe0d940
DEF(some_flag_for_af_scan                   ,0x00005848) // Found @0xffd0f144
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe2990) // Found @0xfffe2990
DEF(zoom_busy                               ,0x00005424) // Found @0xffd09a08
DEF(focus_busy                              ,0x00005334) // Found @0xffd07040
//DEF(recreview_hold                          ,0x00003034) // Found @0xffc75924, ** != ** stubs_min = 0x0000630a (0x6308+2)
DEF(viewport_buffers                        ,0xffe8bd3c) // Found @0xffcb586c
DEF(active_viewport_buffer                  ,0x00004110) // Found @0xffcb56b4
// Camera appears to have only 1 RAW buffer @ 0x10e52420 (Found @0xffe59d04)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3f020
//void *vid_get_viewport_fb()      { return (void*)0x10648cc0; }             // Found @0xffe569d8
DEF(viewport_fb_d                           ,0x00002594) // Found 0x2540 (@0xffc52918) + 0x54 (@0xffc52950)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2540+0x54)); } // Found @0xffc52918 & 0xffc52950
DEF(jpeg_count_str                          ,0x0007486c) // Found @0xffd72050
//char *camera_jpeg_count_str()    { return (char*)0x0007486c; }             // Found @0xffd72050
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe59d60
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd2f2a0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00040000 // Found @0xffe84f40, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffe84f4c, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x00020000 }, // Found @0xffe84ebc, levent 0x601
//    { 0, KEY_POWER           ,0x00800000 }, // Found @0xffe84ed4, levent 0x600
//    { 2, KEY_RIGHT           ,0x00000004 }, // Found @0xffe84ee0, levent 0x07
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe84ef8, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe84ef8, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe84eec, levent 0x00
//    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffe84f04, levent 0x03
//    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffe84f10, levent 0x02
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe84f1c, levent 0x08
//    { 2, KEY_UP              ,0x00100000 }, // Found @0xffe84f58, levent 0x04 (uses inverted logic in physw_status)
//    { 2, KEY_DOWN            ,0x00200000 }, // Found @0xffe84f64, levent 0x05 (uses inverted logic in physw_status)
//    { 2, KEY_LEFT            ,0x00400000 }, // Found @0xffe84f70, levent 0x06 (uses inverted logic in physw_status)
//    { 2, KEY_MENU            ,0x01000000 }, // Found @0xffe84f88, levent 0x09 (uses inverted logic in physw_status)
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcea4b8
//#define CAM_RAW_ROWS      2772 // Found @0xffcea4c4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc2931c

// Misc stuff
DEF(ctypes, 0xffe847da)

// For capt_seq.c
DEF(_nrflag,0x5828) // Found @ ffd10f5c (0x5830) & ffd10f7c (-0x08)
//static long *nrflag = (long*)(0x5830-0x08);  // Found @ ffd10f5c & ffd10f78

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc292d8) //112
NHSTUB(Close                                  ,0xffc26108) //120
NHSTUB(CreateTask                             ,0xffc0f1a8) //120
NHSTUB(DebugAssert                            ,0xffc0f680) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc25b64) //116
NHSTUB(DeleteFile_Fut                         ,0xffc25a80) //112
NHSTUB(DoAELock                               ,0xffc2769c) //120
NHSTUB(DoAFLock                               ,0xffc27554) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc27604) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc65870) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc27648) //104
NHSTUB(ExitTask                               ,0xffc0f438) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc34ce4) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc34dbc) //104
NHSTUB(Fclose_Fut                             ,0xffc25bfc) //120
NHSTUB(Feof_Fut                               ,0xffc25de8) //  1
NHSTUB(Fflush_Fut                             ,0xffc25e24) //  1
NHSTUB(Fgets_Fut                              ,0xffc25d50) //  1
NHSTUB(Fopen_Fut                              ,0xffc25bbc) //120
NHSTUB(Fread_Fut                              ,0xffc25ca8) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc29318) //112
NHSTUB(Fseek_Fut                              ,0xffc25d9c) //120
NHSTUB(Fwrite_Fut                             ,0xffc25cfc) //120
NHSTUB(GetBatteryTemperature                  ,0xffc4561c) //102
NHSTUB(GetCCDTemperature                      ,0xffc455a8) //102
NHSTUB(GetCurrentAvValue                      ,0xffd088c0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc512c0) //122
NHSTUB(GetDrive_FreeClusters                  ,0xffc51320) //  4
NHSTUB(GetDrive_TotalClusters                 ,0xffc512f4) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xffd07bb8) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd08010) //  3
NHSTUB(GetImageFolder                         ,0xffcf1478) //122
NHSTUB(GetKbdState                            ,0xffc435cc) //109
NHSTUB(GetMemInfo                             ,0xffc0a7f8) //115
NHSTUB(GetOpticalTemperature                  ,0xffc45694) //120
NHSTUB(GetParameterData                       ,0xffd2f260) //101
NHSTUB(GetPropertyCase                        ,0xffc6957c) //102
NHSTUB(GetSystemTime                          ,0xffdfd1c4) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcb6ca4) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcb6cb0) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd09d80) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdf5210) //102
NHSTUB(GiveSemaphore                          ,0xffc0f104) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffca72b0) //102
NHSTUB(LEDDrive                               ,0xffc42bc4) //120
NHSTUB(LocalTime                              ,0xffc63580) //115
NHSTUB(LockMainPower                          ,0xffc6ce90) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc25af4) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe53458) //102
NHSTUB(MoveIrisWithAv                         ,0xffdfa8b4) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdfae44) //120
NHSTUB(Open                                   ,0xffc2609c) //120
NHSTUB(PB2Rec                                 ,0xffc6fae4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc571c0) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc57198) //120
NHSTUB(PT_PlaySound                           ,0xffc5f400) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6c6c0) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc6c70c) //120
NHSTUB(PutInNdFilter                          ,0xffdfaca8) //102
NHSTUB(PutOutNdFilter                         ,0xffdfaccc) //102
NHSTUB(Read                                   ,0xffc0b308) //120
NHSTUB(ReadFastDir                            ,0xffdebbf8) //  4
NHSTUB(Rec2PB                                 ,0xffc6fb24) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd7b3fc) //104
NHSTUB(RenameFile_Fut                         ,0xffc259ec) //116
NHSTUB(Restart                                ,0xffc2aab0) //106
NHSTUB(ScreenLock                             ,0xffd7c5a8) //117
NHSTUB(ScreenUnlock                           ,0xffd7c5ec) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffe55be8) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc6cf04) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc7323c) //120
NHSTUB(SetFileAttributes                      ,0xffc26400) //  3
NHSTUB(SetFileTimeStamp                       ,0xffc263a4) //  4
NHSTUB(SetLogicalEventActive                  ,0xffc6cc08) //101
NHSTUB(SetParameterData                       ,0xffd2f1d0) //101
NHSTUB(SetPropertyCase                        ,0xffc6944c) //102
NHSTUB(SleepTask                              ,0xffc2915c) //120
NHSTUB(TakeSemaphore                          ,0xffc0f034) //120
NHSTUB(TurnOffBackLight                       ,0xffc77f9c) //104
NHSTUB(TurnOnBackLight                        ,0xffc77f84) //104
NHSTUB(TurnOnDisplay                          ,0xffc3f2fc) //120
NHSTUB(TurnOffDisplay                         ,0xffc3f328) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd1f9d4) //120
NHSTUB(UnlockAE                               ,0xffc276c0) //120
NHSTUB(UnlockAF                               ,0xffc2758c) //120
NHSTUB(UnlockMainPower                        ,0xffc6cde4) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3594c) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc51140) //105
NHSTUB(VbattGet                               ,0xffc22be4) //120
NHSTUB(Write                                  ,0xffc26198) //120
NHSTUB(WriteSDCard                            ,0xffcfcbcc) //108
NHSTUB(_log                                   ,0xffe8233c) //111
NHSTUB(_log10                                 ,0xffe81280) //112
NHSTUB(_pow                                   ,0xffe813f0) //121
NHSTUB(_sqrt                                  ,0xffe836a4) //  1
NHSTUB(add_ptp_handler                        ,0xffdbeb58) //121
NHSTUB(apex2us                                ,0xffd7d8f8) //121
NHSTUB(close                                  ,0xffc0b120) //109
NHSTUB(err_init_task                          ,0xffc05f50) //111
NHSTUB(exmem_alloc                            ,0xffc64220) //103
NHSTUB(exmem_free                             ,0xffc64298) //103
NHSTUB(free                                   ,0xffc04160) //112
NHSTUB(kbd_p1_f                               ,0xffc23ba4) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc23bb0) //109
NHSTUB(kbd_p2_f                               ,0xffc2345c) //109
NHSTUB(kbd_read_keys                          ,0xffc23b2c) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc42fb0) //109
NHSTUB(lseek                                  ,0xffc26224) //120
NHSTUB(malloc                                 ,0xffc04104) //112
NHSTUB(memcmp                                 ,0xffc11318) //120
NHSTUB(memcpy                                 ,0xffc2e860) //120
NHSTUB(memset                                 ,0xffd7c930) //120
NHSTUB(mkdir                                  ,0xffc265a4) //109
NHSTUB(mktime_ext                             ,0xffc7cdbc) //  1
NHSTUB(open                                   ,0xffc0b070) //109
NHSTUB(OpenFastDir                            ,0xffdebaa4) //  4
NHSTUB(closedir                               ,0xffdeba54) //121
NHSTUB(qsort                                  ,0xffe3c194) //  4
NHSTUB(rand                                   ,0xffc11420) //121
NHSTUB(realloc                                ,0xffd7c9ac) //115
NHSTUB(reboot_fw_update                       ,0xffded46c) //106
NHSTUB(set_control_event                      ,0xffc6c928) //111
NHSTUB(srand                                  ,0xffc11414) //122
NHSTUB(stat                                   ,0xffc2626c) //109
NHSTUB(strcat                                 ,0xffc7c578) //  1
NHSTUB(strchr                                 ,0xffc03fe8) //  1
NHSTUB(strcmp                                 ,0xffc112d4) //120
NHSTUB(strcpy                                 ,0xffc112bc) //120
NHSTUB(strftime                               ,0xffc7c7c4) //113
NHSTUB(strlen                                 ,0xffc04034) //120
NHSTUB(strncmp                                ,0xffc03f9c) //  1
NHSTUB(strncpy                                ,0xffc03f60) //  1
NHSTUB(strrchr                                ,0xffc0400c) //  1
NHSTUB(strtol                                 ,0xffc2eb40) //101
NHSTUB(strtolx                                ,0xffc2e944) //109
   DEF(task_CaptSeq                           ,0xffc59274) //120
   DEF(task_ExpDrv                            ,0xffc91654) //120
   DEF(task_FileWrite                         ,0xffde66d0) //120
   DEF(task_InitFileModules                   ,0xffc705ac) //120
   DEF(task_MovieRecord                       ,0xffd0ca2c) //120
   DEF(task_PhySw                             ,0xffc2378c) //120
NHSTUB(time                                   ,0xffc63434) //109
NHSTUB(vsprintf                               ,0xffc11280) //115
NHSTUB(EngDrvRead                             ,0xffc249f8) //102
