// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00C   // Found @ 0xffc6fc58, "GM1.00C" @ 0xffc6fc65
//   Firmware build timestamp: Jan  7 2010 13:33:51
//   Canon IXUS 105

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12788 (0x31f4) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0012e9fc
//   KEYSYS = d4a                // Found @ 0xffff1c18
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff1c28
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xffd27a5c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd27a1c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xffc47e04) //  2 64%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe29fb8 -> ffef9fa0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002f100) // Found @0xffc24574
DEF(physw_run                               ,0x00001c2c) // Found @0xffc241d8
DEF(physw_sleep_delay                       ,0x00001c2a) // Found @0xffc241d8
DEF(levent_table                            ,0xffec03cc) // Found @0xffec03cc
DEF(FlashParamsTable                        ,0xffefa190) // Found @0xffefa190
DEF(movie_status                            ,0x00005780) // Found @0xffd1bc1c
DEF(full_screen_refresh                     ,0x000076e8) // Found @0xffd8c5d4
DEF(canon_menu_active                       ,0x00002be0) // Found @0xffc7179c
DEF(canon_shoot_menu_active                 ,0x000068c9) // Found @0xffd50818
DEF(playrec_mode                            ,0x0000292c) // Found @0xffc64200
DEF(zoom_status                             ,0x00009f88) // Found @0xffe2c2f8
DEF(some_flag_for_af_scan                   ,0x00005b28) // Found @0xffd1e584
DEF(zoom_busy                               ,0x000056e0) // Found @0xffd17c24
DEF(focus_busy                              ,0x00005584) // Found @0xffd135b8
DEF(recreview_hold                          ,0x000031d0) // Found @0xffc7d224
DEF(viewport_buffers                        ,0xffeaed08) // Found @0xffcbd030
DEF(active_viewport_buffer                  ,0x00004270) // Found @0xffcbcda4
// Camera appears to have only 1 RAW buffer @ 0x41d64ecc (Found @0xffe7b4d0)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xffc43628
//void *vid_get_viewport_fb()      { return (void*)0x40507700; }             // Found @0xffe78174
DEF(viewport_fb_d                           ,0x000026c8) // Found 0x2670 (@0xffc571f4) + 0x58 (@0xffc57228)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2670+0x58)); } // Found @0xffc571f4 & 0xffc57228
DEF(jpeg_count_str                          ,0x00077fdc) // Found @0xffd83ba4
//char *camera_jpeg_count_str()    { return (char*)0x00077fdc; }             // Found @0xffd83ba4
//long hook_raw_size()             { return 0x011e4ee0; }                    // Found @0xffe7b52c
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd40034

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffea7c0c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffea7c18, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x00000100 }, // Found @0xffea7b34, levent 0x601
//    { 0, KEY_POWER           ,0x00000200 }, // Found @0xffea7b40, levent 0x600
//    { 0, KEY_MENU            ,0x00000400 }, // Found @0xffea7b4c, levent 0x09
//    { 1, KEY_LEFT            ,0x08000000 }, // Found @0xffea7b88, levent 0x06
//    { 1, KEY_ZOOM_OUT        ,0x10000000 }, // Found @0xffea7b94, levent 0x03
//    { 1, KEY_ZOOM_IN         ,0x20000000 }, // Found @0xffea7ba0, levent 0x02
//    { 2, KEY_SET             ,0x00000001 }, // Found @0xffea7bac, levent 0x08
//    { 2, KEY_DOWN            ,0x00000002 }, // Found @0xffea7bb8, levent 0x05
//    { 2, KEY_DISPLAY         ,0x00000008 }, // Found @0xffea7bc4, levent 0x0a
//    { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xffea7bd0, levent 0x07
//    { 2, KEY_UP              ,0x00000800 }, // Found @0xffea7bdc, levent 0x04
//    { 2, KEY_SHOOT_FULL      ,0x00005000 }, // Found @0xffea7be8, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00004000 }, // Found @0xffea7bf4, levent 0x00
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00001000 }, // Found @0xffea7be8, levent 0x01
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4104 // Found @0xffcf4dc4
//#define CAM_RAW_ROWS      3048 // Found @0xffcf4dd0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xffc29e80

// Misc stuff
DEF(ctypes, 0xffea67d2)

