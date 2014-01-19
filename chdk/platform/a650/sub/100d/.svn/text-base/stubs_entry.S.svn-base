// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00D   // Found @ 0xffc59fe4, "GM1.00D" @ 0xffc59ff1
//   Firmware build timestamp: Jul  6 2007 12:41:33
//   Canon PowerShot A650 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12635 (0x315b) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000a3f20
//   KEYSYS = d3                 // Found @ 0xffff1b20

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetZoomLensCurrentPosition           ,0xffddefdc) //102        *** != 0xffd07fc4
//NHSTUB(write                                ,0xffc14fcc) //120        *** != 0xffc0a3d8

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffdeadb8 -> ffe8e628
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00013fdc) // Found @0xffc12fc0
DEF(physw_run                               ,0x00001ca4) // Found @0xffc12c70
DEF(physw_sleep_delay                       ,0x00001ca2) // Found @0xffc12c70
DEF(levent_table                            ,0xffe6f8b0) // Found @0xffe6f8b0
DEF(FlashParamsTable                        ,0xffe8e7e4) // Found @0xffe8e7e4
DEF(movie_status                            ,0x00005550) // Found @0xffc4a7c0
DEF(canon_menu_active                       ,0x0000ee9c) // Found @0xffd56ff4
DEF(canon_shoot_menu_active                 ,0x0000e6cd) // Found @0xffd31738
DEF(playrec_mode                            ,0x000056e4) // Found @0xffc50f34
DEF(zoom_status                             ,0x00011174) // Found @0xffdeca7c
DEF(some_flag_for_af_scan                   ,0x00011040) // Found @0xffde385c
DEF(zoom_busy                               ,0x0000d5a8) // Found @0xffd070e0
//DEF(focus_busy                              ,0x0000d498) // Found @0xffd012d0, ** != ** stubs_min = 0x0000d530 (0xD530)
//DEF(recreview_hold                          ,0x00005e58) // Found @0xffc66370, ** != ** stubs_min = 0x0000e480 (0xE480)
// Camera has 2 RAW buffers @ 0x108057c0 & 0x11f6b740
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffe5aa78) // Found @0xffe5aa78
DEF(active_raw_buffer                       ,0x00005684) // Found @0xffc4e0f0

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3396c
//void *vid_get_viewport_fb()      { return (void*)0x1065a560; }             // Found @0xffdb7e64
DEF(viewport_fb_d                           ,0x000053ec) // Found 0x53a0 (@0xffc43b78) + 0x4c (@0xffc43bb0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x53a0+0x4c)); } // Found @0xffc43b78 & 0xffc43bb0
DEF(jpeg_count_str                          ,0x0005cb38) // Found @0xffd634c8
//char *camera_jpeg_count_str()    { return (char*)0x0005cb38; }             // Found @0xffd634c8
//long hook_raw_size()             { return 0x00ee9710; }                    // Found @0xffdb9d28
//int get_flash_params_count(void) { return 0x72; }                          // Found @0xffd21974

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe53450, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe53458, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00004000 }, // Found @0xffe53370, levent 0x600 (uses inverted logic in physw_status)
//    { 1, KEY_SHOOT_FULL      ,0xc0000000 }, // Found @0xffe533c0, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x80000000 }, // Found @0xffe533c0, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x40000000 }, // Found @0xffe533b8, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe533d8, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe533e0, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe533e8, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe533f0, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe533f8, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe53400, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe53408, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffe53410, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffe53418, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4104 // Found @0xffdb1df0
//#define CAM_RAW_ROWS      3048 // Found @0xffdb1df8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc19a44

// Misc stuff
DEF(ctypes, 0xffe4dc3a)

