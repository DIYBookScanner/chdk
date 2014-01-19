// !!! THIS FILE IS GENERATED. DO NOT EDIT. !!!
#include "stubs_asm.h"

// Camera info:
//   DRYOS R43 (DRYOS version 2.3, release #0043)
//   Firmware Ver GM1.00D   // Found @ 0xffc684b0, "GM1.00D" @ 0xffc684bd
//   Firmware build timestamp: Dec  4 2009 16:32:56
//   Canon PowerShot A490

// Values for makefile.inc
//   PLATFORMOSVER = 43
//   PLATFORMID = 12784 (0x31f0) // Found @ 0xfffe0130
//   MAXRAMADDR = 0x01ffffff
//   MEMISOSTART = 0x00129140
//   KEYSYS = d4a                // Found @ 0xffff1a0c
//   NEED_ENCODED_DISKBOOT = 4   // Found @ 0xffff1a1c
//   ARAM_HEAP_START = 0x2ce000  // Found @ 0xffd18168
//   ARAM_HEAP_SIZE  = 0x32000   // Found @ 0xffd18128

// Stubs below should be checked. Stub not matched 100%, or difference found to current 'stubs_entry_2.S'
//    Name                                     Address      Rule  %  Comp to stubs_entry_2.S
NHSTUB(kbd_pwr_off                            ,0xffc435ec) //  2 64%

// Check of modemap from 'platform/CAMERA/shooting.c':
// Firmware modemap table found @ffe07c8c -> ffeca51c
// No problems found with modemap table.

// Values below can be overridden in 'stubs_min.S':
DEF(physw_status                            ,0x0002e754) // Found @0xffc23b2c
DEF(physw_run                               ,0x00001bf0) // Found @0xffc23790
DEF(physw_sleep_delay                       ,0x00001bee) // Found @0xffc23790
DEF(levent_table                            ,0xffe9fe64) // Found @0xffe9fe64
DEF(FlashParamsTable                        ,0xffeca70c) // Found @0xffeca70c
DEF(movie_status                            ,0x00005470) // Found @0xffd0c5f4
DEF(full_screen_refresh                     ,0x000072e8) // Found @0xffd79414
DEF(canon_menu_active                       ,0x00002a3c) // Found @0xffc69fd8
DEF(canon_shoot_menu_active                 ,0x00006571) // Found @0xffd3f9c0
DEF(playrec_mode                            ,0x00002798) // Found @0xffc5d7d8
DEF(zoom_status                             ,0x000095a8) // Found @0xffe0ab68
DEF(some_flag_for_af_scan                   ,0x00005818) // Found @0xffd0ef60
// focus_len_table contains zoom focus lengths for use in 'get_focal_length' (main.c).
// each entry contains 3 int value(s), the first is the zoom focus length.
// there are 7 entries in the table - set NUM_FL to 7
DEF(focus_len_table                         ,0xfffe2990) // Found @0xfffe2990
DEF(zoom_busy                               ,0x000053f0) // Found @0xffd09850
DEF(focus_busy                              ,0x00005300) // Found @0xffd06e88
DEF(recreview_hold                          ,0x0000302c) // Found @0xffc7578c
DEF(viewport_buffers                        ,0xffe88ea4) // Found @0xffcb5574
DEF(active_viewport_buffer                  ,0x000040f8) // Found @0xffcb53bc
// Camera appears to have only 1 RAW buffer @ 0x10e52420 (Found @0xffe56efc)

// Values below go in 'lib.c':
//void *vid_get_bitmap_fb()        { return (void*)0x10361000; }             // Found @0xffc3f024
//void *vid_get_viewport_fb()      { return (void*)0x10648cc0; }             // Found @0xffe53bd0
DEF(viewport_fb_d                           ,0x00002594) // Found 0x2540 (@0xffc528c4) + 0x54 (@0xffc528fc)
//void *vid_get_viewport_fb_d()    { return (void*)(*(int*)(0x2540+0x54)); } // Found @0xffc528c4 & 0xffc528fc
DEF(jpeg_count_str                          ,0x0007571c) // Found @0xffd70a4c
//char *camera_jpeg_count_str()    { return (char*)0x0007571c; }             // Found @0xffd70a4c
//long hook_raw_size()             { return 0x00ec04f0; }                    // Found @0xffe56f58
//int get_flash_params_count(void) { return 0x94; }                          // Found @0xffd2f034

