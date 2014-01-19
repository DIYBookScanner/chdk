#include "stubs_asm.h"
#define NULL_SUB 0xff8141d8

//Definitions for code_gen
DEF(task_InitFileModules,           0xff997208)
DEF(task_MovieRecord,               0xff9482bc)
DEF(task_CaptSeq,                   0xff9533c4)
DEF(task_ExpDrv,                    0xff8fa108)
DEF(task_FileWrite,                 0xff86ac3c)

// Override stubs_entry.S
NHSTUB(VbattGet,                    0xff82f0f4)  //close to **"VbattGet" string
NHSTUB(free,                        0xffc1d8f8)  //There is a call to free close to "Memory.c" string
NHSTUB(GetDrive_ClusterSize,        0xff872990)  //by comparison to ixus65 100a
NHSTUB(GetDrive_FreeClusters,       0xff86b75c)  //close to **"AvailClusters.c"
NHSTUB(GetDrive_TotalClusters,      0xff8729cc)  //by comparison to ixus65 100a
NHSTUB(kbd_pwr_on,                  0xff82b05c)  //by comparsion to ixus65
NHSTUB(kbd_pwr_off,                 0xff82b078)  //by comparsion to ixus65
NHSTUB(UnlockAF,                    0xff94fa20)  //Close to "CompleteUnlockAF"
NHSTUB(DoAFLock,                    0xff94f9b8)  //by comparsion to ixus65 close to "CompleteAFLock"
NHSTUB(kbd_read_keys,               0xff829d60)  //by comparsion to ixus65
NHSTUB(kbd_read_keys_r2,            0xff82aaac)  //by comparison to ixus65
NHSTUB(kbd_p1_f,                    0xff829c94)  //autodetection OK
NHSTUB(kbd_p1_f_cont,               0xff829ca0)  //autodetection OK
NHSTUB(kbd_p2_f,                    0xff82a078)  //autodetection OK
NHSTUB(Mount_FileSystem,            0xff8724d0)  //autodetection OK
NHSTUB(EnterToCompensationEVF,      0xff951ab0)  //autodetection OK, similar to ixus55
NHSTUB(GetZoomLensCurrentPosition,  0xffb6608c)  //by comparison to ixus65
NHSTUB(Restart,                     0xff8252a0)  //by comparison to ixus65
NHSTUB(SetParameterData,            0xff96a23c)  //similar to ixus65

// To do:
//NHSTUB(ExitFromCompensationEVF                ,0xff95324c) //  2 90%
//NHSTUB(GetFocusLensSubjectDistance            ,0xffb751d8) //  1 96%
//NHSTUB(GetFocusLensSubjectDistanceFromLens    ,0xffb75778) //  3 92%
//NHSTUB(GetParameterData                       ,0xff96a31c) //  1 96%
//NHSTUB(GetSystemTime                          ,0xff81761c) //  1 96%
//NHSTUB(PutInNdFilter                          ,0xffb7ff84) //  1 92%
//NHSTUB(PutOutNdFilter                         ,0xffb7ffcc) //  1 94%
//NHSTUB(SetLogicalEventActive                  ,0xff963624) //  1 88%
//NHSTUB(UnsetZoomForMovie                      ,0xff9a7ce0) //  1 89%
//NHSTUB(add_ptp_handler                        ,0xffa62090) //  1 96%
//NHSTUB(exmem_alloc                            ,0xff814f44) //  2 93%
//NHSTUB(malloc                                 ,0xffc1d8ec) //  1 53%
//NHSTUB(taskIdListGet                          ,0xffc2c248) //  1 82%
//NHSTUB(localtime                              ,0xffc15040) //  1 93%
//NHSTUB(MakeAFScan                             ,0xff9542fc) //  1 96%

// Additional
NHSTUB(SetScriptMode,               0xff96368c)  //close to **"SetScriptMode" string
NHSTUB(UniqueLedOff,                0xff830b98)  //close to "gfff" found by comparison to ixus55 100b
NHSTUB(UniqueLedOn,                 0xff830b24)  //close to "gfff" found by comparison to ixus55 100b
NHSTUB(GiveSemaphore,               0xff82395c)  //from movie_record_task


// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

