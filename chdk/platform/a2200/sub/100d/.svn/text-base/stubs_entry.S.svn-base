// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R47 (DRYOS version 2.3, release #0047)
//   Firmware Ver GM1.00D   // Found @ 0xff889bb0, "GM1.00D" @ 0xff889bbd
//   Firmware build timestamp: Jun 10 2011 14:20:32
//   Canon PowerShot A2200

// Values for makefile.inc
//   PLATFORMOSVER = 47
//   PLATFORMID = 12842 (0x322a) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x001698cc
//   KEYSYS = d4c                // Found @ 0xffff350c
//   NEED_ENCODED_DISKBOOT = 6   // Found @ 0xffff351c
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff97247c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff97243c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffac135c -> ffbe5148
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00032914) // Found @0xff834658
DEF(physw_run                               ,0x00001c30) // Found @0xff834218
DEF(physw_sleep_delay                       ,0x00001c38) // Found @0xff834218
DEF(levent_table                            ,0xffb97b9c) // Found @0xffb97b9c
DEF(FlashParamsTable                        ,0xffbe5384) // Found @0xffbe5384
DEF(movie_status                            ,0x000065ec) // Found @0xff96367c
DEF(video_compression_rate                  ,0x0000662c) // Found @0xff963934
DEF(full_screen_refresh                     ,0x00009010) // Found @0xffa006a8
DEF(canon_menu_active                       ,0x00002eec) // Found @0xff88b5b8
DEF(canon_shoot_menu_active                 ,0x00007aa1) // Found @0xff9a7580
DEF(playrec_mode                            ,0x00002c18) // Found @0xff87da48
DEF(zoom_status                             ,0x0000cb38) // Found @0xffac4a30
DEF(some_flag_for_af_scan                   ,0x000069c4) // Found @0xff967364
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe2a98) // Found @0xfffe2a98
DEF(zoom_busy                               ,0x00006544) // Found @0xff9600c0
DEF(focus_busy                              ,0x00006454) // Found @0xff95d4a0
DEF(recreview_hold                          ,0x000034c0) // Found @0xff898ac8
// Palette colour tables  found @ 0xffbad940
DEF(palette_control                         ,0x00009010) // Found @0xffa00624
DEF(active_palette_buffer                   ,0x00009018) // Found @0xffa00628
DEF(palette_buffer_ptr                      ,0x0000901c) // Found @0xffa009cc
DEF(palette_buffer                          ,0x000b41e4) // Found @0xffa009dc
// Offset from start of palette_buffer to color data = 8 (Found @0xffaf5910)
DEF(viewport_buffers                        ,0xffb552d0) // Found @0xff85198c
DEF(active_viewport_buffer                  ,0x000020d0) // Found @0xff851700
// Camera appears to have only 1 RAW buffer @ 0x421316c0 (Found @0xffb1a788)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff85b81c
//void *vid_get_viewport_fb()      { return (void*)0x40546b80; }             // Found @0xffb1731c
DEF(viewport_fb_d                           ,0x000029f8) // Found 0x29a0 (@0xff871344) + 0x58 (@0xff87137c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x29a0+0x58)); } // Found @0xff871344 & 0xff87137c
DEF(jpeg_count_str                          ,0x000b3b14) // Found @0xff9f71c8
//char *camera_jpeg_count_str()    { return (char*)0x000b3b14; }             // Found @0xff9f71c8
//long hook_raw_size()             { return 0x014d2400; }                    // Found @0xffb1a7e0
//int get_flash_params_count(void) { return 0xa0; }                          // Found @0xff98e5ac

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb5626c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x04000000 // Found @0xffb56294, levent 0x902
//#define USB_IDX             2
//#define BATTCOVER_FLAG      0x00040000 // Found @0xffb56274, levent 0x905
//#define BATTCOVER_IDX       2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x01000000 }, // Found @0xffb561dc, levent 0x601
//    { 0, KEY_POWER           ,0x02000000 }, // Found @0xffb561e4, levent 0x600
//    { 0, KEY_MENU            ,0x04000000 }, // Found @0xffb561ec, levent 0x09
//    { 1, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb56214, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb56214, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb5620c, levent 0x00
//    { 1, KEY_UP              ,0x00001000 }, // Found @0xffb5621c, levent 0x04
//    { 1, KEY_RIGHT           ,0x00002000 }, // Found @0xffb56224, levent 0x07
//    { 1, KEY_DOWN            ,0x00004000 }, // Found @0xffb5622c, levent 0x05
//    { 1, KEY_LEFT            ,0x00008000 }, // Found @0xffb56234, levent 0x06
//    { 1, KEY_ZOOM_OUT        ,0x00010000 }, // Found @0xffb5623c, levent 0x03
//    { 1, KEY_ZOOM_IN         ,0x00020000 }, // Found @0xffb56244, levent 0x02
//    { 1, KEY_SET             ,0x00040000 }, // Found @0xffb5624c, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00080000 }, // Found @0xffb56254, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4416 // Found @0xff937b24
//#define CAM_RAW_ROWS      3296 // Found @0xff937b2c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff83a6a8

