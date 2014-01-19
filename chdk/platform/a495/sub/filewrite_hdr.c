#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 4 // filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 * pdc is always required
 * name is not currently used
 */
typedef struct
{
    int unkn1[5];
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    int unkn6;
    char name[32];                               // open stage: sub_FFDE69C0 (1.00f) --> "ADD     R0, R0, #0x38"
                                                 // offset of 'name' from start = 0x38 = 56 bytes = 14 words
} fwt_data_struct;

#include "../../../generic/filewrite.c"
