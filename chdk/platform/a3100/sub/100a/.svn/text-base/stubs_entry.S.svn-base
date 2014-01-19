// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00A   // Found @ 0xff87d0b8, "GM1.00A" @ 0xff87d0c5
//   Firmware build timestamp: Dec 10 2009 13:34:47
//   Canon PowerShot A3100 IS

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12785 (0x31f1) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x001488e0
//   KEYSYS = d4a                // Found @ 0xffff33e0
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff33f0
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff93a484
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff93a444

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xff85471c) //  2 64%    *** != 0x00000000
NHSTUB(kbd_pwr_on                             ,0xff8546dc) //  2 82%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa57c40 -> ffb44890
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00030114) // Found @0xff833cd4
DEF(physw_run                               ,0x00001bf0) // Found @0xff833938
DEF(physw_sleep_delay                       ,0x00001bf8) // Found @0xff833938
DEF(levent_table                            ,0xffafa7e0) // Found @0xffafa7e0
DEF(FlashParamsTable                        ,0xffb44a88) // Found @0xffb44a88
DEF(movie_status                            ,0x00005908) // Found @0xff92d8e8
DEF(full_screen_refresh                     ,0x00007e5c) // Found @0xff9b2870
DEF(canon_menu_active                       ,0x00002ba8) // Found @0xff87ec34
DEF(canon_shoot_menu_active                 ,0x00006c15) // Found @0xff967e48
DEF(playrec_mode                            ,0x000028f0) // Found @0xff871ea4
DEF(zoom_status                             ,0x0000a9b0) // Found @0xffa5b12c
DEF(some_flag_for_af_scan                   ,0x00005cb8) // Found @0xff9306e0
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe29b0) // Found @0xfffe29b0
DEF(zoom_busy                               ,0x0000585c) // Found @0xff9299f4
DEF(focus_busy                              ,0x00005700) // Found @0xff925420
DEF(recreview_hold                          ,0x000031e0) // Found @0xff88bb24
DEF(viewport_buffers                        ,0xffae1370) // Found @0xff8cec74
DEF(active_viewport_buffer                  ,0x0000437c) // Found @0xff8ceabc
// Camera appears to have only 1 RAW buffer @ 0x110b7260 (Found @0xffaadc34)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x103e1000; }             // Found @0xff84fdfc
//void *vid_get_viewport_fb()      { return (void*)0x106f3bc0; }             // Found @0xffaaa904
DEF(viewport_fb_d                           ,0x00002684) // Found 0x2630 (@0xff86475c) + 0x54 (@0xff864788)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2630+0x54)); } // Found @0xff86475c & 0xff864788
DEF(jpeg_count_str                          ,0x00076b3c) // Found @0xff9a9074
//char *camera_jpeg_count_str()    { return (char*)0x00076b3c; }             // Found @0xff9a9074
//long hook_raw_size()             { return 0x011ca240; }                    // Found @0xffaadc90
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xff9567b0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffad98fc, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffad9908, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00000400 }, // Found @0xffad97f4, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x20000000 }, // Found @0xffad980c, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffad983c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffad983c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffad9830, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffad9848, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffad9854, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffad9860, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffad986c, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffad9878, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffad9884, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffad9890, levent 0x08
//    { 2, KEY_MENU            ,0x00000200 }, // Found @0xffad989c, levent 0x09
//    { 2, KEY_DISPLAY         ,0x00000400 }, // Found @0xffad98a8, levent 0x0a
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    4080 // Found @0xff9054e0
//#define CAM_RAW_ROWS      3048 // Found @0xff9054e8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff8397e8

// Misc stuff
DEF(ctypes, 0xffad9112)

