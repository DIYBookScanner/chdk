// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R50 (DRYOS version 2.3, release #0050)
//   Firmware Ver GM1.00B   // Found @ 0xff07f440, "GM1.00B" @ 0xff07f44d
//   Firmware build timestamp: Jan  6 2012 17:07:27
//   Canon PowerShot SX260 HS

// Values for makefile.inc
//   PLATFORMOSVER = 50
//   PLATFORMID = 12868 (0x3244) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x00193a24
//   KEYSYS = d4c                // Found @ 0xffff3ce0
//   NEED_ENCODED_DISKBOOT = 8   // Found @ 0xffff3cf0

// Note, ROM copied to RAM :- from 0xff680924, to 0x00685000, len 16659 words.
//   ARAM_HEAP_START = 0x5ce000  // Found @ 0xff1c9028
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1c8fec

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(DeleteFile_Fut                         ,0xff02163c) //  1 90%
//NHSTUB(LEDDrive                             ,0xff1b9834) //120        *** != 0xff04d06c
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff02214c

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff365dd4 -> ff63fe78
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000388e4) // Found @0xff01f5ac
DEF(physw_run                               ,0x00001c60) // Found @0xff01f158
DEF(physw_sleep_delay                       ,0x00001c68) // Found @0xff01f158
DEF(levent_table                            ,0xff587558) // Found @0xff587558
DEF(FlashParamsTable                        ,0xff6400f4) // Found @0xff6400f4
DEF(movie_status                            ,0x0000ab7c) // Found @0xff1b60c0
DEF(video_compression_rate                  ,0x0000abbc) // Found @0xff1b7ab4
DEF(full_screen_refresh                     ,0x0000dbe8) // Found @0xff27c474
DEF(canon_menu_active                       ,0x000034d4) // Found @0xff0813dc
DEF(canon_shoot_menu_active                 ,0x0000c2f9) // Found @0xff2133e0
DEF(playrec_mode                            ,0x00003224) // Found @0xff074ec0
DEF(zoom_status                             ,0x0001150c) // Found @0xff368204
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 101 entries in the table - set NUM_FL to 101
DEF(focus_len_table                         ,0xfff4bcf0) // Found @0xfff4bcf0
DEF(zoom_busy                               ,0x0000aa14) // Found @0xff1b0fac
DEF(focus_busy                              ,0x0000a870) // Found @0xff1aa514
DEF(recreview_hold                          ,0x00003ff0) // Found @0xff094c20
// Palette colour tables  found @ 0xff5a5b2c
DEF(palette_control                         ,0x0000dbe8) // Found @0xff27c3f0
DEF(active_palette_buffer                   ,0x0000dbf0) // Found @0xff27c3f4
DEF(palette_buffer_ptr                      ,0x0000dbf4) // Found @0xff27c8ac
DEF(palette_buffer                          ,0x000ddb24) // Found @0xff27c8bc
// Offset from start of palette_buffer to color data = 4 (Found @0xff3acaa0)
DEF(bitmap_buffer                           ,0x0000dc24) // Found @0xff2810fc
DEF(active_bitmap_buffer                    ,0x0000dc1c) // Found @0xff281100
DEF(viewport_buffers                        ,0xff441054) // Found @0xff03d9bc
DEF(active_viewport_buffer                  ,0x000021b0) // Found @0xff03d658
// Camera has 2 RAW buffers @ 0x44000000 & 0x4adb54a0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff45507c) // Found @0xff45507c
DEF(active_raw_buffer                       ,0x00003194) // Found @0xff0715e0

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x406c5000; }             // Found @0xff047848
//void *vid_get_viewport_fb()      { return (void*)0x4081ab80; }             // Found @0xff3e3694
DEF(viewport_fb_d                           ,0x00002f14) // Found 0x2ec0 (@0xff062d0c) + 0x54 (@0xff062d44)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2ec0+0x54)); } // Found @0xff062d0c & 0xff062d44
DEF(jpeg_count_str                          ,0x000dd3b4) // Found @0xff26fe14
//char *camera_jpeg_count_str()    { return (char*)0x000dd3b4; }             // Found @0xff26fe14
//long hook_raw_size()             { return 0x01247a60; }                    // Found @0xff3e64ac
//int get_flash_params_count(void) { return 0xa6; }                          // Found @0xff1f3fb4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00080000 // Found @0xff441628, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xff441660, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00400000 }, // Found @0xff441570, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x00800000 }, // Found @0xff441578, levent 0x101
//    { 1, KEY_SHOOT_FULL      ,0x03000000 }, // Found @0xff441588, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x02000000 }, // Found @0xff441588, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x01000000 }, // Found @0xff441580, levent 0x00
//    { 2, KEY_VIDEO           ,0x00000020 }, // Found @0xff4415d8, levent 0x1a
//    { 2, KEY_MENU            ,0x00000040 }, // Found @0xff4415e0, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000080 }, // Found @0xff4415e8, levent 0x0a
//    { 2, KEY_UP              ,0x00000100 }, // Found @0xff4415f0, levent 0x04
//    { 2, KEY_DOWN            ,0x00000200 }, // Found @0xff4415f8, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000400 }, // Found @0xff441600, levent 0x07
//    { 2, KEY_LEFT            ,0x00000800 }, // Found @0xff441608, levent 0x06
//    { 2, KEY_SET             ,0x00001000 }, // Found @0xff441610, levent 0x08
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4176 // Found @0xff17db40
//#define CAM_RAW_ROWS      3060 // Found @0xff17db4c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff025754

