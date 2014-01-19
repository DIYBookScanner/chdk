// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.01A   // Found @ 0xff870898, "GM1.01A" @ 0xff8708a5
//   Firmware build timestamp: Oct 15 2008 18:36:07
//   Canon DIGITAL IXUS 870 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12694 (0x3196) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000de578
//   KEYSYS = d4                 // Found @ 0xffff3554
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff3564
//   ARAM_HEAP_START = 0x30e000  // Found @ 0xff93fc9c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff93fc5c

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetDrive_TotalClusters               ,0xff8554e0) //  1        *** != 0xff85557c
//NHSTUB(kbd_pwr_off                          ,0xff846260) //  2 64%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa4b9b4 -> ffb2d2fc
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00011078) // Found @0xff821ba4
DEF(physw_run                               ,0x00001c28) // Found @0xff821818
DEF(physw_sleep_delay                       ,0x00001c26) // Found @0xff821818
DEF(levent_table                            ,0xffb07270) // Found @0xffb07270
DEF(FlashParamsTable                        ,0xffb2d4d0) // Found @0xffb2d4d0
DEF(movie_status                            ,0x000051e4) // Found @0xff85dd18
DEF(video_compression_rate                  ,0x00005210) // Found @0xff85dfc0
DEF(canon_menu_active                       ,0x00005610) // Found @0xff872298
DEF(canon_shoot_menu_active                 ,0x0000a161) // Found @0xff96aa10
DEF(playrec_mode                            ,0x00005398) // Found @0xff865b40
DEF(zoom_status                             ,0x0000d570) // Found @0xffa4d1c8
DEF(some_flag_for_af_scan                   ,0x00009280) // Found @0xff933ca0
DEF(zoom_busy                               ,0x000088b4) // Found @0xff92b65c
DEF(focus_busy                              ,0x000087ac) // Found @0xff926640
//DEF(recreview_hold                          ,0x00005f94) // Found @0xff882adc, ** != ** stubs_min = 0x00009e9c (0x9E18+0x84)
// Camera has 2 RAW buffers @ 0x412007fc & 0x429aaa2c
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffad77b4) // Found @0xffad77b4
DEF(active_raw_buffer                       ,0x0000533c) // Found @0xff86322c

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403b1000; }             // Found @0xff841de0
//void *vid_get_viewport_fb()      { return (void*)0x40a2f2d0; }             // Found @0xffaa19b8
DEF(viewport_fb_d                           ,0x00005074) // Found 0x501c (@0xff856d80) + 0x58 (@0xff856db8)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x501c+0x58)); } // Found @0xff856d80 & 0xff856db8
DEF(jpeg_count_str                          ,0x0004a980) // Found @0xff9ad200
//char *camera_jpeg_count_str()    { return (char*)0x0004a980; }             // Found @0xff9ad200
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffaa3d98
//int get_flash_params_count(void) { return 0x78; }                          // Found @0xff95a7b0

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffad7034, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffad7040, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffad6f74, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffad6f80, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffad6f98, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffad6f98, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffad6f8c, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffad6fa4, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffad6fb0, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffad6fbc, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffad6fc8, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffad6fd4, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffad6fe0, levent 0x04
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffad6fec, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffad6ff8, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffad7004, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffa9ac80
//#define CAM_RAW_ROWS      2772 // Found @0xffa9ac88
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff827bac

// Misc stuff
DEF(ctypes, 0xffad5eda)

