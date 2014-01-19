// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.00F   // Found @ 0xff87dc7c, "GM1.00F" @ 0xff87dc89
//   Firmware build timestamp: Jun  4 2012 19:11:37
//   Canon PowerShot A2300

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12874 (0x324a) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x001585f0
//   KEYSYS = d4c                // Found @ 0xffff1d28
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff1d38

// Note, ROM copied to RAM :- from 0xffc0246c, to 0x003f1000, len 15733 words.
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff96a04c
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff96a010

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DeleteFile_Fut                       ,0xff830fb4) //  1 90%        == 0xff830fb4
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff831ac4
// ERROR: rand is not found.                               //--- ---    *** != 0x00000000
// ERROR: srand is not found.                              //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa7ff20 -> ffba0ae8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00031160) // Found @0xff82edb8
DEF(physw_run                               ,0x00001c18) // Found @0xff82e968
DEF(physw_sleep_delay                       ,0x00001c20) // Found @0xff82e968
DEF(levent_table                            ,0xffb5ccac) // Found @0xffb5ccac
DEF(FlashParamsTable                        ,0xffba0d44) // Found @0xffba0d44
DEF(movie_status                            ,0x0000635c) // Found @0xff95a260
DEF(video_compression_rate                  ,0x0000639c) // Found @0xff95ae7c
DEF(full_screen_refresh                     ,0x0000860c) // Found @0xff9d2a44
DEF(canon_menu_active                       ,0x00002e4c) // Found @0xff87f714
DEF(canon_shoot_menu_active                 ,0x000077a1) // Found @0xff99b6bc
DEF(playrec_mode                            ,0x00002ba0) // Found @0xff873814
DEF(zoom_status                             ,0x0000b3e8) // Found @0xffa836b8
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfffeabc8) // Found @0xfffeabc8
DEF(zoom_busy                               ,0x0000623c) // Found @0xff95656c
DEF(focus_busy                              ,0x00006114) // Found @0xff953640
DEF(recreview_hold                          ,0x000033f8) // Found @0xff88d2d4
// Palette colour tables  found @ 0xffb6dc10
DEF(palette_control                         ,0x0000860c) // Found @0xff9d29c0
DEF(active_palette_buffer                   ,0x00008614) // Found @0xff9d29c4
DEF(palette_buffer_ptr                      ,0x00008618) // Found @0xff9d2d58
DEF(palette_buffer                          ,0x000b42c0) // Found @0xff9d2d68
// Offset from start of palette_buffer to color data = 4 (Found @0xffab6800)
DEF(viewport_buffers                        ,0xffb10f24) // Found @0xff849d68
DEF(active_viewport_buffer                  ,0x000020bc) // Found @0xff849ad0
// Camera appears to have only 1 RAW buffer @ 0x420b7fc0 (Found @0xffae20c8)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff852ebc
//void *vid_get_viewport_fb()      { return (void*)0x40566b80; }             // Found @0xffadf2ec
DEF(viewport_fb_d                           ,0x000029c4) // Found 0x2970 (@0xff867dc0) + 0x54 (@0xff867df8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2970+0x54)); } // Found @0xff867dc0 & 0xff867df8
DEF(jpeg_count_str                          ,0x000b3b6c) // Found @0xff9c927c
//char *camera_jpeg_count_str()    { return (char*)0x000b3b6c; }             // Found @0xff9c927c
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xffae2120
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff985a60

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb113ec, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb113f4, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_ZOOM_OUT        ,0x00001000 }, // Found @0xffb11374, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00002000 }, // Found @0xffb1137c, levent 0x02
//    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xffb1138c, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xffb1138c, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xffb11384, levent 0x00
//    { 1, KEY_UP              ,0x00400000 }, // Found @0xffb11394, levent 0x04
//    { 1, KEY_DOWN            ,0x00800000 }, // Found @0xffb1139c, levent 0x05
//    { 1, KEY_RIGHT           ,0x01000000 }, // Found @0xffb113a4, levent 0x07
//    { 1, KEY_LEFT            ,0x02000000 }, // Found @0xffb113ac, levent 0x06
//    { 1, KEY_MENU            ,0x04000000 }, // Found @0xffb113b4, levent 0x09
//    { 1, KEY_SET             ,0x08000000 }, // Found @0xffb113bc, levent 0x08
//    { 1, KEY_VIDEO           ,0x10000000 }, // Found @0xffb113c4, levent 0x1a
//    { 1, KEY_HELP            ,0x20000000 }, // Found @0xffb113cc, levent 0x14
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffb113d4, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffb113dc, levent 0x101
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff92e3e0
//#define CAM_RAW_ROWS      3504 // Found @0xff92e3ec
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff834324

