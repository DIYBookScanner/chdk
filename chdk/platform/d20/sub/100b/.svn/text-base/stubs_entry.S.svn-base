// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.00B   // Found @ 0xff079260, "GM1.00B" @ 0xff07926d
//   Firmware build timestamp: Mar 19 2012 18:21:09
//   Canon PowerShot D20

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12866 (0x3242) // Found @ 0xfff40040
//   MAXRAMADDR = 0x07ffffff
//   MEMISOSTART = 0x001716e8
//   KEYSYS = d4c                // Found @ 0xffff39e0
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff39f0

// Note, ROM copied to RAM :- from 0xff4acdbc, to 0x00471000, len 15843 words.
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff18c9a8
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff18c96c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DeleteFile_Fut                       ,0xff020a70) //  1 90%        == 0xff020a70
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff173188) //  3 90%
//NHSTUB(LEDDrive                             ,0xff17e1e8) //120        *** != 0xff04bc04
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff021580

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff2fd5f4 -> ff47b4a0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00033dd4) // Found @0xff01e874
DEF(physw_run                               ,0x00001c30) // Found @0xff01e424
DEF(physw_sleep_delay                       ,0x00001c38) // Found @0xff01e424
DEF(levent_table                            ,0xff411860) // Found @0xff411860
DEF(FlashParamsTable                        ,0xff47b70c) // Found @0xff47b70c
DEF(movie_status                            ,0x00006dfc) // Found @0xff17aad8
DEF(video_compression_rate                  ,0x00006e3c) // Found @0xff17c4c8
DEF(full_screen_refresh                     ,0x00009bcc) // Found @0xff226b1c
DEF(canon_menu_active                       ,0x0000323c) // Found @0xff07b21c
DEF(canon_shoot_menu_active                 ,0x00008571) // Found @0xff1cbc98
DEF(playrec_mode                            ,0x00002f70) // Found @0xff06e758
DEF(zoom_status                             ,0x0000d234) // Found @0xff2ffa34
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 129 entries in the table - set NUM_FL to 129
DEF(focus_len_table                         ,0xfff4abd8) // Found @0xfff4abd8
DEF(zoom_busy                               ,0x00006d04) // Found @0xff176964
DEF(focus_busy                              ,0x00006b94) // Found @0xff171e5c
DEF(recreview_hold                          ,0x000038d8) // Found @0xff08b658
// Palette colour tables  found @ 0xff42ad20
DEF(palette_control                         ,0x00009bcc) // Found @0xff226a98
DEF(active_palette_buffer                   ,0x00009bd4) // Found @0xff226a9c
DEF(palette_buffer_ptr                      ,0x00009bd8) // Found @0xff226f54
DEF(palette_buffer                          ,0x000c1174) // Found @0xff226f64
// Offset from start of palette_buffer to color data = 4 (Found @0xff341dc0)
DEF(bitmap_buffer                           ,0x00009c10) // Found @0xff22a698
DEF(active_bitmap_buffer                    ,0x00009c08) // Found @0xff22a69c
DEF(viewport_buffers                        ,0xff3a221c) // Found @0xff03a4d4
DEF(active_viewport_buffer                  ,0x000020dc) // Found @0xff03a190
// Camera has 2 RAW buffers @ 0x4138ae00 & 0x46000000
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff3b6e50) // Found @0xff3b6e50
DEF(active_raw_buffer                       ,0x00002eec) // Found @0xff06b240

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40491000; }             // Found @0xff046190
//void *vid_get_viewport_fb()      { return (void*)0x405e6b80; }             // Found @0xff360538
DEF(viewport_fb_d                           ,0x00002cd4) // Found 0x2c80 (@0xff05f434) + 0x54 (@0xff05f46c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2c80+0x54)); } // Found @0xff05f434 & 0xff05f46c
DEF(jpeg_count_str                          ,0x000c0a08) // Found @0xff21bf70
//char *camera_jpeg_count_str()    { return (char*)0x000c0a08; }             // Found @0xff21bf70
//long hook_raw_size()             { return 0x0123eaf0; }                    // Found @0xff363368
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff1ab268

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xff3a2994, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xff3a29bc, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_MENU            ,0x00000001 }, // Found @0xff3a2914, levent 0x09
//    { 2, KEY_SET             ,0x00000002 }, // Found @0xff3a291c, levent 0x08
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xff3a2924, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xff3a292c, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xff3a2934, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xff3a293c, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xff3a2944, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xff3a294c, levent 0x04
//    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xff3a295c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xff3a295c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xff3a2954, levent 0x00
//    { 2, KEY_PLAYBACK        ,0x00000400 }, // Found @0xff3a2964, levent 0x101
//    { 2, KEY_POWER           ,0x00000800 }, // Found @0xff3a296c, levent 0x100
//    { 2, KEY_VIDEO           ,0x00004000 }, // Found @0xff3a297c, levent 0x1a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4168 // Found @0xff1469c4
//#define CAM_RAW_ROWS      3060 // Found @0xff1469d0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02447c

