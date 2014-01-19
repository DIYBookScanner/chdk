// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R47 (DRYOS version 2.3, release #0047)
//   Firmware Ver GM1.00D   // Found @ 0xff88bf88, "GM1.00D" @ 0xff88bf95
//   Firmware build timestamp: Jun  8 2011 10:54:51
//   Canon PowerShot A3200 IS

// Values for makefile.inc
//   PLATFORMOSVER = 47
//   PLATFORMID = 12836 (0x3224) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0016a88c
//   KEYSYS = d4c                // Found @ 0xffff350c
//   NEED_ENCODED_DISKBOOT = 6   // Found @ 0xffff351c
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff977eb4
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff977e74

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffac7c28 -> ffbedae8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032d14) // Found @0xff83454c
DEF(physw_run                               ,0x00001c30) // Found @0xff83410c
DEF(physw_sleep_delay                       ,0x00001c38) // Found @0xff83410c
DEF(levent_table                            ,0xffb9ffb0) // Found @0xffb9ffb0
DEF(FlashParamsTable                        ,0xffbedd20) // Found @0xffbedd20
DEF(movie_status                            ,0x00006724) // Found @0xff969018
DEF(video_compression_rate                  ,0x00006764) // Found @0xff9692d0
DEF(full_screen_refresh                     ,0x0000915c) // Found @0xffa066d0
DEF(canon_menu_active                       ,0x00002f60) // Found @0xff88d990
DEF(canon_shoot_menu_active                 ,0x00007be5) // Found @0xff9ad3bc
DEF(playrec_mode                            ,0x00002c88) // Found @0xff87fc8c
DEF(zoom_status                             ,0x0000cf3c) // Found @0xffacb2fc
DEF(some_flag_for_af_scan                   ,0x00006afc) // Found @0xff96cd0c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 12 entries in the table - set NUM_FL to 12
DEF(focus_len_table                         ,0xfffe2f88) // Found @0xfffe2f88
DEF(zoom_busy                               ,0x0000664c) // Found @0xff9648a4
DEF(focus_busy                              ,0x000064c8) // Found @0xff95fb1c
DEF(recreview_hold                          ,0x00003534) // Found @0xff89aeac
// Palette colour tables  found @ 0xffbb5d3c
DEF(palette_control                         ,0x0000915c) // Found @0xffa0664c
DEF(active_palette_buffer                   ,0x00009164) // Found @0xffa06650
DEF(palette_buffer_ptr                      ,0x00009168) // Found @0xffa069f4
DEF(palette_buffer                          ,0x000b4b7c) // Found @0xffa06a04
// Offset from start of palette_buffer to color data = 8 (Found @0xffafc1e8)
DEF(viewport_buffers                        ,0xffb5c5d0) // Found @0xff8519a4
DEF(active_viewport_buffer                  ,0x000020d0) // Found @0xff851718
// Camera appears to have only 1 RAW buffer @ 0x421316c0 (Found @0xffb20fc4)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff85b834
//void *vid_get_viewport_fb()      { return (void*)0x40546b80; }             // Found @0xffb1db58
DEF(viewport_fb_d                           ,0x000029f8) // Found 0x29a0 (@0xff871340) + 0x58 (@0xff871378)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x29a0+0x58)); } // Found @0xff871340 & 0xff871378
DEF(jpeg_count_str                          ,0x000b44d4) // Found @0xff9fd22c
//char *camera_jpeg_count_str()    { return (char*)0x000b44d4; }             // Found @0xff9fd22c
//long hook_raw_size()             { return 0x014d2400; }                    // Found @0xffb2101c
//int get_flash_params_count(void) { return 0xa0; }                          // Found @0xff9941e4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb5d574, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xffb5d594, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x00002000 }, // Found @0xffb5d4dc, levent 0x601
//    { 0, KEY_POWER           ,0x00004000 }, // Found @0xffb5d4e4, levent 0x600
//    { 2, KEY_UP              ,0x00000001 }, // Found @0xffb5d4f4, levent 0x04
//    { 2, KEY_DOWN            ,0x00000002 }, // Found @0xffb5d4fc, levent 0x05
//    { 2, KEY_LEFT            ,0x00000004 }, // Found @0xffb5d504, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000008 }, // Found @0xffb5d50c, levent 0x07
//    { 2, KEY_SET             ,0x00000010 }, // Found @0xffb5d514, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000020 }, // Found @0xffb5d51c, levent 0x0a
//    { 2, KEY_MENU            ,0x00000080 }, // Found @0xffb5d52c, levent 0x09
//    { 2, KEY_SHOOT_FULL      ,0x00003000 }, // Found @0xffb5d554, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00002000 }, // Found @0xffb5d554, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00001000 }, // Found @0xffb5d54c, levent 0x00
//    { 2, KEY_ZOOM_OUT        ,0x00004000 }, // Found @0xffb5d55c, levent 0x03
//    { 2, KEY_ZOOM_IN         ,0x00008000 }, // Found @0xffb5d564, levent 0x02
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4416 // Found @0xff93a144
//#define CAM_RAW_ROWS      3296 // Found @0xff93a14c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83a6c0

