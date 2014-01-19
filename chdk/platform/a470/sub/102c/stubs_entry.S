// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.02C   // Found @ 0xffc56538, "GM1.02C" @ 0xffc56545
//   Firmware build timestamp: Apr  3 2008 14:14:56
//   Canon PowerShot A470

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12666 (0x317a) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a5798
//   KEYSYS = d3enc              // Found @ 0xffff1a98
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff1a78
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffddbaa8
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffddba68

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(PutInNdFilter                        ,0xffdd7a00) //102        *** != 0xffe271f0
//NHSTUB(PutOutNdFilter                       ,0xffdd7a24) //102        *** != 0xffe27228
//NHSTUB(kbd_pwr_off                          ,0xffc30ff4) //  2 67%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffde7b84 -> ffe90570
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000100bc) // Found @0xffc11c0c
DEF(physw_run                               ,0x00001bf0) // Found @0xffc118a8
DEF(physw_sleep_delay                       ,0x00001bee) // Found @0xffc118a8
DEF(levent_table                            ,0xffe73984) // Found @0xffe73984
DEF(FlashParamsTable                        ,0xffe90724) // Found @0xffe90724
DEF(movie_status                            ,0x00005200) // Found @0xffc45690
DEF(canon_menu_active                       ,0x00009064) // Found @0xffd1f904
DEF(canon_shoot_menu_active                 ,0x00009831) // Found @0xffd380c4
DEF(playrec_mode                            ,0x00005370) // Found @0xffc4bc7c
DEF(zoom_status                             ,0x0000d070) // Found @0xffde9384
DEF(some_flag_for_af_scan                   ,0x0000cdec) // Found @0xffdd7de4
DEF(zoom_busy                               ,0x000083d4) // Found @0xffd0677c
DEF(focus_busy                              ,0x000082e0) // Found @0xffd02310
DEF(recreview_hold                          ,0x00005b64) // Found @0xffc64340
// Camera appears to have only 1 RAW buffer @ 0x10f06b20 (Found @0xffe2e564)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc2cc88
//void *vid_get_viewport_fb()      { return (void*)0x10659d50; }             // Found @0xffe2c344
DEF(viewport_fb_d                           ,0x000050f0) // Found 0x50a4 (@0xffc409a4) + 0x4c (@0xffc409dc)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x50a4+0x4c)); } // Found @0xffc409a4 & 0xffc409dc
DEF(jpeg_count_str                          ,0x00049a80) // Found @0xffd5e8c0
//char *camera_jpeg_count_str()    { return (char*)0x00049a80; }             // Found @0xffd5e8c0
//long hook_raw_size()             { return 0x008d0a68; }                    // Found @0xffe2e5c0
//int get_flash_params_count(void) { return 0x73; }                          // Found @0xffd2a71c

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe52658, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe52660, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x04000000 }, // Found @0xffe525c8, levent 0x600 (uses inverted logic in physw_status)
//    { 2, KEY_UP              ,0x00000001 }, // Found @0xffe525d8, levent 0x04
//    { 2, KEY_DOWN            ,0x00000002 }, // Found @0xffe525e0, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000004 }, // Found @0xffe525e8, levent 0x07
//    { 2, KEY_LEFT            ,0x00000008 }, // Found @0xffe525f0, levent 0x06
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe52600, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe52600, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe525f8, levent 0x00
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe52618, levent 0x08
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffe52620, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3152 // Found @0xffe25d64
//#define CAM_RAW_ROWS      2346 // Found @0xffe25d68
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc17e54

// Misc stuff
DEF(ctypes, 0xffe52156)