// Misc stuff
DEF(ctypes, 0xff440390)

// For capt_seq.c
DEF(_nrflag,0xdd10) // Found @ ff28a06c (0xdd10) & ff28a0a8 (+0x00)
//static long *nrflag = (long*)(0xdd10+0x00);  // Found @ ff28a06c & ff28a0a8
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff02570c) //112
NHSTUB(Close                                  ,0xff021cb0) //120
NHSTUB(CreateTask                             ,0x0068ab00) //120
NHSTUB(DebugAssert                            ,0x0068afd8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff0216b0) //116
NHSTUB(DoAELock                               ,0xff023cbc) //120
NHSTUB(DoAFLock                               ,0xff02390c) //120
NHSTUB(EnterToCompensationEVF                 ,0xff023bb0) //104
NHSTUB(ExecuteEventProcedure                  ,0xff07c400) //104
NHSTUB(ExitFromCompensationEVF                ,0xff023bf4) //104
NHSTUB(ExitTask                               ,0x0068ad90) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff02ee68) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff02efb8) //104
NHSTUB(Fclose_Fut                             ,0xff021748) //120
NHSTUB(Feof_Fut                               ,0xff021934) //  1
NHSTUB(Fflush_Fut                             ,0xff021970) //  1
NHSTUB(Fgets_Fut                              ,0xff02189c) //  6
NHSTUB(Fopen_Fut                              ,0xff021708) //120
NHSTUB(Fread_Fut                              ,0xff0217f4) //120
NHSTUB(FreeUncacheableMemory                  ,0xff02574c) //112
NHSTUB(Fseek_Fut                              ,0xff0218e8) //120
NHSTUB(Fwrite_Fut                             ,0xff021848) //120
NHSTUB(GetBatteryTemperature                  ,0xff0523ac) //102
NHSTUB(GetCCDTemperature                      ,0xff052338) //102
NHSTUB(GetCurrentAvValue                      ,0xff1ad380) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff06093c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff060994) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff06096c) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1ab2d8) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1ab728) //  3
NHSTUB(GetImageFolder                         ,0xff187254) //122
NHSTUB(GetKbdState                            ,0xff04dce8) //109
NHSTUB(GetMemInfo                             ,0xff0052e0) //115
NHSTUB(GetOpticalTemperature                  ,0xff052420) //120
NHSTUB(GetParameterData                       ,0xff1f3f74) //101
NHSTUB(GetPropertyCase                        ,0xff080520) //102
NHSTUB(GetSystemTime                          ,0xff35838c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff03fe34) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff03fe40) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1b1424) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff345798) //102
NHSTUB(GiveSemaphore                          ,0x0068aa60) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0de27c) //102
NHSTUB(LocalTime                              ,0x0068f2f4) //115
NHSTUB(LockMainPower                          ,0xff087fe8) //120
NHSTUB(MakeSDCardBootable                     ,0xff060bbc) //105
NHSTUB(MoveFocusLensToDistance                ,0xff3df6e4) //102
NHSTUB(MoveIrisWithAv                         ,0xff354be8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff355424) //120
NHSTUB(Open                                   ,0xff021be8) //120
NHSTUB(PB2Rec                                 ,0xff08b370) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff06a190) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff06a168) //120
NHSTUB(PT_PlaySound                           ,0xff076e60) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff08598c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff0859d8) //120
NHSTUB(PutInNdFilter                          ,0xff3dd22c) //102
NHSTUB(PutOutNdFilter                         ,0xff3dd264) //102
NHSTUB(Read                                   ,0xff005d9c) //120
NHSTUB(ReadFastDir                            ,0xff32ff40) //115
NHSTUB(Rec2PB                                 ,0xff08b3b0) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0a180c) //104
NHSTUB(RenameFile_Fut                         ,0xff0215a8) //116
NHSTUB(Restart                                ,0xff026f7c) //106
NHSTUB(ScreenLock                             ,0xff0a27ec) //117
NHSTUB(ScreenUnlock                           ,0xff0a2850) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff3e280c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff08805c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff08f718) //120
NHSTUB(SetFileAttributes                      ,0xff0220b4) //  6
NHSTUB(SetFileTimeStamp                       ,0xff02203c) //  6
NHSTUB(SetLogicalEventActive                  ,0xff087d24) //101
NHSTUB(SetParameterData                       ,0xff1f3ee4) //101
NHSTUB(SetPropertyCase                        ,0xff080380) //102
NHSTUB(SetScriptMode                          ,0xff087dc0) //120
NHSTUB(SleepTask                              ,0x0068c2e8) //120
NHSTUB(TakeSemaphore                          ,0x0068a990) //120
NHSTUB(TurnOffBackLight                       ,0xff09953c) //104
NHSTUB(TurnOnBackLight                        ,0xff099524) //104
NHSTUB(TurnOnDisplay                          ,0xff047c5c) //120
NHSTUB(TurnOffDisplay                         ,0xff047c6c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1d7914) //120
NHSTUB(UnlockAE                               ,0xff023ce0) //120
NHSTUB(UnlockAF                               ,0xff023944) //120
NHSTUB(UnlockMainPower                        ,0xff087f3c) //120
NHSTUB(VbattGet                               ,0xff01d0f0) //120
NHSTUB(Write                                  ,0xff021d04) //120
NHSTUB(WriteSDCard                            ,0xff19da20) //108
NHSTUB(_log                                   ,0x006915c8) //111
NHSTUB(_log10                                 ,0x00691b08) //112
NHSTUB(_pow                                   ,0x00691c80) //121
NHSTUB(_sqrt                                  ,0x00693c8c) //  6
NHSTUB(add_ptp_handler                        ,0xff2c8184) //121
NHSTUB(apex2us                                ,0xff283e48) //121
NHSTUB(close                                  ,0xff005bf8) //109
NHSTUB(err_init_task                          ,0xff004388) //111
NHSTUB(exmem_alloc                            ,0xff07add4) //101
NHSTUB(exmem_free                             ,0xff07ae4c) //101
NHSTUB(free                                   ,0xff002f84) //112
NHSTUB(kbd_p1_f                               ,0xff01f5fc) //109
NHSTUB(kbd_p1_f_cont                          ,0xff01f608) //109
NHSTUB(kbd_p2_f                               ,0xff01edf0) //109
NHSTUB(kbd_read_keys                          ,0xff01f5ac) //109
NHSTUB(kbd_read_keys_r2                       ,0xff04d560) //109
NHSTUB(lseek                                  ,0xff021ecc) //120
NHSTUB(malloc                                 ,0xff002f2c) //112
NHSTUB(memcmp                                 ,0xff00b99c) //120
NHSTUB(memcpy                                 ,0xff028900) //120
NHSTUB(memset                                 ,0xff281eac) //120
NHSTUB(mkdir                                  ,0xff02214c) //121
NHSTUB(mktime_ext                             ,0xff0a2d4c) //  1
NHSTUB(open                                   ,0xff005b48) //109
NHSTUB(OpenFastDir                            ,0xff32fdec) //115
NHSTUB(closedir                               ,0xff32fd9c) //121
NHSTUB(qsort                                  ,0xff281e4c) //  6
NHSTUB(rand                                   ,0xff281984) //121
NHSTUB(realloc                                ,0xff281f28) //115
NHSTUB(reboot_fw_update                       ,0xff335538) //106
NHSTUB(set_control_event                      ,0xff0878c8) //111
NHSTUB(srand                                  ,0xff281978) //122
NHSTUB(stat                                   ,0xff021f14) //109
NHSTUB(strcat                                 ,0xff0a33cc) //  1
NHSTUB(strchr                                 ,0xff002df8) //  1
NHSTUB(strcmp                                 ,0xff00ba98) //120
NHSTUB(strcpy                                 ,0xff00b984) //120
NHSTUB(strftime                               ,0xff0a2d98) //113
NHSTUB(strlen                                 ,0xff002e44) //120
NHSTUB(strncmp                                ,0xff002dac) //  1
NHSTUB(strncpy                                ,0xff002d70) //  1
NHSTUB(strrchr                                ,0xff002e1c) //  1
NHSTUB(strtol                                 ,0xff0288ec) //101
NHSTUB(strtolx                                ,0xff0286f0) //109
   DEF(task_CaptSeq                           ,0xff06d6bc) //120
   DEF(task_ExpDrv                            ,0xff0bc1b0) //120
   DEF(task_FileWrite                         ,0xff32e7a0) //120
   DEF(task_InitFileModules                   ,0xff08bbc4) //120
   DEF(task_MovieRecord                       ,0xff1b82e8) //120
   DEF(task_PhySw                             ,0xff01f154) //120
   DEF(task_RotaryEncoder                     ,0xff04deb0) //120
NHSTUB(time                                   ,0x0068f8d0) //  6
NHSTUB(vsprintf                               ,0xff00b834) //115
NHSTUB(EngDrvRead                             ,0xff020438) //102
