// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.01A   // Found @ 0xff881328, "GM1.01A" @ 0xff881335
//   Firmware build timestamp: Feb 10 2012 14:53:03
//   Canon PowerShot A3400 IS

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12872 (0x3248) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0015967c
//   KEYSYS = d4c                // Found @ 0xffff1d28
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff1d38

// Note, ROM copied to RAM :- from 0xffc241c8, to 0x003f1000, len 15765 words.
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff972040
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff972004

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff830e64) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff831974
// ERROR: rand is not found.                               //--- ---    *** != 0x00000000
// ERROR: srand is not found.                              //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa97628 -> ffbc05c8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00031ba0) // Found @0xff82edd0
DEF(physw_run                               ,0x00001c18) // Found @0xff82e980
DEF(physw_sleep_delay                       ,0x00001c20) // Found @0xff82e980
DEF(levent_table                            ,0xffb7afcc) // Found @0xffb7afcc
DEF(FlashParamsTable                        ,0xffbc0820) // Found @0xffbc0820
DEF(movie_status                            ,0x00006524) // Found @0xff961dbc
DEF(video_compression_rate                  ,0x00006564) // Found @0xff9629d8
DEF(full_screen_refresh                     ,0x00008a28) // Found @0xff9ea698
DEF(canon_menu_active                       ,0x00002f10) // Found @0xff882dc0
DEF(canon_shoot_menu_active                 ,0x000079f1) // Found @0xff9a6af8
DEF(playrec_mode                            ,0x00002c60) // Found @0xff876cd8
DEF(zoom_status                             ,0x0000bb7c) // Found @0xffa9add0
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfffeabc8) // Found @0xfffeabc8
DEF(zoom_busy                               ,0x000063b0) // Found @0xff95cc84
DEF(focus_busy                              ,0x0000621c) // Found @0xff9580c0
DEF(recreview_hold                          ,0x000034d0) // Found @0xff890ce0
// Palette colour tables  found @ 0xffb8d4fc
DEF(palette_control                         ,0x00008a28) // Found @0xff9ea614
DEF(active_palette_buffer                   ,0x00008a30) // Found @0xff9ea618
DEF(palette_buffer_ptr                      ,0x00008a34) // Found @0xff9ea9ac
DEF(palette_buffer                          ,0x000b38f0) // Found @0xff9ea9bc
// Offset from start of palette_buffer to color data = 4 (Found @0xffad3ca0)
DEF(viewport_buffers                        ,0xffb2f90c) // Found @0xff849c00
DEF(active_viewport_buffer                  ,0x000020bc) // Found @0xff849968
// Camera appears to have only 1 RAW buffer @ 0x420b7fc0 (Found @0xffafccc4)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff852d54
//void *vid_get_viewport_fb()      { return (void*)0x40566b80; }             // Found @0xffaf9ee8
DEF(viewport_fb_d                           ,0x000029f4) // Found 0x29a0 (@0xff868904) + 0x54 (@0xff86893c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x29a0+0x54)); } // Found @0xff868904 & 0xff86893c
DEF(jpeg_count_str                          ,0x000b3004) // Found @0xff9dddec
//char *camera_jpeg_count_str()    { return (char*)0x000b3004; }             // Found @0xff9dddec
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xffafcd1c
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff98f5ac

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb2fdd4, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb2fddc, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_ZOOM_OUT        ,0x00001000 }, // Found @0xffb2fd5c, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00002000 }, // Found @0xffb2fd64, levent 0x02
//    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xffb2fd74, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xffb2fd74, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xffb2fd6c, levent 0x00
//    { 1, KEY_UP              ,0x00400000 }, // Found @0xffb2fd7c, levent 0x04
//    { 1, KEY_DOWN            ,0x00800000 }, // Found @0xffb2fd84, levent 0x05
//    { 1, KEY_RIGHT           ,0x01000000 }, // Found @0xffb2fd8c, levent 0x07
//    { 1, KEY_LEFT            ,0x02000000 }, // Found @0xffb2fd94, levent 0x06
//    { 1, KEY_MENU            ,0x04000000 }, // Found @0xffb2fd9c, levent 0x09
//    { 1, KEY_SET             ,0x08000000 }, // Found @0xffb2fda4, levent 0x08
//    { 1, KEY_VIDEO           ,0x10000000 }, // Found @0xffb2fdac, levent 0x1a
//    { 1, KEY_HELP            ,0x20000000 }, // Found @0xffb2fdb4, levent 0x14
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffb2fdbc, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffb2fdc4, levent 0x101
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff932e60
//#define CAM_RAW_ROWS      3504 // Found @0xff932e6c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff8342d0

