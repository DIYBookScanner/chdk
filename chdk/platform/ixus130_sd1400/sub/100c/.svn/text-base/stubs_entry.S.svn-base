// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00C   // Found @ 0xff88b2a0, "GM1.00C" @ 0xff88b2ad
//   Firmware build timestamp: Jan  7 2010 16:55:55
//   Canon IXUS 130

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12787 (0x31f3) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0014fe20
//   KEYSYS = d4a                // Found @ 0xffff3568
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff3578
//   ARAM_HEAP_START = 0x38e000  // Found @ 0xff96898c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff96894c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xff85fb28) //  2 64%    *** != 0xff811800

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffaa2b24 -> ffbd0b5c
// Mode 33320 in firmware but not in current modemap
// Mode 33322 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032800) // Found @0xff83459c
DEF(physw_run                               ,0x00001c2c) // Found @0xff834200
DEF(physw_sleep_delay                       ,0x00001c34) // Found @0xff834200
DEF(levent_table                            ,0xffb7a384) // Found @0xffb7a384
DEF(FlashParamsTable                        ,0xffbd0d60) // Found @0xffbd0d60
DEF(movie_status                            ,0x00006430) // Found @0xff95a30c
DEF(video_compression_rate                  ,0x0000646c) // Found @0xff95a578
DEF(full_screen_refresh                     ,0x00008dcc) // Found @0xff9f6c30
DEF(canon_menu_active                       ,0x00002f60) // Found @0xff88ce14
DEF(canon_shoot_menu_active                 ,0x000077c5) // Found @0xff997ec8
DEF(playrec_mode                            ,0x00002c98) // Found @0xff87f244
DEF(zoom_status                             ,0x0000c6c4) // Found @0xffaa6010
DEF(some_flag_for_af_scan                   ,0x000067e8) // Found @0xff95d1cc
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe2aa0) // Found @0xfffe2aa0
DEF(zoom_busy                               ,0x00006390) // Found @0xff955f54
DEF(focus_busy                              ,0x00006234) // Found @0xff951814
DEF(recreview_hold                          ,0x000035c0) // Found @0xff89a9ac
DEF(viewport_buffers                        ,0xffb3db40) // Found @0xff84f0cc
DEF(active_viewport_buffer                  ,0x00002040) // Found @0xff84ee8c
// Camera appears to have only 1 RAW buffer @ 0x41db3b80 (Found @0xffb03ef8)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40431000; }             // Found @0xff859828
//void *vid_get_viewport_fb()      { return (void*)0x40547700; }             // Found @0xffb00b88
DEF(viewport_fb_d                           ,0x000029f8) // Found 0x29a0 (@0xff870d10) + 0x58 (@0xff870d48)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x29a0+0x58)); } // Found @0xff870d10 & 0xff870d48
DEF(jpeg_count_str                          ,0x0009eb4c) // Found @0xff9eacbc
//char *camera_jpeg_count_str()    { return (char*)0x0009eb4c; }             // Found @0xff9eacbc
//long hook_raw_size()             { return 0x014d2400; }                    // Found @0xffb03f54
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xff986248

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb3eb24, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffb3eb3c, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SET             ,0x00000004 }, // Found @0xffb3ea64, levent 0x08
//    { 0, KEY_DISPLAY         ,0x00000008 }, // Found @0xffb3ea70, levent 0x0a
//    { 2, KEY_MENU            ,0x00000001 }, // Found @0xffb3ea88, levent 0x09
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffb3ea94, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffb3eaa0, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffb3eaac, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffb3eab8, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffb3eac4, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffb3ead0, levent 0x04
//    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffb3eae8, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffb3eae8, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffb3eadc, levent 0x00
//    { 2, KEY_POWER           ,0x00000400 }, // Found @0xffb3eaf4, levent 0x600
//    { 2, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffb3eb00, levent 0x601
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4416 // Found @0xff92e218
//#define CAM_RAW_ROWS      3296 // Found @0xff92e220
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83a1f8

// Misc stuff
DEF(ctypes, 0xffb3d5de)

