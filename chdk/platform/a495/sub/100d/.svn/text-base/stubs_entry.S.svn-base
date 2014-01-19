// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00D   // Found @ 0xffc68588, "GM1.00D" @ 0xffc68595
//   Firmware build timestamp: Dec  4 2009 15:18:05
//   Canon PowerShot A495

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12783 (0x31ef) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00128e90
//   KEYSYS = d4a                // Found @ 0xffff1a2c
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff1a3c
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd1829c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd1825c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(SetScriptMode                        ,0xffc6cc08) //120        *** != 0xffc00f70
NHSTUB(kbd_pwr_off                            ,0xffc435e4) //  2 64%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe0aa60 -> ffecf688
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002e7f4) // Found @0xffc23b2c
DEF(physw_run                               ,0x00001bf0) // Found @0xffc23790
DEF(physw_sleep_delay                       ,0x00001bf8) // Found @0xffc23790
DEF(levent_table                            ,0xffea2d00) // Found @0xffea2d00
DEF(FlashParamsTable                        ,0xffecf87c) // Found @0xffecf87c
DEF(movie_status                            ,0x000054a0) // Found @0xffd0c728
DEF(full_screen_refresh                     ,0x00007370) // Found @0xffd7a970
DEF(canon_menu_active                       ,0x00002a3c) // Found @0xffc6a0cc
DEF(canon_shoot_menu_active                 ,0x000065b5) // Found @0xffd40094
DEF(playrec_mode                            ,0x00002798) // Found @0xffc5d8b0
DEF(zoom_status                             ,0x00009648) // Found @0xffe0d93c
DEF(some_flag_for_af_scan                   ,0x00005848) // Found @0xffd0f094
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe2990) // Found @0xfffe2990
DEF(zoom_busy                               ,0x00005424) // Found @0xffd09958
DEF(focus_busy                              ,0x00005334) // Found @0xffd06f90
//DEF(recreview_hold                          ,0x00003034) // Found @0xffc758d4, ** != ** stubs_min = 0x0000630a (0x6308+2)
DEF(viewport_buffers                        ,0xffe8bd28) // Found @0xffcb581c
DEF(active_viewport_buffer                  ,0x00004110) // Found @0xffcb5664
// Camera appears to have only 1 RAW buffer @ 0x10e52420 (Found @0xffe59d00)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3f020
//void *vid_get_viewport_fb()      { return (void*)0x10648cc0; }             // Found @0xffe569d4
DEF(viewport_fb_d                           ,0x00002594) // Found 0x2540 (@0xffc528c8) + 0x54 (@0xffc52900)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2540+0x54)); } // Found @0xffc528c8 & 0xffc52900
DEF(jpeg_count_str                          ,0x0007486c) // Found @0xffd71fa0
//char *camera_jpeg_count_str()    { return (char*)0x0007486c; }             // Found @0xffd71fa0
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe59d5c
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd2f1f0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00040000 // Found @0xffe84f2c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffe84f38, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x00020000 }, // Found @0xffe84ea8, levent 0x601
//    { 0, KEY_POWER           ,0x00800000 }, // Found @0xffe84ec0, levent 0x600
//    { 2, KEY_RIGHT           ,0x00000004 }, // Found @0xffe84ecc, levent 0x07
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe84ee4, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe84ee4, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe84ed8, levent 0x00
//    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffe84ef0, levent 0x03
//    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffe84efc, levent 0x02
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe84f08, levent 0x08
//    { 2, KEY_UP              ,0x00100000 }, // Found @0xffe84f44, levent 0x04 (uses inverted logic in physw_status)
//    { 2, KEY_DOWN            ,0x00200000 }, // Found @0xffe84f50, levent 0x05 (uses inverted logic in physw_status)
//    { 2, KEY_LEFT            ,0x00400000 }, // Found @0xffe84f5c, levent 0x06 (uses inverted logic in physw_status)
//    { 2, KEY_MENU            ,0x01000000 }, // Found @0xffe84f74, levent 0x09 (uses inverted logic in physw_status)
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcea468
//#define CAM_RAW_ROWS      2772 // Found @0xffcea474
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc2931c

// Misc stuff
DEF(ctypes, 0xffe847c6)

