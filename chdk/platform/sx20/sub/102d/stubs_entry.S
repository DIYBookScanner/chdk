// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R39 (DRYOS version 2.3, release #0039)
//   Firmware Ver GM1.02D   // Found @ 0xff88e430, "GM1.02D" @ 0xff88e43d
//   Firmware build timestamp: Mar  9 2010 10:00:57
//   Canon PowerShot SX20 IS

// Values for makefile.inc
//   PLATFORMOSVER = 39
//   PLATFORMID = 12772 (0x31e4) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0013dd6c
//   KEYSYS = d4                 // Found @ 0xffff35a0
//   NEED_ENCODED_DISKBOOT = 3   // Found @ 0xffff35b0
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff96b28c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff96b24c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DoAFLock                             ,0xff836a9c) //120        *** != 0xff879704
//NHSTUB(TurnOffBackLight                     ,0xff8a5b30) //104        *** != 0xff89b6f4
//NHSTUB(UIFS_WriteFirmInfoToFile             ,0xff979b78) //120        *** != 0xdeadc0de
//NHSTUB(UnlockAF                             ,0xff836b38) //120        *** != 0xff879714
//NHSTUB(VbattGet                             ,0xff831cec) //120        *** != 0xff95d27c
//NHSTUB(kbd_pwr_off                          ,0xff85f2c4) //  2 60%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffaac914 -> ffbe87b4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032464) // Found @0xff83341c
DEF(physw_run                               ,0x00001c44) // Found @0xff83308c
DEF(physw_sleep_delay                       ,0x00001c42) // Found @0xff83308c
DEF(levent_table                            ,0xffba33a8) // Found @0xffba33a8
DEF(FlashParamsTable                        ,0xffbe899c) // Found @0xffbe899c
DEF(movie_status                            ,0x00002c30) // Found @0xff878e00
DEF(video_compression_rate                  ,0x00002c5c) // Found @0xff879008
DEF(full_screen_refresh                     ,0x00009cf4) // Found @0xffa02778
DEF(canon_menu_active                       ,0x0000312c) // Found @0xff88fee0
DEF(canon_shoot_menu_active                 ,0x00008845) // Found @0xff9aa1e4
DEF(playrec_mode                            ,0x00002e58) // Found @0xff882278
DEF(zoom_status                             ,0x0000c6c0) // Found @0xffaaf648
DEF(some_flag_for_af_scan                   ,0x00007934) // Found @0xff95fd00
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 1 int value, which is the the zoom focus length.
// there are 6 entries in the table - set NUM_FL to 6
DEF(focus_len_table                         ,0xffbadd24) // Found @0xffbadd24
DEF(zoom_busy                               ,0x00006ec0) // Found @0xff955efc
DEF(focus_busy                              ,0x00006d50) // Found @0xff950090
//DEF(recreview_hold                          ,0x00003d2c) // Found @0xff8a1bb0, ** != ** stubs_min = 0x000083d8 (0x82E0+0xF8)
// Palette colour tables  found @ 0xffbbc158
DEF(active_palette_buffer                   ,0x00009cfc) // Found @0xffa026b4
DEF(palette_buffer_ptr                      ,0x00009d08) // Found @0xffa02388
// Offset from start of palette_buffer to color data = 8 (Found @0xffae5998)
// Camera appears to have only 1 RAW buffer @ 0x41f723e0 (Found @0xffb05b50)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff859684
//void *vid_get_viewport_fb()      { return (void*)0x41020120; }             // Found @0xffb03448
DEF(viewport_fb_d                           ,0x00002a88) // Found 0x2a30 (@0xff870890) + 0x58 (@0xff8708c8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2a30+0x58)); } // Found @0xff870890 & 0xff8708c8
DEF(jpeg_count_str                          ,0x00072dfc) // Found @0xff9f7368
//char *camera_jpeg_count_str()    { return (char*)0x00072dfc; }             // Found @0xff9f7368
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffb05bac
//int get_flash_params_count(void) { return 0x84; }                          // Found @0xff9907e0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb44d84, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb44d90, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb44c1c, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb44c1c, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb44c10, levent 0x00
//    { 0, KEY_POWER           ,0x00002000 }, // Found @0xffb44c28, levent 0x600
//    { 0, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffb44c34, levent 0x601
//    { 1, KEY_VIDEO           ,0x00000020 }, // Found @0xffb44c88, levent 0x12
//    { 1, KEY_SET             ,0x00000100 }, // Found @0xffb44cac, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00000200 }, // Found @0xffb44cb8, levent 0x0a
//    { 1, KEY_UP              ,0x00000400 }, // Found @0xffb44cc4, levent 0x04
//    { 1, KEY_DOWN            ,0x00000800 }, // Found @0xffb44cd0, levent 0x05
//    { 1, KEY_RIGHT           ,0x00001000 }, // Found @0xffb44cdc, levent 0x07
//    { 1, KEY_LEFT            ,0x00002000 }, // Found @0xffb44ce8, levent 0x06
//    { 1, KEY_MENU            ,0x00004000 }, // Found @0xffb44cf4, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4080 // Found @0xff92b724
//#define CAM_RAW_ROWS      3048 // Found @0xff92b72c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff838e2c

