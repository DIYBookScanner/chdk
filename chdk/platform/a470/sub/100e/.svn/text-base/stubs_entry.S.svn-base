// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00E   // Found @ 0xffc5601c, "GM1.00E" @ 0xffc56029
//   Firmware build timestamp: Jan  8 2008 16:51:20
//   Canon PowerShot A470

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12666 (0x317a) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x000a5718  (*** DOES NOT MATCH MAKEFILE VALUE 0x000a5798***)
//   KEYSYS = d3enc              // Found @ 0xffff1a98
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff1a78
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffddb06c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffddb02c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(PutInNdFilter                        ,0xffdd6fc4) //102        *** != 0xffe267b4
//NHSTUB(PutOutNdFilter                       ,0xffdd6fe8) //102        *** != 0xffe267ec
//NHSTUB(kbd_pwr_off                          ,0xffc30b30) //  2 67%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffde7148 -> ffe8fab4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0001007c) // Found @0xffc11c0c
DEF(physw_run                               ,0x00001bf0) // Found @0xffc118a8
DEF(physw_sleep_delay                       ,0x00001bee) // Found @0xffc118a8
DEF(levent_table                            ,0xffe72ec8) // Found @0xffe72ec8
DEF(FlashParamsTable                        ,0xffe8fc68) // Found @0xffe8fc68
DEF(movie_status                            ,0x000051d8) // Found @0xffc45174
DEF(canon_menu_active                       ,0x00009014) // Found @0xffd1eec4
DEF(canon_shoot_menu_active                 ,0x000097e1) // Found @0xffd37684
DEF(playrec_mode                            ,0x00005348) // Found @0xffc4b760
DEF(zoom_status                             ,0x0000d020) // Found @0xffde8948
DEF(some_flag_for_af_scan                   ,0x0000cd9c) // Found @0xffdd73a8
DEF(zoom_busy                               ,0x000083a4) // Found @0xffd05d3c
DEF(focus_busy                              ,0x000082b0) // Found @0xffd018d0
DEF(recreview_hold                          ,0x00005b3c) // Found @0xffc63e24
// Camera appears to have only 1 RAW buffer @ 0x10f06b20 (Found @0xffe2db28)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc2cc48
//void *vid_get_viewport_fb()      { return (void*)0x10659d50; }             // Found @0xffe2b908
DEF(viewport_fb_d                           ,0x000050cc) // Found 0x5080 (@0xffc40488) + 0x4c (@0xffc404c0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x5080+0x4c)); } // Found @0xffc40488 & 0xffc404c0
DEF(jpeg_count_str                          ,0x00049a00) // Found @0xffd5de80
//char *camera_jpeg_count_str()    { return (char*)0x00049a00; }             // Found @0xffd5de80
//long hook_raw_size()             { return 0x008d0a68; }                    // Found @0xffe2db84
//int get_flash_params_count(void) { return 0x73; }                          // Found @0xffd29cdc

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe51bbc, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe51bc4, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x04000000 }, // Found @0xffe51b2c, levent 0x600 (uses inverted logic in physw_status)
//    { 2, KEY_UP              ,0x00000001 }, // Found @0xffe51b3c, levent 0x04
//    { 2, KEY_DOWN            ,0x00000002 }, // Found @0xffe51b44, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000004 }, // Found @0xffe51b4c, levent 0x07
//    { 2, KEY_LEFT            ,0x00000008 }, // Found @0xffe51b54, levent 0x06
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe51b64, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe51b64, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe51b5c, levent 0x00
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe51b7c, levent 0x08
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffe51b84, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3152 // Found @0xffe25328
//#define CAM_RAW_ROWS      2346 // Found @0xffe2532c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc17e54

// Misc stuff
DEF(ctypes, 0xffe5171a)

