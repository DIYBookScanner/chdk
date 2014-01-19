// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R39 (DRYOS version 2.3, release #0039)
//   Firmware Ver GM1.00B   // Found @ 0xffc5fdec, "GM1.00B" @ 0xffc5fdf9
//   Firmware build timestamp: Jun  5 2009 17:09:33
//   Canon PowerShot SX120 IS

// Values for makefile.inc
//   PLATFORMOSVER = 39
//   PLATFORMID = 12768 (0x31e0) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0010a6ac
//   KEYSYS = d4                 // Found @ 0xffff1d0c
//   NEED_ENCODED_DISKBOOT = 3   // Found @ 0xffff1d1c
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xffd20e2c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd20dec

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetDrive_ClusterSize                 ,0xffc4591c) //  5        *** != 0xffc45918
//NHSTUB(GetDrive_FreeClusters                ,0xffc4597c) //  5        *** != 0xffc45978
//NHSTUB(GetDrive_TotalClusters               ,0xffc45600) //  3        *** != 0xffc45948
// ALT: NHSTUB(GetDrive_TotalClusters, 0xffc45880) // 3 12/0
// ALT: NHSTUB(GetDrive_TotalClusters, 0xffc458ac) // 3 12/0
//NHSTUB(RefreshPhysicalScreen                ,0xffd90b78) //104        *** != 0xffd9098c
//NHSTUB(ScreenUnlock                         ,0xffd9098c) //117        *** != 0xffd90b78
//NHSTUB(SetScriptMode                        ,0xffc65c00) //120        *** != 0xffc63b40
//NHSTUB(kbd_pwr_off                          ,0xffc36f50) //  2 64%    *** != 0xffc36f60
NHSTUB(kbd_pwr_on                             ,0xffc36f10) //  2 82%
//NHSTUB(stat                                 ,0xffc13ae0) //109        *** != 0xffc13a9c

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe1dae4 -> ffeec334
// Current modemap entry not found in firmware - MODE_VIDEO_COMPACT        2602

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000d148) // Found @0xffc119cc
DEF(physw_run                               ,0x00001bec) // Found @0xffc1163c
DEF(physw_sleep_delay                       ,0x00001bea) // Found @0xffc1163c
DEF(levent_table                            ,0xffeb9d1c) // Found @0xffeb9d1c
DEF(FlashParamsTable                        ,0xffeec518) // Found @0xffeec518
DEF(movie_status                            ,0x000061d8) // Found @0xffd1429c
DEF(full_screen_refresh                     ,0x0000829c) // Found @0xffd8ea50
DEF(canon_menu_active                       ,0x00002e8c) // Found @0xffc61838
DEF(canon_shoot_menu_active                 ,0x000072d5) // Found @0xffd4d33c
DEF(playrec_mode                            ,0x00002bcc) // Found @0xffc542ac
DEF(zoom_status                             ,0x0000a4d4) // Found @0xffe1f314
DEF(some_flag_for_af_scan                   ,0x000066ac) // Found @0xffd16e3c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 23 entries in the table - set NUM_FL to 23
DEF(focus_len_table                         ,0xfffe328c) // Found @0xfffe328c
DEF(zoom_busy                               ,0x00006108) // Found @0xffd10868
DEF(focus_busy                              ,0x00005ffc) // Found @0xffd0b93c
//DEF(recreview_hold                          ,0x000037c0) // Found @0xffc6ed0c, ** != ** stubs_min = 0x00006f34 (0x6E84+0xB0)
// Palette colour tables  found @ 0xffecb874
DEF(active_palette_buffer                   ,0x000082a4) // Found @0xffd8e98c
DEF(palette_buffer_ptr                      ,0x000082b0) // Found @0xffd8e674
// Offset from start of palette_buffer to color data = 8 (Found @0xffe4ad74)
// Camera appears to have only 1 RAW buffer @ 0x414ef7e0 (Found @0xffe687a8)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xffc32730
//void *vid_get_viewport_fb()      { return (void*)0x40768620; }             // Found @0xffe660b4
DEF(viewport_fb_d                           ,0x0000295c) // Found 0x2904 (@0xffc470bc) + 0x58 (@0xffc470e8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2904+0x58)); } // Found @0xffc470bc & 0xffc470e8
DEF(jpeg_count_str                          ,0x00052c6c) // Found @0xffd83d88
//char *camera_jpeg_count_str()    { return (char*)0x00052c6c; }             // Found @0xffd83d88
//long hook_raw_size()             { return 0x00ed09f0; }                    // Found @0xffe68804
//int get_flash_params_count(void) { return 0x84; }                          // Found @0xffd39830

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe9a70c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe9a718, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xffe9a664, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xffe9a664, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xffe9a658, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffe9a670, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000020 }, // Found @0xffe9a67c, levent 0x03
//    { 2, KEY_POWER           ,0x00000040 }, // Found @0xffe9a688, levent 0x600 (uses inverted logic in physw_status)
//    { 2, KEY_PLAYBACK        ,0x00000080 }, // Found @0xffe9a694, levent 0x601 (uses inverted logic in physw_status)
//    { 2, KEY_UP              ,0x00000100 }, // Found @0xffe9a6a0, levent 0x04
//    { 2, KEY_DOWN            ,0x00000200 }, // Found @0xffe9a6ac, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xffe9a6b8, levent 0x07
//    { 2, KEY_LEFT            ,0x00000800 }, // Found @0xffe9a6c4, levent 0x06
//    { 2, KEY_SET             ,0x00001000 }, // Found @0xffe9a6d0, levent 0x08
//    { 2, KEY_MENU            ,0x00002000 }, // Found @0xffe9a6dc, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00004000 }, // Found @0xffe9a6e8, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3728 // Found @0xffce4274
//#define CAM_RAW_ROWS      2778 // Found @0xffce427c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xffc170b0

