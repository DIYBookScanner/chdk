// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R52 (DRYOS version 2.3, release #0052)
//   Firmware Ver GM1.00A   // Found @ 0xff0c1640, "GM1.00A" @ 0xff0c164d
//   Firmware build timestamp: Nov 28 2012 14:48:51
//   Canon PowerShot ELPH 130 IS

// Values for makefile.inc
//   PLATFORMOSVER = 52
//   PLATFORMID = 12901 (0x3265) // Found @ 0xfff40040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00242f28
//   KEYSYS = d4d                // Found @ 0xffff1d2c
//   NEED_ENCODED_DISKBOOT = 10   // Found @ 0xffff1d3c

// Note, ROM copied to RAM :- from 0xff6982d4, to 0x00671000, len 43703 words.
//   ARAM_HEAP_START = 0x5ce000  // Found @ 0xff201a10
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff2019d4

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff033b68) //  1 90%
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff034678
// ERROR: RefreshPhysicalScreen is not found.              //--- ---    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff36a698 -> ff61c088
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0003a950) // Found @0xff0313b4
DEF(physw_run                               ,0x00001dec) // Found @0xff030f08
DEF(physw_sleep_delay                       ,0x00001df4) // Found @0xff030f08
DEF(levent_table                            ,0xff55ffa0) // Found @0xff55ffa0
DEF(FlashParamsTable                        ,0xff61c2bc) // Found @0xff61c2bc
DEF(movie_status                            ,0x00007c6c) // Found @0xff1f3da0
DEF(video_compression_rate                  ,0x00007c9c) // Found @0xff1f4504
DEF(full_screen_refresh                     ,0x000087a0) // Found @0xff20f624
DEF(canon_menu_active                       ,0x00003fa0) // Found @0xff0ca2ac
DEF(canon_shoot_menu_active                 ,0x0000a385) // Found @0xff27c790
DEF(playrec_mode                            ,0x000039c8) // Found @0xff0b5fec
DEF(zoom_status                             ,0x0000bbac) // Found @0xff2eee9c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 101 entries in the table - set NUM_FL to 101
DEF(focus_len_table                         ,0xfff4a3e0) // Found @0xfff4a3e0
DEF(zoom_busy                               ,0x00007b20) // Found @0xff1eea84
DEF(focus_busy                              ,0x00007990) // Found @0xff1e9a80
DEF(recreview_hold                          ,0x00002d34) // Found @0xff088464
// Palette colour tables  found @ 0xff566bec
DEF(active_palette_buffer                   ,0x000087a8) // Found @0xff20f5a8
DEF(palette_buffer_ptr                      ,0x000087ac) // Found @0xff20f938
// Offset from start of palette_buffer to color data = 4 (Found @0xff38afe0)
// Camera appears to have only 1 RAW buffer @ 0x42365c30 (Found @0xff413f98)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x406b1000; }             // Found @0xff08b550
//void *vid_get_viewport_fb()      { return (void*)0x40806b80; }             // Found @0xff412680
DEF(viewport_fb_d                           ,0x00003728) // Found 0x36d4 (@0xff0a7858) + 0x54 (@0xff0a7890)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x36d4+0x54)); } // Found @0xff0a7858 & 0xff0a7890
DEF(jpeg_count_str                          ,0x00164144) // Found @0xff269ea4
//char *camera_jpeg_count_str()    { return (char*)0x00164144; }             // Found @0xff269ea4
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xff413ff0
//int get_flash_params_count(void) { return 0x91; }                          // Found @0xff2075ac

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x02000000 // Found @0xff4fbaf0, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xff4fbb00, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 2, KEY_POWER           ,0x00000001 }, // Found @0xff4fba60, levent 0x100
//    { 2, KEY_PLAYBACK        ,0x00000002 }, // Found @0xff4fba68, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x0000000c }, // Found @0xff4fba78, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000008 }, // Found @0xff4fba78, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000004 }, // Found @0xff4fba70, levent 0x00
//    { 2, KEY_ZOOM_OUT        ,0x00000010 }, // Found @0xff4fba80, levent 0x03
//    { 2, KEY_UP              ,0x00000040 }, // Found @0xff4fba88, levent 0x04
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xff4fba90, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000100 }, // Found @0xff4fba98, levent 0x07
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xff4fbaa0, levent 0x09
//    { 2, KEY_SET             ,0x00000400 }, // Found @0xff4fbaa8, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00001000 }, // Found @0xff4fbab0, levent 0x0a
//    { 2, KEY_ZOOM_IN         ,0x00004000 }, // Found @0xff4fbac0, levent 0x02
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff1be31c
//#define CAM_RAW_ROWS      3504 // Found @0xff1be328
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff038dd4