// For capt_seq.c
DEF(_nrflag,0xd784) // Found @ ffd0eca0 (0xd784)
//static long *nrflag = (long*)(0xd784);       // Found @ ffd0eca0

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc19a08) //112
NHSTUB(Close                                  ,0xffc14f20) //120
NHSTUB(CreateTask                             ,0xffc0baf0) //120
NHSTUB(DebugAssert                            ,0xffc0bfc8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc1486c) //116
NHSTUB(DeleteFile_Fut                         ,0xffc14788) //112
NHSTUB(DoAELock                               ,0xffc1729c) //120
NHSTUB(DoAFLock                               ,0xffc16d94) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc17108) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc0c1a8) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc17158) //104
NHSTUB(ExitTask                               ,0xffc0bd80) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc24250) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc24410) //104
NHSTUB(Fclose_Fut                             ,0xffc14904) //120
NHSTUB(Feof_Fut                               ,0xffc14af0) //  1
NHSTUB(Fflush_Fut                             ,0xffc14b2c) //  1
NHSTUB(Fgets_Fut                              ,0xffc14a58) //  1
NHSTUB(Fopen_Fut                              ,0xffc148c4) //120
NHSTUB(Fread_Fut                              ,0xffc149b0) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc19a3c) //112
NHSTUB(Fseek_Fut                              ,0xffc14aa4) //120
NHSTUB(Fwrite_Fut                             ,0xffc14a04) //120
NHSTUB(GetBatteryTemperature                  ,0xffc39d34) //102
NHSTUB(GetCCDTemperature                      ,0xffc39cc4) //102
NHSTUB(GetCurrentAvValue                      ,0xffd03f7c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc40084) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc40124) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc400b8) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffd01e10) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd0211c) //  1
NHSTUB(GetKbdState                            ,0xffc37bf0) //109
NHSTUB(GetMemInfo                             ,0xffc03c58) //115
NHSTUB(GetOpticalTemperature                  ,0xffc39da4) //120
NHSTUB(GetParameterData                       ,0xffd21934) //101
NHSTUB(GetPropertyCase                        ,0xffc5aecc) //101
NHSTUB(GetSystemTime                          ,0xffde6fb4) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc2c9ec) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc2c9f8) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd07444) //120
NHSTUB(GiveSemaphore                          ,0xffc0ba5c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc999c0) //102
NHSTUB(LEDDrive                               ,0xffc37174) //120
NHSTUB(LocalTime                              ,0xffc572f8) //115
NHSTUB(LockMainPower                          ,0xffc5d20c) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc147fc) //116
NHSTUB(MoveFocusLensToDistance                ,0xffdb4cbc) //102
NHSTUB(MoveIrisWithAv                         ,0xffd0435c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffd07ef0) //120
NHSTUB(Open                                   ,0xffc14ef8) //120
NHSTUB(PB2Rec                                 ,0xffc600a8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc5266c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc52634) //120
NHSTUB(PT_PlaySound                           ,0xffc521e0) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5c8f0) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5c93c) //120
NHSTUB(PutInNdFilter                          ,0xffd0568c) //102
NHSTUB(PutOutNdFilter                         ,0xffd056b0) //102
NHSTUB(Read                                   ,0xffc0a378) //120
NHSTUB(ReadFastDir                            ,0xffdd0640) //  1
NHSTUB(Rec2PB                                 ,0xffc600d8) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd6f958) //104
NHSTUB(RenameFile_Fut                         ,0xffc14734) //  1
NHSTUB(Restart                                ,0xffc1ba64) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffdb7018) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5d280) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc63bd0) //120
NHSTUB(SetFileAttributes                      ,0xffc1524c) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc151fc) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5cf70) //  1
NHSTUB(SetParameterData                       ,0xffd21810) //101
NHSTUB(SetPropertyCase                        ,0xffc5adc4) //103
NHSTUB(SetScriptMode                          ,0xffc5cfc0) //120
NHSTUB(SleepTask                              ,0xffc19890) //120
NHSTUB(TakeSemaphore                          ,0xffc0b98c) //120
NHSTUB(TurnOffBackLight                       ,0xffc69390) //104
NHSTUB(TurnOnBackLight                        ,0xffc69378) //104
NHSTUB(TurnOnDisplay                          ,0xffc33a1c) //120
NHSTUB(TurnOffDisplay                         ,0xffc33a2c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd57a68) //120
NHSTUB(UnlockAE                               ,0xffc172d8) //120
NHSTUB(UnlockAF                               ,0xffc16de4) //120
NHSTUB(UnlockMainPower                        ,0xffc5d160) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd278c0) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3fe4c) //105
NHSTUB(VbattGet                               ,0xffc1189c) //120
NHSTUB(Write                                  ,0xffc14fcc) //120
NHSTUB(WriteSDCard                            ,0xffcf89dc) //108
NHSTUB(_log                                   ,0xffe4ba40) //111
NHSTUB(_log10                                 ,0xffe4a984) //112
NHSTUB(_pow                                   ,0xffe4aaf4) //121
NHSTUB(_sqrt                                  ,0xffe4cda8) //  1
NHSTUB(add_ptp_handler                        ,0xffcb0674) //121
NHSTUB(apex2us                                ,0xffd70ed0) //121
NHSTUB(close                                  ,0xffc0a190) //109
NHSTUB(err_init_task                          ,0xffc04eb0) //111
NHSTUB(exmem_alloc                            ,0xffc57de4) //102
NHSTUB(exmem_free                             ,0xffc57e5c) //102
NHSTUB(free                                   ,0xffc03ab0) //112
NHSTUB(kbd_p1_f                               ,0xffc130c4) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc130d0) //109
NHSTUB(kbd_p2_f                               ,0xffc12910) //109
NHSTUB(kbd_read_keys                          ,0xffc12fc0) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc3764c) //109
NHSTUB(kbd_pwr_off                            ,0xffc37c7c) //  1
NHSTUB(kbd_pwr_on                             ,0xffc37c24) //  1
NHSTUB(lseek                                  ,0xffc15060) //120
NHSTUB(malloc                                 ,0xffc039dc) //112
NHSTUB(memcmp                                 ,0xffc0e820) //120
NHSTUB(memcpy                                 ,0xffc73a9c) //120
NHSTUB(memset                                 ,0xffe1de08) //120
NHSTUB(mkdir                                  ,0xffc152c4) //109
NHSTUB(mktime_ext                             ,0xffc74308) //  1
NHSTUB(open                                   ,0xffc0a0e0) //109
NHSTUB(OpenFastDir                            ,0xffdd05ac) //  1
NHSTUB(closedir                               ,0xffdd0710) //  1
NHSTUB(qsort                                  ,0xffd702a8) //  1
NHSTUB(rand                                   ,0xffc0e928) //121
NHSTUB(realloc                                ,0xffc03b90) //115
NHSTUB(reboot_fw_update                       ,0xffdd4fe0) //106
NHSTUB(set_control_event                      ,0xffc5cd44) //  1
NHSTUB(srand                                  ,0xffc0e91c) //122
NHSTUB(stat                                   ,0xffc1512c) //  1
NHSTUB(strcat                                 ,0xffc739c8) //  1
NHSTUB(strchr                                 ,0xffc73a50) //  1
NHSTUB(strcmp                                 ,0xffc0e7b8) //120
NHSTUB(strcpy                                 ,0xffc0e764) //120
NHSTUB(strftime                               ,0xffc73d10) //  1
NHSTUB(strlen                                 ,0xffc0e7fc) //120
NHSTUB(strncmp                                ,0xffc73a04) //  1
NHSTUB(strncpy                                ,0xffc0e77c) //  1
NHSTUB(strrchr                                ,0xffc73a74) //  1
NHSTUB(strtol                                 ,0xffc1fe0c) //101
NHSTUB(strtolx                                ,0xffc1fc10) //109
   DEF(task_CaptSeq                           ,0xffc4db88) //120
   DEF(task_ExpDrv                            ,0xffc93848) //120
   DEF(task_FileWrite                         ,0xffdce728) //120
   DEF(task_InitFileModules                   ,0xffc60ae8) //120
   DEF(task_MovieRecord                       ,0xffc4aa38) //120
   DEF(task_PhySw                             ,0xffc12c6c) //120
NHSTUB(time                                   ,0xffc571ac) //109
NHSTUB(vsprintf                               ,0xffc0e6e4) //115
NHSTUB(EngDrvRead                             ,0xffc13ec8) //102
