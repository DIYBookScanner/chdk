// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00C   // Found @ 0xff86c370, "GM1.00C" @ 0xff86c37d
//   Firmware build timestamp: Jan  8 2008 14:58:32
//   Possible corrupt firmware dump - file size too small for start address 0xff810000
//     file size = 4.00MB, should be 7.94MB
//   Could not find Camera name - possible corrupt firmware dump

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = ?           // Not found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000cbc48
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffa2d9c8
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffa2d988

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(PutInNdFilter                        ,0xffa299b4) //102        *** != 0xffa82748
//NHSTUB(PutOutNdFilter                       ,0xffa299d8) //102        *** != 0xffa82780

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa3dc5c -> ffaf7e70
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00010610) // Found @0xff821e48
DEF(physw_run                               ,0x00001c00) // Found @0xff821ae0
DEF(physw_sleep_delay                       ,0x00001bfe) // Found @0xff821ae0
DEF(levent_table                            ,0xffad2ce8) // Found @0xffad2ce8
DEF(FlashParamsTable                        ,0xffaf8034) // Found @0xffaf8034
DEF(movie_status                            ,0x000053cc) // Found @0xff859fec
DEF(canon_menu_active                       ,0x000099e8) // Found @0xff94fe8c
DEF(canon_shoot_menu_active                 ,0x00009fcd) // Found @0xff96c438
DEF(playrec_mode                            ,0x0000555c) // Found @0xff8613c4
DEF(zoom_status                             ,0x0000d474) // Found @0xffa3f45c
DEF(some_flag_for_af_scan                   ,0x0000d1f8) // Found @0xffa2a32c
DEF(zoom_busy                               ,0x00008a88) // Found @0xff932810
DEF(focus_busy                              ,0x00008994) // Found @0xff92e3bc
//DEF(recreview_hold                          ,0x000061a4) // Found @0xff87ee14, ** != ** stubs_min = 0x00009da4 (0x9CF8+0xAC)
// Camera has 2 RAW buffers @ 0x107d68c0 & 0x11b97b60
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffab0cb8) // Found @0xffab0cb8
DEF(active_raw_buffer                       ,0x0000550c) // Found @0xff85e86c

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff83e9ac
//void *vid_get_viewport_fb()      { return (void*)0x1065adc0; }             // Found @0xffa87980
DEF(viewport_fb_d                           ,0x0000524c) // Found 0x51fc (@0xff8532b8) + 0x50 (@0xff8532f0)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x51fc+0x50)); } // Found @0xff8532b8 & 0xff8532f0
DEF(jpeg_count_str                          ,0x0004c97c) // Found @0xff9a66f4
//char *camera_jpeg_count_str()    { return (char*)0x0004c97c; }             // Found @0xff9a66f4
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffa89c04
//int get_flash_params_count(void) { return 0x73; }                          // Found @0xff95d668

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffab0784, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffab0790, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffab06c4, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffab06d0, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffab06e8, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffab06e8, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffab06dc, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffab06f4, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffab0700, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffab070c, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffab0718, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffab0724, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffab0730, levent 0x04
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffab073c, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffab0748, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffab0754, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffa812b0
//#define CAM_RAW_ROWS      2772 // Found @0xffa812b8
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff8285b8

// Misc stuff
DEF(ctypes, 0xffab025e)

