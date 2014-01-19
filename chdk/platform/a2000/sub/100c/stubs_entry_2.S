#include "stubs_asm.h"
#define NULL_SUB 0xFFC00940

// Override stubs_entry.S
NHSTUB(ExecuteEventProcedure,       0xffc5543c)
NHSTUB(GetBatteryTemperature,       0xFFC33494) //point to GetCCDTemperature
NHSTUB(Lseek,                       0xFFC1354C)
NHSTUB(Read,                        0xFFC133EC)
NHSTUB(kbd_pwr_off,                 0xFFC31418)
NHSTUB(write,                       0xffc0a198)

// These don't exist/aren't found in dryos
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(CloseConsole,                0xFFC0C954)
NHSTUB(CPrintf,                     0xFFC0C6B0)
NHSTUB(CPutChar,                    0xFFC0C70C)
NHSTUB(CreateCountingSemaphore,     0xFFC0B648)
NHSTUB(CreateProxyOfEventProcedure, 0xFFC55E08)
NHSTUB(DeleteProxyOfEventProcedure, 0xFFC55E60)
NHSTUB(DeleteSemaphore,             0xFFC0B6A0)
NHSTUB(ExportToEventProcedure,      0xFFC55DFC)
NHSTUB(GetCh,                       0xFFC0C738)
NHSTUB(GetStringWithPrompt,         0xFFC0C788)
NHSTUB(GetTimeOfSystem,             0xFFD15828)
NHSTUB(OpenConsole,                 0xFFC0C7E8)
NHSTUB(PostLEDMessage,              0xFFC30908)
NHSTUB(RotateConsoleZOder,          0xFFC0C4A0)
NHSTUB(WriteToRom,                  0xFFD117F0)
NHSTUB(atol,                        0xFFC6C8D0)
NHSTUB(closefastdir,                0xffddcf4c)
NHSTUB(sprintf,                     0xFFC0D7B4)
NHSTUB(sscanf,                      0xFFD7B328)
