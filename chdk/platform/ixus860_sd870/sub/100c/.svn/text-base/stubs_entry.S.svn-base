// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R23 (DRYOS version 2.3, release #0023)
//   Firmware Ver GM1.00C   // Found @ 0xff868588, "GM1.00C" @ 0xff868595
//   Firmware build timestamp: Jul 20 2007 18:32:15
//   Canon DIGITAL IXUS 860 IS

// Values for makefile.inc
//   PLATFORMOSVER = 23
//   PLATFORMID = 12640 (0x3160) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x0009fe50
//   KEYSYS = d3                 // Found @ 0xffff3184

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetCCDTemperature                    ,0xff846ac0) //102        *** != 0xff846c54
//NHSTUB(NewTaskShell                         ,0xff868ef4) //120        *** != 0xffc596b0
//NHSTUB(PutInNdFilter                        ,0xff9262dc) //102        *** != 0xff9e448c
//NHSTUB(PutOutNdFilter                       ,0xff926300) //102        *** != 0xff9e44c4
//NHSTUB(UIFS_WriteFirmInfoToFile             ,0xff981760) //120        *** != 0xffd4a934
//NHSTUB(kbd_pwr_off                          ,0xff84447c) //  2 67%    *** != 0xff84448c
NHSTUB(kbd_pwr_on                             ,0xff84443c) //  2 86%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa20600 -> ffacfef8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x000113fc) // Found @0xff8230cc
DEF(physw_run                               ,0x00001ca4) // Found @0xff822d7c
DEF(physw_sleep_delay                       ,0x00001ca2) // Found @0xff822d7c
DEF(levent_table                            ,0xffaac8b8) // Found @0xffaac8b8
DEF(FlashParamsTable                        ,0xffad00b4) // Found @0xffad00b4
DEF(movie_status                            ,0x0000551c) // Found @0xff857f90
DEF(canon_menu_active                       ,0x0000c04c) // Found @0xff98090c
DEF(canon_shoot_menu_active                 ,0x0000b65d) // Found @0xff951f90
DEF(playrec_mode                            ,0x000056c8) // Found @0xff85eed0
DEF(zoom_status                             ,0x0000e560) // Found @0xffa21df8
DEF(some_flag_for_af_scan                   ,0x0000e498) // Found @0xffa1a914
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 8 entries in the table - set NUM_FL to 8
DEF(focus_len_table                         ,0xfffe2990) // Found @0xfffe2990
DEF(zoom_busy                               ,0x0000a75c) // Found @0xff927cd4
//DEF(focus_busy                              ,0x0000a658) // Found @0xff922ac0, ** != ** stubs_min = 0x0000a65c (0xA65C)
//DEF(recreview_hold                          ,0x00006188) // Found @0xff8771cc, ** != ** stubs_min = 0x0000b474 (0xB474)
// Camera appears to have only 1 RAW buffer @ 0x10f3e0e0 (Found @0xff9eae38)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff84034c
//void *vid_get_viewport_fb()      { return (void*)0x1065b4b0; }             // Found @0xff9e8fb0
DEF(viewport_fb_d                           ,0x000053b0) // Found 0x5360 (@0xff8513b4) + 0x50 (@0xff8513ec)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x5360+0x50)); } // Found @0xff8513b4 & 0xff8513ec
DEF(jpeg_count_str                          ,0x0005a668) // Found @0xff9921b4
//char *camera_jpeg_count_str()    { return (char*)0x0005a668; }             // Found @0xff9921b4
//long hook_raw_size()             { return 0x009dcce0; }                    // Found @0xff9eae94
//int get_flash_params_count(void) { return 0x72; }                          // Found @0xff94372c

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffa8fd64, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00040000 // Found @0xffa8fd70, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_POWER           ,0x40000000 }, // Found @0xffa8fca4, levent 0x600
//    { 0, KEY_PLAYBACK        ,0x80000000 }, // Found @0xffa8fcb0, levent 0x601
//    { 2, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffa8fcc8, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffa8fcc8, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffa8fcbc, levent 0x00
//    { 2, KEY_ZOOM_IN         ,0x00000004 }, // Found @0xffa8fcd4, levent 0x02
//    { 2, KEY_ZOOM_OUT        ,0x00000008 }, // Found @0xffa8fce0, levent 0x03
//    { 2, KEY_DISPLAY         ,0x00000200 }, // Found @0xffa8fd28, levent 0x0a
//    { 2, KEY_MENU            ,0x00000400 }, // Found @0xffa8fd34, levent 0x09
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    3336 // Found @0xff9e3310
//#define CAM_RAW_ROWS      2480 // Found @0xff9e3318
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff829944

