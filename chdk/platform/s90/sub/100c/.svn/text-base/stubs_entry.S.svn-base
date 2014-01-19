// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R39 (DRYOS version 2.3, release #0039)
//   Firmware Ver GM1.00C   // Found @ 0xff88bb58, "GM1.00C" @ 0xff88bb65
//   Firmware build timestamp: Sep  3 2009 09:36:41
//   Canon PowerShot S90

// Values for makefile.inc
//   PLATFORMOSVER = 39
//   PLATFORMID = 12769 (0x31e1) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00141dbc
//   KEYSYS = d4                 // Found @ 0xffff3564
//   NEED_ENCODED_DISKBOOT = 3   // Found @ 0xffff3574
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff96fd1c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff96fcdc

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(SetScriptMode                        ,0xff89441c) //120        *** != 0xff810f4c
//NHSTUB(kbd_pwr_off                          ,0xff85e3a4) //  2 60%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffaae880 -> ffbef980
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000330d8) // Found @0xff8335b4
DEF(physw_run                               ,0x00001c44) // Found @0xff83320c
DEF(physw_sleep_delay                       ,0x00001c42) // Found @0xff83320c
DEF(levent_table                            ,0xffb8b470) // Found @0xffb8b470
DEF(FlashParamsTable                        ,0xffbefb70) // Found @0xffbefb70
DEF(movie_status                            ,0x00007ae8) // Found @0xff961448
DEF(video_compression_rate                  ,0x00007b14) // Found @0xff9616b0
DEF(full_screen_refresh                     ,0x0000a36c) // Found @0xffa07d74
//DEF(canon_menu_active                       ,0x00003038) // Found @0xff88d630,          stubs_min = 0x00003038 (0x3034+4)
//DEF(canon_shoot_menu_active                 ,0x00008dd1) // Found @0xff9ab74c, ** != ** stubs_min = 0x00008945 (0x8944+1)
DEF(playrec_mode                            ,0x00002d64) // Found @0xff87f9f4
DEF(zoom_status                             ,0x00008aa4) // Found @0xff99bb20
DEF(some_flag_for_af_scan                   ,0x00007ff4) // Found @0xff9644d8
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 10 entries in the table - set NUM_FL to 10
DEF(focus_len_table                         ,0xfffe2af8) // Found @0xfffe2af8
//DEF(zoom_busy                               ,0x00007a14) // Found @0xff95d678,          stubs_min = 0x00007a14 (0x7a00+0x14)
//DEF(focus_busy                              ,0x000078dc) // Found @0xff957bb0,          stubs_min = 0x000078dc (0x78d4+8)
//DEF(recreview_hold                          ,0x00003a94) // Found @0xff89e690, ** != ** stubs_min = 0x00008a28 (0x8944+0xE4)
// Palette colour tables  found @ 0xffba53b4
DEF(active_palette_buffer                   ,0x0000a374) // Found @0xffa07cb4
DEF(palette_buffer_ptr                      ,0x0000a380) // Found @0xffa07988
// Offset from start of palette_buffer to color data = 8 (Found @0xffae54a8)
// Camera appears to have only 1 RAW buffer @ 0x4213a6ec (Found @0xffb0254c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff858728
//void *vid_get_viewport_fb()      { return (void*)0x407e8a00; }             // Found @0xffaff2dc
DEF(viewport_fb_d                           ,0x00002a78) // Found 0x2a20 (@0xff86f9f8) + 0x58 (@0xff86fa30)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2a20+0x58)); } // Found @0xff86f9f8 & 0xff86fa30
DEF(jpeg_count_str                          ,0x0009792c) // Found @0xff9fbf38
//char *camera_jpeg_count_str()    { return (char*)0x0009792c; }             // Found @0xff9fbf38
//long hook_raw_size()             { return 0x00ee9200; }                    // Found @0xffb025a8
//int get_flash_params_count(void) { return 0x85; }                          // Found @0xff994abc

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb3aa50, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00200000 // Found @0xffb3aa68, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffb3a93c, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffb3a93c, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffb3a930, levent 0x00
//    { 0, KEY_POWER           ,0x00000400 }, // Found @0xffb3a948, levent 0x600
//    { 0, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffb3a954, levent 0x601
//    { 1, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffb3a9b4, levent 0x02
//    { 1, KEY_ZOOM_OUT        ,0x00000020 }, // Found @0xffb3a9c0, levent 0x03
//    { 1, KEY_LEFT            ,0x00000100 }, // Found @0xffb3a9e4, levent 0x06
//    { 1, KEY_RIGHT           ,0x00000200 }, // Found @0xffb3a9f0, levent 0x07
//    { 1, KEY_DOWN            ,0x00000400 }, // Found @0xffb3a9fc, levent 0x05
//    { 1, KEY_DISPLAY         ,0x00001000 }, // Found @0xffb3aa14, levent 0x0a
//    { 1, KEY_MENU            ,0x00002000 }, // Found @0xffb3aa20, levent 0x09
//    { 1, KEY_UP              ,0x00004000 }, // Found @0xffb3aa2c, levent 0x04
//    { 1, KEY_SET             ,0x00008000 }, // Found @0xffb3aa38, levent 0x08
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3744 // Found @0xff9345cc
//#define CAM_RAW_ROWS      2784 // Found @0xff9345d4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff838e10

