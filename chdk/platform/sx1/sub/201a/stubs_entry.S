// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM2.01A   // Found @ 0xff87ccb4, "GM2.01A" @ 0xff87ccc1
//   Firmware build timestamp: Apr 15 2009 09:44:14
//   Canon PowerShot SX1 IS

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12693 (0x3195) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x07ffffff
//   MEMISOSTART = 0x000c2d08
//   KEYSYS = d4                 // Found @ 0xffff3674
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff3684
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff96a758
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff96a718

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(ExitFromCompensationEVF              ,0xff825b88) //104        *** != 0xff825bac
//NHSTUB(kbd_pwr_off                          ,0xff84da28) //  2 60%    *** != 0x00000000

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffaa300c -> ffbbb0e4
// Current modemap entry not found in firmware - MODE_VIDEO_STD            3622

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00012da4) // Found @0xff821af4
DEF(physw_run                               ,0x00001c30) // Found @0xff821768
DEF(physw_sleep_delay                       ,0x00001c2e) // Found @0xff821768
DEF(levent_table                            ,0xffb89f60) // Found @0xffb89f60
DEF(FlashParamsTable                        ,0xffbbb2bc) // Found @0xffbbb2bc
DEF(movie_status                            ,0x000055a8) // Found @0xff867b10
DEF(video_compression_rate                  ,0x000055d4) // Found @0xff867d14
DEF(canon_menu_active                       ,0x00005a5c) // Found @0xff87e710
DEF(canon_shoot_menu_active                 ,0x0000b819) // Found @0xff9a68a0
DEF(playrec_mode                            ,0x000057c4) // Found @0xff8716c8
DEF(zoom_status                             ,0x0000f2a0) // Found @0xffaa4d38
DEF(some_flag_for_af_scan                   ,0x0000a5e8) // Found @0xff95e58c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 1 int value, which is the the zoom focus length.
// there are 6 entries in the table - set NUM_FL to 6
DEF(focus_len_table                         ,0xffbbebbc) // Found @0xffbbebbc
DEF(zoom_busy                               ,0x00009ae8) // Found @0xff953f40
DEF(focus_busy                              ,0x00009974) // Found @0xff94cf54
//DEF(recreview_hold                          ,0x0000678c) // Found @0xff89020c, ** != ** stubs_min = 0x0000b400 (0xB31C+0xE4)
// Camera has 2 RAW buffers @ 0x41b724c0 & 0x435627d8
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffb37054) // Found @0xffb37054
DEF(active_raw_buffer                       ,0x00005764) // Found @0xff86e680

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff84807c
//void *vid_get_viewport_fb()      { return (void*)0x4133bb10; }             // Found @0xffafc468
DEF(viewport_fb_d                           ,0x00005420) // Found 0x53c8 (@0xff85fbb0) + 0x58 (@0xff85fbdc)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x53c8+0x58)); } // Found @0xff85fbb0 & 0xff85fbdc
DEF(jpeg_count_str                          ,0x0005ced4) // Found @0xff9ed744
//char *camera_jpeg_count_str()    { return (char*)0x0005ced4; }             // Found @0xff9ed744
//long hook_raw_size()             { return 0x01076d90; }                    // Found @0xffafe960
//int get_flash_params_count(void) { return 0x79; }                          // Found @0xff98d594

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb36748, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb36754, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb365e0, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb365e0, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb365d4, levent 0x00
//    { 0, KEY_POWER           ,0x00002000 }, // Found @0xffb365ec, levent 0x600
//    { 0, KEY_PLAYBACK        ,0x00004000 }, // Found @0xffb365f8, levent 0x601
//    { 1, KEY_VIDEO           ,0x00000020 }, // Found @0xffb3664c, levent 0x12
//    { 1, KEY_SET             ,0x00000100 }, // Found @0xffb36670, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00000200 }, // Found @0xffb3667c, levent 0x0a
//    { 1, KEY_UP              ,0x00000400 }, // Found @0xffb36688, levent 0x04
//    { 1, KEY_DOWN            ,0x00000800 }, // Found @0xffb36694, levent 0x05
//    { 1, KEY_RIGHT           ,0x00001000 }, // Found @0xffb366a0, levent 0x07
//    { 1, KEY_LEFT            ,0x00002000 }, // Found @0xffb366ac, levent 0x06
//    { 1, KEY_MENU            ,0x00004000 }, // Found @0xffb366b8, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4152 // Found @0xffaf52ec
//#define CAM_RAW_ROWS      2772 // Found @0xffaf52f0
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff8280b0

