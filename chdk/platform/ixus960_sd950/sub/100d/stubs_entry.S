// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00D   // Found @ 0xff86890c, "GM1.00D" @ 0xff868919
//   Firmware build timestamp: Aug 23 2007 09:21:45
//   Canon DIGITAL IXUS 960 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12639 (0x315f) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000a6234
//   KEYSYS = d3                 // Found @ 0xffff31c8

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetCCDTemperature                    ,0xff846c74) //102        *** != 0xff846e08
//NHSTUB(GetOpticalTemperature                ,0xff846d54) //120        *** != 0xff846ce4
//NHSTUB(NewTaskShell                         ,0xff869278) //120        *** != 0xffc596b0
//NHSTUB(PutInNdFilter                        ,0xff928924) //102        *** != 0xff9e8ac4
//NHSTUB(PutOutNdFilter                       ,0xff928948) //102        *** != 0xff9e8afc
//NHSTUB(UIFS_WriteFirmInfoToFile             ,0xff983f58) //120        *** != 0xffd4a934
//NHSTUB(kbd_pwr_off                          ,0xff844630) //  2 67%    *** != 0xff844640
NHSTUB(kbd_pwr_on                             ,0xff8445f0) //  2 86%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa26630 -> ffad6ddc
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00014cfc) // Found @0xff823068
DEF(physw_run                               ,0x00001ca4) // Found @0xff822d18
DEF(physw_sleep_delay                       ,0x00001ca2) // Found @0xff822d18
DEF(levent_table                            ,0xffab3444) // Found @0xffab3444
DEF(FlashParamsTable                        ,0xffad6f9c) // Found @0xffad6f9c
DEF(movie_status                            ,0x00005524) // Found @0xff85824c
DEF(canon_menu_active                       ,0x0000f7d4) // Found @0xff983100
DEF(canon_shoot_menu_active                 ,0x0000ede5) // Found @0xff9546d0
DEF(playrec_mode                            ,0x000056d0) // Found @0xff85f234
DEF(zoom_status                             ,0x00011e48) // Found @0xffa27e28
DEF(some_flag_for_af_scan                   ,0x00011d80) // Found @0xffa20824
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe296c) // Found @0xfffe296c
DEF(zoom_busy                               ,0x0000de7c) // Found @0xff92a31c
//DEF(focus_busy                              ,0x0000dd78) // Found @0xff92513c, ** != ** stubs_min = 0x0000dd7c (0xDD7C)
//DEF(recreview_hold                          ,0x0000618c) // Found @0xff8774b4, ** != ** stubs_min = 0x0000ebfc (0xEBFC)
// Camera has 2 RAW buffers @ 0x108067a0 & 0x11f6c720
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffa95cc4) // Found @0xffa95cc4
DEF(active_raw_buffer                       ,0x00005670) // Found @0xff85c590

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff8404d8
//void *vid_get_viewport_fb()      { return (void*)0x1065b540; }             // Found @0xff9ed600
DEF(viewport_fb_d                           ,0x000053b8) // Found 0x5368 (@0xff851564) + 0x50 (@0xff85159c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x5368+0x50)); } // Found @0xff851564 & 0xff85159c
DEF(jpeg_count_str                          ,0x0005e288) // Found @0xff994a8c
//char *camera_jpeg_count_str()    { return (char*)0x0005e288; }             // Found @0xff994a8c
//long hook_raw_size()             { return 0x00ee9710; }                    // Found @0xff9ef4c4
//int get_flash_params_count(void) { return 0x72; }                          // Found @0xff945ea4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffa95924, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffa95930, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x40000000 }, // Found @0xffa95864, levent 0x601
//    { 0, KEY_POWER           ,0x80000000 }, // Found @0xffa95870, levent 0x600
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffa95888, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffa95888, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffa9587c, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffa95894, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffa958a0, levent 0x03
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffa958e8, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffa958f4, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4104 // Found @0xff9e79d8
//#define CAM_RAW_ROWS      3048 // Found @0xff9e79e0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff8298ec

// Misc stuff
DEF(ctypes, 0xffa95366)

