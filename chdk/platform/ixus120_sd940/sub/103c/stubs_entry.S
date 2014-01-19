// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R39 (DRYOS version 2.3, release #0039)
//   Firmware Ver GM1.03C   // Found @ 0xff883ab0, "GM1.03C" @ 0xff883abd
//   Firmware build timestamp: Jan  7 2010 13:31:50
//   Canon PowerShot SD940 IS

// Values for makefile.inc
//   PLATFORMOSVER = 39
//   PLATFORMID = 12774 (0x31e6) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0013ca18
//   KEYSYS = d4                 // Found @ 0xffff3564
//   NEED_ENCODED_DISKBOOT = 3   // Found @ 0xffff3574
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff94b420
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff94b3e0

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xff858e10) //  2 64%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa75bcc -> ffb972e0
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00031b78) // Found @0xff833554
DEF(physw_run                               ,0x00001c44) // Found @0xff8331c8
DEF(physw_sleep_delay                       ,0x00001c42) // Found @0xff8331c8
DEF(levent_table                            ,0xffb42100) // Found @0xffb42100
DEF(FlashParamsTable                        ,0xffb974c8) // Found @0xffb974c8
DEF(movie_status                            ,0x00006260) // Found @0xff93d528
DEF(video_compression_rate                  ,0x0000628c) // Found @0xff93d794
DEF(full_screen_refresh                     ,0x00008bb0) // Found @0xff9cfb9c
DEF(canon_menu_active                       ,0x00002d48) // Found @0xff885530
DEF(canon_shoot_menu_active                 ,0x00007751) // Found @0xff97bb7c
DEF(playrec_mode                            ,0x00002a7c) // Found @0xff877b4c
DEF(zoom_status                             ,0x0000b9dc) // Found @0xffa78464
DEF(some_flag_for_af_scan                   ,0x0000673c) // Found @0xff940518
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 10 entries in the table - set NUM_FL to 10
DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c
DEF(zoom_busy                               ,0x000061cc) // Found @0xff93a5fc
DEF(focus_busy                              ,0x00006078) // Found @0xff934b74
DEF(recreview_hold                          ,0x000033a4) // Found @0xff894324
// Palette colour tables  found @ 0xffb58c38
DEF(active_palette_buffer                   ,0x00008bb8) // Found @0xff9cfad8
DEF(palette_buffer_ptr                      ,0x00008bc4) // Found @0xff9cf7ac
// Offset from start of palette_buffer to color data = 8 (Found @0xffaafc18)
// Camera appears to have only 1 RAW buffer @ 0x4219d120 (Found @0xffad704c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff8532dc
//void *vid_get_viewport_fb()      { return (void*)0x4088b700; }             // Found @0xffad4920
DEF(viewport_fb_d                           ,0x000027e8) // Found 0x2790 (@0xff869e3c) + 0x58 (@0xff869e74)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2790+0x58)); } // Found @0xff869e3c & 0xff869e74
DEF(jpeg_count_str                          ,0x000700b0) // Found @0xff9c42f8
//char *camera_jpeg_count_str()    { return (char*)0x000700b0; }             // Found @0xff9c42f8
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffad70a8
//int get_flash_params_count(void) { return 0x84; }                          // Found @0xff96b5d0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb0c940, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffb0c958, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SET             ,0x00000004 }, // Found @0xffb0c880, levent 0x08
//    { 0, KEY_DISPLAY         ,0x00000008 }, // Found @0xffb0c88c, levent 0x0a
//    { 2, KEY_MENU            ,0x00000001 }, // Found @0xffb0c8a4, levent 0x09
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffb0c8b0, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffb0c8bc, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffb0c8c8, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffb0c8d4, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffb0c8e0, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffb0c8ec, levent 0x04
//    { 2, KEY_SHOOT_FULL      ,0x00000300 }, // Found @0xffb0c904, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000200 }, // Found @0xffb0c904, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000100 }, // Found @0xffb0c8f8, levent 0x00
//    { 2, KEY_POWER           ,0x00000400 }, // Found @0xffb0c910, levent 0x600
//    { 2, KEY_PLAYBACK        ,0x00000800 }, // Found @0xffb0c91c, levent 0x601
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4080 // Found @0xff91124c
//#define CAM_RAW_ROWS      3048 // Found @0xff911254
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff8388dc

// Misc stuff
DEF(ctypes, 0xffb0b3fa)

