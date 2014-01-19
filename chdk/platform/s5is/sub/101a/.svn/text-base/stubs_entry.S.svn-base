// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R20 (DRYOS version 2.3, release #0020)
//   Firmware Ver GM1.01A   // Found @ 0xff8739b0, "GM1.01A" @ 0xff8739bd
//   Firmware build timestamp: May 29 2007 18:17:20
//   Canon PowerShot S5 IS

// Values for makefile.inc
//   PLATFORMOSVER = 20
//   PLATFORMID = 12616 (0x3148) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0009b610
//   KEYSYS = d3                 // Found @ 0xffff31c8

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetZoomLensCurrentPoint              ,0xff95783c) //120        *** != 0xff957d84
//NHSTUB(GetZoomLensCurrentPosition           ,0xff9576b8) //102        *** != 0xff957d88
//NHSTUB(Lseek                                ,0xff825ecc) //120        *** != 0xff825f94
//NHSTUB(Read                                 ,0xff81a2c8) //120        *** != 0xff825e34
//NHSTUB(SetParameterData                     ,0xff972f14) //  1 59%    *** != 0xff972f9c
// ERROR: UIFS_WriteFirmInfoToFile is not found.           //--- ---    *** != 0x00000000
//NHSTUB(kbd_pwr_off                          ,0xff84dc38) //  2 67%    *** != 0x00000000
//NHSTUB(srand                                ,0xff81e828) //122        *** != 0xff81bdb4
//NHSTUB(write                                ,0xff825e38) //120        *** != 0xff81a328

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa450e8 -> ffaefee8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00011abc) // Found @0xff823990
DEF(physw_run                               ,0x00001cd8) // Found @0xff82366c
DEF(physw_sleep_delay                       ,0x00001cda) // Found @0xff82366c
DEF(levent_table                            ,0xffac65dc) // Found @0xffac65dc
DEF(FlashParamsTable                        ,0xffaf0088) // Found @0xffaf0088
DEF(movie_status                            ,0x000058a0) // Found @0xff862c60
DEF(canon_menu_active                       ,0x00006e3c) // Found @0xff8970dc
DEF(canon_shoot_menu_active                 ,0x0000c05d) // Found @0xff982648
DEF(playrec_mode                            ,0x00005aa0) // Found @0xff869d1c
DEF(zoom_status                             ,0x000068f8) // Found @0xff886424
DEF(some_flag_for_af_scan                   ,0x0000ecbc) // Found @0xffa3e2bc
DEF(focus_busy                              ,0x0000b27c) // Found @0xff9507e0
//DEF(recreview_hold                          ,0x000067c4) // Found @0xff882ac8, ** != ** stubs_min = 0x0000be2c (0xBE2C)
// Camera appears to have only 1 RAW buffer @ 0x1163b8e0 (Found @0xffa11f4c)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff84a0b4
//void *vid_get_viewport_fb()      { return (void*)0x10d29360; }             // Found @0xffa104a0
DEF(jpeg_count_str                          ,0x00058304) // Found @0xff9be610
//char *camera_jpeg_count_str()    { return (char*)0x00058304; }             // Found @0xff9be610
//long hook_raw_size()             { return 0x009dcce0; }                    // Found @0xffa11fa8
//int get_flash_params_count(void) { return 0x6f; }                          // Found @0xff973064

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffa9ceb8, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00200000 // Found @0xffa9ced8, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffa9cdb0, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffa9cdb0, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffa9cda8, levent 0x00
//    { 0, KEY_PLAYBACK        ,0x00000004 }, // Found @0xffa9cdb8, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_LEFT            ,0x00001000 }, // Found @0xffa9ce28, levent 0x06
//    { 1, KEY_VIDEO           ,0x00002000 }, // Found @0xffa9ce30, levent 0x12
//    { 1, KEY_SET             ,0x00010000 }, // Found @0xffa9ce40, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00020000 }, // Found @0xffa9ce48, levent 0x0a
//    { 1, KEY_MENU            ,0x00040000 }, // Found @0xffa9ce50, levent 0x09
//    { 1, KEY_DOWN            ,0x00080000 }, // Found @0xffa9ce58, levent 0x05
//    { 1, KEY_UP              ,0x00100000 }, // Found @0xffa9ce60, levent 0x04
//    { 1, KEY_RIGHT           ,0x00200000 }, // Found @0xffa9ce68, levent 0x07
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    *** Not Found ***
//#define CAM_RAW_ROWS      *** Not Found ***
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff82add8

