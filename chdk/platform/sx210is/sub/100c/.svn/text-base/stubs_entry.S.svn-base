// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00C   // Found @ 0xff8900cc, "GM1.00C" @ 0xff8900d9
//   Firmware build timestamp: Feb  5 2010 13:36:08
//   Canon PowerShot SX210 IS

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12790 (0x31f6) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00152728
//   KEYSYS = d4a                // Found @ 0xffff3570
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff3580
//   ARAM_HEAP_START = 0x38e000  // Found @ 0xff97c6bc
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff97c67c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(kbd_pwr_off                            ,0xff861ed0) //  2 60%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffad1940 -> ffc093b4
// Mode 33322 in firmware but not in current modemap
// Mode 33321 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000336c4) // Found @0xff83466c
DEF(physw_run                               ,0x00001c30) // Found @0xff8342c4
DEF(physw_sleep_delay                       ,0x00001c38) // Found @0xff8342c4
DEF(levent_table                            ,0xffbc1084) // Found @0xffbc1084
DEF(FlashParamsTable                        ,0xffc095bc) // Found @0xffc095bc
DEF(movie_status                            ,0x0000720c) // Found @0xff96de58
DEF(video_compression_rate                  ,0x00007248) // Found @0xff96e098
DEF(full_screen_refresh                     ,0x00009d08) // Found @0xffa1cf64
DEF(canon_menu_active                       ,0x0000368c) // Found @0xff891c4c
DEF(canon_shoot_menu_active                 ,0x00008511) // Found @0xff9b5a6c
DEF(playrec_mode                            ,0x000033bc) // Found @0xff883e64
//DEF(zoom_status                             ,0x0000d544) // Found @0xffad4e40, ** != ** stubs_min = 0x0000d524 (0xD524)
DEF(some_flag_for_af_scan                   ,0x000075d8) // Found @0xff970d5c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 126 entries in the table - set NUM_FL to 126
DEF(focus_len_table                         ,0xfffea1cc) // Found @0xfffea1cc
DEF(zoom_busy                               ,0x00007140) // Found @0xff969464
DEF(focus_busy                              ,0x00006fc8) // Found @0xff9639d0
//DEF(recreview_hold                          ,0x00004140) // Found @0xff8a3648, ** != ** stubs_min = 0x00008144 (0x804C+0xF8)
DEF(viewport_buffers                        ,0xffb64808) // Found @0xff84fd4c
DEF(active_viewport_buffer                  ,0x00002058) // Found @0xff84fae8
// Camera appears to have only 1 RAW buffer @ 0x41db3b80 (Found @0xffb2fb2c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40431000; }             // Found @0xff85be4c
//void *vid_get_viewport_fb()      { return (void*)0x40547700; }             // Found @0xffb2c7b4
DEF(viewport_fb_d                           ,0x00003110) // Found 0x30b8 (@0xff8750cc) + 0x58 (@0xff875104)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x30b8+0x58)); } // Found @0xff8750cc & 0xff875104
DEF(jpeg_count_str                          ,0x000a05dc) // Found @0xffa0e708
//char *camera_jpeg_count_str()    { return (char*)0x000a05dc; }             // Found @0xffa0e708
//long hook_raw_size()             { return 0x014d2400; }                    // Found @0xffb2fb88
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xff99d9e8

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb65924, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffb6592c, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00002002 }, // Found @0xffb65834, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00002000 }, // Found @0xffb6585c, levent 0x00
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb65834, levent 0x01
//    { 0, KEY_POWER           ,0x00000008 }, // Found @0xffb6583c, levent 0x600
//    { 0, KEY_UP              ,0x00000080 }, // Found @0xffb6584c, levent 0x04
//    { 0, KEY_DOWN            ,0x00000100 }, // Found @0xffb65854, levent 0x05
//    { 0, KEY_PLAYBACK        ,0x00800000 }, // Found @0xffb6586c, levent 0x601
//    { 1, KEY_RIGHT           ,0x00004000 }, // Found @0xffb658ec, levent 0x07
//    { 1, KEY_LEFT            ,0x00008000 }, // Found @0xffb658f4, levent 0x06
//    { 1, KEY_SET             ,0x00010000 }, // Found @0xffb658fc, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00020000 }, // Found @0xffb65904, levent 0x0a
//    { 1, KEY_MENU            ,0x00040000 }, // Found @0xffb6590c, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4416 // Found @0xff93e0b8
//#define CAM_RAW_ROWS      3296 // Found @0xff93e0c0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83a69c

// Misc stuff
DEF(ctypes, 0xffb642a6)

