// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.01A   // Found @ 0xff87fb50, "GM1.01A" @ 0xff87fb5d
//   Firmware build timestamp: Feb 10 2012 12:50:54
//   Canon PowerShot A4000 IS

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12867 (0x3243) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00157c84
//   KEYSYS = d4c                // Found @ 0xffff1d28
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff1d38

// Note, ROM copied to RAM :- from 0xffc04d54, to 0x003f1000, len 15733 words.
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff96d684
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff96d648

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff830e30) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff831940
// ERROR: rand is not found.                               //--- ---    *** != 0x00000000
// ERROR: srand is not found.                              //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa82714 -> ffba19b8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00031270) // Found @0xff82ed9c
DEF(physw_run                               ,0x00001c18) // Found @0xff82e94c
DEF(physw_sleep_delay                       ,0x00001c20) // Found @0xff82e94c
DEF(levent_table                            ,0xffb5d664) // Found @0xffb5d664
DEF(FlashParamsTable                        ,0xffba1c10) // Found @0xffba1c10
DEF(movie_status                            ,0x00006424) // Found @0xff95d8bc
DEF(video_compression_rate                  ,0x00006464) // Found @0xff95e4d8
DEF(full_screen_refresh                     ,0x0000872c) // Found @0xff9d75c0
DEF(canon_menu_active                       ,0x00002ec8) // Found @0xff8815e8
DEF(canon_shoot_menu_active                 ,0x00007881) // Found @0xff99fa04
DEF(playrec_mode                            ,0x00002c1c) // Found @0xff8755f4
DEF(zoom_status                             ,0x0000b750) // Found @0xffa85eac
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 127 entries in the table - set NUM_FL to 127
DEF(focus_len_table                         ,0xfffeabc8) // Found @0xfffeabc8
DEF(zoom_busy                               ,0x000062bc) // Found @0xff958830
DEF(focus_busy                              ,0x00006150) // Found @0xff953fbc
DEF(recreview_hold                          ,0x00003474) // Found @0xff88eeac
// Palette colour tables  found @ 0xffb6e604
DEF(palette_control                         ,0x0000872c) // Found @0xff9d753c
DEF(active_palette_buffer                   ,0x00008734) // Found @0xff9d7540
DEF(palette_buffer_ptr                      ,0x00008738) // Found @0xff9d78d4
DEF(palette_buffer                          ,0x000b2228) // Found @0xff9d78e4
// Offset from start of palette_buffer to color data = 4 (Found @0xffab8f00)
DEF(viewport_buffers                        ,0xffb0f144) // Found @0xff849bd8
DEF(active_viewport_buffer                  ,0x000020b4) // Found @0xff849940
// Camera appears to have only 1 RAW buffer @ 0x420b7fc0 (Found @0xffae1e1c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40411000; }             // Found @0xff852d80
//void *vid_get_viewport_fb()      { return (void*)0x40566b80; }             // Found @0xffadf040
DEF(viewport_fb_d                           ,0x000029b4) // Found 0x2960 (@0xff867a04) + 0x54 (@0xff867a3c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2960+0x54)); } // Found @0xff867a04 & 0xff867a3c
DEF(jpeg_count_str                          ,0x000b1abc) // Found @0xff9cd838
//char *camera_jpeg_count_str()    { return (char*)0x000b1abc; }             // Found @0xff9cd838
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xffae1e74
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff989b60

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb0f608, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb0f610, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_ZOOM_OUT        ,0x00001000 }, // Found @0xffb0f590, levent 0x03
//    { 0, KEY_ZOOM_IN         ,0x00002000 }, // Found @0xffb0f598, levent 0x02
//    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xffb0f5a8, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xffb0f5a8, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xffb0f5a0, levent 0x00
//    { 1, KEY_UP              ,0x00400000 }, // Found @0xffb0f5b0, levent 0x04
//    { 1, KEY_DOWN            ,0x00800000 }, // Found @0xffb0f5b8, levent 0x05
//    { 1, KEY_RIGHT           ,0x01000000 }, // Found @0xffb0f5c0, levent 0x07
//    { 1, KEY_LEFT            ,0x02000000 }, // Found @0xffb0f5c8, levent 0x06
//    { 1, KEY_MENU            ,0x04000000 }, // Found @0xffb0f5d0, levent 0x09
//    { 1, KEY_SET             ,0x08000000 }, // Found @0xffb0f5d8, levent 0x08
//    { 1, KEY_VIDEO           ,0x10000000 }, // Found @0xffb0f5e0, levent 0x1a
//    { 1, KEY_HELP            ,0x20000000 }, // Found @0xffb0f5e8, levent 0x14
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffb0f5f0, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffb0f5f8, levent 0x101
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff92edac
//#define CAM_RAW_ROWS      3504 // Found @0xff92edb8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff8342c4

