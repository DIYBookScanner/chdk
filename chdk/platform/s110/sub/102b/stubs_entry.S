// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R51 (DRYOS version 2.3, release #0051)
//   Firmware Ver GM1.02B   // Found @ 0xf80d5d0c, "GM1.02B" @ 0xf80d5d19
//   Firmware build timestamp: Jan 10 2013 20:17:26
//   Canon PowerShot S110

// Values for makefile.inc
//   PLATFORMOSVER = 51
//   PLATFORMID = 12891 (0x325b) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x0028bc88
//   KEYSYS = d4c                // Found @ 0xffff3cd0
//   NEED_ENCODED_DISKBOOT = 9   // Found @ 0xffff3ce0

// Note, ROM copied to RAM :- from 0xf896e004, to 0x00685000, len 47257 words.
//   ARAM_HEAP_START = 0x5ce000  // Found @ 0xf8272458
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xf827241c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xf8023c84) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xf8024794

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @f845b040 -> f8906ef8
// Mode 16924 in firmware but not in current modemap
// Mode  8745 in firmware but not in current modemap
// Mode 33295 in firmware but not in current modemap

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000415fc) // Found @0xf8021508
DEF(physw_run                               ,0x00001e80) // Found @0xf8021064
DEF(physw_sleep_delay                       ,0x00001e88) // Found @0xf8021064
DEF(levent_table                            ,0xf87c767c) // Found @0xf87c767c
DEF(FlashParamsTable                        ,0xf890717c) // Found @0xf890717c
DEF(movie_status                            ,0x00009cbc) // Found @0xf8234628
DEF(video_compression_rate                  ,0x00009cec) // Found @0xf82358e0
DEF(full_screen_refresh                     ,0x0000a9f4) // Found @0xf8282054
DEF(canon_menu_active                       ,0x00004a18) // Found @0xf80df580
DEF(canon_shoot_menu_active                 ,0x0000d6a5) // Found @0xf833bda8
DEF(playrec_mode                            ,0x00003fd0) // Found @0xf80ca3e0
DEF(zoom_status                             ,0x00007224) // Found @0xf81acdc8
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 121 entries in the table - set NUM_FL to 121
DEF(focus_len_table                         ,0xf8f4a910) // Found @0xf8f4a910
DEF(zoom_busy                               ,0x00009b6c) // Found @0xf822f6fc
DEF(focus_busy                              ,0x00009984) // Found @0xf82281dc
DEF(recreview_hold                          ,0x00002cd4) // Found @0xf8071560
// Palette colour tables  found @ 0xf87cb350
DEF(palette_control                         ,0x0000a9f4) // Found @0xf8281fd0
DEF(active_palette_buffer                   ,0x0000a9fc) // Found @0xf8281fd4
DEF(palette_buffer_ptr                      ,0x0000aa00) // Found @0xf828248c
DEF(palette_buffer                          ,0x001a7524) // Found @0xf828249c
// Offset from start of palette_buffer to color data = 4 (Found @0xf8485fec)
DEF(bitmap_buffer                           ,0x0000aa38) // Found @0xf82870c0
DEF(active_bitmap_buffer                    ,0x0000aa30) // Found @0xf82870c4
// Camera has 2 RAW buffers @ 0x44000000 & 0x4ad65bc0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xf8675258) // Found @0xf8675258
DEF(active_raw_buffer                       ,0x00003f48) // Found @0xf80c5f8c

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xf8074fa0
//void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xf8519358
DEF(viewport_fb_d                           ,0x0000388c) // Found 0x3838 (@0xf8095da8) + 0x54 (@0xf8095de0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3838+0x54)); } // Found @0xf8095da8 & 0xf8095de0
DEF(jpeg_count_str                          ,0x001ad150) // Found @0xf8319350
//char *camera_jpeg_count_str()    { return (char*)0x001ad150; }             // Found @0xf8319350
//long hook_raw_size()             { return 0x01297380; }                    // Found @0xf851acf4
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xf8278314

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00000800 // Found @0xf864b504, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xf864b534, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_DOWN            ,0x00000002 }, // Found @0xf864b444, levent 0x05
//    { 0, KEY_LEFT            ,0x00000004 }, // Found @0xf864b44c, levent 0x06
//    { 0, KEY_MENU            ,0x00000008 }, // Found @0xf864b454, levent 0x09
//    { 0, KEY_SET             ,0x00000020 }, // Found @0xf864b464, levent 0x08
//    { 0, KEY_UP              ,0x00000040 }, // Found @0xf864b46c, levent 0x04
//    { 0, KEY_RIGHT           ,0x00000080 }, // Found @0xf864b474, levent 0x07
//    { 0, KEY_ZOOM_OUT        ,0x00008000 }, // Found @0xf864b4b4, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00010000 }, // Found @0xf864b4bc, levent 0x02
//    { 1, KEY_POWER           ,0x00400000 }, // Found @0xf864b4dc, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x00800000 }, // Found @0xf864b4e4, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x000000c0 }, // Found @0xf864b4f4, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000080 }, // Found @0xf864b4f4, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000040 }, // Found @0xf864b4ec, levent 0x00
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4160 // Found @0xf81fdad8
//#define CAM_RAW_ROWS      3124 // Found @0xf81fdae0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xf8039b1c

