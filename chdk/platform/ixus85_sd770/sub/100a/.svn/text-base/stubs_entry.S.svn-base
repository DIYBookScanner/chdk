// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00A   // Found @ 0xff86bef0, "GM1.00A" @ 0xff86befd
//   Firmware build timestamp: Jan 31 2008 13:20:56
//   Canon PowerShot SD770 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12661 (0x3175) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000cba08
//   KEYSYS = d3enc              // Found @ 0xffff33e0
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff33c0
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffa2997c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffa2993c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DebugAssert                          ,0xff81bcf0) //111        *** != 0xff81bcf8
//NHSTUB(PutInNdFilter                        ,0xffa25968) //102        *** != 0xffa7cbdc
//NHSTUB(PutOutNdFilter                       ,0xffa2598c) //102        *** != 0xffa7cc10

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa398b0 -> ffaf0bf0
// Mode 32774 in firmware but not in current modemap
// Mode 32779 in firmware but not in current modemap
// Mode 32781 in firmware but not in current modemap
// Mode 16407 in firmware but not in current modemap
// Current modemap entry not found in firmware - MODE_PORTRAIT            16397
// Current modemap entry not found in firmware - MODE_NIGHT_SNAPSHOT      16395

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000104d0) // Found @0xff821e34
DEF(physw_run                               ,0x00001c00) // Found @0xff821ad0
DEF(physw_sleep_delay                       ,0x00001bfe) // Found @0xff821ad0
DEF(levent_table                            ,0xffacd870) // Found @0xffacd870
DEF(FlashParamsTable                        ,0xffaf0db4) // Found @0xffaf0db4
DEF(movie_status                            ,0x000053a4) // Found @0xff859b6c
DEF(canon_menu_active                       ,0x00009608) // Found @0xff94df84
DEF(canon_shoot_menu_active                 ,0x00009f4d) // Found @0xff96b2bc
DEF(playrec_mode                            ,0x00005534) // Found @0xff860f44
DEF(zoom_status                             ,0x0000d328) // Found @0xffa3b0b0
DEF(some_flag_for_af_scan                   ,0x0000d0ac) // Found @0xffa262e0
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe297c) // Found @0xfffe297c
DEF(zoom_busy                               ,0x000086a8) // Found @0xff930200
DEF(focus_busy                              ,0x000085b4) // Found @0xff92bdac
//DEF(recreview_hold                          ,0x00005dc4) // Found @0xff87cd54, ** != ** stubs_min = 0x00009d2c (0x9C80+0xAC)
// Camera has 2 RAW buffers @ 0x107d68c0 & 0x11b97b60
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffaab1c4) // Found @0xffaab1c4
DEF(active_raw_buffer                       ,0x000054e4) // Found @0xff85e3ec

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff83e868
//void *vid_get_viewport_fb()      { return (void*)0x1065adc0; }             // Found @0xffa81ed0
DEF(viewport_fb_d                           ,0x00005224) // Found 0x51d4 (@0xff852e38) + 0x50 (@0xff852e70)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x51d4+0x50)); } // Found @0xff852e38 & 0xff852e70
DEF(jpeg_count_str                          ,0x0004c73c) // Found @0xff9a22a0
//char *camera_jpeg_count_str()    { return (char*)0x0004c73c; }             // Found @0xff9a22a0
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffa84154
//int get_flash_params_count(void) { return 0x73; }                          // Found @0xff95c8a0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffaaacbc, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffaaacc8, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffaaac08, levent 0x600
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffaaac20, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffaaac20, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffaaac14, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffaaac2c, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffaaac38, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffaaac44, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffaaac50, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffaaac5c, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffaaac68, levent 0x04
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffaaac74, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffaaac80, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffaaac8c, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffa7b800
//#define CAM_RAW_ROWS      2772 // Found @0xffa7b808
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff8285a4

// Misc stuff
DEF(ctypes, 0xffaaa7ae)

