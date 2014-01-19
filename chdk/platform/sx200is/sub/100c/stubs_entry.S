// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00C   // Found @ 0xff8733d4, "GM1.00C" @ 0xff8733e1
//   Firmware build timestamp: Jan 28 2009 14:08:40
//   Canon PowerShot SX200 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12736 (0x31c0) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0012351c
//   KEYSYS = d4                 // Found @ 0xffff356c
//   NEED_ENCODED_DISKBOOT = 2   // Found @ 0xffff357c
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff94553c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff9454fc

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetSystemTime                        ,0xffa695a4) //120        *** != 0xff8606ac
//NHSTUB(kbd_pwr_off                          ,0xff848480) //  2 60%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa751d8 -> ffb6d0a4
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000f058) // Found @0xff821e24
DEF(physw_run                               ,0x00001c34) // Found @0xff821a94
DEF(physw_sleep_delay                       ,0x00001c32) // Found @0xff821a94
DEF(levent_table                            ,0xffb399f0) // Found @0xffb399f0
DEF(FlashParamsTable                        ,0xffb6d284) // Found @0xffb6d284
DEF(movie_status                            ,0x000065c0) // Found @0xff937fd0
DEF(video_compression_rate                  ,0x000065ec) // Found @0xff93823c
DEF(canon_menu_active                       ,0x00002f10) // Found @0xff874e3c
DEF(canon_shoot_menu_active                 ,0x0000786d) // Found @0xff97761c
DEF(playrec_mode                            ,0x00002c70) // Found @0xff868020
DEF(zoom_status                             ,0x0000b850) // Found @0xffa775d0
DEF(some_flag_for_af_scan                   ,0x00006af8) // Found @0xff93b340
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 126 entries in the table - set NUM_FL to 126
DEF(focus_len_table                         ,0xfffe8538) // Found @0xfffe8538
DEF(zoom_busy                               ,0x000064f0) // Found @0xff9342b4
DEF(focus_busy                              ,0x000063f8) // Found @0xff92e97c
//DEF(recreview_hold                          ,0x000038dc) // Found @0xff885a10, ** != ** stubs_min = 0x00007508 (0x7434+0xD4)
// Palette colour tables  found @ 0xffb55158
//DEF(active_palette_buffer                   ,0x00008d8c) // Found @0xff9cff80,          stubs_min = 0x00008d8c (0x8D8C)
//DEF(palette_buffer_ptr                      ,0x00008d9c) // Found @0xff9cfc44,          stubs_min = 0x00008d9c (0x8D9C)
// Offset from start of palette_buffer to color data = 12 (Found @0xff9cebb0)
// Camera appears to have only 1 RAW buffer @ 0x424b41c0 (Found @0xffac8d10)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff842ac8
//void *vid_get_viewport_fb()      { return (void*)0x415f9e20; }             // Found @0xffac67f0
DEF(viewport_fb_d                           ,0x000029a8) // Found 0x2950 (@0xff859398) + 0x58 (@0xff8593d0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2950+0x58)); } // Found @0xff859398 & 0xff8593d0
DEF(jpeg_count_str                          ,0x0005408c) // Found @0xff9c1f28
//char *camera_jpeg_count_str()    { return (char*)0x0005408c; }             // Found @0xff9c1f28
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffac8d6c
//int get_flash_params_count(void) { return 0x7a; }                          // Found @0xff963320

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffafe514, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00200000 // Found @0xffafe544, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffafe418, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffafe418, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffafe40c, levent 0x00
//    { 0, KEY_POWER           ,0x00000400 }, // Found @0xffafe424, levent 0x600
//    { 0, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffafe430, levent 0x601
//    { 1, KEY_UP              ,0x00000100 }, // Found @0xffafe4a8, levent 0x04
//    { 1, KEY_LEFT            ,0x00000200 }, // Found @0xffafe4b4, levent 0x06
//    { 1, KEY_SET             ,0x00000400 }, // Found @0xffafe4c0, levent 0x08
//    { 1, KEY_MENU            ,0x00000800 }, // Found @0xffafe4cc, levent 0x09
//    { 1, KEY_DOWN            ,0x00001000 }, // Found @0xffafe4d8, levent 0x05
//    { 1, KEY_RIGHT           ,0x00002000 }, // Found @0xffafe4e4, levent 0x07
//    { 1, KEY_DISPLAY         ,0x00008000 }, // Found @0xffafe4fc, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4080 // Found @0xff9025b0
//#define CAM_RAW_ROWS      3048 // Found @0xff9025b4
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff827850

// Misc stuff
DEF(ctypes, 0xffafd12a)