// Misc stuff
DEF(ctypes, 0xffb5be52)

// For capt_seq.c
DEF(_nrflag,0x6b38) // Found @ ff971108 (0x6b30) & ff971144 (+0x08)
//static long *nrflag = (long*)(0x6b30+0x08);  // Found @ ff971108 & ff971144
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83a678) //112
NHSTUB(Close                                  ,0xff836c70) //120
NHSTUB(CreateTask                             ,0xff81e9b0) //120
NHSTUB(DebugAssert                            ,0xff81ec88) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff83666c) //116
NHSTUB(DeleteFile_Fut                         ,0xff836588) //112
NHSTUB(DoAELock                               ,0xff838720) //120
NHSTUB(DoAFLock                               ,0xff83842c) //120
NHSTUB(EnterToCompensationEVF                 ,0xff838688) //104
NHSTUB(ExecuteEventProcedure                  ,0xff889190) //104
NHSTUB(ExitFromCompensationEVF                ,0xff8386cc) //104
NHSTUB(ExitTask                               ,0xff81ec40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff846c90) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff846d68) //104
NHSTUB(Fclose_Fut                             ,0xff836704) //120
NHSTUB(Feof_Fut                               ,0xff8368f0) //  1
NHSTUB(Fflush_Fut                             ,0xff83692c) //  1
NHSTUB(Fgets_Fut                              ,0xff836858) //  6
NHSTUB(Fopen_Fut                              ,0xff8366c4) //120
NHSTUB(Fread_Fut                              ,0xff8367b0) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83a6b8) //112
NHSTUB(Fseek_Fut                              ,0xff8368a4) //120
NHSTUB(Fwrite_Fut                             ,0xff836804) //120
NHSTUB(GetBatteryTemperature                  ,0xff8621e0) //102
NHSTUB(GetCCDTemperature                      ,0xff86216c) //102
NHSTUB(GetCurrentAvValue                      ,0xff9616ec) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86fca4) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86fcfc) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff86fcd4) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff9607a0) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff960c00) //  3
NHSTUB(GetImageFolder                         ,0xff940fcc) //122
NHSTUB(GetKbdState                            ,0xff860268) //109
NHSTUB(GetMemInfo                             ,0xff81a29c) //115
NHSTUB(GetOpticalTemperature                  ,0xff862254) //120
NHSTUB(GetParameterData                       ,0xff9941a4) //101
NHSTUB(GetPropertyCase                        ,0xff88cef8) //102
NHSTUB(GetSystemTime                          ,0xffab6650) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff853c08) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff853c14) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff964c28) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffaa33c8) //102
NHSTUB(GiveSemaphore                          ,0xff83a070) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8d8b84) //102
NHSTUB(LEDDrive                               ,0xff85f87c) //120
NHSTUB(LocalTime                              ,0xff886a80) //115
NHSTUB(LockMainPower                          ,0xff891db4) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8365fc) //116
NHSTUB(MakeSDCardBootable                     ,0xff86ff34) //105
NHSTUB(MoveFocusLensToDistance                ,0xffb19eb4) //102
NHSTUB(MoveIrisWithAv                         ,0xffab32b8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffab3970) //120
NHSTUB(Open                                   ,0xff836ba8) //120
NHSTUB(PB2Rec                                 ,0xff894f7c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8782e4) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff8782bc) //120
NHSTUB(PT_PlaySound                           ,0xff881ac4) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff891580) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8915cc) //120
NHSTUB(PutInNdFilter                          ,0xffab37b8) //102
NHSTUB(PutOutNdFilter                         ,0xffab37dc) //102
NHSTUB(Read                                   ,0xff81ad58) //120
NHSTUB(ReadFastDir                            ,0xffa90bec) //  6
NHSTUB(Rec2PB                                 ,0xff894fbc) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8a5940) //104
NHSTUB(RenameFile_Fut                         ,0xff8364f4) //116
NHSTUB(Restart                                ,0xff83be88) //106
NHSTUB(ScreenLock                             ,0xff8a6b78) //117
NHSTUB(ScreenUnlock                           ,0xff8a6bdc) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb1cd30) //102
NHSTUB(SetAutoShutdownTime                    ,0xff891e28) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff898b34) //120
NHSTUB(SetFileAttributes                      ,0xff837074) //  6
NHSTUB(SetFileTimeStamp                       ,0xff836ffc) //  6
NHSTUB(SetLogicalEventActive                  ,0xff891b2c) //101
NHSTUB(SetParameterData                       ,0xff994114) //101
NHSTUB(SetPropertyCase                        ,0xff88cddc) //102
NHSTUB(SetScriptMode                          ,0xff891b7c) //120
NHSTUB(SleepTask                              ,0xff83a31c) //120
NHSTUB(TakeSemaphore                          ,0xff839fa0) //120
NHSTUB(TurnOffBackLight                       ,0xff89e2ac) //104
NHSTUB(TurnOnBackLight                        ,0xff89e294) //104
NHSTUB(TurnOnDisplay                          ,0xff85bc6c) //120
NHSTUB(TurnOffDisplay                         ,0xff85bc7c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff985628) //120
NHSTUB(UnlockAE                               ,0xff838744) //120
NHSTUB(UnlockAF                               ,0xff838464) //120
NHSTUB(UnlockMainPower                        ,0xff891d08) //120
NHSTUB(UnsetZoomForMovie                      ,0xff99d6b8) //104
NHSTUB(VbattGet                               ,0xff832e20) //120
NHSTUB(Write                                  ,0xff836cc4) //120
NHSTUB(WriteSDCard                            ,0xff950e38) //108
NHSTUB(_log                                   ,0xffb58978) //111
NHSTUB(_log10                                 ,0xffb58eb8) //112
NHSTUB(_pow                                   ,0xffb59030) //121
NHSTUB(_sqrt                                  ,0xffb5ac54) //  6
NHSTUB(add_ptp_handler                        ,0xffa46d50) //121
NHSTUB(apex2us                                ,0xffa0ba38) //121
NHSTUB(close                                  ,0xff81abb4) //109
NHSTUB(err_init_task                          ,0xff815fd4) //111
NHSTUB(exmem_alloc                            ,0xff887a48) //101
NHSTUB(exmem_free                             ,0xff887ac0) //101
NHSTUB(free                                   ,0xff814244) //112
NHSTUB(kbd_p1_f                               ,0xff8345c8) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8345d4) //109
NHSTUB(kbd_p2_f                               ,0xff833ddc) //109
NHSTUB(kbd_read_keys                          ,0xff83454c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85fcc0) //109
NHSTUB(lseek                                  ,0xff836e8c) //120
NHSTUB(malloc                                 ,0xff8141ec) //112
NHSTUB(memcmp                                 ,0xff8208bc) //120
NHSTUB(memcpy                                 ,0xff83fcf8) //120
NHSTUB(memset                                 ,0xffa0aa38) //120
NHSTUB(mkdir                                  ,0xff83710c) //109
NHSTUB(mktime_ext                             ,0xff8a79bc) //  1
NHSTUB(open                                   ,0xff81ab04) //109
NHSTUB(OpenFastDir                            ,0xffa90a98) //  6
NHSTUB(closedir                               ,0xffa90a48) //121
NHSTUB(qsort                                  ,0xffafcdd8) //  6
NHSTUB(rand                                   ,0xffa0ab78) //121
NHSTUB(realloc                                ,0xffa0aab4) //115
NHSTUB(reboot_fw_update                       ,0xffa96088) //106
NHSTUB(set_control_event                      ,0xff8917f0) //111
NHSTUB(srand                                  ,0xffa0ab6c) //122
NHSTUB(stat                                   ,0xff836ed4) //109
NHSTUB(strcat                                 ,0xff8a7174) //  1
NHSTUB(strchr                                 ,0xff8140b8) //  1
NHSTUB(strcmp                                 ,0xff820878) //120
NHSTUB(strcpy                                 ,0xff820860) //120
NHSTUB(strftime                               ,0xff8a73bc) //113
NHSTUB(strlen                                 ,0xff814104) //120
NHSTUB(strncmp                                ,0xff81406c) //  1
NHSTUB(strncpy                                ,0xff814030) //  1
NHSTUB(strrchr                                ,0xff8140dc) //  1
NHSTUB(strtol                                 ,0xff83fff8) //101
NHSTUB(strtolx                                ,0xff83fdfc) //109
   DEF(task_CaptSeq                           ,0xff87aa8c) //120
   DEF(task_ExpDrv                            ,0xff8be348) //120
   DEF(task_FileWrite                         ,0xffa8ea9c) //120
   DEF(task_InitFileModules                   ,0xff895794) //120
   DEF(task_MovieRecord                       ,0xff969ae4) //120
   DEF(task_PhySw                             ,0xff834108) //120
NHSTUB(time                                   ,0xff88705c) //109
NHSTUB(vsprintf                               ,0xff820820) //115
NHSTUB(EngDrvRead                             ,0xff835414) //102
