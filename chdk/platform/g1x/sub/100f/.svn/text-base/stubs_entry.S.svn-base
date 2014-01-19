// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R49 (DRYOS version 2.3, release #0049)
//   Firmware Ver GM1.00F   // Found @ 0xff08ea04, "GM1.00F" @ 0xff08ea11
//   Firmware build timestamp: Jan 19 2012 17:44:58
//   Canon PowerShot G1 X

// Values for makefile.inc
//   PLATFORMOSVER = 49
//   PLATFORMID = 12851 (0x3233) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x0018c774
//   KEYSYS = d4c                // Found @ 0xffff3bb0
//   NEED_ENCODED_DISKBOOT = 7   // Found @ 0xffff3bc0
//   ARAM_HEAP_START = 0x5de000  // Found @ 0xff1db828
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1db7e8

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff388834 -> ff639cc4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00038bfc) // Found @0xff023c4c
DEF(physw_run                               ,0x00001bf4) // Found @0xff0237dc
DEF(physw_sleep_delay                       ,0x00001bfc) // Found @0xff0237dc
DEF(levent_table                            ,0xff59dcd4) // Found @0xff59dcd4
DEF(FlashParamsTable                        ,0xff639f28) // Found @0xff639f28
DEF(movie_status                            ,0x00009ddc) // Found @0xff1c8b34
DEF(video_compression_rate                  ,0x00009e1c) // Found @0xff1c9fdc
DEF(full_screen_refresh                     ,0x0000cd94) // Found @0xff29aeac
DEF(canon_menu_active                       ,0x00004464) // Found @0xff090524
DEF(canon_shoot_menu_active                 ,0x0000b4e9) // Found @0xff22c6d4
DEF(playrec_mode                            ,0x00004184) // Found @0xff081de0
DEF(zoom_status                             ,0x0000b010) // Found @0xff213710
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 101 entries in the table - set NUM_FL to 101
DEF(focus_len_table                         ,0xfff4a6c8) // Found @0xfff4a6c8
DEF(zoom_busy                               ,0x00009c94) // Found @0xff1c382c
DEF(focus_busy                              ,0x00009ae4) // Found @0xff1bd34c
DEF(recreview_hold                          ,0x00005144) // Found @0xff0a3164
// Palette colour tables  found @ 0xff5ba798
DEF(palette_control                         ,0x0000cd94) // Found @0xff29ae28
DEF(active_palette_buffer                   ,0x0000cd9c) // Found @0xff29ae2c
DEF(palette_buffer_ptr                      ,0x0000cda0) // Found @0xff29b2e4
DEF(palette_buffer                          ,0x000cc858) // Found @0xff29b2f4
// Offset from start of palette_buffer to color data = 4 (Found @0xff3caa9c)
DEF(bitmap_buffer                           ,0x0000cdd8) // Found @0xff29eb38
DEF(active_bitmap_buffer                    ,0x0000cdd0) // Found @0xff29eb3c
DEF(viewport_buffers                        ,0xff464664) // Found @0xff045214
DEF(active_viewport_buffer                  ,0x00002150) // Found @0xff044ee8
// Camera has 2 RAW buffers @ 0x44000000 & 0x4a6ba6a0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff476254) // Found @0xff476254
DEF(active_raw_buffer                       ,0x000040d4) // Found @0xff07da9c

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40685000; }             // Found @0xff0501b8
//void *vid_get_viewport_fb()      { return (void*)0x407dab80; }             // Found @0xff407a0c
DEF(viewport_fb_d                           ,0x00003de0) // Found 0x3d88 (@0xff06e504) + 0x58 (@0xff06e53c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3d88+0x58)); } // Found @0xff06e504 & 0xff06e53c
DEF(jpeg_count_str                          ,0x000cc108) // Found @0xff28c994
//char *camera_jpeg_count_str()    { return (char*)0x000cc108; }             // Found @0xff28c994
//long hook_raw_size()             { return 0x01941be8; }                    // Found @0xff40a828
//int get_flash_params_count(void) { return 0x9f; }                          // Found @0xff206724

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00000002 // Found @0xff464d1c, levent 0x20a
//#define SD_READONLY_IDX     1
//#define USB_MASK            0x10000000 // Found @0xff464d94, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SET             ,0x00000800 }, // Found @0xff464ca4, levent 0x08
//    { 0, KEY_RIGHT           ,0x00001000 }, // Found @0xff464cac, levent 0x07
//    { 0, KEY_DOWN            ,0x00002000 }, // Found @0xff464cb4, levent 0x05
//    { 0, KEY_MENU            ,0x00004000 }, // Found @0xff464cbc, levent 0x09
//    { 0, KEY_LEFT            ,0x00008000 }, // Found @0xff464cc4, levent 0x06
//    { 0, KEY_UP              ,0x00040000 }, // Found @0xff464cdc, levent 0x04
//    { 0, KEY_VIDEO           ,0x00080000 }, // Found @0xff464ce4, levent 0x19
//    { 0, KEY_ZOOM_IN         ,0x00100000 }, // Found @0xff464cec, levent 0x02
//    { 0, KEY_ZOOM_OUT        ,0x00200000 }, // Found @0xff464cf4, levent 0x03
//    { 2, KEY_POWER           ,0x00000800 }, // Found @0xff464d34, levent 0x100
//    { 2, KEY_PLAYBACK        ,0x00008000 }, // Found @0xff464d54, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x000c0000 }, // Found @0xff464d64, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00080000 }, // Found @0xff464d64, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00040000 }, // Found @0xff464d5c, levent 0x00
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4496 // Found @0xff190c98
//#define CAM_RAW_ROWS      3366 // Found @0xff190ca4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02ac74