// Misc stuff
DEF(ctypes, 0xffa9644e)

// For capt_seq.c
DEF(_nrflag,0xb704) // Found @ ff9610bc (0xb704)
//static long *nrflag = (long*)(0xb704);       // Found @ ff9610bc

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff82ad9c) //112
NHSTUB(Close                                  ,0xff825d8c) //120
NHSTUB(CreateTask                             ,0xff81b9c4) //120
NHSTUB(DebugAssert                            ,0xff81bd94) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff8256d8) //116
NHSTUB(DeleteFile_Fut                         ,0xff8255f4) //112
NHSTUB(DoAELock                               ,0xff828214) //120
NHSTUB(DoAFLock                               ,0xff827c90) //120
NHSTUB(EnterToCompensationEVF                 ,0xff828070) //104
NHSTUB(ExecuteEventProcedure                  ,0xff81bf64) //104
NHSTUB(ExitFromCompensationEVF                ,0xff828164) //104
NHSTUB(ExitTask                               ,0xff81bc54) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff838ea0) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff838f48) //104
NHSTUB(Fclose_Fut                             ,0xff825770) //120
NHSTUB(Feof_Fut                               ,0xff82595c) //  1
NHSTUB(Fflush_Fut                             ,0xff825998) //  1
NHSTUB(Fgets_Fut                              ,0xff8258c4) //  1
NHSTUB(Fopen_Fut                              ,0xff825730) //120
NHSTUB(Fread_Fut                              ,0xff82581c) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82add0) //112
NHSTUB(Fseek_Fut                              ,0xff825910) //120
NHSTUB(Fwrite_Fut                             ,0xff825870) //120
NHSTUB(GetBatteryTemperature                  ,0xff85062c) //102
NHSTUB(GetCCDTemperature                      ,0xff8505bc) //102
NHSTUB(GetCurrentAvValue                      ,0xff952e5c) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff856dd0) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff856e70) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff856e04) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff95126c) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff951568) //  1
NHSTUB(GetKbdState                            ,0xff84daec) //109
NHSTUB(GetMemInfo                             ,0xff813ca8) //115
NHSTUB(GetOpticalTemperature                  ,0xff85069c) //120
NHSTUB(GetParameterData                       ,0xff973028) //101
NHSTUB(GetPropertyCase                        ,0xff874864) //101
NHSTUB(GetSystemTime                          ,0xffa4126c) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff8412f0) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff8412fc) //120
NHSTUB(GiveSemaphore                          ,0xff81b930) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8db5fc) //102
NHSTUB(LEDDrive                               ,0xff84cfec) //120
NHSTUB(LocalTime                              ,0xff8706cc) //115
NHSTUB(LockMainPower                          ,0xff877df8) //120
NHSTUB(MakeDirectory_Fut                      ,0xff825668) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa0d4e4) //102
NHSTUB(MoveIrisWithAv                         ,0xff9537b8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff957bfc) //120
NHSTUB(Open                                   ,0xff825d64) //120
NHSTUB(PB2Rec                                 ,0xff87b3e0) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86ba2c) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86b9f8) //120
NHSTUB(PT_PlaySound                           ,0xff86b5a4) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xff87617c) //120
NHSTUB(PostLogicalEventToUI                   ,0xff8761c8) //120
NHSTUB(PutInNdFilter                          ,0xffa0bdc8) //102
NHSTUB(PutOutNdFilter                         ,0xffa0be00) //102
NHSTUB(ReadFastDir                            ,0xffa279c8) //  1
NHSTUB(Rec2PB                                 ,0xff87b420) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8b2e58) //120
NHSTUB(RenameFile_Fut                         ,0xff8255a0) //  1
NHSTUB(Restart                                ,0xff82cde4) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffa0f680) //102
NHSTUB(SetAutoShutdownTime                    ,0xff877f58) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87f94c) //120
NHSTUB(SetFileAttributes                      ,0xff8260b8) //  1
NHSTUB(SetFileTimeStamp                       ,0xff826068) //  1
NHSTUB(SetLogicalEventActive                  ,0xff877bb4) //  1
NHSTUB(SetPropertyCase                        ,0xff874774) //101
NHSTUB(SetScriptMode                          ,0xff877c04) //120
NHSTUB(SleepTask                              ,0xff82ac20) //120
NHSTUB(TakeSemaphore                          ,0xff81b860) //120
NHSTUB(TurnOffBackLight                       ,0xff888468) //104
NHSTUB(TurnOnBackLight                        ,0xff888450) //104
NHSTUB(TurnOnDisplay                          ,0xff84a164) //120
NHSTUB(TurnOffDisplay                         ,0xff84a174) //120
NHSTUB(UnlockAE                               ,0xff828250) //120
NHSTUB(UnlockAF                               ,0xff827cfc) //120
NHSTUB(UnlockMainPower                        ,0xff877d54) //120
NHSTUB(UpdateMBROnFlash                       ,0xff856b98) //105
NHSTUB(VbattGet                               ,0xff8222cc) //120
NHSTUB(Write                                  ,0xff825e38) //120
NHSTUB(WriteSDCard                            ,0xff9441ec) //108
NHSTUB(_log                                   ,0xffa93fc0) //111
NHSTUB(_log10                                 ,0xffa92f04) //112
NHSTUB(_pow                                   ,0xffa93074) //121
NHSTUB(_sqrt                                  ,0xffa95328) //  1
NHSTUB(add_ptp_handler                        ,0xff8f048c) //121
NHSTUB(apex2us                                ,0xff9caf14) //121
NHSTUB(close                                  ,0xff81a0e0) //109
NHSTUB(err_init_task                          ,0xff814f00) //111
NHSTUB(exmem_alloc                            ,0xff8714ec) //101
NHSTUB(exmem_free                             ,0xff871460) //101
NHSTUB(free                                   ,0xff813b00) //112
NHSTUB(kbd_p1_f                               ,0xff823a6c) //109
NHSTUB(kbd_p1_f_cont                          ,0xff823a78) //109
NHSTUB(kbd_p2_f                               ,0xff82330c) //109
NHSTUB(kbd_read_keys                          ,0xff823990) //109
NHSTUB(kbd_read_keys_r2                       ,0xff84d4ac) //109
NHSTUB(lseek                                  ,0xff825ecc) //120
NHSTUB(malloc                                 ,0xff813a2c) //112
NHSTUB(memcmp                                 ,0xff81e72c) //120
NHSTUB(memcpy                                 ,0xff8b32c8) //120
NHSTUB(memset                                 ,0xffa64c5c) //120
NHSTUB(mkdir                                  ,0xff826130) //109
NHSTUB(mktime_ext                             ,0xff8b3b34) //  1
NHSTUB(open                                   ,0xff81a030) //109
NHSTUB(OpenFastDir                            ,0xffa27934) //  1
NHSTUB(closedir                               ,0xffa27a98) //  1
NHSTUB(qsort                                  ,0xff9ca2ec) //  1
NHSTUB(rand                                   ,0xff81e834) //121
NHSTUB(realloc                                ,0xff813be0) //115
NHSTUB(reboot_fw_update                       ,0xffa2f824) //106
NHSTUB(set_control_event                      ,0xff877988) //  1
NHSTUB(stat                                   ,0xff825f98) //  1
NHSTUB(strcat                                 ,0xff8b31f4) //  1
NHSTUB(strchr                                 ,0xff8b327c) //  1
NHSTUB(strcmp                                 ,0xff81e6c4) //120
NHSTUB(strcpy                                 ,0xff81e670) //120
NHSTUB(strftime                               ,0xff8b353c) //  1
NHSTUB(strlen                                 ,0xff81e708) //120
NHSTUB(strncmp                                ,0xff8b3230) //  1
NHSTUB(strncpy                                ,0xff81e688) //  1
NHSTUB(strrchr                                ,0xff8b32a0) //  1
NHSTUB(strtol                                 ,0xff831dac) //101
NHSTUB(strtolx                                ,0xff831bb0) //109
   DEF(task_CaptSeq                           ,0xff866d48) //120
   DEF(task_ExpDrv                            ,0xff8d3888) //120
   DEF(task_FileWrite                         ,0xffa25bd8) //120
   DEF(task_InitFileModules                   ,0xff87bff0) //120
   DEF(task_MovieRecord                       ,0xff862f10) //120
   DEF(task_PhySw                             ,0xff823668) //120
NHSTUB(time                                   ,0xff870bd0) //109
NHSTUB(vsprintf                               ,0xff81e5f0) //115
NHSTUB(EngDrvRead                             ,0xff82486c) //102