// For capt_seq.c
DEF(_nrflag,0x6ad8) // Found @ ff93d410 (0x6ae0) & ff93d430 (-0x08)
//static long *nrflag = (long*)(0x6ae0-0x08);  // Found @ ff93d410 & ff93d42c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff82780c) //112
NHSTUB(Close                                  ,0xff823cf0) //120
NHSTUB(CreateTask                             ,0xff81afac) //120
NHSTUB(DebugAssert                            ,0xff81b284) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823680) //116
NHSTUB(DeleteFile_Fut                         ,0xff82359c) //112
NHSTUB(DoAELock                               ,0xff825854) //120
NHSTUB(DoAFLock                               ,0xff82560c) //120
NHSTUB(EnterToCompensationEVF                 ,0xff825748) //104
NHSTUB(ExecuteEventProcedure                  ,0xff87057c) //104
NHSTUB(ExitFromCompensationEVF                ,0xff8257f4) //104
NHSTUB(ExitTask                               ,0xff81b23c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff8303c0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff830504) //104
NHSTUB(Fclose_Fut                             ,0xff823718) //120
NHSTUB(Feof_Fut                               ,0xff823904) //  1
NHSTUB(Fflush_Fut                             ,0xff823940) //  1
NHSTUB(Fgets_Fut                              ,0xff82386c) //  1
NHSTUB(Fopen_Fut                              ,0xff8236d8) //120
NHSTUB(Fread_Fut                              ,0xff8237c4) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82784c) //112
NHSTUB(Fseek_Fut                              ,0xff8238b8) //120
NHSTUB(Fwrite_Fut                             ,0xff823818) //120
NHSTUB(GetBatteryTemperature                  ,0xff84b5a8) //102
NHSTUB(GetCCDTemperature                      ,0xff84b534) //102
NHSTUB(GetCurrentAvValue                      ,0xff931328) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff857acc) //  5
NHSTUB(GetDrive_FreeClusters                  ,0xff857b24) //  5
NHSTUB(GetDrive_TotalClusters                 ,0xff857af8) //  5
NHSTUB(GetFocusLensSubjectDistance            ,0xff92f7e4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff92fbc0) //  3
NHSTUB(GetKbdState                            ,0xff848340) //109
NHSTUB(GetMemInfo                             ,0xff813be4) //115
NHSTUB(GetOpticalTemperature                  ,0xff84b61c) //120
NHSTUB(GetParameterData                       ,0xff9632e0) //101
NHSTUB(GetPropertyCase                        ,0xff8742e8) //102
NHSTUB(GetVRAMHPixelsSize                     ,0xff8393a0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8393ac) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff93462c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa5cb24) //102
NHSTUB(GiveSemaphore                          ,0xff827228) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8abb04) //102
NHSTUB(LEDDrive                               ,0xff847614) //120
NHSTUB(LocalTime                              ,0xff86df6c) //115
NHSTUB(LockMainPower                          ,0xff87bce0) //120
NHSTUB(MakeDirectory_Fut                      ,0xff823610) //116
NHSTUB(MoveFocusLensToDistance                ,0xffac3188) //102
NHSTUB(MoveIrisWithAv                         ,0xffa675d8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa67c24) //120
NHSTUB(Open                                   ,0xff823cc8) //120
NHSTUB(PB2Rec                                 ,0xff87d780) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff860884) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86085c) //120
NHSTUB(PT_PlaySound                           ,0xff86046c) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff879a08) //120
NHSTUB(PostLogicalEventToUI                   ,0xff879a54) //120
NHSTUB(PutInNdFilter                          ,0xffac0f60) //102
NHSTUB(PutOutNdFilter                         ,0xffac0f98) //102
NHSTUB(Read                                   ,0xff819ae4) //120
NHSTUB(ReadFastDir                            ,0xffa4794c) //  1
NHSTUB(Rec2PB                                 ,0xff87ee50) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9d4f7c) //104
NHSTUB(RenameFile_Fut                         ,0xff823548) //  1
NHSTUB(Restart                                ,0xff828f5c) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffac5968) //102
NHSTUB(SetAutoShutdownTime                    ,0xff87bd54) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff882d6c) //120
NHSTUB(SetFileAttributes                      ,0xff82401c) //  1
NHSTUB(SetFileTimeStamp                       ,0xff823fcc) //  1
NHSTUB(SetLogicalEventActive                  ,0xff87ba30) //101
NHSTUB(SetParameterData                       ,0xff963250) //101
NHSTUB(SetPropertyCase                        ,0xff8741e0) //102
NHSTUB(SetScriptMode                          ,0xff87ba80) //120
NHSTUB(SleepTask                              ,0xff827490) //120
NHSTUB(TakeSemaphore                          ,0xff827158) //120
NHSTUB(TurnOffBackLight                       ,0xff889254) //104
NHSTUB(TurnOnBackLight                        ,0xff88923c) //104
NHSTUB(TurnOnDisplay                          ,0xff842ba8) //120
NHSTUB(TurnOffDisplay                         ,0xff842bb8) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff94f9d8) //120
NHSTUB(UnlockAE                               ,0xff825878) //120
NHSTUB(UnlockAF                               ,0xff825644) //120
NHSTUB(UnlockMainPower                        ,0xff87bc34) //120
NHSTUB(UnsetZoomForMovie                      ,0xff969764) //104
NHSTUB(UpdateMBROnFlash                       ,0xff857924) //105
NHSTUB(VbattGet                               ,0xff820644) //120
NHSTUB(Write                                  ,0xff823d9c) //120
NHSTUB(WriteSDCard                            ,0xff920e8c) //108
NHSTUB(_log                                   ,0xffafa3c0) //111
NHSTUB(_log10                                 ,0xffaf904c) //112
NHSTUB(_pow                                   ,0xffaf91bc) //121
NHSTUB(_sqrt                                  ,0xffafbf64) //  1
NHSTUB(add_ptp_handler                        ,0xffa125d4) //121
NHSTUB(apex2us                                ,0xff9d8170) //121
NHSTUB(close                                  ,0xff8198fc) //109
NHSTUB(err_init_task                          ,0xff814e2c) //111
NHSTUB(exmem_alloc                            ,0xff86ee2c) //103
NHSTUB(exmem_free                             ,0xff86eea4) //103
NHSTUB(free                                   ,0xff813a3c) //112
NHSTUB(kbd_p1_f                               ,0xff821ea0) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821eac) //109
NHSTUB(kbd_p2_f                               ,0xff821760) //109
NHSTUB(kbd_read_keys                          ,0xff821e24) //109
NHSTUB(kbd_read_keys_r2                       ,0xff847b04) //109
NHSTUB(lseek                                  ,0xff823e30) //120
NHSTUB(malloc                                 ,0xff813968) //112
NHSTUB(memcmp                                 ,0xff81cc5c) //120
NHSTUB(memcpy                                 ,0xff88fe10) //120
NHSTUB(memset                                 ,0xff9d7458) //120
NHSTUB(mkdir                                  ,0xff824094) //109
NHSTUB(mktime_ext                             ,0xff89067c) //  1
NHSTUB(open                                   ,0xff81984c) //109
NHSTUB(OpenFastDir                            ,0xffa478b8) //  1
NHSTUB(closedir                               ,0xffa47a1c) //  1
NHSTUB(qsort                                  ,0xffaaf200) //  1
NHSTUB(rand                                   ,0xff81cd64) //121
NHSTUB(realloc                                ,0xff813b1c) //115
NHSTUB(reboot_fw_update                       ,0xffa4effc) //106
NHSTUB(set_control_event                      ,0xff87b694) //111
NHSTUB(srand                                  ,0xff81cd58) //122
NHSTUB(stat                                   ,0xff823efc) //  1
NHSTUB(strcat                                 ,0xff88fc24) //  1
NHSTUB(strchr                                 ,0xff88fcac) //  1
NHSTUB(strcmp                                 ,0xff81cbf4) //120
NHSTUB(strcpy                                 ,0xff81cbdc) //120
NHSTUB(strftime                               ,0xff890084) //  1
NHSTUB(strlen                                 ,0xff81cc38) //120
NHSTUB(strncmp                                ,0xff88fc60) //  1
NHSTUB(strncpy                                ,0xff82d1bc) //  1
NHSTUB(strrchr                                ,0xff9d7430) //  1
NHSTUB(strtol                                 ,0xff82d3f4) //101
NHSTUB(strtolx                                ,0xff82d1f8) //109
   DEF(task_CaptSeq                           ,0xff86327c) //120
   DEF(task_ExpDrv                            ,0xff8a2214) //120
   DEF(task_FileWrite                         ,0xffa4348c) //120
   DEF(task_InitFileModules                   ,0xff87f81c) //120
   DEF(task_MovieRecord                       ,0xff9382b8) //120
   DEF(task_PhySw                             ,0xff821a90) //120
   DEF(task_RotaryEncoder                     ,0xff84856c) //120
NHSTUB(time                                   ,0xff86e4e4) //109
NHSTUB(vsprintf                               ,0xff81cba0) //115
NHSTUB(EngDrvRead                             ,0xff822cdc) //102
