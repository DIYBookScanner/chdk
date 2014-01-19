#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define NR_ON (2)
#define NR_OFF (1)
#define NR_AUTO (0)

static long *nrflag = (long*)0x5cdc;

#include "../../../generic/capt_seq.c"

/*
from debug strings:
[0x5cd8]: defect correct setting (0=according to table, 1=off, 2=normal, 3=long)
[0x5cdc]: darksub setting (0=according to table, 1=off, 2=on)
*/

void __attribute__((naked,noinline)) sub_FF941BA0_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4,R5,LR} \n" 
      "    BL      sub_FF98A850 \n" 
      "    LDR     R5, =0x5B94 \n" 
      "    LDR     R3, =0x5B90 \n" 
      "    MOV     R2, #0x1C \n" 
      "    LDR     R1, [R3] \n" 
      "    MOV     R0, R5 \n" 
      "    BL      sub_FFABC2D0 \n" 
      "    BL      sub_FF82CF00 \n" 
      "    LDR     R4, =0x5BB0 \n" 
      "    MOV     R3, R0 \n" 
      "    LDR     R12, [R4] \n" 
      "    MOV     R2, #0x154 \n" 
      "    TST     R3, #1 \n" 
      "    LDR     R1, =0xFF941B94 \n" 
      "    ADD     R2, R2, #3 \n" 
      "    LDR     R0, =0xFF941B5C \n" 
      "    STR     R3, [R12, #4] \n" 
      "    BEQ     loc_FF941BF0 \n" 
      "    BL      sub_FF814C10 \n" 
"loc_FF941BF0:\n"
      "    BL      sub_FFA4872C \n" 
      "    LDR     R2, [R4] \n" 
      "    LDR     R3, =0x5B74 \n" 
      "    STRH    R0, [R2, #0x14] \n" 
      "    LDR     R1, [R3] \n" 
      "    LDRH    R0, [R1, #0x10] \n" 
      "    LDRSH   R1, [R2, #0x14] \n" 
      "    LDRSH   R2, [R5, #8] \n" 
"BL      capt_seq_hook_set_nr\n"        // +
      "    BL      sub_FF946310 \n" 
      "    LDR     R3, =0x5B70 \n" 
      "    LDR     R2, [R3] \n" 
      "    LDR     R1, [R2, #4] \n" 
      "    LDR     R2, =0x5B8C \n" 
      "    CMP     R1, #2 \n" 
      "    STR     R0, [R2] \n" 
      "    MOVEQ   R3, #0 \n" 
      "    STREQ   R3, [R2] \n" 
      "    LDMFD   SP!, {R4,R5,PC} \n" 
    );
}


void __attribute__((naked,noinline)) sub_FF9432B8_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4-R6,LR} \n" 
      "    LDR     R3, =0x5B70 \n" 
      "    LDR     R2, [R3] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF9432FC \n" 
      "    LDR     R3, =0x5B90 \n" 
      "    LDR     R2, [R3] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF9432FC \n" 
      "    LDR     R3, =0x5B74 \n" 
      "    LDR     R2, [R3] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF9432FC \n" 
      "    LDR     R3, =0x5BB0 \n" 
      "    LDR     R2, [R3] \n" 
      "    CMP     R2, #0 \n" 
      "    BNE     loc_FF943310 \n" 
"loc_FF9432FC:\n"
      "    MOV     R2, #0x520 \n" 
      "    LDR     R0, =0xFF9431DC \n" 
      "    LDR     R1, =0xFF941B94 \n" 
      "    ADD     R2, R2, #2 \n" 
      "    BL      sub_FF814C10 \n" 
"loc_FF943310:\n"
      "    BL      sub_FF941A14 \n" 
      "    CMP     R0, #0 \n" 
      "    BNE     loc_FF94334C \n" 
      "    LDR     R3, =0x5B90 \n" 
      "    LDR     R2, [R3] \n" 
      "    LDR     R1, [R2, #4] \n" 
      "    CMP     R1, #0 \n" 
      "    BEQ     loc_FF94334C \n" 
      "    LDR     R0, =0xFF943264 \n" 
      "    BL      sub_FFAC039C \n" 
      "    LDR     R0, =0xFF943284 \n" 
      "    BL      sub_FFAC039C \n" 
      "    BL      sub_FF941A48 \n" 
      "    LDR     R0, =0xFF9432A8 \n" 
      "    BL      sub_FFAC039C \n" 
"loc_FF94334C:\n"
      "    LDR     R3, =0x6763C \n" 
      "    MVN     R4, #0 \n" 
      "    LDR     R0, [R3] \n" 
      "    MOV     R1, R4 \n" 
      "    BL      sub_FF821CB4 \n" 
      "    LDR     R3, =0x67640 \n" 
      "    MOV     R1, R4 \n" 
      "    LDR     R0, [R3] \n" 
      "    BL      sub_FF821CB4 \n" 
    //before take
    "BL      shooting_expo_param_override\n"  // +
      "    LDR     R3, =0x5B80 \n" 
      "    LDR     R3, [R3] \n" 
      "    CMP     R3, #1 \n" 
      "    CMPNE   R3, #3 \n" 
      "    BEQ     loc_FF9433C0 \n" 
      "    CMP     R3, #4 \n" 
      "    BEQ     loc_FF9433C0 \n" 
      "    LDR     R3, =0x5B74 \n" 
      "    LDR     R2, [R3] \n" 
      "    LDRH    R1, [R2, #2] \n" 
      "    CMP     R1, #1 \n" 
      "    BNE     loc_FF9433BC \n" 
      "    LDR     R3, =0x5BB0 \n" 
      "    LDR     R2, [R3] \n" 
      "    LDR     R1, [R2, #8] \n" 
      "    CMP     R1, #1 \n" 
      "    BLS     loc_FF9433BC \n" 
      "    BL      sub_FF942354 \n" 
      "    B       loc_FF9433C0 \n" 