// Misc stuff
DEF(ctypes, 0xf8648b60)

// For capt_seq.c
DEF(_nrflag,0xd95c) // Found @ f834ee18 (0xd95c) & f834ee54 (+0x00)
//static long *nrflag = (long*)(0xd95c+0x00);  // Found @ f834ee18 & f834ee54
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xf8039ad4) //112
NHSTUB(Close                                  ,0xf80242f8) //120
NHSTUB(CreateTask                             ,0x0068ab8c) //120
NHSTUB(DebugAssert                            ,0x0068b104) //111
NHSTUB(DeleteDirectory_Fut                    ,0xf8023cf8) //116
NHSTUB(DoAELock                               ,0xf8037fdc) //120
NHSTUB(DoAFLock                               ,0xf8037bb8) //120
NHSTUB(EnterToCompensationEVF                 ,0xf8037f38) //104
NHSTUB(ExecuteEventProcedure                  ,0xf80d2bb0) //104
NHSTUB(ExitFromCompensationEVF                ,0xf8037f7c) //104
NHSTUB(ExitTask                               ,0x0068ae1c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xf804a1a4) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xf804a30c) //104
NHSTUB(Fclose_Fut                             ,0xf8023d90) //120
NHSTUB(Feof_Fut                               ,0xf8023f7c) //  1
NHSTUB(Fflush_Fut                             ,0xf8023fb8) //  1
NHSTUB(Fgets_Fut                              ,0xf8023ee4) //  6
NHSTUB(Fopen_Fut                              ,0xf8023d50) //120
NHSTUB(Fread_Fut                              ,0xf8023e3c) //120
NHSTUB(FreeUncacheableMemory                  ,0xf8039b14) //112
NHSTUB(Fseek_Fut                              ,0xf8023f30) //120
NHSTUB(Fwrite_Fut                             ,0xf8023e90) //120
NHSTUB(GetBatteryTemperature                  ,0xf807f4ec) //102
NHSTUB(GetCCDTemperature                      ,0xf807f478) //102
NHSTUB(GetCurrentAvValue                      ,0xf822b230) //120
NHSTUB(GetDrive_ClusterSize                   ,0xf8093818) //122
NHSTUB(GetDrive_FreeClusters                  ,0xf8093870) //119
NHSTUB(GetDrive_TotalClusters                 ,0xf8093848) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xf82291f4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xf82295b0) //  3
NHSTUB(GetImageFolder                         ,0xf82077f0) //122
NHSTUB(GetKbdState                            ,0xf807baa0) //109
NHSTUB(GetMemInfo                             ,0xf8005378) //115
NHSTUB(GetOpticalTemperature                  ,0xf807f560) //120
NHSTUB(GetParameterData                       ,0xf82782d4) //101
NHSTUB(GetPropertyCase                        ,0xf80d6d40) //101
NHSTUB(GetSystemTime                          ,0xf8456aac) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xf805c31c) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xf805c328) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xf822fb70) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xf842853c) //102
NHSTUB(GiveSemaphore                          ,0x0068aaec) //120
NHSTUB(IsStrobeChargeCompleted                ,0xf8136be8) //102
NHSTUB(LEDDrive                               ,0xf8262928) //120
NHSTUB(LocalTime                              ,0x006994c4) //115
NHSTUB(LockMainPower                          ,0xf80db874) //120
NHSTUB(MakeSDCardBootable                     ,0xf8093aa8) //105
NHSTUB(MoveFocusLensToDistance                ,0xf8514e8c) //102
NHSTUB(MoveIrisWithAv                         ,0xf8452c48) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xf84535fc) //120
NHSTUB(Open                                   ,0xf8024230) //120
NHSTUB(PB2Rec                                 ,0xf8066d40) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xf8263a08) //102
NHSTUB(PT_MoveOpticalZoomAt                   ,0xf82639e0) //102
NHSTUB(PT_PlaySound                           ,0xf80cc584) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xf80d905c) //120
NHSTUB(PostLogicalEventToUI                   ,0xf80d90a8) //120
NHSTUB(PutInNdFilter                          ,0xf84533d4) //102
NHSTUB(PutOutNdFilter                         ,0xf84533f8) //102
NHSTUB(Read                                   ,0xf8005e34) //120
NHSTUB(ReadFastDir                            ,0xf840fe44) //115
NHSTUB(Rec2PB                                 ,0xf8066d80) //104
NHSTUB(RefreshPhysicalScreen                  ,0xf80ddf6c) //104
NHSTUB(RenameFile_Fut                         ,0xf8023bf0) //116
NHSTUB(Restart                                ,0xf803b30c) //106
NHSTUB(ScreenLock                             ,0xf80def44) //117
NHSTUB(ScreenUnlock                           ,0xf80defa8) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xf85181d0) //102
NHSTUB(SetAutoShutdownTime                    ,0xf80db8e8) //120
NHSTUB(SetCurrentCaptureModeType              ,0xf80e7a58) //120
NHSTUB(SetFileAttributes                      ,0xf80246fc) //  6
NHSTUB(SetFileTimeStamp                       ,0xf8024684) //  6
NHSTUB(SetLogicalEventActive                  ,0xf80db5c0) //101
NHSTUB(SetParameterData                       ,0xf82781b0) //101
NHSTUB(SetPropertyCase                        ,0xf80d6bb8) //101
NHSTUB(SetScriptMode                          ,0xf80db610) //120
NHSTUB(SleepTask                              ,0x0068f868) //120
NHSTUB(TakeSemaphore                          ,0x0068aa1c) //120
NHSTUB(TurnOffBackLight                       ,0xf80ec840) //104
NHSTUB(TurnOnBackLight                        ,0xf80ec828) //104
NHSTUB(TurnOnDisplay                          ,0xf80753b4) //120
NHSTUB(TurnOffDisplay                         ,0xf80753c4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xf8299d9c) //120
NHSTUB(UnlockAE                               ,0xf8038000) //120
NHSTUB(UnlockAF                               ,0xf8037bf0) //120
NHSTUB(UnlockMainPower                        ,0xf80db7c8) //120
NHSTUB(UnsetZoomForMovie                      ,0xf806d12c) //104
NHSTUB(VbattGet                               ,0xf801fc50) //120
NHSTUB(Write                                  ,0xf802434c) //120
NHSTUB(WriteSDCard                            ,0xf821cc84) //108
NHSTUB(_log                                   ,0x006ae840) //111
NHSTUB(_log10                                 ,0xf8648914) //112
NHSTUB(_pow                                   ,0xf86488dc) //121
NHSTUB(_sqrt                                  ,0x006b0fd0) //  6
NHSTUB(add_ptp_handler                        ,0xf81875d8) //121
NHSTUB(apex2us                                ,0xf8348264) //121
NHSTUB(close                                  ,0xf8005c90) //109
NHSTUB(err_init_task                          ,0xf80043b4) //111
NHSTUB(exmem_alloc                            ,0xf80d1584) //101
NHSTUB(exmem_free                             ,0xf80d15fc) //101
NHSTUB(free                                   ,0xf8002f54) //112
NHSTUB(kbd_p1_f                               ,0xf8021558) //109
NHSTUB(kbd_p1_f_cont                          ,0xf8021564) //109
NHSTUB(kbd_p2_f                               ,0xf8020cfc) //109
NHSTUB(kbd_read_keys                          ,0xf8021508) //109
NHSTUB(kbd_read_keys_r2                       ,0xf807b2f4) //109
NHSTUB(lseek                                  ,0xf8024514) //120
NHSTUB(malloc                                 ,0xf8002efc) //112
NHSTUB(memcmp                                 ,0xf800d42c) //120
NHSTUB(memcpy                                 ,0xf803c418) //120
NHSTUB(memset                                 ,0xf80f0ca8) //120
NHSTUB(mkdir                                  ,0xf8024794) //121
NHSTUB(mktime_ext                             ,0xf80f0280) //  1
NHSTUB(open                                   ,0xf8005be0) //109
NHSTUB(OpenFastDir                            ,0xf840fcf0) //115
NHSTUB(closedir                               ,0xf840fca0) //121
NHSTUB(qsort                                  ,0xf8345888) //  6
NHSTUB(rand                                   ,0xf803c3e8) //121
NHSTUB(realloc                                ,0xf83458e8) //115
NHSTUB(reboot_fw_update                       ,0xf84560fc) //106
NHSTUB(set_control_event                      ,0xf80db1a0) //111
NHSTUB(srand                                  ,0xf803c3dc) //122
NHSTUB(stat                                   ,0xf802455c) //109
NHSTUB(strcat                                 ,0xf80f0bdc) //  1
NHSTUB(strchr                                 ,0xf8002dc8) //  1
NHSTUB(strcmp                                 ,0xf800d528) //120
NHSTUB(strcpy                                 ,0xf800d414) //120
NHSTUB(strftime                               ,0xf80f02cc) //113
NHSTUB(strlen                                 ,0xf8002e14) //120
NHSTUB(strncmp                                ,0xf8002d7c) //  1
NHSTUB(strncpy                                ,0xf8002d40) //  1
NHSTUB(strrchr                                ,0xf8002dec) //  1
NHSTUB(strtol                                 ,0xf803c3c8) //101
NHSTUB(strtolx                                ,0xf803c1cc) //109
   DEF(task_CaptSeq                           ,0xf80c1810) //120
   DEF(task_ExpDrv                            ,0xf810cfa0) //120
   DEF(task_FileWrite                         ,0xf840ec68) //120
   DEF(task_InitFileModules                   ,0xf80675a8) //120
   DEF(task_MovieRecord                       ,0xf8235e00) //120
   DEF(task_PhySw                             ,0xf8021060) //120
   DEF(task_RotaryEncoder                     ,0xf807bdb8) //120
   DEF(task_TouchPanel                        ,0xf8080d84) //120
   DEF(hook_CreateTask                        ,0x0068ab8c) //105
NHSTUB(time                                   ,0x0069991c) //  6
NHSTUB(vsprintf                               ,0xf800d2c4) //115
NHSTUB(EngDrvRead                             ,0xf8022434) //102
