// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.00A   // Found @ 0xff870db8, "GM1.00A" @ 0xff870dc5
//   Firmware build timestamp: Feb 25 2009 18:42:06
//   Canon PowerShot D10

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12732 (0x31bc) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x00146a2c
//   KEYSYS = d4                 // Found @ 0xffff3564
//   NEED_ENCODED_DISKBOOT = 2   // Found @ 0xffff3574
//   ARAM_HEAP_START = 0x34e000  // Found @ 0xff93c6d8
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff93c698

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(DoAFLock                             ,0xff8255ec) //120        *** != 0xff85e914
//NHSTUB(EnterToCompensationEVF               ,0xff8256d8) //104        *** != 0x00000000
//NHSTUB(ExitFromCompensationEVF              ,0xff82571c) //104        *** != 0x00000000
//NHSTUB(UnlockAF                             ,0xff825624) //120        *** != 0xff85e924
//NHSTUB(exmem_free                           ,0xff86c888) //103        *** != 0xff86c7b0
//NHSTUB(kbd_pwr_off                          ,0xff8470e4) //  2 64%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa54a9c -> ffb32f18
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0000e238) // Found @0xff821de4
DEF(physw_run                               ,0x00001c38) // Found @0xff821a58
DEF(physw_sleep_delay                       ,0x00001c36) // Found @0xff821a58
DEF(levent_table                            ,0xffb08638) // Found @0xffb08638
DEF(FlashParamsTable                        ,0xffb330f4) // Found @0xffb330f4
DEF(movie_status                            ,0x00005fe0) // Found @0xff92f390
DEF(video_compression_rate                  ,0x0000600c) // Found @0xff92f54c
DEF(canon_menu_active                       ,0x00002e2c) // Found @0xff872820
DEF(canon_shoot_menu_active                 ,0x00007405) // Found @0xff96b630
DEF(playrec_mode                            ,0x00002b8c) // Found @0xff865a74
DEF(zoom_status                             ,0x0000ad70) // Found @0xffa56cc8
DEF(some_flag_for_af_scan                   ,0x00006508) // Found @0xff932628
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c
DEF(zoom_busy                               ,0x00005f10) // Found @0xff92b6a0
DEF(focus_busy                              ,0x00005e08) // Found @0xff9265c0
DEF(recreview_hold                          ,0x0000342c) // Found @0xff8819cc
// Palette colour tables  found @ 0xffb1b630
DEF(active_palette_buffer                   ,0x00008484) // Found @0xff9b4b60
DEF(palette_buffer_ptr                      ,0x00008494) // Found @0xff9b4838
// Offset from start of palette_buffer to color data = 12 (Found @0xff9b3914)
// Camera appears to have only 1 RAW buffer @ 0x41643dec (Found @0xffa9e638)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x403f1000; }             // Found @0xff842dc8
//void *vid_get_viewport_fb()      { return (void*)0x40a05158; }             // Found @0xffa9c12c
DEF(viewport_fb_d                           ,0x000028dc) // Found 0x2884 (@0xff8575b4) + 0x58 (@0xff8575f4)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2884+0x58)); } // Found @0xff8575b4 & 0xff8575f4
DEF(jpeg_count_str                          ,0x000525e4) // Found @0xff9abbc0
//char *camera_jpeg_count_str()    { return (char*)0x000525e4; }             // Found @0xff9abbc0
//long hook_raw_size()             { return 0x011e4ee0; }                    // Found @0xffa9e694
//int get_flash_params_count(void) { return 0x7a; }                          // Found @0xff95a4fc

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffad634c, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffad6358, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffad628c, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffad6298, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffad62b0, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffad62b0, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffad62a4, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffad62bc, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffad62c8, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffad62d4, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffad62e0, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffad62ec, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffad62f8, levent 0x04
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffad6304, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffad6310, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffad631c, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4104 // Found @0xff8fb074
//#define CAM_RAW_ROWS      3048 // Found @0xff8fb07c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff827744

// Misc stuff
DEF(ctypes, 0xffad03aa)