// For capt_seq.c
DEF(_nrflag,0x5828) // Found @ ffd10eac (0x5830) & ffd10ecc (-0x08)
//static long *nrflag = (long*)(0x5830-0x08);  // Found @ ffd10eac & ffd10ec8

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
NHSTUB(ExecuteEventProcedure                  ,0xffc65820) //104
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
NHSTUB(GetCurrentAvValue                      ,0xffd08810) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc512c0) //122
NHSTUB(GetDrive_FreeClusters                  ,0xffc51320) //  4
NHSTUB(GetDrive_TotalClusters                 ,0xffc512f4) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xffd07b08) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd07f60) //  3
NHSTUB(GetImageFolder                         ,0xffcf1428) //122
NHSTUB(GetKbdState                            ,0xffc435cc) //109
NHSTUB(GetMemInfo                             ,0xffc0a7f8) //115
NHSTUB(GetOpticalTemperature                  ,0xffc45694) //120
NHSTUB(GetParameterData                       ,0xffd2f1b0) //101
NHSTUB(GetPropertyCase                        ,0xffc6952c) //102
NHSTUB(GetSystemTime                          ,0xffdfd1c0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcb6c54) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcb6c60) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd09cd0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdf520c) //102
NHSTUB(GiveSemaphore                          ,0xffc0f104) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffca7260) //102
NHSTUB(LEDDrive                               ,0xffc42bc4) //120
NHSTUB(LocalTime                              ,0xffc63530) //115
NHSTUB(LockMainPower                          ,0xffc6ce40) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc25af4) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe53454) //102
NHSTUB(MoveIrisWithAv                         ,0xffdfa8b0) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdfae40) //120
NHSTUB(Open                                   ,0xffc2609c) //120
NHSTUB(PB2Rec                                 ,0xffc6fa94) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc57170) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc57148) //120
NHSTUB(PT_PlaySound                           ,0xffc5f3b0) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6c670) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc6c6bc) //120
NHSTUB(PutInNdFilter                          ,0xffdfaca4) //102
NHSTUB(PutOutNdFilter                         ,0xffdfacc8) //102
NHSTUB(Read                                   ,0xffc0b308) //120
NHSTUB(ReadFastDir                            ,0xffdebbf4) //  4
NHSTUB(Rec2PB                                 ,0xffc6fad4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd7b34c) //104
NHSTUB(RenameFile_Fut                         ,0xffc259ec) //116
NHSTUB(Restart                                ,0xffc2aab0) //106
NHSTUB(ScreenLock                             ,0xffd7c4f8) //117
NHSTUB(ScreenUnlock                           ,0xffd7c53c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffe55be4) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc6ceb4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc731ec) //120
NHSTUB(SetFileAttributes                      ,0xffc26400) //  3
NHSTUB(SetFileTimeStamp                       ,0xffc263a4) //  4
NHSTUB(SetLogicalEventActive                  ,0xffc6cbb8) //101
NHSTUB(SetParameterData                       ,0xffd2f120) //101
NHSTUB(SetPropertyCase                        ,0xffc693fc) //102
NHSTUB(SleepTask                              ,0xffc2915c) //120
NHSTUB(TakeSemaphore                          ,0xffc0f034) //120
NHSTUB(TurnOffBackLight                       ,0xffc77f4c) //104
NHSTUB(TurnOnBackLight                        ,0xffc77f34) //104
NHSTUB(TurnOnDisplay                          ,0xffc3f2fc) //120
NHSTUB(TurnOffDisplay                         ,0xffc3f328) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd1f924) //120
NHSTUB(UnlockAE                               ,0xffc276c0) //120
NHSTUB(UnlockAF                               ,0xffc2758c) //120
NHSTUB(UnlockMainPower                        ,0xffc6cd94) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3589c) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc51140) //105
NHSTUB(VbattGet                               ,0xffc22be4) //120
NHSTUB(Write                                  ,0xffc26198) //120
NHSTUB(WriteSDCard                            ,0xffcfcb1c) //108
NHSTUB(_log                                   ,0xffe82328) //111
NHSTUB(_log10                                 ,0xffe8126c) //112
NHSTUB(_pow                                   ,0xffe813dc) //121
NHSTUB(_sqrt                                  ,0xffe83690) //  1
NHSTUB(add_ptp_handler                        ,0xffdbeb54) //121
NHSTUB(apex2us                                ,0xffd7d848) //121
NHSTUB(close                                  ,0xffc0b120) //109
NHSTUB(err_init_task                          ,0xffc05f50) //111
NHSTUB(exmem_alloc                            ,0xffc641d0) //103
NHSTUB(exmem_free                             ,0xffc64248) //103
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
NHSTUB(memset                                 ,0xffd7c880) //120
NHSTUB(mkdir                                  ,0xffc265a4) //109
NHSTUB(mktime_ext                             ,0xffc7cd6c) //  1
NHSTUB(open                                   ,0xffc0b070) //109
NHSTUB(OpenFastDir                            ,0xffdebaa0) //  4
NHSTUB(closedir                               ,0xffdeba50) //121
NHSTUB(qsort                                  ,0xffe3c190) //  4
NHSTUB(rand                                   ,0xffc11420) //121
NHSTUB(realloc                                ,0xffd7c8fc) //115
NHSTUB(reboot_fw_update                       ,0xffded468) //106
NHSTUB(set_control_event                      ,0xffc6c8d8) //111
NHSTUB(srand                                  ,0xffc11414) //122
NHSTUB(stat                                   ,0xffc2626c) //109
NHSTUB(strcat                                 ,0xffc7c528) //  1
NHSTUB(strchr                                 ,0xffc03fe8) //  1
NHSTUB(strcmp                                 ,0xffc112d4) //120
NHSTUB(strcpy                                 ,0xffc112bc) //120
NHSTUB(strftime                               ,0xffc7c774) //113
NHSTUB(strlen                                 ,0xffc04034) //120
NHSTUB(strncmp                                ,0xffc03f9c) //  1
NHSTUB(strncpy                                ,0xffc03f60) //  1
NHSTUB(strrchr                                ,0xffc0400c) //  1
NHSTUB(strtol                                 ,0xffc2eb40) //101
NHSTUB(strtolx                                ,0xffc2e944) //109
   DEF(task_CaptSeq                           ,0xffc59224) //120
   DEF(task_ExpDrv                            ,0xffc91604) //120
   DEF(task_FileWrite                         ,0xffde66cc) //120
   DEF(task_InitFileModules                   ,0xffc7055c) //120
   DEF(task_MovieRecord                       ,0xffd0c97c) //120
   DEF(task_PhySw                             ,0xffc2378c) //120
NHSTUB(time                                   ,0xffc633e4) //109
NHSTUB(vsprintf                               ,0xffc11280) //115
NHSTUB(EngDrvRead                             ,0xffc249f8) //102
