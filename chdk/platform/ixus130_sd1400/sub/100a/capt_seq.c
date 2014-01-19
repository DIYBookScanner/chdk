#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*)0x67c0;    // ff95f134: at taskcreate_ShutterSoundTask()

#include "../../../generic/capt_seq.c"

// FF87A2C0: task_CaptSeqTask()
void __attribute__((naked,noinline)) capt_seq_task() {
  asm volatile (
	"PUSH	{r3, r4, r5, r6, r7, r8, r9, lr}\n"
	"LDR	r6, =0x00002b9c\n" // was: "[pc, #-1152]	; ff879e9c" 
	"LDR	r4, =0x00039644\n" // was: "[pc, #-1104]	; ff879ed0" 
	"LDR	r9, =0x1\n" // was: "mov ..., #1"
	"LDR	r7, =0x0\n" // was: "mov ..., #0"
"loc_FF87A2D4:\n"
	"LDR	r0, [r6, #4]\n"
	"LDR	r2, =0x0\n" // was: "mov ..., #0"
	"MOV	r1, sp\n"
	"BL	sub_FF8396E4\n"
	"TST	r0, #1\n"	// 0x1
	"BEQ	loc_FF87A300\n"
	"LDR	r1, =0x000005b4\n" // was: "[pc, #1352]	; ff87a88c" 
	"LDR	r0, =0xFF879E50\n" // was: "[pc, #1336]	; ff87a880"  **"SsShootTask.c" 
	"BL	sub_ff81eb14\n"
	"BL	sub_ff81eacc\n"
	"POP	{r3, r4, r5, r6, r7, r8, r9, pc}\n"
"loc_FF87A300:\n" 
	"LDR	r0, [sp]\n"
	"LDR	r1, [r0]\n"
	"CMP	r1, #29\n"	// 0x1d
	"ADDLS	pc, pc, r1, lsl #2\n"
	"B	loc_FF87A59C\n"	
	"B  loc_FF87A38C\n" // 0 jumptable start
	"B  loc_FF87A3F0\n" // 1
	"B  loc_FF87A42C\n" // 2
	"B  loc_FF87A440\n" // 3
	"B  loc_FF87A438\n" // 4
	"B  loc_FF87A448\n" // 5
	"B  loc_FF87A450\n" // 6
	"B  loc_FF87A458\n" // 7
	"B  loc_FF87A4B0\n" // 8
	"B  loc_FF87A4D8\n" // 9
	"B  loc_FF87A4BC\n" // 10
	"B  loc_FF87A4C8\n" // 11
	"B  loc_FF87A4D0\n" // 12
	"B  loc_FF87A4E0\n" // 13
	"B  loc_FF87A4E8\n" // 14
	"B  loc_FF87A4F0\n" // 15
	"B  loc_FF87A4F8\n" // 16
	"B  loc_FF87A500\n" // 17
	"B  loc_FF87A50C\n" // 18
	"B  loc_FF87A514\n" // 19
	"B  loc_FF87A51C\n" // 20
	"B  loc_FF87A524\n" // 21
	"B  loc_FF87A52C\n" // 22
	"B  loc_FF87A538\n" // 23
	"B  loc_FF87A540\n" // 24
	"B  loc_FF87A548\n" // 25
	"B  loc_FF87A550\n" // 26
	"B  loc_FF87A558\n" // 27
	"B  loc_FF87A564\n" // 28
	"B  loc_FF87A5A8\n" // 29
"loc_FF87A38C:\n" // jumptable entry 0 
	"BL	sub_FF87AC50\n" 
        "BL     shooting_expo_param_override\n" // added
	"BL	sub_FF87805C\n" 

        // this code added to avoid some incorrect behavior if overrides are used.
        // but it can cause some unexpected side effects. In this case, remove this code!
        "MOV    r0, #0\n"
        "STR    r0, [r4, #36]\n"  // 0x24 fixes overrides  behavior at short shutter press

	"B	loc_FF87A5A8\n"
/*    
	"LDR	r0, [r4, #36]\n"
	"CMP	r0, #0\n"	// 0x0
	"BEQ	loc_FF87A5A8\n" 
	"BL	sub_FF879B30\n" 
	"MOV	r5, r0\n"
	"LDR	r0, [r4, #36]\n"
	"CMP	r0, #0\n"	// 0x0
	"BEQ	loc_FF87A3D4\n"
	"LDR	r0, =0xc\n" // was: "mov ..., #12"
	"BL	sub_FF87F124\n"
	"TST	r0, #1\n"	// 0x1
	"STRNE	r9, [r6, #16]\n"
	"LDRNE	r0, [r5, #8]\n"
	"ORRNE	r0, r0, #1073741824\n"	// 0x40000000
	"STRNE	r0, [r5, #8]\n"
	"BNE	loc_FF87A5A8\n"
"loc_FF87A3D4:\n"
	"MOV	r0, r5\n"
	"BL	sub_FF879DD4\n"
	"MOV	r0, r5\n"
	
	"BL	sub_ff95f120_my\n" // taskcreate_ShutterSoundTask()
        "BL     capt_seq_hook_raw_here\n" // added

	"TST	r0, #1\n"	// 0x1
	"STRNE	r9, [r6, #16]\n"
	"B	loc_FF87A5A8\n"
*/    
"loc_FF87A3F0:\n" // jumptable entry 1 
	"LDR	r0, [r4, #36]\n"
	"CMP	r0, #0\n"	// 0x0
	"BNE	loc_FF87A41C\n" 
	"LDR	r0, =0xc\n" // was: "mov ..., #12"
	"BL	sub_FF87F124\n" 
	"TST	r0, #1\n"	// 0x1
	"LDRNE	r0, [sp]\n"
	"LDRNE	r1, =0x1\n" // was: "mov ..., #1"
	"LDRNE	r2, [r0, #12]\n"
	"LDRNE	r0, =0x1\n" // was: "mov ..., #1"
	"BNE	loc_FF87A4A8\n"
"loc_FF87A41C:\n" 
	"LDR	r0, [sp]\n"
	//"BL	sub_ff87a714\n"
	"BL	sub_ff87a714_my\n"
"loc_FF87A424:\n" // 2 refs
	"STR	r7, [r4, #36]\n"
	"B	loc_FF87A5A8\n"
"loc_FF87A42C:\n" // jumptable entry 2
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_FF87AEF4\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A438:\n" // jumptable entry 4
	"BL	sub_FF87A86C\n" 
	"B	loc_FF87A424\n" 
"loc_FF87A440:\n" // jumptable entry 3
	"BL	sub_FF87AC30\n" 
	"B	loc_FF87A424\n" 
"loc_FF87A448:\n" // jumptable entry 5 
	"BL	sub_FF87AC38\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A450:\n" // jumptable entry 6 
	"BL	sub_FF87AE04\n" 
	"B	loc_FF87A4B4\n" 
"loc_FF87A458:\n" // jumptable entry 7 
	"LDR	r5, [r0, #12]\n"
	"BL	sub_FF87AC40\n" 
	"MOV	r0, r5\n"
	"BL	sub_FF95E03C\n" 
	"TST	r0, #1\n"	// 0x1
	"MOV	r8, r0\n"
	"BNE	loc_FF87A498\n"
	"BL	sub_FF88C384\n"
	"STR	r0, [r5, #24]\n"
	"MOV	r0, r5\n"
	"BL	sub_FF95EF80\n"
	"MOV	r0, r5\n"
	"BL	sub_FF95F31C\n"
	"MOV	r8, r0\n"
	"LDR	r0, [r5, #24]\n"
	"BL	sub_FF88C5BC\n"
"loc_FF87A498:\n"
	"BL	sub_FF87AC30\n"
	"MOV	r2, r5\n"
	"LDR	r1, =0x9\n" // was: "mov ..., #9"
	"MOV	r0, r8\n"
"loc_FF87A4A8:\n"
	"BL	sub_FF87851C\n"
	"B	loc_FF87A5A8\n"
"loc_FF87A4B0:\n" // jumptable entry 8
	"BL	sub_FF87AE6C\n"
"loc_FF87A4B4:\n"
	"BL	sub_FF87805C\n"
	"B	loc_FF87A5A8\n"
"loc_FF87A4BC:\n" // jumptable entry 10
	"LDR	r0, [r4, #84]\n"
	"BL	sub_FF87B298\n"
	"B	loc_FF87A5A8\n"
"loc_FF87A4C8:\n" // jumptable entry 11
	"BL	sub_FF87B54C\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A4D0:\n" // jumptable entry 12
	"BL	sub_FF87B5E0\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A4D8:\n" // jumptable entry 9 
	"BL	sub_FF87AC30\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A4E0:\n" // jumptable entry 13
	"BL	sub_FF95E254\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A4E8:\n" // jumptable entry 14 
	"BL	sub_FF95E468\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A4F0:\n" // jumptable entry 15
	"BL	sub_FF95E500\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A4F8:\n" // jumptable entry 16 
	"BL	sub_FF95E5D0\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A500:\n" // jumptable entry 17
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_FF95E838\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A50C:\n" // jumptable entry 18
	"BL	sub_FF95E988\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A514:\n" // jumptable entry 19
	"BL	sub_FF95EA18\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A51C:\n" // jumptable entry 20
	"BL	sub_FF95EAD8\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A524:\n" // jumptable entry 21
	"BL	sub_FF87B06C\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A52C:\n" // jumptable entry 22
	"BL	sub_FF87B114\n"
	"BL	sub_FF8376FC\n"
	"B	loc_FF87A5A8\n"
"loc_FF87A538:\n" // jumptable entry 23
	"BL	sub_FF95E69C\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A540:\n" // jumptable entry 24
	"BL	sub_FF95E708\n" 
//"loc_FF87A544:\n" // this line does not have a correspondence in 100a dump!
	"B	loc_FF87A5A8\n" 
"loc_FF87A548:\n" // jumptable entry 25 
	"BL	sub_FF87D72C\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A550:\n" // jumptable entry 26 
	"BL	sub_FF87D7B4\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A558:\n" // jumptable entry 27 
	"BL	sub_FF87D810\n" 
	"BL	sub_FF87D7D0\n" 
	"B	loc_FF87A5A8\n" 
"loc_FF87A564:\n" // jumptable entry 28
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_FF95FCE0\n" 
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_FF95FE14\n" 
	"LDRH	r0, [r4, #148]\n"
	"CMP	r0, #4\n"	// 0x4
	"LDRNEH	r0, [r4]\n" // compiler doesn't like ldrhne, -> ldrneh
	"SUBNE	ip, r0, #33280\n"	// 0x8200
	"SUBNES	ip, ip, #42\n"	// 0x2a compiler doesn't like subsne, -> subnes
	"BNE	loc_FF87A5A8\n" 
	"BL	sub_FF87D7B4\n"
	"BL	sub_FF87DD24\n"
	"BL	sub_FF87DC34\n"
	"B	loc_FF87A5A8\n"
"loc_FF87A59C:\n" // jumptable default
	"LDR	r1, =0x0000070b\n" // was: "[pc, #668]	; ff87a890"  
	"LDR	r0, =0xFF879E50\n" // was: "[pc, #648]	; ff87a880"  **"SsShootTask.c"
	"BL	sub_ff81eb14\n"
"loc_FF87A5A8:\n" // 30 refs jumptable entry 29
	"LDR	r0, [sp]\n"
	"LDR	r1, [r0, #4]\n"
	"LDR	r0, [r6]\n"
	"BL	sub_FF883F4C\n"
	"LDR	r5, [sp]\n"
	"LDR	r0, [r5, #8]\n"
	"CMP	r0, #0\n"	// 0x0
	"LDREQ	r1, =0x00000132\n" // was: "[pc, #632]	; ff87a894" 
	"LDREQ	r0, =0xFF879E50\n" // was: "subeq	r0, pc, #1920"   *"SsShootTask.c" 
	"BLEQ	sub_ff81eb14\n"
	"STR	r7, [r5, #8]\n"
	"B	loc_FF87A2D4\n"
    );
}

