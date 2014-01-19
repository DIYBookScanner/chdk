// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R49 (DRYOS version 2.3, release #0049)
//   Firmware Ver GM1.00D   // Found @ 0xff090020, "GM1.00D" @ 0xff09002d
//   Firmware build timestamp: Jul 19 2011 09:08:40
//   Canon PowerShot SX40 HS

// Values for makefile.inc
//   PLATFORMOSVER = 49
//   PLATFORMID = 12856 (0x3238) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x00198c30
//   KEYSYS = d4c                // Found @ 0xffff3b48
//   NEED_ENCODED_DISKBOOT = 7   // Found @ 0xffff3b58
//   ARAM_HEAP_START = 0x5de000  // Found @ 0xff1deca8
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1dec68

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff36a8b0 -> ff607cdc
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00037548) // Found @0xff024dd8
DEF(physw_run                               ,0x00001c10) // Found @0xff024968
DEF(physw_sleep_delay                       ,0x00001c18) // Found @0xff024968
DEF(levent_table                            ,0xff5939d4) // Found @0xff5939d4
DEF(FlashParamsTable                        ,0xff607f3c) // Found @0xff607f3c
DEF(movie_status                            ,0x00002f1c) // Found @0xff075800
DEF(video_compression_rate                  ,0x00002f5c) // Found @0xff077cfc
DEF(full_screen_refresh                     ,0x0000c2d8) // Found @0xff2917a8
DEF(canon_menu_active                       ,0x000034f0) // Found @0xff091b44
DEF(canon_shoot_menu_active                 ,0x0000ab6d) // Found @0xff22a6cc
DEF(playrec_mode                            ,0x00003214) // Found @0xff0834dc
DEF(zoom_status                             ,0x000111f8) // Found @0xff36e6a0
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 1 int value, which is the the zoom focus length.
// there are 201 entries in the table - set NUM_FL to 201
DEF(focus_len_table                         ,0xfff4a7b4) // Found @0xfff4a7b4
DEF(zoom_busy                               ,0x00002e2c) // Found @0xff071c54
DEF(focus_busy                              ,0x00008d08) // Found @0xff1bbe54
DEF(recreview_hold                          ,0x000041e4) // Found @0xff0a4414
// Palette colour tables  found @ 0xff5af94c
DEF(palette_control                         ,0x0000c2d8) // Found @0xff291724
DEF(active_palette_buffer                   ,0x0000c2e0) // Found @0xff291728
DEF(palette_buffer_ptr                      ,0x0000c2e4) // Found @0xff291be0
DEF(palette_buffer                          ,0x000df7f0) // Found @0xff291bf0
// Offset from start of palette_buffer to color data = 4 (Found @0xff3addd4)
DEF(bitmap_buffer                           ,0x0000c31c) // Found @0xff295434
DEF(active_bitmap_buffer                    ,0x0000c314) // Found @0xff295438
DEF(viewport_buffers                        ,0xff434544) // Found @0xff045b90
DEF(active_viewport_buffer                  ,0x0000215c) // Found @0xff045808
// Camera has 2 RAW buffers @ 0x44000000 & 0x4adb54a0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff445cc4) // Found @0xff445cc4
DEF(active_raw_buffer                       ,0x00003154) // Found @0xff07ecc4

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40685000; }             // Found @0xff0515c4
//void *vid_get_viewport_fb()      { return (void*)0x407dab80; }             // Found @0xff3e0b00
DEF(viewport_fb_d                           ,0x00002cf8) // Found 0x2ca0 (@0xff06bf94) + 0x58 (@0xff06bfcc)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2ca0+0x58)); } // Found @0xff06bf94 & 0xff06bfcc
DEF(jpeg_count_str                          ,0x000df0e8) // Found @0xff285400
//char *camera_jpeg_count_str()    { return (char*)0x000df0e8; }             // Found @0xff285400
//long hook_raw_size()             { return 0x01247a60; }                    // Found @0xff3e3904
//int get_flash_params_count(void) { return 0x9f; }                          // Found @0xff205d7c

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00000002 // Found @0xff434b34, levent 0x20a
//#define SD_READONLY_IDX     1
//#define USB_MASK            0x40000000 // Found @0xff434bac, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_UP              ,0x00000400 }, // Found @0xff434ab4, levent 0x04
//    { 0, KEY_DOWN            ,0x00000800 }, // Found @0xff434abc, levent 0x05
//    { 0, KEY_LEFT            ,0x00001000 }, // Found @0xff434ac4, levent 0x06
//    { 0, KEY_RIGHT           ,0x00002000 }, // Found @0xff434acc, levent 0x07
//    { 0, KEY_SET             ,0x00004000 }, // Found @0xff434ad4, levent 0x08
//    { 0, KEY_VIDEO           ,0x00008000 }, // Found @0xff434adc, levent 0x19
//    { 0, KEY_DISPLAY         ,0x00020000 }, // Found @0xff434aec, levent 0x0a
//    { 0, KEY_MENU            ,0x00040000 }, // Found @0xff434af4, levent 0x09
//    { 2, KEY_POWER           ,0x00000800 }, // Found @0xff434b54, levent 0x100
//    { 2, KEY_PLAYBACK        ,0x00001000 }, // Found @0xff434b5c, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x0000c000 }, // Found @0xff434b74, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00008000 }, // Found @0xff434b74, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00004000 }, // Found @0xff434b6c, levent 0x00
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4176 // Found @0xff18e020
//#define CAM_RAW_ROWS      3060 // Found @0xff18e02c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02bea8