// For capt_seq.c
DEF(_nrflag,0x8888) // Found @ ffd0cb54 (0x8888)
//static long *nrflag = (long*)(0x8888);       // Found @ ffd0cb54

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
NHSTUB(ExecuteEventProcedure                  ,0xffc53308) //104
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
NHSTUB(GetBatteryTemperature                  ,0xffc32bd8) //102
NHSTUB(GetCCDTemperature                      ,0xffc32b68) //102
NHSTUB(GetCurrentAvValue                      ,0xffd032e4) //102
NHSTUB(GetDrive_ClusterSize                   ,0xffc3c8d0) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc3c938) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc3c904) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffd023dc) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd026e8) //  1
NHSTUB(GetKbdState                            ,0xffc30b18) //109
NHSTUB(GetMemInfo                             ,0xffc03c40) //115
NHSTUB(GetOpticalTemperature                  ,0xffc32c48) //120
NHSTUB(GetParameterData                       ,0xffd29c9c) //101
NHSTUB(GetPropertyCase                        ,0xffc56f08) //102
NHSTUB(GetSystemTime                          ,0xffdda8c0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffca18c0) //102
NHSTUB(GetVRAMVPixelsSize                     ,0xffca18cc) //102
NHSTUB(GetZoomLensCurrentPoint                ,0xffd060a0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdd1c94) //102
NHSTUB(GiveSemaphore                          ,0xffc0b844) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc97108) //102
NHSTUB(LEDDrive                               ,0xffc303c0) //120
NHSTUB(LocalTime                              ,0xffc51028) //115
NHSTUB(LockMainPower                          ,0xffc5b568) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc1347c) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe28454) //102
NHSTUB(MoveIrisWithAv                         ,0xffdd6bdc) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdd7160) //120
NHSTUB(Open                                   ,0xffc13b34) //120
NHSTUB(PB2Rec                                 ,0xffc5e188) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc467e8) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc467c0) //120
NHSTUB(PT_PlaySound                           ,0xffc460d4) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5abd8) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5ac24) //120
NHSTUB(Read                                   ,0xffc0a15c) //120
NHSTUB(ReadFastDir                            ,0xffdc4160) //  1
NHSTUB(Rec2PB                                 ,0xffc5e1b8) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd66e5c) //104
NHSTUB(RenameFile_Fut                         ,0xffc133b4) //  1
NHSTUB(Restart                                ,0xffc19690) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe2ab18) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5b5dc) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc61880) //120
NHSTUB(SetFileAttributes                      ,0xffc13e88) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13e38) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5b304) //  1
NHSTUB(SetParameterData                       ,0xffd29c0c) //101
NHSTUB(SetPropertyCase                        ,0xffc56e08) //102
NHSTUB(SetScriptMode                          ,0xffc5b354) //120
NHSTUB(SleepTask                              ,0xffc17c9c) //120
NHSTUB(TakeSemaphore                          ,0xffc0b774) //120
NHSTUB(TurnOffBackLight                       ,0xffc65db0) //104
NHSTUB(TurnOnBackLight                        ,0xffc65d98) //104
NHSTUB(TurnOnDisplay                          ,0xffc2ccf8) //120
NHSTUB(TurnOffDisplay                         ,0xffc2cd08) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd1f7a4) //120
NHSTUB(UnlockAE                               ,0xffc15cb0) //120
NHSTUB(UnlockAF                               ,0xffc158b8) //120
NHSTUB(UnlockMainPower                        ,0xffc5b4bc) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd2ed10) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3c710) //105
NHSTUB(VbattGet                               ,0xffc105d0) //120
NHSTUB(Write                                  ,0xffc13c08) //120
NHSTUB(WriteSDCard                            ,0xffcf8a00) //108
NHSTUB(_log                                   ,0xffe4f520) //111
NHSTUB(_log10                                 ,0xffe4e464) //112
NHSTUB(_pow                                   ,0xffe4e5d4) //121
NHSTUB(_sqrt                                  ,0xffe50888) //  1
NHSTUB(add_ptp_handler                        ,0xffd960e4) //121
NHSTUB(apex2us                                ,0xffd68398) //121
NHSTUB(close                                  ,0xffc09f74) //109
NHSTUB(err_init_task                          ,0xffc04e98) //111
NHSTUB(exmem_alloc                            ,0xffc51af0) //103
NHSTUB(exmem_free                             ,0xffc51b68) //103
NHSTUB(free                                   ,0xffc03a98) //112
NHSTUB(kbd_p1_f                               ,0xffc11d08) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11d14) //109
NHSTUB(kbd_p2_f                               ,0xffc11548) //109
NHSTUB(kbd_read_keys                          ,0xffc11c0c) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc30728) //109
NHSTUB(lseek                                  ,0xffc13c9c) //120
NHSTUB(malloc                                 ,0xffc039c4) //112
NHSTUB(memcmp                                 ,0xffc0d90c) //120
NHSTUB(memcpy                                 ,0xffc6e698) //120
NHSTUB(memset                                 ,0xffd67210) //120
NHSTUB(mkdir                                  ,0xffc13f00) //109
NHSTUB(mktime_ext                             ,0xffc6ef04) //  1
NHSTUB(open                                   ,0xffc09ec4) //109
NHSTUB(OpenFastDir                            ,0xffdc40cc) //  1
NHSTUB(closedir                               ,0xffdc4230) //  1
NHSTUB(qsort                                  ,0xffd67718) //  1
NHSTUB(rand                                   ,0xffc0da14) //121
NHSTUB(realloc                                ,0xffc03b78) //115
NHSTUB(reboot_fw_update                       ,0xffdc8a34) //106
NHSTUB(set_control_event                      ,0xffc5b058) //  1
NHSTUB(srand                                  ,0xffc0da08) //122
NHSTUB(stat                                   ,0xffc13d68) //  1
NHSTUB(strcat                                 ,0xffc6e484) //  1
NHSTUB(strchr                                 ,0xffc6e50c) //  1
NHSTUB(strcmp                                 ,0xffc0d8a4) //120
NHSTUB(strcpy                                 ,0xffc0d88c) //120
NHSTUB(strftime                               ,0xffc6e90c) //  1
NHSTUB(strlen                                 ,0xffc0d8e8) //120
NHSTUB(strncmp                                ,0xffc6e4c0) //  1
NHSTUB(strncpy                                ,0xffc1d81c) //  1
NHSTUB(strrchr                                ,0xffc6e530) //  1
NHSTUB(strtol                                 ,0xffc1da54) //101
NHSTUB(strtolx                                ,0xffc1d858) //109
   DEF(task_CaptSeq                           ,0xffc488a4) //120
   DEF(task_ExpDrv                            ,0xffc900b8) //120
   DEF(task_FileWrite                         ,0xffdc0ea8) //120
   DEF(task_InitFileModules                   ,0xffc5ebf8) //120
   DEF(task_MovieRecord                       ,0xffc453d8) //120
   DEF(task_PhySw                             ,0xffc118a4) //120
NHSTUB(time                                   ,0xffc50edc) //109
NHSTUB(vsprintf                               ,0xffc0d80c) //115
NHSTUB(EngDrvRead                             ,0xffc12b48) //102