// ROM:FF970A8C taskcreate_ShutterSoundTask(), LOCATION: SsCaptureSeq.c:0
void __attribute__((naked,noinline)) sub_ff95f120_my() {
  asm volatile ( //FF95F068
	"PUSH	{r0, r1, r2, r3, r4, r5, r6, r7, r8, lr}\n"
	"MOV	r4, r0\n"
	"BL	sub_FF95FFE4\n"
	"MVN	r1, #0\n"	// 0x0
	"BL	sub_FF883F80\n"
	"LDR	r5, =0x000067c0\n" // was: "[pc, #-552]	; ff95ef14" 
	"LDR	r0, [r5, #12]\n"
	"CMP	r0, #0\n"	// 0x0
	"BNE	loc_FF95F0B8\n"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_ff839f2c\n"
	"STR	r0, [r5, #12]\n"
	"LDR	r3, =0x0\n" // was: "mov ..., #0"
	"STR	r3, [sp]\n"
	"LDR	r3, =0xFF95EBC8\n" // was: "[pc, #496]	; ff95f354"
	"LDR	r0, =0xFF95F2A0\n" // was: "add	r0, pc, #496"   *"ShutterSoundTask"
	"LDR	r2, =0x400\n" // was: "mov ..., #1024"
	"LDR	r1, =0x17\n" // was: "mov ..., #23"
	"BL	sub_ff839ef8\n"
"loc_FF95F0B8:\n"
	"LDR	r2, =0x4\n" // was: "mov ..., #4"
	"ADD	r1, sp, #8\n"	// 0x8
	"LDR	r0, =0x8a\n" // was: "mov ..., #138"
	"BL	sub_FF88C1F4\n"
	"TST	r0, #1\n"	// 0x1
	"LDRNE	r1, =0x000003cd\n" // was: "[pc, #480]	; ff95f36c" 
	"LDRNE	r0, =0xFF95EE60\n" // was: "subne	r0, pc, #632"   *"SsCaptureSeq.c"
	"BLNE	sub_ff81eb14\n"
	"LDR	r6, =0x00039708\n" // was: "[pc, #420]	; ff95f33c" 
	"LDR	r7, =0x00039644\n" // was: "[pc, #-604]	; ff95ef40" 
	"LDR	r3, [r6]\n"
	"LDRSH	r2, [r6, #12]\n"
	"LDRSH	r1, [r6, #14]\n"
	"LDR	r0, [r7, #136]\n"
	"BL	sub_FF92947C\n"
	"BL	sub_ff862ca4\n" // GetCCDTemperature() WAS ff862ca4 NOT CHANGED
	"LDR	r3, =0x000067c8\n" // was: "[pc, #440]	; ff95f370" 
	"STRH	r0, [r4, #164]\n"
	"SUB	r2, r3, #4\n"	// 0x4
	"STRD	r2, [sp]\n"
	"MOV	r1, r0\n"
	"LDRH	r0, [r7, #92]\n"
	"LDRSH	r2, [r6, #12]\n"
	"SUB	r3, r3, #8\n"	// 0x8
	"BL	sub_FF961B88\n"

        "BL     wait_until_remote_button_is_released\n"
        "BL     capt_seq_hook_set_nr\n"
        "B      sub_FF95F11C\n" // continue in Canon firmware ????????
/*
	"LDR	r0, [r4, #28]\n"
	"CMP	r0, #0\n"	// 0x0
	"LDRNE	r0, =0x1\n" // was: "mov ..., #1"
	"STRNE	r0, [r5]\n"
	"LDR	r0, [r5]\n"
	"LSL	r1, r0, #16\n"
	"LDRH	r0, [r7, #92]\n"
	"LSR	r1, r1, #16\n"
	"BL	sub_ff961d9c\n"
	"STR	r0, [r4, #172]\n"
	"LDR	r0, [r5, #4]\n"
	"BL	sub_ff92c5c4\n"
	"LDR	r0, [r5, #8]\n"
	"BL	sub_ff8b1504\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_ff8b151c\n"
	"MOV	r1, r4\n"
	"LDR	r0, =0xff95ecf0\n" // was: "sub	r0, pc, #1328"  
	"BL	sub_ff8b14e0\n"
	"LDR	r0, [r5]\n"
	"CMP	r0, #1\n"	// 0x1
	"BEQ	loc_ff95f248\n"
	"CMP	r0, #2\n"	// 0x2
	"BEQ	loc_ff95f260\n"
	"CMP	r0, #3\n"	// 0x3
	"BEQ	loc_ff95f280\n"
	"CMP	r0, #7\n"	// 0x7
	"BNE	loc_ff95f29c\n"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
"loc_ff95f248:\n"
	"BL	sub_ff8b1510\n"
	"LDR	r2, [sp, #8]\n"
	"ADD	r1, sp, #12\n"	// 0xc
	"MOV	r0, r4\n"
	"BL	sub_ff95ef78\n"
	"B	loc_ff95f278\n"
"loc_ff95f260:\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_ff8b1510\n"
	"LDR	r2, [sp, #8]\n"
	"ADD	r1, sp, #12\n"	// 0xc
	"MOV	r0, r4\n"
	"BL	sub_ff95f474\n"
"loc_ff95f278:\n" // 2 refs
	"MOV	r8, r0\n"
	"B	loc_ff95f2a8\n"
"loc_ff95f280:\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_ff8b1510\n"
	"LDR	r2, [sp, #8]\n"
	"ADD	r1, sp, #12\n"	// 0xc
	"MOV	r0, r4\n"
	"BL	sub_ff95f540\n"
	"B	loc_ff95f278\n"
"loc_ff95f29c:\n"
	"LDR	r1, =0x00000429\n" // was: "[pc, #208]	; ff95f374" 
	"LDR	r0, =0xff95ef18\n" // was: "sub	r0, pc, #912"   *"SsCaptureSeq.c"
	"BL	sub_ff81eb14\n"
"loc_ff95f2a8:\n"
	"TST	r8, #1\n"	// 0x1
	"MOVNE	r0, r8\n"
	"BNE	loc_ff95f32c\n"
	"LDR	r0, =0xff95ed2c\n" // was: "[pc, #188]	; ff95f378" 
	"LDR	r1, =0x0\n" // was: "mov ..., #0"
	"BL	sub_ff8b14e0\n"
	"LDRH	r0, [r7]\n"
	"SUB	ip, r0, #32768\n"	// 0x8000
	"SUBS	ip, ip, #524\n"	// 0x20c
	"BLEQ	sub_ff89d470\n"
	"LDR	r2, =0x000067c4\n" // was: "[pc, #164]	; ff95f37c" 
	"LDR	r0, [r4, #24]\n"
	"LDR	r3, =0x4\n" // was: "mov ..., #4"
	"LDR	r1, =0x45\n" // was: "mov ..., #69"
	"BL	sub_ff88c728\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_ff929534\n"
	"STR	r0, [r4, #216]\n"
	"BL	sub_ff87ce94\n"
	"BL	sub_ff96009c\n"
	"LDR	r5, =0x0000044c\n" // was: "[pc, #128]	; ff95f380" 
	"LDR	r2, =0x00003a98\n" // was: "[pc, #-988]	; ff95ef28" 
	"LDR	r3, =0xff95ef18\n" // was: "sub	r3, pc, #1008"   *"SsCaptureSeq.c"
	"LDR	r1, =0x4\n" // was: "mov ..., #4"
	"STR	r5, [sp]\n"
	"BL	sub_ff87f4f0\n"
	"CMP	r0, #0\n"	// 0x0
	"LDRNE	r0, =0xff95ef18\n" // was: "[pc, #104]	; ff95f384"  **"SsCaptureSeq.c"
	"MOVNE	r1, r5\n"
	"BLNE	sub_ff81eb14\n"
	"LDRH	r0, [sp, #12]\n"
	"STRH	r0, [r4, #20]\n"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
"loc_ff95f32c:\n"
	"ADD	sp, sp, #16\n"	// 0x10
	"POP	{r4, r5, r6, r7, r8, pc}\n"
*/
    );
}

