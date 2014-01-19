#include "lolevel.h"
#include "platform.h"

// ifdef allows easy building with/without filewrite support for testing
#ifdef CAM_HAS_FILEWRITETASK_HOOK
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
    int unkn1, unkn2, unkn3, unkn4, unkn5;
    cam_ptp_data_chunk pdc[MAX_CHUNKS_FOR_JPEG];
    char name[32];
} fwt_data_struct;

#include "../../../generic/filewrite.c"

void __attribute__((naked,noinline)) filewritetask() { // FFA25FB4 "FileWriteTask"
asm volatile (
"                STMFD   SP!, {R1-R5,LR}\n"
"                LDR     R4, =0x9314\n"
"loc_FFA25FBC:\n"
// jumptable FFA25FFC default entry
"                LDR     R0, [R4,#0x10]\n"
"                MOV     R2, #0\n"
"                ADD     R1, SP, #8\n"
"                BL      sub_FF826C30\n" // KerQueue.c 0
"                CMP     R0, #0\n"
"                BNE     loc_FFA25FEC\n"
"                LDR     R0, [SP,#8]\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #1\n"
"                BNE     loc_FFA25FF4\n"
"                LDR     R0, [R4,#8]\n"
"                BL      sub_FF82711C\n" // GiveSemaphore
"loc_FFA25FEC:\n"
"                BL      _ExitTask\n"
"                LDMFD   SP!, {R1-R5,PC}\n"
"loc_FFA25FF4:\n"
"                SUB     R1, R1, #2\n"
"                CMP     R1, #5\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FFA25FBC\n"
"                B       loc_FFA2601C\n"
"                B       loc_FFA26080\n"
"                B       loc_FFA26088\n"
"                B       loc_FFA26088\n"
"                B       loc_FFA26088\n"
"                B       loc_FFA26090\n"
"loc_FFA2601C:\n"
// jumptable FFA25FFC entry 0
"                MOV     R0, #0\n"
"                STR     R0, [SP]\n"
"loc_FFA26024:\n"
"                LDR     R0, [R4,#0x10]\n"
"                MOV     R1, SP\n"
"                BL      sub_FF826E74\n" // KerQueue.c 0
"                LDR     R0, [SP]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FFA26050\n"
"                LDR     R0, [R4,#0x10]\n"
"                MOV     R2, #0\n"
"                ADD     R1, SP, #4\n"
"                BL      sub_FF826C30\n" // KerQueue.c 0
"                B       loc_FFA26024\n"
"loc_FFA26050:\n"
"                LDR     R0, [R4]\n"
"                CMN     R0, #1\n"
"                BEQ     loc_FFA26074\n"
//"                BL      _Close\n"
"                BL      fwt_close\n" //+
"                MVN     R0, #0\n"
"                STR     R0, [R4]\n"
"                LDR     R0, =0xCD788\n"
"                BL      sub_FF855E18\n" // Mounter.c 0
"                BL      sub_FF8543A4\n" // FileSem.c 136
"loc_FFA26074:\n"
"                LDR     R0, [R4,#0xC]\n"
"                BL      sub_FF82711C\n" // GiveSemaphore
"                B       loc_FFA25FBC\n"
"loc_FFA26080:\n"
// jumptable FFA25FFC entry 1
"                BL      sub_FFA26268_my\n" //->
"                B       loc_FFA25FBC\n"
"loc_FFA26088:\n"
// jumptable FFA25FFC entries 2-4
"                BL      sub_FFA263B4_my\n" // dwFWrite.c 4 ->
"                B       loc_FFA25FBC\n"
"loc_FFA26090:\n"
// jumptable FFA25FFC entry 5
"                BL      sub_FFA264B0_my\n"
"                B       loc_FFA25FBC\n"

    );
}

