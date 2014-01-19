// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00B   // Found @ 0xffc5e390, "GM1.00B" @ 0xffc5e39d
//   Firmware build timestamp: Jun 25 2008 15:08:34
//   Canon PowerShot SX110 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12690 (0x3192) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000a2728
//   KEYSYS = d4                 // Found @ 0xffff1a08
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff1a18
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd24b80
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd24b40

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetBatteryTemperature                ,0xffc3885c) //102        *** != 0xffc387ec
//NHSTUB(LEDDrive                             ,0xffc35930) //120        *** != 0xffd17758
//NHSTUB(kbd_pwr_off                          ,0xffc36434) //  2 60%    *** != 0xffc36444

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe1421c -> ffedd5f4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000fb38) // Found @0xffc113f0
DEF(physw_run                               ,0x00001be4) // Found @0xffc11064
DEF(physw_sleep_delay                       ,0x00001be2) // Found @0xffc11064
DEF(levent_table                            ,0xffeb9c50) // Found @0xffeb9c50
DEF(FlashParamsTable                        ,0xffedd7c4) // Found @0xffedd7c4
DEF(movie_status                            ,0x00005278) // Found @0xffc4ca28
DEF(canon_menu_active                       ,0x000093d4) // Found @0xffd2c7f4
DEF(canon_shoot_menu_active                 ,0x00009b0d) // Found @0xffd49ac0
DEF(playrec_mode                            ,0x0000540c) // Found @0xffc542a4
DEF(zoom_status                             ,0x0000c79c) // Found @0xffe15a30
DEF(some_flag_for_af_scan                   ,0x00008c78) // Found @0xffd19670
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 23 entries in the table - set NUM_FL to 23
DEF(focus_len_table                         ,0xfffe31bc) // Found @0xfffe31bc
DEF(zoom_busy                               ,0x000086cc) // Found @0xffd12000
DEF(focus_busy                              ,0x000085bc) // Found @0xffd0cda4
//DEF(recreview_hold                          ,0x00005fa8) // Found @0xffc6d37c, ** != ** stubs_min = 0x00009840 (0x9770+0xD0)
// Camera has 2 RAW buffers @ 0x10805040 & 0x11a34c40
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffe9f8c0) // Found @0xffe9f8c0
DEF(active_raw_buffer                       ,0x000053bc) // Found @0xffc51968

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc31d1c
//void *vid_get_viewport_fb()      { return (void*)0x10659de0; }             // Found @0xffe5e820
DEF(viewport_fb_d                           ,0x00005114) // Found 0x50c0 (@0xffc46568) + 0x54 (@0xffc46594)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x50c0+0x54)); } // Found @0xffc46568 & 0xffc46594
DEF(jpeg_count_str                          ,0x00045e58) // Found @0xffd84a7c
//char *camera_jpeg_count_str()    { return (char*)0x00045e58; }             // Found @0xffd84a7c
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe60bb4
//int get_flash_params_count(void) { return 0x77; }                          // Found @0xffd389b8

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe97f24, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe97f30, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xffe97e04, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xffe97e04, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xffe97df8, levent 0x00
//    { 0, KEY_POWER           ,0x00004000 }, // Found @0xffe97e1c, levent 0x600 (uses inverted logic in physw_status)
//    { 0, KEY_PLAYBACK        ,0x00800000 }, // Found @0xffe97e40, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_ZOOM_IN         ,0x00000100 }, // Found @0xffe97e88, levent 0x02
//    { 1, KEY_ZOOM_OUT        ,0x00000200 }, // Found @0xffe97e94, levent 0x03
//    { 1, KEY_RIGHT           ,0x00010000 }, // Found @0xffe97ea0, levent 0x07
//    { 1, KEY_DOWN            ,0x00020000 }, // Found @0xffe97eac, levent 0x05
//    { 1, KEY_LEFT            ,0x00040000 }, // Found @0xffe97eb8, levent 0x06
//    { 1, KEY_UP              ,0x00080000 }, // Found @0xffe97ec4, levent 0x04
//    { 1, KEY_SET             ,0x00100000 }, // Found @0xffe97ed0, levent 0x08
//    { 1, KEY_DISPLAY         ,0x02000000 }, // Found @0xffe97ee8, levent 0x0a
//    { 1, KEY_MENU            ,0x08000000 }, // Found @0xffe97f00, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffe578ec
//#define CAM_RAW_ROWS      2772 // Found @0xffe578f4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc1786c

