// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00F   // Found @ 0xff86c0a0, "GM1.00F" @ 0xff86c0ad
//   Firmware build timestamp: Oct 28 2008 13:41:31
//   Canon PowerShot SD890 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12659 (0x3173) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x000cbd40
//   KEYSYS = d3enc              // Found @ 0xffff33e0
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff33c0
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffa2eba4
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffa2eb64

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(PutInNdFilter                        ,0xffa2ab90) //102        *** != 0xffa83868
//NHSTUB(PutOutNdFilter                       ,0xffa2abb4) //102        *** != 0xffa8389c

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa3ee38 -> ffaf9518
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00010650) // Found @0xff821e38
DEF(physw_run                               ,0x00001c00) // Found @0xff821ad0
DEF(physw_sleep_delay                       ,0x00001bfe) // Found @0xff821ad0
DEF(levent_table                            ,0xffad4084) // Found @0xffad4084
DEF(FlashParamsTable                        ,0xffaf96d8) // Found @0xffaf96d8
DEF(movie_status                            ,0x000053cc) // Found @0xff859cfc
DEF(canon_menu_active                       ,0x000099e0) // Found @0xff950108
DEF(canon_shoot_menu_active                 ,0x00009fd9) // Found @0xff96cce0
DEF(playrec_mode                            ,0x0000555c) // Found @0xff8610f4
DEF(zoom_status                             ,0x0000d4a4) // Found @0xffa40638
DEF(some_flag_for_af_scan                   ,0x0000d228) // Found @0xffa2b508
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 12 entries in the table - set NUM_FL to 12
DEF(focus_len_table                         ,0xfffe297c) // Found @0xfffe297c
DEF(zoom_busy                               ,0x00008aa0) // Found @0xff932a0c
DEF(focus_busy                              ,0x0000898c) // Found @0xff92e0b8
//DEF(recreview_hold                          ,0x00006188) // Found @0xff87eb14, ** != ** stubs_min = 0x00009d98 (0x9CEC+0xAC)
// Camera has 2 RAW buffers @ 0x107d68c0 & 0x11b97b60
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffab1c2c) // Found @0xffab1c2c
DEF(active_raw_buffer                       ,0x0000550c) // Found @0xff85e57c

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff83e89c
//void *vid_get_viewport_fb()      { return (void*)0x1065adc0; }             // Found @0xffa88a6c
DEF(viewport_fb_d                           ,0x0000524c) // Found 0x51fc (@0xff853074) + 0x50 (@0xff8530ac)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x51fc+0x50)); } // Found @0xff853074 & 0xff8530ac
DEF(jpeg_count_str                          ,0x0004ca80) // Found @0xff9a6f4c
//char *camera_jpeg_count_str()    { return (char*)0x0004ca80; }             // Found @0xff9a6f4c
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffa8acf0
//int get_flash_params_count(void) { return 0x73; }                          // Found @0xff95d8e4

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffab16e8, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffab16f4, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 1, KEY_POWER           ,0x40000000 }, // Found @0xffab1628, levent 0x600
//    { 1, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffab1634, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffab164c, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffab164c, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffab1640, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffab1658, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffab1664, levent 0x03
//    { 2, KEY_LEFT            ,0x00000010 }, // Found @0xffab1670, levent 0x06
//    { 2, KEY_RIGHT           ,0x00000020 }, // Found @0xffab167c, levent 0x07
//    { 2, KEY_DOWN            ,0x00000040 }, // Found @0xffab1688, levent 0x05
//    { 2, KEY_UP              ,0x00000080 }, // Found @0xffab1694, levent 0x04
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffab16a0, levent 0x08
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffab16ac, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffab16b8, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3720 // Found @0xffa8248c
//#define CAM_RAW_ROWS      2772 // Found @0xffa82494
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff8285a4

// Misc stuff
DEF(ctypes, 0xffab11b6)