void __attribute__((naked,noinline)) sub_FFA26268_my( ) {
asm volatile (
"                STMFD   SP!, {R4-R8,LR}\n"
"                MOV     R4, R0\n"
"                ADD     R0, R0, #0x2C\n"
"                SUB     SP, SP, #0x38\n"
"                BL      sub_FF855E18\n" // Mounter.c 0
"                MOV     R1, #0\n"
"                BL      sub_FF854354\n"
"                LDR     R0, [R4,#0xC]\n"
"                BL      sub_FF8527FC\n"
"                LDR     R7, [R4,#8]\n"
"                LDR     R8, =0x1B6\n"
"                ADD     R6, R4, #0x2C\n"
"                LDR     R5, [R4,#0xC]\n"
//hook start
      "STMFD SP!, {R4-R12,LR}\n"
      "MOV R0, R4\n"
      "BL filewrite_main_hook\n"
      "LDMFD SP!, {R4-R12,LR}\n"
//hook end

"                MOV     R0, R6\n"
"                MOV     R1, R7\n"
"                MOV     R2, R8\n"
//"                BL      _Open\n"
"                BL      fwt_open\n"
"                LDR     PC,=0xFFA262AC\n" // jump back to ROM
/*
"                CMN     R0, #1\n"
"                BNE     loc_FFA2630C\n"
"                MOV     R0, R6\n"
"                BL      sub_FF824190\n"
"                MOV     R2, #0xF\n"
"                MOV     R1, R6\n"
"                MOV     R0, SP\n"
"                BL      sub_FFACBD60\n"
"                LDR     R0, =0x41FF\n"
"                MOV     R1, #0\n"
"                STRB    R1, [SP,#0xF]\n"
"                STR     R0, [SP,#0x20]\n"
"                MOV     R0, #0x10\n"
"                ADD     R2, SP, #0x24\n"
"                STMIA   R2, {R0,R1,R5}\n"
"                ADD     R1, SP, #0x20\n"
"                MOV     R0, SP\n"
"                STR     R5, [SP,#0x30]\n"
"                STR     R5, [SP,#0x34]\n"
"                BL      sub_FF853C68\n"
"                MOV     R2, R8\n"
"                MOV     R1, R7\n"
"                MOV     R0, R6\n"
"                BL      _Open\n"
"loc_FFA2630C:\n"
"                LDR     R5, =0x9314\n"
"                CMN     R0, #1\n"
"                STR     R0, [R5]\n"
"                BNE     loc_FFA26354\n"
"                LDR     R0, [R5,#0x18]\n"
"                CMP     R0, #0\n"
"                BLXNE   R0\n"
"                ADD     R0, R4, #0x2C\n"
"                BL      sub_FF855E18\n" // Mounter.c 0
"                BL      sub_FF8543A4\n" // FileSem.c 136
"                LDR     R1, [R5,#0x14]\n"
"                CMP     R1, #0\n"
"                ADDNE   SP, SP, #0x38\n"
"                LDMNEFD SP!, {R4-R8,LR}\n"
"                LDRNE   R0, =0x9200001\n"
"                BXNE    R1\n"
"loc_FFA2634C:\n"
"                ADD     SP, SP, #0x38\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
"loc_FFA26354:\n"
"                LDR     R0, =0xCD788\n"
"                MOV     R2, #0x20\n"
"                ADD     R1, R4, #0x2C\n"
"                BL      sub_FFACBEC8\n"
"                MOV     R1, R4\n"
"                MOV     R0, #4\n"
"                BL      sub_FFA25F0C\n"
"                B       loc_FFA2634C\n"
*/
    );
}