// For capt_seq.c
DEF(_nrflag,0x64e8) // Found @ ff9345d0 (0x64f0) & ff9345f0 (-0x08)
//static long *nrflag = (long*)(0x64f0-0x08);  // Found @ ff9345d0 & ff9345ec

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff827700) //112
NHSTUB(Close                                  ,0xff823cb0) //120
NHSTUB(CreateTask                             ,0xff81afac) //120
NHSTUB(DebugAssert                            ,0xff81b284) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823640) //116
NHSTUB(DeleteFile_Fut                         ,0xff82355c) //112
NHSTUB(DoAELock                               ,0xff825770) //120
NHSTUB(ExecuteEventProcedure                  ,0xff86df60) //104
NHSTUB(ExitTask                               ,0xff81b23c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff83024c) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff830390) //104
NHSTUB(Fclose_Fut                             ,0xff8236d8) //120
NHSTUB(Feof_Fut                               ,0xff8238c4) //  1
NHSTUB(Fflush_Fut                             ,0xff823900) //  1
NHSTUB(Fgets_Fut                              ,0xff82382c) //  1
NHSTUB(Fopen_Fut                              ,0xff823698) //120
NHSTUB(Fread_Fut                              ,0xff823784) //120
NHSTUB(FreeUncacheableMemory                  ,0xff827740) //112
NHSTUB(Fseek_Fut                              ,0xff823878) //120
NHSTUB(Fwrite_Fut                             ,0xff8237d8) //120
NHSTUB(GetBatteryTemperature                  ,0xff849844) //102
NHSTUB(GetCCDTemperature                      ,0xff8497d0) //102
NHSTUB(GetCurrentAvValue                      ,0xff928378) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff855d3c) //  5
NHSTUB(GetDrive_FreeClusters                  ,0xff855d94) //  5
NHSTUB(GetDrive_TotalClusters                 ,0xff855d68) //  5
NHSTUB(GetFocusLensSubjectDistance            ,0xff927428) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff927804) //  3
NHSTUB(GetKbdState                            ,0xff8470cc) //109
NHSTUB(GetMemInfo                             ,0xff813be4) //115
NHSTUB(GetOpticalTemperature                  ,0xff8498b8) //120
NHSTUB(GetParameterData                       ,0xff95a4bc) //101
NHSTUB(GetPropertyCase                        ,0xff871ccc) //102
NHSTUB(GetSystemTime                          ,0xffa4861c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff839b9c) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff839ba8) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff92ba1c) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa3c378) //102
NHSTUB(GiveSemaphore                          ,0xff82711c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8a74bc) //102
NHSTUB(LEDDrive                               ,0xff846818) //120
NHSTUB(LocalTime                              ,0xff86b950) //115
NHSTUB(LockMainPower                          ,0xff877d60) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8235d0) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa98b5c) //102
NHSTUB(MoveIrisWithAv                         ,0xffa46724) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa46cac) //120
NHSTUB(Open                                   ,0xff823c88) //120
NHSTUB(PB2Rec                                 ,0xff87ad90) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff85e8dc) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff85e8b4) //120
NHSTUB(PT_PlaySound                           ,0xff85e4ec) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff877388) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8773d4) //120
NHSTUB(PutInNdFilter                          ,0xffa46b10) //102
NHSTUB(PutOutNdFilter                         ,0xffa46b34) //102
NHSTUB(Read                                   ,0xff819ae4) //120
NHSTUB(ReadFastDir                            ,0xffa2a474) //  1
NHSTUB(Rec2PB                                 ,0xff8797fc) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9b96d0) //104
NHSTUB(RenameFile_Fut                         ,0xff823508) //  1
NHSTUB(Restart                                ,0xff828e54) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffa9b33c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff877dd4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87edec) //120
NHSTUB(SetFileAttributes                      ,0xff823fdc) //  1
NHSTUB(SetFileTimeStamp                       ,0xff823f8c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff877adc) //101
NHSTUB(SetParameterData                       ,0xff95a42c) //101
NHSTUB(SetPropertyCase                        ,0xff871bc4) //102
NHSTUB(SetScriptMode                          ,0xff877b2c) //120
NHSTUB(SleepTask                              ,0xff827384) //120
NHSTUB(TakeSemaphore                          ,0xff82704c) //120
NHSTUB(TurnOffBackLight                       ,0xff88527c) //104
NHSTUB(TurnOnBackLight                        ,0xff885264) //104
NHSTUB(TurnOnDisplay                          ,0xff842e90) //120
NHSTUB(TurnOffDisplay                         ,0xff842ea0) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff94656c) //120
NHSTUB(UnlockAE                               ,0xff825794) //120
NHSTUB(UnlockMainPower                        ,0xff877cb4) //120
NHSTUB(UnsetZoomForMovie                      ,0xff960e78) //104
NHSTUB(UpdateMBROnFlash                       ,0xff855b94) //105
NHSTUB(VbattGet                               ,0xff820690) //120
NHSTUB(Write                                  ,0xff823d5c) //120
NHSTUB(WriteSDCard                            ,0xff918b18) //108
NHSTUB(_log                                   ,0xffacd640) //111
NHSTUB(_log10                                 ,0xffacc2cc) //112
NHSTUB(_pow                                   ,0xffacc43c) //121
NHSTUB(_sqrt                                  ,0xffacf1e4) //  1
NHSTUB(add_ptp_handler                        ,0xff9f4f54) //121
NHSTUB(apex2us                                ,0xff9ba774) //121
NHSTUB(close                                  ,0xff8198fc) //109
NHSTUB(err_init_task                          ,0xff814e2c) //111
NHSTUB(exmem_alloc                            ,0xff86c810) //103
NHSTUB(free                                   ,0xff813a3c) //112
NHSTUB(kbd_p1_f                               ,0xff821e60) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821e6c) //109
NHSTUB(kbd_p2_f                               ,0xff821724) //109
NHSTUB(kbd_read_keys                          ,0xff821de4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff846b8c) //109
NHSTUB(lseek                                  ,0xff823df0) //120
NHSTUB(malloc                                 ,0xff813968) //112
NHSTUB(memcmp                                 ,0xff81cc60) //120
NHSTUB(memcpy                                 ,0xff88b7f4) //120
NHSTUB(memset                                 ,0xff9b9a5c) //120
NHSTUB(mkdir                                  ,0xff824054) //109
NHSTUB(mktime_ext                             ,0xff88c060) //  1
NHSTUB(open                                   ,0xff81984c) //109
NHSTUB(OpenFastDir                            ,0xffa2a3e0) //  1
NHSTUB(closedir                               ,0xffa2a544) //  1
NHSTUB(qsort                                  ,0xffa83b3c) //  1
NHSTUB(rand                                   ,0xff81cd68) //121
NHSTUB(realloc                                ,0xff813b1c) //115
NHSTUB(reboot_fw_update                       ,0xffa31b24) //106
NHSTUB(set_control_event                      ,0xff877810) //111
NHSTUB(srand                                  ,0xff81cd5c) //122
NHSTUB(stat                                   ,0xff823ebc) //  1
NHSTUB(strcat                                 ,0xff88b608) //  1
NHSTUB(strchr                                 ,0xff88b690) //  1
NHSTUB(strcmp                                 ,0xff81cbf8) //120
NHSTUB(strcpy                                 ,0xff81cbe0) //120
NHSTUB(strftime                               ,0xff88ba68) //  1
NHSTUB(strlen                                 ,0xff81cc3c) //120
NHSTUB(strncmp                                ,0xff88b644) //  1
NHSTUB(strncpy                                ,0xff82d048) //  1
NHSTUB(strrchr                                ,0xff9b9a34) //  1
NHSTUB(strtol                                 ,0xff82d280) //101
NHSTUB(strtolx                                ,0xff82d084) //109
   DEF(task_CaptSeq                           ,0xff860f34) //120
   DEF(task_ExpDrv                            ,0xff89dc5c) //120
   DEF(task_FileWrite                         ,0xffa25fb4) //120
   DEF(task_InitFileModules                   ,0xff87b84c) //120
   DEF(task_MovieRecord                       ,0xff92f5c8) //120
   DEF(task_PhySw                             ,0xff821a54) //120
NHSTUB(time                                   ,0xff86bec8) //109
NHSTUB(vsprintf                               ,0xff81cba4) //115
NHSTUB(EngDrvRead                             ,0xff822c9c) //102
