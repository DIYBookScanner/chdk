// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R47 (DRYOS version 2.3, release #0047)
//   Firmware Ver GM1.00B   // Found @ 0xffc6ab10, "GM1.00B" @ 0xffc6ab1d
//   Firmware build timestamp: Dec 17 2010 08:51:53
//   Canon PowerShot A800

// Values for makefile.inc
//   PLATFORMOSVER = 47
//   PLATFORMID = 12838 (0x3226) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0013a700
//   KEYSYS = d4c                // Found @ 0xffff1a20
//   NEED_ENCODED_DISKBOOT = 6   // Found @ 0xffff1a30
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd23d54
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd23d14

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
// ERROR: rand is not found.                               //--- ---    *** != 0x00000000
// ERROR: srand is not found.                              //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe267ac -> ffee9f10
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002f048) // Found @0xffc23c3c
DEF(physw_run                               ,0x00001bf8) // Found @0xffc237fc
DEF(physw_sleep_delay                       ,0x00001c00) // Found @0xffc237fc
DEF(levent_table                            ,0xffeba30c) // Found @0xffeba30c
DEF(FlashParamsTable                        ,0xffeea134) // Found @0xffeea134
DEF(movie_status                            ,0x000056b8) // Found @0xffd18138
DEF(full_screen_refresh                     ,0x00007810) // Found @0xffd88cc8
DEF(canon_menu_active                       ,0x00002a98) // Found @0xffc6c4e8
DEF(canon_shoot_menu_active                 ,0x000068a9) // Found @0xffd4c494
DEF(playrec_mode                            ,0x000027e4) // Found @0xffc5f96c
DEF(zoom_status                             ,0x0000a050) // Found @0xffe2a40c
DEF(some_flag_for_af_scan                   ,0x00005a70) // Found @0xffd1b170
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe2ee8) // Found @0xfffe2ee8
DEF(zoom_busy                               ,0x0000560c) // Found @0xffd14e64
DEF(focus_busy                              ,0x0000551c) // Found @0xffd125c4
DEF(recreview_hold                          ,0x000030d4) // Found @0xffc78de0
DEF(viewport_buffers                        ,0xffeaaa10) // Found @0xffcbe40c
DEF(active_viewport_buffer                  ,0x0000424c) // Found @0xffcbe284
// Camera appears to have only 1 RAW buffer @ 0x10e59860 (Found @0xffe72f9c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3fafc
//void *vid_get_viewport_fb()      { return (void*)0x1068c2e0; }             // Found @0xffe6fb54
DEF(viewport_fb_d                           ,0x000025dc) // Found 0x2588 (@0xffc543b8) + 0x54 (@0xffc543f0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2588+0x54)); } // Found @0xffc543b8 & 0xffc543f0
DEF(jpeg_count_str                          ,0x00088994) // Found @0xffd810bc
//char *camera_jpeg_count_str()    { return (char*)0x00088994; }             // Found @0xffd810bc
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe72ff4
//int get_flash_params_count(void) { return 0xa0; }                          // Found @0xffd3af20

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe9db60, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x01000000 // Found @0xffe9db80, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x00020000 }, // Found @0xffe9db10, levent 0x601
//    { 0, KEY_POWER           ,0x00800000 }, // Found @0xffe9db20, levent 0x600
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe9db30, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe9db30, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe9db28, levent 0x00
//    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffe9db38, levent 0x03
//    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffe9db40, levent 0x02
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe9db48, levent 0x08
//    { 2, KEY_RIGHT           ,0x00000200 }, // Found @0xffe9db50, levent 0x07
//    { 2, KEY_UP              ,0x02000000 }, // Found @0xffe9db88, levent 0x04 (uses inverted logic in physw_status)
//    { 2, KEY_DOWN            ,0x04000000 }, // Found @0xffe9db90, levent 0x05 (uses inverted logic in physw_status)
//    { 2, KEY_LEFT            ,0x08000000 }, // Found @0xffe9db98, levent 0x06 (uses inverted logic in physw_status)
//    { 2, KEY_MENU            ,0x20000000 }, // Found @0xffe9dba8, levent 0x09 (uses inverted logic in physw_status)
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcf3210
//#define CAM_RAW_ROWS      2772 // Found @0xffcf321c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc29904

// Misc stuff
DEF(ctypes, 0xffe9d26e)

