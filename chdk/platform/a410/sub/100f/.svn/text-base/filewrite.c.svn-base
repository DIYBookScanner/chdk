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
#define CAM_HAS_COMPLETEFILEWRITE_REPLACEMENT 1

#include "../../../generic/filewrite.c"

// *** filewritetask ***

void __attribute__((naked,noinline)) filewritetask(  ) { //0xFFC52424
asm volatile (
      "    STMFD   SP!, {R4,LR} \n" 
      "    LDR     R4, =0x1D47C \n" 
      "    SUB     SP, SP, #4 \n" 
      "    B       loc_FFC52458 \n" 
"loc_FFC52434:\n"
      "    TST     R3, #4 \n" 
      "    BEQ     loc_FFC52454 \n" 
      "    LDR     R0, [R4] \n" 
      "    BL      sub_FFC10974 \n" 
      "    LDR     R0, [R4] \n" 
      "    MOV     R1, #8 \n" 
      "    BL      sub_FFC107D8 \n" 
      "    B       loc_FFC52458 \n" 
"loc_FFC52454:\n"
      "    BL      sub_FFC5236C_my \n" //replaced routine, see below
"loc_FFC52458:\n"
      "    MOV     R1, #7 \n" 
      "    LDR     R0, [R4] \n" 
      "    MOV     R2, #0 \n" 
      "    BL      sub_FFC107B8 \n" 
      "    CMP     R0, #0 \n" 
      "    MOV     R1, SP \n" 
      "    BEQ     loc_FFC52488 \n" 
      "    MOV     R1, #0x268 \n"
      "    LDR     R0, =0xFFC522C4 \n" 
      "    ADD     R1, R1, #3 \n" 
      "    BL      sub_FFC03B58 \n" 
      "    B       loc_FFC524A0 \n" 
"loc_FFC52488:\n"
      "    LDR     R0, [R4] \n" 
      "    BL      sub_FFC109C4 \n" 
      "    LDR     R3, [SP] \n" 
      "    TST     R3, #2 \n" 
      "    MOV     R1, #5 \n" 
      "    BEQ     loc_FFC52434 \n" 
"loc_FFC524A0:\n"
      "    LDR     R3, =0x1D480 \n" 
      "    LDR     R0, [R3] \n" 
      "    BL      sub_FFC11D68 \n" 
      "    BL      sub_FFC12724 \n" 
      "    ADD     SP, SP, #4 \n" 
      "    LDMFD   SP!, {R4,PC} \n" 
      "    MOV     PC, LR \n"
    );
}

void __attribute__((naked,noinline)) sub_FFC5236C_my(  ) {
asm volatile (
"loc_FFC5236C:\n"
      "    STMFD   SP!, {R4,R5,LR} \n"              // rom:ffc5236c  0xE92D4030 
      "    LDR     R2, =0x1D460 \n"                 // rom:ffc52370  0xE59F2094 
      "    LDRH    R3, [R2] \n"                     // rom:ffc52374  0xE1D230B0 
      "    SUB     R3, R3, #1 \n"                   // rom:ffc52378  0xE2433001 
      "    CMP     R3, #3 \n"                       // rom:ffc5237c  0xE3530003 
      "    LDRLS   PC, [PC, R3, LSL #2] \n"         // rom:ffc52380  0x979FF103 
      "    B       loc_FFC523B8 \n"                 // rom:ffc52384  0xEA00000B 
      "    .long loc_FFC52398\n"
      "    .long loc_FFC523A8\n" 
      "    .long loc_FFC523A8\n"
      "    .long loc_FFC523A8\n"
"loc_FFC52398:\n"
      "    LDR     R0, =0x1D420 \n" //location of the data block
      "    BL      sub_FFC5221C_my \n" //->"Open", replaced routine
      "    MOV     R4, R0 \n"                       // rom:ffc523a0  0xE1A04000 
      "    B       loc_FFC523BC \n"                 // rom:ffc523a4  0xEA000004 
"loc_FFC523A8:\n"
      "    LDR     R0, =0x1D420 \n"                 // rom:ffc523a8  0xE59F0060 
      "    BL      sub_FFC522D0 \n"                 // rom:ffc523ac  0xEBFFFFC7 
      "    MOV     R4, R0 \n"                       // rom:ffc523b0  0xE1A04000 
      "    B       loc_FFC523BC \n"                 // rom:ffc523b4  0xEA000000 
"loc_FFC523B8:\n"
      "    MOV     R4, #1 \n"                       // rom:ffc523b8  0xE3A04001 
"loc_FFC523BC:\n"
      "    CMP     R4, #0 \n"                       // rom:ffc523bc  0xE3540000 
      "    MOV     R1, #1 \n"                       // rom:ffc523c0  0xE3A01001 
      "    LDMEQFD SP!, {R4,R5,PC} \n"              // rom:ffc523c4  0x08BD8030 
      "    LDR     R3, =0x1D47C \n"                 // rom:ffc523c8  0xE59F3044 
      "    LDR     R0, [R3] \n"                     // rom:ffc523cc  0xE5930000 
      "    BL      sub_FFC10974 \n"                 // rom:ffc523d0  0xEBFEF967 
      "    LDR     R3, =0x1D488 \n"                 // rom:ffc523d4  0xE59F303C 
      "    LDR     R5, [R3] \n"                     // rom:ffc523d8  0xE5935000 
      "    LDR     R1, =0x1D484 \n"                 // rom:ffc523dc  0xE59F1038 
      "    LDR     R12, =0x24E0 \n"                 // rom:ffc523e0  0xE59FC038 
      "    MOV     R3, #1 \n"                       // rom:ffc523e4  0xE3A03001 
      "    MOV     R2, #0 \n"                       // rom:ffc523e8  0xE3A02000 
      "    CMP     R5, #0 \n"                       // rom:ffc523ec  0xE3550000 
      "    STR     R3, [R1] \n"                     // rom:ffc523f0  0xE5813000 
      "    MOV     R0, R4 \n"                       // rom:ffc523f4  0xE1A00004 
      "    STR     R2, [R12] \n"                    // rom:ffc523f8  0xE58C2000 
      "    LDMEQFD SP!, {R4,R5,PC} \n"              // rom:ffc523fc  0x08BD8030 
      "    MOV     LR, PC \n"                       // rom:ffc52400  0xE1A0E00F 
      "    MOV     PC, R5 \n" //end of save, sends signal to filesheduletask
      "    BL      fwt_after_close\n" //+
      "    LDMFD   SP!, {R4,R5,PC} \n"              // rom:ffc52408  0xE8BD8030 
    );
}