// Misc stuff
DEF(ctypes, 0xffb2b0da)

// For capt_seq.c
DEF(_nrflag,0xa5cc) // Found @ ff960d5c (0xa5d0) & ff960d78 (-0x04)
//static long *nrflag = (long*)(0xa5d0-0x04);  // Found @ ff960d5c & ff960d74

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff82806c) //112
NHSTUB(Close                                  ,0xff823a44) //120
NHSTUB(CreateTask                             ,0xff81aef4) //120
NHSTUB(DebugAssert                            ,0xff81b1cc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff8233d4) //116
NHSTUB(DeleteFile_Fut                         ,0xff8232f0) //112
NHSTUB(DoAELock                               ,0xff825be8) //120
NHSTUB(DoAFLock                               ,0xff825898) //120
NHSTUB(EnterToCompensationEVF                 ,0xff825b44) //104
NHSTUB(ExecuteEventProcedure                  ,0xff879ea0) //104
NHSTUB(ExitTask                               ,0xff81b184) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff8312a4) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff8313e8) //104
NHSTUB(Fclose_Fut                             ,0xff82346c) //120
NHSTUB(Feof_Fut                               ,0xff823658) //  1
NHSTUB(Fflush_Fut                             ,0xff823694) //  1
NHSTUB(Fgets_Fut                              ,0xff8235c0) //  1
NHSTUB(Fopen_Fut                              ,0xff82342c) //120
NHSTUB(Fread_Fut                              ,0xff823518) //120
NHSTUB(FreeUncacheableMemory                  ,0xff8280ac) //112
NHSTUB(Fseek_Fut                              ,0xff82360c) //120
NHSTUB(Fwrite_Fut                             ,0xff82356c) //120
NHSTUB(GetBatteryTemperature                  ,0xff850b00) //102
NHSTUB(GetCCDTemperature                      ,0xff850a90) //102
NHSTUB(GetCurrentAvValue                      ,0xff94f5d4) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff85e284) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff85e2ec) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff85e2b8) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff94da5c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff94dd68) //  3
NHSTUB(GetKbdState                            ,0xff84d880) //109
NHSTUB(GetMemInfo                             ,0xff813c24) //115
NHSTUB(GetOpticalTemperature                  ,0xff850b70) //120
NHSTUB(GetParameterData                       ,0xff98d554) //101
NHSTUB(GetPropertyCase                        ,0xff87dbcc) //102
NHSTUB(GetSystemTime                          ,0xffa91c08) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff83d4e8) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff83d4f4) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff9548a8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa8210c) //102
NHSTUB(GiveSemaphore                          ,0xff827a88) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8bdbdc) //102
NHSTUB(LEDDrive                               ,0xff84cc34) //120
NHSTUB(LocalTime                              ,0xff87763c) //115
NHSTUB(LockMainPower                          ,0xff885580) //120
NHSTUB(MakeDirectory_Fut                      ,0xff823364) //116
NHSTUB(MoveFocusLensToDistance                ,0xffaf87a8) //102
NHSTUB(MoveIrisWithAv                         ,0xffa8c398) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa8cac0) //120
NHSTUB(Open                                   ,0xff823a1c) //120
NHSTUB(PB2Rec                                 ,0xff888840) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8697c0) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff869798) //120
NHSTUB(PT_PlaySound                           ,0xff869110) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff88328c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8832d8) //120
NHSTUB(PutInNdFilter                          ,0xffa8c944) //102
NHSTUB(PutOutNdFilter                         ,0xffa8c968) //102
NHSTUB(Read                                   ,0xff819a4c) //120
NHSTUB(ReadFastDir                            ,0xffa6fe78) //  1
NHSTUB(Rec2PB                                 ,0xff8871b8) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9fa710) //104
NHSTUB(RenameFile_Fut                         ,0xff82329c) //  1
NHSTUB(Restart                                ,0xff8298f0) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffafb628) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8855f4) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff88d348) //120
NHSTUB(SetFileAttributes                      ,0xff823d70) //  1
NHSTUB(SetFileTimeStamp                       ,0xff823d20) //  1
NHSTUB(SetLogicalEventActive                  ,0xff885240) //101
NHSTUB(SetParameterData                       ,0xff98d430) //101
NHSTUB(SetPropertyCase                        ,0xff87dac4) //102
NHSTUB(SetScriptMode                          ,0xff885290) //120
NHSTUB(SleepTask                              ,0xff827cf0) //120
NHSTUB(TakeSemaphore                          ,0xff8279b8) //120
NHSTUB(TurnOffBackLight                       ,0xff893fc8) //104
NHSTUB(TurnOnBackLight                        ,0xff893fb0) //104
NHSTUB(TurnOnDisplay                          ,0xff8481a0) //120
NHSTUB(TurnOffDisplay                         ,0xff8481b0) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff978be0) //120
NHSTUB(UnlockAE                               ,0xff825c0c) //120
NHSTUB(UnlockAF                               ,0xff8258d0) //120
NHSTUB(UnlockMainPower                        ,0xff8854d4) //120
NHSTUB(UpdateMBROnFlash                       ,0xff85e0c4) //105
NHSTUB(VbattGet                               ,0xff82046c) //120
NHSTUB(Write                                  ,0xff823af0) //120
NHSTUB(WriteSDCard                            ,0xff93dd0c) //108
NHSTUB(_log                                   ,0xffb28358) //111
NHSTUB(_log10                                 ,0xffb26fe4) //112
NHSTUB(_pow                                   ,0xffb27154) //121
NHSTUB(_sqrt                                  ,0xffb29fb4) //  1
NHSTUB(add_ptp_handler                        ,0xffa3afd0) //121
NHSTUB(apex2us                                ,0xff9fdbdc) //121
NHSTUB(close                                  ,0xff819864) //109
NHSTUB(err_init_task                          ,0xff814e80) //111
NHSTUB(exmem_alloc                            ,0xff87857c) //103
NHSTUB(exmem_free                             ,0xff8785f4) //103
NHSTUB(free                                   ,0xff813a7c) //112
NHSTUB(kbd_p1_f                               ,0xff821bf0) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821bfc) //109
NHSTUB(kbd_p2_f                               ,0xff821408) //109
NHSTUB(kbd_read_keys                          ,0xff821af4) //109
NHSTUB(kbd_read_keys_r2                       ,0xff84d130) //109
NHSTUB(lseek                                  ,0xff823b84) //120
NHSTUB(malloc                                 ,0xff8139a8) //112
NHSTUB(memcmp                                 ,0xff81cba4) //120
NHSTUB(memcpy                                 ,0xff8a0984) //120
NHSTUB(memset                                 ,0xff9fcf14) //120
NHSTUB(mkdir                                  ,0xff823de8) //109
NHSTUB(mktime_ext                             ,0xff8a11f0) //  1
NHSTUB(open                                   ,0xff8197b4) //109
NHSTUB(OpenFastDir                            ,0xffa6fde4) //  1
NHSTUB(closedir                               ,0xffa6ff48) //  1
NHSTUB(qsort                                  ,0xffae3d64) //  1
NHSTUB(rand                                   ,0xff81ccac) //121
NHSTUB(realloc                                ,0xff813b5c) //115
NHSTUB(reboot_fw_update                       ,0xffa77878) //106
NHSTUB(set_control_event                      ,0xff884e9c) //111
NHSTUB(srand                                  ,0xff81cca0) //122
NHSTUB(stat                                   ,0xff823c50) //  1
NHSTUB(strcat                                 ,0xff8a0798) //  1
NHSTUB(strchr                                 ,0xff8a0820) //  1
NHSTUB(strcmp                                 ,0xff81cb3c) //120
NHSTUB(strcpy                                 ,0xff81cb24) //120
NHSTUB(strftime                               ,0xff8a0bf8) //  1
NHSTUB(strlen                                 ,0xff81cb80) //120
NHSTUB(strncmp                                ,0xff8a07d4) //  1
NHSTUB(strncpy                                ,0xff82dbf8) //  1
NHSTUB(strrchr                                ,0xff9fceec) //  1
NHSTUB(strtol                                 ,0xff82de30) //101
NHSTUB(strtolx                                ,0xff82dc34) //109
   DEF(task_CaptSeq                           ,0xff86cb80) //120
   DEF(task_ExpDrv                            ,0xff8b3e4c) //120
   DEF(task_FileWrite                         ,0xffa6c6fc) //120
   DEF(task_InitFileModules                   ,0xff8892bc) //120
   DEF(task_MovieRecord                       ,0xff867d90) //120
   DEF(task_PhySw                             ,0xff821764) //120
   DEF(task_RotaryEncoder                     ,0xff84daf0) //120
NHSTUB(time                                   ,0xff877c1c) //109
NHSTUB(vsprintf                               ,0xff81cae8) //115
NHSTUB(EngDrvRead                             ,0xff822a30) //102