// Misc stuff
DEF(ctypes, 0xff3a1b40)

// For capt_seq.c
DEF(_nrflag,0x9cf4) // Found @ ff232fc4 (0x9cf4) & ff233000 (+0x00)
//static long *nrflag = (long*)(0x9cf4+0x00);  // Found @ ff232fc4 & ff233000
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff024434) //112
NHSTUB(Close                                  ,0xff0210e4) //120
NHSTUB(CreateTask                             ,0x00476824) //120
NHSTUB(DebugAssert                            ,0x00476afc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff020ae4) //116
NHSTUB(DoAELock                               ,0xff022f84) //120
NHSTUB(DoAFLock                               ,0xff022c94) //120
NHSTUB(EnterToCompensationEVF                 ,0xff022eec) //104
NHSTUB(ExecuteEventProcedure                  ,0xff076220) //104
NHSTUB(ExitFromCompensationEVF                ,0xff022f30) //104
NHSTUB(ExitTask                               ,0x00476ab4) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff02dadc) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff02dc2c) //104
NHSTUB(Fclose_Fut                             ,0xff020b7c) //120
NHSTUB(Feof_Fut                               ,0xff020d68) //  1
NHSTUB(Fflush_Fut                             ,0xff020da4) //  1
NHSTUB(Fgets_Fut                              ,0xff020cd0) //  6
NHSTUB(Fopen_Fut                              ,0xff020b3c) //120
NHSTUB(Fread_Fut                              ,0xff020c28) //120
NHSTUB(FreeUncacheableMemory                  ,0xff024474) //112
NHSTUB(Fseek_Fut                              ,0xff020d1c) //120
NHSTUB(Fwrite_Fut                             ,0xff020c7c) //120
NHSTUB(GetBatteryTemperature                  ,0xff04fedc) //102
NHSTUB(GetCCDTemperature                      ,0xff04fe68) //102
NHSTUB(GetCurrentAvValue                      ,0xff173c90) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff05dc60) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff05dcb8) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff05dc90) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff172e18) //102
NHSTUB(GetImageFolder                         ,0xff1500b0) //122
NHSTUB(GetKbdState                            ,0xff04c66c) //109
NHSTUB(GetMemInfo                             ,0xff00509c) //115
NHSTUB(GetOpticalTemperature                  ,0xff04ff50) //120
NHSTUB(GetParameterData                       ,0xff1ab228) //101
NHSTUB(GetPropertyCase                        ,0xff07a2ec) //102
NHSTUB(GetSystemTime                          ,0xff2ede7c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff03cc8c) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff03cc98) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff176de4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff2d8908) //102
NHSTUB(GiveSemaphore                          ,0x00477704) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0ce1d4) //102
NHSTUB(LocalTime                              ,0x0047b1b8) //115
NHSTUB(LockMainPower                          ,0xff07fe10) //120
NHSTUB(MakeSDCardBootable                     ,0xff05dee0) //105
NHSTUB(MoveFocusLensToDistance                ,0xff35c594) //102
NHSTUB(MoveIrisWithAv                         ,0xff2e83ac) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff2e8ae0) //120
NHSTUB(Open                                   ,0xff02101c) //120
NHSTUB(PB2Rec                                 ,0xff083128) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff06668c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff066664) //120
NHSTUB(PT_PlaySound                           ,0xff070714) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff07f504) //120
NHSTUB(PostLogicalEventToUI                   ,0xff07f550) //120
NHSTUB(PutInNdFilter                          ,0xff2e88b8) //102
NHSTUB(PutOutNdFilter                         ,0xff2e88dc) //102
NHSTUB(Read                                   ,0xff005b58) //120
NHSTUB(ReadFastDir                            ,0xff2c6004) //115
NHSTUB(Rec2PB                                 ,0xff08181c) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff097f8c) //104
NHSTUB(RenameFile_Fut                         ,0xff0209dc) //116
NHSTUB(Restart                                ,0xff025c98) //106
NHSTUB(ScreenLock                             ,0xff098f6c) //117
NHSTUB(ScreenUnlock                           ,0xff098fd0) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff35f6b0) //102
NHSTUB(SetAutoShutdownTime                    ,0xff07fe84) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff088e18) //120
NHSTUB(SetFileAttributes                      ,0xff0214e8) //  6
NHSTUB(SetFileTimeStamp                       ,0xff021470) //  6
NHSTUB(SetLogicalEventActive                  ,0xff07fb8c) //101
NHSTUB(SetParameterData                       ,0xff1ab198) //101
NHSTUB(SetPropertyCase                        ,0xff07a14c) //102
NHSTUB(SetScriptMode                          ,0xff07fbdc) //120
NHSTUB(SleepTask                              ,0x004779b0) //120
NHSTUB(TakeSemaphore                          ,0x00477634) //120
NHSTUB(TurnOffBackLight                       ,0xff090170) //104
NHSTUB(TurnOnBackLight                        ,0xff090158) //104
NHSTUB(TurnOnDisplay                          ,0xff0465a4) //120
NHSTUB(TurnOffDisplay                         ,0xff0465b4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff197c94) //120
NHSTUB(UnlockAE                               ,0xff022fa8) //120
NHSTUB(UnlockAF                               ,0xff022ccc) //120
NHSTUB(UnlockMainPower                        ,0xff07fd64) //120
NHSTUB(UnsetZoomForMovie                      ,0xff1ba94c) //104
NHSTUB(VbattGet                               ,0xff01c408) //120
NHSTUB(Write                                  ,0xff021138) //120
NHSTUB(WriteSDCard                            ,0xff1653c4) //108
NHSTUB(_log                                   ,0x0047cce0) //111
NHSTUB(_log10                                 ,0x0047d220) //112
NHSTUB(_pow                                   ,0x0047d398) //121
NHSTUB(_sqrt                                  ,0x0047f0e4) //  6
NHSTUB(add_ptp_handler                        ,0xff272b74) //121
NHSTUB(apex2us                                ,0xff22d3d0) //121
NHSTUB(close                                  ,0xff0059b4) //109
NHSTUB(err_init_task                          ,0xff00437c) //111
NHSTUB(exmem_alloc                            ,0xff074ac8) //101
NHSTUB(exmem_free                             ,0xff074b40) //101
NHSTUB(free                                   ,0xff002f78) //112
NHSTUB(kbd_p1_f                               ,0xff01e8c4) //109
NHSTUB(kbd_p1_f_cont                          ,0xff01e8d0) //109
NHSTUB(kbd_p2_f                               ,0xff01e0bc) //109
NHSTUB(kbd_read_keys                          ,0xff01e874) //109
NHSTUB(kbd_read_keys_r2                       ,0xff04c120) //109
NHSTUB(lseek                                  ,0xff021300) //120
NHSTUB(malloc                                 ,0xff002f20) //112
NHSTUB(memcmp                                 ,0xff00ae6c) //120
NHSTUB(memcpy                                 ,0xff0275c4) //120
NHSTUB(memset                                 ,0xff22b434) //120
NHSTUB(mkdir                                  ,0xff021580) //121
NHSTUB(mktime_ext                             ,0xff0994cc) //  1
NHSTUB(open                                   ,0xff005904) //109
NHSTUB(OpenFastDir                            ,0xff2c5eb0) //115
NHSTUB(closedir                               ,0xff2c5e60) //121
NHSTUB(qsort                                  ,0xff22b3d4) //  6
NHSTUB(rand                                   ,0xff22af0c) //121
NHSTUB(realloc                                ,0xff22b4b0) //115
NHSTUB(reboot_fw_update                       ,0xff2cb3e0) //106
NHSTUB(set_control_event                      ,0xff07f84c) //111
NHSTUB(srand                                  ,0xff22af00) //122
NHSTUB(stat                                   ,0xff021348) //109
NHSTUB(strcat                                 ,0xff099b68) //  1
NHSTUB(strchr                                 ,0xff002dec) //  1
NHSTUB(strcmp                                 ,0xff00af68) //120
NHSTUB(strcpy                                 ,0xff00ae54) //120
NHSTUB(strftime                               ,0xff099518) //113
NHSTUB(strlen                                 ,0xff002e38) //120
NHSTUB(strncmp                                ,0xff002da0) //  1
NHSTUB(strncpy                                ,0xff002d64) //  1
NHSTUB(strrchr                                ,0xff002e10) //  1
NHSTUB(strtol                                 ,0xff0275b0) //101
NHSTUB(strtolx                                ,0xff0273b4) //109
   DEF(task_CaptSeq                           ,0xff069298) //120
   DEF(task_ExpDrv                            ,0xff0b20b4) //120
   DEF(task_FileWrite                         ,0xff2c4864) //120
   DEF(task_InitFileModules                   ,0xff083918) //120
   DEF(task_MovieRecord                       ,0xff17ccfc) //120
   DEF(task_PhySw                             ,0xff01e420) //120
NHSTUB(time                                   ,0x0047b794) //  6
NHSTUB(vsprintf                               ,0xff00ad04) //115
NHSTUB(EngDrvRead                             ,0xff01f86c) //102
