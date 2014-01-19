#include "stubs_asm.h"
#define NULL_SUB 0xffc00b28

// These don't exist

NHSTUB(kbd_pwr_on,                      NULL_SUB)   // endereço dummy com uma instrução bx lr (um ret, creio)
NHSTUB(rand,                            NULL_SUB)   // Não encontrei manualmente
NHSTUB(srand,                           NULL_SUB)   // idem acima
NHSTUB(SetZoomActuatorSpeedPercent,     NULL_SUB)

// Override stubs_entry.S

NHSTUB(mkdir, 0xffc267fc)   
NHSTUB(MakeAFScan, 0xffd1b2e0)   
NHSTUB(TurnOffMic, 0xffc444ec)   
NHSTUB(TurnOnMic, 0xffc44518)   
