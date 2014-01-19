#include "lolevel.h"
#include "platform.h"

typedef struct {
    unsigned int address;
    unsigned int length;
} cam_ptp_data_chunk; //camera specific structure

#define MAX_CHUNKS_FOR_JPEG 3 //model specific
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
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

void __attribute__((naked,noinline)) filewritetask(  ) { //0xFFC5655C
asm volatile (
"                STMFD   SP!, {R4,LR}\n"
"                LDR     R4, =0x19924\n"
"                SUB     SP, SP, #4\n"
"                B       loc_FFC56590\n"
"loc_FFC5656C:\n"
"                TST     R3, #4\n"
"                BEQ     loc_FFC5658C\n"
"                LDR     R0, [R4]\n"
"                BL      sub_FFC0FB44\n" // ClearEventFlag
"                LDR     R0, [R4]\n"
"                MOV     R1, #8\n"
"                BL      sub_FFC0F9A8\n" // SetEventFlag
"                B       loc_FFC56590\n"
"loc_FFC5658C:\n"
"                BL      sub_FFC564A4_my\n" // ->
"loc_FFC56590:\n"
"                MOV     R1, #7\n"
"                LDR     R0, [R4]\n"
"                MOV     R2, #0\n"
"                BL      sub_FFC0F988\n"
"                CMP     R0, #0\n"
"                MOV     R1, SP\n"
"                BEQ     loc_FFC565C0\n"
"                MOV     R1, #0x2B0\n"
"                LDR     R0, =0xFFC563F8\n" // "dwFWrite.c"
"                ADD     R1, R1, #1\n"
"                BL      sub_FFC03AE8\n" // DebugAssert
"                B       loc_FFC565D8\n"
"loc_FFC565C0:\n"
"                LDR     R0, [R4]\n"
"                BL      sub_FFC0FB94\n"  // GetEventFlagValue
"                LDR     R3, [SP]\n"
"                TST     R3, #2\n"
"                MOV     R1, #5\n"
"                BEQ     loc_FFC5656C\n"
"loc_FFC565D8:\n"
"                LDR     R3, =0x19928\n"
"                LDR     R0, [R3]\n"
"                BL      sub_FFC10E54\n" // Givesemaphore
"                BL      _ExitTask\n"
"                ADD     SP, SP, #4\n"
"                LDMFD   SP!, {R4,PC}\n"
    );
}

void __attribute__((naked,noinline)) sub_FFC564A4_my(  ) {
asm volatile (
"                STMFD   SP!, {R4,R5,LR}\n"
"                LDR     R2, =0x19908\n"
"                LDRH    R3, [R2]\n"
"                SUB     R3, R3, #1\n"
"                CMP     R3, #3\n"
"                LDRLS   PC, [PC,R3,LSL#2]\n"
//"                B       loc_FFC564F0\n"
"                LDR     PC, =0xFFC564F0\n"
"                .long loc_FFC564D0\n"
"                .long 0xFFC564E0\n"
"                .long 0xFFC564E0\n"
"                .long 0xFFC564E0\n"
// only the first case is hooked, remaining jump directly back to firmware
/*
"                DCD loc_FFC564E0\n"
"                DCD loc_FFC564E0\n"
"                DCD loc_FFC564E0\n"
*/
"loc_FFC564D0:\n"
"                LDR     R0, =0x198C8\n"
"                BL      sub_FFC56350_my\n" // ->
"                MOV     R4, R0\n"
//"                B       loc_FFC564F4\n"
"                LDR     PC,=0xFFC564F4\n" // jump back to frimware
/*
"loc_FFC564E0:\n"
"                LDR     R0, =0x198C8\n"
"                BL      sub_FFC56404\n" // LOCATION: dwFWrite.c:604
"                MOV     R4, R0\n"
"                B       loc_FFC564F4\n"
"loc_FFC564F0:\n"
"                MOV     R4, #1\n"
"loc_FFC564F4:\n"
"                CMP     R4, #0\n"
"                MOV     R1, #1\n"
"                LDMEQFD SP!, {R4,R5,PC}\n"
"                LDR     R3, =0x19924\n"
"                LDR     R0, [R3]\n"
"                BL      ClearEventFlag\n"
"                LDR     R3, =0x19930\n"
"                LDR     R5, [R3]\n"
"                LDR     R1, =0x1992C\n"
"                LDR     R12, =0x279C\n"
"                MOV     R3, #1\n"
"                MOV     R2, #0\n"
"                CMP     R5, #0\n"
"                STR     R3, [R1]\n"
"                MOV     R0, R4\n"
"                STR     R2, [R12]\n"
"                LDMEQFD SP!, {R4,R5,PC}\n"
"                MOV     LR, PC\n"
"                MOV     PC, R5\n"
"                LDMFD   SP!, {R4,R5,PC}\n"
*/
    );
}

void __attribute__((naked,noinline)) sub_FFC56350_my(  ) {
asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                MOV     R4, R0\n"
"                ADD     R5, R4, #0x1C\n"
"                MOV     R0, R5\n"
"                BL      sub_FFC56028\n"
"                LDR     R0, [R4,#0x3C]\n"
"                BL      sub_FFC5F0CC\n"
"                LDR     R3, [R4]\n"
"                MOV     R1, #0x600\n"
"                TST     R3, #0x10000\n"
"                ADD     R1, R1, #1\n"
"                MOV     R2, #0x1B4\n"
"                ORRNE   R1, R1, #0x8000\n"
"                LDR     R3, [R4,#0x3C]\n"
"                ADD     R2, R2, #2\n"
// hook
      "STMFD SP!, {R1-R12,LR}\n"
      "MOV R0, R4\n"
      "BL filewrite_main_hook\n"
      "BL filewrite_jpeg_complete\n"
      "CMP R0, #0\n"
      "LDRNE R0, =0xFFC01A04\n" // "/null" as file name (works only on VxWorks)
      "LDMFD SP!, {R1-R12,LR}\n"
      "MOVEQ R0, R5\n" //canon file name
//hook end
//"                MOV     R0, R5\n"
"                LDR   PC, =0xFFC56390\n" // jump back to firmware
/*
"                BL      sub_FFC5612C\n"
"                MOV     R1, R4\n"
"                MOV     R2, R0\n"
"                MOV     R4, #0\n"
"                LDR     R3, =0x1990C\n"
"                CMP     R2, R4\n"
"                LDR     R6, =0x19908\n"
"                MOV     R0, R5\n"
"                STR     R2, [R3]\n"
"                BGT     loc_FFC563D0\n"
"                BL      sub_FFC5603C\n"
"                MOVL    R0, 0x9200001\n"
"                BL      sub_FFC53D30\n"
"                MOV     R0, #2\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
"loc_FFC563D0:\n"
"                LDR     R3, =0x19910\n"
"                LDRH    R0, [R6]\n"
"                STR     R4, [R3]\n"
"                BL      sub_FFC562A0\n"
"                STRH    R0, [R6]\n"
"                MOV     R0, R4\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
*/
    );
}