// For capt_seq.c
DEF(_nrflag,0x9268) // Found @ ff935c18 (0x926c) & ff935c34 (-0x04)
//static long *nrflag = (long*)(0x926c-0x04);  // Found @ ff935c18 & ff935c30

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff827b68) //112
NHSTUB(Close                                  ,0xff823af4) //120
NHSTUB(CreateTask                             ,0xff81aef4) //120
NHSTUB(DebugAssert                            ,0xff81b1cc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823484) //116
NHSTUB(DeleteFile_Fut                         ,0xff8233a0) //112
NHSTUB(DoAELock                               ,0xff8258c4) //120
NHSTUB(DoAFLock                               ,0xff8255d8) //120
NHSTUB(EnterToCompensationEVF                 ,0xff82582c) //104
NHSTUB(ExecuteEventProcedure                  ,0xff86dac0) //104
NHSTUB(ExitFromCompensationEVF                ,0xff825870) //104
NHSTUB(ExitTask                               ,0xff81b184) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff830d00) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff830e44) //104
NHSTUB(Fclose_Fut                             ,0xff82351c) //120
NHSTUB(Feof_Fut                               ,0xff823708) //  1
NHSTUB(Fflush_Fut                             ,0xff823744) //  1
NHSTUB(Fgets_Fut                              ,0xff823670) //  1
NHSTUB(Fopen_Fut                              ,0xff8234dc) //120
NHSTUB(Fread_Fut                              ,0xff8235c8) //120
NHSTUB(FreeUncacheableMemory                  ,0xff827ba8) //112
NHSTUB(Fseek_Fut                              ,0xff8236bc) //120
NHSTUB(Fwrite_Fut                             ,0xff82361c) //120
NHSTUB(GetBatteryTemperature                  ,0xff848cf4) //102
NHSTUB(GetCCDTemperature                      ,0xff848c84) //102
NHSTUB(GetCurrentAvValue                      ,0xff928280) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff8554ac) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff855514) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff927344) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff92772c) //  3
NHSTUB(GetKbdState                            ,0xff846248) //109
NHSTUB(GetMemInfo                             ,0xff813c24) //115
NHSTUB(GetOpticalTemperature                  ,0xff848d64) //120
NHSTUB(GetParameterData                       ,0xff95a770) //101
NHSTUB(GetPropertyCase                        ,0xff8717a8) //102
NHSTUB(GetSystemTime                          ,0xffa3d910) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8c4160) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8c416c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff92b9cc) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa337f0) //102
NHSTUB(GiveSemaphore                          ,0xff827584) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8ab714) //102
NHSTUB(LEDDrive                               ,0xff8459e8) //120
NHSTUB(LocalTime                              ,0xff86b25c) //115
NHSTUB(LockMainPower                          ,0xff878ec8) //120
NHSTUB(MakeDirectory_Fut                      ,0xff823414) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa9e3fc) //102
NHSTUB(MoveIrisWithAv                         ,0xffa3a93c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa3aec4) //120
NHSTUB(Open                                   ,0xff823acc) //120
NHSTUB(PB2Rec                                 ,0xff87bf0c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff85f93c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff85f914) //120
NHSTUB(PT_PlaySound                           ,0xff85f28c) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff876ca4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff876cf0) //120
NHSTUB(PutInNdFilter                          ,0xffa3ad28) //102
NHSTUB(PutOutNdFilter                         ,0xffa3ad4c) //102
NHSTUB(Read                                   ,0xff819a4c) //120
NHSTUB(ReadFastDir                            ,0xffa21ca0) //  1
NHSTUB(Rec2PB                                 ,0xff87a8a4) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9b8424) //104
NHSTUB(RenameFile_Fut                         ,0xff82334c) //  1
NHSTUB(Restart                                ,0xff8293dc) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffaa0bc8) //102
NHSTUB(SetAutoShutdownTime                    ,0xff878f3c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff8800bc) //120
NHSTUB(SetFileAttributes                      ,0xff823e20) //  1
NHSTUB(SetFileTimeStamp                       ,0xff823dd0) //  1
NHSTUB(SetLogicalEventActive                  ,0xff878c18) //101
NHSTUB(SetParameterData                       ,0xff95a6e0) //101
NHSTUB(SetPropertyCase                        ,0xff8716a0) //102
NHSTUB(SetScriptMode                          ,0xff878c68) //120
NHSTUB(SleepTask                              ,0xff8277ec) //120
NHSTUB(TakeSemaphore                          ,0xff8274b4) //120
NHSTUB(TurnOffBackLight                       ,0xff886078) //104
NHSTUB(TurnOnBackLight                        ,0xff886060) //104
NHSTUB(TurnOnDisplay                          ,0xff841ea8) //120
NHSTUB(TurnOffDisplay                         ,0xff841eb8) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff94b858) //120
NHSTUB(UnlockAE                               ,0xff8258e8) //120
NHSTUB(UnlockAF                               ,0xff825610) //120
NHSTUB(UnlockMainPower                        ,0xff878e1c) //120
NHSTUB(UnsetZoomForMovie                      ,0xff9607a0) //104
NHSTUB(UpdateMBROnFlash                       ,0xff8552ec) //105
NHSTUB(VbattGet                               ,0xff820570) //120
NHSTUB(Write                                  ,0xff823ba0) //120
NHSTUB(WriteSDCard                            ,0xff918858) //108
NHSTUB(_log                                   ,0xffad3158) //111
NHSTUB(_log10                                 ,0xffad1de4) //112
NHSTUB(_pow                                   ,0xffad1f54) //121
NHSTUB(_sqrt                                  ,0xffad4db4) //  1
NHSTUB(add_ptp_handler                        ,0xff9ef744) //121
NHSTUB(apex2us                                ,0xff9b9440) //121
NHSTUB(close                                  ,0xff819864) //109
NHSTUB(err_init_task                          ,0xff814e80) //111
NHSTUB(exmem_alloc                            ,0xff86c19c) //103
NHSTUB(exmem_free                             ,0xff86c214) //103
NHSTUB(free                                   ,0xff813a7c) //112
NHSTUB(kbd_p1_f                               ,0xff821ca0) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821cac) //109
NHSTUB(kbd_p2_f                               ,0xff8214b8) //109
NHSTUB(kbd_read_keys                          ,0xff821ba4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff845de0) //109
NHSTUB(lseek                                  ,0xff823c34) //120
NHSTUB(malloc                                 ,0xff8139a8) //112
NHSTUB(memcmp                                 ,0xff81cbb4) //120
NHSTUB(memcpy                                 ,0xff8928f4) //120
NHSTUB(memset                                 ,0xff9b8778) //120
NHSTUB(mkdir                                  ,0xff823e98) //109
NHSTUB(mktime_ext                             ,0xff893160) //  1
NHSTUB(open                                   ,0xff8197b4) //109
NHSTUB(OpenFastDir                            ,0xffa21c0c) //  1
NHSTUB(closedir                               ,0xffa21d70) //  1
NHSTUB(qsort                                  ,0xffa84fc8) //  1
NHSTUB(rand                                   ,0xff81ccbc) //121
NHSTUB(realloc                                ,0xff813b5c) //115
NHSTUB(reboot_fw_update                       ,0xffa296a0) //106
NHSTUB(set_control_event                      ,0xff878894) //111
NHSTUB(srand                                  ,0xff81ccb0) //122
NHSTUB(stat                                   ,0xff823d00) //  1
NHSTUB(strcat                                 ,0xff892708) //  1
NHSTUB(strchr                                 ,0xff892790) //  1
NHSTUB(strcmp                                 ,0xff81cb4c) //120
NHSTUB(strcpy                                 ,0xff81cb34) //120
NHSTUB(strftime                               ,0xff892b68) //  1
NHSTUB(strlen                                 ,0xff81cb90) //120
NHSTUB(strncmp                                ,0xff892744) //  1
NHSTUB(strncpy                                ,0xff82d678) //  1
NHSTUB(strrchr                                ,0xff9b8750) //  1
NHSTUB(strtol                                 ,0xff82d8b0) //101
NHSTUB(strtolx                                ,0xff82d6b4) //109
   DEF(task_CaptSeq                           ,0xff861cfc) //120
   DEF(task_ExpDrv                            ,0xff8a4608) //120
   DEF(task_FileWrite                         ,0xffa1e5c0) //120
   DEF(task_InitFileModules                   ,0xff87c980) //120
   DEF(task_MovieRecord                       ,0xff85e03c) //120
   DEF(task_PhySw                             ,0xff821814) //120
   DEF(task_RotaryEncoder                     ,0xff846338) //120
NHSTUB(time                                   ,0xff86b83c) //109
NHSTUB(vsprintf                               ,0xff81caf8) //115
NHSTUB(EngDrvRead                             ,0xff822ae0) //102
