// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00C   // Found @ 0xffc6b6c0, "GM1.00C" @ 0xffc6b6cd
//   Firmware build timestamp: Jan  7 2010 13:32:44
//   Canon PowerShot A3000 IS

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12786 (0x31f2) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00133d38
//   KEYSYS = d4a                // Found @ 0xffff1aac
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff1abc
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd1f374
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd1f334

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DoAFLock                             ,0xffc27744) //120        *** != 0xffc59f78
//NHSTUB(LEDDrive                             ,0xffc43a04) //120        *** != 0xffc43acc
//NHSTUB(ScreenLock                           ,0xffd86d9c) //117        *** != 0xffd86fa4
//NHSTUB(ScreenUnlock                         ,0xffd86de0) //117        *** != 0xffd85c54
//NHSTUB(SetScriptMode                        ,0xffc6fd38) //120        *** != 0xffc00f70
//NHSTUB(UnlockAF                             ,0xffc2777c) //120        *** != 0xffc59f88
//NHSTUB(kbd_pwr_off                          ,0xffc445a0) //  2 64%    *** != 0x00000000
NHSTUB(kbd_pwr_on                             ,0xffc44560) //  2 82%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe16228 -> ffeddb84
// Mode  2609 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002eed4) // Found @0xffc23cd4
DEF(physw_run                               ,0x00001bf0) // Found @0xffc23938
DEF(physw_sleep_delay                       ,0x00001bf8) // Found @0xffc23938
DEF(levent_table                            ,0xffeafe20) // Found @0xffeafe20
DEF(FlashParamsTable                        ,0xffeddd7c) // Found @0xffeddd7c
DEF(movie_status                            ,0x000056f8) // Found @0xffd13678
DEF(full_screen_refresh                     ,0x000076cc) // Found @0xffd8520c
DEF(canon_menu_active                       ,0x00002b7c) // Found @0xffc6d20c
DEF(canon_shoot_menu_active                 ,0x000068b1) // Found @0xffd4825c
DEF(playrec_mode                            ,0x000028d8) // Found @0xffc60944
DEF(zoom_status                             ,0x00009cd8) // Found @0xffe18568
DEF(some_flag_for_af_scan                   ,0x00005aa0) // Found @0xffd16004
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe29b0) // Found @0xfffe29b0
DEF(zoom_busy                               ,0x00005648) // Found @0xffd0f784
DEF(focus_busy                              ,0x000054ec) // Found @0xffd0b1b0
//DEF(recreview_hold                          ,0x00003174) // Found @0xffc78d30, ** != ** stubs_min = 0x00006598 (0x64CC+0xCC)
DEF(viewport_buffers                        ,0xffe98618) // Found @0xffcb932c
DEF(active_viewport_buffer                  ,0x00004290) // Found @0xffcb9174
// Camera appears to have only 1 RAW buffer @ 0x10e59860 (Found @0xffe65a8c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3fc80
//void *vid_get_viewport_fb()      { return (void*)0x10650100; }             // Found @0xffe62758
DEF(viewport_fb_d                           ,0x00002674) // Found 0x2620 (@0xffc53a98) + 0x54 (@0xffc53ad0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2620+0x54)); } // Found @0xffc53a98 & 0xffc53ad0
DEF(jpeg_count_str                          ,0x00075120) // Found @0xffd7bd90
//char *camera_jpeg_count_str()    { return (char*)0x00075120; }             // Found @0xffd7bd90
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe65ae8
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd36d50

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe9177c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe91788, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00000400 }, // Found @0xffe91674, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x20000000 }, // Found @0xffe9168c, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffe916bc, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffe916bc, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffe916b0, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe916c8, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe916d4, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe916e0, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe916ec, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe916f8, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe91704, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe91710, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffe9171c, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffe91728, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcee63c
//#define CAM_RAW_ROWS      2772 // Found @0xffcee648
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc296f0

// Misc stuff
DEF(ctypes, 0xffe90f92)

