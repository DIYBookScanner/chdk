#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 7 // filewritetask is prepared for this many chunks
                              // Found in sub_FF339D5C (1.00a) --> "CMP     R0, #6" and
                              // corresponds to filewritetask() jump table entries 0-6
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1;
    int file_offset;
    int full_size;
    int unkn2, unkn3;
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    int seek_flag;      // offset from start 0x4c = 76 bytes = 19 words
    int unkn4, unkn5;
    char name[32];      // offset from start 0x58 = 88 bytes = 22 words
} fwt_data_struct;
// seek_flag is different:
// seek state is activated (from state 0xc, open) when
// (word at 0x4c) AND 0x40
// OR
// write offset is not 0
#define FWT_MUSTSEEK    0x40   // value of the masked seek_flag indicating seek is required
#define FWT_SEEKMASK    0x40   // masks out unneeded bits of seek_flag

#include "../../../generic/filewrite.c"
