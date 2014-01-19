// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00C   // Found @ 0xffc58d44, "GM1.00C" @ 0xffc58d51
//   Firmware build timestamp: Jul  5 2007 11:32:58
//   Canon PowerShot A720 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12637 (0x315d) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009d024
//   KEYSYS = d3                 // Found @ 0xffff1aa4

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetZoomLensCurrentPosition           ,0xffdd0040) //102        *** != 0xffd03b5c
//NHSTUB(SetPropertyCase                      ,0xffc59b24) //103        *** != 0xffc50cc8
//NHSTUB(write                                ,0xffc150d8) //120        *** != 0xffc0a4a8

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffddc128 -> ffe7cffc
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0001061c) // Found @0xffc130cc
DEF(physw_run                               ,0x00001ca4) // Found @0xffc12d7c
DEF(physw_sleep_delay                       ,0x00001ca2) // Found @0xffc12d7c
DEF(levent_table                            ,0xffe60474) // Found @0xffe60474
DEF(FlashParamsTable                        ,0xffe7d1b4) // Found @0xffe7d1b4
DEF(movie_status                            ,0x00005570) // Found @0xffc498b4
DEF(canon_menu_active                       ,0x0000b55c) // Found @0xffd49f2c
DEF(canon_shoot_menu_active                 ,0x0000ae15) // Found @0xffd2b690
DEF(playrec_mode                            ,0x00005704) // Found @0xffc4fcb4
DEF(zoom_status                             ,0x0000d7c4) // Found @0xffddd920
DEF(some_flag_for_af_scan                   ,0x0000d688) // Found @0xffdd48c0
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 15 entries in the table - set NUM_FL to 15
DEF(focus_len_table                         ,0xfffe299c) // Found @0xfffe299c
DEF(zoom_busy                               ,0x00009dc0) // Found @0xffd02c78
//DEF(focus_busy                              ,0x00009cb8) // Found @0xffcfcffc, ** != ** stubs_min = 0x00009d50 (0x9D50)
//DEF(recreview_hold                          ,0x00005dc0) // Found @0xffc64708, ** != ** stubs_min = 0x0000abe8 (0xABE8)
// Camera appears to have only 1 RAW buffer @ 0x10f6c860 (Found @0xffdab258)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc32c24
//void *vid_get_viewport_fb()      { return (void*)0x1065a4d0; }             // Found @0xffda95c4
DEF(viewport_fb_d                           ,0x00005410) // Found 0x53c4 (@0xffc42ec8) + 0x4c (@0xffc42f00)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x53c4+0x4c)); } // Found @0xffc42ec8 & 0xffc42f00
DEF(jpeg_count_str                          ,0x000580cc) // Found @0xffd55dcc
//char *camera_jpeg_count_str()    { return (char*)0x000580cc; }             // Found @0xffd55dcc
//long hook_raw_size()             { return 0x009dcce0; }                    // Found @0xffdab2b4
//int get_flash_params_count(void) { return 0x72; }                          // Found @0xffd1c5f8

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffe44040, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffe44048, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x00004000 }, // Found @0xffe43f60, levent 0x600 (uses inverted logic in physw_status)
//    { 1, KEY_SHOOT_FULL      ,0xc0000000 }, // Found @0xffe43fb0, levent 0x01
//    { 1, KEY_SHOOT_FULL_ONLY ,0x80000000 }, // Found @0xffe43fb0, levent 0x01
//    { 1, KEY_SHOOT_HALF      ,0x40000000 }, // Found @0xffe43fa8, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffe43fc8, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffe43fd0, levent 0x03
//    { 2, KEY_UP              ,0x00000010 }, // Found @0xffe43fd8, levent 0x04
//    { 2, KEY_DOWN            ,0x00000020 }, // Found @0xffe43fe0, levent 0x05
//    { 2, KEY_RIGHT           ,0x00000040 }, // Found @0xffe43fe8, levent 0x07
//    { 2, KEY_LEFT            ,0x00000080 }, // Found @0xffe43ff0, levent 0x06
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe43ff8, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffe44000, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffe44008, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3336 // Found @0xffda3720
//#define CAM_RAW_ROWS      2480 // Found @0xffda3728
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc19884

// Misc stuff
DEF(ctypes, 0xffe3ead6)