// For capt_seq.c
DEF(_nrflag,0x5a80) // Found @ ffd17f90 (0x5a88) & ffd17fb0 (-0x08)
//static long *nrflag = (long*)(0x5a88-0x08);  // Found @ ffd17f90 & ffd17fac

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc296ac) //112
NHSTUB(Close                                  ,0xffc262b8) //120
NHSTUB(CreateTask                             ,0xffc0f110) //120
NHSTUB(DebugAssert                            ,0xffc0f5e8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc25d14) //116
NHSTUB(DeleteFile_Fut                         ,0xffc25c30) //112
NHSTUB(DoAELock                               ,0xffc2788c) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc277f4) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc68958) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc27838) //104
NHSTUB(ExitTask                               ,0xffc0f3a0) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc35110) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc351e8) //104
NHSTUB(Fclose_Fut                             ,0xffc25dac) //120
NHSTUB(Feof_Fut                               ,0xffc25f98) //  1
NHSTUB(Fflush_Fut                             ,0xffc25fd4) //  1
NHSTUB(Fgets_Fut                              ,0xffc25f00) //  1
NHSTUB(Fopen_Fut                              ,0xffc25d6c) //120
NHSTUB(Fread_Fut                              ,0xffc25e58) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc296ec) //112
NHSTUB(Fseek_Fut                              ,0xffc25f4c) //120
NHSTUB(Fwrite_Fut                             ,0xffc25eac) //120
NHSTUB(GetBatteryTemperature                  ,0xffc46680) //102
NHSTUB(GetCCDTemperature                      ,0xffc4660c) //102
NHSTUB(GetCurrentAvValue                      ,0xffd0ca30) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc52440) //122
//NHSTUB(GetDrive_FreeClusters                ,0xffc524a0) //  4            == 0xffc524a0
NHSTUB(GetDrive_TotalClusters                 ,0xffc52474) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xffd0bd28) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd0c180) //  3
NHSTUB(GetImageFolder                         ,0xffcf55f8) //122
NHSTUB(GetKbdState                            ,0xffc4452c) //109
NHSTUB(GetMemInfo                             ,0xffc0a760) //115
NHSTUB(GetOpticalTemperature                  ,0xffc466f4) //120
NHSTUB(GetParameterData                       ,0xffd36d10) //101
NHSTUB(GetPropertyCase                        ,0xffc6c664) //102
NHSTUB(GetSystemTime                          ,0xffe082b8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcba764) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcba770) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd0fafc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdff8ec) //102
NHSTUB(GiveSemaphore                          ,0xffc0f06c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcaac70) //102
NHSTUB(LocalTime                              ,0xffc66668) //115
NHSTUB(LockMainPower                          ,0xffc6ff70) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc25ca4) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe5f1d8) //102
NHSTUB(MoveIrisWithAv                         ,0xffe050ac) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe0563c) //120
NHSTUB(Open                                   ,0xffc2624c) //120
NHSTUB(PB2Rec                                 ,0xffc72d38) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc59f28) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc59f00) //120
NHSTUB(PT_PlaySound                           ,0xffc624e8) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6f7a0) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc6f7ec) //120
NHSTUB(PutInNdFilter                          ,0xffe054a0) //102
NHSTUB(PutOutNdFilter                         ,0xffe054c4) //102
NHSTUB(Read                                   ,0xffc0b270) //120
NHSTUB(ReadFastDir                            ,0xffdf6414) //  4
NHSTUB(Rec2PB                                 ,0xffc72d78) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd85bf0) //104
NHSTUB(RenameFile_Fut                         ,0xffc25b9c) //116
NHSTUB(Restart                                ,0xffc2ae90) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe61968) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc6ffe4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc76674) //120
NHSTUB(SetFileAttributes                      ,0xffc265b0) //  3
NHSTUB(SetFileTimeStamp                       ,0xffc26554) //  4
NHSTUB(SetLogicalEventActive                  ,0xffc6fce8) //101
NHSTUB(SetParameterData                       ,0xffd36c80) //101
NHSTUB(SetPropertyCase                        ,0xffc6c534) //102
NHSTUB(SleepTask                              ,0xffc29530) //120
NHSTUB(TakeSemaphore                          ,0xffc0ef9c) //120
NHSTUB(TurnOffBackLight                       ,0xffc7b440) //104
NHSTUB(TurnOnBackLight                        ,0xffc7b428) //104
NHSTUB(TurnOnDisplay                          ,0xffc3ff5c) //120
NHSTUB(TurnOffDisplay                         ,0xffc3ff88) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd27398) //120
NHSTUB(UnlockAE                               ,0xffc278b0) //120
NHSTUB(UnlockMainPower                        ,0xffc6fec4) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3cc54) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc522c0) //105
NHSTUB(VbattGet                               ,0xffc22cf0) //120
NHSTUB(Write                                  ,0xffc26348) //120
NHSTUB(WriteSDCard                            ,0xffd00d4c) //108
NHSTUB(_log                                   ,0xffe8eaf4) //111
NHSTUB(_log10                                 ,0xffe8da38) //112
NHSTUB(_pow                                   ,0xffe8dba8) //121
NHSTUB(_sqrt                                  ,0xffe8fe5c) //  1
NHSTUB(add_ptp_handler                        ,0xffdc8e94) //121
NHSTUB(apex2us                                ,0xffd880ec) //121
NHSTUB(close                                  ,0xffc0b088) //109
NHSTUB(err_init_task                          ,0xffc05f50) //111
NHSTUB(exmem_alloc                            ,0xffc67308) //103
NHSTUB(exmem_free                             ,0xffc67380) //103
NHSTUB(free                                   ,0xffc04160) //112
NHSTUB(kbd_p1_f                               ,0xffc23d54) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc23d60) //109
NHSTUB(kbd_p2_f                               ,0xffc23604) //109
NHSTUB(kbd_read_keys                          ,0xffc23cd4) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc43eac) //109
NHSTUB(lseek                                  ,0xffc263d4) //120
NHSTUB(malloc                                 ,0xffc04104) //112
NHSTUB(memcmp                                 ,0xffc11280) //120
NHSTUB(memcpy                                 ,0xffc2ec8c) //120
NHSTUB(memset                                 ,0xffd87124) //120
NHSTUB(mkdir                                  ,0xffc26754) //109
NHSTUB(mktime_ext                             ,0xffc806fc) //  1
NHSTUB(open                                   ,0xffc0afd8) //109
NHSTUB(OpenFastDir                            ,0xffdf62c0) //  4
NHSTUB(closedir                               ,0xffdf6270) //121
NHSTUB(qsort                                  ,0xffe4724c) //  4
NHSTUB(rand                                   ,0xffc11388) //121
NHSTUB(realloc                                ,0xffd871a0) //115
NHSTUB(reboot_fw_update                       ,0xffdf7c88) //106
NHSTUB(set_control_event                      ,0xffc6fa08) //111
NHSTUB(srand                                  ,0xffc1137c) //122
NHSTUB(stat                                   ,0xffc2641c) //109
NHSTUB(strcat                                 ,0xffc7feb8) //  1
NHSTUB(strchr                                 ,0xffc03fe8) //  1
NHSTUB(strcmp                                 ,0xffc1123c) //120
NHSTUB(strcpy                                 ,0xffc11224) //120
NHSTUB(strftime                               ,0xffc80104) //113
NHSTUB(strlen                                 ,0xffc04034) //120
NHSTUB(strncmp                                ,0xffc03f9c) //  1
NHSTUB(strncpy                                ,0xffc03f60) //  1
NHSTUB(strrchr                                ,0xffc0400c) //  1
NHSTUB(strtol                                 ,0xffc2ef6c) //101
NHSTUB(strtolx                                ,0xffc2ed70) //109
   DEF(task_CaptSeq                           ,0xffc5c1e8) //120
   DEF(task_ExpDrv                            ,0xffc95048) //120
   DEF(task_FileWrite                         ,0xffdf0eec) //120
   DEF(task_InitFileModules                   ,0xffc736c4) //120
   DEF(task_MovieRecord                       ,0xffd138cc) //120
   DEF(task_PhySw                             ,0xffc23934) //120
NHSTUB(time                                   ,0xffc6651c) //109
NHSTUB(vsprintf                               ,0xffc111e8) //115
NHSTUB(EngDrvRead                             ,0xffc24ba8) //102
