// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R51 (DRYOS version 2.3, release #0051)
//   Firmware Ver GM1.00A   // Found @ 0xff8941c8, "GM1.00A" @ 0xff8941d5
//   Firmware build timestamp: Jun 20 2012 13:39:37
//   Canon PowerShot SX160 IS

// Values for makefile.inc
//   PLATFORMOSVER = 51
//   PLATFORMID = 12890 (0x325a) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x001639d4
//   KEYSYS = d4c                // Found @ 0xffff1d50
//   NEED_ENCODED_DISKBOOT = 9   // Found @ 0xffff1d60

// Note, ROM copied to RAM :- from 0xffcd8b18, to 0x00431000, len 15719 words.
//   ARAM_HEAP_START = 0x38e000  // Found @ 0xff9a0530
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff9a04f4

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff82b324) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff82be34

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffae97e0 -> ffc89b08
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00033958) // Found @0xff8291e8
DEF(physw_run                               ,0x00001d30) // Found @0xff828d38
DEF(physw_sleep_delay                       ,0x00001d38) // Found @0xff828d38
DEF(levent_table                            ,0xffc1ae54) // Found @0xffc1ae54
DEF(FlashParamsTable                        ,0xffc89d70) // Found @0xffc89d70
DEF(movie_status                            ,0x00007524) // Found @0xff98f57c
DEF(video_compression_rate                  ,0x00007554) // Found @0xff98fcf4
DEF(full_screen_refresh                     ,0x00007d0c) // Found @0xff9ad354
DEF(canon_menu_active                       ,0x00003f98) // Found @0xff89ccc8
DEF(canon_shoot_menu_active                 ,0x00009731) // Found @0xffa1ef40
DEF(playrec_mode                            ,0x00003570) // Found @0xff889660
DEF(zoom_status                             ,0x0000a0a8) // Found @0xffa73a88
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 127 entries in the table - set NUM_FL to 127
DEF(focus_len_table                         ,0xfffeabe0) // Found @0xfffeabe0
DEF(zoom_busy                               ,0x000073b8) // Found @0xff98a54c
DEF(focus_busy                              ,0x0000723c) // Found @0xff98461c
DEF(recreview_hold                          ,0x000028ec) // Found @0xff85d330
// Palette colour tables  found @ 0xffc1e600
DEF(palette_control                         ,0x00007d0c) // Found @0xff9ad2d0
DEF(active_palette_buffer                   ,0x00007d14) // Found @0xff9ad2d4
DEF(palette_buffer_ptr                      ,0x00007d18) // Found @0xff9ad78c
DEF(palette_buffer                          ,0x000c81bc) // Found @0xff9ad79c
// Offset from start of palette_buffer to color data = 4 (Found @0xffb0544c)
DEF(bitmap_buffer                           ,0x00007d50) // Found @0xff9b1180
DEF(active_bitmap_buffer                    ,0x00007d48) // Found @0xff9b1184
DEF(viewport_buffers                        ,0xffba4534) // Found @0xff84b3e0
DEF(active_viewport_buffer                  ,0x00002178) // Found @0xff84b148
// Camera appears to have only 1 RAW buffer @ 0x420f6420 (Found @0xffb5a2f4)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40451000; }             // Found @0xff8609fc
//void *vid_get_viewport_fb()      { return (void*)0x405a6b80; }             // Found @0xffb589e8
DEF(viewport_fb_d                           ,0x000032c4) // Found 0x3270 (@0xff87a288) + 0x54 (@0xff87a2c0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3270+0x54)); } // Found @0xff87a288 & 0xff87a2c0
DEF(jpeg_count_str                          ,0x000cc97c) // Found @0xffa0a6a0
//char *camera_jpeg_count_str()    { return (char*)0x000cc97c; }             // Found @0xffa0a6a0
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xffb5a348
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff9a4a38

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x02000000 // Found @0xffba4b8c, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xffba4b9c, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_DISPLAY         ,0x80000000 }, // Found @0xffba4ac4, levent 0x0a
//    { 1, KEY_SET             ,0x00000001 }, // Found @0xffba4acc, levent 0x08
//    { 1, KEY_MENU            ,0x00800000 }, // Found @0xffba4ae4, levent 0x09
//    { 1, KEY_SHOOT_FULL      ,0x30000000 }, // Found @0xffba4afc, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x20000000 }, // Found @0xffba4afc, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x10000000 }, // Found @0xffba4af4, levent 0x00
//    { 1, KEY_UP              ,0x40000000 }, // Found @0xffba4b04, levent 0x04
//    { 1, KEY_DOWN            ,0x80000000 }, // Found @0xffba4b0c, levent 0x05
//    { 2, KEY_PLAYBACK        ,0x00000008 }, // Found @0xffba4b1c, levent 0x101
//    { 2, KEY_POWER           ,0x00000020 }, // Found @0xffba4b24, levent 0x100
//    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffba4b2c, levent 0x03
//    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffba4b34, levent 0x02
//    { 2, KEY_RIGHT           ,0x00001000 }, // Found @0xffba4b44, levent 0x07
//    { 2, KEY_LEFT            ,0x00002000 }, // Found @0xffba4b4c, levent 0x06
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff95b0b8
//#define CAM_RAW_ROWS      3504 // Found @0xff95b0c4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff82ec94