// For capt_seq.c
DEF(_nrflag,0x75b0) // Found @ ff972f8c (0x75b8) & ff972fac (-0x08)
//static long *nrflag = (long*)(0x75b8-0x08);  // Found @ ff972f8c & ff972fa8

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83a658) //112
NHSTUB(Close                                  ,0xff836c50) //120
NHSTUB(CreateTask                             ,0xff81e83c) //120
NHSTUB(DebugAssert                            ,0xff81eb14) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff8366ac) //116
NHSTUB(DeleteFile_Fut                         ,0xff8365c8) //112
NHSTUB(DoAELock                               ,0xff83863c) //120
NHSTUB(DoAFLock                               ,0xff8383f0) //120
NHSTUB(EnterToCompensationEVF                 ,0xff838598) //104
NHSTUB(ExecuteEventProcedure                  ,0xff88d364) //104
NHSTUB(ExitFromCompensationEVF                ,0xff8385dc) //104
NHSTUB(ExitTask                               ,0xff81eacc) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff846458) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff846530) //104
NHSTUB(Fclose_Fut                             ,0xff836744) //120
NHSTUB(Feof_Fut                               ,0xff836930) //  1
NHSTUB(Fflush_Fut                             ,0xff83696c) //  1
NHSTUB(Fgets_Fut                              ,0xff836898) //  1
NHSTUB(Fopen_Fut                              ,0xff836704) //120
NHSTUB(Fread_Fut                              ,0xff8367f0) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83a698) //112
NHSTUB(Fseek_Fut                              ,0xff8368e4) //120
NHSTUB(Fwrite_Fut                             ,0xff836844) //120
NHSTUB(GetBatteryTemperature                  ,0xff866f08) //102
NHSTUB(GetCCDTemperature                      ,0xff866e94) //102
NHSTUB(GetCurrentAvValue                      ,0xff9665d4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff873868) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff8738c8) //  4
NHSTUB(GetDrive_TotalClusters                 ,0xff87389c) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff964644) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9649cc) //  3
NHSTUB(GetImageFolder                         ,0xff94513c) //122
NHSTUB(GetKbdState                            ,0xff861d88) //109
NHSTUB(GetMemInfo                             ,0xff81a16c) //115
NHSTUB(GetOpticalTemperature                  ,0xff866f7c) //120
NHSTUB(GetParameterData                       ,0xff99d9a8) //101
NHSTUB(GetPropertyCase                        ,0xff891070) //102
NHSTUB(GetSystemTime                          ,0xffac3fac) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff851458) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff851464) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff9698ac) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffab484c) //102
NHSTUB(GiveSemaphore                          ,0xff83a074) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8da74c) //102
NHSTUB(LEDDrive                               ,0xff860ff8) //120
NHSTUB(LocalTime                              ,0xff88ac58) //115
NHSTUB(LockMainPower                          ,0xff8975b4) //120
NHSTUB(MakeDirectory_Fut                      ,0xff83663c) //116
NHSTUB(MoveFocusLensToDistance                ,0xffb2918c) //102
NHSTUB(MoveIrisWithAv                         ,0xffac169c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffac1d10) //120
NHSTUB(Open                                   ,0xff836be4) //120
NHSTUB(PB2Rec                                 ,0xff89a7a8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff87c00c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff87bfe4) //120
NHSTUB(PT_PlaySound                           ,0xff885cd0) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff89538c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8953d8) //120
NHSTUB(PutInNdFilter                          ,0xffb26e48) //102
NHSTUB(PutOutNdFilter                         ,0xffb26e80) //102
NHSTUB(Read                                   ,0xff81ac7c) //120
NHSTUB(ReadFastDir                            ,0xffaa1d20) //  4
NHSTUB(Rec2PB                                 ,0xff899080) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffa1db68) //104
NHSTUB(RenameFile_Fut                         ,0xff836534) //116
NHSTUB(Restart                                ,0xff83be34) //106
NHSTUB(ScreenLock                             ,0xffa1ed98) //117
NHSTUB(ScreenUnlock                           ,0xffa1eddc) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb2b928) //102
NHSTUB(SetAutoShutdownTime                    ,0xff897628) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff8a0618) //120
NHSTUB(SetFileAttributes                      ,0xff836f48) //  3
NHSTUB(SetFileTimeStamp                       ,0xff836eec) //  4
NHSTUB(SetLogicalEventActive                  ,0xff8972f0) //101
NHSTUB(SetParameterData                       ,0xff99d918) //101
NHSTUB(SetPropertyCase                        ,0xff890f40) //102
NHSTUB(SetScriptMode                          ,0xff897340) //120
NHSTUB(SleepTask                              ,0xff83a2dc) //120
NHSTUB(TakeSemaphore                          ,0xff839fa4) //120
NHSTUB(TurnOffBackLight                       ,0xff8a732c) //104
NHSTUB(TurnOnBackLight                        ,0xff8a7314) //104
NHSTUB(TurnOnDisplay                          ,0xff85c1e4) //120
NHSTUB(TurnOffDisplay                         ,0xff85c1f4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff98a11c) //120
NHSTUB(UnlockAE                               ,0xff8386c8) //120
NHSTUB(UnlockAF                               ,0xff838480) //120
NHSTUB(UnlockMainPower                        ,0xff897508) //120
NHSTUB(UpdateMBROnFlash                       ,0xff8736e8) //105
NHSTUB(VbattGet                               ,0xff832ffc) //120
NHSTUB(Write                                  ,0xff836ce0) //120
NHSTUB(WriteSDCard                            ,0xff95416c) //108
NHSTUB(_log                                   ,0xffb613b4) //111
NHSTUB(_log10                                 ,0xffb60040) //112
NHSTUB(_pow                                   ,0xffb601b0) //121
NHSTUB(_sqrt                                  ,0xffb62fbc) //  1
NHSTUB(add_ptp_handler                        ,0xffa5c93c) //121
NHSTUB(apex2us                                ,0xffa2260c) //121
NHSTUB(close                                  ,0xff81aa94) //109
NHSTUB(err_init_task                          ,0xff815f4c) //111
NHSTUB(exmem_alloc                            ,0xff88bb98) //103
NHSTUB(exmem_free                             ,0xff88bc10) //103
NHSTUB(free                                   ,0xff81415c) //112
NHSTUB(kbd_p1_f                               ,0xff8346e4) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8346f0) //109
NHSTUB(kbd_p2_f                               ,0xff833f90) //109
NHSTUB(kbd_read_keys                          ,0xff83466c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff861580) //109
NHSTUB(lseek                                  ,0xff836d6c) //120
NHSTUB(malloc                                 ,0xff814100) //112
NHSTUB(memcmp                                 ,0xff82067c) //120
NHSTUB(memcpy                                 ,0xff83fdb4) //120
NHSTUB(memset                                 ,0xffa21644) //120
NHSTUB(mkdir                                  ,0xff8370ec) //109
NHSTUB(mktime_ext                             ,0xff8af464) //  1
NHSTUB(open                                   ,0xff81a9e4) //109
NHSTUB(OpenFastDir                            ,0xffaa1bcc) //  4
NHSTUB(closedir                               ,0xffaa1b7c) //121
NHSTUB(qsort                                  ,0xffb17f74) //  4
NHSTUB(rand                                   ,0xff820784) //121
NHSTUB(realloc                                ,0xffa216c0) //115
NHSTUB(reboot_fw_update                       ,0xffaa7164) //106
NHSTUB(set_control_event                      ,0xff896f40) //111
NHSTUB(srand                                  ,0xff820778) //122
NHSTUB(stat                                   ,0xff836db4) //109
NHSTUB(strcat                                 ,0xff8aec20) //  1
NHSTUB(strchr                                 ,0xff813fe4) //  1
NHSTUB(strcmp                                 ,0xff820638) //120
NHSTUB(strcpy                                 ,0xff820620) //120
NHSTUB(strftime                               ,0xff8aee6c) //113
NHSTUB(strlen                                 ,0xff814030) //120
NHSTUB(strncmp                                ,0xff813f98) //  1
NHSTUB(strncpy                                ,0xff813f5c) //  1
NHSTUB(strrchr                                ,0xff814008) //  1
NHSTUB(strtol                                 ,0xff840094) //101
NHSTUB(strtolx                                ,0xff83fe98) //109
   DEF(task_CaptSeq                           ,0xff87eb90) //120
   DEF(task_ExpDrv                            ,0xff8c475c) //120
   DEF(task_FileWrite                         ,0xffa9c7f8) //120
   DEF(task_InitFileModules                   ,0xff89b134) //120
   DEF(task_MovieRecord                       ,0xff96e110) //120
   DEF(task_PhySw                             ,0xff8342c0) //120
   DEF(task_RotaryEncoder                     ,0xff862024) //120
NHSTUB(time                                   ,0xff88b238) //109
NHSTUB(vsprintf                               ,0xff8205e4) //115
NHSTUB(EngDrvRead                             ,0xff835538) //102
