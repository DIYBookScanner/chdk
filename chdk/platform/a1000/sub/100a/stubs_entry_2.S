#include "stubs_asm.h"
#define NULL_SUB 0xFFC00940

// Override stubs_entry.S
NHSTUB(PT_PlaySound,                0xffc48fbc)
NHSTUB(SetAE_ShutterSpeed,          0xffe3de6c)
NHSTUB(kbd_pwr_off,                 0xffc3164c)

// Additional
NHSTUB(GetCurrentTargetDistance,    0xffcff6e4)
NHSTUB(PostLEDMessage,              0xffc30b34)
NHSTUB(RefreshUSBMode,              0xffc26cec)
NHSTUB(SetZoomActuatorSpeedPercent, 0xffde8f8c)
NHSTUB(TurnOffMic,                  0xffc31c88)
NHSTUB(TurnOnMic,                   0xffc31c5c)
NHSTUB(UniqueLedOff,                0xffcc5a14)
NHSTUB(UniqueLedOn,                 0xffcc59dc)