// Misc stuff
DEF(ctypes, 0xffba3d5c)

// For capt_seq.c
DEF(_nrflag,0x98dc) // Found @ ffa2d98c (0x98dc) & ffa2d9c8 (+0x00)
//static long *nrflag = (long*)(0x98dc+0x00);  // Found @ ffa2d98c & ffa2d9c8
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff82ec4c) //112
NHSTUB(Close                                  ,0xff82b998) //120
NHSTUB(CreateTask                             ,0x004368b0) //120
NHSTUB(DebugAssert                            ,0x00436b88) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff82b398) //116
NHSTUB(DoAELock                               ,0xff82d8e0) //120
NHSTUB(DoAFLock                               ,0xff82d530) //120
NHSTUB(EnterToCompensationEVF                 ,0xff82d7d0) //104
NHSTUB(ExecuteEventProcedure                  ,0xff8911cc) //104
NHSTUB(ExitFromCompensationEVF                ,0xff82d814) //104
NHSTUB(ExitTask                               ,0x00436b40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff83cac4) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff83cc2c) //104
NHSTUB(Fclose_Fut                             ,0xff82b430) //120
NHSTUB(Feof_Fut                               ,0xff82b61c) //  1
NHSTUB(Fflush_Fut                             ,0xff82b658) //  1
NHSTUB(Fgets_Fut                              ,0xff82b584) //  6
NHSTUB(Fopen_Fut                              ,0xff82b3f0) //120
NHSTUB(Fread_Fut                              ,0xff82b4dc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82ec8c) //112
NHSTUB(Fseek_Fut                              ,0xff82b5d0) //120
NHSTUB(Fwrite_Fut                             ,0xff82b530) //120
NHSTUB(GetBatteryTemperature                  ,0xff8693ac) //102
NHSTUB(GetCCDTemperature                      ,0xff869338) //102
NHSTUB(GetCurrentAvValue                      ,0xff987674) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff878bac) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff878c04) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff878bdc) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff985634) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9859f0) //  3
NHSTUB(GetImageFolder                         ,0xff964b18) //122
NHSTUB(GetKbdState                            ,0xff865eb0) //109
NHSTUB(GetMemInfo                             ,0xff815024) //115
NHSTUB(GetOpticalTemperature                  ,0xff869424) //120
NHSTUB(GetParameterData                       ,0xff9a49f8) //101
NHSTUB(GetPropertyCase                        ,0xff8951f4) //101
NHSTUB(GetSystemTime                          ,0xffae4e88) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff84d400) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff84d40c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff98a9c0) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffad1100) //102
NHSTUB(GiveSemaphore                          ,0x00437790) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8de9f0) //102
NHSTUB(LEDDrive                               ,0xff9919b4) //120
NHSTUB(LocalTime                              ,0x0043b244) //115
NHSTUB(LockMainPower                          ,0xff8993bc) //120
NHSTUB(MakeSDCardBootable                     ,0xff878e3c) //105
NHSTUB(MoveFocusLensToDistance                ,0xffb54520) //102
NHSTUB(MoveIrisWithAv                         ,0xffadfae8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffae0324) //120
NHSTUB(Open                                   ,0xff82b8d0) //120
NHSTUB(PB2Rec                                 ,0xff8561ac) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff992aa8) //102
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff992a80) //102
NHSTUB(PT_PlaySound                           ,0xff88b628) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff896d38) //120
NHSTUB(PostLogicalEventToUI                   ,0xff896d84) //120
NHSTUB(PutInNdFilter                          ,0xffb52f6c) //102
NHSTUB(PutOutNdFilter                         ,0xffb52fa8) //102
NHSTUB(Read                                   ,0xff815ae0) //120
NHSTUB(ReadFastDir                            ,0xffabc98c) //115
NHSTUB(Rec2PB                                 ,0xff8561ec) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff89b6c4) //104
NHSTUB(RenameFile_Fut                         ,0xff82b290) //116
NHSTUB(Restart                                ,0xff83045c) //106
NHSTUB(ScreenLock                             ,0xff89c69c) //117
NHSTUB(ScreenUnlock                           ,0xff89c700) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb57860) //102
NHSTUB(SetAutoShutdownTime                    ,0xff899430) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff8a5708) //120
NHSTUB(SetFileAttributes                      ,0xff82bd9c) //  6
NHSTUB(SetFileTimeStamp                       ,0xff82bd24) //  6
NHSTUB(SetLogicalEventActive                  ,0xff899108) //101
NHSTUB(SetParameterData                       ,0xff9a4968) //101
NHSTUB(SetPropertyCase                        ,0xff89506c) //101
NHSTUB(SetScriptMode                          ,0xff899158) //120
NHSTUB(SleepTask                              ,0x00437a3c) //120
NHSTUB(TakeSemaphore                          ,0x004376c0) //120
NHSTUB(TurnOffBackLight                       ,0xff8a6954) //104
NHSTUB(TurnOnBackLight                        ,0xff8a693c) //104
NHSTUB(TurnOnDisplay                          ,0xff860e10) //120
NHSTUB(TurnOffDisplay                         ,0xff860e20) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff9c05a8) //120
NHSTUB(UnlockAE                               ,0xff82d904) //120
NHSTUB(UnlockAF                               ,0xff82d568) //120
NHSTUB(UnlockMainPower                        ,0xff899310) //120
NHSTUB(VbattGet                               ,0xff827ad0) //120
NHSTUB(Write                                  ,0xff82b9ec) //120
NHSTUB(WriteSDCard                            ,0xff9776ec) //108
NHSTUB(_log                                   ,0x0043cc38) //111
NHSTUB(_log10                                 ,0x0043d178) //112
NHSTUB(_pow                                   ,0x0043d2f0) //121
NHSTUB(_sqrt                                  ,0x0043ef14) //  6
NHSTUB(add_ptp_handler                        ,0xffa6d3e0) //121
NHSTUB(apex2us                                ,0xffa26d84) //121
NHSTUB(close                                  ,0xff81593c) //109
NHSTUB(err_init_task                          ,0xff814304) //111
NHSTUB(exmem_alloc                            ,0xff88fa58) //101
NHSTUB(exmem_free                             ,0xff88fad0) //101
NHSTUB(free                                   ,0xff812f00) //112
NHSTUB(kbd_p1_f                               ,0xff829238) //109
NHSTUB(kbd_p1_f_cont                          ,0xff829244) //109
NHSTUB(kbd_p2_f                               ,0xff8289d0) //109
NHSTUB(kbd_read_keys                          ,0xff8291e8) //109
NHSTUB(kbd_read_keys_r2                       ,0xff8657f8) //109
NHSTUB(lseek                                  ,0xff82bbb4) //120
NHSTUB(malloc                                 ,0xff812ea8) //112
NHSTUB(memcmp                                 ,0xff81a968) //120
NHSTUB(memcpy                                 ,0xff830dac) //120
NHSTUB(memset                                 ,0xffa24d2c) //120
NHSTUB(mkdir                                  ,0xff82be34) //121
NHSTUB(mktime_ext                             ,0xff8a9c04) //  1
NHSTUB(open                                   ,0xff81588c) //109
NHSTUB(OpenFastDir                            ,0xffabc838) //115
NHSTUB(closedir                               ,0xffabc7e8) //121
NHSTUB(qsort                                  ,0xffb39e18) //  6
NHSTUB(rand                                   ,0xffa24cfc) //121
NHSTUB(realloc                                ,0xffa24da8) //115
NHSTUB(reboot_fw_update                       ,0xffae44e4) //106
NHSTUB(set_control_event                      ,0xff898cfc) //111
NHSTUB(srand                                  ,0xffa24cf0) //122
NHSTUB(stat                                   ,0xff82bbfc) //109
NHSTUB(strcat                                 ,0xff8aa284) //  1
NHSTUB(strchr                                 ,0xff812d74) //  1
NHSTUB(strcmp                                 ,0xff81aa64) //120
NHSTUB(strcpy                                 ,0xff81a950) //120
NHSTUB(strftime                               ,0xff8a9c50) //113
NHSTUB(strlen                                 ,0xff812dc0) //120
NHSTUB(strncmp                                ,0xff812d28) //  1
NHSTUB(strncpy                                ,0xff812cec) //  1
NHSTUB(strrchr                                ,0xff812d98) //  1
NHSTUB(strtol                                 ,0xff830d98) //101
NHSTUB(strtolx                                ,0xff830b9c) //109
   DEF(task_CaptSeq                           ,0xff884680) //120
   DEF(task_ExpDrv                            ,0xff8c276c) //120
   DEF(task_FileWrite                         ,0xffabb7b0) //120
   DEF(task_InitFileModules                   ,0xff856b18) //120
   DEF(task_MovieRecord                       ,0xff990214) //120
   DEF(task_PhySw                             ,0xff828d34) //120
   DEF(task_RotaryEncoder                     ,0xff86601c) //120
   DEF(hook_CreateTask                        ,0x004368b0) //105
NHSTUB(time                                   ,0x0043b6ec) //  6
NHSTUB(vsprintf                               ,0xff81a800) //115
NHSTUB(EngDrvRead                             ,0xff82a078) //102