// For capt_seq.c
DEF(_nrflag,0x9f90) // Found @ ffd0a438 (0x9f90)
//static long *nrflag = (long*)(0x9f90);       // Found @ ffd0a438

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc19848) //112
NHSTUB(Close                                  ,0xffc1502c) //120
NHSTUB(CreateTask                             ,0xffc0bbc0) //120
NHSTUB(DebugAssert                            ,0xffc0c098) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc14978) //116
NHSTUB(DeleteFile_Fut                         ,0xffc14894) //112
NHSTUB(DoAELock                               ,0xffc17238) //120
NHSTUB(DoAFLock                               ,0xffc16d2c) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc170a4) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc0c278) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc170f4) //104
NHSTUB(ExitTask                               ,0xffc0be50) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc23930) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc23a2c) //104
NHSTUB(Fclose_Fut                             ,0xffc14a10) //120
NHSTUB(Feof_Fut                               ,0xffc14bfc) //  1
NHSTUB(Fflush_Fut                             ,0xffc14c38) //  1
NHSTUB(Fgets_Fut                              ,0xffc14b64) //  1
NHSTUB(Fopen_Fut                              ,0xffc149d0) //120
NHSTUB(Fread_Fut                              ,0xffc14abc) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc1987c) //112
NHSTUB(Fseek_Fut                              ,0xffc14bb0) //120
NHSTUB(Fwrite_Fut                             ,0xffc14b10) //120
NHSTUB(GetBatteryTemperature                  ,0xffc39178) //102
NHSTUB(GetCCDTemperature                      ,0xffc39108) //102
NHSTUB(GetCurrentAvValue                      ,0xffcffca8) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc3f4c4) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xffc3f564) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xffc3f4f8) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xffcfdb3c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffcfde48) //  1
NHSTUB(GetKbdState                            ,0xffc37034) //109
NHSTUB(GetMemInfo                             ,0xffc03c58) //115
NHSTUB(GetOpticalTemperature                  ,0xffc391e8) //120
NHSTUB(GetParameterData                       ,0xffd1c5b8) //101
NHSTUB(GetPropertyCase                        ,0xffc59c2c) //101
NHSTUB(GetSystemTime                          ,0xffdd7efc) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffc2bbf8) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffc2bc04) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd02fdc) //120
NHSTUB(GiveSemaphore                          ,0xffc0bb2c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffc974e4) //102
NHSTUB(LEDDrive                               ,0xffc36638) //120
NHSTUB(LocalTime                              ,0xffc56058) //115
NHSTUB(LockMainPower                          ,0xffc5bf6c) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc14908) //116
NHSTUB(MoveFocusLensToDistance                ,0xffda6578) //102
NHSTUB(MoveIrisWithAv                         ,0xffd00088) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffd03a88) //120
NHSTUB(Open                                   ,0xffc15004) //120
NHSTUB(PB2Rec                                 ,0xffc5ecf8) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc513cc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc51394) //120
NHSTUB(PT_PlaySound                           ,0xffc50f40) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc5b650) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc5b69c) //120
NHSTUB(PutInNdFilter                          ,0xffda4a98) //102
NHSTUB(PutOutNdFilter                         ,0xffda4ad0) //102
NHSTUB(Read                                   ,0xffc0a448) //120
NHSTUB(ReadFastDir                            ,0xffdc1b98) //  1
NHSTUB(Rec2PB                                 ,0xffc5ed28) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd62184) //104
NHSTUB(RenameFile_Fut                         ,0xffc14840) //  1
NHSTUB(Restart                                ,0xffc1b8a4) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffda87c0) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc5bfe0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc6214c) //120
NHSTUB(SetFileAttributes                      ,0xffc15358) //  1
NHSTUB(SetFileTimeStamp                       ,0xffc15308) //  1
NHSTUB(SetLogicalEventActive                  ,0xffc5bcd0) //  1
NHSTUB(SetParameterData                       ,0xffd1c528) //101
NHSTUB(SetScriptMode                          ,0xffc5bd20) //120
NHSTUB(SleepTask                              ,0xffc196d0) //120
NHSTUB(TakeSemaphore                          ,0xffc0ba5c) //120
NHSTUB(TurnOffBackLight                       ,0xffc676f4) //104
NHSTUB(TurnOnBackLight                        ,0xffc676dc) //104
NHSTUB(TurnOnDisplay                          ,0xffc32cd4) //120
NHSTUB(TurnOffDisplay                         ,0xffc32ce4) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd4a934) //120
NHSTUB(UnlockAE                               ,0xffc17274) //120
NHSTUB(UnlockAF                               ,0xffc16d7c) //120
NHSTUB(UnlockMainPower                        ,0xffc5bec0) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd22418) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc3f28c) //105
NHSTUB(VbattGet                               ,0xffc119a8) //120
NHSTUB(Write                                  ,0xffc150d8) //120
NHSTUB(WriteSDCard                            ,0xffcf51b0) //108
NHSTUB(_log                                   ,0xffe3c8dc) //111
NHSTUB(_log10                                 ,0xffe3b820) //112
NHSTUB(_pow                                   ,0xffe3b990) //121
NHSTUB(_sqrt                                  ,0xffe3dc44) //  1
NHSTUB(add_ptp_handler                        ,0xffcad7d0) //121
NHSTUB(apex2us                                ,0xffd6363c) //121
NHSTUB(close                                  ,0xffc0a260) //109
NHSTUB(err_init_task                          ,0xffc04eb0) //111
NHSTUB(exmem_alloc                            ,0xffc56b44) //102
NHSTUB(exmem_free                             ,0xffc56bbc) //102
NHSTUB(free                                   ,0xffc03ab0) //112
NHSTUB(kbd_p1_f                               ,0xffc131d0) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc131dc) //109
NHSTUB(kbd_p2_f                               ,0xffc12a1c) //109
NHSTUB(kbd_read_keys                          ,0xffc130cc) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc36b14) //109
NHSTUB(kbd_pwr_off                            ,0xffc370c0) //  1
NHSTUB(kbd_pwr_on                             ,0xffc37068) //  1
NHSTUB(lseek                                  ,0xffc1516c) //120
NHSTUB(malloc                                 ,0xffc039dc) //112
NHSTUB(memcmp                                 ,0xffc0e8f0) //120
NHSTUB(memcpy                                 ,0xffc71bf4) //120
NHSTUB(memset                                 ,0xffe0e37c) //120
NHSTUB(mkdir                                  ,0xffc153d0) //109
NHSTUB(mktime_ext                             ,0xffc72460) //  1
NHSTUB(open                                   ,0xffc0a1b0) //109
NHSTUB(OpenFastDir                            ,0xffdc1b04) //  1
NHSTUB(closedir                               ,0xffdc1c68) //  1
NHSTUB(qsort                                  ,0xffd62a14) //  1
NHSTUB(rand                                   ,0xffc0e9f8) //121
NHSTUB(realloc                                ,0xffc03b90) //115
NHSTUB(reboot_fw_update                       ,0xffdc6538) //106
NHSTUB(set_control_event                      ,0xffc5baa4) //  1
NHSTUB(srand                                  ,0xffc0e9ec) //122
NHSTUB(stat                                   ,0xffc15238) //  1
NHSTUB(strcat                                 ,0xffc71b20) //  1
NHSTUB(strchr                                 ,0xffc71ba8) //  1
NHSTUB(strcmp                                 ,0xffc0e888) //120
NHSTUB(strcpy                                 ,0xffc0e834) //120
NHSTUB(strftime                               ,0xffc71e68) //  1
NHSTUB(strlen                                 ,0xffc0e8cc) //120
NHSTUB(strncmp                                ,0xffc71b5c) //  1
NHSTUB(strncpy                                ,0xffc0e84c) //  1
NHSTUB(strrchr                                ,0xffc71bcc) //  1
NHSTUB(strtol                                 ,0xffc1fc0c) //101
NHSTUB(strtolx                                ,0xffc1fa10) //109
   DEF(task_CaptSeq                           ,0xffc4cb64) //120
   DEF(task_ExpDrv                            ,0xffc91454) //120
   DEF(task_FileWrite                         ,0xffdbfc80) //120
   DEF(task_InitFileModules                   ,0xffc5f754) //120
   DEF(task_MovieRecord                       ,0xffc49b18) //120
   DEF(task_PhySw                             ,0xffc12d78) //120
NHSTUB(time                                   ,0xffc55f0c) //109
NHSTUB(vsprintf                               ,0xffc0e7b4) //115
NHSTUB(EngDrvRead                             ,0xffc13fd4) //102