void __attribute__((naked,noinline)) sub_ff87a714_my() { // FF87A6C4
  asm volatile ( 
	"PUSH	{r4, r5, r6, lr}\n"
	"LDR	r4, [r0, #12]\n"
	"LDR	r6, =0x00039644\n" // was: "[pc, #-2132]	; ff879ed0" 
	"LDR	r0, [r4, #8]\n"
	"LDR	r5, =0x0\n" // was: "mov ..., #0"
	"ORR	r0, r0, #1\n"	// 0x1
	"STR	r0, [r4, #8]\n"
	"LDR	r0, [r6, #36]\n"
	"CMP	r0, #0\n"	// 0x0
	"LDREQ	r0, =0x2\n" // was: "mov ..., #2"
	"BLEQ	sub_FF876718\n"
	"BL	sub_FF87AC40\n"
	"LDR	r0, [r6, #36]\n"
	"CMP	r0, #0\n"	// 0x0
	"BNE	loc_FF87A78C\n" 
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_FF95FCE0\n" 
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_FF95FE14\n" 
	"MOV	r0, r4\n"
	"BL	sub_FF87B014\n" 
	"MOV	r0, r4\n"
	"BL	sub_FF95DC80\n" 
	"CMP	r0, #0\n"	// 0x0
	"BEQ	loc_FF87A754\n" 
	"BL	sub_FF95FD20\n" 
	"BL	sub_FF95FE58\n" 
	"BL	sub_FF95FEA8\n" 
	"MOV	r0, r4\n"
	"BL	sub_FF95DD64\n" 
	"TST	r0, #1\n"	// 0x1
	"MOVNE	r2, r4\n"
	"POPNE	{r4, r5, r6, lr}\n"
	"LDRNE	r1, =0x1\n" // was: "mov ..., #1"
	"BNE	sub_FF87851C\n"
	"B	loc_FF87A768\n"
"loc_FF87A754:\n" //WAS ff87a7a4
	"MOV	r0, r4\n"
	"BL	sub_FF95DD00\n"
	"BL	sub_FF95FD20\n"
	"BL	sub_FF95FE58\n"
	"BL	sub_FF95FEA8\n"
"loc_FF87A768:\n"
	"MOV	r0, r4\n"
	"BL	sub_FF879DD4\n"
	"MOV	r0, r4\n"
	"BL	sub_FF95EF80\n"
	"BL	sub_FF95FABC\n"
	"MOV	r0, r4\n"
	//"BL	sub_ff95f120\n"
	"BL	sub_ff95f120_my\n"
	"MOV	r5, r0\n"
        "BL     capt_seq_hook_raw_here\n" // added (sx210is)
	"B	loc_FF87A79C\n"
"loc_FF87A78C:\n"
	"LDR	r0, =0x00002b9c\n" // was: "[pc, #-2376]	; ff879e9c" 
	"LDR	r0, [r0, #16]\n"
	"CMP	r0, #0\n"	// 0x0
	"LDRNE	r5, =0x1d\n" // was: "mov ..., #29"
"loc_FF87A79C:\n"
	"BL	sub_FF87D7B4\n"
	"BL	sub_FF87D7FC\n"
	"BL	sub_FF87D83C\n"
	"MOV	r2, r4\n"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"MOV	r0, r5\n"
	"BL	sub_FF87851C\n"
	"BL	sub_FF95F2D0\n"
	"CMP	r0, #0\n"	// 0x0
	"LDRNE	r0, [r4, #8]\n"
	"ORRNE	r0, r0, #8192\n"	// 0x2000
	"STRNE	r0, [r4, #8]\n"
	"POP	{r4, r5, r6, pc}\n"
    );
}