// Misc stuff
DEF(ctypes, 0xffa8f7a6)

// For capt_seq.c
DEF(_nrflag,0xaafc) // Found @ ff9315bc (0xaafc)
//static long *nrflag = (long*)(0xaafc);       // Found @ ff9315bc

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff829908) //112
NHSTUB(Close                                  ,0xff82502c) //120
NHSTUB(CreateTask                             ,0xff81bbb8) //120
NHSTUB(DebugAssert                            ,0xff81c090) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff824978) //116
NHSTUB(DeleteFile_Fut                         ,0xff824894) //112
NHSTUB(DoAELock                               ,0xff8270cc) //120
NHSTUB(DoAFLock                               ,0xff826bb8) //120
NHSTUB(EnterToCompensationEVF                 ,0xff826f2c) //104
NHSTUB(ExecuteEventProcedure                  ,0xff81c270) //104
NHSTUB(ExitFromCompensationEVF                ,0xff826f7c) //104
NHSTUB(ExitTask                               ,0xff81be48) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff834214) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff8343d4) //104
NHSTUB(Fclose_Fut                             ,0xff824a10) //120
NHSTUB(Feof_Fut                               ,0xff824bfc) //  1
NHSTUB(Fflush_Fut                             ,0xff824c38) //  1
NHSTUB(Fgets_Fut                              ,0xff824b64) //  1
NHSTUB(Fopen_Fut                              ,0xff8249d0) //120
NHSTUB(Fread_Fut                              ,0xff824abc) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82993c) //112
NHSTUB(Fseek_Fut                              ,0xff824bb0) //120
NHSTUB(Fwrite_Fut                             ,0xff824b10) //120
NHSTUB(GetBatteryTemperature                  ,0xff846b30) //102
NHSTUB(GetCurrentAvValue                      ,0xff924f7c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff84d8a0) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff84d940) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff84d8d4) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff923634) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff923940) //  1
NHSTUB(GetKbdState                            ,0xff844408) //109
NHSTUB(GetMemInfo                             ,0xff813c58) //115
NHSTUB(GetOpticalTemperature                  ,0xff846ba0) //120
NHSTUB(GetParameterData                       ,0xff9436ec) //  1
NHSTUB(GetPropertyCase                        ,0xff869470) //101
NHSTUB(GetSystemTime                          ,0xffa1d890) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8c0e50) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8c0e5c) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xff928038) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffa14b84) //102
NHSTUB(GiveSemaphore                          ,0xff81bb24) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8b4cbc) //102
NHSTUB(LEDDrive                               ,0xff8439fc) //120
NHSTUB(LocalTime                              ,0xff865240) //115
NHSTUB(LockMainPower                          ,0xff86d04c) //120
NHSTUB(MakeDirectory_Fut                      ,0xff824908) //116
NHSTUB(MoveFocusLensToDistance                ,0xff9e5f64) //102
NHSTUB(MoveIrisWithAv                         ,0xff925208) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff928ae4) //120
NHSTUB(Open                                   ,0xff825004) //120
NHSTUB(PB2Rec                                 ,0xff870204) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff8605e8) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff8605b0) //120
NHSTUB(PT_PlaySound                           ,0xff86015c) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xff86ae94) //120
NHSTUB(PostLogicalEventToUI                   ,0xff86aee0) //120
NHSTUB(Read                                   ,0xff81a440) //120
NHSTUB(ReadFastDir                            ,0xffa040d4) //  1
NHSTUB(Rec2PB                                 ,0xff86ebfc) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff99e624) //104
NHSTUB(RenameFile_Fut                         ,0xff824840) //  1
NHSTUB(Restart                                ,0xff82b964) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xff9e81ac) //102
NHSTUB(SetAutoShutdownTime                    ,0xff86d0c0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff874b44) //120
NHSTUB(SetFileAttributes                      ,0xff825358) //  1
NHSTUB(SetFileTimeStamp                       ,0xff825308) //  1
NHSTUB(SetLogicalEventActive                  ,0xff86cc7c) //  1
NHSTUB(SetParameterData                       ,0xff94365c) //101
NHSTUB(SetPropertyCase                        ,0xff869368) //103
NHSTUB(SetScriptMode                          ,0xff86cccc) //120
NHSTUB(SleepTask                              ,0xff829790) //120
NHSTUB(TakeSemaphore                          ,0xff81ba54) //120
NHSTUB(TurnOffBackLight                       ,0xff87a148) //104
NHSTUB(TurnOnBackLight                        ,0xff87a130) //104
NHSTUB(TurnOnDisplay                          ,0xff8403fc) //120
NHSTUB(TurnOffDisplay                         ,0xff84040c) //120
NHSTUB(UnlockAE                               ,0xff827108) //120
NHSTUB(UnlockAF                               ,0xff826c08) //120
NHSTUB(UnlockMainPower                        ,0xff86cfa0) //120
NHSTUB(UnsetZoomForMovie                      ,0xff94a2c4) //104
NHSTUB(UpdateMBROnFlash                       ,0xff84d668) //105
NHSTUB(VbattGet                               ,0xff8219a8) //120
NHSTUB(Write                                  ,0xff8250d8) //120
NHSTUB(WriteSDCard                            ,0xff9182fc) //108
NHSTUB(_log                                   ,0xffa8d318) //111
NHSTUB(_log10                                 ,0xffa8c25c) //112
NHSTUB(_pow                                   ,0xffa8c3cc) //121
NHSTUB(_sqrt                                  ,0xffa8e680) //  1
NHSTUB(add_ptp_handler                        ,0xff8caa9c) //121
NHSTUB(apex2us                                ,0xff99fadc) //121
NHSTUB(close                                  ,0xff81a258) //109
NHSTUB(err_init_task                          ,0xff814eb0) //111
NHSTUB(exmem_alloc                            ,0xff866388) //102
NHSTUB(exmem_free                             ,0xff866400) //102
NHSTUB(free                                   ,0xff813ab0) //112
NHSTUB(kbd_p1_f                               ,0xff8231d0) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8231dc) //109
NHSTUB(kbd_p2_f                               ,0xff822a1c) //109
NHSTUB(kbd_read_keys                          ,0xff8230cc) //109
NHSTUB(kbd_read_keys_r2                       ,0xff843fa8) //109
NHSTUB(lseek                                  ,0xff82516c) //120
NHSTUB(malloc                                 ,0xff8139dc) //112
NHSTUB(memcmp                                 ,0xff81e8f4) //120
NHSTUB(memcpy                                 ,0xff88fb00) //120
NHSTUB(memset                                 ,0xffa5b468) //120
NHSTUB(mkdir                                  ,0xff8253d0) //109
NHSTUB(mktime_ext                             ,0xff89036c) //  1
NHSTUB(open                                   ,0xff81a1a8) //109
NHSTUB(OpenFastDir                            ,0xffa04040) //  1
NHSTUB(closedir                               ,0xffa041a4) //  1
NHSTUB(qsort                                  ,0xff99eeb4) //  1
NHSTUB(rand                                   ,0xff81e9fc) //121
NHSTUB(realloc                                ,0xff813b90) //115
NHSTUB(reboot_fw_update                       ,0xffa0ba98) //106
NHSTUB(set_control_event                      ,0xff86c968) //  1
NHSTUB(srand                                  ,0xff81e9f0) //122
NHSTUB(stat                                   ,0xff825238) //  1
NHSTUB(strcat                                 ,0xff88fa2c) //  1
NHSTUB(strchr                                 ,0xff88fab4) //  1
NHSTUB(strcmp                                 ,0xff81e88c) //120
NHSTUB(strcpy                                 ,0xff81e838) //120
NHSTUB(strftime                               ,0xff88fd74) //  1
NHSTUB(strlen                                 ,0xff81e8d0) //120
NHSTUB(strncmp                                ,0xff88fa68) //  1
NHSTUB(strncpy                                ,0xff81e850) //  1
NHSTUB(strrchr                                ,0xff88fad8) //  1
NHSTUB(strtol                                 ,0xff82ff78) //101
NHSTUB(strtolx                                ,0xff82fd7c) //109
   DEF(task_CaptSeq                           ,0xff85bd10) //120
   DEF(task_ExpDrv                            ,0xff8aebf4) //120
   DEF(task_FileWrite                         ,0xffa021bc) //120
   DEF(task_InitFileModules                   ,0xff870ce8) //120
   DEF(task_MovieRecord                       ,0xff85821c) //120
   DEF(task_PhySw                             ,0xff822d78) //120
NHSTUB(time                                   ,0xff865744) //109
NHSTUB(vsprintf                               ,0xff81e7b8) //115
NHSTUB(EngDrvRead                             ,0xff823fd4) //102
