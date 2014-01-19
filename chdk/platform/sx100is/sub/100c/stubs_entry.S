// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00C   // Found @ 0xffc5add8, "GM1.00C" @ 0xffc5ade5
//   Firmware build timestamp: Aug 29 2007 15:27:50
//   Canon PowerShot SX100 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12638 (0x315e) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009f498
//   KEYSYS = d3                 // Found @ 0xffff1a04

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetCCDTemperature                    ,0xffc3a2e0) //102        *** != 0xffc3a474
//NHSTUB(GetOpticalTemperature                ,0xffc3a3c0) //120        *** != 0xffdc4fc4
//NHSTUB(GetZoomLensCurrentPosition           ,0xffdeac9c) //102        *** != 0xffd0e3a0
//NHSTUB(kbd_pwr_off                          ,0xffc37f44) //  2 67%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdf5dd8 -> ffe9e824
// Mode  2598 in firmware but not in current modemap
// Current modemap entry not found in firmware - MODE_INDOOR              32785

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00010c1c) // Found @0xffc130f4
DEF(physw_run                               ,0x00001ca4) // Found @0xffc12da0
DEF(physw_sleep_delay                       ,0x00001ca2) // Found @0xffc12da0
DEF(levent_table                            ,0xffe7cb64) // Found @0xffe7cb64
DEF(FlashParamsTable                        ,0xffe9e9dc) // Found @0xffe9e9dc
DEF(movie_status                            ,0x00005588) // Found @0xffc4abe4
DEF(canon_menu_active                       ,0x0000bafc) // Found @0xffd60be0
DEF(canon_shoot_menu_active                 ,0x0000b1fd) // Found @0xffd380a8
DEF(playrec_mode                            ,0x00005724) // Found @0xffc51684
DEF(zoom_status                             ,0x0000de14) // Found @0xffdf75d0
DEF(some_flag_for_af_scan                   ,0x0000dd08) // Found @0xffdef988
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 23 entries in the table - set NUM_FL to 23
DEF(focus_len_table                         ,0xfffe31ac) // Found @0xfffe31ac
DEF(zoom_busy                               ,0x0000a424) // Found @0xffd0e064
DEF(focus_busy                              ,0x0000a318) // Found @0xffd0835c
//DEF(recreview_hold                          ,0x000061d8) // Found @0xffc68cf4, ** != ** stubs_min = 0x0000af6c (0xAF6C)
// Camera appears to have only 1 RAW buffer @ 0x10f6c860 (Found @0xffdc5d60)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc33cb8
//void *vid_get_viewport_fb()      { return (void*)0x1065a4d0; }             // Found @0xffdc3ec0
DEF(viewport_fb_d                           ,0x00005424) // Found 0x53d8 (@0xffc44194) + 0x4c (@0xffc441cc)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x53d8+0x4c)); } // Found @0xffc44194 & 0xffc441cc
DEF(jpeg_count_str                          ,0x00059a1c) // Found @0xffd6d358
//char *camera_jpeg_count_str()    { return (char*)0x00059a1c; }             // Found @0xffd6d358
//long hook_raw_size()             { return 0x009dcce0; }                    // Found @0xffdc5dbc
//int get_flash_params_count(void) { return 0x72; }                          // Found @0xffd268dc

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe5f9fc, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe5fa04, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xffe5f93c, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xffe5f93c, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xffe5f934, levent 0x00
//    { 0, KEY_POWER           ,0x00004000 }, // Found @0xffe5f944, levent 0x600 (uses inverted logic in physw_status)
//    { 0, KEY_PLAYBACK        ,0x00800000 }, // Found @0xffe5f95c, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_ZOOM_IN         ,0x00000100 }, // Found @0xffe5f98c, levent 0x02
//    { 1, KEY_ZOOM_OUT        ,0x00000200 }, // Found @0xffe5f994, levent 0x03
//    { 1, KEY_SET             ,0x00010000 }, // Found @0xffe5f99c, levent 0x08
//    { 1, KEY_UP              ,0x00020000 }, // Found @0xffe5f9a4, levent 0x04
//    { 1, KEY_LEFT            ,0x00040000 }, // Found @0xffe5f9ac, levent 0x06
//    { 1, KEY_DOWN            ,0x00080000 }, // Found @0xffe5f9b4, levent 0x05
//    { 1, KEY_RIGHT           ,0x00100000 }, // Found @0xffe5f9bc, levent 0x07
//    { 1, KEY_MENU            ,0x02000000 }, // Found @0xffe5f9cc, levent 0x09
//    { 1, KEY_DISPLAY         ,0x04000000 }, // Found @0xffe5f9d4, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3336 // Found @0xffdbddc0
//#define CAM_RAW_ROWS      2480 // Found @0xffdbddc8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc19e6c