// Misc stuff
DEF(ctypes, 0xff4f9478)

// For capt_seq.c
DEF(_nrflag,0xb334) // Found @ ff2a4c74 (0xb334) & ff2a4cb0 (+0x00)
//static long *nrflag = (long*)(0xb334+0x00);  // Found @ ff2a4c74 & ff2a4cb0
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff038d8c) //112
NHSTUB(Close                                  ,0xff0341dc) //120
NHSTUB(CreateTask                             ,0x006768b0) //120
NHSTUB(DebugAssert                            ,0x00676c28) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff033bdc) //116
NHSTUB(DoAELock                               ,0xff035d10) //120
NHSTUB(DoAFLock                               ,0xff035a30) //120
NHSTUB(EnterToCompensationEVF                 ,0xff035c78) //104
NHSTUB(ExecuteEventProcedure                  ,0xff0be6a0) //104
NHSTUB(ExitFromCompensationEVF                ,0xff035cbc) //104
NHSTUB(ExitTask                               ,0x00676b40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff06a1a0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff06a308) //104
NHSTUB(Fclose_Fut                             ,0xff033c74) //120
NHSTUB(Feof_Fut                               ,0xff033e60) //  1
NHSTUB(Fflush_Fut                             ,0xff033e9c) //  1
NHSTUB(Fgets_Fut                              ,0xff033dc8) //  6
NHSTUB(Fopen_Fut                              ,0xff033c34) //120
NHSTUB(Fread_Fut                              ,0xff033d20) //120
NHSTUB(FreeUncacheableMemory                  ,0xff038dcc) //112
NHSTUB(Fseek_Fut                              ,0xff033e14) //120
NHSTUB(Fwrite_Fut                             ,0xff033d74) //120
NHSTUB(GetBatteryTemperature                  ,0xff0934bc) //102
NHSTUB(GetCCDTemperature                      ,0xff093448) //102
NHSTUB(GetCurrentAvValue                      ,0xff1eb93c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff0a578c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff0a5f6c) //  6
NHSTUB(GetDrive_TotalClusters                 ,0xff0a5f44) //  6
NHSTUB(GetFocusLensSubjectDistance            ,0xff1eabb0) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1eaf44) //  3
NHSTUB(GetImageFolder                         ,0xff1c5a04) //122
NHSTUB(GetKbdState                            ,0xff0907a0) //109
NHSTUB(GetMemInfo                             ,0xff00506c) //115
NHSTUB(GetOpticalTemperature                  ,0xff093530) //120
NHSTUB(GetParameterData                       ,0xff20756c) //101
NHSTUB(GetPropertyCase                        ,0xff0c2a60) //101
NHSTUB(GetSystemTime                          ,0xff3661c8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff0766f4) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff076700) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1eef00) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff352778) //102
NHSTUB(GiveSemaphore                          ,0x00677904) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff136238) //102
NHSTUB(LEDDrive                               ,0xff1f5be4) //120
NHSTUB(LocalTime                              ,0x0067f6b0) //115
NHSTUB(LockMainPower                          ,0xff0c4ed8) //120
NHSTUB(MakeSDCardBootable                     ,0xff0a63f0) //105
NHSTUB(MoveFocusLensToDistance                ,0xff40e1e8) //102
NHSTUB(MoveIrisWithAv                         ,0xff36095c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff361098) //120
NHSTUB(Open                                   ,0xff034114) //120
NHSTUB(PB2Rec                                 ,0xff081764) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff1f6ce8) //102
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff1f6cb8) //102
NHSTUB(PT_PlaySound                           ,0xff0d54c8) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff0c45c8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff0c4614) //120
NHSTUB(PutInNdFilter                          ,0xff360e70) //102
NHSTUB(PutOutNdFilter                         ,0xff360e94) //102
NHSTUB(Read                                   ,0xff005b28) //120
NHSTUB(ReadFastDir                            ,0xff33d874) //115
NHSTUB(Rec2PB                                 ,0xff0817a4) //104
NHSTUB(RenameFile_Fut                         ,0xff033ad4) //116
NHSTUB(Restart                                ,0xff0382e8) //106
NHSTUB(ScreenLock                             ,0xff0c9d9c) //117
NHSTUB(ScreenUnlock                           ,0xff0c9df0) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff411558) //102
NHSTUB(SetAutoShutdownTime                    ,0xff0c4f4c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0d2ce8) //120
NHSTUB(SetFileAttributes                      ,0xff0345e0) //  6
NHSTUB(SetFileTimeStamp                       ,0xff034568) //  6
NHSTUB(SetLogicalEventActive                  ,0xff0c4c50) //101
NHSTUB(SetParameterData                       ,0xff2074d8) //101
NHSTUB(SetPropertyCase                        ,0xff0c28d0) //101
NHSTUB(SetScriptMode                          ,0xff0c4ca0) //120
NHSTUB(SleepTask                              ,0x00677bb0) //120
NHSTUB(TakeSemaphore                          ,0x00677834) //120
NHSTUB(TurnOffBackLight                       ,0xff0d4d94) //104
NHSTUB(TurnOnBackLight                        ,0xff0d4d7c) //104
NHSTUB(TurnOnDisplay                          ,0xff08b958) //120
NHSTUB(TurnOffDisplay                         ,0xff08b968) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff2234b4) //120
NHSTUB(UnlockAE                               ,0xff035d34) //120
NHSTUB(UnlockAF                               ,0xff035a60) //120
NHSTUB(UnlockMainPower                        ,0xff0c4e2c) //120
NHSTUB(VbattGet                               ,0xff03014c) //120
NHSTUB(Write                                  ,0xff034230) //120
NHSTUB(WriteSDCard                            ,0xff1dbe64) //108
NHSTUB(_log                                   ,0x00697808) //111
NHSTUB(_log10                                 ,0x00697d48) //112
NHSTUB(_pow                                   ,0x00697ec0) //121
NHSTUB(_sqrt                                  ,0x00699c5c) //  6
NHSTUB(add_ptp_handler                        ,0xff16a4a4) //121
NHSTUB(apex2us                                ,0xff29de84) //121
NHSTUB(close                                  ,0xff005984) //109
NHSTUB(err_init_task                          ,0xff004320) //111
NHSTUB(exmem_alloc                            ,0xff0bd068) //101
NHSTUB(exmem_free                             ,0xff0bd0e0) //101
NHSTUB(free                                   ,0xff002ef0) //112
NHSTUB(kbd_p1_f                               ,0xff031404) //109
NHSTUB(kbd_p1_f_cont                          ,0xff031410) //109
NHSTUB(kbd_p2_f                               ,0xff030ba0) //109
NHSTUB(kbd_read_keys                          ,0xff0313b4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff0901fc) //109
NHSTUB(lseek                                  ,0xff0343f8) //120
NHSTUB(malloc                                 ,0xff002e98) //112
NHSTUB(memcmp                                 ,0xff00ad4c) //120
NHSTUB(memcpy                                 ,0xff039818) //120
NHSTUB(memset                                 ,0xff0d8eb8) //120
NHSTUB(mkdir                                  ,0xff034678) //121
NHSTUB(mktime_ext                             ,0xff0d8360) //  1
NHSTUB(open                                   ,0xff0058d4) //109
NHSTUB(OpenFastDir                            ,0xff33d720) //115
NHSTUB(closedir                               ,0xff33d6d0) //121
NHSTUB(qsort                                  ,0xff282ec4) //  6
NHSTUB(rand                                   ,0xff0d8dbc) //121
NHSTUB(realloc                                ,0xff282f24) //115
NHSTUB(reboot_fw_update                       ,0xff365834) //106
NHSTUB(set_control_event                      ,0xff0c4910) //111
NHSTUB(srand                                  ,0xff0d8db0) //122
NHSTUB(stat                                   ,0xff034440) //109
NHSTUB(strcat                                 ,0xff0d8dec) //  1
NHSTUB(strchr                                 ,0xff002d64) //  1
NHSTUB(strcmp                                 ,0xff00ae48) //120
NHSTUB(strcpy                                 ,0xff00ad34) //120
NHSTUB(strftime                               ,0xff0d83ac) //113
NHSTUB(strlen                                 ,0xff002db0) //120
NHSTUB(strncmp                                ,0xff002d18) //  1
NHSTUB(strncpy                                ,0xff002cdc) //  1
NHSTUB(strrchr                                ,0xff002d88) //  1
NHSTUB(strtol                                 ,0xff039804) //101
NHSTUB(strtolx                                ,0xff039608) //109
   DEF(task_CaptSeq                           ,0xff0b06bc) //120
   DEF(task_ExpDrv                            ,0xff11d558) //120
   DEF(task_FileWrite                         ,0xff3399b0) //120
   DEF(task_InitFileModules                   ,0xff0820b8) //120
   DEF(task_MovieRecord                       ,0xff1f49d8) //120
   DEF(task_PhySw                             ,0xff030f04) //120
   DEF(hook_CreateTask                        ,0x006768b0) //105
NHSTUB(time                                   ,0x0067fb58) //  6
NHSTUB(vsprintf                               ,0xff00abe4) //115
NHSTUB(EngDrvRead                             ,0xff0322e4) //102