void __attribute__((naked,noinline)) sub_FFA263B4_my( ) {
asm volatile (
"                STMFD   SP!, {R4-R10,LR}\n"
"                MOV     R4, R0\n"
"                LDR     R0, [R0]\n"
"                CMP     R0, #4\n"
"                LDREQ   R6, [R4,#0x18]\n"
"                LDREQ   R7, [R4,#0x14]\n"
"                BEQ     loc_FFA263F0\n"
"                CMP     R0, #5\n"
"                LDREQ   R6, [R4,#0x20]\n"
"                LDREQ   R7, [R4,#0x1C]\n"
"                BEQ     loc_FFA263F0\n"
"                CMP     R0, #6\n"
"                BNE     loc_FFA26404\n"
"                LDR     R6, [R4,#0x28]\n"
"                LDR     R7, [R4,#0x24]\n"
"loc_FFA263F0:\n"
"                CMP     R6, #0\n"
"                BNE     loc_FFA26414\n"
"loc_FFA263F8:\n"
"                MOV     R1, R4\n"
"                MOV     R0, #7\n"
"                B       loc_FFA264A8\n"
"loc_FFA26404:\n"
"                LDR     R1, =0x20D\n"
"                LDR     R0, =0xFFA26394\n" // "dwFWrite.c"
"                BL      sub_FF81B284\n" // DebugAssert
"                B       loc_FFA263F8\n"
"loc_FFA26414:\n"
"                LDR     R9, =0x9314\n"
"                MOV     R5, R6\n"
"loc_FFA2641C:\n"
"                LDR     R0, [R4,#4]\n"
"                CMP     R5, #0x1000000\n"
"                MOVLS   R8, R5\n"
"                MOVHI   R8, #0x1000000\n"
"                BIC     R1, R0, #0xFF000000\n"
"                CMP     R1, #0\n"
"                BICNE   R0, R0, #0xFF000000\n"
"                RSBNE   R0, R0, #0x1000000\n"
"                CMPNE   R8, R0\n"
"                MOVHI   R8, R0\n"
"                LDR     R0, [R9]\n"
"                MOV     R2, R8\n"
"                MOV     R1, R7\n"
//"                BL      _Write\n"
"                BL      fwt_write\n"
"                LDR     R1, [R4,#4]\n"
"                CMP     R8, R0\n"
"                ADD     R1, R1, R0\n"
"                STR     R1, [R4,#4]\n"
"                BEQ     loc_FFA2647C\n"
"                LDR     R0, =0x10B1\n"
"                BL      sub_FF877A6C\n" // IsControlEventActive
"                LDR     R1, =0x9200005\n"
"                STR     R1, [R4,#0x10]\n"
"                B       loc_FFA263F8\n"
"loc_FFA2647C:\n"
"                SUB     R5, R5, R0\n"
"                CMP     R5, R6\n"
"                ADD     R7, R7, R0\n"
"                LDRCS   R0, =0xFFA26394\n" // "dwFWrite.c"
"                MOVCS   R1, #0x23C\n"
"                BLCS    sub_FF81B284\n" // DebugAssert
"                CMP     R5, #0\n"
"                BNE     loc_FFA2641C\n"
"                LDR     R0, [R4]\n"
"                MOV     R1, R4\n"
"                ADD     R0, R0, #1\n"
"loc_FFA264A8:\n"
"                LDMFD   SP!, {R4-R10,LR}\n"
"                B       sub_FFA25F0C\n"
    );
}

void __attribute__((naked,noinline)) sub_FFA264B0_my( ) {
asm volatile (
"                STMFD   SP!, {R4,R5,LR}\n"
"                LDR     R5, =0x9314\n"
"                MOV     R4, R0\n"
"                LDR     R0, [R5]\n"
"                SUB     SP, SP, #0x1C\n"
"                CMN     R0, #1\n"
"                BEQ     loc_FFA264E4\n"
//"                BL      _Close\n"
"                BL      fwt_close\n"
"                CMP     R0, #0\n"
"                LDRNE   R0, =0x9200003\n"
"                STRNE   R0, [R4,#0x10]\n"
"                MVN     R0, #0\n"
"                STR     R0, [R5]\n"
"loc_FFA264E4:\n"
"                LDR     PC, =0xFFA264E4\n" // jump back to firmware
/*
"                LDR     R0, [R4,#0x10]\n"
"                TST     R0, #1\n"
"                BNE     loc_FFA2652C\n"
"                LDR     R0, =0x81FF\n"
"                ADD     R1, SP, #4\n"
"                STR     R0, [SP,#4]\n"
"                MOV     R0, #0x20\n"
"                STR     R0, [SP,#8]\n"
"                LDR     R0, [R4,#4]\n"
"                STR     R0, [SP,#0xC]\n"
"                LDR     R0, [R4,#0xC]\n"
"                STR     R0, [SP,#0x10]\n"
"                LDR     R0, [R4,#0xC]\n"
"                STR     R0, [SP,#0x14]\n"
"                LDR     R0, [R4,#0xC]\n"
"                STR     R0, [SP,#0x18]\n"
"                ADD     R0, R4, #0x2C\n"
"                BL      sub_FF853C68\n"
"loc_FFA2652C:\n"
"                LDR     R0, [R5,#0x18]\n"
"                CMP     R0, #0\n"
"                BLXNE   R0\n"
"                ADD     R0, R4, #0x2C\n"
"                BL      sub_FF855E18\n" // Mounter.c 0
"                BL      sub_FF8543A4\n" // FileSem.c 136
"                LDR     R1, [R5,#0x14]\n"
"                CMP     R1, #0\n"
"                LDRNE   R0, [R4,#0x10]\n"
"                BLXNE   R1\n"
"                ADD     SP, SP, #0x1C\n"
"                LDMFD   SP!, {R4,R5,PC}\n"
*/
    );
}
#endif