// Misc stuff
DEF(ctypes, 0xffb54b52)

// For capt_seq.c
DEF(_nrflag,0x6a00) // Found @ ff96b6d0 (0x69f8) & ff96b70c (+0x08)
//static long *nrflag = (long*)(0x69f8+0x08);  // Found @ ff96b6d0 & ff96b70c
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83a660) //112
NHSTUB(Close                                  ,0xff836d7c) //120
NHSTUB(CreateTask                             ,0xff81e9b0) //120
NHSTUB(DebugAssert                            ,0xff81ec88) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff836778) //116
NHSTUB(DeleteFile_Fut                         ,0xff836694) //112
NHSTUB(DoAELock                               ,0xff8387bc) //120
NHSTUB(DoAFLock                               ,0xff8384c8) //120
NHSTUB(EnterToCompensationEVF                 ,0xff838724) //104
NHSTUB(ExecuteEventProcedure                  ,0xff886db8) //104
NHSTUB(ExitFromCompensationEVF                ,0xff838768) //104
NHSTUB(ExitTask                               ,0xff81ec40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff846c78) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff846d50) //104
NHSTUB(Fclose_Fut                             ,0xff836810) //120
NHSTUB(Feof_Fut                               ,0xff8369fc) //  1
NHSTUB(Fflush_Fut                             ,0xff836a38) //  1
NHSTUB(Fgets_Fut                              ,0xff836964) //  6
NHSTUB(Fopen_Fut                              ,0xff8367d0) //120
NHSTUB(Fread_Fut                              ,0xff8368bc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83a6a0) //112
NHSTUB(Fseek_Fut                              ,0xff8369b0) //120
NHSTUB(Fwrite_Fut                             ,0xff836910) //120
NHSTUB(GetBatteryTemperature                  ,0xff8621dc) //102
NHSTUB(GetCCDTemperature                      ,0xff862168) //102
NHSTUB(GetCurrentAvValue                      ,0xff95f060) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff86fca8) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86fd00) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff86fcd8) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff95e124) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff95e584) //  3
NHSTUB(GetImageFolder                         ,0xff93e9ac) //122
NHSTUB(GetKbdState                            ,0xff8602b4) //109
NHSTUB(GetMemInfo                             ,0xff81a29c) //115
NHSTUB(GetOpticalTemperature                  ,0xff862250) //120
NHSTUB(GetParameterData                       ,0xff98e56c) //101
NHSTUB(GetPropertyCase                        ,0xff88ab20) //102
NHSTUB(GetSystemTime                          ,0xffaafd84) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff853bf0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff853bfc) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff960444) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa9d884) //102
NHSTUB(GiveSemaphore                          ,0xff83a058) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8d66c4) //102
NHSTUB(LEDDrive                               ,0xff85f8c8) //120
NHSTUB(LocalTime                              ,0xff8846a8) //115
NHSTUB(LockMainPower                          ,0xff88f9dc) //120
NHSTUB(MakeDirectory_Fut                      ,0xff836708) //116
NHSTUB(MakeSDCardBootable                     ,0xff86ff38) //105
NHSTUB(MoveFocusLensToDistance                ,0xffb13678) //102
NHSTUB(MoveIrisWithAv                         ,0xffaad664) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffaadd0c) //120
NHSTUB(Open                                   ,0xff836cb4) //120
NHSTUB(PB2Rec                                 ,0xff892ba4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8761b4) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff87618c) //120
NHSTUB(PT_PlaySound                           ,0xff87f6ec) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff88f1a8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff88f1f4) //120
NHSTUB(PutInNdFilter                          ,0xffaadb54) //102
NHSTUB(PutOutNdFilter                         ,0xffaadb78) //102
NHSTUB(Read                                   ,0xff81ad58) //120
NHSTUB(ReadFastDir                            ,0xffa8b014) //  6
NHSTUB(Rec2PB                                 ,0xff892be4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8a3468) //104
NHSTUB(RenameFile_Fut                         ,0xff836600) //116
NHSTUB(Restart                                ,0xff83be70) //106
NHSTUB(ScreenLock                             ,0xff8a46a0) //117
NHSTUB(ScreenUnlock                           ,0xff8a4704) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb164f4) //102
NHSTUB(SetAutoShutdownTime                    ,0xff88fa50) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89675c) //120
NHSTUB(SetFileAttributes                      ,0xff837180) //  6
NHSTUB(SetFileTimeStamp                       ,0xff837108) //  6
NHSTUB(SetLogicalEventActive                  ,0xff88f754) //101
NHSTUB(SetParameterData                       ,0xff98e4dc) //101
NHSTUB(SetPropertyCase                        ,0xff88aa04) //102
NHSTUB(SetScriptMode                          ,0xff88f7a4) //120
NHSTUB(SleepTask                              ,0xff83a304) //120
NHSTUB(TakeSemaphore                          ,0xff839f88) //120
NHSTUB(TurnOffBackLight                       ,0xff89beb8) //104
NHSTUB(TurnOnBackLight                        ,0xff89bea0) //104
NHSTUB(TurnOnDisplay                          ,0xff85bc54) //120
NHSTUB(TurnOffDisplay                         ,0xff85bc64) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff97fad8) //120
NHSTUB(UnlockAE                               ,0xff8387e0) //120
NHSTUB(UnlockAF                               ,0xff838500) //120
NHSTUB(UnlockMainPower                        ,0xff88f930) //120
NHSTUB(UnsetZoomForMovie                      ,0xff99797c) //104
NHSTUB(VbattGet                               ,0xff832e20) //120
NHSTUB(Write                                  ,0xff836dd0) //120
NHSTUB(WriteSDCard                            ,0xff94e7cc) //108
NHSTUB(_log                                   ,0xffb51678) //111
NHSTUB(_log10                                 ,0xffb51bb8) //112
NHSTUB(_pow                                   ,0xffb51d30) //121
NHSTUB(_sqrt                                  ,0xffb53954) //  6
NHSTUB(add_ptp_handler                        ,0xffa40c00) //121
NHSTUB(apex2us                                ,0xffa05a10) //121
NHSTUB(close                                  ,0xff81abb4) //109
NHSTUB(err_init_task                          ,0xff815fd4) //111
NHSTUB(exmem_alloc                            ,0xff885670) //101
NHSTUB(exmem_free                             ,0xff8856e8) //101
NHSTUB(free                                   ,0xff814244) //112
NHSTUB(kbd_p1_f                               ,0xff8346d4) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8346e0) //109
NHSTUB(kbd_p2_f                               ,0xff833ee8) //109
NHSTUB(kbd_read_keys                          ,0xff834658) //109
NHSTUB(kbd_read_keys_r2                       ,0xff85fd0c) //109
NHSTUB(lseek                                  ,0xff836f98) //120
NHSTUB(malloc                                 ,0xff8141ec) //112
NHSTUB(memcmp                                 ,0xff8208bc) //120
NHSTUB(memcpy                                 ,0xff83fce0) //120
NHSTUB(memset                                 ,0xffa04a10) //120
NHSTUB(mkdir                                  ,0xff837218) //109
NHSTUB(mktime_ext                             ,0xff8a54e4) //  1
NHSTUB(open                                   ,0xff81ab04) //109
NHSTUB(OpenFastDir                            ,0xffa8aec0) //  6
NHSTUB(closedir                               ,0xffa8ae70) //121
NHSTUB(qsort                                  ,0xffaf6500) //  6
NHSTUB(rand                                   ,0xffa04b50) //121
NHSTUB(realloc                                ,0xffa04a8c) //115
NHSTUB(reboot_fw_update                       ,0xffa904b0) //106
NHSTUB(set_control_event                      ,0xff88f418) //111
NHSTUB(srand                                  ,0xffa04b44) //122
NHSTUB(stat                                   ,0xff836fe0) //109
NHSTUB(strcat                                 ,0xff8a4c9c) //  1
NHSTUB(strchr                                 ,0xff8140b8) //  1
NHSTUB(strcmp                                 ,0xff820878) //120
NHSTUB(strcpy                                 ,0xff820860) //120
NHSTUB(strftime                               ,0xff8a4ee4) //113
NHSTUB(strlen                                 ,0xff814104) //120
NHSTUB(strncmp                                ,0xff81406c) //  1
NHSTUB(strncpy                                ,0xff814030) //  1
NHSTUB(strrchr                                ,0xff8140dc) //  1
NHSTUB(strtol                                 ,0xff83ffe0) //101
NHSTUB(strtolx                                ,0xff83fde4) //109
   DEF(task_CaptSeq                           ,0xff8788f0) //120
   DEF(task_ExpDrv                            ,0xff8bbe80) //120
   DEF(task_FileWrite                         ,0xffa88ec4) //120
   DEF(task_InitFileModules                   ,0xff8933bc) //120
   DEF(task_MovieRecord                       ,0xff964148) //120
   DEF(task_PhySw                             ,0xff834214) //120
NHSTUB(time                                   ,0xff884c84) //109
NHSTUB(vsprintf                               ,0xff820820) //115
NHSTUB(EngDrvRead                             ,0xff835520) //102
