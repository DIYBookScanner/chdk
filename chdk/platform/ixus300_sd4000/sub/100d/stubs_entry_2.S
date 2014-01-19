#include "stubs_asm.h"
#define NULL_SUB 0xFF810B1C

// Override stubs_entry.S
NHSTUB(DoAFLock,                    0xFF87A910)
NHSTUB(GetDrive_FreeClusters,       0xFF871E90)
NHSTUB(GetImageFolder,              0xFF94337C)
NHSTUB(MoveFocusLensToDistance,     0xFFB2289C)
NHSTUB(PutInNdFilter,               0xFFB2056C)
NHSTUB(PutOutNdFilter,              0xFFB205A4)
NHSTUB(ScreenLock,                  0xFFA1356C)
NHSTUB(SetScriptMode,               0xFF810F6C)
NHSTUB(UnlockAF,                    0xFF87A920)
NHSTUB(kbd_pwr_off,                 NULL_SUB)
NHSTUB(kbd_pwr_on,                  NULL_SUB)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)
NHSTUB(UnsetZoomForMovie,           NULL_SUB)

// Additional
NHSTUB(GetLogToFile,                0xFF975780)
NHSTUB(LockAndRefresh,              0xFFA13354)
NHSTUB(LogPrintf,                   0xFF88C920)
NHSTUB(PostLEDMessage,              0xFF860C6C)
NHSTUB(ScreenUnLock,                0xFFA12124)
NHSTUB(UnlockAndRefresh,            0xFFA13398)
NHSTUB(closefastdir,                0xFFA95C40)
NHSTUB(dumpMemoryToFile,            0xFF836004)
NHSTUB(get_ptp_handler,             0xFFA4EC7C)
NHSTUB(get_task_info,               0xFF813A38)
NHSTUB(get_task_lists,              0xFF83544C)
NHSTUB(remove_ptp_handler,          0xFFA4EBB0)
NHSTUB(taskResume,                  0xFF8955C4)
