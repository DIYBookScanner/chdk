// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R20 (DRYOS version 2.3, release #0020)
//   Firmware Ver GM1.01B   // Found @ 0xff8738e8, "GM1.01B" @ 0xff8738f5
//   Firmware build timestamp: Jun 14 2007 20:11:19
//   Canon PowerShot S5 IS

// Values for makefile.inc
//   PLATFORMOSVER = 20
//   PLATFORMID = 12616 (0x3148) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x03ffffff
//   MEMISOSTART = 0x0009b610
//   KEYSYS = d3                 // Found @ 0xffff31c8

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
//NHSTUB(GetZoomLensCurrentPoint              ,0xff957774) //120        *** != 0xff957cbc
//NHSTUB(GetZoomLensCurrentPosition           ,0xff9575f0) //102        *** != 0xff957cc0
//NHSTUB(Lseek                                ,0xff825e04) //120        *** != 0xff825ecc
//NHSTUB(Read                                 ,0xff81a200) //120        *** != 0xff825d6c
//NHSTUB(SetParameterData                     ,0xff972e4c) //  1 59%    *** != 0xff972ed4
// ERROR: UIFS_WriteFirmInfoToFile is not found.           //--- ---    *** != 0x00000000
//NHSTUB(kbd_pwr_off                          ,0xff84db70) //  2 67%    *** != 0x00000000
//NHSTUB(srand                                ,0xff81e760) //122        *** != 0xff81bcec
//NHSTUB(write                                ,0xff825d70) //120        *** != 0xff81a260

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffa45020 -> ffaefdf8
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x00011abc) // Found @0xff8238c8
DEF(physw_run                               ,0x00001cd8) // Found @0xff8235a4
DEF(physw_sleep_delay                       ,0x00001cda) // Found @0xff8235a4
DEF(levent_table                            ,0xffac64ec) // Found @0xffac64ec
DEF(FlashParamsTable                        ,0xffaeff98) // Found @0xffaeff98
DEF(movie_status                            ,0x000058a0) // Found @0xff862b98
DEF(canon_menu_active                       ,0x00006e3c) // Found @0xff897014
DEF(canon_shoot_menu_active                 ,0x0000c05d) // Found @0xff982580
DEF(playrec_mode                            ,0x00005aa0) // Found @0xff869c54
DEF(zoom_status                             ,0x000068f8) // Found @0xff88635c
DEF(some_flag_for_af_scan                   ,0x0000ecbc) // Found @0xffa3e1f4
DEF(focus_busy                              ,0x0000b27c) // Found @0xff950718
//DEF(recreview_hold                          ,0x000067c4) // Found @0xff882a00, ** != ** stubs_min = 0x0000be2c (0xBE2C)
// Camera appears to have only 1 RAW buffer @ 0x1163b8e0 (Found @0xffa11e84)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xff849fec
//void *vid_get_viewport_fb()      { return (void*)0x10d29360; }             // Found @0xffa103d8
DEF(jpeg_count_str                          ,0x00058304) // Found @0xff9be548
//char *camera_jpeg_count_str()    { return (char*)0x00058304; }             // Found @0xff9be548
//long hook_raw_size()             { return 0x009dcce0; }                    // Found @0xffa11ee0
//int get_flash_params_count(void) { return 0x6f; }                          // Found @0xff972f9c

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00020000 // Found @0xffa9cdc4, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00200000 // Found @0xffa9cde4, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_SHOOT_FULL      ,0x00000003 }, // Found @0xffa9ccbc, levent 0x01
//    { 0, KEY_SHOOT_FULL_ONLY ,0x00000002 }, // Found @0xffa9ccbc, levent 0x01
//    { 0, KEY_SHOOT_HALF      ,0x00000001 }, // Found @0xffa9ccb4, levent 0x00
//    { 0, KEY_PLAYBACK        ,0x00000004 }, // Found @0xffa9ccc4, levent 0x601 (uses inverted logic in physw_status)
//    { 1, KEY_LEFT            ,0x00001000 }, // Found @0xffa9cd34, levent 0x06
//    { 1, KEY_VIDEO           ,0x00002000 }, // Found @0xffa9cd3c, levent 0x12
//    { 1, KEY_SET             ,0x00010000 }, // Found @0xffa9cd4c, levent 0x08
//    { 1, KEY_DISPLAY         ,0x00020000 }, // Found @0xffa9cd54, levent 0x0a
//    { 1, KEY_MENU            ,0x00040000 }, // Found @0xffa9cd5c, levent 0x09
//    { 1, KEY_DOWN            ,0x00080000 }, // Found @0xffa9cd64, levent 0x05
//    { 1, KEY_UP              ,0x00100000 }, // Found @0xffa9cd6c, levent 0x04
//    { 1, KEY_RIGHT           ,0x00200000 }, // Found @0xffa9cd74, levent 0x07
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_RAW_ROWPIX    *** Not Found ***
//#define CAM_RAW_ROWS      *** Not Found ***
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xff82ad10