// Bitmap masks and physw_status index values for SD_READONLY and USB power flags (for kbd.c).
//#define SD_READONLY_FLAG    0x00040000 // Found @0xffe820bc, levent 0x90a
//#define SD_READONLY_IDX     2
//#define USB_MASK            0x00080000 // Found @0xffe820c8, levent 0x902
//#define USB_IDX             2

// Keymap values for kbd.c. Additional keys may be present, only common values included here.
//static KeyMap keymap[] = {
//    { 0, KEY_PLAYBACK        ,0x00020000 }, // Found @0xffe82038, levent 0x601
//    { 0, KEY_POWER           ,0x00800000 }, // Found @0xffe82050, levent 0x600
//    { 2, KEY_RIGHT           ,0x00000004 }, // Found @0xffe8205c, levent 0x07
//    { 2, KEY_SHOOT_FULL      ,0x00000030 }, // Found @0xffe82074, levent 0x01
//    { 2, KEY_SHOOT_FULL_ONLY ,0x00000020 }, // Found @0xffe82074, levent 0x01
//    { 2, KEY_SHOOT_HALF      ,0x00000010 }, // Found @0xffe82068, levent 0x00
//    { 2, KEY_ZOOM_OUT        ,0x00000040 }, // Found @0xffe82080, levent 0x03
//    { 2, KEY_ZOOM_IN         ,0x00000080 }, // Found @0xffe8208c, levent 0x02
//    { 2, KEY_SET             ,0x00000100 }, // Found @0xffe82098, levent 0x08
//    { 2, KEY_UP              ,0x00100000 }, // Found @0xffe820d4, levent 0x04 (uses inverted logic in physw_status)
//    { 2, KEY_DOWN            ,0x00200000 }, // Found @0xffe820e0, levent 0x05 (uses inverted logic in physw_status)
//    { 2, KEY_LEFT            ,0x00400000 }, // Found @0xffe820ec, levent 0x06 (uses inverted logic in physw_status)
//    { 2, KEY_MENU            ,0x01000000 }, // Found @0xffe82104, levent 0x09 (uses inverted logic in physw_status)
//    { 0, 0, 0 }
//};

// Values below go in 'platform_camera.h':
//#define CAM_DRYOS         1
//#define CAM_DRYOS_2_3_R39 1 // Defined for cameras with DryOS version R39 or higher
//#define CAM_RAW_ROWPIX    3720 // Found @0xffcea048
//#define CAM_RAW_ROWS      2772 // Found @0xffcea054
//#undef  CAM_UNCACHED_BIT
//#define CAM_UNCACHED_BIT  0x10000000 // Found @0xffc29320

// Misc stuff
DEF(ctypes, 0xffe81956)

// For capt_seq.c
DEF(_nrflag,0x57f8) // Found @ ffd10d74 (0x5800) & ffd10d94 (-0x08)
//static long *nrflag = (long*)(0x5800-0x08);  // Found @ ffd10d74 & ffd10d90

