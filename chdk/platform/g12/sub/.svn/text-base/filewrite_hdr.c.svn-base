#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

// Found in sub_FFAE0EFC (1.00c) --> "CMP     R0, #6"
#define MAX_CHUNKS_FOR_JPEG 7   // filewritetask is prepared for this many chunks
/*
 * fwt_data_struct: defined here as it's camera dependent
 * unneeded members are designated with unkn
 * pdc is required, everything after that is optional (DryOS < R50)
 * file_offset, full_size, seek_flag only needs to be defined for DryOS>=r50 generation cameras
 */
typedef struct
{
    int unkn1[5];                                   // sub_FFAE0EFC --> "LDR     R7, [R0, #0x14]!"
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    int unkn2;
    char name[32];                                  // sub_FFAE0DBC --> "ADD     R0, R0, #0x50"
                                                    // offset of 'name' from start = 0x50 = 80 bytes = 20 words
} fwt_data_struct;

#include "../../../generic/filewrite.c"