// Misc stuff
DEF(ctypes, 0xff4639ce)

// For capt_seq.c
DEF(_nrflag,0xceb0) // Found @ ff2a7988 (0xceac) & ff2a79c4 (+0x04)
//static long *nrflag = (long*)(0xceac+0x04);  // Found @ ff2a7988 & ff2a79c4
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff02ac2c) //112
NHSTUB(Close                                  ,0xff026458) //120
NHSTUB(CreateTask                             ,0xff00eaf0) //120
NHSTUB(DebugAssert                            ,0xff00edc8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff025e54) //116
NHSTUB(DeleteFile_Fut                         ,0xff025d70) //112
NHSTUB(DoAELock                               ,0xff028548) //120
NHSTUB(DoAFLock                               ,0xff0280d0) //120
NHSTUB(EnterToCompensationEVF                 ,0xff0284a4) //104
NHSTUB(ExecuteEventProcedure                  ,0xff08b9c0) //104
NHSTUB(ExitFromCompensationEVF                ,0xff0284e8) //104
NHSTUB(ExitTask                               ,0xff00ed80) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff036ba4) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff036c84) //104
NHSTUB(Fclose_Fut                             ,0xff025eec) //120
NHSTUB(Feof_Fut                               ,0xff0260d8) //  1
NHSTUB(Fflush_Fut                             ,0xff026114) //  1
NHSTUB(Fgets_Fut                              ,0xff026040) //  6
NHSTUB(Fopen_Fut                              ,0xff025eac) //120
NHSTUB(Fread_Fut                              ,0xff025f98) //120
NHSTUB(FreeUncacheableMemory                  ,0xff02ac6c) //112
NHSTUB(Fseek_Fut                              ,0xff02608c) //120
NHSTUB(Fwrite_Fut                             ,0xff025fec) //120
NHSTUB(GetBatteryTemperature                  ,0xff05de30) //102
NHSTUB(GetCCDTemperature                      ,0xff05ddbc) //102
NHSTUB(GetCurrentAvValue                      ,0xff1c0284) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff06cbb8) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff06cc10) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff06cbe8) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1be0c8) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1be518) //  3
NHSTUB(GetImageFolder                         ,0xff19a434) //122
NHSTUB(GetKbdState                            ,0xff05726c) //109
NHSTUB(GetMemInfo                             ,0xff00a2b8) //115
NHSTUB(GetOpticalTemperature                  ,0xff05dea4) //120
NHSTUB(GetParameterData                       ,0xff2066e4) //101
NHSTUB(GetPropertyCase                        ,0xff08fa60) //102
NHSTUB(GetSystemTime                          ,0xff3747c0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff047814) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff047820) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1c3ca4) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff360cf4) //102
NHSTUB(GiveSemaphore                          ,0xff02a394) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0f2418) //102
NHSTUB(LEDDrive                               ,0xff056488) //120
NHSTUB(LocalTime                              ,0xff089384) //115
NHSTUB(LockMainPower                          ,0xff096d28) //120
NHSTUB(MakeDirectory_Fut                      ,0xff025de4) //116
NHSTUB(MakeSDCardBootable                     ,0xff06ce48) //105
NHSTUB(MoveFocusLensToDistance                ,0xff403c44) //102
NHSTUB(MoveIrisWithAv                         ,0xff370f10) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff3718a0) //120
NHSTUB(Open                                   ,0xff026390) //120
NHSTUB(PB2Rec                                 ,0xff09a0d4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff0780fc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff0780d4) //120
NHSTUB(PT_PlaySound                           ,0xff083df4) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff094594) //120
NHSTUB(PostLogicalEventToUI                   ,0xff0945e0) //120
NHSTUB(PutInNdFilter                          ,0xff371678) //102
NHSTUB(PutOutNdFilter                         ,0xff37169c) //102
NHSTUB(Read                                   ,0xff00ad74) //120
NHSTUB(ReadFastDir                            ,0xff34c570) //115
NHSTUB(Rec2PB                                 ,0xff09a114) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0b3058) //104
NHSTUB(RenameFile_Fut                         ,0xff025cdc) //116
NHSTUB(Restart                                ,0xff02c444) //106
NHSTUB(ScreenLock                             ,0xff0b4284) //117
NHSTUB(ScreenUnlock                           ,0xff0b42e8) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff406b84) //102
NHSTUB(SetAutoShutdownTime                    ,0xff096d9c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0a0250) //120
NHSTUB(SetFileAttributes                      ,0xff02685c) //  6
NHSTUB(SetFileTimeStamp                       ,0xff0267e4) //  6
NHSTUB(SetLogicalEventActive                  ,0xff096a74) //101
NHSTUB(SetParameterData                       ,0xff2065c0) //101
NHSTUB(SetPropertyCase                        ,0xff08f8d8) //102
NHSTUB(SetScriptMode                          ,0xff096ac4) //120
NHSTUB(SleepTask                              ,0xff02a640) //120
NHSTUB(TakeSemaphore                          ,0xff02a2c4) //120
NHSTUB(TurnOffBackLight                       ,0xff0aab48) //104
NHSTUB(TurnOnBackLight                        ,0xff0aab30) //104
NHSTUB(TurnOnDisplay                          ,0xff050600) //120
NHSTUB(TurnOffDisplay                         ,0xff050610) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1f08d8) //120
NHSTUB(UnlockAE                               ,0xff02856c) //120
NHSTUB(UnlockAF                               ,0xff028108) //120
NHSTUB(UnlockMainPower                        ,0xff096c7c) //120
NHSTUB(VbattGet                               ,0xff022338) //120
NHSTUB(Write                                  ,0xff0264ac) //120
NHSTUB(WriteSDCard                            ,0xff1aed6c) //108
NHSTUB(_log                                   ,0xff4601b8) //111
NHSTUB(_log10                                 ,0xff4606f8) //112
NHSTUB(_pow                                   ,0xff460870) //121
NHSTUB(_sqrt                                  ,0xff4627d0) //  6
NHSTUB(add_ptp_handler                        ,0xff2eb6bc) //121
NHSTUB(apex2us                                ,0xff2a1304) //121
NHSTUB(close                                  ,0xff00abd0) //109
NHSTUB(err_init_task                          ,0xff00602c) //111
NHSTUB(exmem_alloc                            ,0xff08a344) //101
NHSTUB(exmem_free                             ,0xff08a3bc) //101
NHSTUB(free                                   ,0xff004264) //112
NHSTUB(kbd_p1_f                               ,0xff023c9c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff023ca8) //109
NHSTUB(kbd_p2_f                               ,0xff023474) //109
NHSTUB(kbd_read_keys                          ,0xff023c4c) //109
NHSTUB(kbd_read_keys_r2                       ,0xff056960) //109
NHSTUB(lseek                                  ,0xff026674) //120
NHSTUB(malloc                                 ,0xff00420c) //112
NHSTUB(memcmp                                 ,0xff010a1c) //120
NHSTUB(memcpy                                 ,0xff0304a4) //120
NHSTUB(memset                                 ,0xff29f328) //120
NHSTUB(mkdir                                  ,0xff0268f4) //109
NHSTUB(mktime_ext                             ,0xff0b51a0) //  1
NHSTUB(open                                   ,0xff00ab20) //109
NHSTUB(OpenFastDir                            ,0xff34c41c) //115
NHSTUB(closedir                               ,0xff34c3cc) //121
NHSTUB(qsort                                  ,0xff3cb660) //  6
NHSTUB(rand                                   ,0xff29f464) //121
NHSTUB(realloc                                ,0xff29f3a4) //115
NHSTUB(reboot_fw_update                       ,0xff351cc4) //106
NHSTUB(set_control_event                      ,0xff096668) //111
NHSTUB(srand                                  ,0xff29f458) //122
NHSTUB(stat                                   ,0xff0266bc) //109
NHSTUB(strcat                                 ,0xff0b4958) //  1
NHSTUB(strchr                                 ,0xff0040d8) //  1
NHSTUB(strcmp                                 ,0xff0109d8) //120
NHSTUB(strcpy                                 ,0xff0109c0) //120
NHSTUB(strftime                               ,0xff0b4ba0) //113
NHSTUB(strlen                                 ,0xff004124) //120
NHSTUB(strncmp                                ,0xff00408c) //  1
NHSTUB(strncpy                                ,0xff004050) //  1
NHSTUB(strrchr                                ,0xff0040fc) //  1
NHSTUB(strtol                                 ,0xff0307a4) //101
NHSTUB(strtolx                                ,0xff0305a8) //109
   DEF(task_CaptSeq                           ,0xff07b330) //120
   DEF(task_ExpDrv                            ,0xff0cd9f0) //120
   DEF(task_FileWrite                         ,0xff34a364) //120
   DEF(task_InitFileModules                   ,0xff09a978) //120
   DEF(task_MovieRecord                       ,0xff1ca86c) //120
   DEF(task_PhySw                             ,0xff0237d8) //120
   DEF(task_RotaryEncoder                     ,0xff0575cc) //120
NHSTUB(time                                   ,0xff089960) //109
NHSTUB(vsprintf                               ,0xff010980) //115
NHSTUB(EngDrvRead                             ,0xff024ac8) //102