// Misc stuff
DEF(ctypes, 0xffe9289e)

// For capt_seq.c
DEF(_nrflag,0x8c64) // Found @ ffd1b5ac (0x8c68) & ffd1b5c8 (-0x04)
//static long *nrflag = (long*)(0x8c68-0x04);  // Found @ ffd1b5ac & ffd1b5c4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc17828) //112
NHSTUB(Close                                  ,0xffc13348) //120
NHSTUB(CreateTask                             ,0xffc0b8c0) //120
NHSTUB(DebugAssert                            ,0xffc0bd98) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc12cd8) //116
NHSTUB(DeleteFile_Fut                         ,0xffc12bf4) //112
NHSTUB(DoAELock                               ,0xffc153bc) //120
NHSTUB(DoAFLock                               ,0xffc15048) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc15318) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc5b5b8) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc1535c) //104
NHSTUB(ExitTask                               ,0xffc0bb50) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc20894) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc209d8) //104
NHSTUB(Fclose_Fut                             ,0xffc12d70) //120
NHSTUB(Feof_Fut                               ,0xffc12f5c) //  1
NHSTUB(Fflush_Fut                             ,0xffc12f98) //  1
NHSTUB(Fgets_Fut                              ,0xffc12ec4) //  1
NHSTUB(Fopen_Fut                              ,0xffc12d30) //120
NHSTUB(Fread_Fut                              ,0xffc12e1c) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc17868) //112
NHSTUB(Fseek_Fut                              ,0xffc12f10) //120
NHSTUB(Fwrite_Fut                             ,0xffc12e70) //120
NHSTUB(GetCCDTemperature                      ,0xffc387ec) //102
NHSTUB(GetCurrentAvValue                      ,0xffd0f3d4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc44dcc) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc44e34) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc44e00) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffd0d8d4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd0dbe0) //  3
NHSTUB(GetKbdState                            ,0xffc362cc) //109
NHSTUB(GetMemInfo                             ,0xffc03c28) //115
NHSTUB(GetOpticalTemperature                  ,0xffc388cc) //120
NHSTUB(GetParameterData                       ,0xffd38978) //101
NHSTUB(GetPropertyCase                        ,0xffc5f2a0) //102
NHSTUB(GetSystemTime                          ,0xffe08398) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc2aab4) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc2aac0) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd12370) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe02890) //102
NHSTUB(GiveSemaphore                          ,0xffc0b81c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc92e08) //102
NHSTUB(LocalTime                              ,0xffc595bc) //115
NHSTUB(LockMainPower                          ,0xffc63da0) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc12c68) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe5b264) //102
NHSTUB(MoveIrisWithAv                         ,0xffe04a30) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe0507c) //120
NHSTUB(Open                                   ,0xffc13320) //120
NHSTUB(PB2Rec                                 ,0xffc65a2c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc4ddc4) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc4dd9c) //120
NHSTUB(PT_PlaySound                           ,0xffc4d9ac) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc61bb4) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc61c00) //120
NHSTUB(PutInNdFilter                          ,0xffe5903c) //102
NHSTUB(PutOutNdFilter                         ,0xffe59074) //102
NHSTUB(Read                                   ,0xffc0a138) //120
NHSTUB(ReadFastDir                            ,0xffdf35b8) //  1
NHSTUB(Rec2PB                                 ,0xffc65a80) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd8fc00) //104
NHSTUB(RenameFile_Fut                         ,0xffc12ba0) //  1
NHSTUB(Restart                                ,0xffc190a0) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe5da30) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc63e14) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc6a8c4) //120
NHSTUB(SetFileAttributes                      ,0xffc13674) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc13624) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc63af0) //101
NHSTUB(SetParameterData                       ,0xffd388e8) //101
NHSTUB(SetPropertyCase                        ,0xffc5f198) //102
NHSTUB(SetScriptMode                          ,0xffc63b40) //120
NHSTUB(SleepTask                              ,0xffc176ac) //120
NHSTUB(TakeSemaphore                          ,0xffc0b74c) //120
NHSTUB(TurnOffBackLight                       ,0xffc6f9fc) //104
NHSTUB(TurnOnBackLight                        ,0xffc6f9e4) //104
NHSTUB(TurnOnDisplay                          ,0xffc31de4) //120
NHSTUB(TurnOffDisplay                         ,0xffc31df4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd2d3a0) //120
NHSTUB(UnlockAE                               ,0xffc153e0) //120
NHSTUB(UnlockAF                               ,0xffc1509c) //120
NHSTUB(UnlockMainPower                        ,0xffc63cf4) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3e944) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc44c0c) //105
NHSTUB(VbattGet                               ,0xffc10314) //120
NHSTUB(Write                                  ,0xffc133f4) //120
NHSTUB(WriteSDCard                            ,0xffd02b30) //108
NHSTUB(_log                                   ,0xffe90410) //111
NHSTUB(_log10                                 ,0xffe8f354) //112
NHSTUB(_pow                                   ,0xffe8f4c4) //121
NHSTUB(_sqrt                                  ,0xffe91778) //  1
NHSTUB(add_ptp_handler                        ,0xffdc1104) //121
NHSTUB(apex2us                                ,0xffd910e4) //121
NHSTUB(close                                  ,0xffc09f50) //109
NHSTUB(err_init_task                          ,0xffc04e84) //111
NHSTUB(exmem_alloc                            ,0xffc59dbc) //103
NHSTUB(exmem_free                             ,0xffc59e34) //103
NHSTUB(free                                   ,0xffc03a80) //112
NHSTUB(kbd_p1_f                               ,0xffc114f4) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc11500) //109
NHSTUB(kbd_p2_f                               ,0xffc10d04) //109
NHSTUB(kbd_read_keys                          ,0xffc113f0) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc35d7c) //109
NHSTUB(lseek                                  ,0xffc13488) //120
NHSTUB(malloc                                 ,0xffc039ac) //112
NHSTUB(memcmp                                 ,0xffc0d8b4) //120
NHSTUB(memcpy                                 ,0xffc74b70) //120
NHSTUB(memset                                 ,0xffd8ff54) //120
NHSTUB(mkdir                                  ,0xffc136ec) //109
NHSTUB(mktime_ext                             ,0xffc753dc) //  1
NHSTUB(open                                   ,0xffc09ea0) //109
NHSTUB(OpenFastDir                            ,0xffdf3524) //  1
NHSTUB(closedir                               ,0xffdf3688) //  1
NHSTUB(qsort                                  ,0xffd9045c) //  1
NHSTUB(rand                                   ,0xffc0d9bc) //121
NHSTUB(realloc                                ,0xffc03b60) //115
NHSTUB(reboot_fw_update                       ,0xffdf7e8c) //106
NHSTUB(set_control_event                      ,0xffc6376c) //111
NHSTUB(srand                                  ,0xffc0d9b0) //122
NHSTUB(stat                                   ,0xffc13554) //  1
NHSTUB(strcat                                 ,0xffc74984) //  1
NHSTUB(strchr                                 ,0xffc74a0c) //  1
NHSTUB(strcmp                                 ,0xffc0d84c) //120
NHSTUB(strcpy                                 ,0xffc0d834) //120
NHSTUB(strftime                               ,0xffc74de4) //  1
NHSTUB(strlen                                 ,0xffc0d890) //120
NHSTUB(strncmp                                ,0xffc749c0) //  1
NHSTUB(strncpy                                ,0xffc1d254) //  1
NHSTUB(strrchr                                ,0xffd8ff2c) //  1
NHSTUB(strtol                                 ,0xffc1d48c) //101
NHSTUB(strtolx                                ,0xffc1d290) //109
   DEF(task_CaptSeq                           ,0xffc503b0) //120
   DEF(task_ExpDrv                            ,0xffc8bddc) //120
   DEF(task_FileWrite                         ,0xffdefed8) //120
   DEF(task_InitFileModules                   ,0xffc67a68) //120
   DEF(task_MovieRecord                       ,0xffc4cc8c) //120
   DEF(task_PhySw                             ,0xffc11060) //120
   DEF(task_RotaryEncoder                     ,0xffc36528) //120
NHSTUB(time                                   ,0xffc59470) //109
NHSTUB(vsprintf                               ,0xffc0d7f8) //115
NHSTUB(EngDrvRead                             ,0xffc12334) //102