// Misc stuff
DEF(ctypes, 0xffb0e994)

// For capt_seq.c
DEF(_nrflag,0x8868) // Found @ ff9e4120 (0x8868) & ff9e415c (+0x00)
//static long *nrflag = (long*)(0x8868+0x00);  // Found @ ff9e4120 & ff9e415c
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff83427c) //112
NHSTUB(Close                                  ,0xff8314a4) //120
NHSTUB(CreateTask                             ,0x003f6824) //120
NHSTUB(DebugAssert                            ,0x003f6afc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff830ea4) //116
NHSTUB(DoAELock                               ,0xff833020) //120
NHSTUB(DoAFLock                               ,0xff832d24) //120
NHSTUB(EnterToCompensationEVF                 ,0xff832f88) //104
NHSTUB(ExecuteEventProcedure                  ,0xff87cb10) //104
NHSTUB(ExitFromCompensationEVF                ,0xff832fcc) //104
NHSTUB(ExitTask                               ,0x003f6ab4) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff83d708) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff83d864) //104
NHSTUB(Fclose_Fut                             ,0xff830f3c) //120
NHSTUB(Feof_Fut                               ,0xff831128) //  1
NHSTUB(Fflush_Fut                             ,0xff831164) //  1
NHSTUB(Fgets_Fut                              ,0xff831090) //  6
NHSTUB(Fopen_Fut                              ,0xff830efc) //120
NHSTUB(Fread_Fut                              ,0xff830fe8) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8342bc) //112
NHSTUB(Fseek_Fut                              ,0xff8310dc) //120
NHSTUB(Fwrite_Fut                             ,0xff83103c) //120
NHSTUB(GetBatteryTemperature                  ,0xff85896c) //102
NHSTUB(GetCCDTemperature                      ,0xff8588f8) //102
NHSTUB(GetCurrentAvValue                      ,0xff955b6c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff866458) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff8664b0) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff866488) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff954d80) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9551d0) //  3
NHSTUB(GetImageFolder                         ,0xff938318) //122
NHSTUB(GetKbdState                            ,0xff856978) //109
NHSTUB(GetMemInfo                             ,0xff81508c) //115
NHSTUB(GetOpticalTemperature                  ,0xff8589e0) //120
NHSTUB(GetParameterData                       ,0xff989b20) //101
NHSTUB(GetPropertyCase                        ,0xff880b88) //102
NHSTUB(GetSystemTime                          ,0xffa74adc) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff84bcb8) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff84bcc4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff958ca4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa65c38) //102
NHSTUB(GiveSemaphore                          ,0x003f7704) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8cab30) //102
NHSTUB(LEDDrive                               ,0xff95fac0) //120
NHSTUB(LocalTime                              ,0x003fb1b8) //115
NHSTUB(LockMainPower                          ,0xff885438) //120
NHSTUB(MakeSDCardBootable                     ,0xff8666e8) //105
NHSTUB(MoveFocusLensToDistance                ,0xffadb0fc) //102
NHSTUB(MoveIrisWithAv                         ,0xffa6ff14) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa70648) //120
NHSTUB(Open                                   ,0xff8313dc) //120
NHSTUB(PB2Rec                                 ,0xff888168) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86e588) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86e560) //120
NHSTUB(PT_PlaySound                           ,0xff87734c) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff884b2c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff884b78) //120
NHSTUB(PutInNdFilter                          ,0xffa70420) //102
NHSTUB(PutOutNdFilter                         ,0xffa70444) //102
NHSTUB(Read                                   ,0xff815b48) //120
NHSTUB(ReadFastDir                            ,0xffa561d4) //115
NHSTUB(Rec2PB                                 ,0xff8881a8) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff896d88) //104
NHSTUB(RenameFile_Fut                         ,0xff830d9c) //116
NHSTUB(Restart                                ,0xff835a90) //106
NHSTUB(ScreenLock                             ,0xff897da8) //117
NHSTUB(ScreenUnlock                           ,0xff897e0c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffade218) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8854ac) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff88c324) //120
NHSTUB(SetFileAttributes                      ,0xff8318a8) //  6
NHSTUB(SetFileTimeStamp                       ,0xff831830) //  6
NHSTUB(SetLogicalEventActive                  ,0xff8851b4) //101
NHSTUB(SetParameterData                       ,0xff989a90) //101
NHSTUB(SetPropertyCase                        ,0xff880a00) //102
NHSTUB(SetScriptMode                          ,0xff885204) //120
NHSTUB(SleepTask                              ,0x003f79b0) //120
NHSTUB(TakeSemaphore                          ,0x003f7634) //120
NHSTUB(TurnOffBackLight                       ,0xff891ea8) //104
NHSTUB(TurnOnBackLight                        ,0xff891e90) //104
NHSTUB(TurnOnDisplay                          ,0xff853170) //120
NHSTUB(TurnOffDisplay                         ,0xff853180) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff97b6d8) //120
NHSTUB(UnlockAE                               ,0xff833044) //120
NHSTUB(UnlockAF                               ,0xff832d5c) //120
NHSTUB(UnlockMainPower                        ,0xff88538c) //120
NHSTUB(UnsetZoomForMovie                      ,0xff9902c0) //104
NHSTUB(VbattGet                               ,0xff82c3bc) //120
NHSTUB(Write                                  ,0xff8314f8) //120
NHSTUB(WriteSDCard                            ,0xff948040) //108
NHSTUB(_log                                   ,0x003fcce0) //111
NHSTUB(_log10                                 ,0x003fd220) //112
NHSTUB(_pow                                   ,0x003fd398) //121
NHSTUB(_sqrt                                  ,0x003fefbc) //  6
NHSTUB(add_ptp_handler                        ,0xffa19e48) //121
NHSTUB(apex2us                                ,0xff9dd938) //121
NHSTUB(close                                  ,0xff8159a4) //109
NHSTUB(err_init_task                          ,0xff81436c) //111
NHSTUB(exmem_alloc                            ,0xff87b4e4) //101
NHSTUB(exmem_free                             ,0xff87b55c) //101
NHSTUB(free                                   ,0xff812f68) //112
NHSTUB(kbd_p1_f                               ,0xff82edec) //109
NHSTUB(kbd_p1_f_cont                          ,0xff82edf8) //109
NHSTUB(kbd_p2_f                               ,0xff82e5e4) //109
NHSTUB(kbd_read_keys                          ,0xff82ed9c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff856494) //109
NHSTUB(lseek                                  ,0xff8316c0) //120
NHSTUB(malloc                                 ,0xff812f10) //112
NHSTUB(memcmp                                 ,0xff81ae20) //120
NHSTUB(memcpy                                 ,0xff8371fc) //120
NHSTUB(memset                                 ,0xff9dbbcc) //120
NHSTUB(mkdir                                  ,0xff831940) //121
NHSTUB(mktime_ext                             ,0xff8982d8) //  1
NHSTUB(open                                   ,0xff8158f4) //109
NHSTUB(OpenFastDir                            ,0xffa56080) //115
NHSTUB(closedir                               ,0xffa56030) //121
NHSTUB(qsort                                  ,0xff9dbb6c) //  6
NHSTUB(realloc                                ,0xff9dbc48) //115
NHSTUB(reboot_fw_update                       ,0xffa5b5b0) //106
NHSTUB(set_control_event                      ,0xff884e74) //111
NHSTUB(stat                                   ,0xff831708) //109
NHSTUB(strcat                                 ,0xff898958) //  1
NHSTUB(strchr                                 ,0xff812ddc) //  1
NHSTUB(strcmp                                 ,0xff81af1c) //120
NHSTUB(strcpy                                 ,0xff81ae08) //120
NHSTUB(strftime                               ,0xff898324) //113
NHSTUB(strlen                                 ,0xff812e28) //120
NHSTUB(strncmp                                ,0xff812d90) //  1
NHSTUB(strncpy                                ,0xff812d54) //  1
NHSTUB(strrchr                                ,0xff812e00) //  1
NHSTUB(strtol                                 ,0xff8371e8) //101
NHSTUB(strtolx                                ,0xff836fec) //109
   DEF(task_CaptSeq                           ,0xff870db0) //120
   DEF(task_ExpDrv                            ,0xff8afadc) //120
   DEF(task_FileWrite                         ,0xffa54a38) //120
   DEF(task_InitFileModules                   ,0xff88895c) //120
   DEF(task_MovieRecord                       ,0xff95ed68) //120
   DEF(task_PhySw                             ,0xff82e948) //120
NHSTUB(time                                   ,0x003fb794) //  6
NHSTUB(vsprintf                               ,0xff81acb8) //115
NHSTUB(EngDrvRead                             ,0xff82fc2c) //102
