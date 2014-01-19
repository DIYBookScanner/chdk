// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.01F   // Found @ 0xff86e6dc, "GM1.01F" @ 0xff86e6e9
//   Firmware build timestamp: May 14 2009 09:18:27
//   Canon DIGITAL IXUS 110 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12733 (0x31bd) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00148428
//   KEYSYS = d4                 // Found @ 0xffff3564
//   NEED_ENCODED_DISKBOOT = 2   // Found @ 0xffff3574
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff92e9e4
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff92e9a4

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xff844148) //  2 64%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa6ac28 -> ffb5a440
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000ec78) // Found @0xff821dfc
DEF(physw_run                               ,0x00001c34) // Found @0xff821a64
DEF(physw_sleep_delay                       ,0x00001c32) // Found @0xff821a64
DEF(levent_table                            ,0xffb27f50) // Found @0xffb27f50
DEF(FlashParamsTable                        ,0xffb5a61c) // Found @0xffb5a61c
DEF(movie_status                            ,0x00005ef8) // Found @0xff921558
DEF(video_compression_rate                  ,0x00005f24) // Found @0xff9217c4
DEF(canon_menu_active                       ,0x00002d10) // Found @0xff870138
DEF(canon_shoot_menu_active                 ,0x000070c1) // Found @0xff95c9f0
DEF(playrec_mode                            ,0x00002a78) // Found @0xff8634f0
DEF(zoom_status                             ,0x0000b488) // Found @0xffa6d018
DEF(some_flag_for_af_scan                   ,0x00006430) // Found @0xff92483c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 10 entries in the table - set NUM_FL to 10
//DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c,          stubs_min = 0xfffe2a8c (0xfffe2a8c)
DEF(zoom_busy                               ,0x00005e28) // Found @0xff91d888
DEF(focus_busy                              ,0x00005d20) // Found @0xff9186f8
DEF(recreview_hold                          ,0x00003640) // Found @0xff881428
// Palette colour tables  found @ 0xffb4128c
//DEF(active_palette_buffer                   ,0x000084cc) // Found @0xff9b2820,          stubs_min = 0x000084cc (0x84cc)
//DEF(palette_buffer_ptr                      ,0x000084dc) // Found @0xff9b24e4,          stubs_min = 0x000084dc (0x84dc)
// Offset from start of palette_buffer to color data = 12 (Found @0xff9b1490)
// Camera appears to have only 1 RAW buffer @ 0x424ad900 (Found @0xffac0d34)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff83dc44
//void *vid_get_viewport_fb()      { return (void*)0x415f3570; }             // Found @0xffabe804
DEF(viewport_fb_d                           ,0x000027bc) // Found 0x2764 (@0xff854ed8) + 0x58 (@0xff854f10)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2764+0x58)); } // Found @0xff854ed8 & 0xff854f10
DEF(jpeg_count_str                          ,0x00035278) // Found @0xff9a6d74
//char *camera_jpeg_count_str()    { return (char*)0x00035278; }             // Found @0xff9a6d74
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffac0d90
//int get_flash_params_count(void) { return 0x7a; }                          // Found @0xff94c298

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffaeec7c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffaeec94, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00000001 }, // Found @0xffaeeb80, levent 0x600
//    { 1, KEY_SHOOT_FULL      ,0x00009000 }, // Found @0xffaeebbc, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00008000 }, // Found @0xffaeebbc, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00001000 }, // Found @0xffaeeb98, levent 0x00
//    { 1, KEY_ZOOM_OUT        ,0x00002000 }, // Found @0xffaeeba4, levent 0x03
//    { 1, KEY_ZOOM_IN         ,0x00004000 }, // Found @0xffaeebb0, levent 0x02
//    { 2, KEY_LEFT            ,0x00000020 }, // Found @0xffaeec04, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffaeec10, levent 0x07
//    { 2, KEY_DOWN            ,0x00000080 }, // Found @0xffaeec1c, levent 0x05
//    { 2, KEY_UP              ,0x00000200 }, // Found @0xffaeec34, levent 0x04
//    { 2, KEY_SET             ,0x00000400 }, // Found @0xffaeec40, levent 0x08
//    { 2, KEY_MENU            ,0x00000800 }, // Found @0xffaeec4c, levent 0x09
//    { 2, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffaeec58, levent 0x601
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4080 // Found @0xff8eb104
//#define CAM_RAW_ROWS      3048 // Found @0xff8eb108
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff827520

// Misc stuff
DEF(ctypes, 0xffaed9ce)