// For capt_seq.c
DEF(_nrflag,0x5c98) // Found @ ff93266c (0x5ca0) & ff93268c (-0x08)
//static long *nrflag = (long*)(0x5ca0-0x08);  // Found @ ff93266c & ff932688

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8397a4) //112
NHSTUB(Close                                  ,0xff8362b8) //120
NHSTUB(CreateTask                             ,0xff81f110) //120
NHSTUB(DebugAssert                            ,0xff81f5e8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff835d14) //116
NHSTUB(DeleteFile_Fut                         ,0xff835c30) //112
NHSTUB(DoAELock                               ,0xff83788c) //120
NHSTUB(DoAFLock                               ,0xff837744) //120
NHSTUB(EnterToCompensationEVF                 ,0xff8377f4) //104
NHSTUB(ExecuteEventProcedure                  ,0xff87a350) //104
NHSTUB(ExitFromCompensationEVF                ,0xff837838) //104
NHSTUB(ExitTask                               ,0xff81f3a0) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff8452e8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff8453c0) //104
NHSTUB(Fclose_Fut                             ,0xff835dac) //120
NHSTUB(Feof_Fut                               ,0xff835f98) //  1
NHSTUB(Fflush_Fut                             ,0xff835fd4) //  1
NHSTUB(Fgets_Fut                              ,0xff835f00) //  1
NHSTUB(Fopen_Fut                              ,0xff835d6c) //120
NHSTUB(Fread_Fut                              ,0xff835e58) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8397e4) //112
NHSTUB(Fseek_Fut                              ,0xff835f4c) //120
NHSTUB(Fwrite_Fut                             ,0xff835eac) //120
NHSTUB(GetBatteryTemperature                  ,0xff8567fc) //102
NHSTUB(GetCCDTemperature                      ,0xff856788) //102
NHSTUB(GetCurrentAvValue                      ,0xff926ca0) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff863130) //122
//NHSTUB(GetDrive_FreeClusters                ,0xff863190) //  4            == 0xff863190
NHSTUB(GetDrive_TotalClusters                 ,0xff863164) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xff925f98) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9263f0) //  3
NHSTUB(GetImageFolder                         ,0xff90c464) //122
NHSTUB(GetKbdState                            ,0xff8546a8) //109
NHSTUB(GetMemInfo                             ,0xff81a760) //115
NHSTUB(GetOpticalTemperature                  ,0xff856870) //120
NHSTUB(GetParameterData                       ,0xff956770) //101
NHSTUB(GetPropertyCase                        ,0xff87e05c) //102
NHSTUB(GetSystemTime                          ,0xffa47174) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8d010c) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8d0118) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff929d6c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa37b14) //102
NHSTUB(GiveSemaphore                          ,0xff81f06c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8c04a8) //102
NHSTUB(LEDDrive                               ,0xff853b80) //120
NHSTUB(LocalTime                              ,0xff877dc0) //115
NHSTUB(LockMainPower                          ,0xff882a2c) //120
NHSTUB(MakeDirectory_Fut                      ,0xff835ca4) //116
NHSTUB(MoveFocusLensToDistance                ,0xffaa7378) //102
NHSTUB(MoveIrisWithAv                         ,0xffa4380c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa43d9c) //120
NHSTUB(Open                                   ,0xff83624c) //120
NHSTUB(PB2Rec                                 ,0xff885aa4) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86b1dc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86b1b4) //120
NHSTUB(PT_PlaySound                           ,0xff873aa0) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff88225c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8822a8) //120
NHSTUB(PutInNdFilter                          ,0xffa43c00) //102
NHSTUB(PutOutNdFilter                         ,0xffa43c24) //102
NHSTUB(Read                                   ,0xff81b270) //120
NHSTUB(ReadFastDir                            ,0xffa2d14c) //  4
NHSTUB(Rec2PB                                 ,0xff885ae4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9b3254) //104
NHSTUB(RenameFile_Fut                         ,0xff835b9c) //116
NHSTUB(Restart                                ,0xff83af88) //106
NHSTUB(ScreenLock                             ,0xff9b4414) //117
NHSTUB(ScreenUnlock                           ,0xff9b4458) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffaa9b14) //102
NHSTUB(SetAutoShutdownTime                    ,0xff882aa0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff88943c) //120
NHSTUB(SetFileAttributes                      ,0xff8365b0) //  3
NHSTUB(SetFileTimeStamp                       ,0xff836554) //  4
NHSTUB(SetLogicalEventActive                  ,0xff8827a4) //101
NHSTUB(SetParameterData                       ,0xff9566e0) //101
NHSTUB(SetPropertyCase                        ,0xff87df2c) //102
NHSTUB(SetScriptMode                          ,0xff8827f4) //120
NHSTUB(SleepTask                              ,0xff839628) //120
NHSTUB(TakeSemaphore                          ,0xff81ef9c) //120
NHSTUB(TurnOffBackLight                       ,0xff88e2a8) //104
NHSTUB(TurnOnBackLight                        ,0xff88e290) //104
NHSTUB(TurnOnDisplay                          ,0xff8500d8) //120
NHSTUB(TurnOffDisplay                         ,0xff850104) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff944bfc) //120
NHSTUB(UnlockAE                               ,0xff8378b0) //120
NHSTUB(UnlockAF                               ,0xff83777c) //120
NHSTUB(UnlockMainPower                        ,0xff882980) //120
NHSTUB(UnsetZoomForMovie                      ,0xff95c6c8) //104
NHSTUB(UpdateMBROnFlash                       ,0xff862fb0) //105
NHSTUB(VbattGet                               ,0xff832cf0) //120
NHSTUB(Write                                  ,0xff836348) //120
NHSTUB(WriteSDCard                            ,0xff9196d8) //108
NHSTUB(_log                                   ,0xffad6bd4) //111
NHSTUB(_log10                                 ,0xffad5b18) //112
NHSTUB(_pow                                   ,0xffad5c88) //121
NHSTUB(_sqrt                                  ,0xffad7f3c) //  1
NHSTUB(add_ptp_handler                        ,0xff9f665c) //121
NHSTUB(apex2us                                ,0xff9b577c) //121
NHSTUB(close                                  ,0xff81b088) //109
NHSTUB(err_init_task                          ,0xff815f50) //111
NHSTUB(exmem_alloc                            ,0xff878d00) //103
NHSTUB(exmem_free                             ,0xff878d78) //103
NHSTUB(free                                   ,0xff814160) //112
NHSTUB(kbd_p1_f                               ,0xff833d54) //109
NHSTUB(kbd_p1_f_cont                          ,0xff833d60) //109
NHSTUB(kbd_p2_f                               ,0xff833604) //109
NHSTUB(kbd_read_keys                          ,0xff833cd4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff854028) //109
NHSTUB(lseek                                  ,0xff8363d4) //120
NHSTUB(malloc                                 ,0xff814104) //112
NHSTUB(memcmp                                 ,0xff821280) //120
NHSTUB(memcpy                                 ,0xff83ee14) //120
NHSTUB(memset                                 ,0xff9b47b4) //120
NHSTUB(mkdir                                  ,0xff836754) //109
NHSTUB(mktime_ext                             ,0xff8959e0) //  1
NHSTUB(open                                   ,0xff81afd8) //109
NHSTUB(OpenFastDir                            ,0xffa2cff8) //  4
NHSTUB(closedir                               ,0xffa2cfa8) //121
NHSTUB(qsort                                  ,0xffa8dea0) //  4
NHSTUB(rand                                   ,0xff821388) //121
NHSTUB(realloc                                ,0xff9b4830) //115
NHSTUB(reboot_fw_update                       ,0xffa2e9c0) //106
NHSTUB(set_control_event                      ,0xff8824c4) //111
NHSTUB(srand                                  ,0xff82137c) //122
NHSTUB(stat                                   ,0xff83641c) //109
NHSTUB(strcat                                 ,0xff89519c) //  1
NHSTUB(strchr                                 ,0xff813fe8) //  1
NHSTUB(strcmp                                 ,0xff82123c) //120
NHSTUB(strcpy                                 ,0xff821224) //120
NHSTUB(strftime                               ,0xff8953e8) //113
NHSTUB(strlen                                 ,0xff814034) //120
NHSTUB(strncmp                                ,0xff813f9c) //  1
NHSTUB(strncpy                                ,0xff813f60) //  1
NHSTUB(strrchr                                ,0xff81400c) //  1
NHSTUB(strtol                                 ,0xff83f0f4) //101
NHSTUB(strtolx                                ,0xff83eef8) //109
   DEF(task_CaptSeq                           ,0xff86d6a0) //120
   DEF(task_ExpDrv                            ,0xff8aa748) //120
   DEF(task_FileWrite                         ,0xffa27c24) //120
   DEF(task_InitFileModules                   ,0xff886470) //120
   DEF(task_MovieRecord                       ,0xff92db3c) //120
   DEF(task_PhySw                             ,0xff833934) //120
NHSTUB(time                                   ,0xff8783a0) //109
NHSTUB(vsprintf                               ,0xff8211e8) //115
NHSTUB(EngDrvRead                             ,0xff834ba8) //102
