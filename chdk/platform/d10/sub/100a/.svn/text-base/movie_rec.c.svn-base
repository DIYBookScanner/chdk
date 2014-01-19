#include "conf.h"

// from sx10
void change_video_tables(int a, int b){
}

// from sx10, not sure if the values are right, seems to work
void  set_quality(int *x){ // -17 highest; +12 lowest
 if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

void __attribute__((naked,noinline)) movie_record_task(){ 
 asm volatile(
"                STMFD   SP!, {R2-R8,LR}\n"
"                LDR     R8, =0x442\n"
"                LDR     R7, =0x2710\n"
"                LDR     R4, =0x5FA8\n"
"                MOV     R6, #0\n"
"                MOV     R5, #1\n"
"loc_FF92F5E0:\n"
"                LDR     R0, [R4,#0x18]\n"
"                MOV     R2, #0\n"
"                ADD     R1, SP, #4\n"
"                BL      sub_FF826C30\n" // KerQueue.c 0
"                LDR     R0, [R4,#0x20]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF92F6B0\n"
"                LDR     R0, [SP,#4]\n"
"                LDR     R1, [R0]\n"
"                SUB     R1, R1, #2\n"
"                CMP     R1, #9\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FF92F6B0\n"
"                B       loc_FF92F664\n"
"                B       loc_FF92F684\n"
"                B       loc_FF92F694\n"
"                B       loc_FF92F69C\n"
"                B       loc_FF92F66C\n"
"                B       loc_FF92F6A4\n"
"                B       loc_FF92F674\n"
"                B       loc_FF92F6B0\n"
"                B       loc_FF92F6AC\n"
"                B       loc_FF92F63C\n"
"loc_FF92F63C:\n"
// jumptable FF92F60C entry 9
"                LDR     R0, =0xFF92F2F0\n" // locret
"                STR     R6, [R4,#0x34]\n"
"                STR     R0, [R4,#0x9C]\n"
"                LDR     R0, =0xFF92E96C\n"
"                LDR     R2, =0xFF92E888\n"
"                LDR     R1, =0x4B268\n"
"                STR     R6, [R4,#0x24]\n"
"                BL      sub_FF839668\n"
"                STR     R5, [R4,#0x38]\n"
"                B       loc_FF92F6B0\n"
"loc_FF92F664:\n"
// jumptable FF92F60C entry 0
"                BL      unlock_optical_zoom\n" // +
"                BL      sub_FF92F3E8\n" // MovieRecorder.c 0
"                B       loc_FF92F6B0\n"
"loc_FF92F66C:\n"
// jumptable FF92F60C entry 4
"                BL      sub_FF92EF94\n"
"                LDR     R0, =video_compression_rate \n" // added
"                BL      set_quality \n"                 // added
"                B       loc_FF92F6B0\n"
"loc_FF92F674:\n"
// jumptable FF92F60C entry 6
"                LDR     R1, [R0,#0x18]\n"
"                LDR     R0, [R0,#4]\n"
"                BL      sub_FFA42458\n" // MovWriter.c 0
"                B       loc_FF92F6B0\n"
"loc_FF92F684:\n"
// jumptable FF92F60C entry 1
"                LDR     R0, [R4,#0x38]\n"
"                CMP     R0, #5\n"
"                STRNE   R5, [R4,#0x28]\n"
"                B       loc_FF92F6B0\n"
"loc_FF92F694:\n"
// jumptable FF92F60C entry 2
"                BL      sub_FF92ECCC\n" // MovieRecorder.c 0
"                B       loc_FF92F6B0\n"
"loc_FF92F69C:\n"
// jumptable FF92F60C entry 3
"                BL      sub_FF92E9B8\n" // MovieRecorder.c 0
"                B       loc_FF92F6B0\n"
"loc_FF92F6A4:\n"
// jumptable FF92F60C entry 5
"                BL      sub_FF92E814\n" // MovieRecorder.c 100
"                B       loc_FF92F6B0\n"
"loc_FF92F6AC:\n"
// jumptable FF92F60C entry 8
"                BL      sub_FF92F818\n" // MovieRecorder.c 100
"loc_FF92F6B0:\n"
// jumptable FF92F60C default entry
// jumptable FF92F60C entry 7
"                LDR     R1, [SP,#4]\n"
"                LDR     R3, =0xFF92E678\n" // "MovieRecorder.c"
"                STR     R6, [R1]\n"
"                STR     R8, [SP]\n"
"                LDR     R0, [R4,#0x1C]\n"
"                MOV     R2, R7\n"
"                BL      sub_FF827584\n"
"                B       loc_FF92F5E0\n"
 );
}