// For capt_seq.c
DEF(_nrflag,0x91ac) // Found @ ff93d88c (0x91ac)
//static long *nrflag = (long*)(0x91ac);       // Found @ ff93d88c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff82857c) //112
NHSTUB(Close                                  ,0xff823da0) //120
NHSTUB(CreateTask                             ,0xff81b818) //120
NHSTUB(DebugAssert                            ,0xff81bcf0) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823730) //116
NHSTUB(DeleteFile_Fut                         ,0xff82364c) //112
NHSTUB(DoAELock                               ,0xff825f88) //120
NHSTUB(DoAFLock                               ,0xff825b98) //120
NHSTUB(EnterToCompensationEVF                 ,0xff825e94) //104
NHSTUB(ExecuteEventProcedure                  ,0xff86965c) //104
NHSTUB(ExitFromCompensationEVF                ,0xff825ee4) //104
NHSTUB(ExitTask                               ,0xff81baa8) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff832b14) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff832c58) //104
NHSTUB(Fclose_Fut                             ,0xff8237c8) //120
NHSTUB(Feof_Fut                               ,0xff8239b4) //  1
NHSTUB(Fflush_Fut                             ,0xff8239f0) //  1
NHSTUB(Fgets_Fut                              ,0xff82391c) //  1
NHSTUB(Fopen_Fut                              ,0xff823788) //120
NHSTUB(Fread_Fut                              ,0xff823874) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8285b0) //112
NHSTUB(Fseek_Fut                              ,0xff823968) //120
NHSTUB(Fwrite_Fut                             ,0xff8238c8) //120
NHSTUB(GetBatteryTemperature                  ,0xff8455e0) //102
NHSTUB(GetCCDTemperature                      ,0xff845570) //102
NHSTUB(GetCurrentAvValue                      ,0xff92fdd0) //102
NHSTUB(GetDrive_ClusterSize                   ,0xff84f500) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff84f568) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff84f534) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff92eec8) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff92f1d4) //  1
NHSTUB(GetKbdState                            ,0xff842b28) //109
NHSTUB(GetMemInfo                             ,0xff813c40) //115
NHSTUB(GetOpticalTemperature                  ,0xff845650) //120
NHSTUB(GetParameterData                       ,0xff95d628) //101
NHSTUB(GetPropertyCase                        ,0xff86d25c) //102
NHSTUB(GetSystemTime                          ,0xffa2d21c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8c8aec) //102
NHSTUB(GetVRAMVPixelsSize                     ,0xff8c8af8) //102
NHSTUB(GetZoomLensCurrentPoint                ,0xff932b74) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa2326c) //102
NHSTUB(GiveSemaphore                          ,0xff81b77c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8bdc20) //102
NHSTUB(LEDDrive                               ,0xff8422b8) //120
NHSTUB(LocalTime                              ,0xff866d20) //115
NHSTUB(LockMainPower                          ,0xff875708) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8236c0) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa844bc) //102
NHSTUB(MoveIrisWithAv                         ,0xffa295cc) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa29b50) //120
NHSTUB(Open                                   ,0xff823d78) //120
NHSTUB(PB2Rec                                 ,0xff87871c) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff85be58) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff85be30) //120
NHSTUB(PT_PlaySound                           ,0xff85b4b4) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff8734c8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff873514) //120
NHSTUB(Read                                   ,0xff81a094) //120
NHSTUB(ReadFastDir                            ,0xffa122ec) //  1
NHSTUB(Rec2PB                                 ,0xff877120) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9b0484) //104
NHSTUB(RenameFile_Fut                         ,0xff8235f8) //  1
NHSTUB(Restart                                ,0xff829df4) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffa86b90) //102
NHSTUB(SetAutoShutdownTime                    ,0xff87577c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87c5b8) //120
NHSTUB(SetFileAttributes                      ,0xff8240cc) //  1
NHSTUB(SetFileTimeStamp                       ,0xff82407c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff8753e8) //  1
NHSTUB(SetParameterData                       ,0xff95d598) //101
NHSTUB(SetPropertyCase                        ,0xff86d15c) //102
NHSTUB(SetScriptMode                          ,0xff875438) //120
NHSTUB(SleepTask                              ,0xff828400) //120
NHSTUB(TakeSemaphore                          ,0xff81b6ac) //120
NHSTUB(TurnOffBackLight                       ,0xff881e30) //104
NHSTUB(TurnOnBackLight                        ,0xff881e18) //104
NHSTUB(TurnOnDisplay                          ,0xff83ea5c) //120
NHSTUB(TurnOffDisplay                         ,0xff83ea6c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff950de8) //120
NHSTUB(UnlockAE                               ,0xff825fb8) //120
NHSTUB(UnlockAF                               ,0xff825bdc) //120
NHSTUB(UnlockMainPower                        ,0xff87565c) //120
NHSTUB(UnsetZoomForMovie                      ,0xff962c8c) //104
NHSTUB(UpdateMBROnFlash                       ,0xff84f340) //105
NHSTUB(VbattGet                               ,0xff82072c) //120
NHSTUB(Write                                  ,0xff823e4c) //120
NHSTUB(WriteSDCard                            ,0xff922a68) //108
NHSTUB(_log                                   ,0xffaadd18) //111
NHSTUB(_log10                                 ,0xffaacc5c) //112
NHSTUB(_pow                                   ,0xffaacdcc) //121
NHSTUB(_sqrt                                  ,0xffaaf138) //  1
NHSTUB(add_ptp_handler                        ,0xff9e0928) //121
NHSTUB(apex2us                                ,0xff9b19c0) //121
NHSTUB(close                                  ,0xff819eac) //109
NHSTUB(err_init_task                          ,0xff814e98) //111
NHSTUB(exmem_alloc                            ,0xff867e44) //103
NHSTUB(exmem_free                             ,0xff867ebc) //103
NHSTUB(free                                   ,0xff813a98) //112
NHSTUB(kbd_p1_f                               ,0xff821f4c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821f58) //109
NHSTUB(kbd_p2_f                               ,0xff821780) //109
NHSTUB(kbd_read_keys                          ,0xff821e48) //109
NHSTUB(kbd_read_keys_r2                       ,0xff8426e0) //109
NHSTUB(kbd_pwr_off                            ,0xff842bac) //  2
NHSTUB(kbd_pwr_on                             ,0xff842b5c) //  2
NHSTUB(lseek                                  ,0xff823ee0) //120
NHSTUB(malloc                                 ,0xff8139c4) //112
NHSTUB(memcmp                                 ,0xff81d854) //120
NHSTUB(memcpy                                 ,0xff894584) //120
NHSTUB(memset                                 ,0xff9b0838) //120
NHSTUB(mkdir                                  ,0xff824144) //109
NHSTUB(mktime_ext                             ,0xff894df0) //  1
NHSTUB(open                                   ,0xff819dfc) //109
NHSTUB(OpenFastDir                            ,0xffa12258) //  1
NHSTUB(closedir                               ,0xffa123bc) //  1
NHSTUB(qsort                                  ,0xff9b0d40) //  1
NHSTUB(rand                                   ,0xff81d95c) //121
NHSTUB(realloc                                ,0xff813b78) //115
NHSTUB(reboot_fw_update                       ,0xffa19cec) //106
NHSTUB(set_control_event                      ,0xff875064) //  1
NHSTUB(srand                                  ,0xff81d950) //122
NHSTUB(stat                                   ,0xff823fac) //  1
NHSTUB(strcat                                 ,0xff894370) //  1
NHSTUB(strchr                                 ,0xff8943f8) //  1
NHSTUB(strcmp                                 ,0xff81d7ec) //120
NHSTUB(strcpy                                 ,0xff81d7d4) //120
NHSTUB(strftime                               ,0xff8947f8) //  1
NHSTUB(strlen                                 ,0xff81d830) //120
NHSTUB(strncmp                                ,0xff8943ac) //  1
NHSTUB(strncpy                                ,0xff82e210) //  1
NHSTUB(strrchr                                ,0xff89441c) //  1
NHSTUB(strtol                                 ,0xff82e448) //101
NHSTUB(strtolx                                ,0xff82e24c) //109
   DEF(task_CaptSeq                           ,0xff85e2b0) //120
   DEF(task_ExpDrv                            ,0xff8b6a80) //120
   DEF(task_FileWrite                         ,0xffa0f034) //120
   DEF(task_InitFileModules                   ,0xff8791d0) //120
   DEF(task_MovieRecord                       ,0xff85a278) //120
   DEF(task_PhySw                             ,0xff821adc) //120
   DEF(task_RotaryEncoder                     ,0xff842c84) //120
NHSTUB(time                                   ,0xff867224) //109
NHSTUB(vsprintf                               ,0xff81d754) //115
NHSTUB(EngDrvRead                             ,0xff822d8c) //102