void __attribute__((naked,noinline)) sub_FFC5221C_my(  ) {
asm volatile (
"loc_FFC5221C:\n"
      "    STMFD   SP!, {R4-R6,LR} \n"              // rom:ffc5221c  0xE92D4070 
      "    MOV     R4, R0 \n"                       // rom:ffc52220  0xE1A04000 
      "    ADD     R5, R4, #0x1C \n"                // rom:ffc52224  0xE284501C 
      "    MOV     R0, R5 \n"                       // rom:ffc52228  0xE1A00005 
      "    BL      sub_FFC51EF4 \n"                 // rom:ffc5222c  0xEBFFFF30 
      "    LDR     R0, [R4, #0x3C] \n"              // rom:ffc52230  0xE594003C 
      "    BL      sub_FFC5B244 \n"                 // rom:ffc52234  0xEB002402 
      "    LDR     R3, [R4] \n"                     // rom:ffc52238  0xE5943000 
      "    MOV     R1, #0x600 \n"                   // rom:ffc5223c  0xE3A01C06 
      "    TST     R3, #0x10000 \n"                 // rom:ffc52240  0xE3130801 
      "    ADD     R1, R1, #1 \n"                   // rom:ffc52244  0xE2811001 
      "    MOV     R2, #0x1B4 \n"                   // rom:ffc52248  0xE3A02F6D 
      "    ORRNE   R1, R1, #0x8000 \n"              // rom:ffc5224c  0x13811902 
      "    LDR     R3, [R4, #0x3C] \n"              // rom:ffc52250  0xE594303C 
      "    ADD     R2, R2, #2 \n" // 0x1b6 = 666 octal (file permission)
//place hook here
//the task's data block is at [r4] at this point, filename starts at [r4+0x1c]
//the block can be captured here for a (new) camera with unknown data block structure
//for ptp remote capture, pass '/null' as filename
//if writing does not need to be prevented, just continue
      "STMFD SP!, {R1-R12,LR}\n"
      "MOV R0, R4\n"
      "BL filewrite_main_hook\n"
      "BL filewrite_jpeg_complete\n"
      "CMP R0, #0\n"
      "LDRNE R0, =loc_mynull\n" // /null as file name (works only on VxWorks)
      "LDMFD SP!, {R1-R12,LR}\n"
      "MOVEQ R0, R5\n" //canon file name
//hook end
      //"    MOV     R0, R5 \n" //- file name
      "    BL      sub_FFC51FF8 \n" // Open
      "    MOV     R1, R4 \n"                       // rom:ffc52260  0xE1A01004 
      "    MOV     R2, R0 \n"                       // rom:ffc52264  0xE1A02000 
      "    MOV     R4, #0 \n"                       // rom:ffc52268  0xE3A04000 
      "    LDR     R3, =0x1D464 \n"                 // rom:ffc5226c  0xE59F3044 
      "    CMP     R2, R4 \n"                       // rom:ffc52270  0xE1520004 
      "    LDR     R6, =0x1D460 \n"                 // rom:ffc52274  0xE59F6040 
      "    MOV     R0, R5 \n"                       // rom:ffc52278  0xE1A00005 
      "    STR     R2, [R3] \n"                     // rom:ffc5227c  0xE5832000 
      "    BGT     loc_FFC5229C \n"                 // rom:ffc52280  0xCA000005 
      "    BL      sub_FFC51F08 \n"                 // rom:ffc52284  0xEBFFFF1F 
      "    MOV     R0, #0x8000001 \n"               // rom:ffc52288  0xE3A00342 
      "    ADD     R0, R0, #0x1200000 \n"           // rom:ffc5228c  0xE2800612 
      "    BL      sub_FFC4FA70 \n"                 // rom:ffc52290  0xEBFFF5F6 
      "    MOV     R0, #2 \n"                       // rom:ffc52294  0xE3A00002 
      "    LDMFD   SP!, {R4-R6,PC} \n"              // rom:ffc52298  0xE8BD8070 
"loc_FFC5229C:\n"
      "    LDR     R3, =0x1D468 \n"                 // rom:ffc5229c  0xE59F301C 
      "    LDRH    R0, [R6] \n"                     // rom:ffc522a0  0xE1D600B0 
      "    STR     R4, [R3] \n"                     // rom:ffc522a4  0xE5834000 
      "    BL      sub_FFC5216C \n"                 // rom:ffc522a8  0xEBFFFFAF 
      "    STRH    R0, [R6] \n"                     // rom:ffc522ac  0xE1C600B0 
      "    MOV     R0, R4 \n"                       // rom:ffc522b0  0xE1A00004 
      "    LDMFD   SP!, {R4-R6,PC} \n"              // rom:ffc522b4  0xE8BD8070 
//mod start
"loc_mynull:\n"
".long   0x6c756e2f\n" // "/null"
".long   0x0000006c\n"
//mod end
    );
}