// Stubs below matched 100%.
//    Name                                     Address                Comp to stubs_entry_2.S
NHSTUB(AllocateUncacheableMemory              ,0xffc292dc) //112
NHSTUB(Close                                  ,0xffc2610c) //120
NHSTUB(CreateTask                             ,0xffc0f1a8) //120
NHSTUB(DebugAssert                            ,0xffc0f680) //111
NHSTUB(DeleteDirectory_Fut                    ,0xffc25b68) //116
NHSTUB(DeleteFile_Fut                         ,0xffc25a84) //112
NHSTUB(DoAELock                               ,0xffc276a0) //120
NHSTUB(DoAFLock                               ,0xffc27558) //120
NHSTUB(EnterToCompensationEVF                 ,0xffc27608) //104
NHSTUB(ExecuteEventProcedure                  ,0xffc65748) //104
NHSTUB(ExitFromCompensationEVF                ,0xffc2764c) //104
NHSTUB(ExitTask                               ,0xffc0f438) //120
NHSTUB(ExpCtrlTool_StartContiAE               ,0xffc34ce8) //104
NHSTUB(ExpCtrlTool_StopContiAE                ,0xffc34dc0) //104
NHSTUB(Fclose_Fut                             ,0xffc25c00) //120
NHSTUB(Feof_Fut                               ,0xffc25dec) //  1
NHSTUB(Fflush_Fut                             ,0xffc25e28) //  1
NHSTUB(Fgets_Fut                              ,0xffc25d54) //  1
NHSTUB(Fopen_Fut                              ,0xffc25bc0) //120
NHSTUB(Fread_Fut                              ,0xffc25cac) //120
NHSTUB(FreeUncacheableMemory                  ,0xffc2931c) //112
NHSTUB(Fseek_Fut                              ,0xffc25da0) //120
NHSTUB(Fwrite_Fut                             ,0xffc25d00) //120
NHSTUB(GetBatteryTemperature                  ,0xffc45624) //102
NHSTUB(GetCCDTemperature                      ,0xffc455b0) //102
NHSTUB(GetCurrentAvValue                      ,0xffd08708) //120
NHSTUB(GetDrive_ClusterSize                   ,0xffc512bc) //122
NHSTUB(GetDrive_FreeClusters                  ,0xffc5131c) //  4
NHSTUB(GetDrive_TotalClusters                 ,0xffc512f0) //  3
NHSTUB(GetFocusLensSubjectDistance            ,0xffd07a00) //102
NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffd07e58) //  3
NHSTUB(GetImageFolder                         ,0xffcf1008) //122
NHSTUB(GetKbdState                            ,0xffc435d4) //109
NHSTUB(GetMemInfo                             ,0xffc0a7f8) //115
NHSTUB(GetOpticalTemperature                  ,0xffc4569c) //120
NHSTUB(GetParameterData                       ,0xffd2eff4) //101
NHSTUB(GetPropertyCase                        ,0xffc69454) //102
NHSTUB(GetSystemTime                          ,0xffdfa400) //120
NHSTUB(GetVRAMHPixelsSize                     ,0xffcb69ac) //120
NHSTUB(GetVRAMVPixelsSize                     ,0xffcb69b8) //120
NHSTUB(GetZoomLensCurrentPoint                ,0xffd09bc8) //120
NHSTUB(GetZoomLensCurrentPosition             ,0xffdf2444) //102
NHSTUB(GiveSemaphore                          ,0xffc0f104) //120
NHSTUB(IsStrobeChargeCompleted                ,0xffca6fa0) //102
NHSTUB(LEDDrive                               ,0xffc42bc8) //120
NHSTUB(LocalTime                              ,0xffc63458) //115
NHSTUB(LockMainPower                          ,0xffc6cd2c) //120
NHSTUB(MakeDirectory_Fut                      ,0xffc25af8) //116
NHSTUB(MoveFocusLensToDistance                ,0xffe50650) //102
NHSTUB(MoveIrisWithAv                         ,0xffdf7ae8) //120
NHSTUB(MoveZoomLensWithPoint                  ,0xffdf8074) //120
NHSTUB(Open                                   ,0xffc260a0) //120
NHSTUB(PB2Rec                                 ,0xffc6f998) //104
NHSTUB(PT_MoveDigitalZoomToWide               ,0xffc57098) //120
NHSTUB(PT_MoveOpticalZoomAt                   ,0xffc57070) //120
NHSTUB(PT_PlaySound                           ,0xffc5f2d8) //122
NHSTUB(PostLogicalEventForNotPowerType        ,0xffc6c55c) //120
NHSTUB(PostLogicalEventToUI                   ,0xffc6c5a8) //120
NHSTUB(PutInNdFilter                          ,0xffdf7ed8) //102
NHSTUB(PutOutNdFilter                         ,0xffdf7efc) //102
NHSTUB(Read                                   ,0xffc0b308) //120
NHSTUB(ReadFastDir                            ,0xffde8e40) //  4
NHSTUB(Rec2PB                                 ,0xffc6f9d8) //104
NHSTUB(RefreshPhysicalScreen                  ,0xffd79df0) //104
NHSTUB(RenameFile_Fut                         ,0xffc259f0) //116
NHSTUB(Restart                                ,0xffc2aab4) //106
NHSTUB(ScreenLock                             ,0xffd7af9c) //117
NHSTUB(ScreenUnlock                           ,0xffd7afe0) //117
NHSTUB(SetAE_ShutterSpeed                     ,0xffe52de0) //102
NHSTUB(SetAutoShutdownTime                    ,0xffc6cda0) //120
NHSTUB(SetCurrentCaptureModeType              ,0xffc730bc) //120
NHSTUB(SetFileAttributes                      ,0xffc26404) //  3
NHSTUB(SetFileTimeStamp                       ,0xffc263a8) //  4
NHSTUB(SetLogicalEventActive                  ,0xffc6caa4) //101
NHSTUB(SetParameterData                       ,0xffd2ef64) //101
NHSTUB(SetPropertyCase                        ,0xffc69324) //102
NHSTUB(SetScriptMode                          ,0xffc6caf4) //120
NHSTUB(SleepTask                              ,0xffc29160) //120
NHSTUB(TakeSemaphore                          ,0xffc0f034) //120
NHSTUB(TurnOffBackLight                       ,0xffc77d38) //104
NHSTUB(TurnOnBackLight                        ,0xffc77d20) //104
NHSTUB(TurnOnDisplay                          ,0xffc3f300) //120
NHSTUB(TurnOffDisplay                         ,0xffc3f32c) //120
NHSTUB(UIFS_WriteFirmInfoToFile               ,0xffd1f768) //120
NHSTUB(UnlockAE                               ,0xffc276c4) //120
NHSTUB(UnlockAF                               ,0xffc27590) //120
NHSTUB(UnlockMainPower                        ,0xffc6cc80) //120
NHSTUB(UnsetZoomForMovie                      ,0xffd354b4) //104
NHSTUB(UpdateMBROnFlash                       ,0xffc5113c) //105
NHSTUB(VbattGet                               ,0xffc22be4) //120
NHSTUB(Write                                  ,0xffc2619c) //120
NHSTUB(WriteSDCard                            ,0xffcfc6fc) //108
NHSTUB(_log                                   ,0xffe7f4b8) //111
NHSTUB(_log10                                 ,0xffe7e3fc) //112
NHSTUB(_pow                                   ,0xffe7e56c) //121
NHSTUB(_sqrt                                  ,0xffe80820) //  1
NHSTUB(add_ptp_handler                        ,0xffdbd2d4) //121
NHSTUB(apex2us                                ,0xffd7c2ec) //121
NHSTUB(close                                  ,0xffc0b120) //109
NHSTUB(err_init_task                          ,0xffc05f50) //111
NHSTUB(exmem_alloc                            ,0xffc640f8) //103
NHSTUB(exmem_free                             ,0xffc64170) //103
NHSTUB(free                                   ,0xffc04160) //112
NHSTUB(kbd_p1_f                               ,0xffc23ba8) //109
NHSTUB(kbd_p1_f_cont                          ,0xffc23bb4) //109
NHSTUB(kbd_p2_f                               ,0xffc2345c) //109
NHSTUB(kbd_read_keys                          ,0xffc23b2c) //109
NHSTUB(kbd_read_keys_r2                       ,0xffc42fb8) //109
NHSTUB(lseek                                  ,0xffc26228) //120
NHSTUB(malloc                                 ,0xffc04104) //112
NHSTUB(memcmp                                 ,0xffc11318) //120
NHSTUB(memcpy                                 ,0xffc2e864) //120
NHSTUB(memset                                 ,0xffd7b324) //120
NHSTUB(mkdir                                  ,0xffc265a8) //109
NHSTUB(mktime_ext                             ,0xffc7cb50) //  1
NHSTUB(open                                   ,0xffc0b070) //109
NHSTUB(OpenFastDir                            ,0xffde8cec) //  4
NHSTUB(closedir                               ,0xffde8c9c) //121
NHSTUB(qsort                                  ,0xffe39368) //  4
NHSTUB(rand                                   ,0xffc11420) //121
NHSTUB(realloc                                ,0xffd7b3a0) //115
NHSTUB(reboot_fw_update                       ,0xffdea6b4) //106
NHSTUB(set_control_event                      ,0xffc6c7c4) //111
NHSTUB(srand                                  ,0xffc11414) //122
NHSTUB(stat                                   ,0xffc26270) //109
NHSTUB(strcat                                 ,0xffc7c30c) //  1
NHSTUB(strchr                                 ,0xffc03fe8) //  1
NHSTUB(strcmp                                 ,0xffc112d4) //120
NHSTUB(strcpy                                 ,0xffc112bc) //120
NHSTUB(strftime                               ,0xffc7c558) //113
NHSTUB(strlen                                 ,0xffc04034) //120
NHSTUB(strncmp                                ,0xffc03f9c) //  1
NHSTUB(strncpy                                ,0xffc03f60) //  1
NHSTUB(strrchr                                ,0xffc0400c) //  1
NHSTUB(strtol                                 ,0xffc2eb44) //101
NHSTUB(strtolx                                ,0xffc2e948) //109
   DEF(task_CaptSeq                           ,0xffc5914c) //120
   DEF(task_ExpDrv                            ,0xffc91338) //120
   DEF(task_FileWrite                         ,0xffde3918) //120
   DEF(task_InitFileModules                   ,0xffc70464) //120
   DEF(task_MovieRecord                       ,0xffd0c848) //120
   DEF(task_PhySw                             ,0xffc2378c) //120
NHSTUB(time                                   ,0xffc6330c) //109
NHSTUB(vsprintf                               ,0xffc11280) //115
NHSTUB(EngDrvRead                             ,0xffc249fc) //102
