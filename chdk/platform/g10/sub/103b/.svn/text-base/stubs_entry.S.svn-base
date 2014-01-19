// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R31 (DRYOS version 2.3, release #0031)
//   Firmware Ver GM1.03B   // Found @ 0xff8768bc, "GM1.03B" @ 0xff8768c9
//   Firmware build timestamp: Jan  9 2009 11:49:57
//   Canon PowerShot G10

// Values for makefile.inc
//   PLATFORMOSVER = 31
//   PLATFORMID = 12687 (0x318f) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x07ffffff
//   MEMISOSTART = 0x000eeecc
//   KEYSYS = d4                 // Found @ 0xffff368c
//   NEED_ENCODED_DISKBOOT = 1   // Found @ 0xffff369c
//   ARAM_HEAP_START = 0x3ce000  // Found @ 0xff952c0c
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xff952bcc

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(kbd_pwr_off                          ,0xff84b174) //  2 60%        == 0xff84b174

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa7aa74 -> ffb7506c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00011cb8) // Found @0xff821c28
DEF(physw_run                               ,0x00001c2c) // Found @0xff82189c
DEF(physw_sleep_delay                       ,0x00001c2a) // Found @0xff82189c
DEF(levent_table                            ,0xffb43abc) // Found @0xffb43abc
DEF(FlashParamsTable                        ,0xffb7524c) // Found @0xffb7524c
DEF(movie_status                            ,0x00005418) // Found @0xff8629c4
DEF(video_compression_rate                  ,0x00005444) // Found @0xff862b90
DEF(canon_menu_active                       ,0x00005868) // Found @0xff8782dc
DEF(canon_shoot_menu_active                 ,0x0000a8ad) // Found @0xff987990
DEF(playrec_mode                            ,0x000055d0) // Found @0xff86b300
DEF(zoom_status                             ,0x0000e0b0) // Found @0xffa7c754
DEF(some_flag_for_af_scan                   ,0x000096f8) // Found @0xff946b5c
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 14 entries in the table - set NUM_FL to 14
DEF(focus_len_table                         ,0xfffe2a8c) // Found @0xfffe2a8c
DEF(zoom_busy                               ,0x00008d44) // Found @0xff93e458
DEF(focus_busy                              ,0x00008c44) // Found @0xff938b44
DEF(recreview_hold                          ,0x00006274) // Found @0xff888be8
// Palette colour tables  found @ 0xffb59420
DEF(active_palette_buffer                   ,0x0000bac4) // Found @0xff9d6428
DEF(palette_buffer_ptr                      ,0x0000bab8) // Found @0xff9d62dc
// Offset from start of palette_buffer to color data = 16 (Found @0xff9d5268)
// Camera has 2 RAW buffers @ 0x413245a0 & 0x43164d80
//  Note: active buffer --> raw_buffers[ active_raw_buffer   *3]
//        other buffer  --> raw_buffers[(active_raw_buffer^1)*3]
DEF(raw_buffers                             ,0xffb101cc) // Found @0xffb101cc
DEF(active_raw_buffer                       ,0x00005574) // Found @0xff868430

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x40471000; }             // Found @0xff846a4c
//void *vid_get_viewport_fb()      { return (void*)0x40816dc0; }             // Found @0xffad4d80
DEF(viewport_fb_d                           ,0x000052a4) // Found 0x524c (@0xff85b864) + 0x58 (@0xff85b89c)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x524c+0x58)); } // Found @0xff85b864 & 0xff85b89c
DEF(jpeg_count_str                          ,0x0004c95c) // Found @0xff9cccec
//char *camera_jpeg_count_str()    { return (char*)0x0004c95c; }             // Found @0xff9cccec
//long hook_raw_size()             { return 0x01574d00; }                    // Found @0xffad713c
//int get_flash_params_count(void) { return 0x78; }                          // Found @0xff971c50

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffb0f980, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffb0f98c, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffb0f800, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffb0f800, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffb0f7f4, levent 0x00
//    { 0, KEY_POWER           ,0x40000000 }, // Found @0xffb0f830, levent 0x600 (uses inverted logic in physw_status)
//    { 0, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffb0f83c, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffb0f86c, levent 0x03
//    { 1, KEY_ZOOM_IN         ,0x00000010 }, // Found @0xffb0f878, levent 0x02
//    { 1, KEY_LEFT            ,0x00000400 }, // Found @0xffb0f8c0, levent 0x06
//    { 1, KEY_SET             ,0x00000800 }, // Found @0xffb0f8cc, levent 0x08
//    { 1, KEY_RIGHT           ,0x00001000 }, // Found @0xffb0f8d8, levent 0x07
//    { 1, KEY_DOWN            ,0x00002000 }, // Found @0xffb0f8e4, levent 0x05
//    { 1, KEY_UP              ,0x00004000 }, // Found @0xffb0f8f0, levent 0x04
//    { 1, KEY_DISPLAY         ,0x00020000 }, // Found @0xffb0f914, levent 0x0a
//    { 1, KEY_MENU            ,0x00040000 }, // Found @0xffb0f920, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    4480 // Found @0xffacde48
//#define CAM_RAW_ROWS      3348 // Found @0xffacde4c
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x40000000 // Found @0xff828844

