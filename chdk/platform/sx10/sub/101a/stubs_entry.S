// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.01A   // Found @ 0xff8787c8, "GM1.01A" @ 0xff8787d5
//   Firmware build timestamp: Oct  3 2008 10:47:12
//   Canon PowerShot SX10 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12685 (0x318d) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000acb74
//   KEYSYS = d4                 // Found @ 0xffff3570
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff3580
//   ARAM_HEAP_START = 0x30e000  // Found @ 0xff956394
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff956354

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xff84b810) //  2 60%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa79988 -> ffb74388
// Current modemap entry not found in firmware - MODE_VIDEO_STD            3622

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00011ec4) // Found @0xff821b14
DEF(physw_run                               ,0x00001c30) // Found @0xff821788
DEF(physw_sleep_delay                       ,0x00001c2e) // Found @0xff821788
DEF(levent_table                            ,0xffb4acc8) // Found @0xffb4acc8
DEF(FlashParamsTable                        ,0xffb7455c) // Found @0xffb7455c
DEF(movie_status                            ,0x00005430) // Found @0xff864304
DEF(video_compression_rate                  ,0x0000545c) // Found @0xff864510
DEF(canon_menu_active                       ,0x000058d8) // Found @0xff87a1ec
DEF(canon_shoot_menu_active                 ,0x0000ac29) // Found @0xff98cb24
DEF(playrec_mode                            ,0x00005640) // Found @0xff86d218
DEF(zoom_status                             ,0x0000e3e0) // Found @0xffa7b654
DEF(some_flag_for_af_scan                   ,0x00009b58) // Found @0xff94a2bc
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 1 int value, which is the the zoom focus length.
// there are 6 entries in the table - set NUM_FL to 6
DEF(focus_len_table                         ,0xffb77ce0) // Found @0xffb77ce0
DEF(zoom_busy                               ,0x00009100) // Found @0xff9407f0
DEF(focus_busy                              ,0x00008f8c) // Found @0xff939804
//DEF(recreview_hold                          ,0x0000645c) // Found @0xff88b560, ** != ** stubs_min = 0x0000a868 (0xA78C+0xDC)
// Camera has 2 RAW buffers @ 0x40f65b18 & 0x424f1948
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffb0b50c) // Found @0xffb0b50c
DEF(active_raw_buffer                       ,0x000055e4) // Found @0xff86a56c

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403b1000; }             // Found @0xff846c28
//void *vid_get_viewport_fb()      { return (void*)0x4070d9d0; }             // Found @0xffad15ac
DEF(viewport_fb_d                           ,0x000052b8) // Found 0x5260 (@0xff85c76c) + 0x58 (@0xff85c7a4)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x5260+0x58)); } // Found @0xff85c76c & 0xff85c7a4
DEF(jpeg_count_str                          ,0x0004c138) // Found @0xff9d284c
//char *camera_jpeg_count_str()    { return (char*)0x0004c138; }             // Found @0xff9d284c
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffad3a30
//int get_flash_params_count(void) { return 0x78; }                          // Found @0xff975474

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb0ad5c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb0ad68, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb0abe8, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb0abe8, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb0abdc, levent 0x00
//    { 0, KEY_POWER           ,0x00002000 }, // Found @0xffb0abf4, levent 0x600
//    { 0, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffb0ac00, levent 0x601
//    { 1, KEY_VIDEO           ,0x00000020 }, // Found @0xffb0ac60, levent 0x12
//    { 1, KEY_SET             ,0x00000100 }, // Found @0xffb0ac84, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00000200 }, // Found @0xffb0ac90, levent 0x0a
//    { 1, KEY_UP              ,0x00000400 }, // Found @0xffb0ac9c, levent 0x04
//    { 1, KEY_DOWN            ,0x00000800 }, // Found @0xffb0aca8, levent 0x05
//    { 1, KEY_RIGHT           ,0x00001000 }, // Found @0xffb0acb4, levent 0x07
//    { 1, KEY_LEFT            ,0x00002000 }, // Found @0xffb0acc0, levent 0x06
//    { 1, KEY_MENU            ,0x00004000 }, // Found @0xffb0accc, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffaca170
//#define CAM_RAW_ROWS      2772 // Found @0xffaca178
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff828010

// Misc stuff
DEF(ctypes, 0xffb04666)