// For capt_seq.c
DEF(_nrflag,0x6718) // Found @ ff942680 (0x6720) & ff9426a0 (-0x08)
//static long *nrflag = (long*)(0x6720-0x08);  // Found @ ff942680 & ff94269c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff838898) //112
NHSTUB(Close                                  ,0xff8353b4) //120
NHSTUB(CreateTask                             ,0xff81e5b4) //120
NHSTUB(DebugAssert                            ,0xff81e88c) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff834e24) //116
NHSTUB(DeleteFile_Fut                         ,0xff834d40) //112
NHSTUB(DoAELock                               ,0xff836a6c) //120
NHSTUB(DoAFLock                               ,0xff83687c) //120
NHSTUB(EnterToCompensationEVF                 ,0xff8369d4) //104
NHSTUB(ExecuteEventProcedure                  ,0xff880c54) //104
NHSTUB(ExitFromCompensationEVF                ,0xff836a18) //104
NHSTUB(ExitTask                               ,0xff81e844) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff844034) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff84410c) //104
NHSTUB(Fclose_Fut                             ,0xff834ebc) //120
NHSTUB(Feof_Fut                               ,0xff8350a8) //  1
NHSTUB(Fflush_Fut                             ,0xff8350e4) //  1
NHSTUB(Fgets_Fut                              ,0xff835010) //  1
NHSTUB(Fopen_Fut                              ,0xff834e7c) //120
NHSTUB(Fread_Fut                              ,0xff834f68) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8388d8) //112
NHSTUB(Fseek_Fut                              ,0xff83505c) //120
NHSTUB(Fwrite_Fut                             ,0xff834fbc) //120
NHSTUB(GetBatteryTemperature                  ,0xff85bd0c) //102
NHSTUB(GetCCDTemperature                      ,0xff85bc98) //102
NHSTUB(GetCurrentAvValue                      ,0xff936720) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff868774) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff8687d4) //  3
NHSTUB(GetDrive_TotalClusters                 ,0xff8687a8) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff9358ec) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff935d34) //  3
NHSTUB(GetImageFolder                         ,0xff919078) //122
NHSTUB(GetKbdState                            ,0xff858df8) //109
NHSTUB(GetMemInfo                             ,0xff81a070) //115
NHSTUB(GetOpticalTemperature                  ,0xff85bd80) //120
NHSTUB(GetParameterData                       ,0xff96b590) //101
NHSTUB(GetPropertyCase                        ,0xff8849a4) //102
NHSTUB(GetSystemTime                          ,0xffa69ef8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8da340) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8da34c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff93a970) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa5db08) //102
NHSTUB(GiveSemaphore                          ,0xff8382b4) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8bc2c4) //102
NHSTUB(LEDDrive                               ,0xff8582f4) //120
NHSTUB(LocalTime                              ,0xff87e5c8) //115
NHSTUB(LockMainPower                          ,0xff88aabc) //120
NHSTUB(MakeDirectory_Fut                      ,0xff834db4) //116
NHSTUB(MoveFocusLensToDistance                ,0xffad12ac) //102
NHSTUB(MoveIrisWithAv                         ,0xffa679e0) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa67f6c) //120
NHSTUB(Open                                   ,0xff83535c) //120
NHSTUB(PB2Rec                                 ,0xff88da58) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff870990) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff870968) //120
NHSTUB(PT_PlaySound                           ,0xff879764) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff88a2f4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff88a340) //120
NHSTUB(PutInNdFilter                          ,0xffa67dd0) //102
NHSTUB(PutOutNdFilter                         ,0xffa67df4) //102
NHSTUB(Read                                   ,0xff81ab78) //120
NHSTUB(ReadFastDir                            ,0xffa4d2c0) //  3
NHSTUB(Rec2PB                                 ,0xff88da98) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9d206c) //104
NHSTUB(RenameFile_Fut                         ,0xff834cac) //116
NHSTUB(Restart                                ,0xff839ff0) //106
NHSTUB(ScreenLock                             ,0xff9d1e44) //117
NHSTUB(ScreenUnlock                           ,0xff9d1e84) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffad3a98) //102
NHSTUB(SetAutoShutdownTime                    ,0xff88ab30) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff891b68) //120
NHSTUB(SetFileAttributes                      ,0xff835684) //  3
NHSTUB(SetFileTimeStamp                       ,0xff835640) //  3
NHSTUB(SetLogicalEventActive                  ,0xff88a838) //101
NHSTUB(SetParameterData                       ,0xff96b500) //101
NHSTUB(SetPropertyCase                        ,0xff8848a8) //102
NHSTUB(SetScriptMode                          ,0xff88a888) //120
NHSTUB(SleepTask                              ,0xff83851c) //120
NHSTUB(TakeSemaphore                          ,0xff8381e4) //120
NHSTUB(TurnOffBackLight                       ,0xff8976a8) //104
NHSTUB(TurnOnBackLight                        ,0xff897690) //104
NHSTUB(TurnOnDisplay                          ,0xff8534e0) //120
NHSTUB(TurnOffDisplay                         ,0xff8534f0) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff956904) //120
NHSTUB(UnlockAE                               ,0xff836a90) //120
NHSTUB(UnlockAF                               ,0xff8368b4) //120
NHSTUB(UnlockMainPower                        ,0xff88aa10) //120
NHSTUB(UnsetZoomForMovie                      ,0xff9714ac) //104
NHSTUB(UpdateMBROnFlash                       ,0xff8685f4) //105
NHSTUB(VbattGet                               ,0xff831df4) //120
NHSTUB(Write                                  ,0xff835444) //120
NHSTUB(WriteSDCard                            ,0xff926720) //108
NHSTUB(_log                                   ,0xffb08ebc) //111
NHSTUB(_log10                                 ,0xffb07e00) //112
NHSTUB(_pow                                   ,0xffb07f70) //121
NHSTUB(_sqrt                                  ,0xffb0a224) //  1
NHSTUB(add_ptp_handler                        ,0xffa1700c) //121
NHSTUB(apex2us                                ,0xff9d555c) //121
NHSTUB(close                                  ,0xff81a990) //109
NHSTUB(err_init_task                          ,0xff815f28) //111
NHSTUB(exmem_alloc                            ,0xff87f488) //103
NHSTUB(exmem_free                             ,0xff87f500) //103
NHSTUB(free                                   ,0xff814138) //112
NHSTUB(kbd_p1_f                               ,0xff8335d0) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8335dc) //109
NHSTUB(kbd_p2_f                               ,0xff832e94) //109
NHSTUB(kbd_read_keys                          ,0xff833554) //109
NHSTUB(kbd_read_keys_r2                       ,0xff8587b8) //109
NHSTUB(lseek                                  ,0xff8354d0) //120
NHSTUB(malloc                                 ,0xff8140dc) //112
NHSTUB(memcmp                                 ,0xff8203d8) //120
NHSTUB(memcpy                                 ,0xff83de48) //120
NHSTUB(memset                                 ,0xff9d45ac) //120
NHSTUB(mkdir                                  ,0xff835828) //109
NHSTUB(mktime_ext                             ,0xff89eaf4) //  1
NHSTUB(open                                   ,0xff81a8e0) //109
NHSTUB(OpenFastDir                            ,0xffa4d18c) //  3
NHSTUB(closedir                               ,0xffa4d148) //  3
NHSTUB(qsort                                  ,0xffab58d4) //  1
NHSTUB(rand                                   ,0xff8204e0) //121
NHSTUB(realloc                                ,0xff9d4628) //115
NHSTUB(reboot_fw_update                       ,0xffa527d0) //106
NHSTUB(set_control_event                      ,0xff88a55c) //111
NHSTUB(srand                                  ,0xff8204d4) //122
NHSTUB(stat                                   ,0xff83550c) //109
NHSTUB(strcat                                 ,0xff89e2b0) //  1
NHSTUB(strchr                                 ,0xff813fc0) //  1
NHSTUB(strcmp                                 ,0xff820394) //120
NHSTUB(strcpy                                 ,0xff82037c) //120
NHSTUB(strftime                               ,0xff89e4fc) //  1
NHSTUB(strlen                                 ,0xff81400c) //120
NHSTUB(strncmp                                ,0xff813f74) //  1
NHSTUB(strncpy                                ,0xff813f38) //  1
NHSTUB(strrchr                                ,0xff813fe4) //  1
NHSTUB(strtol                                 ,0xff83e128) //101
NHSTUB(strtolx                                ,0xff83df2c) //109
   DEF(task_CaptSeq                           ,0xff872fe0) //120
   DEF(task_ExpDrv                            ,0xff8b2fd0) //120
   DEF(task_FileWrite                         ,0xffa48b1c) //120
   DEF(task_InitFileModules                   ,0xff88e57c) //120
   DEF(task_MovieRecord                       ,0xff93d810) //120
   DEF(task_PhySw                             ,0xff8331c4) //120
NHSTUB(time                                   ,0xff87eb40) //109
NHSTUB(vsprintf                               ,0xff820340) //115
NHSTUB(EngDrvRead                             ,0xff834418) //102