// ff8bab28: task_ExpDrvTask()
// Is anything changed in here? If not, why not just call original?
void __attribute__((naked,noinline)) exp_drv_task() { // was FF8C25DC
  asm volatile ( //FF8BAAD8
	"PUSH	{r4, r5, r6, r7, r8, lr}\n"
	"SUB	sp, sp, #32\n"	// 0x20
	"LDR	r8, =0x00000bb8\n" // was: "[pc, #-908]	; ff8ba7ac" 
	"LDR	r7, =0x00003f58\n" // was: "[pc, #2736]	; ff8bb5ec" 
	"LDR	r5, =0x00042ab0\n" // was: "[pc, #2764]	; ff8bb60c" 
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"ADD	r6, sp, #16\n"	// 0x10
	"STR	r0, [sp, #12]\n"
"loc_FF8BAAF8:\n"
	"LDR	r0, [r7, #32]\n"
	"LDR	r2, =0x0\n" // was: "mov ..., #0"
	"ADD	r1, sp, #28\n"	// 0x1c
	"BL	sub_FF8396E4\n"
	"LDR	r0, [sp, #12]\n"
	"CMP	r0, #1\n"	// 0x1
	"BNE	loc_FF8BAB44\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r0, [r0]\n"
	"CMP	r0, #19\n"	// 0x13
	"CMPNE	r0, #20\n"	// 0x14
	"CMPNE	r0, #21\n"	// 0x15
	"CMPNE	r0, #22\n"	// 0x16
	"BEQ	loc_FF8BACA8\n"
	"CMP	r0, #40\n"	// 0x28
	"BEQ	loc_FF8BAC30\n"
	"ADD	r1, sp, #12\n"	// 0xc
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_FF8BAA88\n"
"loc_FF8BAB44:\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r1, [r0]\n"
	"CMP	r1, #46\n"	// 0x2e
	"BNE	loc_FF8BAB74\n"
	"LDR	r0, [sp, #28]\n"
	"BL	sub_ff8bbe38\n"
	"LDR	r0, [r7, #28]\n"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"BL	sub_FF883F4C\n"
	"BL	sub_ff81eacc\n" // eventproc_export_ExitTask()
	"ADD	sp, sp, #32\n"	// 0x20
	"POP	{r4, r5, r6, r7, r8, pc}\n"
"loc_FF8BAB74:\n"
	"CMP	r1, #45\n"	// 0x2d
	"BNE	loc_FF8BAB90\n"
	"LDR	r2, [r0, #140]!\n"
	"LDR	r1, [r0, #4]\n"
	"MOV	r0, r1\n"
	"BLX	r2\n"
	"B	loc_FF8BB0D0\n"
"loc_FF8BAB90:\n"
	"CMP	r1, #38\n"	// 0x26
	"BNE	loc_FF8BABE0\n"
	"LDR	r0, [r7, #28]\n"
	"LDR	r1, =0x80\n" // was: "mov ..., #128"
	"BL	sub_FF883F80\n"
	"LDR	r0, =0xFF8B71EC\n" // was: "[pc, #2580]	; ff8bb610"  
	"LDR	r1, =0x80\n" // was: "mov ..., #128"
	"BL	sub_FF952E50\n" 
	"LDR	r0, [r7, #28]\n"
	"MOV	r2, r8\n"
	"LDR	r1, =0x80\n" // was: "mov ..., #128"
	"BL	sub_FF883E8C\n"
	"TST	r0, #1\n"	// 0x1
	"LDRNE	r1, =0x00000e5f\n" // was: "[pc, #2552]	; ff8bb614" 
	"BNE	loc_FF8BAC9C\n"
"loc_FF8BABCC:\n" // 5 refs
	"LDR	r1, [sp, #28]\n"
	"LDR	r0, [r1, #144]\n"
	"LDR	r1, [r1, #140]\n"
	"BLX	r1\n"
	"B	loc_FF8BB0D0\n"
"loc_FF8BABE0:\n"
	"CMP	r1, #39\n"	// 0x27
	"BNE	loc_FF8BAC28\n"
	"ADD	r1, sp, #12\n"	// 0xc
	"BL	sub_FF8BAA88\n"
	"LDR	r0, [r7, #28]\n"
	"LDR	r1, =0x100\n" // was: "mov ..., #256"
	"BL	sub_FF883F80\n"
	"LDR	r0, =0xFF8B71FC\n" // was: "[pc, #2500]	; ff8bb618" 
	"LDR	r1, =0x100\n" // was: "mov ..., #256"
	"BL	sub_FF9530D8\n"
	"LDR	r0, [r7, #28]\n"
	"MOV	r2, r8\n"
	"LDR	r1, =0x100\n" // was: "mov ..., #256"
	"BL	sub_FF883E8C\n"
	"TST	r0, #1\n"	// 0x1
	"BEQ	loc_FF8BABCC\n"
	"LDR	r1, =0x00000e69\n" // was: "[pc, #2468]	; ff8bb61c" 
	"B	loc_FF8BAC9C\n"
"loc_FF8BAC28:\n"
	"CMP	r1, #40\n"	// 0x28
	"BNE	loc_FF8BAC40\n"
"loc_FF8BAC30:\n"
	"LDR	r0, [sp, #28]\n"
	"ADD	r1, sp, #12\n"	// 0xc
	"BL	sub_FF8BAA88\n"
	"B	loc_FF8BABCC\n" //WAS ff8bac1c
"loc_FF8BAC40:\n" //WSA ff8bac90
	"CMP	r1, #43\n"	// 0x2b
	"BNE	loc_FF8BAC58\n"
	"BL	sub_FF8AA368\n"
	"BL	sub_FF8AAF9C\n"
	"BL	sub_FF8AAAEC\n"
	"B	loc_FF8BABCC\n"
"loc_FF8BAC58:\n"
	"CMP	r1, #44\n"	// 0x2c
	"BNE	loc_FF8BACA8\n"
	"LDR	r0, [r7, #28]\n"
	"LDR	r1, =0x4\n" // was: "mov ..., #4"
	"BL	sub_FF883F80\n"
	"LDR	r1, =0xFF8B721C\n" // was: "[pc, #-1252]	; ff8ba7e0"
	"LDR	r0, =0xfffff400\n" // was: "[pc, #-1252]	; ff8ba7e4" 
	"LDR	r2, =0x4\n" // was: "mov ..., #4"
	"BL	sub_FF8A9DE4\n" //WAS ff8a9e34
	"BL	sub_FF8AA06C\n" //WAS ff8aa0bc
	"LDR	r0, [r7, #28]\n"
	"MOV	r2, r8\n"
	"LDR	r1, =0x4\n" // was: "mov ..., #4"
	"BL	sub_FF883DA8\n" //WAS ff883df8
	"TST	r0, #1\n"	// 0x1
	"BEQ	loc_FF8BABCC\n" //ff8bac1c
	"LDR	r1, =0x00000e91\n" // was: "[pc, #2352]	; ff8bb620" 
"loc_FF8BAC9C:\n" // 2 refs WSA ff8bacec
	"LDR	r0, =0xff8b78ac\n" // was: "[pc, #-1344]	; ff8ba7b4"  **"ExpDrv.c"
	"BL	sub_ff81eb14\n"
	"B	loc_FF8BABCC\n"
"loc_FF8BACA8:\n" // 2 refs
	"LDR	r0, [sp, #28]\n"
	"LDR	r4, =0x1\n" // was: "mov ..., #1"
	"LDR	r1, [r0]\n"
	"CMP	r1, #17\n"	// 0x11
	"CMPNE	r1, #18\n"	// 0x12
	"BNE	loc_FF8BAD18\n"
	"LDR	r1, [r0, #124]\n"
	"ADD	r1, r1, r1, lsl #1\n"
	"ADD	r1, r0, r1, lsl #2\n"
	"SUB	r1, r1, #8\n"	// 0x8
	"LDM	r1, {r2, r3, r4}\n"
	"STM	r6, {r2, r3, r4}\n"
	"BL	sub_FF8B93AC\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r1, [r0, #124]\n"
	"LDR	r3, [r0, #140]\n"
	"LDR	r2, [r0, #144]\n"
	"ADD	r0, r0, #4\n"	// 0x4
	"BLX	r3\n"
	"LDR	r0, [sp, #28]\n"
	"BL	sub_FF8BC1AC\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r1, [r0, #124]\n"
	"LDR	r3, [r0, #148]\n"
	"LDR	r2, [r0, #152]\n"
	"ADD	r0, r0, #4\n"	// 0x4
	"BLX	r3\n"
	"B	loc_FF8BB010\n"
"loc_FF8BAD18:\n"
	"CMP	r1, #19\n"	// 0x13
	"CMPNE	r1, #20\n"	// 0x14
	"CMPNE	r1, #21\n"	// 0x15
	"CMPNE	r1, #22\n"	// 0x16
	"BNE	loc_FF8BADD0\n"
	"ADD	r3, sp, #12\n"	// 0xc
	"MOV	r2, sp\n"
	"ADD	r1, sp, #16\n"	// 0x10
	"BL	sub_FF8B9688\n"
	"CMP	r0, #1\n"	// 0x1
	"MOV	r4, r0\n"
	"CMPNE	r4, #5\n"	// 0x5
	"BNE	loc_FF8BAD6C\n"
	"LDR	r0, [sp, #28]\n"
	"MOV	r2, r4\n"
	"LDR	r1, [r0, #124]!\n"
	"LDR	ip, [r0, #16]!\n"
	"LDR	r3, [r0, #4]\n"
	"MOV	r0, sp\n"
	"BLX	ip\n"
	"B	loc_FF8BADA4\n"
"loc_FF8BAD6C:\n"
	"LDR	r0, [sp, #28]\n"
	"CMP	r4, #2\n"	// 0x2
	"LDR	r3, [r0, #144]\n"
	"CMPNE	r4, #6\n"	// 0x6
	"BNE	loc_FF8BADB8\n"
	"LDR	ip, [r0, #140]\n"
	"MOV	r0, sp\n"
	"MOV	r2, r4\n"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"BLX	ip\n"
	"LDR	r0, [sp, #28]\n"
	"MOV	r2, sp\n"
	"ADD	r1, sp, #16\n"	// 0x10
	"BL	sub_FF8BA79C\n"
"loc_FF8BADA4:\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r2, [sp, #12]\n"
	"MOV	r1, r4\n"
	"BL	sub_FF8BAA28\n"
	"B	loc_FF8BB010\n"
"loc_FF8BADB8:\n"
	"LDR	r1, [r0, #124]\n"
	"LDR	ip, [r0, #140]\n"
	"ADD	r0, r0, #4\n"	// 0x4
	"MOV	r2, r4\n"
	"BLX	ip\n"
	"B	loc_FF8BB010\n"
"loc_FF8BADD0:\n"
	"CMP	r1, #34\n"	// 0x22
	"CMPNE	r1, #35\n"	// 0x23
	"BNE	loc_FF8BAE1C\n"
	"LDR	r1, [r0, #124]\n"
	"ADD	r1, r1, r1, lsl #1\n"
	"ADD	r1, r0, r1, lsl #2\n"
	"SUB	r1, r1, #8\n"	// 0x8
	"LDM	r1, {r2, r3, r4}\n"
	"STM	r6, {r2, r3, r4}\n"
	"BL	sub_FF8B88FC\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r1, [r0, #124]\n"
	"LDR	r3, [r0, #140]\n"
	"LDR	r2, [r0, #144]\n"
	"ADD	r0, r0, #4\n"	// 0x4
	"BLX	r3\n"
	"LDR	r0, [sp, #28]\n"
	"BL	sub_FF8B8BF0\n"
	"B	loc_FF8BB010\n"
"loc_FF8BAE1C:\n"
	"ADD	r1, r0, #4\n"	// 0x4
	"LDM	r1, {r2, r3, ip}\n"
	"STM	r6, {r2, r3, ip}\n"
	"LDR	r1, [r0]\n"
	"CMP	r1, #37\n"	// 0x25
	"ADDLS	pc, pc, r1, lsl #2\n"
	"B loc_FF8BAFF0\n"
	"B  loc_FF8BAED0\n"  // 0 jump table start
	"B  loc_FF8BAED0\n"  
	"B  loc_FF8BAED8\n"  
	"B  loc_FF8BAEE0\n"  
	"B  loc_FF8BAEE0\n"  
	"B  loc_FF8BAEE0\n"  
	"B  loc_FF8BAED0\n"  
	"B  loc_FF8BAED8\n"  
	"B  loc_FF8BAEE0\n"  
	"B  loc_FF8BAEE0\n"  
	"B  loc_FF8BAEF8\n"  // 10
	"B  loc_FF8BAEF8\n"  
	"B  loc_FF8BAFE4\n"  
	"B  loc_FF8BAFEC\n"  
	"B  loc_FF8BAFEC\n"  
	"B  loc_FF8BAFEC\n"  
	"B  loc_FF8BAFEC\n"  
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAFF0\n"  // 20
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAEE8\n"  
	"B  loc_FF8BAEF0\n"  
	"B  loc_FF8BAEF0\n"  
	"B  loc_FF8BAF04\n"  
	"B  loc_FF8BAF04\n"  
	"B  loc_FF8BAF0C\n"  
	"B  loc_FF8BAF3C\n"  
	"B  loc_FF8BAF6C\n"  // 30
	"B  loc_FF8BAF9C\n"  
	"B  loc_FF8BAFCC\n"  
	"B  loc_FF8BAFCC\n"  
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAFF0\n"  
	"B  loc_FF8BAFD4\n"  
	"B  loc_FF8BAFDC\n"  // 37
"loc_FF8BAED0:\n" // jump table entries 0, 1, 6
	"BL	sub_FF8B7704\n" 
	"B	loc_FF8BAFF0\n" 
"loc_FF8BAED8:\n" // jump table entries 2, 7
	"BL	sub_FF8B7988\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAEE0:\n" // jump table entries 3, 4, 5, 8, 9
	"BL	sub_FF8B7B90\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAEE8:\n" // jump table entry 23
	"BL	sub_FF8B7E08\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAEF0:\n" // jump table entry 24, 25
	"BL	sub_FF8B8000\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAEF8:\n" // jump table entries 10, 11
	"BL	sub_FF8B82BC\n"
	"LDR	r4, =0x0\n" // was: "mov ..., #0"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAF04:\n" // jump table entry 26, 27
	"BL	sub_FF8B83FC\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAF0C:\n" // jump table entry 28
	"LDRH	r1, [r0, #4]\n"
	"STRH	r1, [sp, #16]\n"
	"LDRH	r1, [r5, #2]\n"
	"STRH	r1, [sp, #18]\n"
	"LDRH	r1, [r5, #4]\n"
	"STRH	r1, [sp, #20]\n"
	"LDRH	r1, [r5, #6]\n"
	"STRH	r1, [sp, #22]\n"
	"LDRH	r1, [r0, #12]\n"
	"STRH	r1, [sp, #24]\n"
	"BL	sub_FF8BBE5C\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAF3C:\n" // jump table entry 29
	"LDRH	r1, [r0, #4]\n"
	"STRH	r1, [sp, #16]\n"
	"LDRH	r1, [r5, #2]\n"
	"STRH	r1, [sp, #18]\n"
	"LDRH	r1, [r5, #4]\n"
	"STRH	r1, [sp, #20]\n"
	"LDRH	r1, [r5, #6]\n"
	"STRH	r1, [sp, #22]\n"
	"LDRH	r1, [r5, #8]\n"
	"STRH	r1, [sp, #24]\n"
	"BL	sub_FF8BBFC4\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAF6C:\n" // jump table entry 30
	"LDRH	r1, [r5]\n"
	"STRH	r1, [sp, #16]\n"
	"LDRH	r1, [r0, #6]\n"
	"STRH	r1, [sp, #18]\n"
	"LDRH	r1, [r5, #4]\n"
	"STRH	r1, [sp, #20]\n"
	"LDRH	r1, [r5, #6]\n"
	"STRH	r1, [sp, #22]\n"
	"LDRH	r1, [r5, #8]\n"
	"STRH	r1, [sp, #24]\n"
	"BL	sub_FF8BC070\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAF9C:\n" // jump table entry 31
	"LDRH	r1, [r5]\n"
	"STRH	r1, [sp, #16]\n"
	"LDRH	r1, [r5, #2]\n"
	"STRH	r1, [sp, #18]\n"
	"LDRH	r1, [r5, #4]\n"
	"STRH	r1, [sp, #20]\n"
	"LDRH	r1, [r5, #6]\n"
	"STRH	r1, [sp, #22]\n"
	"LDRH	r1, [r0, #12]\n"
	"STRH	r1, [sp, #24]\n"
	"BL	sub_FF8BC110\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAFCC:\n" // jump table entries 32, 33
	"BL	sub_FF8B8754\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAFD4:\n" // jump table entry 36
	"BL	sub_FF8B8CF4\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAFDC:\n" // jump table entry 37
	"BL	sub_FF8B8F30\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAFE4:\n" // jump table entry 12
	"BL	sub_FF8B90AC\n"
	"B	loc_FF8BAFF0\n"
"loc_FF8BAFEC:\n" // jump table entries 13, 14, 15, 16
	"BL	sub_FF8B9248\n"
"loc_FF8BAFF0:\n" // jump table entries 17, 18, 19, 20, 21, 22, 34, 35, default
	"LDR	r0, [sp, #28]\n"
	"LDR	r1, [r0, #124]\n"
	"LDR	r3, [r0, #140]\n"
	"LDR	r2, [r0, #144]\n"
	"ADD	r0, r0, #4\n"	// 0x4
	"BLX	r3\n"
	"CMP	r4, #1\n"	// 0x1
	"BNE	loc_FF8BB058\n"
"loc_FF8BB010:\n" // 4 refs
	"LDR	r0, [sp, #28]\n"
	"LDR	r2, =0xc\n" // was: "mov ..., #12"
	"LDR	r1, [r0, #124]\n"
	"ADD	r1, r1, r1, lsl #1\n"
	"ADD	r0, r0, r1, lsl #2\n"
	"SUB	r4, r0, #8\n"	// 0x8
	"LDR	r0, =0x00042ab0\n" // was: "[pc, #1420]	; ff8bb60c" 
	"ADD	r1, sp, #16\n"	// 0x10
	"BL	sub_FFB396B4\n"
	"LDR	r0, =0x00042abc\n" // was: "[pc, #1432]	; ff8bb624" 
	"LDR	r2, =0xc\n" // was: "mov ..., #12"
	"ADD	r1, sp, #16\n"	// 0x10
	"BL	sub_FFB396B4\n"
	"LDR	r0, =0x00042ac8\n" // was: "[pc, #1420]	; ff8bb628" 
	"LDR	r2, =0xc\n" // was: "mov ..., #12"
	"MOV	r1, r4\n"
	"BL	sub_FFB396B4\n"
	"B	loc_FF8BB0D0\n"
"loc_FF8BB058:\n"
	"LDR	r0, [sp, #28]\n"
	"LDR	r0, [r0]\n"
	"CMP	r0, #11\n"	// 0xb
	"BNE	loc_FF8BB0A0\n"
	"LDR	r3, =0x0\n" // was: "mov ..., #0"
	"STR	r3, [sp]\n"
	"LDR	r3, =0x1\n" // was: "mov ..., #1"
	"LDR	r2, =0x1\n" // was: "mov ..., #1"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_FF8B750C\n"
	"LDR	r3, =0x0\n" // was: "mov ..., #0"
	"STR	r3, [sp]\n"
	"LDR	r3, =0x1\n" // was: "mov ..., #1"
	"LDR	r2, =0x1\n" // was: "mov ..., #1"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"B	loc_FF8BB0CC\n"
"loc_FF8BB0A0:\n"
	"LDR	r3, =0x1\n" // was: "mov ..., #1"
	"LDR	r2, =0x1\n" // was: "mov ..., #1"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"STR	r3, [sp]\n"
	"BL	sub_FF8B750C\n"
	"LDR	r3, =0x1\n" // was: "mov ..., #1"
	"LDR	r2, =0x1\n" // was: "mov ..., #1"
	"LDR	r1, =0x1\n" // was: "mov ..., #1"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"STR	r3, [sp]\n"
"loc_FF8BB0CC:\n"
	"BL	sub_FF8B764C\n"
"loc_FF8BB0D0:\n" // 3 refs
	"LDR	r0, [sp, #28]\n"
	"BL	sub_FF8BBDE8\n"
	"B	loc_FF8BAAF8\n"
    );
}