// Misc stuff
DEF(ctypes, 0xffb39372)

// For capt_seq.c
DEF(_nrflag,0x7fd0) // Found @ ff966940 (0x7fd8) & ff966960 (-0x08)
//static long *nrflag = (long*)(0x7fd8-0x08);  // Found @ ff966940 & ff96695c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff838dcc) //112
NHSTUB(Close                                  ,0xff835414) //120
NHSTUB(CreateTask                             ,0xff81e5b4) //120
NHSTUB(DebugAssert                            ,0xff81e88c) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff834e84) //116
NHSTUB(DeleteFile_Fut                         ,0xff834da0) //112
NHSTUB(DoAELock                               ,0xff836de0) //120
NHSTUB(DoAFLock                               ,0xff836b98) //120
NHSTUB(EnterToCompensationEVF                 ,0xff836d3c) //104
NHSTUB(ExecuteEventProcedure                  ,0xff888cfc) //104
NHSTUB(ExitFromCompensationEVF                ,0xff836d80) //104
NHSTUB(ExitTask                               ,0xff81e844) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff844700) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff8447d8) //104
NHSTUB(Fclose_Fut                             ,0xff834f1c) //120
NHSTUB(Feof_Fut                               ,0xff835108) //  1
NHSTUB(Fflush_Fut                             ,0xff835144) //  1
NHSTUB(Fgets_Fut                              ,0xff835070) //  1
NHSTUB(Fopen_Fut                              ,0xff834edc) //120
NHSTUB(Fread_Fut                              ,0xff834fc8) //120
NHSTUB(FreeUncacheableMemory                  ,0xff838e0c) //112
NHSTUB(Fseek_Fut                              ,0xff8350bc) //120
NHSTUB(Fwrite_Fut                             ,0xff83501c) //120
NHSTUB(GetBatteryTemperature                  ,0xff8615f0) //102
NHSTUB(GetCCDTemperature                      ,0xff86157c) //102
NHSTUB(GetCurrentAvValue                      ,0xff95a354) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86e380) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86e3e0) //  3
NHSTUB(GetDrive_TotalClusters                 ,0xff86e3b4) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff958928) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff958d70) //  3
NHSTUB(GetImageFolder                         ,0xff93c458) //122
NHSTUB(GetKbdState                            ,0xff85e258) //109
NHSTUB(GetMemInfo                             ,0xff81a070) //115
NHSTUB(GetOpticalTemperature                  ,0xff861664) //120
NHSTUB(GetParameterData                       ,0xff994a7c) //101
//NHSTUB(GetPropertyCase                      ,0xff88ca64) //102            == 0xff88ca64
NHSTUB(GetSystemTime                          ,0xffa9d1c0) //120
//NHSTUB(GetVRAMHPixelsSize                   ,0xff84f110) //120            == 0xff84f110
//NHSTUB(GetVRAMVPixelsSize                   ,0xff84f11c) //120            == 0xff84f11c
NHSTUB(GetZoomLensCurrentPoint                ,0xff95d9ec) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa90e0c) //102
NHSTUB(GiveSemaphore                          ,0xff8387e8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8d8710) //102
NHSTUB(LEDDrive                               ,0xff85d648) //120
NHSTUB(LocalTime                              ,0xff886670) //115
NHSTUB(LockMainPower                          ,0xff89467c) //120
NHSTUB(MakeDirectory_Fut                      ,0xff834e14) //116
NHSTUB(MoveFocusLensToDistance                ,0xffafbcf0) //102
NHSTUB(MoveIrisWithAv                         ,0xffa9ab34) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa9b1a8) //120
NHSTUB(Open                                   ,0xff8353bc) //120
NHSTUB(PB2Rec                                 ,0xff8977c4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8776dc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff8776b4) //120
NHSTUB(PT_PlaySound                           ,0xff88180c) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff8924a8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8924f4) //120
NHSTUB(PutInNdFilter                          ,0xffaf9a40) //102
NHSTUB(PutOutNdFilter                         ,0xffaf9a78) //102
NHSTUB(Read                                   ,0xff81ab78) //120
NHSTUB(ReadFastDir                            ,0xffa7d748) //  3
NHSTUB(Rec2PB                                 ,0xff897804) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffa08eec) //104
NHSTUB(RenameFile_Fut                         ,0xff834d0c) //116
NHSTUB(Restart                                ,0xff83a520) //106
NHSTUB(ScreenLock                             ,0xffa0a10c) //117
NHSTUB(ScreenUnlock                           ,0xffa0a134) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffafe49c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8946f0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89b7b4) //120
NHSTUB(SetFileAttributes                      ,0xff8356e4) //  3
NHSTUB(SetFileTimeStamp                       ,0xff8356a0) //  3
NHSTUB(SetLogicalEventActive                  ,0xff8943cc) //101
NHSTUB(SetParameterData                       ,0xff994958) //101
NHSTUB(SetPropertyCase                        ,0xff88c960) //102
NHSTUB(SleepTask                              ,0xff838a50) //120
NHSTUB(TakeSemaphore                          ,0xff838718) //120
NHSTUB(TurnOffBackLight                       ,0xff8a494c) //104
NHSTUB(TurnOnBackLight                        ,0xff8a4934) //104
NHSTUB(TurnOnDisplay                          ,0xff85892c) //120
NHSTUB(TurnOffDisplay                         ,0xff85893c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff97ea00) //120
NHSTUB(UnlockAE                               ,0xff836e04) //120
NHSTUB(UnlockAF                               ,0xff836bd0) //120
NHSTUB(UnlockMainPower                        ,0xff8945d0) //120
NHSTUB(UnsetZoomForMovie                      ,0xff8a0eb4) //104
NHSTUB(UpdateMBROnFlash                       ,0xff86e200) //105
NHSTUB(VbattGet                               ,0xff831e04) //120
NHSTUB(Write                                  ,0xff8354a4) //120
NHSTUB(WriteSDCard                            ,0xff94a55c) //108
NHSTUB(_log                                   ,0xffb365f8) //111
NHSTUB(_log10                                 ,0xffb35284) //112
NHSTUB(_pow                                   ,0xffb353f4) //121
NHSTUB(_sqrt                                  ,0xffb3819c) //  1
NHSTUB(add_ptp_handler                        ,0xffa46fc0) //121
NHSTUB(apex2us                                ,0xffa0d7a8) //121
NHSTUB(close                                  ,0xff81a990) //109
NHSTUB(err_init_task                          ,0xff815f28) //111
NHSTUB(exmem_alloc                            ,0xff887530) //103
NHSTUB(exmem_free                             ,0xff8875a8) //103
NHSTUB(free                                   ,0xff814138) //112
NHSTUB(kbd_p1_f                               ,0xff833630) //109
NHSTUB(kbd_p1_f_cont                          ,0xff83363c) //109
NHSTUB(kbd_p2_f                               ,0xff832ed8) //109
NHSTUB(kbd_read_keys                          ,0xff8335b4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85db5c) //109
NHSTUB(lseek                                  ,0xff835530) //120
NHSTUB(malloc                                 ,0xff8140dc) //112
NHSTUB(memcmp                                 ,0xff8203e8) //120
NHSTUB(memcpy                                 ,0xff83e43c) //120
NHSTUB(memset                                 ,0xffa0c7f8) //120
NHSTUB(mkdir                                  ,0xff835888) //109
NHSTUB(mktime_ext                             ,0xff8ac304) //  1
NHSTUB(open                                   ,0xff81a8e0) //109
NHSTUB(OpenFastDir                            ,0xffa7d614) //  3
NHSTUB(closedir                               ,0xffa7d5d0) //  3
NHSTUB(qsort                                  ,0xffaec3d8) //  1
NHSTUB(rand                                   ,0xff8204f0) //121
NHSTUB(realloc                                ,0xffa0c874) //115
NHSTUB(reboot_fw_update                       ,0xffa82c58) //106
NHSTUB(set_control_event                      ,0xff894020) //111
NHSTUB(srand                                  ,0xff8204e4) //122
NHSTUB(stat                                   ,0xff83556c) //109
NHSTUB(strcat                                 ,0xff8abac0) //  1
NHSTUB(strchr                                 ,0xff813fc0) //  1
NHSTUB(strcmp                                 ,0xff8203a4) //120
NHSTUB(strcpy                                 ,0xff82038c) //120
NHSTUB(strftime                               ,0xff8abd0c) //  1
NHSTUB(strlen                                 ,0xff81400c) //120
NHSTUB(strncmp                                ,0xff813f74) //  1
NHSTUB(strncpy                                ,0xff813f38) //  1
NHSTUB(strrchr                                ,0xff813fe4) //  1
NHSTUB(strtol                                 ,0xff83e71c) //101
NHSTUB(strtolx                                ,0xff83e520) //109
   DEF(task_CaptSeq                           ,0xff87a208) //120
   DEF(task_ExpDrv                            ,0xff8c0e54) //120
   DEF(task_FileWrite                         ,0xffa78fa0) //120
   DEF(task_InitFileModules                   ,0xff8982e8) //120
   DEF(task_MovieRecord                       ,0xff96172c) //120
   DEF(task_PhySw                             ,0xff833208) //120
   DEF(task_RotaryEncoder                     ,0xff85e508) //120
NHSTUB(time                                   ,0xff886be8) //109
NHSTUB(vsprintf                               ,0xff820350) //115
NHSTUB(EngDrvRead                             ,0xff834478) //102
