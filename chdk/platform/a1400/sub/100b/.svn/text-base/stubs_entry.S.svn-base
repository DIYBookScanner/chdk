// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R52 (DRYOS version 2.3, release #0052)
//   Firmware Ver GM1.00B   // Found @ 0xff88cce4, "GM1.00B" @ 0xff88ccf1
//   Firmware build timestamp: Dec  6 2012 18:32:55
//   Canon PowerShot A1400

// Values for makefile.inc
//   PLATFORMOSVER = 52
//   PLATFORMID = 12900 (0x3264) // Found @ 0xfffe0040
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0015a048
//   KEYSYS = d4d                // Found @ 0xffff1d54
//   NEED_ENCODED_DISKBOOT = 10   // Found @ 0xffff1d64

// Note, ROM copied to RAM :- from 0xffc53a20, to 0x003f1000, len 15975 words.
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff97f678
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff97f63c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DeleteFile_Fut                       ,0xff82cdf8) //  1 90%        == 0xff82cdf8
//NHSTUB(GetBatteryTemperature                ,0xff862fd0) //102        *** != 0x00000000
// ERROR: MakeDirectory_Fut is not found.                  //--- ---    *** != 0xff82d908
// ERROR: RefreshPhysicalScreen is not found.              //--- ---    *** != 0x00000000
//NHSTUB(Restart                              ,0xff8312a8) //106        *** != 0xff831200

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa9b104 -> ffbebdf0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000325e4) // Found @0xff82acbc
DEF(physw_run                               ,0x00001c90) // Found @0xff82a80c
DEF(physw_sleep_delay                       ,0x00001c98) // Found @0xff82a80c
DEF(levent_table                            ,0xffb9a87c) // Found @0xffb9a87c
DEF(FlashParamsTable                        ,0xffbec020) // Found @0xffbec020
DEF(movie_status                            ,0x000069e4) // Found @0xff970990
DEF(video_compression_rate                  ,0x00006a14) // Found @0xff9710f4
DEF(full_screen_refresh                     ,0x00007424) // Found @0xff98d1d0
DEF(canon_menu_active                       ,0x00003748) // Found @0xff895300
DEF(canon_shoot_menu_active                 ,0x00008a09) // Found @0xff9e5a94
DEF(playrec_mode                            ,0x00003188) // Found @0xff882808
DEF(zoom_status                             ,0x00009eb8) // Found @0xffa37e00
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 64 entries in the table - set NUM_FL to 64
DEF(focus_len_table                         ,0xfffea3e0) // Found @0xfffea3e0
DEF(zoom_busy                               ,0x000068f0) // Found @0xff96cfcc
DEF(focus_busy                              ,0x000067bc) // Found @0xff969a68
DEF(recreview_hold                          ,0x00002720) // Found @0xff859ea8
// Palette colour tables  found @ 0xffba14b8
DEF(active_palette_buffer                   ,0x0000742c) // Found @0xff98d154
DEF(palette_buffer_ptr                      ,0x00007430) // Found @0xff98d4e4
// Offset from start of palette_buffer to color data = 4 (Found @0xffabbba8)
// Camera appears to have only 1 RAW buffer @ 0x420e5c30 (Found @0xffb16a34)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40431000; }             // Found @0xff85ce98
//void *vid_get_viewport_fb()      { return (void*)0x40586b80; }             // Found @0xffb1511c
DEF(viewport_fb_d                           ,0x00002f90) // Found 0x2f3c (@0xff876e34) + 0x54 (@0xff876e6c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2f3c+0x54)); } // Found @0xff876e34 & 0xff876e6c
DEF(jpeg_count_str                          ,0x000c86fc) // Found @0xff9d40b4
//char *camera_jpeg_count_str()    { return (char*)0x000c86fc; }             // Found @0xff9d40b4
//long hook_raw_size()             { return 0x01794300; }                    // Found @0xffb16a8c
//int get_flash_params_count(void) { return 0x91; }                          // Found @0xff985214

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x02000000 // Found @0xffb47274, levent 0x20a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x10000000 // Found @0xffb47284, levent 0x202
//#define USB_IDX             2
//#define BATTCOVER_FLAG      0x04000000 // Found @0xffb4727c, levent 0x205
//#define BATTCOVER_IDX       2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_UP              ,0x00001000 }, // Found @0xffb471e4, levent 0x04
//    { 0, KEY_ZOOM_OUT        ,0x00002000 }, // Found @0xffb471ec, levent 0x03
//    { 1, KEY_SHOOT_FULL      ,0x00300000 }, // Found @0xffb471fc, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x00200000 }, // Found @0xffb471fc, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x00100000 }, // Found @0xffb471f4, levent 0x00
//    { 1, KEY_LEFT            ,0x00400000 }, // Found @0xffb47204, levent 0x06
//    { 1, KEY_RIGHT           ,0x00800000 }, // Found @0xffb4720c, levent 0x07
//    { 1, KEY_MENU            ,0x01000000 }, // Found @0xffb47214, levent 0x09
//    { 1, KEY_SET             ,0x02000000 }, // Found @0xffb4721c, levent 0x08
//    { 1, KEY_DISPLAY         ,0x08000000 }, // Found @0xffb4722c, levent 0x0a
//    { 1, KEY_ZOOM_IN         ,0x10000000 }, // Found @0xffb47234, levent 0x02
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffb47244, levent 0x100
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffb4724c, levent 0x101
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4704 // Found @0xff943780
//#define CAM_RAW_ROWS      3504 // Found @0xff94378c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff831d9c