// For capt_seq.c
DEF(_nrflag,0x8dcc) // Found @ ff93b258 (0x8dcc)
//static long *nrflag = (long*)(0x8dcc);       // Found @ ff93b258

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff828568) //112
NHSTUB(Close                                  ,0xff823d8c) //120
NHSTUB(CreateTask                             ,0xff81b818) //120
NHSTUB(DeleteDirectory_Fut                    ,0xff82371c) //116
NHSTUB(DeleteFile_Fut                         ,0xff823638) //112
NHSTUB(DoAELock                               ,0xff825f74) //120
NHSTUB(DoAFLock                               ,0xff825b84) //120
NHSTUB(EnterToCompensationEVF                 ,0xff825e80) //104
NHSTUB(ExecuteEventProcedure                  ,0xff8691dc) //104
NHSTUB(ExitFromCompensationEVF                ,0xff825ed0) //104
NHSTUB(ExitTask                               ,0xff81baa8) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff8329d0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff832b14) //104
NHSTUB(Fclose_Fut                             ,0xff8237b4) //120
NHSTUB(Feof_Fut                               ,0xff8239a0) //  1
NHSTUB(Fflush_Fut                             ,0xff8239dc) //  1
NHSTUB(Fgets_Fut                              ,0xff823908) //  1
NHSTUB(Fopen_Fut                              ,0xff823774) //120
NHSTUB(Fread_Fut                              ,0xff823860) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82859c) //112
NHSTUB(Fseek_Fut                              ,0xff823954) //120
NHSTUB(Fwrite_Fut                             ,0xff8238b4) //120
NHSTUB(GetBatteryTemperature                  ,0xff845160) //102
NHSTUB(GetCCDTemperature                      ,0xff8450f0) //102
NHSTUB(GetCurrentAvValue                      ,0xff92d7c0) //102
NHSTUB(GetDrive_ClusterSize                   ,0xff84f080) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff84f0e8) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff84f0b4) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff92c8b8) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff92cbc4) //  1
NHSTUB(GetKbdState                            ,0xff842950) //109
NHSTUB(GetMemInfo                             ,0xff813c40) //115
NHSTUB(GetOpticalTemperature                  ,0xff8451d0) //120
NHSTUB(GetParameterData                       ,0xff95c860) //101
NHSTUB(GetPropertyCase                        ,0xff86cddc) //102
NHSTUB(GetSystemTime                          ,0xffa291d0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8c64c0) //102
NHSTUB(GetVRAMVPixelsSize                     ,0xff8c64cc) //102
NHSTUB(GetZoomLensCurrentPoint                ,0xff930564) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa1f220) //102
NHSTUB(GiveSemaphore                          ,0xff81b77c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8bb92c) //102
NHSTUB(LEDDrive                               ,0xff842174) //120
NHSTUB(LocalTime                              ,0xff8668a0) //115
NHSTUB(LockMainPower                          ,0xff8738f0) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8236ac) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa7ea0c) //102
NHSTUB(MoveIrisWithAv                         ,0xffa25580) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa25b04) //120
NHSTUB(Open                                   ,0xff823d64) //120
NHSTUB(PB2Rec                                 ,0xff876594) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff85b9d8) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff85b9b0) //120
NHSTUB(PT_PlaySound                           ,0xff85b034) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff872f60) //120
NHSTUB(PostLogicalEventToUI                   ,0xff872fac) //120
NHSTUB(Read                                   ,0xff81a094) //120
NHSTUB(ReadFastDir                            ,0xffa0e2a0) //  1
NHSTUB(Rec2PB                                 ,0xff8765c4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9ac06c) //104
NHSTUB(RenameFile_Fut                         ,0xff8235e4) //  1
NHSTUB(Restart                                ,0xff829de0) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffa810e0) //102
NHSTUB(SetAutoShutdownTime                    ,0xff873964) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87a50c) //120
NHSTUB(SetFileAttributes                      ,0xff8240b8) //  1
NHSTUB(SetFileTimeStamp                       ,0xff824068) //  1
NHSTUB(SetLogicalEventActive                  ,0xff87368c) //  1
NHSTUB(SetParameterData                       ,0xff95c7d0) //101
NHSTUB(SetPropertyCase                        ,0xff86ccdc) //102
NHSTUB(SetScriptMode                          ,0xff8736dc) //120
NHSTUB(SleepTask                              ,0xff8283ec) //120
NHSTUB(TakeSemaphore                          ,0xff81b6ac) //120
NHSTUB(TurnOffBackLight                       ,0xff87fdd8) //104
NHSTUB(TurnOnBackLight                        ,0xff87fdc0) //104
NHSTUB(TurnOnDisplay                          ,0xff83e918) //120
NHSTUB(TurnOffDisplay                         ,0xff83e928) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff94eeec) //120
NHSTUB(UnlockAE                               ,0xff825fa4) //120
NHSTUB(UnlockAF                               ,0xff825bc8) //120
NHSTUB(UnlockMainPower                        ,0xff873844) //120
NHSTUB(UnsetZoomForMovie                      ,0xff961ebc) //104
NHSTUB(UpdateMBROnFlash                       ,0xff84eec0) //105
NHSTUB(VbattGet                               ,0xff82071c) //120
NHSTUB(Write                                  ,0xff823e38) //120
NHSTUB(WriteSDCard                            ,0xff920458) //108
NHSTUB(_log                                   ,0xffaa8268) //111
NHSTUB(_log10                                 ,0xffaa71ac) //112
NHSTUB(_pow                                   ,0xffaa731c) //121
NHSTUB(_sqrt                                  ,0xffaa9688) //  1
NHSTUB(add_ptp_handler                        ,0xff9dc8cc) //121
NHSTUB(apex2us                                ,0xff9ad5a8) //121
NHSTUB(close                                  ,0xff819eac) //109
NHSTUB(err_init_task                          ,0xff814e98) //111
NHSTUB(exmem_alloc                            ,0xff8679c4) //103
NHSTUB(exmem_free                             ,0xff867a3c) //103
NHSTUB(free                                   ,0xff813a98) //112
NHSTUB(kbd_p1_f                               ,0xff821f38) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821f44) //109
NHSTUB(kbd_p2_f                               ,0xff821770) //109
NHSTUB(kbd_read_keys                          ,0xff821e34) //109
NHSTUB(kbd_read_keys_r2                       ,0xff842534) //109
NHSTUB(kbd_pwr_off                            ,0xff8429d4) //  2
NHSTUB(kbd_pwr_on                             ,0xff842984) //  2
NHSTUB(lseek                                  ,0xff823ecc) //120
NHSTUB(malloc                                 ,0xff8139c4) //112
NHSTUB(memcmp                                 ,0xff81d844) //120
NHSTUB(memcpy                                 ,0xff892290) //120
NHSTUB(memset                                 ,0xff9ac420) //120
NHSTUB(mkdir                                  ,0xff824130) //109
NHSTUB(mktime_ext                             ,0xff892afc) //  1
NHSTUB(open                                   ,0xff819dfc) //109
NHSTUB(OpenFastDir                            ,0xffa0e20c) //  1
NHSTUB(closedir                               ,0xffa0e370) //  1
NHSTUB(qsort                                  ,0xff9ac928) //  1
NHSTUB(rand                                   ,0xff81d94c) //121
NHSTUB(realloc                                ,0xff813b78) //115
NHSTUB(reboot_fw_update                       ,0xffa15ca0) //106
NHSTUB(set_control_event                      ,0xff8733e0) //  1
NHSTUB(srand                                  ,0xff81d940) //122
NHSTUB(stat                                   ,0xff823f98) //  1
NHSTUB(strcat                                 ,0xff89207c) //  1
NHSTUB(strchr                                 ,0xff892104) //  1
NHSTUB(strcmp                                 ,0xff81d7dc) //120
NHSTUB(strcpy                                 ,0xff81d7c4) //120
NHSTUB(strftime                               ,0xff892504) //  1
NHSTUB(strlen                                 ,0xff81d820) //120
NHSTUB(strncmp                                ,0xff8920b8) //  1
NHSTUB(strncpy                                ,0xff82e0cc) //  1
NHSTUB(strrchr                                ,0xff892128) //  1
NHSTUB(strtol                                 ,0xff82e304) //101
NHSTUB(strtolx                                ,0xff82e108) //109
   DEF(task_CaptSeq                           ,0xff85de30) //120
   DEF(task_ExpDrv                            ,0xff8b478c) //120
   DEF(task_FileWrite                         ,0xffa0afe8) //120
   DEF(task_InitFileModules                   ,0xff87719c) //120
   DEF(task_MovieRecord                       ,0xff859df8) //120
   DEF(task_PhySw                             ,0xff821acc) //120
NHSTUB(time                                   ,0xff866da4) //109
NHSTUB(vsprintf                               ,0xff81d744) //115
NHSTUB(EngDrvRead                             ,0xff822d78) //102