// Misc stuff
DEF(ctypes, 0xffb2f15c)

// For capt_seq.c
DEF(_nrflag,0x8b64) // Found @ ff9f71f4 (0x8b64) & ff9f7230 (+0x00)
//static long *nrflag = (long*)(0x8b64+0x00);  // Found @ ff9f71f4 & ff9f7230
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff834288) //112
NHSTUB(Close                                  ,0xff8314d8) //120
NHSTUB(CreateTask                             ,0x003f6824) //120
NHSTUB(DebugAssert                            ,0x003f6afc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff830ed8) //116
NHSTUB(DoAELock                               ,0xff833028) //120
NHSTUB(DoAFLock                               ,0xff832d74) //120
NHSTUB(EnterToCompensationEVF                 ,0xff832f90) //104
NHSTUB(ExecuteEventProcedure                  ,0xff87e2e8) //104
NHSTUB(ExitFromCompensationEVF                ,0xff832fd4) //104
NHSTUB(ExitTask                               ,0x003f6ab4) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff83d718) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff83d874) //104
NHSTUB(Fclose_Fut                             ,0xff830f70) //120
NHSTUB(Feof_Fut                               ,0xff83115c) //  1
NHSTUB(Fflush_Fut                             ,0xff831198) //  1
NHSTUB(Fgets_Fut                              ,0xff8310c4) //  6
NHSTUB(Fopen_Fut                              ,0xff830f30) //120
NHSTUB(Fread_Fut                              ,0xff83101c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8342c8) //112
NHSTUB(Fseek_Fut                              ,0xff831110) //120
NHSTUB(Fwrite_Fut                             ,0xff831070) //120
NHSTUB(GetBatteryTemperature                  ,0xff858994) //102
NHSTUB(GetCCDTemperature                      ,0xff858920) //102
NHSTUB(GetCurrentAvValue                      ,0xff959c84) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff867094) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff8670ec) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff8670c4) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff958e84) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9592d4) //  3
NHSTUB(GetImageFolder                         ,0xff93c3e0) //122
NHSTUB(GetKbdState                            ,0xff8569a0) //109
NHSTUB(GetMemInfo                             ,0xff81509c) //115
NHSTUB(GetOpticalTemperature                  ,0xff858a08) //120
NHSTUB(GetParameterData                       ,0xff98f56c) //101
NHSTUB(GetPropertyCase                        ,0xff882360) //102
NHSTUB(GetSystemTime                          ,0xffa89db4) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff84bce0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff84bcec) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff95d104) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa7ad40) //102
NHSTUB(GiveSemaphore                          ,0x003f7704) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8cca9c) //102
NHSTUB(LEDDrive                               ,0xff964050) //120
NHSTUB(LocalTime                              ,0x003fb1b8) //115
NHSTUB(LockMainPower                          ,0xff8870ac) //120
NHSTUB(MakeSDCardBootable                     ,0xff867324) //105
NHSTUB(MoveFocusLensToDistance                ,0xffaf5fa0) //102
NHSTUB(MoveIrisWithAv                         ,0xffa851ec) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa85920) //120
NHSTUB(Open                                   ,0xff831410) //120
NHSTUB(PB2Rec                                 ,0xff889df4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86fbfc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86fbd4) //120
NHSTUB(PT_PlaySound                           ,0xff878b24) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff886760) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8867ac) //120
NHSTUB(PutInNdFilter                          ,0xffa856f8) //102
NHSTUB(PutOutNdFilter                         ,0xffa8571c) //102
NHSTUB(Read                                   ,0xff815b58) //120
NHSTUB(ReadFastDir                            ,0xffa6a478) //115
NHSTUB(Rec2PB                                 ,0xff889e34) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff898d00) //104
NHSTUB(RenameFile_Fut                         ,0xff830dd0) //116
NHSTUB(Restart                                ,0xff835a9c) //106
NHSTUB(ScreenLock                             ,0xff899d20) //117
NHSTUB(ScreenUnlock                           ,0xff899d84) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffaf90c0) //102
NHSTUB(SetAutoShutdownTime                    ,0xff887120) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff88e13c) //120
NHSTUB(SetFileAttributes                      ,0xff8318dc) //  6
NHSTUB(SetFileTimeStamp                       ,0xff831864) //  6
NHSTUB(SetLogicalEventActive                  ,0xff886e28) //101
NHSTUB(SetParameterData                       ,0xff98f4dc) //101
NHSTUB(SetPropertyCase                        ,0xff8821d8) //102
NHSTUB(SetScriptMode                          ,0xff886e78) //120
NHSTUB(SleepTask                              ,0x003f79b0) //120
NHSTUB(TakeSemaphore                          ,0x003f7634) //120
NHSTUB(TurnOffBackLight                       ,0xff893d3c) //104
NHSTUB(TurnOnBackLight                        ,0xff893d24) //104
NHSTUB(TurnOnDisplay                          ,0xff853144) //120
NHSTUB(TurnOffDisplay                         ,0xff853154) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff9800a0) //120
NHSTUB(UnlockAE                               ,0xff83304c) //120
NHSTUB(UnlockAF                               ,0xff832dac) //120
NHSTUB(UnlockMainPower                        ,0xff887000) //120
NHSTUB(UnsetZoomForMovie                      ,0xff995d98) //104
NHSTUB(VbattGet                               ,0xff82c3cc) //120
NHSTUB(Write                                  ,0xff83152c) //120
NHSTUB(WriteSDCard                            ,0xff94c144) //108
NHSTUB(_log                                   ,0x003fcce0) //111
NHSTUB(_log10                                 ,0x003fd220) //112
NHSTUB(_pow                                   ,0x003fd398) //121
NHSTUB(_sqrt                                  ,0x003ff038) //  6
NHSTUB(add_ptp_handler                        ,0xffa2cf44) //121
NHSTUB(apex2us                                ,0xff9f0a14) //121
NHSTUB(close                                  ,0xff8159b4) //109
NHSTUB(err_init_task                          ,0xff81437c) //111
NHSTUB(exmem_alloc                            ,0xff87ccbc) //101
NHSTUB(exmem_free                             ,0xff87cd34) //101
NHSTUB(free                                   ,0xff812f78) //112
NHSTUB(kbd_p1_f                               ,0xff82ee20) //109
NHSTUB(kbd_p1_f_cont                          ,0xff82ee2c) //109
NHSTUB(kbd_p2_f                               ,0xff82e618) //109
NHSTUB(kbd_read_keys                          ,0xff82edd0) //109
NHSTUB(kbd_read_keys_r2                       ,0xff8564b0) //109
NHSTUB(lseek                                  ,0xff8316f4) //120
NHSTUB(malloc                                 ,0xff812f20) //112
NHSTUB(memcmp                                 ,0xff81ae30) //120
NHSTUB(memcpy                                 ,0xff83720c) //120
NHSTUB(memset                                 ,0xff9eeca4) //120
NHSTUB(mkdir                                  ,0xff831974) //121
NHSTUB(mktime_ext                             ,0xff89a250) //  1
NHSTUB(open                                   ,0xff815904) //109
NHSTUB(OpenFastDir                            ,0xffa6a324) //115
NHSTUB(closedir                               ,0xffa6a2d4) //121
NHSTUB(qsort                                  ,0xff9eec44) //  6
NHSTUB(realloc                                ,0xff9eed20) //115
NHSTUB(reboot_fw_update                       ,0xffa6f854) //106
NHSTUB(set_control_event                      ,0xff886ad4) //111
NHSTUB(stat                                   ,0xff83173c) //109
NHSTUB(strcat                                 ,0xff89a8d0) //  1
NHSTUB(strchr                                 ,0xff812dec) //  1
NHSTUB(strcmp                                 ,0xff81af2c) //120
NHSTUB(strcpy                                 ,0xff81ae18) //120
NHSTUB(strftime                               ,0xff89a29c) //113
NHSTUB(strlen                                 ,0xff812e38) //120
NHSTUB(strncmp                                ,0xff812da0) //  1
NHSTUB(strncpy                                ,0xff812d64) //  1
NHSTUB(strrchr                                ,0xff812e10) //  1
NHSTUB(strtol                                 ,0xff8371f8) //101
NHSTUB(strtolx                                ,0xff836ffc) //109
   DEF(task_CaptSeq                           ,0xff872424) //120
   DEF(task_ExpDrv                            ,0xff8b1a4c) //120
   DEF(task_FileWrite                         ,0xffa68cd8) //120
   DEF(task_InitFileModules                   ,0xff88a668) //120
   DEF(task_MovieRecord                       ,0xff963268) //120
   DEF(task_PhySw                             ,0xff82e97c) //120
   DEF(task_TouchPanel                        ,0xff859214) //120
NHSTUB(time                                   ,0x003fb794) //  6
NHSTUB(vsprintf                               ,0xff81acc8) //115
NHSTUB(EngDrvRead                             ,0xff82fc60) //102
