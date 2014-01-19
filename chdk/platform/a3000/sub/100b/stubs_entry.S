// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00B   // Found @ 0xffc6b670, "GM1.00B" @ 0xffc6b67d
//   Firmware build timestamp: Dec  7 2009 09:08:33
//   Canon PowerShot A3000 IS

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12786 (0x31f2) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00133d38
//   KEYSYS = d4a                // Found @ 0xffff1aac
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff1abc
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd1f2c4
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd1f284

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DoAFLock                             ,0xffc27744) //120        *** != 0xffc59f28
//NHSTUB(LEDDrive                             ,0xffc43a04) //120        *** != 0xffc43acc
//NHSTUB(ScreenLock                           ,0xffd86cec) //117        *** != 0xffd86ef4
//NHSTUB(ScreenUnlock                         ,0xffd86d30) //117        *** != 0xffd85ba4
//NHSTUB(SetScriptMode                        ,0xffc6fce8) //120        *** != 0xffc00f70
//NHSTUB(UnlockAF                             ,0xffc2777c) //120        *** != 0xffc59f38
//NHSTUB(kbd_pwr_off                          ,0xffc445a0) //  2 64%    *** != 0x00000000
NHSTUB(kbd_pwr_on                             ,0xffc44560) //  2 82%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe16178 -> ffeddac4
// Mode  2609 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002eed4) // Found @0xffc23cd4
DEF(physw_run                               ,0x00001bf0) // Found @0xffc23938
DEF(physw_sleep_delay                       ,0x00001bf8) // Found @0xffc23938
DEF(levent_table                            ,0xffeafd60) // Found @0xffeafd60
DEF(FlashParamsTable                        ,0xffeddcbc) // Found @0xffeddcbc
DEF(movie_status                            ,0x000056f8) // Found @0xffd135c8
DEF(full_screen_refresh                     ,0x000076cc) // Found @0xffd8515c
DEF(canon_menu_active                       ,0x00002b7c) // Found @0xffc6d1bc
DEF(canon_shoot_menu_active                 ,0x000068b1) // Found @0xffd481ac
DEF(playrec_mode                            ,0x000028d8) // Found @0xffc608f4
DEF(zoom_status                             ,0x00009cd8) // Found @0xffe184b8
DEF(some_flag_for_af_scan                   ,0x00005aa0) // Found @0xffd15f54
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe29b0) // Found @0xfffe29b0
DEF(zoom_busy                               ,0x00005648) // Found @0xffd0f6d4
DEF(focus_busy                              ,0x000054ec) // Found @0xffd0b100
//DEF(recreview_hold                          ,0x00003174) // Found @0xffc78ce0, ** != ** stubs_min = 0x00006598 (0x64CC+0xCC)
DEF(viewport_buffers                        ,0xffe98558) // Found @0xffcb92dc
DEF(active_viewport_buffer                  ,0x00004290) // Found @0xffcb9124
// Camera appears to have only 1 RAW buffer @ 0x10e59860 (Found @0xffe659dc)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3fc80
//void *vid_get_viewport_fb()      { return (void*)0x10650100; }             // Found @0xffe626a8
DEF(viewport_fb_d                           ,0x00002674) // Found 0x2620 (@0xffc53a48) + 0x54 (@0xffc53a80)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2620+0x54)); } // Found @0xffc53a48 & 0xffc53a80
DEF(jpeg_count_str                          ,0x00075120) // Found @0xffd7bce0
//char *camera_jpeg_count_str()    { return (char*)0x00075120; }             // Found @0xffd7bce0
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe65a38
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd36ca0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe916bc, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe916c8, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00000400 }, // Found @0xffe915b4, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x20000000 }, // Found @0xffe915cc, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffe915fc, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffe915fc, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffe915f0, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe91608, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe91614, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe91620, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe9162c, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe91638, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe91644, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe91650, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffe9165c, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffe91668, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcee5ec
//#define CAM_RAW_ROWS      2772 // Found @0xffcee5f8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc296f0

// Misc stuff
DEF(ctypes, 0xffe90ed2)