// For capt_seq.c
DEF(_nrflag,0x6410) // Found @ ff9267cc (0x6418) & ff9267ec (-0x08)
//static long *nrflag = (long*)(0x6418-0x08);  // Found @ ff9267cc & ff9267e8

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8274dc) //112
NHSTUB(Close                                  ,0xff823cc8) //120
NHSTUB(CreateTask                             ,0xff81afac) //120
NHSTUB(DebugAssert                            ,0xff81b284) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823658) //116
NHSTUB(DeleteFile_Fut                         ,0xff823574) //112
NHSTUB(DoAELock                               ,0xff82556c) //120
NHSTUB(DoAFLock                               ,0xff825380) //120
NHSTUB(EnterToCompensationEVF                 ,0xff82546c) //104
NHSTUB(ExecuteEventProcedure                  ,0xff86b884) //104
NHSTUB(ExitFromCompensationEVF                ,0xff8254b0) //104
NHSTUB(ExitTask                               ,0xff81b23c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff830020) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff830164) //104
NHSTUB(Fclose_Fut                             ,0xff8236f0) //120
NHSTUB(Feof_Fut                               ,0xff8238dc) //  1
NHSTUB(Fflush_Fut                             ,0xff823918) //  1
NHSTUB(Fgets_Fut                              ,0xff823844) //  1
NHSTUB(Fopen_Fut                              ,0xff8236b0) //120
NHSTUB(Fread_Fut                              ,0xff82379c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82751c) //112
NHSTUB(Fseek_Fut                              ,0xff823890) //120
NHSTUB(Fwrite_Fut                             ,0xff8237f0) //120
NHSTUB(GetBatteryTemperature                  ,0xff847118) //102
NHSTUB(GetCCDTemperature                      ,0xff8470a4) //102
NHSTUB(GetCurrentAvValue                      ,0xff91a4b0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff85360c) //  5
NHSTUB(GetDrive_FreeClusters                  ,0xff853664) //  5
NHSTUB(GetDrive_TotalClusters                 ,0xff853638) //  5
NHSTUB(GetFocusLensSubjectDistance            ,0xff919560) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff91993c) //  3
NHSTUB(GetKbdState                            ,0xff844130) //109
NHSTUB(GetMemInfo                             ,0xff813be4) //115
NHSTUB(GetOpticalTemperature                  ,0xff84718c) //120
NHSTUB(GetParameterData                       ,0xff94c258) //101
NHSTUB(GetPropertyCase                        ,0xff86f5f0) //102
NHSTUB(GetSystemTime                          ,0xffa5f164) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8b59cc) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8b59d8) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff91dc00) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa50b44) //102
NHSTUB(GiveSemaphore                          ,0xff826ef8) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8a71a0) //102
NHSTUB(LEDDrive                               ,0xff843600) //120
NHSTUB(LocalTime                              ,0xff869274) //115
NHSTUB(LockMainPower                          ,0xff876f80) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8235e8) //116
NHSTUB(MoveFocusLensToDistance                ,0xffabb19c) //102
NHSTUB(MoveIrisWithAv                         ,0xffa5d268) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa5d7f0) //120
NHSTUB(Open                                   ,0xff823ca0) //120
NHSTUB(PB2Rec                                 ,0xff879ff8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff85c4c8) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff85c4a0) //120
NHSTUB(PT_PlaySound                           ,0xff85c0a4) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff874ce0) //120
NHSTUB(PostLogicalEventToUI                   ,0xff874d2c) //120
NHSTUB(PutInNdFilter                          ,0xffa5d654) //102
NHSTUB(PutOutNdFilter                         ,0xffa5d678) //102
NHSTUB(Read                                   ,0xff819ae4) //120
NHSTUB(ReadFastDir                            ,0xffa3d384) //  1
NHSTUB(Rec2PB                                 ,0xff8789fc) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9b78b8) //104
NHSTUB(RenameFile_Fut                         ,0xff823520) //  1
NHSTUB(Restart                                ,0xff828c2c) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffabd97c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff876ff4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87ea48) //120
NHSTUB(SetFileAttributes                      ,0xff823ff4) //  1
NHSTUB(SetFileTimeStamp                       ,0xff823fa4) //  1
NHSTUB(SetLogicalEventActive                  ,0xff876cd0) //101
NHSTUB(SetParameterData                       ,0xff94c1c8) //101
NHSTUB(SetPropertyCase                        ,0xff86f4e8) //102
NHSTUB(SetScriptMode                          ,0xff876d20) //120
NHSTUB(SleepTask                              ,0xff827160) //120
NHSTUB(TakeSemaphore                          ,0xff826e28) //120
NHSTUB(TurnOffBackLight                       ,0xff88492c) //104
NHSTUB(TurnOnBackLight                        ,0xff884914) //104
NHSTUB(TurnOnDisplay                          ,0xff83dd68) //120
NHSTUB(TurnOffDisplay                         ,0xff83dd78) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff939098) //120
NHSTUB(UnlockAE                               ,0xff825590) //120
NHSTUB(UnlockAF                               ,0xff8253b8) //120
NHSTUB(UnlockMainPower                        ,0xff876ed4) //120
NHSTUB(UnsetZoomForMovie                      ,0xff952aa0) //104
NHSTUB(UpdateMBROnFlash                       ,0xff853464) //105
NHSTUB(VbattGet                               ,0xff820644) //120
NHSTUB(Write                                  ,0xff823d74) //120
NHSTUB(WriteSDCard                            ,0xff90ac68) //108
NHSTUB(_log                                   ,0xffaeac64) //111
NHSTUB(_log10                                 ,0xffae98f0) //112
NHSTUB(_pow                                   ,0xffae9a60) //121
NHSTUB(_sqrt                                  ,0xffaec808) //  1
NHSTUB(add_ptp_handler                        ,0xffa05234) //121
NHSTUB(apex2us                                ,0xff9baac0) //121
NHSTUB(close                                  ,0xff8198fc) //109
NHSTUB(err_init_task                          ,0xff814e2c) //111
NHSTUB(exmem_alloc                            ,0xff86a134) //103
NHSTUB(exmem_free                             ,0xff86a1ac) //103
NHSTUB(free                                   ,0xff813a3c) //112
NHSTUB(kbd_p1_f                               ,0xff821e78) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821e84) //109
NHSTUB(kbd_p2_f                               ,0xff821730) //109
NHSTUB(kbd_read_keys                          ,0xff821dfc) //109
NHSTUB(kbd_read_keys_r2                       ,0xff843ad4) //109
NHSTUB(lseek                                  ,0xff823e08) //120
NHSTUB(malloc                                 ,0xff813968) //112
NHSTUB(memcmp                                 ,0xff81cc5c) //120
NHSTUB(memcpy                                 ,0xff88b508) //120
NHSTUB(memset                                 ,0xff9b9da8) //120
NHSTUB(mkdir                                  ,0xff82406c) //109
NHSTUB(mktime_ext                             ,0xff88bd74) //  1
NHSTUB(open                                   ,0xff81984c) //109
NHSTUB(OpenFastDir                            ,0xffa3d2f0) //  1
NHSTUB(closedir                               ,0xffa3d454) //  1
NHSTUB(qsort                                  ,0xffaa00b0) //  1
NHSTUB(rand                                   ,0xff81cd64) //121
NHSTUB(realloc                                ,0xff813b1c) //115
NHSTUB(reboot_fw_update                       ,0xffa44a34) //106
NHSTUB(set_control_event                      ,0xff876934) //111
NHSTUB(srand                                  ,0xff81cd58) //122
NHSTUB(stat                                   ,0xff823ed4) //  1
NHSTUB(strcat                                 ,0xff88b31c) //  1
NHSTUB(strchr                                 ,0xff88b3a4) //  1
NHSTUB(strcmp                                 ,0xff81cbf4) //120
NHSTUB(strcpy                                 ,0xff81cbdc) //120
NHSTUB(strftime                               ,0xff88b77c) //  1
NHSTUB(strlen                                 ,0xff81cc38) //120
NHSTUB(strncmp                                ,0xff88b358) //  1
NHSTUB(strncpy                                ,0xff82ce1c) //  1
NHSTUB(strrchr                                ,0xff9b9d80) //  1
NHSTUB(strtol                                 ,0xff82d054) //101
NHSTUB(strtolx                                ,0xff82ce58) //109
   DEF(task_CaptSeq                           ,0xff85eae4) //120
   DEF(task_ExpDrv                            ,0xff89d8cc) //120
   DEF(task_FileWrite                         ,0xffa38ec4) //120
   DEF(task_InitFileModules                   ,0xff87aac0) //120
   DEF(task_MovieRecord                       ,0xff921840) //120
   DEF(task_PhySw                             ,0xff821a60) //120
   DEF(task_RotaryEncoder                     ,0xff844220) //120
NHSTUB(time                                   ,0xff8697ec) //109
NHSTUB(vsprintf                               ,0xff81cba0) //115
NHSTUB(EngDrvRead                             ,0xff822cb4) //102