// For capt_seq.c
DEF(_nrflag,0x91a4) // Found @ ff93db0c (0x91a4)
//static long *nrflag = (long*)(0x91a4);       // Found @ ff93db0c

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff828568) //112
NHSTUB(Close                                  ,0xff823d90) //120
NHSTUB(CreateTask                             ,0xff81b818) //120
NHSTUB(DebugAssert                            ,0xff81bcf0) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823720) //116
NHSTUB(DeleteFile_Fut                         ,0xff82363c) //112
NHSTUB(DoAELock                               ,0xff825f74) //120
NHSTUB(DoAFLock                               ,0xff825b84) //120
NHSTUB(EnterToCompensationEVF                 ,0xff825e80) //104
NHSTUB(ExecuteEventProcedure                  ,0xff86938c) //104
NHSTUB(ExitFromCompensationEVF                ,0xff825ed0) //104
NHSTUB(ExitTask                               ,0xff81baa8) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff832b00) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff832c44) //104
NHSTUB(Fclose_Fut                             ,0xff8237b8) //120
NHSTUB(Feof_Fut                               ,0xff8239a4) //  1
NHSTUB(Fflush_Fut                             ,0xff8239e0) //  1
NHSTUB(Fgets_Fut                              ,0xff82390c) //  1
NHSTUB(Fopen_Fut                              ,0xff823778) //120
NHSTUB(Fread_Fut                              ,0xff823864) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82859c) //112
NHSTUB(Fseek_Fut                              ,0xff823958) //120
NHSTUB(Fwrite_Fut                             ,0xff8238b8) //120
NHSTUB(GetBatteryTemperature                  ,0xff84539c) //102
NHSTUB(GetCCDTemperature                      ,0xff84532c) //102
NHSTUB(GetCurrentAvValue                      ,0xff92facc) //102
NHSTUB(GetDrive_ClusterSize                   ,0xff84f2bc) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff84f324) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff84f2f0) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff92ebc4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff92eed0) //  1
NHSTUB(GetKbdState                            ,0xff8428e4) //109
NHSTUB(GetMemInfo                             ,0xff813c40) //115
NHSTUB(GetOpticalTemperature                  ,0xff84540c) //120
NHSTUB(GetParameterData                       ,0xff95d8a4) //101
NHSTUB(GetPropertyCase                        ,0xff86cf8c) //102
NHSTUB(GetSystemTime                          ,0xffa2e3f8) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8c851c) //102
NHSTUB(GetVRAMVPixelsSize                     ,0xff8c8528) //102
NHSTUB(GetZoomLensCurrentPoint                ,0xff932d74) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa24448) //102
NHSTUB(GiveSemaphore                          ,0xff81b77c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8bd988) //102
NHSTUB(LEDDrive                               ,0xff842068) //120
NHSTUB(LocalTime                              ,0xff866a50) //115
NHSTUB(LockMainPower                          ,0xff875438) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8236b0) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa855a8) //102
NHSTUB(MoveIrisWithAv                         ,0xffa2a7a8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa2ad2c) //120
NHSTUB(Open                                   ,0xff823d68) //120
NHSTUB(PB2Rec                                 ,0xff878454) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff85bb68) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff85bb40) //120
NHSTUB(PT_PlaySound                           ,0xff85b1c4) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff8731f8) //120
NHSTUB(PostLogicalEventToUI                   ,0xff873244) //120
NHSTUB(Read                                   ,0xff81a094) //120
NHSTUB(ReadFastDir                            ,0xffa13470) //  1
NHSTUB(Rec2PB                                 ,0xff876e58) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff9b1258) //104
NHSTUB(RenameFile_Fut                         ,0xff8235e8) //  1
NHSTUB(Restart                                ,0xff829de0) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffa87c7c) //102
NHSTUB(SetAutoShutdownTime                    ,0xff8754ac) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87c2b8) //120
NHSTUB(SetFileAttributes                      ,0xff8240bc) //  1
NHSTUB(SetFileTimeStamp                       ,0xff82406c) //  1
NHSTUB(SetLogicalEventActive                  ,0xff875118) //  1
NHSTUB(SetParameterData                       ,0xff95d814) //101
NHSTUB(SetPropertyCase                        ,0xff86ce8c) //102
NHSTUB(SetScriptMode                          ,0xff875168) //120
NHSTUB(SleepTask                              ,0xff8283ec) //120
NHSTUB(TakeSemaphore                          ,0xff81b6ac) //120
NHSTUB(TurnOffBackLight                       ,0xff881cac) //104
NHSTUB(TurnOnBackLight                        ,0xff881c94) //104
NHSTUB(TurnOnDisplay                          ,0xff83e94c) //120
NHSTUB(TurnOffDisplay                         ,0xff83e95c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff951064) //120
NHSTUB(UnlockAE                               ,0xff825fa4) //120
NHSTUB(UnlockAF                               ,0xff825bc8) //120
NHSTUB(UnlockMainPower                        ,0xff87538c) //120
NHSTUB(UnsetZoomForMovie                      ,0xff962e40) //104
NHSTUB(UpdateMBROnFlash                       ,0xff84f0fc) //105
NHSTUB(VbattGet                               ,0xff82071c) //120
NHSTUB(Write                                  ,0xff823e3c) //120
NHSTUB(WriteSDCard                            ,0xff922764) //108
NHSTUB(_log                                   ,0xffaaec70) //111
NHSTUB(_log10                                 ,0xffaadbb4) //112
NHSTUB(_pow                                   ,0xffaadd24) //121
NHSTUB(_sqrt                                  ,0xffab0090) //  1
NHSTUB(add_ptp_handler                        ,0xff9e1a94) //121
NHSTUB(apex2us                                ,0xff9b2794) //121
NHSTUB(close                                  ,0xff819eac) //109
NHSTUB(err_init_task                          ,0xff814e98) //111
NHSTUB(exmem_alloc                            ,0xff867b74) //103
NHSTUB(exmem_free                             ,0xff867bec) //103
NHSTUB(free                                   ,0xff813a98) //112
NHSTUB(kbd_p1_f                               ,0xff821f3c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821f48) //109
NHSTUB(kbd_p2_f                               ,0xff821770) //109
NHSTUB(kbd_read_keys                          ,0xff821e38) //109
NHSTUB(kbd_read_keys_r2                       ,0xff842490) //109
NHSTUB(kbd_pwr_off                            ,0xff842968) //  2
NHSTUB(kbd_pwr_on                             ,0xff842918) //  2
NHSTUB(lseek                                  ,0xff823ed0) //120
NHSTUB(malloc                                 ,0xff8139c4) //112
NHSTUB(memcmp                                 ,0xff81d844) //120
NHSTUB(memcpy                                 ,0xff894328) //120
NHSTUB(memset                                 ,0xff9b160c) //120
NHSTUB(mkdir                                  ,0xff824134) //109
NHSTUB(mktime_ext                             ,0xff894b94) //  1
NHSTUB(open                                   ,0xff819dfc) //109
NHSTUB(OpenFastDir                            ,0xffa133dc) //  1
NHSTUB(closedir                               ,0xffa13540) //  1
NHSTUB(qsort                                  ,0xff9b1b14) //  1
NHSTUB(rand                                   ,0xff81d94c) //121
NHSTUB(realloc                                ,0xff813b78) //115
NHSTUB(reboot_fw_update                       ,0xffa1ae70) //106
NHSTUB(set_control_event                      ,0xff874d94) //  1
NHSTUB(srand                                  ,0xff81d940) //122
NHSTUB(stat                                   ,0xff823f9c) //  1
NHSTUB(strcat                                 ,0xff894114) //  1
NHSTUB(strchr                                 ,0xff89419c) //  1
NHSTUB(strcmp                                 ,0xff81d7dc) //120
NHSTUB(strcpy                                 ,0xff81d7c4) //120
NHSTUB(strftime                               ,0xff89459c) //  1
NHSTUB(strlen                                 ,0xff81d820) //120
NHSTUB(strncmp                                ,0xff894150) //  1
NHSTUB(strncpy                                ,0xff82e1fc) //  1
NHSTUB(strrchr                                ,0xff8941c0) //  1
NHSTUB(strtol                                 ,0xff82e434) //101
NHSTUB(strtolx                                ,0xff82e238) //109
   DEF(task_CaptSeq                           ,0xff85dfc0) //120
   DEF(task_ExpDrv                            ,0xff8b67e8) //120
   DEF(task_FileWrite                         ,0xffa101b8) //120
   DEF(task_InitFileModules                   ,0xff878f08) //120
   DEF(task_MovieRecord                       ,0xff859f88) //120
   DEF(task_PhySw                             ,0xff821acc) //120
   DEF(task_RotaryEncoder                     ,0xff842a40) //120
NHSTUB(time                                   ,0xff866f54) //109
NHSTUB(vsprintf                               ,0xff81d744) //115
NHSTUB(EngDrvRead                             ,0xff822d7c) //102
