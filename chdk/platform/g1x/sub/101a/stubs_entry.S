// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R49 (DRYOS version 2.3, release #0049)
//   Firmware Ver GM1.01A   // Found @ 0xff08ea38, "GM1.01A" @ 0xff08ea45
//   Firmware build timestamp: Jun 11 2012 10:18:29
//   Canon PowerShot G1 X

// Values for makefile.inc
//   PLATFORMOSVER = 49
//   PLATFORMID = 12851 (0x3233) // Found @ 0xfff40040
//   MAXRAMADDR = 0x0fffffff
//   MEMISOSTART = 0x0018c7b4
//   KEYSYS = d4c                // Found @ 0xffff3bb0
//   NEED_ENCODED_DISKBOOT = 7   // Found @ 0xffff3bc0
//   ARAM_HEAP_START = 0x5de000  // Found @ 0xff1db884
//   ARAM_HEAP_SIZE  = 0x22000   // Found @ 0xff1db844

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ff388e1c -> ff63a38c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00038c1c) // Found @0xff023c4c
DEF(physw_run                               ,0x00001bf4) // Found @0xff0237dc
DEF(physw_sleep_delay                       ,0x00001bfc) // Found @0xff0237dc
DEF(levent_table                            ,0xff59e2ec) // Found @0xff59e2ec
DEF(FlashParamsTable                        ,0xff63a5f0) // Found @0xff63a5f0
DEF(movie_status                            ,0x00009de4) // Found @0xff1c8b6c
DEF(video_compression_rate                  ,0x00009e24) // Found @0xff1ca014
DEF(full_screen_refresh                     ,0x0000cda4) // Found @0xff29af08
DEF(canon_menu_active                       ,0x0000446c) // Found @0xff090558
DEF(canon_shoot_menu_active                 ,0x0000b4f9) // Found @0xff22c730
DEF(playrec_mode                            ,0x0000418c) // Found @0xff081e14
DEF(zoom_status                             ,0x0000b020) // Found @0xff21376c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 2 int value(s), the first is the zoom focus length.
// there are 101 entries in the table - set NUM_FL to 101
DEF(focus_len_table                         ,0xfff4a6c8) // Found @0xfff4a6c8
DEF(zoom_busy                               ,0x00009c9c) // Found @0xff1c3864
DEF(focus_busy                              ,0x00009aec) // Found @0xff1bd384
DEF(recreview_hold                          ,0x0000514c) // Found @0xff0a3198
// Palette colour tables  found @ 0xff5badb0
DEF(palette_control                         ,0x0000cda4) // Found @0xff29ae84
DEF(active_palette_buffer                   ,0x0000cdac) // Found @0xff29ae88
DEF(palette_buffer_ptr                      ,0x0000cdb0) // Found @0xff29b340
DEF(palette_buffer                          ,0x000cc858) // Found @0xff29b350
// Offset from start of palette_buffer to color data = 4 (Found @0xff3cb084)
DEF(bitmap_buffer                           ,0x0000cde8) // Found @0xff29eb94
DEF(active_bitmap_buffer                    ,0x0000cde0) // Found @0xff29eb98
DEF(viewport_buffers                        ,0xff464c7c) // Found @0xff045214
DEF(active_viewport_buffer                  ,0x00002150) // Found @0xff044ee8
// Camera has 2 RAW buffers @ 0x44000000 & 0x4a6ba6a0
//  Note: active buffer --> raw_buffers[active_raw_buffer]
//        other buffer  --> raw_buffers[active_raw_buffer^1]
DEF(raw_buffers                             ,0xff47686c) // Found @0xff47686c
DEF(active_raw_buffer                       ,0x000040dc) // Found @0xff07dad0

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40685000; }             // Found @0xff0501b8
//void *vid_get_viewport_fb()      { return (void*)0x407dab80; }             // Found @0xff408024
DEF(viewport_fb_d                           ,0x00003de8) // Found 0x3d90 (@0xff06e538) + 0x58 (@0xff06e570)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x3d90+0x58)); } // Found @0xff06e538 & 0xff06e570
DEF(jpeg_count_str                          ,0x000cc108) // Found @0xff28c9f0
//char *camera_jpeg_count_str()    { return (char*)0x000cc108; }             // Found @0xff28c9f0
//long hook_raw_size()             { return 0x01941be8; }                    // Found @0xff40ae40
//int get_flash_params_count(void) { return 0x9f; }                          // Found @0xff206780

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00000002 // Found @0xff465334, levent 0x20a
//#define SD_READONLY_IDX     1
//#define USB_MASK            0x10000000 // Found @0xff4653ac, levent 0x202
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SET             ,0x00000800 }, // Found @0xff4652bc, levent 0x08
//    { 0, KEY_RIGHT           ,0x00001000 }, // Found @0xff4652c4, levent 0x07
//    { 0, KEY_DOWN            ,0x00002000 }, // Found @0xff4652cc, levent 0x05
//    { 0, KEY_MENU            ,0x00004000 }, // Found @0xff4652d4, levent 0x09
//    { 0, KEY_LEFT            ,0x00008000 }, // Found @0xff4652dc, levent 0x06
//    { 0, KEY_UP              ,0x00040000 }, // Found @0xff4652f4, levent 0x04
//    { 0, KEY_VIDEO           ,0x00080000 }, // Found @0xff4652fc, levent 0x19
//    { 0, KEY_ZOOM_IN         ,0x00100000 }, // Found @0xff465304, levent 0x02
//    { 0, KEY_ZOOM_OUT        ,0x00200000 }, // Found @0xff46530c, levent 0x03
//    { 2, KEY_POWER           ,0x00000800 }, // Found @0xff46534c, levent 0x100
//    { 2, KEY_PLAYBACK        ,0x00008000 }, // Found @0xff46536c, levent 0x101
//    { 2, KEY_SHOOT_FULL      ,0x000c0000 }, // Found @0xff46537c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00080000 }, // Found @0xff46537c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00040000 }, // Found @0xff465374, levent 0x00
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_DRYOS_2_3_R47 1 // Defined for cameras with DryOS version R47 or higher
//#define CAM_RAW_ROWPIX    4496 // Found @0xff190cd0
//#define CAM_RAW_ROWS      3366 // Found @0xff190cdc
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff02ac74

