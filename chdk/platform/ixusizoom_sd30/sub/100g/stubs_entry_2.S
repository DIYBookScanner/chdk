#include "stubs_asm.h"
#define NULL_SUB 0xFF8118C0

// Override stubs_entry.S
NHSTUB(DisplayImagePhysicalScreen,  0xFF921F58)
NHSTUB(EnterToCompensationEVF,      0xFF948C84)
NHSTUB(ExitFromCompensationEVF,     0xFF948C94)
NHSTUB(VbattGet,                    0xFF82CF1C)
NHSTUB(free,                        0xFFAD366C)
NHSTUB(kbd_pwr_off,                 0xFF828F4C)
NHSTUB(kbd_pwr_on,                  0xFF828F30)
NHSTUB(kbd_read_keys_r2,            0xFF828950)

// Additional
NHSTUB(GetCurrentMachineTime,       0xFF81F2D4)
NHSTUB(GiveSemaphore,               0xFF8222B0)
NHSTUB(SetScriptMode,               0xFF95C208)
NHSTUB(SetTimerWhen,                0xFF815284)
NHSTUB(SetZoomActuatorSpeedPercent, 0xFFA712B8)
NHSTUB(kbd_read_keys,               0xFF827CB8)
NHSTUB(semBCreate,                  0xFFADF884)

NHSTUB(printf,                      0xFFACE29C)
NHSTUB(taskNameToId,                0xFFAE11C0)