// For capt_seq.c
DEF(_nrflag,0x9b40) // Found @ ff94c9b0 (0x9b44) & ff94c9cc (-0x04)
//static long *nrflag = (long*)(0x9b44-0x04);  // Found @ ff94c9b0 & ff94c9c8

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff827fcc) //112
NHSTUB(Close                                  ,0xff823a64) //120
NHSTUB(CreateTask                             ,0xff81aef4) //120
NHSTUB(DebugAssert                            ,0xff81b1cc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff8233f4) //116
NHSTUB(DeleteFile_Fut                         ,0xff823310) //112
NHSTUB(DoAELock                               ,0xff825bb4) //120
NHSTUB(DoAFLock                               ,0xff825864) //120
NHSTUB(EnterToCompensationEVF                 ,0xff825b10) //104
NHSTUB(ExecuteEventProcedure                  ,0xff8759f0) //104
NHSTUB(ExitFromCompensationEVF                ,0xff825b54) //104
NHSTUB(ExitTask                               ,0xff81b184) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff8311d8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff83131c) //104
NHSTUB(Fclose_Fut                             ,0xff82348c) //120
NHSTUB(Feof_Fut                               ,0xff823678) //  1
NHSTUB(Fflush_Fut                             ,0xff8236b4) //  1
NHSTUB(Fgets_Fut                              ,0xff8235e0) //  1
NHSTUB(Fopen_Fut                              ,0xff82344c) //120
NHSTUB(Fread_Fut                              ,0xff823538) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82800c) //112
NHSTUB(Fseek_Fut                              ,0xff82362c) //120
NHSTUB(Fwrite_Fut                             ,0xff82358c) //120
NHSTUB(GetBatteryTemperature                  ,0xff84e660) //102
NHSTUB(GetCCDTemperature                      ,0xff84e5f0) //102
NHSTUB(GetCurrentAvValue                      ,0xff93be84) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff85ae98) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff85af00) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff85aecc) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff93a30c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff93a618) //  3
NHSTUB(GetKbdState                            ,0xff84b660) //109
NHSTUB(GetMemInfo                             ,0xff813c24) //115
NHSTUB(GetOpticalTemperature                  ,0xff84e6d0) //120
NHSTUB(GetParameterData                       ,0xff975434) //101
NHSTUB(GetPropertyCase                        ,0xff8796d8) //102
NHSTUB(GetSystemTime                          ,0xffa67b4c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff83ccb4) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff83ccc0) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff941130) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa5b24c) //102
NHSTUB(GiveSemaphore                          ,0xff8279e8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8b6a00) //102
NHSTUB(LEDDrive                               ,0xff84ab48) //120
NHSTUB(LocalTime                              ,0xff87318c) //115
NHSTUB(LockMainPower                          ,0xff880f70) //120
NHSTUB(MakeDirectory_Fut                      ,0xff823384) //116
NHSTUB(MoveFocusLensToDistance                ,0xffacd92c) //102
NHSTUB(MoveIrisWithAv                         ,0xffa63120) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa63848) //120
NHSTUB(Open                                   ,0xff823a3c) //120
NHSTUB(PB2Rec                                 ,0xff883fd8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86608c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff866064) //120
NHSTUB(PT_PlaySound                           ,0xff8659dc) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff87ec9c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff87ece8) //120
NHSTUB(PutInNdFilter                          ,0xffa636cc) //102
NHSTUB(PutOutNdFilter                         ,0xffa636f0) //102
NHSTUB(Read                                   ,0xff819a4c) //120
NHSTUB(ReadFastDir                            ,0xffa49124) //  1
NHSTUB(Rec2PB                                 ,0xff882960) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9df040) //104
NHSTUB(RenameFile_Fut                         ,0xff8232bc) //  1
NHSTUB(Restart                                ,0xff829848) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffad07bc) //102
NHSTUB(SetAutoShutdownTime                    ,0xff880fe4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff8886b4) //120
NHSTUB(SetFileAttributes                      ,0xff823d90) //  1
NHSTUB(SetFileTimeStamp                       ,0xff823d40) //  1
NHSTUB(SetLogicalEventActive                  ,0xff880c30) //101
NHSTUB(SetParameterData                       ,0xff975310) //101
NHSTUB(SetPropertyCase                        ,0xff8795d0) //102
NHSTUB(SetScriptMode                          ,0xff880c80) //120
NHSTUB(SleepTask                              ,0xff827c50) //120
NHSTUB(TakeSemaphore                          ,0xff827918) //120
NHSTUB(TurnOffBackLight                       ,0xff88f28c) //104
NHSTUB(TurnOnBackLight                        ,0xff88f274) //104
NHSTUB(TurnOnDisplay                          ,0xff846cf0) //120
NHSTUB(TurnOffDisplay                         ,0xff846d00) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff963744) //120
NHSTUB(UnlockAE                               ,0xff825bd8) //120
NHSTUB(UnlockAF                               ,0xff82589c) //120
NHSTUB(UnlockMainPower                        ,0xff880ec4) //120
NHSTUB(UpdateMBROnFlash                       ,0xff85acd8) //105
NHSTUB(VbattGet                               ,0xff82046c) //120
NHSTUB(Write                                  ,0xff823b10) //120
NHSTUB(WriteSDCard                            ,0xff92a9a4) //108
NHSTUB(_log                                   ,0xffb018e4) //111
NHSTUB(_log10                                 ,0xffb00570) //112
NHSTUB(_pow                                   ,0xffb006e0) //121
NHSTUB(_sqrt                                  ,0xffb03540) //  1
NHSTUB(add_ptp_handler                        ,0xffa1727c) //121
NHSTUB(apex2us                                ,0xff9e0128) //121
NHSTUB(close                                  ,0xff819864) //109
NHSTUB(err_init_task                          ,0xff814e80) //111
NHSTUB(exmem_alloc                            ,0xff8740cc) //103
NHSTUB(exmem_free                             ,0xff874144) //103
NHSTUB(free                                   ,0xff813a7c) //112
NHSTUB(kbd_p1_f                               ,0xff821c10) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821c1c) //109
NHSTUB(kbd_p2_f                               ,0xff821428) //109
NHSTUB(kbd_read_keys                          ,0xff821b14) //109
NHSTUB(kbd_read_keys_r2                       ,0xff84af6c) //109
NHSTUB(lseek                                  ,0xff823ba4) //120
NHSTUB(malloc                                 ,0xff8139a8) //112
NHSTUB(memcmp                                 ,0xff81cba4) //120
NHSTUB(memcpy                                 ,0xff89ba88) //120
NHSTUB(memset                                 ,0xff9df460) //120
NHSTUB(mkdir                                  ,0xff823e08) //109
NHSTUB(mktime_ext                             ,0xff89c2f4) //  1
NHSTUB(open                                   ,0xff8197b4) //109
NHSTUB(OpenFastDir                            ,0xffa49090) //  1
NHSTUB(closedir                               ,0xffa491f4) //  1
NHSTUB(qsort                                  ,0xffab815c) //  1
NHSTUB(rand                                   ,0xff81ccac) //121
NHSTUB(realloc                                ,0xff813b5c) //115
NHSTUB(reboot_fw_update                       ,0xffa50b24) //106
NHSTUB(set_control_event                      ,0xff88088c) //111
NHSTUB(srand                                  ,0xff81cca0) //122
NHSTUB(stat                                   ,0xff823c70) //  1
NHSTUB(strcat                                 ,0xff89b89c) //  1
NHSTUB(strchr                                 ,0xff89b924) //  1
NHSTUB(strcmp                                 ,0xff81cb3c) //120
NHSTUB(strcpy                                 ,0xff81cb24) //120
NHSTUB(strftime                               ,0xff89bcfc) //  1
NHSTUB(strlen                                 ,0xff81cb80) //120
NHSTUB(strncmp                                ,0xff89b8d8) //  1
NHSTUB(strncpy                                ,0xff82db14) //  1
NHSTUB(strrchr                                ,0xff9df438) //  1
NHSTUB(strtol                                 ,0xff82dd4c) //101
NHSTUB(strtolx                                ,0xff82db50) //109
   DEF(task_CaptSeq                           ,0xff868b98) //120
   DEF(task_ExpDrv                            ,0xff8ad7cc) //120
   DEF(task_FileWrite                         ,0xffa45a44) //120
   DEF(task_InitFileModules                   ,0xff884a54) //120
   DEF(task_MovieRecord                       ,0xff86458c) //120
   DEF(task_PhySw                             ,0xff821784) //120
   DEF(task_RotaryEncoder                     ,0xff84b8d8) //120
NHSTUB(time                                   ,0xff87376c) //109
NHSTUB(vsprintf                               ,0xff81cae8) //115
NHSTUB(EngDrvRead                             ,0xff822a50) //102