// Misc stuff
DEF(ctypes, 0xffb3a416)

// For capt_seq.c
DEF(_nrflag,0x7910) // Found @ ff9625a8 (0x7918) & ff9625c8 (-0x08)
//static long *nrflag = (long*)(0x7918-0x08);  // Found @ ff9625a8 & ff9625c4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff838de8) //112
NHSTUB(Close                                  ,0xff83527c) //120
NHSTUB(CreateTask                             ,0xff81e5b4) //120
NHSTUB(DebugAssert                            ,0xff81e88c) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff834cec) //116
NHSTUB(DeleteFile_Fut                         ,0xff834c08) //112
NHSTUB(DoAELock                               ,0xff836e28) //120
NHSTUB(EnterToCompensationEVF                 ,0xff836d84) //104
NHSTUB(ExecuteEventProcedure                  ,0xff88b598) //104
NHSTUB(ExitFromCompensationEVF                ,0xff836dc8) //104
NHSTUB(ExitTask                               ,0xff81e844) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff84465c) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff844734) //104
NHSTUB(Fclose_Fut                             ,0xff834d84) //120
NHSTUB(Feof_Fut                               ,0xff834f70) //  1
NHSTUB(Fflush_Fut                             ,0xff834fac) //  1
NHSTUB(Fgets_Fut                              ,0xff834ed8) //  1
NHSTUB(Fopen_Fut                              ,0xff834d44) //120
NHSTUB(Fread_Fut                              ,0xff834e30) //120
NHSTUB(FreeUncacheableMemory                  ,0xff838e28) //112
NHSTUB(Fseek_Fut                              ,0xff834f24) //120
NHSTUB(Fwrite_Fut                             ,0xff834e84) //120
NHSTUB(GetBatteryTemperature                  ,0xff862744) //102
NHSTUB(GetCCDTemperature                      ,0xff8626d0) //102
NHSTUB(GetCurrentAvValue                      ,0xff9526d8) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86f1c8) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86f228) //  3
NHSTUB(GetDrive_TotalClusters                 ,0xff86f1fc) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff950bcc) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff951000) //  3
NHSTUB(GetImageFolder                         ,0xff933568) //122
NHSTUB(GetKbdState                            ,0xff85f11c) //109
NHSTUB(GetMemInfo                             ,0xff81a070) //115
NHSTUB(GetOpticalTemperature                  ,0xff8627b8) //120
NHSTUB(GetParameterData                       ,0xff9907a0) //101
NHSTUB(GetPropertyCase                        ,0xff88f32c) //102
NHSTUB(GetSystemTime                          ,0xffa9b880) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff84f904) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff84f910) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff956864) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa8ed0c) //102
NHSTUB(GiveSemaphore                          ,0xff838804) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8ce3f4) //102
NHSTUB(LEDDrive                               ,0xff85e338) //120
NHSTUB(LocalTime                              ,0xff888f0c) //115
NHSTUB(LockMainPower                          ,0xff896efc) //120
NHSTUB(MakeDirectory_Fut                      ,0xff834c7c) //116
NHSTUB(MoveFocusLensToDistance                ,0xffaff710) //102
NHSTUB(MoveIrisWithAv                         ,0xffa971a8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa978d0) //120
NHSTUB(Open                                   ,0xff835224) //120
NHSTUB(PB2Rec                                 ,0xff899e38) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8796b4) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff87968c) //120
NHSTUB(PT_PlaySound                           ,0xff8840a8) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff894df8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff894e44) //120
NHSTUB(PutInNdFilter                          ,0xffa97754) //102
NHSTUB(PutOutNdFilter                         ,0xffa97778) //102
NHSTUB(Read                                   ,0xff81ab78) //120
NHSTUB(ReadFastDir                            ,0xffa7d6d4) //  3
NHSTUB(Rec2PB                                 ,0xff8988a4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffa04ad8) //104
NHSTUB(RenameFile_Fut                         ,0xff834b74) //116
NHSTUB(Restart                                ,0xff83a53c) //106
NHSTUB(ScreenLock                             ,0xffa04aa4) //117
NHSTUB(ScreenUnlock                           ,0xffa04b48) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb025c0) //102
NHSTUB(SetAutoShutdownTime                    ,0xff896f70) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89eb78) //120
NHSTUB(SetFileAttributes                      ,0xff83554c) //  3
NHSTUB(SetFileTimeStamp                       ,0xff835508) //  3
NHSTUB(SetLogicalEventActive                  ,0xff896c4c) //101
NHSTUB(SetParameterData                       ,0xff99067c) //101
NHSTUB(SetPropertyCase                        ,0xff88f230) //102
NHSTUB(SetScriptMode                          ,0xff896c9c) //120
NHSTUB(SleepTask                              ,0xff838a6c) //120
NHSTUB(TakeSemaphore                          ,0xff838734) //120
NHSTUB(TurnOnBackLight                        ,0xff8a5b18) //104
NHSTUB(TurnOnDisplay                          ,0xff859888) //120
NHSTUB(TurnOffDisplay                         ,0xff859898) //120
NHSTUB(UnlockAE                               ,0xff836e4c) //120
NHSTUB(UnlockMainPower                        ,0xff896e50) //120
NHSTUB(UpdateMBROnFlash                       ,0xff86f048) //105
NHSTUB(Write                                  ,0xff83530c) //120
NHSTUB(WriteSDCard                            ,0xff940c34) //108
NHSTUB(_log                                   ,0xffb37ed8) //111
NHSTUB(_log10                                 ,0xffb36e1c) //112
NHSTUB(_pow                                   ,0xffb36f8c) //121
NHSTUB(_sqrt                                  ,0xffb39240) //  1
NHSTUB(add_ptp_handler                        ,0xffa49320) //121
NHSTUB(apex2us                                ,0xffa08264) //121
NHSTUB(close                                  ,0xff81a990) //109
NHSTUB(err_init_task                          ,0xff815f28) //111
NHSTUB(exmem_alloc                            ,0xff889dcc) //103
NHSTUB(exmem_free                             ,0xff889e44) //103
NHSTUB(free                                   ,0xff814138) //112
NHSTUB(kbd_p1_f                               ,0xff833498) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8334a4) //109
NHSTUB(kbd_p2_f                               ,0xff832d58) //109
NHSTUB(kbd_read_keys                          ,0xff83341c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85e850) //109
NHSTUB(lseek                                  ,0xff835398) //120
NHSTUB(malloc                                 ,0xff8140dc) //112
NHSTUB(memcmp                                 ,0xff8203d8) //120
NHSTUB(memcpy                                 ,0xff83e458) //120
NHSTUB(memset                                 ,0xffa072b4) //120
NHSTUB(mkdir                                  ,0xff8356f0) //109
NHSTUB(mktime_ext                             ,0xff8ad110) //  1
NHSTUB(open                                   ,0xff81a8e0) //109
NHSTUB(OpenFastDir                            ,0xffa7d5a0) //  3
NHSTUB(closedir                               ,0xffa7d55c) //  3
NHSTUB(qsort                                  ,0xffaeb65c) //  1
NHSTUB(rand                                   ,0xff8204e0) //121
NHSTUB(realloc                                ,0xffa07330) //115
NHSTUB(reboot_fw_update                       ,0xffa82be4) //106
NHSTUB(set_control_event                      ,0xff8968a0) //111
NHSTUB(srand                                  ,0xff8204d4) //122
NHSTUB(stat                                   ,0xff8353d4) //109
NHSTUB(strcat                                 ,0xff8ac8cc) //  1
NHSTUB(strchr                                 ,0xff813fc0) //  1
NHSTUB(strcmp                                 ,0xff820394) //120
NHSTUB(strcpy                                 ,0xff82037c) //120
NHSTUB(strftime                               ,0xff8acb18) //  1
NHSTUB(strlen                                 ,0xff81400c) //120
NHSTUB(strncmp                                ,0xff813f74) //  1
NHSTUB(strncpy                                ,0xff813f38) //  1
NHSTUB(strrchr                                ,0xff813fe4) //  1
NHSTUB(strtol                                 ,0xff83e738) //101
NHSTUB(strtolx                                ,0xff83e53c) //109
   DEF(task_CaptSeq                           ,0xff87cd90) //120
   DEF(task_ExpDrv                            ,0xff8c1480) //120
   DEF(task_FileWrite                         ,0xffa78f30) //120
   DEF(task_InitFileModules                   ,0xff89a91c) //120
   DEF(task_MovieRecord                       ,0xff879084) //120
   DEF(task_PhySw                             ,0xff833088) //120
   DEF(task_RotaryEncoder                     ,0xff85f3cc) //120
NHSTUB(time                                   ,0xff889484) //109
NHSTUB(vsprintf                               ,0xff820340) //115
NHSTUB(EngDrvRead                             ,0xff8342e0) //102