// Misc stuff
DEF(ctypes, 0xffb4671c)

// For capt_seq.c
DEF(_nrflag,0x9714) // Found @ ff9f469c (0x9714) & ff9f46d8 (+0x00)
//static long *nrflag = (long*)(0x9714+0x00);  // Found @ ff9f469c & ff9f46d8
//#define NR_AUTO (0)                          // have to explictly reset value back to 0 to enable auto

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff831d54) //112
NHSTUB(Close                                  ,0xff82d46c) //120
NHSTUB(CreateTask                             ,0x003f68b0) //120
NHSTUB(DebugAssert                            ,0x003f6c28) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff82ce6c) //116
NHSTUB(DoAELock                               ,0xff82ef2c) //120
NHSTUB(DoAFLock                               ,0xff82ec4c) //120
NHSTUB(EnterToCompensationEVF                 ,0xff82ee94) //104
NHSTUB(ExecuteEventProcedure                  ,0xff889d44) //104
NHSTUB(ExitFromCompensationEVF                ,0xff82eed8) //104
NHSTUB(ExitTask                               ,0x003f6b40) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff83e6bc) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff83e830) //104
NHSTUB(Fclose_Fut                             ,0xff82cf04) //120
NHSTUB(Feof_Fut                               ,0xff82d0f0) //  1
NHSTUB(Fflush_Fut                             ,0xff82d12c) //  1
NHSTUB(Fgets_Fut                              ,0xff82d058) //  6
NHSTUB(Fopen_Fut                              ,0xff82cec4) //120
NHSTUB(Fread_Fut                              ,0xff82cfb0) //120
NHSTUB(FreeUncacheableMemory                  ,0xff831d94) //112
NHSTUB(Fseek_Fut                              ,0xff82d0a4) //120
NHSTUB(Fwrite_Fut                             ,0xff82d004) //120
NHSTUB(GetCCDTemperature                      ,0xff862f5c) //102
NHSTUB(GetCurrentAvValue                      ,0xff96b8cc) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff874e6c) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff875680) //  6
NHSTUB(GetDrive_TotalClusters                 ,0xff875658) //  6
NHSTUB(GetFocusLensSubjectDistance            ,0xff96ab98) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff96af2c) //  3
NHSTUB(GetImageFolder                         ,0xff94aeac) //122
NHSTUB(GetKbdState                            ,0xff861738) //109
NHSTUB(GetMemInfo                             ,0xff814fcc) //115
NHSTUB(GetOpticalTemperature                  ,0xff863048) //120
NHSTUB(GetParameterData                       ,0xff9851d4) //101
NHSTUB(GetPropertyCase                        ,0xff88e0f8) //101
NHSTUB(GetSystemTime                          ,0xffa981fc) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff84a9b4) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff84a9c0) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff96d448) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa88d50) //102
NHSTUB(GiveSemaphore                          ,0x003f7904) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8d4254) //102
NHSTUB(LEDDrive                               ,0xff972694) //120
NHSTUB(LocalTime                              ,0x003fb2e8) //115
NHSTUB(LockMainPower                          ,0xff89056c) //120
NHSTUB(MakeSDCardBootable                     ,0xff875b04) //105
NHSTUB(MoveFocusLensToDistance                ,0xffb10c84) //102
NHSTUB(MoveIrisWithAv                         ,0xffa9371c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa93e4c) //120
NHSTUB(Open                                   ,0xff82d3a4) //120
NHSTUB(PB2Rec                                 ,0xff852db8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff973794) //102
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff973764) //102
NHSTUB(PT_PlaySound                           ,0xff89cc54) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff88fc5c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff88fca8) //120
NHSTUB(PutInNdFilter                          ,0xffa93c24) //102
NHSTUB(PutOutNdFilter                         ,0xffa93c48) //102
NHSTUB(Read                                   ,0xff815a88) //120
NHSTUB(ReadFastDir                            ,0xffa77d8c) //115
NHSTUB(Rec2PB                                 ,0xff852df8) //104
NHSTUB(RenameFile_Fut                         ,0xff82cd64) //116
NHSTUB(ScreenLock                             ,0xff894df8) //117
NHSTUB(ScreenUnlock                           ,0xff894e4c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffb13ff4) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8905e0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff89b0b0) //120
NHSTUB(SetFileAttributes                      ,0xff82d870) //  6
NHSTUB(SetFileTimeStamp                       ,0xff82d7f8) //  6
NHSTUB(SetLogicalEventActive                  ,0xff8902e4) //101
NHSTUB(SetParameterData                       ,0xff985140) //101
NHSTUB(SetPropertyCase                        ,0xff88df68) //101
NHSTUB(SetScriptMode                          ,0xff890334) //120
NHSTUB(SleepTask                              ,0x003f7bb0) //120
NHSTUB(TakeSemaphore                          ,0x003f7834) //120
NHSTUB(TurnOffBackLight                       ,0xff89c520) //104
NHSTUB(TurnOnBackLight                        ,0xff89c508) //104
NHSTUB(TurnOnDisplay                          ,0xff85d2a0) //120
NHSTUB(TurnOffDisplay                         ,0xff85d2b0) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff9a08f0) //120
NHSTUB(UnlockAE                               ,0xff82ef50) //120
NHSTUB(UnlockAF                               ,0xff82ec7c) //120
NHSTUB(UnlockMainPower                        ,0xff8904c0) //120
NHSTUB(UnsetZoomForMovie                      ,0xff9166b4) //104
NHSTUB(VbattGet                               ,0xff829b04) //120
NHSTUB(Write                                  ,0xff82d4c0) //120
NHSTUB(WriteSDCard                            ,0xff95c6bc) //108
NHSTUB(_log                                   ,0x003fd0b0) //111
NHSTUB(_log10                                 ,0x003fd5f0) //112
NHSTUB(_pow                                   ,0x003fd768) //121
NHSTUB(_sqrt                                  ,0x003ff38c) //  6
NHSTUB(add_ptp_handler                        ,0xffa31728) //121
NHSTUB(apex2us                                ,0xff9ed768) //121
NHSTUB(close                                  ,0xff8158e4) //109
NHSTUB(err_init_task                          ,0xff8142ac) //111
NHSTUB(exmem_alloc                            ,0xff88870c) //101
NHSTUB(exmem_free                             ,0xff888784) //101
NHSTUB(free                                   ,0xff812ea8) //112
NHSTUB(kbd_p1_f                               ,0xff82ad0c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff82ad18) //109
NHSTUB(kbd_p2_f                               ,0xff82a4a4) //109
NHSTUB(kbd_read_keys                          ,0xff82acbc) //109
NHSTUB(kbd_read_keys_r2                       ,0xff861248) //109
NHSTUB(lseek                                  ,0xff82d688) //120
NHSTUB(malloc                                 ,0xff812e50) //112
NHSTUB(memcmp                                 ,0xff81a938) //120
NHSTUB(memcpy                                 ,0xff832128) //120
NHSTUB(memset                                 ,0xff89febc) //120
NHSTUB(mkdir                                  ,0xff82d908) //121
NHSTUB(mktime_ext                             ,0xff89f6c4) //  1
NHSTUB(open                                   ,0xff815834) //109
NHSTUB(OpenFastDir                            ,0xffa77c38) //115
NHSTUB(closedir                               ,0xffa77be8) //121
NHSTUB(qsort                                  ,0xffae9970) //  6
NHSTUB(rand                                   ,0xffae9444) //121
NHSTUB(realloc                                ,0xff9eb338) //115
NHSTUB(reboot_fw_update                       ,0xffa97820) //106
NHSTUB(set_control_event                      ,0xff88ffa4) //111
NHSTUB(srand                                  ,0xffae9438) //122
NHSTUB(stat                                   ,0xff82d6d0) //109
NHSTUB(strcat                                 ,0xff89fd44) //  1
NHSTUB(strchr                                 ,0xff812d1c) //  1
NHSTUB(strcmp                                 ,0xff81aa34) //120
NHSTUB(strcpy                                 ,0xff81a920) //120
NHSTUB(strftime                               ,0xff89f710) //113
NHSTUB(strlen                                 ,0xff812d68) //120
NHSTUB(strncmp                                ,0xff812cd0) //  1
NHSTUB(strncpy                                ,0xff812c94) //  1
NHSTUB(strrchr                                ,0xff812d40) //  1
NHSTUB(strtol                                 ,0xff832114) //101
NHSTUB(strtolx                                ,0xff831f18) //109
   DEF(task_CaptSeq                           ,0xff87d2a4) //120
   DEF(task_ExpDrv                            ,0xff8b98f4) //120
   DEF(task_FileWrite                         ,0xffa73eec) //120
   DEF(task_InitFileModules                   ,0xff853790) //120
   DEF(task_MovieRecord                       ,0xff9715c8) //120
   DEF(task_PhySw                             ,0xff82a808) //120
   DEF(hook_CreateTask                        ,0x003f68b0) //105
NHSTUB(time                                   ,0x003fb790) //  6
NHSTUB(vsprintf                               ,0xff81a7d0) //115
NHSTUB(EngDrvRead                             ,0xff82bb4c) //102