// For capt_seq.c
DEF(_nrflag,0x67c0) // Found @ ff95f1b0 (0x67c8) & ff95f1d0 (-0x08)
//static long *nrflag = (long*)(0x67c8-0x08);  // Found @ ff95f1b0 & ff95f1cc

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83a1b4) //112
NHSTUB(Close                                  ,0xff836b78) //120
NHSTUB(CreateTask                             ,0xff81e83c) //120
NHSTUB(DebugAssert                            ,0xff81eb14) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff8365d4) //116
NHSTUB(DeleteFile_Fut                         ,0xff8364f0) //112
NHSTUB(DoAELock                               ,0xff838280) //120
NHSTUB(DoAFLock                               ,0xff83809c) //120
NHSTUB(EnterToCompensationEVF                 ,0xff8381e8) //104
NHSTUB(ExecuteEventProcedure                  ,0xff888538) //104
NHSTUB(ExitFromCompensationEVF                ,0xff83822c) //104
NHSTUB(ExitTask                               ,0xff81eacc) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff845e30) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff845f08) //104
NHSTUB(Fclose_Fut                             ,0xff83666c) //120
NHSTUB(Feof_Fut                               ,0xff836858) //  1
NHSTUB(Fflush_Fut                             ,0xff836894) //  1
NHSTUB(Fgets_Fut                              ,0xff8367c0) //  1
NHSTUB(Fopen_Fut                              ,0xff83662c) //120
NHSTUB(Fread_Fut                              ,0xff836718) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83a1f4) //112
NHSTUB(Fseek_Fut                              ,0xff83680c) //120
NHSTUB(Fwrite_Fut                             ,0xff83676c) //120
NHSTUB(GetBatteryTemperature                  ,0xff862d18) //102
NHSTUB(GetCCDTemperature                      ,0xff862ca4) //102
NHSTUB(GetCurrentAvValue                      ,0xff953204) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86f4b0) //122
//NHSTUB(GetDrive_FreeClusters                ,0xff86f510) //  4            == 0xff86f510
NHSTUB(GetDrive_TotalClusters                 ,0xff86f4e4) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff952494) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9528dc) //  3
NHSTUB(GetImageFolder                         ,0xff935288) //122
NHSTUB(GetKbdState                            ,0xff85fb10) //109
NHSTUB(GetMemInfo                             ,0xff81a16c) //115
NHSTUB(GetOpticalTemperature                  ,0xff862d8c) //120
NHSTUB(GetParameterData                       ,0xff986208) //101
NHSTUB(GetPropertyCase                        ,0xff88c244) //102
NHSTUB(GetSystemTime                          ,0xffa92b68) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff85079c) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8507a8) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff9562cc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa861d8) //102
NHSTUB(GiveSemaphore                          ,0xff839bd0) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8d0c10) //102
NHSTUB(LEDDrive                               ,0xff85ef6c) //120
NHSTUB(LocalTime                              ,0xff885e2c) //115
NHSTUB(LockMainPower                          ,0xff890ca0) //120
NHSTUB(MakeDirectory_Fut                      ,0xff836564) //116
NHSTUB(MoveFocusLensToDistance                ,0xffafd56c) //102
NHSTUB(MoveIrisWithAv                         ,0xffa908c8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa90e58) //120
NHSTUB(Open                                   ,0xff836b0c) //120
NHSTUB(PB2Rec                                 ,0xff893be0) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff877c04) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff877bdc) //120
NHSTUB(PT_PlaySound                           ,0xff880eb4) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff8904d0) //120
NHSTUB(PostLogicalEventToUI                   ,0xff89051c) //120
NHSTUB(PutInNdFilter                          ,0xffa90cbc) //102
NHSTUB(PutOutNdFilter                         ,0xffa90ce0) //102
NHSTUB(Read                                   ,0xff81ac7c) //120
NHSTUB(ReadFastDir                            ,0xffa751f8) //  4
NHSTUB(Rec2PB                                 ,0xff893c20) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9f786c) //104
NHSTUB(RenameFile_Fut                         ,0xff83645c) //116
NHSTUB(Restart                                ,0xff83b994) //106
NHSTUB(ScreenLock                             ,0xff9f8a9c) //117
NHSTUB(ScreenUnlock                           ,0xff9f8ae0) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffaffcfc) //102
NHSTUB(SetAutoShutdownTime                    ,0xff890d14) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff897e1c) //120
NHSTUB(SetFileAttributes                      ,0xff836e70) //  3
NHSTUB(SetFileTimeStamp                       ,0xff836e14) //  4
NHSTUB(SetLogicalEventActive                  ,0xff890a18) //101
NHSTUB(SetParameterData                       ,0xff986178) //101
NHSTUB(SetPropertyCase                        ,0xff88c114) //102
NHSTUB(SetScriptMode                          ,0xff890a68) //120
NHSTUB(SleepTask                              ,0xff839e38) //120
NHSTUB(TakeSemaphore                          ,0xff839b00) //120
NHSTUB(TurnOffBackLight                       ,0xff89df30) //104
NHSTUB(TurnOnBackLight                        ,0xff89df18) //104
NHSTUB(TurnOnDisplay                          ,0xff859b70) //120
NHSTUB(TurnOffDisplay                         ,0xff859b80) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff9734d0) //120
NHSTUB(UnlockAE                               ,0xff8382a4) //120
NHSTUB(UnlockAF                               ,0xff838120) //120
NHSTUB(UnlockMainPower                        ,0xff890bf4) //120
NHSTUB(UnsetZoomForMovie                      ,0xff98c45c) //104
NHSTUB(UpdateMBROnFlash                       ,0xff86f330) //105
NHSTUB(VbattGet                               ,0xff832f14) //120
NHSTUB(Write                                  ,0xff836c08) //120
NHSTUB(WriteSDCard                            ,0xff942b50) //108
NHSTUB(_log                                   ,0xffb3af28) //111
NHSTUB(_log10                                 ,0xffb39e6c) //112
NHSTUB(_pow                                   ,0xffb39fdc) //121
NHSTUB(_sqrt                                  ,0xffb3c2f4) //  1
NHSTUB(add_ptp_handler                        ,0xffa334cc) //121
NHSTUB(apex2us                                ,0xff9fc310) //121
NHSTUB(close                                  ,0xff81aa94) //109
NHSTUB(err_init_task                          ,0xff815f4c) //111
NHSTUB(exmem_alloc                            ,0xff886d6c) //103
NHSTUB(exmem_free                             ,0xff886de4) //103
NHSTUB(free                                   ,0xff81415c) //112
NHSTUB(kbd_p1_f                               ,0xff834614) //109
NHSTUB(kbd_p1_f_cont                          ,0xff834620) //109
NHSTUB(kbd_p2_f                               ,0xff833ecc) //109
NHSTUB(kbd_read_keys                          ,0xff83459c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85f4cc) //109
NHSTUB(lseek                                  ,0xff836c94) //120
NHSTUB(malloc                                 ,0xff814100) //112
NHSTUB(memcmp                                 ,0xff82066c) //120
NHSTUB(memcpy                                 ,0xff83f81c) //120
NHSTUB(memset                                 ,0xff9fb348) //120
NHSTUB(mkdir                                  ,0xff837014) //109
NHSTUB(mktime_ext                             ,0xff8a5ad4) //  1
NHSTUB(open                                   ,0xff81a9e4) //109
NHSTUB(OpenFastDir                            ,0xffa750a4) //  4
NHSTUB(closedir                               ,0xffa75054) //121
NHSTUB(qsort                                  ,0xffae54e8) //  4
NHSTUB(rand                                   ,0xff820774) //121
NHSTUB(realloc                                ,0xff9fb3c4) //115
NHSTUB(reboot_fw_update                       ,0xffa7a63c) //106
NHSTUB(set_control_event                      ,0xff890738) //111
NHSTUB(srand                                  ,0xff820768) //122
NHSTUB(stat                                   ,0xff836cdc) //109
NHSTUB(strcat                                 ,0xff8a5290) //  1
NHSTUB(strchr                                 ,0xff813fe4) //  1
NHSTUB(strcmp                                 ,0xff820628) //120
NHSTUB(strcpy                                 ,0xff820610) //120
NHSTUB(strftime                               ,0xff8a54dc) //113
NHSTUB(strlen                                 ,0xff814030) //120
NHSTUB(strncmp                                ,0xff813f98) //  1
NHSTUB(strncpy                                ,0xff813f5c) //  1
NHSTUB(strrchr                                ,0xff814008) //  1
NHSTUB(strtol                                 ,0xff83fafc) //101
NHSTUB(strtolx                                ,0xff83f900) //109
   DEF(task_CaptSeq                           ,0xff87a310) //120
   DEF(task_ExpDrv                            ,0xff8bab28) //120
   DEF(task_FileWrite                         ,0xffa6fcd0) //120
   DEF(task_InitFileModules                   ,0xff8946cc) //120
   DEF(task_MovieRecord                       ,0xff95a5f4) //120
   DEF(task_PhySw                             ,0xff8341fc) //120
NHSTUB(time                                   ,0xff88640c) //109
NHSTUB(vsprintf                               ,0xff8205d4) //115
NHSTUB(EngDrvRead                             ,0xff835468) //102