// Misc stuff
DEF(ctypes, 0xffb10774)

// For capt_seq.c
DEF(_nrflag,0x8748) // Found @ ff9df5b4 (0x8748) & ff9df5f0 (+0x00)
//static long *nrflag = (long*)(0x8748+0x00);  // Found @ ff9df5b4 & ff9df5f0
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8342dc) //112
NHSTUB(Close                                  ,0xff831628) //120
NHSTUB(CreateTask                             ,0x003f6824) //120
NHSTUB(DebugAssert                            ,0x003f6afc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff831028) //116
NHSTUB(DoAELock                               ,0xff833164) //120
NHSTUB(DoAFLock                               ,0xff832e70) //120
NHSTUB(EnterToCompensationEVF                 ,0xff8330cc) //104
NHSTUB(ExecuteEventProcedure                  ,0xff87ac3c) //104
NHSTUB(ExitFromCompensationEVF                ,0xff833110) //104
NHSTUB(ExitTask                               ,0x003f6ab4) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff83d768) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff83d8c4) //104
NHSTUB(Fclose_Fut                             ,0xff8310c0) //120
NHSTUB(Feof_Fut                               ,0xff8312ac) //  1
NHSTUB(Fflush_Fut                             ,0xff8312e8) //  1
NHSTUB(Fgets_Fut                              ,0xff831214) //  6
NHSTUB(Fopen_Fut                              ,0xff831080) //120
NHSTUB(Fread_Fut                              ,0xff83116c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff83431c) //112
NHSTUB(Fseek_Fut                              ,0xff831260) //120
NHSTUB(Fwrite_Fut                             ,0xff8311c0) //120
NHSTUB(GetBatteryTemperature                  ,0xff858d28) //102
NHSTUB(GetCCDTemperature                      ,0xff858cb4) //102
NHSTUB(GetCurrentAvValue                      ,0xff9551ac) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff866814) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff86686c) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff866844) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff954404) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff954854) //  3
NHSTUB(GetImageFolder                         ,0xff937960) //122
NHSTUB(GetKbdState                            ,0xff856acc) //109
NHSTUB(GetMemInfo                             ,0xff81509c) //115
NHSTUB(GetOpticalTemperature                  ,0xff858d9c) //120
NHSTUB(GetParameterData                       ,0xff985a20) //101
NHSTUB(GetPropertyCase                        ,0xff87ecb4) //102
NHSTUB(GetSystemTime                          ,0xffa72320) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff84be48) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff84be54) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff9569ec) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa63fc0) //102
NHSTUB(GiveSemaphore                          ,0x003f7704) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8ca0f4) //102
NHSTUB(LEDDrive                               ,0xff95c454) //120
NHSTUB(LocalTime                              ,0x003fb1b8) //115
NHSTUB(LockMainPower                          ,0xff883560) //120
NHSTUB(MakeSDCardBootable                     ,0xff866aa4) //105
NHSTUB(MoveFocusLensToDistance                ,0xffadb3a4) //102
NHSTUB(MoveIrisWithAv                         ,0xffa6e230) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa6e958) //120
NHSTUB(Open                                   ,0xff831560) //120
NHSTUB(PB2Rec                                 ,0xff8863c8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86c880) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86c858) //120
NHSTUB(PT_PlaySound                           ,0xff875478) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff882c54) //120
NHSTUB(PostLogicalEventToUI                   ,0xff882ca0) //120
NHSTUB(PutInNdFilter                          ,0xffa6e730) //102
NHSTUB(PutOutNdFilter                         ,0xffa6e754) //102
NHSTUB(Read                                   ,0xff815b58) //120
NHSTUB(ReadFastDir                            ,0xffa544f0) //115
NHSTUB(Rec2PB                                 ,0xff886408) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8950a4) //104
NHSTUB(RenameFile_Fut                         ,0xff830f20) //116
NHSTUB(Restart                                ,0xff835af0) //106
NHSTUB(ScreenLock                             ,0xff8960c4) //117
NHSTUB(ScreenUnlock                           ,0xff896128) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffade4c4) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8835d4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff88a60c) //120
NHSTUB(SetFileAttributes                      ,0xff831a2c) //  6
NHSTUB(SetFileTimeStamp                       ,0xff8319b4) //  6
NHSTUB(SetLogicalEventActive                  ,0xff8832dc) //101
NHSTUB(SetParameterData                       ,0xff985990) //101
NHSTUB(SetPropertyCase                        ,0xff87eb2c) //102
NHSTUB(SetScriptMode                          ,0xff88332c) //120
NHSTUB(SleepTask                              ,0x003f79b0) //120
NHSTUB(TakeSemaphore                          ,0x003f7634) //120
NHSTUB(TurnOffBackLight                       ,0xff8902c0) //104
NHSTUB(TurnOnBackLight                        ,0xff8902a8) //104
NHSTUB(TurnOnDisplay                          ,0xff8532ac) //120
NHSTUB(TurnOffDisplay                         ,0xff8532bc) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff977f80) //120
NHSTUB(UnlockAE                               ,0xff833188) //120
NHSTUB(UnlockAF                               ,0xff832ea8) //120
NHSTUB(UnlockMainPower                        ,0xff8834b4) //120
NHSTUB(UnsetZoomForMovie                      ,0xff98c15c) //104
NHSTUB(VbattGet                               ,0xff82c3d0) //120
NHSTUB(Write                                  ,0xff83167c) //120
NHSTUB(WriteSDCard                            ,0xff9476c4) //108
NHSTUB(_log                                   ,0x003fcce0) //111
NHSTUB(_log10                                 ,0x003fd220) //112
NHSTUB(_pow                                   ,0x003fd398) //121
NHSTUB(_sqrt                                  ,0x003fefbc) //  6
NHSTUB(add_ptp_handler                        ,0xffa174bc) //121
NHSTUB(apex2us                                ,0xff9d8dc0) //121
NHSTUB(close                                  ,0xff8159b4) //109
NHSTUB(err_init_task                          ,0xff81437c) //111
NHSTUB(exmem_alloc                            ,0xff879610) //101
NHSTUB(exmem_free                             ,0xff879688) //101
NHSTUB(free                                   ,0xff812f78) //112
NHSTUB(kbd_p1_f                               ,0xff82ee08) //109
NHSTUB(kbd_p1_f_cont                          ,0xff82ee14) //109
NHSTUB(kbd_p2_f                               ,0xff82e600) //109
NHSTUB(kbd_read_keys                          ,0xff82edb8) //109
NHSTUB(kbd_read_keys_r2                       ,0xff8565e8) //109
NHSTUB(lseek                                  ,0xff831844) //120
NHSTUB(malloc                                 ,0xff812f20) //112
NHSTUB(memcmp                                 ,0xff81ae34) //120
NHSTUB(memcpy                                 ,0xff83725c) //120
NHSTUB(memset                                 ,0xff9d7050) //120
NHSTUB(mkdir                                  ,0xff831ac4) //121
NHSTUB(mktime_ext                             ,0xff8965f4) //  1
NHSTUB(open                                   ,0xff815904) //109
NHSTUB(OpenFastDir                            ,0xffa5439c) //115
NHSTUB(closedir                               ,0xffa5434c) //121
NHSTUB(qsort                                  ,0xff9d6ff0) //  6
NHSTUB(realloc                                ,0xff9d70cc) //115
NHSTUB(reboot_fw_update                       ,0xffa598cc) //106
NHSTUB(set_control_event                      ,0xff882f9c) //111
NHSTUB(stat                                   ,0xff83188c) //109
NHSTUB(strcat                                 ,0xff896c74) //  1
NHSTUB(strchr                                 ,0xff812dec) //  1
NHSTUB(strcmp                                 ,0xff81af30) //120
NHSTUB(strcpy                                 ,0xff81ae1c) //120
NHSTUB(strftime                               ,0xff896640) //113
NHSTUB(strlen                                 ,0xff812e38) //120
NHSTUB(strncmp                                ,0xff812da0) //  1
NHSTUB(strncpy                                ,0xff812d64) //  1
NHSTUB(strrchr                                ,0xff812e10) //  1
NHSTUB(strtol                                 ,0xff837248) //101
NHSTUB(strtolx                                ,0xff83704c) //109
   DEF(task_CaptSeq                           ,0xff86f0f0) //120
   DEF(task_ExpDrv                            ,0xff8aee90) //120
   DEF(task_FileWrite                         ,0xffa52d50) //120
   DEF(task_InitFileModules                   ,0xff886c2c) //120
   DEF(task_MovieRecord                       ,0xff95b70c) //120
   DEF(task_PhySw                             ,0xff82e964) //120
NHSTUB(time                                   ,0x003fb794) //  6
NHSTUB(vsprintf                               ,0xff81accc) //115
NHSTUB(EngDrvRead                             ,0xff82fdb0) //102