// For capt_seq.c
DEF(_nrflag,0x5b08) // Found @ ffd20454 (0x5b10) & ffd20474 (-0x08)
//static long *nrflag = (long*)(0x5b10-0x08);  // Found @ ffd20454 & ffd20470

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc29e3c) //112
NHSTUB(Close                                  ,0xffc26b54) //120
NHSTUB(CreateTask                             ,0xffc0e83c) //120
NHSTUB(DebugAssert                            ,0xffc0eb14) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc265b0) //116
NHSTUB(DeleteFile_Fut                         ,0xffc264cc) //112
NHSTUB(DoAELock                               ,0xffc28128) //120
NHSTUB(DoAFLock                               ,0xffc27fe0) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc28090) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc6cef0) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc280d4) //104
NHSTUB(ExitTask                               ,0xffc0eacc) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc35864) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc3593c) //104
NHSTUB(Fclose_Fut                             ,0xffc26648) //120
NHSTUB(Feof_Fut                               ,0xffc26834) //  1
NHSTUB(Fflush_Fut                             ,0xffc26870) //  1
NHSTUB(Fgets_Fut                              ,0xffc2679c) //  1
NHSTUB(Fopen_Fut                              ,0xffc26608) //120
NHSTUB(Fread_Fut                              ,0xffc266f4) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc29e7c) //112
NHSTUB(Fseek_Fut                              ,0xffc267e8) //120
NHSTUB(Fwrite_Fut                             ,0xffc26748) //120
NHSTUB(GetBatteryTemperature                  ,0xffc49edc) //102
NHSTUB(GetCCDTemperature                      ,0xffc49e68) //102
NHSTUB(GetCurrentAvValue                      ,0xffd14ed4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc55b18) //122
NHSTUB(GetDrive_FreeClusters                  ,0xffc55b78) //  4
NHSTUB(GetDrive_TotalClusters                 ,0xffc55b4c) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xffd14174) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd145bc) //  3
NHSTUB(GetImageFolder                         ,0xffcfbd88) //122
NHSTUB(GetKbdState                            ,0xffc47dec) //109
NHSTUB(GetMemInfo                             ,0xffc0a16c) //115
NHSTUB(GetOpticalTemperature                  ,0xffc49f50) //120
NHSTUB(GetParameterData                       ,0xffd3fff4) //101
NHSTUB(GetPropertyCase                        ,0xffc70bfc) //102
NHSTUB(GetSystemTime                          ,0xffe1be28) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcbe1e8) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcbe1f4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd17f9c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffe13574) //102
NHSTUB(GiveSemaphore                          ,0xffc29858) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffcaec1c) //102
NHSTUB(LEDDrive                               ,0xffc47398) //120
NHSTUB(LocalTime                              ,0xffc6ab34) //115
NHSTUB(LockMainPower                          ,0xffc74504) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc26540) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe74bf4) //102
NHSTUB(MoveIrisWithAv                         ,0xffe18c04) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffe19194) //120
NHSTUB(Open                                   ,0xffc26ae8) //120
NHSTUB(PB2Rec                                 ,0xffc7716c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc5d76c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc5d744) //120
NHSTUB(PT_PlaySound                           ,0xffc65da4) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc73d34) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc73d80) //120
NHSTUB(PutInNdFilter                          ,0xffe18ff8) //102
NHSTUB(PutOutNdFilter                         ,0xffe1901c) //102
NHSTUB(Read                                   ,0xffc0ac7c) //120
NHSTUB(ReadFastDir                            ,0xffe09134) //  4
NHSTUB(Rec2PB                                 ,0xffc771ac) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd8cfbc) //104
NHSTUB(RenameFile_Fut                         ,0xffc26438) //116
NHSTUB(Restart                                ,0xffc2b614) //106
NHSTUB(ScreenLock                             ,0xffd8e168) //117
NHSTUB(ScreenUnlock                           ,0xffd8e1ac) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffe77384) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc74578) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc7ab90) //120
NHSTUB(SetFileAttributes                      ,0xffc26e4c) //  3
NHSTUB(SetFileTimeStamp                       ,0xffc26df0) //  4
NHSTUB(SetLogicalEventActive                  ,0xffc7427c) //101
NHSTUB(SetParameterData                       ,0xffd3ff64) //101
NHSTUB(SetPropertyCase                        ,0xffc70acc) //102
NHSTUB(SetScriptMode                          ,0xffc742cc) //120
NHSTUB(SleepTask                              ,0xffc29ac0) //120
NHSTUB(TakeSemaphore                          ,0xffc29788) //120
NHSTUB(TurnOffBackLight                       ,0xffc7f854) //104
NHSTUB(TurnOnBackLight                        ,0xffc7f83c) //104
NHSTUB(TurnOnDisplay                          ,0xffc43904) //120
NHSTUB(TurnOffDisplay                         ,0xffc43930) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd3069c) //120
NHSTUB(UnlockAE                               ,0xffc2814c) //120
NHSTUB(UnlockAF                               ,0xffc28018) //120
NHSTUB(UnlockMainPower                        ,0xffc74458) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd45eb8) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc55998) //105
NHSTUB(VbattGet                               ,0xffc22f14) //120
NHSTUB(Write                                  ,0xffc26be4) //120
NHSTUB(WriteSDCard                            ,0xffd074dc) //108
NHSTUB(_log                                   ,0xffea431c) //111
NHSTUB(_log10                                 ,0xffea3260) //112
NHSTUB(_pow                                   ,0xffea33d0) //121
NHSTUB(_sqrt                                  ,0xffea5684) //  1
NHSTUB(add_ptp_handler                        ,0xffdd768c) //121
NHSTUB(apex2us                                ,0xffd8f4b8) //121
NHSTUB(close                                  ,0xffc0aa94) //109
NHSTUB(err_init_task                          ,0xffc05f4c) //111
NHSTUB(exmem_alloc                            ,0xffc6b7d4) //103
NHSTUB(exmem_free                             ,0xffc6b84c) //103
NHSTUB(free                                   ,0xffc0415c) //112
NHSTUB(kbd_p1_f                               ,0xffc245f0) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc245fc) //109
NHSTUB(kbd_p2_f                               ,0xffc23ea4) //109
NHSTUB(kbd_read_keys                          ,0xffc24574) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc47800) //109
NHSTUB(lseek                                  ,0xffc26c70) //120
NHSTUB(malloc                                 ,0xffc04100) //112
NHSTUB(memcmp                                 ,0xffc1066c) //120
NHSTUB(memcpy                                 ,0xffc2f3e0) //120
NHSTUB(memset                                 ,0xffd8e4f0) //120
NHSTUB(mkdir                                  ,0xffc26ff0) //109
NHSTUB(mktime_ext                             ,0xffc84a0c) //  1
NHSTUB(open                                   ,0xffc0a9e4) //109
NHSTUB(OpenFastDir                            ,0xffe08fe0) //  4
NHSTUB(closedir                               ,0xffe08f90) //121
NHSTUB(qsort                                  ,0xffe5bd80) //  4
NHSTUB(rand                                   ,0xffc10774) //121
NHSTUB(realloc                                ,0xffd8e56c) //115
NHSTUB(reboot_fw_update                       ,0xffe0a9a8) //106
NHSTUB(set_control_event                      ,0xffc73f9c) //111
NHSTUB(srand                                  ,0xffc10768) //122
NHSTUB(stat                                   ,0xffc26cb8) //109
NHSTUB(strcat                                 ,0xffc841c8) //  1
NHSTUB(strchr                                 ,0xffc03fe4) //  1
NHSTUB(strcmp                                 ,0xffc10628) //120
NHSTUB(strcpy                                 ,0xffc10610) //120
NHSTUB(strftime                               ,0xffc84414) //113
NHSTUB(strlen                                 ,0xffc04030) //120
NHSTUB(strncmp                                ,0xffc03f98) //  1
NHSTUB(strncpy                                ,0xffc03f5c) //  1
NHSTUB(strrchr                                ,0xffc04008) //  1
NHSTUB(strtol                                 ,0xffc2f6c0) //101
NHSTUB(strtolx                                ,0xffc2f4c4) //109
   DEF(task_CaptSeq                           ,0xffc5fa2c) //120
   DEF(task_ExpDrv                            ,0xffc99668) //120
   DEF(task_FileWrite                         ,0xffe03c0c) //120
   DEF(task_InitFileModules                   ,0xffc77bf8) //120
   DEF(task_MovieRecord                       ,0xffd1be60) //120
   DEF(task_PhySw                             ,0xffc241d4) //120
NHSTUB(time                                   ,0xffc6a9e8) //109
NHSTUB(vsprintf                               ,0xffc105d4) //115
NHSTUB(EngDrvRead                             ,0xffc25444) //102