// For capt_seq.c
DEF(_nrflag,0x5a94) // Found @ ffd1d9c8 (0x5a8c) & ffd1da04 (+0x08)
//static long *nrflag = (long*)(0x5a8c+0x08);  // Found @ ffd1d9c8 & ffd1da04
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc298bc) //112
NHSTUB(Close                                  ,0xffc26360) //120
NHSTUB(CreateTask                             ,0xffc0f290) //120
NHSTUB(DebugAssert                            ,0xffc0f768) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc25d5c) //116
NHSTUB(DeleteFile_Fut                         ,0xffc25c78) //112
NHSTUB(DoAELock                               ,0xffc27b6c) //120
NHSTUB(DoAFLock                               ,0xffc27a24) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc27ad4) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc67d18) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc27b18) //104
NHSTUB(ExitTask                               ,0xffc0f520) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc358f8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc35a78) //104
NHSTUB(Fclose_Fut                             ,0xffc25df4) //120
NHSTUB(Feof_Fut                               ,0xffc25fe0) //  1
NHSTUB(Fflush_Fut                             ,0xffc2601c) //  1
NHSTUB(Fgets_Fut                              ,0xffc25f48) //  6
NHSTUB(Fopen_Fut                              ,0xffc25db4) //120
NHSTUB(Fread_Fut                              ,0xffc25ea0) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc298fc) //112
NHSTUB(Fseek_Fut                              ,0xffc25f94) //120
NHSTUB(Fwrite_Fut                             ,0xffc25ef4) //120
NHSTUB(GetBatteryTemperature                  ,0xffc45dec) //102
NHSTUB(GetCCDTemperature                      ,0xffc45d78) //102
NHSTUB(GetCurrentAvValue                      ,0xffd13ed4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc52da4) //122
NHSTUB(GetDrive_FreeClusters                  ,0xffc52dfc) //119
NHSTUB(GetDrive_TotalClusters                 ,0xffc52dd4) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xffd1313c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd13598) //  3
NHSTUB(GetImageFolder                         ,0xffcfa088) //122
NHSTUB(GetKbdState                            ,0xffc43e6c) //109
NHSTUB(GetMemInfo                             ,0xffc0a8a0) //115
NHSTUB(GetOpticalTemperature                  ,0xffc45e64) //120
NHSTUB(GetParameterData                       ,0xffd3aee0) //101
NHSTUB(GetPropertyCase                        ,0xffc6ba84) //102
NHSTUB(GetSystemTime                          ,0xffe193fc) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcbf898) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcbf8a4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd151e8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe09db4) //102
NHSTUB(GiveSemaphore                          ,0xffc0f1f0) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcaf2c8) //102
NHSTUB(LEDDrive                               ,0xffc43538) //120
NHSTUB(LocalTime                              ,0xffc65708) //115
NHSTUB(LockMainPower                          ,0xffc70290) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc25cec) //116
NHSTUB(MakeSDCardBootable                     ,0xffc53034) //105
NHSTUB(MoveFocusLensToDistance                ,0xffe6bef0) //102
NHSTUB(MoveIrisWithAv                         ,0xffe15bd4) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe16278) //120
NHSTUB(Open                                   ,0xffc26298) //120
NHSTUB(PB2Rec                                 ,0xffc72f50) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc58dec) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc58dc4) //120
NHSTUB(PT_PlaySound                           ,0xffc61544) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6fabc) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc6fb08) //120
NHSTUB(PutInNdFilter                          ,0xffe160c0) //102
NHSTUB(PutOutNdFilter                         ,0xffe160e4) //102
NHSTUB(Read                                   ,0xffc0b35c) //120
NHSTUB(ReadFastDir                            ,0xffdff8d0) //  6
NHSTUB(Rec2PB                                 ,0xffc72f90) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffc80098) //104
NHSTUB(RenameFile_Fut                         ,0xffc25be4) //116
NHSTUB(Restart                                ,0xffc2b0d8) //106
NHSTUB(ScreenLock                             ,0xffc81278) //117
NHSTUB(ScreenUnlock                           ,0xffc812dc) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffe6ed6c) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc70304) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc76628) //120
NHSTUB(SetFileAttributes                      ,0xffc26764) //  6
NHSTUB(SetFileTimeStamp                       ,0xffc266ec) //  6
NHSTUB(SetLogicalEventActive                  ,0xffc70008) //101
NHSTUB(SetParameterData                       ,0xffd3ae50) //101
NHSTUB(SetPropertyCase                        ,0xffc6b968) //102
NHSTUB(SetScriptMode                          ,0xffc70058) //120
NHSTUB(SleepTask                              ,0xffc29760) //120
NHSTUB(TakeSemaphore                          ,0xffc0f120) //120
NHSTUB(TurnOffBackLight                       ,0xffc7b568) //104
NHSTUB(TurnOnBackLight                        ,0xffc7b550) //104
NHSTUB(TurnOnDisplay                          ,0xffc3ff34) //120
NHSTUB(TurnOffDisplay                         ,0xffc3ff44) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd2db9c) //120
NHSTUB(UnlockAE                               ,0xffc27b90) //120
NHSTUB(UnlockAF                               ,0xffc27a5c) //120
NHSTUB(UnlockMainPower                        ,0xffc701e4) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd41454) //104
NHSTUB(VbattGet                               ,0xffc22b4c) //120
NHSTUB(Write                                  ,0xffc263b4) //120
NHSTUB(WriteSDCard                            ,0xffd07b28) //108
NHSTUB(_log                                   ,0xffe99e98) //111
NHSTUB(_log10                                 ,0xffe9a3d8) //112
NHSTUB(_pow                                   ,0xffe9a550) //121
NHSTUB(_sqrt                                  ,0xffe9c174) //  6
NHSTUB(add_ptp_handler                        ,0xffdd53ac) //121
NHSTUB(apex2us                                ,0xffd8dfd0) //121
NHSTUB(close                                  ,0xffc0b1b8) //109
NHSTUB(err_init_task                          ,0xffc05fd8) //111
NHSTUB(exmem_alloc                            ,0xffc666d0) //101
NHSTUB(exmem_free                             ,0xffc66748) //101
NHSTUB(free                                   ,0xffc04248) //112
NHSTUB(kbd_p1_f                               ,0xffc23cb8) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc23cc4) //109
NHSTUB(kbd_p2_f                               ,0xffc234cc) //109
NHSTUB(kbd_read_keys                          ,0xffc23c3c) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc43878) //109
NHSTUB(lseek                                  ,0xffc2657c) //120
NHSTUB(malloc                                 ,0xffc041f0) //112
NHSTUB(memcmp                                 ,0xffc114d8) //120
NHSTUB(memcpy                                 ,0xffc2ee6c) //120
NHSTUB(memset                                 ,0xffd8d00c) //120
//NHSTUB(mkdir                                ,0xffc267fc) //109            == 0xffc267fc
NHSTUB(mktime_ext                             ,0xffc82008) //  1
NHSTUB(open                                   ,0xffc0b108) //109
NHSTUB(OpenFastDir                            ,0xffdff77c) //  6
NHSTUB(closedir                               ,0xffdff72c) //121
NHSTUB(qsort                                  ,0xffe527e4) //  6
NHSTUB(realloc                                ,0xffd8d088) //115
NHSTUB(reboot_fw_update                       ,0xffe01178) //106
NHSTUB(set_control_event                      ,0xffc6fd2c) //111
NHSTUB(stat                                   ,0xffc265c4) //109
NHSTUB(strcat                                 ,0xffc817c0) //  1
NHSTUB(strchr                                 ,0xffc040bc) //  1
NHSTUB(strcmp                                 ,0xffc11494) //120
NHSTUB(strcpy                                 ,0xffc1147c) //120
NHSTUB(strftime                               ,0xffc81a08) //113
NHSTUB(strlen                                 ,0xffc04108) //120
NHSTUB(strncmp                                ,0xffc04070) //  1
NHSTUB(strncpy                                ,0xffc04034) //  1
NHSTUB(strrchr                                ,0xffc040e0) //  1
NHSTUB(strtol                                 ,0xffc2f16c) //101
NHSTUB(strtolx                                ,0xffc2ef70) //109
   DEF(task_CaptSeq                           ,0xffc5b06c) //120
   DEF(task_ExpDrv                            ,0xffc98190) //120
   DEF(task_FileWrite                         ,0xffdfd780) //120
   DEF(task_InitFileModules                   ,0xffc7387c) //120
   DEF(task_MovieRecord                       ,0xffd18384) //120
   DEF(task_PhySw                             ,0xffc237f8) //120
NHSTUB(time                                   ,0xffc65ce4) //109
NHSTUB(vsprintf                               ,0xffc1143c) //115
NHSTUB(EngDrvRead                             ,0xffc24b04) //102
