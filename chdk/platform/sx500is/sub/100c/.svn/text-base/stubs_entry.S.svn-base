// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R51 (DRYOS version 2.3, release #0051)
//   Firmware Ver GM1.00C   // Found @ 0xff087344, "GM1.00C" @ 0xff087351
//   Firmware build timestamp: Jun  8 2012 09:42:03
//   Canon PowerShot SX500 IS

// Values for makefile.inc
//   PLATFORMOSVER = 51
//   PLATFORMID = 12892 (0x325c) // Found @ 0xfff40040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x001791c0
//   KEYSYS = d4c                // Found @ 0xffff1d2c
//   NEED_ENCODED_DISKBOOT = 9   // Found @ 0xffff1d3c

// Note, ROM copied to RAM :- from 0xff4e1414, to 0x00431000, len 15719 words.
//   ARAM_HEAP_START = 0x38e000  // Found @ 0xff1999e8
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1999ac

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff01b644) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff01c154

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff2e3b90 -> ff48d370
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00033bb8) // Found @0xff019508
DEF(physw_run                               ,0x00001d30) // Found @0xff019058
DEF(physw_sleep_delay                       ,0x00001d38) // Found @0xff019058
DEF(levent_table                            ,0xff41a684) // Found @0xff41a684
DEF(FlashParamsTable                        ,0xff48d5d8) // Found @0xff48d5d8
DEF(movie_status                            ,0x000077e4) // Found @0xff188a50
DEF(video_compression_rate                  ,0x00007814) // Found @0xff1891c8
DEF(full_screen_refresh                     ,0x00007fcc) // Found @0xff1a680c
DEF(canon_menu_active                       ,0x00004048) // Found @0xff08fe20
DEF(canon_shoot_menu_active                 ,0x000099e9) // Found @0xff218db0
DEF(playrec_mode                            ,0x000035e0) // Found @0xff07c7e8
DEF(zoom_status                             ,0x0000a384) // Found @0xff26e634
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 127 entries in the table - set NUM_FL to 127
DEF(focus_len_table                         ,0xfff4a4f8) // Found @0xfff4a4f8
DEF(zoom_busy                               ,0x0000342c) // Found @0xff071348
DEF(focus_busy                              ,0x000073c0) // Found @0xff179e64
DEF(recreview_hold                          ,0x000028f8) // Found @0xff04d758
// Palette colour tables  found @ 0xff41de30
DEF(palette_control                         ,0x00007fcc) // Found @0xff1a6788
DEF(active_palette_buffer                   ,0x00007fd4) // Found @0xff1a678c
DEF(palette_buffer_ptr                      ,0x00007fd8) // Found @0xff1a6c44
DEF(palette_buffer                          ,0x000ddb54) // Found @0xff1a6c54
// Offset from start of palette_buffer to color data = 4 (Found @0xff2feaf0)
DEF(bitmap_buffer                           ,0x00008010) // Found @0xff1aa638
DEF(active_bitmap_buffer                    ,0x00008008) // Found @0xff1aa63c
DEF(viewport_buffers                        ,0xff39dd90) // Found @0xff03b88c
DEF(active_viewport_buffer                  ,0x00002184) // Found @0xff03b5d8
// Camera appears to have only 1 RAW buffer @ 0x420f6420 (Found @0xff353b24)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40451000; }             // Found @0xff050e18
//void *vid_get_viewport_fb()      { return (void*)0x405a6b80; }             // Found @0xff352208
DEF(viewport_fb_d                           ,0x000032dc) // Found 0x3288 (@0xff06b970) + 0x54 (@0xff06b9a8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3288+0x54)); } // Found @0xff06b970 & 0xff06b9a8
DEF(jpeg_count_str                          ,0x000e2314) // Found @0xff203a20
//char *camera_jpeg_count_str()    { return (char*)0x000e2314; }             // Found @0xff203a20
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xff353b78
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff19def0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x02000000 // Found @0xff39e410, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xff39e418, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_UP              ,0x00000400 }, // Found @0xff39e368, levent 0x04
//    { 0, KEY_DOWN            ,0x00000800 }, // Found @0xff39e370, levent 0x05
//    { 0, KEY_SET             ,0x00001000 }, // Found @0xff39e378, levent 0x08
//    { 0, KEY_RIGHT           ,0x00002000 }, // Found @0xff39e380, levent 0x07
//    { 0, KEY_MENU            ,0x00008000 }, // Found @0xff39e390, levent 0x09
//    { 0, KEY_LEFT            ,0x00010000 }, // Found @0xff39e398, levent 0x06
//    { 0, KEY_DISPLAY         ,0x00040000 }, // Found @0xff39e3a8, levent 0x0a
//    { 2, KEY_POWER           ,0x00000002 }, // Found @0xff39e3c8, levent 0x100
//    { 2, KEY_PLAYBACK        ,0x00000008 }, // Found @0xff39e3d0, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x00000600 }, // Found @0xff39e3e0, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000400 }, // Found @0xff39e3e0, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000200 }, // Found @0xff39e3d8, levent 0x00
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff15047c
//#define CAM_RAW_ROWS      3504 // Found @0xff150488
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff01f0f4