// For capt_seq.c
DEF(_nrflag,0xe21c) // Found @ ff933c9c (0xe21c)
//static long *nrflag = (long*)(0xe21c);       // Found @ ff933c9c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff8298b0) //112
NHSTUB(Close                                  ,0xff824fc8) //120
NHSTUB(CreateTask                             ,0xff81baf0) //120
NHSTUB(DebugAssert                            ,0xff81bfc8) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff824914) //116
NHSTUB(DeleteFile_Fut                         ,0xff824830) //112
NHSTUB(DoAELock                               ,0xff827068) //120
NHSTUB(DoAFLock                               ,0xff826b54) //120
NHSTUB(EnterToCompensationEVF                 ,0xff826ec8) //104
NHSTUB(ExecuteEventProcedure                  ,0xff81c1a8) //104
NHSTUB(ExitFromCompensationEVF                ,0xff826f18) //104
NHSTUB(ExitTask                               ,0xff81bd80) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff834204) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff8343c4) //104
NHSTUB(Fclose_Fut                             ,0xff8249ac) //120
NHSTUB(Feof_Fut                               ,0xff824b98) //  1
NHSTUB(Fflush_Fut                             ,0xff824bd4) //  1
NHSTUB(Fgets_Fut                              ,0xff824b00) //  1
NHSTUB(Fopen_Fut                              ,0xff82496c) //120
NHSTUB(Fread_Fut                              ,0xff824a58) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8298e4) //112
NHSTUB(Fseek_Fut                              ,0xff824b4c) //120
NHSTUB(Fwrite_Fut                             ,0xff824aac) //120
NHSTUB(GetBatteryTemperature                  ,0xff846ce4) //102
NHSTUB(GetCurrentAvValue                      ,0xff9275c4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff84da50) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff84daf0) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff84da84) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff925c7c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff925f88) //  1
NHSTUB(GetKbdState                            ,0xff8445bc) //109
NHSTUB(GetMemInfo                             ,0xff813c58) //115
NHSTUB(GetParameterData                       ,0xff945e64) //  1
NHSTUB(GetPropertyCase                        ,0xff8697f4) //101
NHSTUB(GetSystemTime                          ,0xffa238c0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8c2660) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8c266c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff92a680) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa1abc8) //102
NHSTUB(GiveSemaphore                          ,0xff81ba5c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8b5978) //102
NHSTUB(LEDDrive                               ,0xff843bd8) //120
NHSTUB(LocalTime                              ,0xff8655c4) //115
NHSTUB(LockMainPower                          ,0xff86d3d0) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8248a4) //116
NHSTUB(MoveFocusLensToDistance                ,0xff9ea6b8) //102
NHSTUB(MoveIrisWithAv                         ,0xff927850) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff92b12c) //120
NHSTUB(Open                                   ,0xff824fa0) //120
NHSTUB(PB2Rec                                 ,0xff87058c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86096c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff860934) //120
NHSTUB(PT_PlaySound                           ,0xff8604e0) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xff86b218) //120
NHSTUB(PostLogicalEventToUI                   ,0xff86b264) //120
NHSTUB(Read                                   ,0xff81a378) //120
NHSTUB(ReadFastDir                            ,0xffa0a1bc) //  1
NHSTUB(Rec2PB                                 ,0xff86ef84) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9a0f54) //104
NHSTUB(RenameFile_Fut                         ,0xff8247dc) //  1
NHSTUB(Restart                                ,0xff82b90c) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xff9ec7b4) //102
NHSTUB(SetAutoShutdownTime                    ,0xff86d444) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff874e2c) //120
NHSTUB(SetFileAttributes                      ,0xff8252f4) //  1
NHSTUB(SetFileTimeStamp                       ,0xff8252a4) //  1
NHSTUB(SetLogicalEventActive                  ,0xff86d000) //  1
NHSTUB(SetParameterData                       ,0xff945dd4) //101
NHSTUB(SetPropertyCase                        ,0xff8696ec) //103
NHSTUB(SetScriptMode                          ,0xff86d050) //120
NHSTUB(SleepTask                              ,0xff829738) //120
NHSTUB(TakeSemaphore                          ,0xff81b98c) //120
NHSTUB(TurnOffBackLight                       ,0xff87a430) //104
NHSTUB(TurnOnBackLight                        ,0xff87a418) //104
NHSTUB(TurnOnDisplay                          ,0xff840588) //120
NHSTUB(TurnOffDisplay                         ,0xff840598) //120
NHSTUB(UnlockAE                               ,0xff8270a4) //120
NHSTUB(UnlockAF                               ,0xff826ba4) //120
NHSTUB(UnlockMainPower                        ,0xff86d324) //120
NHSTUB(UnsetZoomForMovie                      ,0xff94ca38) //104
NHSTUB(UpdateMBROnFlash                       ,0xff84d818) //105
NHSTUB(VbattGet                               ,0xff821944) //120
NHSTUB(Write                                  ,0xff825074) //120
NHSTUB(WriteSDCard                            ,0xff91a968) //108
NHSTUB(_log                                   ,0xffa92ed8) //111
NHSTUB(_log10                                 ,0xffa91e1c) //112
NHSTUB(_pow                                   ,0xffa91f8c) //121
NHSTUB(_sqrt                                  ,0xffa94240) //  1
NHSTUB(add_ptp_handler                        ,0xff8cc2b0) //121
NHSTUB(apex2us                                ,0xff9a240c) //121
NHSTUB(close                                  ,0xff81a190) //109
NHSTUB(err_init_task                          ,0xff814eb0) //111
NHSTUB(exmem_alloc                            ,0xff86670c) //102
NHSTUB(exmem_free                             ,0xff866784) //102
NHSTUB(free                                   ,0xff813ab0) //112
NHSTUB(kbd_p1_f                               ,0xff82316c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff823178) //109
NHSTUB(kbd_p2_f                               ,0xff8229b8) //109
NHSTUB(kbd_read_keys                          ,0xff823068) //109
NHSTUB(kbd_read_keys_r2                       ,0xff84415c) //109
NHSTUB(lseek                                  ,0xff825108) //120
NHSTUB(malloc                                 ,0xff8139dc) //112
NHSTUB(memcmp                                 ,0xff81e82c) //120
NHSTUB(memcpy                                 ,0xff88fdec) //120
NHSTUB(memset                                 ,0xffa614e4) //120
NHSTUB(mkdir                                  ,0xff82536c) //109
NHSTUB(mktime_ext                             ,0xff890658) //  1
NHSTUB(open                                   ,0xff81a0e0) //109
NHSTUB(OpenFastDir                            ,0xffa0a128) //  1
NHSTUB(closedir                               ,0xffa0a28c) //  1
NHSTUB(qsort                                  ,0xff9a17e4) //  1
NHSTUB(rand                                   ,0xff81e934) //121
NHSTUB(realloc                                ,0xff813b90) //115
NHSTUB(reboot_fw_update                       ,0xffa11b80) //106
NHSTUB(set_control_event                      ,0xff86ccec) //  1
NHSTUB(srand                                  ,0xff81e928) //122
NHSTUB(stat                                   ,0xff8251d4) //  1
NHSTUB(strcat                                 ,0xff88fd18) //  1
NHSTUB(strchr                                 ,0xff88fda0) //  1
NHSTUB(strcmp                                 ,0xff81e7c4) //120
NHSTUB(strcpy                                 ,0xff81e770) //120
NHSTUB(strftime                               ,0xff890060) //  1
NHSTUB(strlen                                 ,0xff81e808) //120
NHSTUB(strncmp                                ,0xff88fd54) //  1
NHSTUB(strncpy                                ,0xff81e788) //  1
NHSTUB(strrchr                                ,0xff88fdc4) //  1
NHSTUB(strtol                                 ,0xff82ff20) //101
NHSTUB(strtolx                                ,0xff82fd24) //109
   DEF(task_CaptSeq                           ,0xff85c038) //120
   DEF(task_ExpDrv                            ,0xff8af7b0) //120
   DEF(task_FileWrite                         ,0xffa082a4) //120
   DEF(task_InitFileModules                   ,0xff871070) //120
   DEF(task_MovieRecord                       ,0xff8584ec) //120
   DEF(task_PhySw                             ,0xff822d14) //120
NHSTUB(time                                   ,0xff865ac8) //109
NHSTUB(vsprintf                               ,0xff81e6f0) //115
NHSTUB(EngDrvRead                             ,0xff823f70) //102