// Misc stuff
DEF(ctypes, 0xff463fe6)

// For capt_seq.c
DEF(_nrflag,0xcec0) // Found @ ff2a79e4 (0xcebc) & ff2a7a20 (+0x04)
//static long *nrflag = (long*)(0xcebc+0x04);  // Found @ ff2a79e4 & ff2a7a20
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
NHSTUB(ExecuteEventProcedure                  ,0xff08b9f4) //104
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
NHSTUB(GetCurrentAvValue                      ,0xff1c02bc) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff06cbec) //122
NHSTUB(GetDrive_FreeClusters                  ,0xff06cc44) //119
NHSTUB(GetDrive_TotalClusters                 ,0xff06cc1c) //119
NHSTUB(GetFocusLensSubjectDistance            ,0xff1be100) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff1be550) //  3
NHSTUB(GetImageFolder                         ,0xff19a46c) //122
NHSTUB(GetKbdState                            ,0xff05726c) //109
NHSTUB(GetMemInfo                             ,0xff00a2b8) //115
NHSTUB(GetOpticalTemperature                  ,0xff05dea4) //120
NHSTUB(GetParameterData                       ,0xff206740) //101
NHSTUB(GetPropertyCase                        ,0xff08fa94) //102
NHSTUB(GetSystemTime                          ,0xff374da8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff047814) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff047820) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff1c3cdc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xff3612dc) //102
NHSTUB(GiveSemaphore                          ,0xff02a394) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff0f244c) //102
NHSTUB(LEDDrive                               ,0xff056488) //120
NHSTUB(LocalTime                              ,0xff0893b8) //115
NHSTUB(LockMainPower                          ,0xff096d5c) //120
NHSTUB(MakeDirectory_Fut                      ,0xff025de4) //116
NHSTUB(MakeSDCardBootable                     ,0xff06ce7c) //105
NHSTUB(MoveFocusLensToDistance                ,0xff40425c) //102
NHSTUB(MoveIrisWithAv                         ,0xff3714f8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff371e88) //120
NHSTUB(Open                                   ,0xff026390) //120
NHSTUB(PB2Rec                                 ,0xff09a108) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff078130) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff078108) //120
NHSTUB(PT_PlaySound                           ,0xff083e28) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xff0945c8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff094614) //120
NHSTUB(PutInNdFilter                          ,0xff371c60) //102
NHSTUB(PutOutNdFilter                         ,0xff371c84) //102
NHSTUB(Read                                   ,0xff00ad74) //120
NHSTUB(ReadFastDir                            ,0xff34cb58) //115
NHSTUB(Rec2PB                                 ,0xff09a148) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff0b308c) //104
NHSTUB(RenameFile_Fut                         ,0xff025cdc) //116
NHSTUB(Restart                                ,0xff02c444) //106
NHSTUB(ScreenLock                             ,0xff0b42b8) //117
NHSTUB(ScreenUnlock                           ,0xff0b431c) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xff40719c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff096dd0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff0a0284) //120
NHSTUB(SetFileAttributes                      ,0xff02685c) //  6
NHSTUB(SetFileTimeStamp                       ,0xff0267e4) //  6
NHSTUB(SetLogicalEventActive                  ,0xff096aa8) //101
NHSTUB(SetParameterData                       ,0xff20661c) //101
NHSTUB(SetPropertyCase                        ,0xff08f90c) //102
NHSTUB(SetScriptMode                          ,0xff096af8) //120
NHSTUB(SleepTask                              ,0xff02a640) //120
NHSTUB(TakeSemaphore                          ,0xff02a2c4) //120
NHSTUB(TurnOffBackLight                       ,0xff0aab7c) //104
NHSTUB(TurnOnBackLight                        ,0xff0aab64) //104
NHSTUB(TurnOnDisplay                          ,0xff050600) //120
NHSTUB(TurnOffDisplay                         ,0xff050610) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff1f0934) //120
NHSTUB(UnlockAE                               ,0xff02856c) //120
NHSTUB(UnlockAF                               ,0xff028108) //120
NHSTUB(UnlockMainPower                        ,0xff096cb0) //120
NHSTUB(VbattGet                               ,0xff022338) //120
NHSTUB(Write                                  ,0xff0264ac) //120
NHSTUB(WriteSDCard                            ,0xff1aeda4) //108
NHSTUB(_log                                   ,0xff4607d0) //111
NHSTUB(_log10                                 ,0xff460d10) //112
NHSTUB(_pow                                   ,0xff460e88) //121
NHSTUB(_sqrt                                  ,0xff462de8) //  6
NHSTUB(add_ptp_handler                        ,0xff2ebca4) //121
NHSTUB(apex2us                                ,0xff2a1360) //121
NHSTUB(close                                  ,0xff00abd0) //109
NHSTUB(err_init_task                          ,0xff00602c) //111
NHSTUB(exmem_alloc                            ,0xff08a378) //101
NHSTUB(exmem_free                             ,0xff08a3f0) //101
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
NHSTUB(memset                                 ,0xff29f384) //120
NHSTUB(mkdir                                  ,0xff0268f4) //109
NHSTUB(mktime_ext                             ,0xff0b51d4) //  1
NHSTUB(open                                   ,0xff00ab20) //109
NHSTUB(OpenFastDir                            ,0xff34ca04) //115
NHSTUB(closedir                               ,0xff34c9b4) //121
NHSTUB(qsort                                  ,0xff3cbc48) //  6
NHSTUB(rand                                   ,0xff29f4c0) //121
NHSTUB(realloc                                ,0xff29f400) //115
NHSTUB(reboot_fw_update                       ,0xff3522ac) //106
NHSTUB(set_control_event                      ,0xff09669c) //111
NHSTUB(srand                                  ,0xff29f4b4) //122
NHSTUB(stat                                   ,0xff0266bc) //109
NHSTUB(strcat                                 ,0xff0b498c) //  1
NHSTUB(strchr                                 ,0xff0040d8) //  1
NHSTUB(strcmp                                 ,0xff0109d8) //120
NHSTUB(strcpy                                 ,0xff0109c0) //120
NHSTUB(strftime                               ,0xff0b4bd4) //113
NHSTUB(strlen                                 ,0xff004124) //120
NHSTUB(strncmp                                ,0xff00408c) //  1
NHSTUB(strncpy                                ,0xff004050) //  1
NHSTUB(strrchr                                ,0xff0040fc) //  1
NHSTUB(strtol                                 ,0xff0307a4) //101
NHSTUB(strtolx                                ,0xff0305a8) //109
   DEF(task_CaptSeq                           ,0xff07b364) //120
   DEF(task_ExpDrv                            ,0xff0cda24) //120
   DEF(task_FileWrite                         ,0xff34a94c) //120
   DEF(task_InitFileModules                   ,0xff09a9ac) //120
   DEF(task_MovieRecord                       ,0xff1ca8a4) //120
   DEF(task_PhySw                             ,0xff0237d8) //120
   DEF(task_RotaryEncoder                     ,0xff0575cc) //120
NHSTUB(time                                   ,0xff089994) //109
NHSTUB(vsprintf                               ,0xff010980) //115
NHSTUB(EngDrvRead                             ,0xff024ac8) //102
