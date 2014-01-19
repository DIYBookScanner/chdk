#include "stubs_asm.h"
#define NULL_SUB 0xFF8117E8

// Override stubs_entry.S
NHSTUB(DisplayImagePhysicalScreen,  0xFFA378A8)
NHSTUB(GetFocusLensSubjectDistance, 0xFFAEA6D4)
NHSTUB(GetFocusLensSubjectDistanceFromLens, 0xFFAEABD4)
NHSTUB(GetZoomLensCurrentPoint,     0xFFAFF7B4)
NHSTUB(GetZoomLensCurrentPosition,  0xFFAFF7C8)
NHSTUB(MoveZoomLensWithPoint,       0xFFAFF6D8)
NHSTUB(UnsetZoomForMovie,           NULL_SUB)
NHSTUB(free,                        0xFF92B488)
NHSTUB(kbd_read_keys_r2,            0xFFA4457C)

// These don't exist
NHSTUB(SetZoomActuatorSpeedPercent, NULL_SUB)

// Additional
NHSTUB(ExpCtrlTool_StartContiAE,    0xFF97799C)
NHSTUB(ExpCtrlTool_StopContiAE,     0xFF9779CC)
NHSTUB(PostLEDMessage,              0xFFA4290C)
NHSTUB(SetScriptMode,               0xFFB61474)
NHSTUB(UniqueLedOff,                0xFFA42CB0)
NHSTUB(UniqueLedOn,                 0xFFA42C08)
NHSTUB(GetVRAMHPixelsSize,0xFFA6AC20) // by find_eventproc name @ 0xFFBC6460
NHSTUB(GetVRAMVPixelsSize,0xFFA6AC2C) // by find_eventproc name @ 0xFFBC6468