// Misc stuff
DEF(ctypes, 0xff4337e2)

// For capt_seq.c
DEF(_nrflag,0xc3f8) // Found @ ff29e360 (0xc3f8) & ff29e39c (+0x00)
//static long *nrflag = (long*)(0xc3f8+0x00);  // Found @ ff29e360 & ff29e39c
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff02be60) //112
NHSTUB(Close                                  ,0xff0275e4) //120
NHSTUB(CreateTask                             ,0xff00eaf0) //120
NHSTUB(DebugAssert                            ,0xff00edc8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff026fe0) //116
NHSTUB(DeleteFile_Fut                         ,0xff026efc) //112
NHSTUB(DoAELock                               ,0xff0297a8) //120
NHSTUB(DoAFLock                               ,0xff029330) //120
NHSTUB(EnterToCompensationEVF                 ,0xff029704) //104
NHSTUB(ExecuteEventProcedure                  ,0xff08cfdc) //104
NHSTUB(ExitFromCompensationEVF                ,0xff029748) //104
NHSTUB(ExitTask                               ,0xff00ed80) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff037bf0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff037cd0) //104
NHSTUB(Fclose_Fut                             ,0xff027078) //120
NHSTUB(Feof_Fut                               ,0xff027264) //  1
NHSTUB(Fflush_Fut                             ,0xff0272a0) //  1
NHSTUB(Fgets_Fut                              ,0xff0271cc) //  6
NHSTUB(Fopen_Fut                              ,0xff027038) //120
NHSTUB(Fread_Fut                              ,0xff027124) //120
NHSTUB(FreeUncacheableMemory                  ,0xff02bea0) //112
NHSTUB(Fseek_Fut                              ,0xff027218) //120
NHSTUB(Fwrite_Fut                             ,0xff027178) //120
NHSTUB(GetBatteryTemperature                  ,0xff05bbd0) //102
NHSTUB(GetCCDTemperature                      ,0xff05bb5c) //102
NHSTUB(GetCurrentAvValue                      ,0xff1beb90) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff06a5f4) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff06a64c) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff06a624) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1bca4c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1bcdb8) //  3
NHSTUB(GetImageFolder                         ,0xff197630) //122
NHSTUB(GetKbdState                            ,0xff057bec) //109
NHSTUB(GetMemInfo                             ,0xff00a2b8) //115
NHSTUB(GetOpticalTemperature                  ,0xff05bc44) //120
NHSTUB(GetParameterData                       ,0xff205d3c) //101
NHSTUB(GetPropertyCase                        ,0xff09107c) //102
NHSTUB(GetSystemTime                          ,0xff359784) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff0487d8) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff0487e4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff071fe4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff1c4f7c) //102
NHSTUB(GiveSemaphore                          ,0xff02b5e0) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0efddc) //102
NHSTUB(LEDDrive                               ,0xff056e40) //120
NHSTUB(LocalTime                              ,0xff08a9a0) //115
NHSTUB(LockMainPower                          ,0xff09818c) //120
NHSTUB(MakeDirectory_Fut                      ,0xff026f70) //116
NHSTUB(MakeSDCardBootable                     ,0xff06a884) //105
NHSTUB(MoveFocusLensToDistance                ,0xff3dc634) //102
NHSTUB(MoveIrisWithAv                         ,0xff35503c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff355898) //120
NHSTUB(Open                                   ,0xff02751c) //120
NHSTUB(PB2Rec                                 ,0xff09b384) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff079090) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff079068) //120
NHSTUB(PT_PlaySound                           ,0xff085410) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff095b70) //120
NHSTUB(PostLogicalEventToUI                   ,0xff095bbc) //120
NHSTUB(PutInNdFilter                          ,0xff3da118) //102
NHSTUB(PutOutNdFilter                         ,0xff3da150) //102
NHSTUB(Read                                   ,0xff00ad74) //120
NHSTUB(ReadFastDir                            ,0xff339694) //115
NHSTUB(Rec2PB                                 ,0xff099af4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0b19fc) //104
NHSTUB(RenameFile_Fut                         ,0xff026e68) //116
NHSTUB(Restart                                ,0xff02d6a0) //106
NHSTUB(ScreenLock                             ,0xff0b2c28) //117
NHSTUB(ScreenUnlock                           ,0xff0b2c8c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff3dfc78) //102
NHSTUB(SetAutoShutdownTime                    ,0xff098200) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0a1628) //120
NHSTUB(SetFileAttributes                      ,0xff0279e8) //  6
NHSTUB(SetFileTimeStamp                       ,0xff027970) //  6
NHSTUB(SetLogicalEventActive                  ,0xff097ec8) //101
NHSTUB(SetParameterData                       ,0xff205c18) //101
NHSTUB(SetPropertyCase                        ,0xff090ef4) //102
NHSTUB(SetScriptMode                          ,0xff097f64) //120
NHSTUB(SleepTask                              ,0xff02b88c) //120
NHSTUB(TakeSemaphore                          ,0xff02b510) //120
NHSTUB(TurnOffBackLight                       ,0xff0a9688) //104
NHSTUB(TurnOnBackLight                        ,0xff0a9670) //104
NHSTUB(TurnOnDisplay                          ,0xff051a38) //120
NHSTUB(TurnOffDisplay                         ,0xff051a48) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1f157c) //120
NHSTUB(UnlockAE                               ,0xff0297cc) //120
NHSTUB(UnlockAF                               ,0xff029368) //120
NHSTUB(UnlockMainPower                        ,0xff0980e0) //120
NHSTUB(VbattGet                               ,0xff022364) //120
NHSTUB(Write                                  ,0xff027638) //120
NHSTUB(WriteSDCard                            ,0xff1ab440) //108
NHSTUB(_log                                   ,0xff430308) //111
NHSTUB(_log10                                 ,0xff430848) //112
NHSTUB(_pow                                   ,0xff4309c0) //121
NHSTUB(_sqrt                                  ,0xff4325e4) //  6
NHSTUB(add_ptp_handler                        ,0xff2dffb8) //121
NHSTUB(apex2us                                ,0xff297bec) //121
NHSTUB(close                                  ,0xff00abd0) //109
NHSTUB(err_init_task                          ,0xff00602c) //111
NHSTUB(exmem_alloc                            ,0xff08b960) //101
NHSTUB(exmem_free                             ,0xff08b9d8) //101
NHSTUB(free                                   ,0xff004264) //112
NHSTUB(kbd_p1_f                               ,0xff024e28) //109
NHSTUB(kbd_p1_f_cont                          ,0xff024e34) //109
NHSTUB(kbd_p2_f                               ,0xff024600) //109
NHSTUB(kbd_read_keys                          ,0xff024dd8) //109
NHSTUB(kbd_read_keys_r2                       ,0xff0572f4) //109
NHSTUB(lseek                                  ,0xff027800) //120
NHSTUB(malloc                                 ,0xff00420c) //112
NHSTUB(memcmp                                 ,0xff010a48) //120
NHSTUB(memcpy                                 ,0xff03169c) //120
NHSTUB(memset                                 ,0xff295c24) //120
NHSTUB(mkdir                                  ,0xff027a80) //109
NHSTUB(mktime_ext                             ,0xff0b3b98) //  1
NHSTUB(open                                   ,0xff00ab20) //109
NHSTUB(OpenFastDir                            ,0xff339540) //115
NHSTUB(closedir                               ,0xff3394f0) //121
NHSTUB(qsort                                  ,0xff3ae998) //  6
NHSTUB(rand                                   ,0xff295d60) //121
NHSTUB(realloc                                ,0xff295ca0) //115
NHSTUB(reboot_fw_update                       ,0xff33ede8) //106
NHSTUB(set_control_event                      ,0xff097a6c) //111
NHSTUB(srand                                  ,0xff295d54) //122
NHSTUB(stat                                   ,0xff027848) //109
NHSTUB(strcat                                 ,0xff0b3350) //  1
NHSTUB(strchr                                 ,0xff0040d8) //  1
NHSTUB(strcmp                                 ,0xff010a04) //120
NHSTUB(strcpy                                 ,0xff0109ec) //120
NHSTUB(strftime                               ,0xff0b3598) //113
NHSTUB(strlen                                 ,0xff004124) //120
NHSTUB(strncmp                                ,0xff00408c) //  1
NHSTUB(strncpy                                ,0xff004050) //  1
NHSTUB(strrchr                                ,0xff0040fc) //  1
NHSTUB(strtol                                 ,0xff03199c) //101
NHSTUB(strtolx                                ,0xff0317a0) //109
   DEF(task_CaptSeq                           ,0xff07c454) //120
   DEF(task_ExpDrv                            ,0xff0cc408) //120
   DEF(task_FileWrite                         ,0xff3374cc) //120
   DEF(task_InitFileModules                   ,0xff09bb88) //120
   DEF(task_MovieRecord                       ,0xff078534) //120
   DEF(task_PhySw                             ,0xff024964) //120
   DEF(task_RotaryEncoder                     ,0xff057f4c) //120
NHSTUB(time                                   ,0xff08af7c) //109
NHSTUB(vsprintf                               ,0xff0109ac) //115
NHSTUB(EngDrvRead                             ,0xff025c54) //102