// Misc stuff
DEF(ctypes, 0xff39d5b8)

// For capt_seq.c
DEF(_nrflag,0x9b94) // Found @ ff22788c (0x9b94) & ff2278c8 (+0x00)
//static long *nrflag = (long*)(0x9b94+0x00);  // Found @ ff22788c & ff2278c8
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff01f0ac) //112
NHSTUB(Close                                  ,0xff01bcb8) //120
NHSTUB(CreateTask                             ,0x004368b0) //120
NHSTUB(DebugAssert                            ,0x00436b88) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff01b6b8) //116
NHSTUB(DoAELock                               ,0xff01dd1c) //120
NHSTUB(DoAFLock                               ,0xff01d9cc) //120
NHSTUB(EnterToCompensationEVF                 ,0xff01dc78) //104
NHSTUB(ExecuteEventProcedure                  ,0xff084348) //104
NHSTUB(ExitFromCompensationEVF                ,0xff01dcbc) //104
NHSTUB(ExitTask                               ,0x00436b40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff02cf28) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff02d090) //104
NHSTUB(Fclose_Fut                             ,0xff01b750) //120
NHSTUB(Feof_Fut                               ,0xff01b93c) //  1
NHSTUB(Fflush_Fut                             ,0xff01b978) //  1
NHSTUB(Fgets_Fut                              ,0xff01b8a4) //  6
NHSTUB(Fopen_Fut                              ,0xff01b710) //120
NHSTUB(Fread_Fut                              ,0xff01b7fc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff01f0ec) //112
NHSTUB(Fseek_Fut                              ,0xff01b8f0) //120
NHSTUB(Fwrite_Fut                             ,0xff01b850) //120
NHSTUB(GetBatteryTemperature                  ,0xff05a3a0) //102
NHSTUB(GetCCDTemperature                      ,0xff05a32c) //102
NHSTUB(GetCurrentAvValue                      ,0xff17cfa0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff06a22c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff06a284) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff06a25c) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff17af48) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff17b304) //  3
NHSTUB(GetImageFolder                         ,0xff159ee0) //122
NHSTUB(GetKbdState                            ,0xff05689c) //109
NHSTUB(GetMemInfo                             ,0xff005024) //115
NHSTUB(GetOpticalTemperature                  ,0xff05a414) //120
NHSTUB(GetParameterData                       ,0xff19deb0) //101
NHSTUB(GetPropertyCase                        ,0xff088370) //101
NHSTUB(GetSystemTime                          ,0xff2df238) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff03d8c0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff03d8cc) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff0717bc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff182c4c) //102
NHSTUB(GiveSemaphore                          ,0x00437790) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0d1d68) //102
NHSTUB(LEDDrive                               ,0xff18ae78) //120
NHSTUB(LocalTime                              ,0x0043b244) //115
NHSTUB(LockMainPower                          ,0xff08c514) //120
NHSTUB(MakeSDCardBootable                     ,0xff06a4bc) //105
NHSTUB(MoveFocusLensToDistance                ,0xff34db84) //102
NHSTUB(MoveIrisWithAv                         ,0xff2d9f64) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff2da7a0) //120
NHSTUB(Open                                   ,0xff01bbf0) //120
NHSTUB(PB2Rec                                 ,0xff04666c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff18bf68) //102
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff18bf40) //102
NHSTUB(PT_PlaySound                           ,0xff07e7b0) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff089eb4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff089f00) //120
NHSTUB(PutInNdFilter                          ,0xff34c5d0) //102
NHSTUB(PutOutNdFilter                         ,0xff34c60c) //102
NHSTUB(Read                                   ,0xff005ae0) //120
NHSTUB(ReadFastDir                            ,0xff2b938c) //115
NHSTUB(Rec2PB                                 ,0xff0466ac) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff08e81c) //104
NHSTUB(RenameFile_Fut                         ,0xff01b5b0) //116
NHSTUB(Restart                                ,0xff0208bc) //106
NHSTUB(ScreenLock                             ,0xff08f7f4) //117
NHSTUB(ScreenUnlock                           ,0xff08f858) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff351080) //102
NHSTUB(SetAutoShutdownTime                    ,0xff08c588) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff098798) //120
NHSTUB(SetFileAttributes                      ,0xff01c0bc) //  6
NHSTUB(SetFileTimeStamp                       ,0xff01c044) //  6
NHSTUB(SetLogicalEventActive                  ,0xff08c260) //101
NHSTUB(SetParameterData                       ,0xff19de20) //101
NHSTUB(SetPropertyCase                        ,0xff0881e8) //101
NHSTUB(SetScriptMode                          ,0xff08c2b0) //120
NHSTUB(SleepTask                              ,0x00437a3c) //120
NHSTUB(TakeSemaphore                          ,0x004376c0) //120
NHSTUB(TurnOffBackLight                       ,0xff0999e8) //104
NHSTUB(TurnOnBackLight                        ,0xff0999d0) //104
NHSTUB(TurnOnDisplay                          ,0xff05122c) //120
NHSTUB(TurnOffDisplay                         ,0xff05123c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1b9a60) //120
NHSTUB(UnlockAE                               ,0xff01dd40) //120
NHSTUB(UnlockAF                               ,0xff01da04) //120
NHSTUB(UnlockMainPower                        ,0xff08c468) //120
NHSTUB(VbattGet                               ,0xff017c64) //120
NHSTUB(Write                                  ,0xff01bd0c) //120
NHSTUB(WriteSDCard                            ,0xff16cab4) //108
NHSTUB(_log                                   ,0x0043cc38) //111
NHSTUB(_log10                                 ,0x0043d178) //112
NHSTUB(_pow                                   ,0x0043d2f0) //121
NHSTUB(_sqrt                                  ,0x0043ef14) //  6
NHSTUB(add_ptp_handler                        ,0xff26772c) //121
NHSTUB(apex2us                                ,0xff220c84) //121
NHSTUB(close                                  ,0xff00593c) //109
NHSTUB(err_init_task                          ,0xff004304) //111
NHSTUB(exmem_alloc                            ,0xff082bd4) //101
NHSTUB(exmem_free                             ,0xff082c4c) //101
NHSTUB(free                                   ,0xff002f00) //112
NHSTUB(kbd_p1_f                               ,0xff019558) //109
NHSTUB(kbd_p1_f_cont                          ,0xff019564) //109
NHSTUB(kbd_p2_f                               ,0xff018cf0) //109
NHSTUB(kbd_read_keys                          ,0xff019508) //109
NHSTUB(kbd_read_keys_r2                       ,0xff056068) //109
NHSTUB(lseek                                  ,0xff01bed4) //120
NHSTUB(malloc                                 ,0xff002ea8) //112
NHSTUB(memcmp                                 ,0xff00a968) //120
NHSTUB(memcpy                                 ,0xff021210) //120
NHSTUB(memset                                 ,0xff21ec2c) //120
NHSTUB(mkdir                                  ,0xff01c154) //121
NHSTUB(mktime_ext                             ,0xff09cfac) //  1
NHSTUB(open                                   ,0xff00588c) //109
NHSTUB(OpenFastDir                            ,0xff2b9238) //115
NHSTUB(closedir                               ,0xff2b91e8) //121
NHSTUB(qsort                                  ,0xff3334b4) //  6
NHSTUB(rand                                   ,0xff21ebfc) //121
NHSTUB(realloc                                ,0xff21eca8) //115
NHSTUB(reboot_fw_update                       ,0xff2de890) //106
NHSTUB(set_control_event                      ,0xff08be54) //111
NHSTUB(srand                                  ,0xff21ebf0) //122
NHSTUB(stat                                   ,0xff01bf1c) //109
NHSTUB(strcat                                 ,0xff09d62c) //  1
NHSTUB(strchr                                 ,0xff002d74) //  1
NHSTUB(strcmp                                 ,0xff00aa64) //120
NHSTUB(strcpy                                 ,0xff00a950) //120
NHSTUB(strftime                               ,0xff09cff8) //113
NHSTUB(strlen                                 ,0xff002dc0) //120
NHSTUB(strncmp                                ,0xff002d28) //  1
NHSTUB(strncpy                                ,0xff002cec) //  1
NHSTUB(strrchr                                ,0xff002d98) //  1
NHSTUB(strtol                                 ,0xff0211fc) //101
NHSTUB(strtolx                                ,0xff021000) //109
   DEF(task_CaptSeq                           ,0xff07706c) //120
   DEF(task_ExpDrv                            ,0xff0b5b1c) //120
   DEF(task_FileWrite                         ,0xff2b81b0) //120
   DEF(task_InitFileModules                   ,0xff046f88) //120
   DEF(task_MovieRecord                       ,0xff1896e8) //120
   DEF(task_PhySw                             ,0xff019054) //120
   DEF(task_RotaryEncoder                     ,0xff056b3c) //120
   DEF(hook_CreateTask                        ,0x004368b0) //105
NHSTUB(time                                   ,0x0043b6ec) //  6
NHSTUB(vsprintf                               ,0xff00a800) //115
NHSTUB(EngDrvRead                             ,0xff01a398) //102