"loc_FF9433BC:\n"
      "    BL      sub_FF942984 \n" 
"loc_FF9433C0:\n"
      "    BL      sub_FF942C6C \n" 
      "    MOV     R4, R0 \n" 
      "    TST     R4, #1 \n" 
      "    BEQ     loc_FF943404 \n" 
      "    LDR     R6, =0x5BC4 \n" 
      "    LDR     R2, [R6] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF9433F0 \n" 
      "    LDR     R3, =0x5BC8 \n" 
      "    LDR     R1, [R3] \n" 
      "    MOV     LR, PC \n" 
      "    MOV     PC, R2 \n" 
"loc_FF9433F0:\n"
      "    LDR     R5, =0x67638 \n" 
      "    MOV     R1, #2 \n" 
      "    LDR     R0, [R5] \n" 
      "    BL      sub_FF821B20 \n" 
      "    B       loc_FF94340C \n" 
"loc_FF943404:\n"
      "    LDR     R6, =0x5BC4 \n" 
      "    LDR     R5, =0x67638 \n" 
"loc_FF94340C:\n"
      "    BL      sub_FF941BA0_my \n"  // ->
      "    LDR     R3, =0x5BB4 \n" 
      "    LDR     R2, [R3] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF943434 \n" 
      "    LDR     R3, =0x5BB8 \n" 
      "    MOV     R0, R4 \n" 
      "    LDR     R1, [R3] \n" 
      "    MOV     LR, PC \n" 
      "    MOV     PC, R2 \n" 
"loc_FF943434:\n"
      "    BL      sub_FF942E68 \n" 
      "    BL      sub_FF942F54 \n" 
      "    BL      sub_FF942FFC \n" 
    "BL capt_seq_hook_raw_here\n"       // +
      "    LDR     R2, [R6] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF94345C \n" 
      "    LDR     R3, =0x5BC8 \n" 
      "    LDR     R1, [R3] \n" 
      "    MOV     LR, PC \n" 
      "    MOV     PC, R2 \n" 
"loc_FF94345C:\n"
      "    LDR     R0, [R5] \n" 
      "    MOV     R1, #2 \n" 
      "    LDMFD   SP!, {R4-R6,LR} \n" 
      "    B       sub_FF821B20 \n" 
    );
}


void __attribute__((naked,noinline)) capt_seq_task() //@ff944b48 in ixus40 100j
{//THE CODE USES STRANGE JUMP TABLE! (starts at 0x5bd0)
/* the table in ROM:
//    FFADB9A0:                    sub_FF9427E8 //no idea
//    FFADB9A4:                    sub_FF9432B8 //takes the snapshot
//    FFADB9A8:                    sub_FF942A40 //also called after releasing half_press
//    FFADB9AC:                    sub_FF9426DC //this is called after releasing shoot_half
//    FFADB9B0:                    sub_FF943848
//    FFADB9B4:                    sub_FF943B90
//    FFADB9B8:                    sub_FF943E2C
//    FFADB9BC:                    sub_FF943FD0 //cancel movie capt seq
//    FFADB9C0:                    sub_FF944210
//    FFADB9C4:                    sub_FF9443E0
//    FFADB9C8:                    sub_FF9444E0
//    FFADB9CC:                    sub_FF944564
//    FFADB9D0:                    sub_FF9447CC
//    FFADB9D4:                    sub_FF944880
*/
asm volatile (
      "    STMFD   SP!, {R4,R5,LR} \n" 
      "    SUB     SP, SP, #4 \n" 
//patching the jumptable
" LDR R4, =0x5bd0\n" //+
" LDR R5, =sub_FF9432B8_my\n" //+
" STR R5, [R4, #4]\n" //+
//patching finished
      "    MOV     R5, SP \n" 
      "    B       loc_FF944B78 \n" 
"loc_FF944B58:\n"
      "    LDR     R12, [SP] \n" 
      "    CMP     R12, #0xD \n" 
      "    BLS     loc_FF944B6C \n" 
      "    BL      sub_FF814C10 \n" 
      "    LDR     R12, [SP] \n" 
"loc_FF944B6C:\n"
" STMFD   SP!, {R0}\n" //+
" MOV R0, R12\n" //+
" BL set_shooting_status\n" //+ (shooting status hack)
" LDMFD   SP!, {R0}\n" //+
      "    LDR     R3, =0x5BD0 \n" 
      "    MOV     LR, PC \n" 
      "    LDR     PC, [R3, R12, LSL #2] \n" 
"loc_FF944B78:\n"
      "    LDR     R3, =0x67644 \n" 
      "    MOV     R12, #0 \n" 
      "    LDR     R4, =0x5B7C \n" 
      "    MOV     R2, R12 \n" 
      "    MOV     R1, R5 \n" 
      "    LDR     R0, [R3] \n" 
      "    STR     R12, [R4] \n" 
      "    BL      sub_FF822320 \n" 
      "    MOV     R2, #0x7B0 \n" 
      "    TST     R0, #1 \n" 
      "    LDR     R1, =0xFF941B94 \n" 
      "    ADD     R2, R2, #5 \n" 
      "    LDR     R0, =0xFF944B30 \n" 
      "    BEQ     loc_FF944B58 \n" 
      "    BL      sub_FF823B44 \n" 
      "    ADD     SP, SP, #4 \n" 
      "    LDMFD   SP!, {R4,R5,PC} \n" 
    );
}