// Misc stuff
DEF(ctypes, 0xffe9450e)

// For capt_seq.c
DEF(_nrflag,0x6690) // Found @ ffd18ed8 (0x6698) & ffd18ef8 (-0x08)
//static long *nrflag = (long*)(0x6698-0x08);  // Found @ ffd18ed8 & ffd18ef4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc1706c) //112
NHSTUB(Close                                  ,0xffc13890) //120
NHSTUB(CreateTask                             ,0xffc0ad70) //120
NHSTUB(DebugAssert                            ,0xffc0b048) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc13220) //116
NHSTUB(DeleteFile_Fut                         ,0xffc1313c) //112
NHSTUB(DoAELock                               ,0xffc153c4) //120
NHSTUB(DoAFLock                               ,0xffc1516c) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc152bc) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc5cf90) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc15300) //104
NHSTUB(ExitTask                               ,0xffc0b000) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc1fb10) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc1fbe8) //104
NHSTUB(Fclose_Fut                             ,0xffc132b8) //120
NHSTUB(Feof_Fut                               ,0xffc134a4) //  1
NHSTUB(Fflush_Fut                             ,0xffc134e0) //  1
NHSTUB(Fgets_Fut                              ,0xffc1340c) //  1
NHSTUB(Fopen_Fut                              ,0xffc13278) //120
NHSTUB(Fread_Fut                              ,0xffc13364) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc170ac) //112
NHSTUB(Fseek_Fut                              ,0xffc13458) //120
NHSTUB(Fwrite_Fut                             ,0xffc133b8) //120
NHSTUB(GetBatteryTemperature                  ,0xffc394d8) //102
NHSTUB(GetCCDTemperature                      ,0xffc39464) //102
NHSTUB(GetCurrentAvValue                      ,0xffd0e010) //120
NHSTUB(GetFocusLensSubjectDistance            ,0xffd0c5f0) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd0ca40) //  3
NHSTUB(GetImageFolder                         ,0xffcec100) //122
NHSTUB(GetKbdState                            ,0xffc36edc) //109
NHSTUB(GetMemInfo                             ,0xffc08d8c) //115
NHSTUB(GetOpticalTemperature                  ,0xffc39550) //120
NHSTUB(GetParameterData                       ,0xffd397f0) //101
NHSTUB(GetPropertyCase                        ,0xffc60ce0) //102
NHSTUB(GetSystemTime                          ,0xffe14348) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc29984) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc29990) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd10bdc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe0d1e4) //102
NHSTUB(GiveSemaphore                          ,0xffc16a88) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc900b0) //102
NHSTUB(LEDDrive                               ,0xffc36434) //120
NHSTUB(LocalTime                              ,0xffc5ac40) //115
NHSTUB(LockMainPower                          ,0xffc65e60) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc131b0) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe62adc) //102
NHSTUB(MoveIrisWithAv                         ,0xffe1237c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe129c8) //120
NHSTUB(Open                                   ,0xffc13868) //120
NHSTUB(PB2Rec                                 ,0xffc678e0) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc4cf48) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc4cf20) //120
NHSTUB(PT_PlaySound                           ,0xffc55fb8) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc63d5c) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc63da8) //120
NHSTUB(PutInNdFilter                          ,0xffe60828) //102
NHSTUB(PutOutNdFilter                         ,0xffe60860) //102
NHSTUB(Read                                   ,0xffc09894) //120
NHSTUB(ReadFastDir                            ,0xffdfed14) //  1
NHSTUB(Rec2PB                                 ,0xffc68cdc) //104
NHSTUB(RenameFile_Fut                         ,0xffc130e8) //  1
NHSTUB(Restart                                ,0xffc187c0) //106
NHSTUB(ScreenLock                             ,0xffd9094c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffe652c4) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc65ed4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc6c288) //120
NHSTUB(SetFileAttributes                      ,0xffc13bbc) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13b6c) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc65bb0) //101
NHSTUB(SetParameterData                       ,0xffd39760) //101
NHSTUB(SetPropertyCase                        ,0xffc60be4) //102
NHSTUB(SleepTask                              ,0xffc16cf0) //120
NHSTUB(TakeSemaphore                          ,0xffc169b8) //120
NHSTUB(TurnOffBackLight                       ,0xffc71424) //104
NHSTUB(TurnOnBackLight                        ,0xffc7140c) //104
NHSTUB(TurnOnDisplay                          ,0xffc3291c) //120
NHSTUB(TurnOffDisplay                         ,0xffc3292c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd2b640) //120
NHSTUB(UnlockAE                               ,0xffc153e8) //120
NHSTUB(UnlockAF                               ,0xffc151a4) //120
NHSTUB(UnlockMainPower                        ,0xffc65db4) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3fd2c) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc45758) //105
NHSTUB(VbattGet                               ,0xffc10314) //120
NHSTUB(Write                                  ,0xffc1393c) //120
NHSTUB(WriteSDCard                            ,0xffcfff68) //108
NHSTUB(_log                                   ,0xffe92070) //111
NHSTUB(_log10                                 ,0xffe90fb4) //112
NHSTUB(_pow                                   ,0xffe91124) //121
NHSTUB(_sqrt                                  ,0xffe933d8) //  1
NHSTUB(add_ptp_handler                        ,0xffdd0ac4) //121
NHSTUB(apex2us                                ,0xffd91ac4) //121
NHSTUB(close                                  ,0xffc096ac) //109
NHSTUB(err_init_task                          ,0xffc04c44) //111
NHSTUB(exmem_alloc                            ,0xffc5b874) //103
NHSTUB(exmem_free                             ,0xffc5b8ec) //103
NHSTUB(free                                   ,0xffc0379c) //112
NHSTUB(kbd_p1_f                               ,0xffc11a50) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11a5c) //109
NHSTUB(kbd_p2_f                               ,0xffc11308) //109
NHSTUB(kbd_read_keys                          ,0xffc119cc) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc36858) //109
NHSTUB(lseek                                  ,0xffc139d0) //120
NHSTUB(malloc                                 ,0xffc03740) //112
NHSTUB(memcmp                                 ,0xffc0cbbc) //120
NHSTUB(memcpy                                 ,0xffc75854) //120
NHSTUB(memset                                 ,0xffd90cf4) //120
NHSTUB(mkdir                                  ,0xffc13c34) //109
NHSTUB(mktime_ext                             ,0xffc760c0) //  1
NHSTUB(open                                   ,0xffc095fc) //109
NHSTUB(OpenFastDir                            ,0xffdfec80) //  1
NHSTUB(closedir                               ,0xffdfede4) //  1
NHSTUB(qsort                                  ,0xffe4ef08) //  1
NHSTUB(rand                                   ,0xffc0ccc4) //121
NHSTUB(realloc                                ,0xffd90d70) //115
NHSTUB(reboot_fw_update                       ,0xffe027fc) //106
NHSTUB(set_control_event                      ,0xffc65804) //111
NHSTUB(srand                                  ,0xffc0ccb8) //122
NHSTUB(strcat                                 ,0xffc75668) //  1
NHSTUB(strchr                                 ,0xffc756f0) //  1
NHSTUB(strcmp                                 ,0xffc0cb54) //120
NHSTUB(strcpy                                 ,0xffc0cb3c) //120
NHSTUB(strftime                               ,0xffc75ac8) //  1
NHSTUB(strlen                                 ,0xffc0cb98) //120
NHSTUB(strncmp                                ,0xffc756a4) //  1
NHSTUB(strncpy                                ,0xffc1c5b0) //  1
NHSTUB(strrchr                                ,0xffd90ccc) //  1
NHSTUB(strtol                                 ,0xffc1c7e8) //101
NHSTUB(strtolx                                ,0xffc1c5ec) //109
   DEF(task_CaptSeq                           ,0xffc4f640) //120
   DEF(task_ExpDrv                            ,0xffc86e80) //120
   DEF(task_FileWrite                         ,0xffdfa744) //120
   DEF(task_InitFileModules                   ,0xffc696ac) //120
   DEF(task_MovieRecord                       ,0xffd144f0) //120
   DEF(task_PhySw                             ,0xffc11638) //120
   DEF(task_RotaryEncoder                     ,0xffc37070) //120
NHSTUB(time                                   ,0xffc5aaf4) //109
NHSTUB(vsprintf                               ,0xffc0cb00) //115
NHSTUB(EngDrvRead                             ,0xffc1287c) //102