// Misc stuff
DEF(ctypes, 0xffb09676)

// For capt_seq.c
DEF(_nrflag,0x96e0) // Found @ ff94921c (0x96e4) & ff949238 (-0x04)
//static long *nrflag = (long*)(0x96e4-0x04);  // Found @ ff94921c & ff949234

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff828800) //112
NHSTUB(Close                                  ,0xff824088) //120
NHSTUB(CreateTask                             ,0xff81aef4) //120
NHSTUB(DebugAssert                            ,0xff81b1cc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff823a18) //116
NHSTUB(DeleteFile_Fut                         ,0xff823934) //112
NHSTUB(DoAELock                               ,0xff8261b4) //120
NHSTUB(DoAFLock                               ,0xff825e48) //120
NHSTUB(EnterToCompensationEVF                 ,0xff826110) //104
NHSTUB(ExecuteEventProcedure                  ,0xff873ae4) //104
NHSTUB(ExitFromCompensationEVF                ,0xff826154) //104
NHSTUB(ExitTask                               ,0xff81b184) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff831950) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff831a94) //104
NHSTUB(Fclose_Fut                             ,0xff823ab0) //120
NHSTUB(Feof_Fut                               ,0xff823c9c) //  1
NHSTUB(Fflush_Fut                             ,0xff823cd8) //  1
NHSTUB(Fgets_Fut                              ,0xff823c04) //  1
NHSTUB(Fopen_Fut                              ,0xff823a70) //120
NHSTUB(Fread_Fut                              ,0xff823b5c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff828840) //112
NHSTUB(Fseek_Fut                              ,0xff823c50) //120
NHSTUB(Fwrite_Fut                             ,0xff823bb0) //120
NHSTUB(GetBatteryTemperature                  ,0xff84dc90) //102
NHSTUB(GetCCDTemperature                      ,0xff84dc20) //102
NHSTUB(GetCurrentAvValue                      ,0xff93b378) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff859f90) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff859ff8) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff859fc4) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff939848) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff939c30) //  3
NHSTUB(GetKbdState                            ,0xff84afbc) //109
NHSTUB(GetMemInfo                             ,0xff813c24) //115
NHSTUB(GetOpticalTemperature                  ,0xff84dd00) //120
NHSTUB(GetParameterData                       ,0xff971c10) //101
NHSTUB(GetPropertyCase                        ,0xff8777cc) //102
NHSTUB(GetSystemTime                          ,0xffa688c0) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff83ce54) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff83ce60) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff93e7c8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa5dcb4) //102
NHSTUB(GiveSemaphore                          ,0xff82821c) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8b4794) //102
NHSTUB(LEDDrive                               ,0xff84a53c) //120
NHSTUB(LocalTime                              ,0xff871280) //115
NHSTUB(LockMainPower                          ,0xff87ef28) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8239a8) //116
NHSTUB(MoveFocusLensToDistance                ,0xffad17b4) //102
NHSTUB(MoveIrisWithAv                         ,0xffa6528c) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffa659a4) //120
NHSTUB(Open                                   ,0xff824060) //120
NHSTUB(PB2Rec                                 ,0xff8822ec) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff864344) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86431c) //120
NHSTUB(PT_PlaySound                           ,0xff863c98) //102
NHSTUB(PostLogicalEventForNotPowerType        ,0xff87ccec) //120
NHSTUB(PostLogicalEventToUI                   ,0xff87cd38) //120
NHSTUB(PutInNdFilter                          ,0xffa65808) //102
NHSTUB(PutOutNdFilter                         ,0xffa6582c) //102
NHSTUB(Read                                   ,0xff819a4c) //120
NHSTUB(ReadFastDir                            ,0xffa4a190) //  1
NHSTUB(Rec2PB                                 ,0xff880c28) //104
//NHSTUB(RefreshPhysicalScreen                ,0xff9dae54) //104            == 0xff9dae54
NHSTUB(RenameFile_Fut                         ,0xff8238e0) //  1
NHSTUB(Restart                                ,0xff82a074) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffad3f84) //102
NHSTUB(SetAutoShutdownTime                    ,0xff87ef9c) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff885d94) //120
NHSTUB(SetFileAttributes                      ,0xff8243b4) //  1
NHSTUB(SetFileTimeStamp                       ,0xff824364) //  1
NHSTUB(SetLogicalEventActive                  ,0xff87ec78) //101
NHSTUB(SetParameterData                       ,0xff971aec) //101
NHSTUB(SetPropertyCase                        ,0xff8776c4) //102
NHSTUB(SetScriptMode                          ,0xff87ecc8) //120
NHSTUB(SleepTask                              ,0xff828484) //120
NHSTUB(TakeSemaphore                          ,0xff82814c) //120
NHSTUB(TurnOffBackLight                       ,0xff88c57c) //104
NHSTUB(TurnOnBackLight                        ,0xff88c564) //104
NHSTUB(TurnOnDisplay                          ,0xff846b14) //120
NHSTUB(TurnOffDisplay                         ,0xff846b24) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xff95fddc) //120
NHSTUB(UnlockAE                               ,0xff8261d8) //120
NHSTUB(UnlockAF                               ,0xff825e9c) //120
NHSTUB(UnlockMainPower                        ,0xff87ee7c) //120
NHSTUB(UnsetZoomForMovie                      ,0xff977ed0) //104
NHSTUB(UpdateMBROnFlash                       ,0xff859dd0) //105
NHSTUB(VbattGet                               ,0xff820574) //120
NHSTUB(Write                                  ,0xff824134) //120
NHSTUB(WriteSDCard                            ,0xff92a7c0) //108
NHSTUB(_log                                   ,0xffb068f4) //111
NHSTUB(_log10                                 ,0xffb05580) //112
NHSTUB(_pow                                   ,0xffb056f0) //121
NHSTUB(_sqrt                                  ,0xffb08550) //  1
NHSTUB(add_ptp_handler                        ,0xffa1594c) //121
NHSTUB(apex2us                                ,0xff9dc338) //121
NHSTUB(close                                  ,0xff819864) //109
NHSTUB(err_init_task                          ,0xff814e80) //111
NHSTUB(exmem_alloc                            ,0xff8721c0) //103
NHSTUB(exmem_free                             ,0xff872238) //103
NHSTUB(free                                   ,0xff813a7c) //112
NHSTUB(kbd_p1_f                               ,0xff821d24) //109
NHSTUB(kbd_p1_f_cont                          ,0xff821d30) //109
NHSTUB(kbd_p2_f                               ,0xff82153c) //109
NHSTUB(kbd_read_keys                          ,0xff821c28) //109
NHSTUB(kbd_read_keys_r2                       ,0xff84a99c) //109
NHSTUB(lseek                                  ,0xff8241c8) //120
NHSTUB(malloc                                 ,0xff8139a8) //112
NHSTUB(memcmp                                 ,0xff81cbb0) //120
NHSTUB(memcpy                                 ,0xff899344) //120
NHSTUB(memset                                 ,0xff9db1a8) //120
NHSTUB(mkdir                                  ,0xff82442c) //109
NHSTUB(mktime_ext                             ,0xff899bb0) //  1
NHSTUB(open                                   ,0xff8197b4) //109
NHSTUB(OpenFastDir                            ,0xffa4a0fc) //  1
NHSTUB(closedir                               ,0xffa4a260) //  1
NHSTUB(qsort                                  ,0xff9db6b0) //  1
NHSTUB(rand                                   ,0xff81ccb8) //121
NHSTUB(realloc                                ,0xff813b5c) //115
NHSTUB(reboot_fw_update                       ,0xffa51b90) //106
NHSTUB(set_control_event                      ,0xff87e8dc) //111
NHSTUB(srand                                  ,0xff81ccac) //122
NHSTUB(stat                                   ,0xff824294) //  1
NHSTUB(strcat                                 ,0xff899158) //  1
NHSTUB(strchr                                 ,0xff8991e0) //  1
NHSTUB(strcmp                                 ,0xff81cb48) //120
NHSTUB(strcpy                                 ,0xff81cb30) //120
NHSTUB(strftime                               ,0xff8995b8) //  1
NHSTUB(strlen                                 ,0xff81cb8c) //120
NHSTUB(strncmp                                ,0xff899194) //  1
NHSTUB(strncpy                                ,0xff82e2bc) //  1
NHSTUB(strrchr                                ,0xff9db180) //  1
NHSTUB(strtol                                 ,0xff82e4f4) //101
NHSTUB(strtolx                                ,0xff82e2f8) //109
   DEF(task_CaptSeq                           ,0xff866bfc) //120
   DEF(task_ExpDrv                            ,0xff8ab0e0) //120
   DEF(task_FileWrite                         ,0xffa46a14) //120
   DEF(task_InitFileModules                   ,0xff882ea8) //120
   DEF(task_MovieRecord                       ,0xff862c0c) //120
   DEF(task_PhySw                             ,0xff821898) //120
   DEF(task_RotaryEncoder                     ,0xff84b23c) //120
NHSTUB(time                                   ,0xff871860) //109
NHSTUB(vsprintf                               ,0xff81caf4) //115
NHSTUB(EngDrvRead                             ,0xff822b64) //102