// For capt_seq.c
DEF(_nrflag,0x88d8) // Found @ ffd0d594 (0x88d8)
//static long *nrflag = (long*)(0x88d8);       // Found @ ffd0d594

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc17e18) //112
NHSTUB(Close                                  ,0xffc13b5c) //120
NHSTUB(CreateTask                             ,0xffc0b8e0) //120
NHSTUB(DebugAssert                            ,0xffc0bdb8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc134ec) //116
NHSTUB(DeleteFile_Fut                         ,0xffc13408) //112
NHSTUB(DoAELock                               ,0xffc15c80) //120
NHSTUB(DoAFLock                               ,0xffc157a0) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc15a90) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc53824) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc15bdc) //104
NHSTUB(ExitTask                               ,0xffc0bb70) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc218c8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc21a0c) //104
NHSTUB(Fclose_Fut                             ,0xffc13584) //120
NHSTUB(Feof_Fut                               ,0xffc13770) //  1
NHSTUB(Fflush_Fut                             ,0xffc137ac) //  1
NHSTUB(Fgets_Fut                              ,0xffc136d8) //  1
NHSTUB(Fopen_Fut                              ,0xffc13544) //120
NHSTUB(Fread_Fut                              ,0xffc13630) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc17e4c) //112
NHSTUB(Fseek_Fut                              ,0xffc13724) //120
NHSTUB(Fwrite_Fut                             ,0xffc13684) //120
NHSTUB(GetBatteryTemperature                  ,0xffc3309c) //102
NHSTUB(GetCCDTemperature                      ,0xffc3302c) //102
NHSTUB(GetCurrentAvValue                      ,0xffd03d24) //102
NHSTUB(GetDrive_ClusterSize                   ,0xffc3cdec) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc3ce54) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc3ce20) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffd02e1c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd03128) //  1
NHSTUB(GetKbdState                            ,0xffc30fdc) //109
NHSTUB(GetMemInfo                             ,0xffc03c40) //115
NHSTUB(GetOpticalTemperature                  ,0xffc3310c) //120
NHSTUB(GetParameterData                       ,0xffd2a6dc) //101
NHSTUB(GetPropertyCase                        ,0xffc57424) //102
NHSTUB(GetSystemTime                          ,0xffddb2fc) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffca1ddc) //102
NHSTUB(GetVRAMVPixelsSize                     ,0xffca1de8) //102
NHSTUB(GetZoomLensCurrentPoint                ,0xffd06ae0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdd26d0) //102
NHSTUB(GiveSemaphore                          ,0xffc0b844) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc97624) //102
NHSTUB(LEDDrive                               ,0xffc30884) //120
NHSTUB(LocalTime                              ,0xffc51544) //115
NHSTUB(LockMainPower                          ,0xffc5ba84) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc1347c) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe28e90) //102
NHSTUB(MoveIrisWithAv                         ,0xffdd7618) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdd7b9c) //120
NHSTUB(Open                                   ,0xffc13b34) //120
NHSTUB(PB2Rec                                 ,0xffc5e6a4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc46d04) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc46cdc) //120
NHSTUB(PT_PlaySound                           ,0xffc465f0) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5b0f4) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5b140) //120
NHSTUB(Read                                   ,0xffc0a15c) //120
NHSTUB(ReadFastDir                            ,0xffdc4b9c) //  1
NHSTUB(Rec2PB                                 ,0xffc5e6d4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd6789c) //104
NHSTUB(RenameFile_Fut                         ,0xffc133b4) //  1
NHSTUB(Restart                                ,0xffc19690) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe2b554) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5baf8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc61d9c) //120
NHSTUB(SetFileAttributes                      ,0xffc13e88) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13e38) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5b820) //  1
NHSTUB(SetParameterData                       ,0xffd2a64c) //101
NHSTUB(SetPropertyCase                        ,0xffc57324) //102
NHSTUB(SetScriptMode                          ,0xffc5b870) //120
NHSTUB(SleepTask                              ,0xffc17c9c) //120
NHSTUB(TakeSemaphore                          ,0xffc0b774) //120
NHSTUB(TurnOffBackLight                       ,0xffc662cc) //104
NHSTUB(TurnOnBackLight                        ,0xffc662b4) //104
NHSTUB(TurnOnDisplay                          ,0xffc2cd38) //120
NHSTUB(TurnOffDisplay                         ,0xffc2cd48) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd201e4) //120
NHSTUB(UnlockAE                               ,0xffc15cb0) //120
NHSTUB(UnlockAF                               ,0xffc158b8) //120
NHSTUB(UnlockMainPower                        ,0xffc5b9d8) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd2f750) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3cc2c) //105
NHSTUB(VbattGet                               ,0xffc105d0) //120
NHSTUB(Write                                  ,0xffc13c08) //120
NHSTUB(WriteSDCard                            ,0xffcf9440) //108
NHSTUB(_log                                   ,0xffe4ff5c) //111
NHSTUB(_log10                                 ,0xffe4eea0) //112
NHSTUB(_pow                                   ,0xffe4f010) //121
NHSTUB(_sqrt                                  ,0xffe512c4) //  1
NHSTUB(add_ptp_handler                        ,0xffd96b20) //121
NHSTUB(apex2us                                ,0xffd68dd8) //121
NHSTUB(close                                  ,0xffc09f74) //109
NHSTUB(err_init_task                          ,0xffc04e98) //111
NHSTUB(exmem_alloc                            ,0xffc5200c) //103
NHSTUB(exmem_free                             ,0xffc52084) //103
NHSTUB(free                                   ,0xffc03a98) //112
NHSTUB(kbd_p1_f                               ,0xffc11d08) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11d14) //109
NHSTUB(kbd_p2_f                               ,0xffc11548) //109
NHSTUB(kbd_read_keys                          ,0xffc11c0c) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc30bec) //109
NHSTUB(lseek                                  ,0xffc13c9c) //120
NHSTUB(malloc                                 ,0xffc039c4) //112
NHSTUB(memcmp                                 ,0xffc0d90c) //120
NHSTUB(memcpy                                 ,0xffc6ebb4) //120
NHSTUB(memset                                 ,0xffd67c50) //120
NHSTUB(mkdir                                  ,0xffc13f00) //109
NHSTUB(mktime_ext                             ,0xffc6f420) //  1
NHSTUB(open                                   ,0xffc09ec4) //109
NHSTUB(OpenFastDir                            ,0xffdc4b08) //  1
NHSTUB(closedir                               ,0xffdc4c6c) //  1
NHSTUB(qsort                                  ,0xffd68158) //  1
NHSTUB(rand                                   ,0xffc0da14) //121
NHSTUB(realloc                                ,0xffc03b78) //115
NHSTUB(reboot_fw_update                       ,0xffdc9470) //106
NHSTUB(set_control_event                      ,0xffc5b574) //  1
NHSTUB(srand                                  ,0xffc0da08) //122
NHSTUB(stat                                   ,0xffc13d68) //  1
NHSTUB(strcat                                 ,0xffc6e9a0) //  1
NHSTUB(strchr                                 ,0xffc6ea28) //  1
NHSTUB(strcmp                                 ,0xffc0d8a4) //120
NHSTUB(strcpy                                 ,0xffc0d88c) //120
NHSTUB(strftime                               ,0xffc6ee28) //  1
NHSTUB(strlen                                 ,0xffc0d8e8) //120
NHSTUB(strncmp                                ,0xffc6e9dc) //  1
NHSTUB(strncpy                                ,0xffc1d81c) //  1
NHSTUB(strrchr                                ,0xffc6ea4c) //  1
NHSTUB(strtol                                 ,0xffc1da54) //101
NHSTUB(strtolx                                ,0xffc1d858) //109
   DEF(task_CaptSeq                           ,0xffc48dc0) //120
   DEF(task_ExpDrv                            ,0xffc905d4) //120
   DEF(task_FileWrite                         ,0xffdc18e4) //120
   DEF(task_InitFileModules                   ,0xffc5f114) //120
   DEF(task_MovieRecord                       ,0xffc458f4) //120
   DEF(task_PhySw                             ,0xffc118a4) //120
NHSTUB(time                                   ,0xffc513f8) //109
NHSTUB(vsprintf                               ,0xffc0d80c) //115
NHSTUB(EngDrvRead                             ,0xffc12b48) //102