// Misc stuff
DEF(ctypes, 0xffa9635a)

// For capt_seq.c
DEF(_nrflag,0xb704) // Found @ ff960ff4 (0xb704)
//static long *nrflag = (long*)(0xb704);       // Found @ ff960ff4

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xff82acd4) //112
NHSTUB(Close                                  ,0xff825cc4) //120
NHSTUB(CreateTask                             ,0xff81b8fc) //120
NHSTUB(DebugAssert                            ,0xff81bccc) //111
NHSTUB(DeleteDirectory_Fut                    ,0xff825610) //116
NHSTUB(DeleteFile_Fut                         ,0xff82552c) //112
NHSTUB(DoAELock                               ,0xff82814c) //120
NHSTUB(DoAFLock                               ,0xff827bc8) //120
NHSTUB(EnterToCompensationEVF                 ,0xff827fa8) //104
NHSTUB(ExecuteEventProcedure                  ,0xff81be9c) //104
NHSTUB(ExitFromCompensationEVF                ,0xff82809c) //104
NHSTUB(ExitTask                               ,0xff81bb8c) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xff838dd8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xff838e80) //104
NHSTUB(Fclose_Fut                             ,0xff8256a8) //120
NHSTUB(Feof_Fut                               ,0xff825894) //  1
NHSTUB(Fflush_Fut                             ,0xff8258d0) //  1
NHSTUB(Fgets_Fut                              ,0xff8257fc) //  1
NHSTUB(Fopen_Fut                              ,0xff825668) //120
NHSTUB(Fread_Fut                              ,0xff825754) //120
NHSTUB(FreeUncacheableMemory                  ,0xff82ad08) //112
NHSTUB(Fseek_Fut                              ,0xff825848) //120
NHSTUB(Fwrite_Fut                             ,0xff8257a8) //120
NHSTUB(GetBatteryTemperature                  ,0xff850564) //102
NHSTUB(GetCCDTemperature                      ,0xff8504f4) //102
NHSTUB(GetCurrentAvValue                      ,0xff952d94) //120
NHSTUB(GetDrive_ClusterSize                   ,0xff856d08) //  1
NHSTUB(GetDrive_FreeClusters                  ,0xff856da8) //  1
NHSTUB(GetDrive_TotalClusters                 ,0xff856d3c) //  1
NHSTUB(GetFocusLensSubjectDistance            ,0xff9511a4) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xff9514a0) //  1
NHSTUB(GetKbdState                            ,0xff84da24) //109
NHSTUB(GetMemInfo                             ,0xff813ca8) //115
NHSTUB(GetOpticalTemperature                  ,0xff8505d4) //120
NHSTUB(GetParameterData                       ,0xff972f60) //101
NHSTUB(GetPropertyCase                        ,0xff87479c) //101
NHSTUB(GetSystemTime                          ,0xffa411a4) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xff841228) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xff841234) //120
NHSTUB(GiveSemaphore                          ,0xff81b868) //120
NHSTUB(IsStrobeChargeCompleted                ,0xff8db534) //102
NHSTUB(LEDDrive                               ,0xff84cf24) //120
NHSTUB(LocalTime                              ,0xff870604) //115
NHSTUB(LockMainPower                          ,0xff877d30) //120
NHSTUB(MakeDirectory_Fut                      ,0xff8255a0) //116
NHSTUB(MoveFocusLensToDistance                ,0xffa0d41c) //102
NHSTUB(MoveIrisWithAv                         ,0xff9536f0) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xff957b34) //120
NHSTUB(Open                                   ,0xff825c9c) //120
NHSTUB(PB2Rec                                 ,0xff87b318) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xff86b964) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xff86b930) //120
NHSTUB(PT_PlaySound                           ,0xff86b4dc) //103
NHSTUB(PostLogicalEventForNotPowerType        ,0xff8760b4) //120
NHSTUB(PostLogicalEventToUI                   ,0xff876100) //120
NHSTUB(PutInNdFilter                          ,0xffa0bd00) //102
NHSTUB(PutOutNdFilter                         ,0xffa0bd38) //102
NHSTUB(ReadFastDir                            ,0xffa27900) //  1
NHSTUB(Rec2PB                                 ,0xff87b358) //104
NHSTUB(RefreshPhysicalScreen                  ,0xff8b2d90) //120
NHSTUB(RenameFile_Fut                         ,0xff8254d8) //  1
NHSTUB(Restart                                ,0xff82cd1c) //106
NHSTUB(SetAE_ShutterSpeed                     ,0xffa0f5b8) //102
NHSTUB(SetAutoShutdownTime                    ,0xff877e90) //120
NHSTUB(SetCurrentCaptureModeType              ,0xff87f884) //120
NHSTUB(SetFileAttributes                      ,0xff825ff0) //  1
NHSTUB(SetFileTimeStamp                       ,0xff825fa0) //  1
NHSTUB(SetLogicalEventActive                  ,0xff877aec) //  1
NHSTUB(SetPropertyCase                        ,0xff8746ac) //101
NHSTUB(SetScriptMode                          ,0xff877b3c) //120
NHSTUB(SleepTask                              ,0xff82ab58) //120
NHSTUB(TakeSemaphore                          ,0xff81b798) //120
NHSTUB(TurnOffBackLight                       ,0xff8883a0) //104
NHSTUB(TurnOnBackLight                        ,0xff888388) //104
NHSTUB(TurnOnDisplay                          ,0xff84a09c) //120
NHSTUB(TurnOffDisplay                         ,0xff84a0ac) //120
NHSTUB(UnlockAE                               ,0xff828188) //120
NHSTUB(UnlockAF                               ,0xff827c34) //120
NHSTUB(UnlockMainPower                        ,0xff877c8c) //120
NHSTUB(UpdateMBROnFlash                       ,0xff856ad0) //105
NHSTUB(VbattGet                               ,0xff822204) //120
NHSTUB(Write                                  ,0xff825d70) //120
NHSTUB(WriteSDCard                            ,0xff944124) //108
NHSTUB(_log                                   ,0xffa93ecc) //111
NHSTUB(_log10                                 ,0xffa92e10) //112
NHSTUB(_pow                                   ,0xffa92f80) //121
NHSTUB(_sqrt                                  ,0xffa95234) //  1
NHSTUB(add_ptp_handler                        ,0xff8f03c4) //121
NHSTUB(apex2us                                ,0xff9cae4c) //121
NHSTUB(close                                  ,0xff81a018) //109
NHSTUB(err_init_task                          ,0xff814f00) //111
NHSTUB(exmem_alloc                            ,0xff871424) //101
NHSTUB(exmem_free                             ,0xff871398) //101
NHSTUB(free                                   ,0xff813b00) //112
NHSTUB(kbd_p1_f                               ,0xff8239a4) //109
NHSTUB(kbd_p1_f_cont                          ,0xff8239b0) //109
NHSTUB(kbd_p2_f                               ,0xff823244) //109
NHSTUB(kbd_read_keys                          ,0xff8238c8) //109
NHSTUB(kbd_read_keys_r2                       ,0xff84d3e4) //109
NHSTUB(lseek                                  ,0xff825e04) //120
NHSTUB(malloc                                 ,0xff813a2c) //112
NHSTUB(memcmp                                 ,0xff81e664) //120
NHSTUB(memcpy                                 ,0xff8b3200) //120
NHSTUB(memset                                 ,0xffa64b94) //120
NHSTUB(mkdir                                  ,0xff826068) //109
NHSTUB(mktime_ext                             ,0xff8b3a6c) //  1
NHSTUB(open                                   ,0xff819f68) //109
NHSTUB(OpenFastDir                            ,0xffa2786c) //  1
NHSTUB(closedir                               ,0xffa279d0) //  1
NHSTUB(qsort                                  ,0xff9ca224) //  1
NHSTUB(rand                                   ,0xff81e76c) //121
NHSTUB(realloc                                ,0xff813be0) //115
NHSTUB(reboot_fw_update                       ,0xffa2f75c) //106
NHSTUB(set_control_event                      ,0xff8778c0) //  1
NHSTUB(stat                                   ,0xff825ed0) //  1
NHSTUB(strcat                                 ,0xff8b312c) //  1
NHSTUB(strchr                                 ,0xff8b31b4) //  1
NHSTUB(strcmp                                 ,0xff81e5fc) //120
NHSTUB(strcpy                                 ,0xff81e5a8) //120
NHSTUB(strftime                               ,0xff8b3474) //  1
NHSTUB(strlen                                 ,0xff81e640) //120
NHSTUB(strncmp                                ,0xff8b3168) //  1
NHSTUB(strncpy                                ,0xff81e5c0) //  1
NHSTUB(strrchr                                ,0xff8b31d8) //  1
NHSTUB(strtol                                 ,0xff831ce4) //101
NHSTUB(strtolx                                ,0xff831ae8) //109
   DEF(task_CaptSeq                           ,0xff866c80) //120
   DEF(task_ExpDrv                            ,0xff8d37c0) //120
   DEF(task_FileWrite                         ,0xffa25b10) //120
   DEF(task_InitFileModules                   ,0xff87bf28) //120
   DEF(task_MovieRecord                       ,0xff862e48) //120
   DEF(task_PhySw                             ,0xff8235a0) //120
NHSTUB(time                                   ,0xff870b08) //109
NHSTUB(vsprintf                               ,0xff81e528) //115
NHSTUB(EngDrvRead                             ,0xff8247a4) //102