// For capt_seq.c
DEF(_nrflag,0x5a80) // Found @ ffd17ee0 (0x5a88) & ffd17f00 (-0x08)
//static long *nrflag = (long*)(0x5a88-0x08);  // Found @ ffd17ee0 & ffd17efc

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
NHSTUB(ExecuteEventProcedure                  ,0xffc68908) //104
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
NHSTUB(GetCurrentAvValue                      ,0xffd0c980) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc52440) //122
//NHSTUB(GetDrive_FreeClusters                ,0xffc524a0) //  4            == 0xffc524a0
NHSTUB(GetDrive_TotalClusters                 ,0xffc52474) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xffd0bc78) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd0c0d0) //  3
NHSTUB(GetImageFolder                         ,0xffcf55a8) //122
NHSTUB(GetKbdState                            ,0xffc4452c) //109
NHSTUB(GetMemInfo                             ,0xffc0a760) //115
NHSTUB(GetOpticalTemperature                  ,0xffc466f4) //120
NHSTUB(GetParameterData                       ,0xffd36c60) //101
NHSTUB(GetPropertyCase                        ,0xffc6c614) //102
NHSTUB(GetSystemTime                          ,0xffe08208) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcba714) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcba720) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd0fa4c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdff83c) //102
NHSTUB(GiveSemaphore                          ,0xffc0f06c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcaac20) //102
NHSTUB(LocalTime                              ,0xffc66618) //115
NHSTUB(LockMainPower                          ,0xffc6ff20) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc25ca4) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe5f128) //102
NHSTUB(MoveIrisWithAv                         ,0xffe04ffc) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe0558c) //120
NHSTUB(Open                                   ,0xffc2624c) //120
NHSTUB(PB2Rec                                 ,0xffc72ce8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc59ed8) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc59eb0) //120
NHSTUB(PT_PlaySound                           ,0xffc62498) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6f750) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc6f79c) //120
NHSTUB(PutInNdFilter                          ,0xffe053f0) //102
NHSTUB(PutOutNdFilter                         ,0xffe05414) //102
NHSTUB(Read                                   ,0xffc0b270) //120
NHSTUB(ReadFastDir                            ,0xffdf6364) //  4
NHSTUB(Rec2PB                                 ,0xffc72d28) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd85b40) //104
NHSTUB(RenameFile_Fut                         ,0xffc25b9c) //116
NHSTUB(Restart                                ,0xffc2ae90) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffe618b8) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc6ff94) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc76624) //120
NHSTUB(SetFileAttributes                      ,0xffc265b0) //  3
NHSTUB(SetFileTimeStamp                       ,0xffc26554) //  4
NHSTUB(SetLogicalEventActive                  ,0xffc6fc98) //101
NHSTUB(SetParameterData                       ,0xffd36bd0) //101
NHSTUB(SetPropertyCase                        ,0xffc6c4e4) //102
NHSTUB(SleepTask                              ,0xffc29530) //120
NHSTUB(TakeSemaphore                          ,0xffc0ef9c) //120
NHSTUB(TurnOffBackLight                       ,0xffc7b3f0) //104
NHSTUB(TurnOnBackLight                        ,0xffc7b3d8) //104
NHSTUB(TurnOnDisplay                          ,0xffc3ff5c) //120
NHSTUB(TurnOffDisplay                         ,0xffc3ff88) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd272e8) //120
NHSTUB(UnlockAE                               ,0xffc278b0) //120
NHSTUB(UnlockMainPower                        ,0xffc6fe74) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd3cba4) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc522c0) //105
NHSTUB(VbattGet                               ,0xffc22cf0) //120
NHSTUB(Write                                  ,0xffc26348) //120
NHSTUB(WriteSDCard                            ,0xffd00c9c) //108
NHSTUB(_log                                   ,0xffe8ea34) //111
NHSTUB(_log10                                 ,0xffe8d978) //112
NHSTUB(_pow                                   ,0xffe8dae8) //121
NHSTUB(_sqrt                                  ,0xffe8fd9c) //  1
NHSTUB(add_ptp_handler                        ,0xffdc8de4) //121
NHSTUB(apex2us                                ,0xffd8803c) //121
NHSTUB(close                                  ,0xffc0b088) //109
NHSTUB(err_init_task                          ,0xffc05f50) //111
NHSTUB(exmem_alloc                            ,0xffc672b8) //103
NHSTUB(exmem_free                             ,0xffc67330) //103
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
NHSTUB(memset                                 ,0xffd87074) //120
NHSTUB(mkdir                                  ,0xffc26754) //109
NHSTUB(mktime_ext                             ,0xffc806ac) //  1
NHSTUB(open                                   ,0xffc0afd8) //109
NHSTUB(OpenFastDir                            ,0xffdf6210) //  4
NHSTUB(closedir                               ,0xffdf61c0) //121
NHSTUB(qsort                                  ,0xffe4719c) //  4
NHSTUB(rand                                   ,0xffc11388) //121
NHSTUB(realloc                                ,0xffd870f0) //115
NHSTUB(reboot_fw_update                       ,0xffdf7bd8) //106
NHSTUB(set_control_event                      ,0xffc6f9b8) //111
NHSTUB(srand                                  ,0xffc1137c) //122
NHSTUB(stat                                   ,0xffc2641c) //109
NHSTUB(strcat                                 ,0xffc7fe68) //  1
NHSTUB(strchr                                 ,0xffc03fe8) //  1
NHSTUB(strcmp                                 ,0xffc1123c) //120
NHSTUB(strcpy                                 ,0xffc11224) //120
NHSTUB(strftime                               ,0xffc800b4) //113
NHSTUB(strlen                                 ,0xffc04034) //120
NHSTUB(strncmp                                ,0xffc03f9c) //  1
NHSTUB(strncpy                                ,0xffc03f60) //  1
NHSTUB(strrchr                                ,0xffc0400c) //  1
NHSTUB(strtol                                 ,0xffc2ef6c) //101
NHSTUB(strtolx                                ,0xffc2ed70) //109
   DEF(task_CaptSeq                           ,0xffc5c198) //120
   DEF(task_ExpDrv                            ,0xffc94ff8) //120
   DEF(task_FileWrite                         ,0xffdf0e3c) //120
   DEF(task_InitFileModules                   ,0xffc73674) //120
   DEF(task_MovieRecord                       ,0xffd1381c) //120
   DEF(task_PhySw                             ,0xffc23934) //120
NHSTUB(time                                   ,0xffc664cc) //109
NHSTUB(vsprintf                               ,0xffc111e8) //115
NHSTUB(EngDrvRead                             ,0xffc24ba8) //102