// Misc stuff
DEF(ctypes, 0xffe5a4b2)

// For capt_seq.c
DEF(_nrflag,0xa5fc) // Found @ ffd15bc4 (0xa5fc)
//static long *nrflag = (long*)(0xa5fc);       // Found @ ffd15bc4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc19e30) //112
NHSTUB(Close                                  ,0xffc1504c) //120
NHSTUB(CreateTask                             ,0xffc0bbb8) //120
NHSTUB(DebugAssert                            ,0xffc0c090) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc14998) //116
NHSTUB(DeleteFile_Fut                         ,0xffc148b4) //112
NHSTUB(DoAELock                               ,0xffc17480) //120
NHSTUB(DoAFLock                               ,0xffc16f5c) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc172d4) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc0c270) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc17324) //104
NHSTUB(ExitTask                               ,0xffc0be48) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc249b8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc24b78) //104
NHSTUB(Fclose_Fut                             ,0xffc14a30) //120
NHSTUB(Feof_Fut                               ,0xffc14c1c) //  1
NHSTUB(Fflush_Fut                             ,0xffc14c58) //  1
NHSTUB(Fgets_Fut                              ,0xffc14b84) //  1
NHSTUB(Fopen_Fut                              ,0xffc149f0) //120
NHSTUB(Fread_Fut                              ,0xffc14adc) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc19e64) //112
NHSTUB(Fseek_Fut                              ,0xffc14bd0) //120
NHSTUB(Fwrite_Fut                             ,0xffc14b30) //120
NHSTUB(GetBatteryTemperature                  ,0xffc3a350) //102
NHSTUB(GetCurrentAvValue                      ,0xffd0b008) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc406a0) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc40740) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc406d4) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffd08e9c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd091a8) //  1
NHSTUB(GetKbdState                            ,0xffc37df4) //109
NHSTUB(GetMemInfo                             ,0xffc03c58) //115
NHSTUB(GetParameterData                       ,0xffd2689c) //101
NHSTUB(GetPropertyCase                        ,0xffc5bcc0) //101
NHSTUB(GetSystemTime                          ,0xffdf2ffc) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc2cd38) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc2cd44) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd0e3c8) //120
NHSTUB(GiveSemaphore                          ,0xffc0bb24) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc9ef9c) //102
NHSTUB(LEDDrive                               ,0xffc373e8) //120
NHSTUB(LocalTime                              ,0xffc580ec) //115
NHSTUB(LockMainPower                          ,0xffc5f748) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc14928) //116
NHSTUB(MoveFocusLensToDistance                ,0xffdc0d60) //102
NHSTUB(MoveIrisWithAv                         ,0xffd0b3e8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffd0ee74) //120
NHSTUB(Open                                   ,0xffc15024) //120
NHSTUB(PB2Rec                                 ,0xffc6296c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc53460) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc53428) //120
NHSTUB(PT_PlaySound                           ,0xffc52fd4) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5d6e4) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5d730) //120
NHSTUB(PutInNdFilter                          ,0xffdbf16c) //102
NHSTUB(PutOutNdFilter                         ,0xffdbf1a4) //102
NHSTUB(Read                                   ,0xffc0a440) //120
NHSTUB(ReadFastDir                            ,0xffddc6b0) //  1
NHSTUB(Rec2PB                                 ,0xffc61598) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd79fd4) //104
NHSTUB(RenameFile_Fut                         ,0xffc14860) //  1
NHSTUB(Restart                                ,0xffc1be8c) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffdc30bc) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5f7bc) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc66244) //120
NHSTUB(SetFileAttributes                      ,0xffc15378) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc15328) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5f480) //  1
NHSTUB(SetParameterData                       ,0xffd2680c) //101
NHSTUB(SetPropertyCase                        ,0xffc5bbb8) //103
NHSTUB(SetScriptMode                          ,0xffc5f4d0) //120
NHSTUB(SleepTask                              ,0xffc19cb8) //120
NHSTUB(TakeSemaphore                          ,0xffc0ba54) //120
NHSTUB(TurnOffBackLight                       ,0xffc6bd88) //104
NHSTUB(TurnOnBackLight                        ,0xffc6bd70) //104
NHSTUB(TurnOnDisplay                          ,0xffc33d68) //120
NHSTUB(TurnOffDisplay                         ,0xffc33d78) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd61674) //120
NHSTUB(UnlockAE                               ,0xffc174bc) //120
NHSTUB(UnlockAF                               ,0xffc16fc8) //120
NHSTUB(UnlockMainPower                        ,0xffc5f69c) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd2cfcc) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc40468) //105
NHSTUB(VbattGet                               ,0xffc119cc) //120
NHSTUB(Write                                  ,0xffc150f8) //120
NHSTUB(WriteSDCard                            ,0xffcff51c) //108
NHSTUB(_log                                   ,0xffe58024) //111
NHSTUB(_log10                                 ,0xffe56f68) //112
NHSTUB(_pow                                   ,0xffe570d8) //121
NHSTUB(_sqrt                                  ,0xffe5938c) //  1
NHSTUB(add_ptp_handler                        ,0xffcb53d8) //121
NHSTUB(apex2us                                ,0xffd7b48c) //121
NHSTUB(close                                  ,0xffc0a258) //109
NHSTUB(err_init_task                          ,0xffc04eb0) //111
NHSTUB(exmem_alloc                            ,0xffc58bd8) //102
NHSTUB(exmem_free                             ,0xffc58c50) //102
NHSTUB(free                                   ,0xffc03ab0) //112
NHSTUB(kbd_p1_f                               ,0xffc131f0) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc131fc) //109
NHSTUB(kbd_p2_f                               ,0xffc12a40) //109
NHSTUB(kbd_read_keys                          ,0xffc130f4) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc37900) //109
NHSTUB(lseek                                  ,0xffc1518c) //120
NHSTUB(malloc                                 ,0xffc039dc) //112
NHSTUB(memcmp                                 ,0xffc0e8f0) //120
NHSTUB(memcpy                                 ,0xffc76678) //120
NHSTUB(memset                                 ,0xffe2aac0) //120
NHSTUB(mkdir                                  ,0xffc153f0) //109
NHSTUB(mktime_ext                             ,0xffc76ee4) //  1
NHSTUB(open                                   ,0xffc0a1a8) //109
NHSTUB(OpenFastDir                            ,0xffddc61c) //  1
NHSTUB(closedir                               ,0xffddc780) //  1
NHSTUB(qsort                                  ,0xffd7a864) //  1
NHSTUB(rand                                   ,0xffc0e9f8) //121
NHSTUB(realloc                                ,0xffc03b90) //115
NHSTUB(reboot_fw_update                       ,0xffde1050) //106
NHSTUB(set_control_event                      ,0xffc5f184) //  1
NHSTUB(srand                                  ,0xffc0e9ec) //122
NHSTUB(stat                                   ,0xffc15258) //  1
NHSTUB(strcat                                 ,0xffc765a4) //  1
NHSTUB(strchr                                 ,0xffc7662c) //  1
NHSTUB(strcmp                                 ,0xffc0e888) //120
NHSTUB(strcpy                                 ,0xffc0e834) //120
NHSTUB(strftime                               ,0xffc768ec) //  1
NHSTUB(strlen                                 ,0xffc0e8cc) //120
NHSTUB(strncmp                                ,0xffc765e0) //  1
NHSTUB(strncpy                                ,0xffc0e84c) //  1
NHSTUB(strrchr                                ,0xffc76650) //  1
NHSTUB(strtol                                 ,0xffc20338) //101
NHSTUB(strtolx                                ,0xffc2013c) //109
   DEF(task_CaptSeq                           ,0xffc4e2e0) //120
   DEF(task_ExpDrv                            ,0xffc98f18) //120
   DEF(task_FileWrite                         ,0xffdda798) //120
   DEF(task_InitFileModules                   ,0xffc6358c) //120
   DEF(task_MovieRecord                       ,0xffc4ae48) //120
   DEF(task_PhySw                             ,0xffc12d9c) //120
   DEF(task_RotaryEncoder                     ,0xffc3802c) //120
NHSTUB(time                                   ,0xffc57fa0) //109
NHSTUB(vsprintf                               ,0xffc0e7b4) //115
NHSTUB(EngDrvRead                             ,0xffc13ff4) //102
