#include "conf.h"

//int *video_quality = &conf.video_quality;
//int *video_mode    = &conf.video_mode;

void change_video_tables(int a, int b) {
    //int i;
    //for (i=0;i<24;i++) table[i]=(def_table[i]*a)/b;
}

// like other cameras
void  set_quality(int *x) { // -17 highest; +12 lowest
    if (conf.video_mode) *x=12-((conf.video_quality-1)*(12+17)/(99-1));
}

// FF95A538: movie_record_task() aka. task_MovieRecord()
void __attribute__((naked,noinline)) movie_record_task() { // was FF96BD30
  asm volatile (
	"PUSH	{r2, r3, r4, r5, r6, r7, r8, lr}\n"
	"LDR	r8, =0x000004b3\n" // was: [pc, #756]	; ff95a838: (000004b3) 
	"LDR	r7, =0x00002710\n" // was: [pc, #-2500]	; ff959b84: (00002710) 
	"LDR	r4, =0x000063f8\n" // was: [pc, #-4008]	; ff9595a4: (000063f8) 
	"LDR	r6, =0x0\n" // was: "mov ..., #0"
	"LDR	r5, =0x1\n" // was: "mov ..., #1"
"loc_FF95A550:\n"
	"LDR	r0, [r4, #24]\n"
	"LDR	r2, =0x0\n" // was: "mov ..., #0"
	"ADD	r1, sp, #4\n"	// 0x4
	"BL	sub_ff8396e4\n"
	"LDR	r0, [r4, #32]\n"
	"CMP	r0, #0\n"	// 0x0
	"BNE	loc_FF95A620\n"
	"LDR	r0, [sp, #4]\n"
	"LDR	r1, [r0]\n"
	"SUB	r1, r1, #2\n"	// 0x2
	"CMP	r1, #9\n"	// 0x9
	"ADDLS	pc, pc, r1, lsl #2\n"
	"B	loc_FF95A620\n"
	"B	loc_FF95A5D4\n" // 0 jump table start
	"B	loc_FF95A5F4\n"
	"B	loc_FF95A604\n"
	"B	loc_FF95A60C\n"
	"B	loc_FF95A5DC\n"
	"B	loc_FF95A614\n"
	"B	loc_FF95A5E4\n"
	"B	loc_FF95A620\n"
	"B	loc_FF95A61C\n"
	"B	loc_FF95A5AC\n" // 9
"loc_FF95A5AC:\n" // jump table entry 9
	"LDR	r0, =0xFF95A24C\n" // was: "sub	r0, pc, #872"  
	"STR	r6, [r4, #52]\n"
	"STR	r0, [r4, #164]\n"

        // Ixus300 has this, referenced in case 4: (what does it do?)
        //"ADR     R0, =0xFF96BA00\n"
        //"LDR     R0, =sub_ff959f88_my\n"      // +
        //"STR     R0, [R4,#0xAC]\n"

	"LDR	r0, =0xFF959854\n" // was: [pc, #-2596]	; ff959ba4: (0009668c)
	"LDR	r2, =0xFF959770\n" // was: [pc, #640]	; ff95a840: (ff959854) 
	"LDR	r1, =0x0009668c\n" // was: [pc, #632]	; ff95a83c: (ff959770) 
	"STR	r6, [r4, #0x24]\n" // 0x24
	"BL	sub_ff85021c\n"
	"STR	r5, [r4, #56]\n" // 0x38
	"B	loc_FF95A620\n"
"loc_FF95A5D4:\n" // jump table entry 0
        "BL     unlock_optical_zoom\n" // added (disabled in camera.h, crashes)
	"BL	sub_FF95A354\n"
	"B	loc_FF95A620\n"
"loc_FF95A5DC:\n" // jump table entry 4

        // Ixus300 has the next 2 lines instead of the following one: (what does it do?)
        //"LDR     R1, [R4,#0xAC]\n"
        //"BLX     R1\n"

	"BL	sub_FF959ECC\n"
	//"BL	sub_ff959f88_my\n"
	"B	loc_FF95A620\n"
"loc_FF95A5E4:\n" // jump table entry 6
	"LDR	r1, [r0, #24]\n"
	"LDR	r0, [r0, #4]\n"
	"BL	sub_FFA8CB84\n"
	"B	loc_FF95A620\n"
"loc_FF95A5F4:\n" // jump table entry 1
	"LDR	r0, [r4, #56]\n"
	"CMP	r0, #5\n"	// 0x5
	"STRNE	r5, [r4, #40]\n"
	"B	loc_FF95A620\n"
"loc_FF95A604:\n" // jump table entry 2
	"BL	sub_FF959BC8\n"
	"B	loc_FF95A620\n"
"loc_FF95A60C:\n" // jump table entry 3
	"BL	sub_FF9598A0\n"
	"B	loc_FF95A620\n"
"loc_FF95A614:\n" // jump table entry 5
	"BL	sub_FF9596FC\n"
	"B	loc_FF95A620\n"
"loc_FF95A61C:\n" // jump table entry 8
	"BL	sub_FF95A788\n"
"loc_FF95A620:\n" // jump table entry 7, default
	"LDR	r1, [sp, #4]\n"
	"LDR	r3, =0xFF959590\n" // was [pc, #-2684]	; ff959bb0: (ff959590)  **"MovieRecorder.c"
	"STR	r6, [r1]\n"
	"STR	r8, [sp]\n"
	"LDR	r0, [r4, #28]\n"
	"MOV	r2, r7\n"
	"BL	sub_FF83A038\n"
	"B	loc_FF95A550\n"
    );
}
/*
void __attribute__((naked,noinline)) sub_ff959f88_my() { // was FF96BA00
  asm volatile (
	"PUSH	{r4, r5, r6, r7, r8, lr}\n"
	"SUB	sp, sp, #64\n"	// 0x40
	"LDR	r7, =0x0\n" // was: "mov ..., #0"
	"LDR	r6, =0x000063f8\n" // was: "[pc, #-2376]	; ff959654" 
	"MOV	r4, r0\n"
	"STR	r7, [sp, #48]\n"
	"STR	r7, [sp, #40]\n"
	"LDR	r0, [r6, #56]\n"
	"LDR	r8, =0x4\n" // was: "mov ..., #4"
	"CMP	r0, #3\n"	// 0x3
	"STREQ	r8, [r6, #56]\n"
	"LDR	r0, [r6, #164]\n"
	"BLX	r0\n"
	"LDR	r0, [r6, #56]\n"
	"CMP	r0, #4\n"	// 0x4
	"BNE	loc_ff95a0f8\n"
	"ADD	r3, sp, #40\n"	// 0x28
	"ADD	r2, sp, #44\n"	// 0x2c
	"ADD	r1, sp, #48\n"	// 0x30
	"ADD	r0, sp, #52\n"	// 0x34
	"BL	sub_ffa8ccc4\n"
	"CMP	r0, #0\n"	// 0x0
	"LDR	r5, =0x1\n" // was: "mov ..., #1"
	"BNE	loc_ff95a004\n"
	"LDR	r1, [r6, #40]\n"
	"CMP	r1, #1\n"	// 0x1
	"BNE	loc_ff95a100\n"
	"LDR	r1, [r6, #92]\n"
	"LDR	r2, [r6, #60]\n"
	"CMP	r1, r2\n"
	"BCC	loc_ff95a100\n"
"loc_ff95a004:\n"
	"CMP	r0, #-2147483647\n"	// 0x80000001
	"STREQ	r8, [r6, #96]\n"
	"BEQ	loc_ff95a03c\n"
	"CMP	r0, #-2147483645\n"	// 0x80000003
	"STREQ	r5, [r6, #96]\n"
	"BEQ	loc_ff95a03c\n"
	"CMP	r0, #-2147483643\n"	// 0x80000005
	"LDREQ	r0, =0x2\n" // was: "mov ..., #2"
	"BEQ	loc_ff95a038\n"
	"CMP	r0, #-2147483641\n"	// 0x80000007
	"STRNE	r7, [r6, #96]\n"
	"BNE	loc_ff95a03c\n"
	"LDR	r0, =0x3\n" // was: "mov ..., #3"
"loc_ff95a038:\n"
	"STR	r0, [r6, #96]\n"
"loc_ff95a03c:\n" // 3 refs
	"LDR	r0, =0x000966c0\n" // was: "[pc, #-2512]	; ff959674" 
	"LDR	r0, [r0, #8]\n"
	"CMP	r0, #0\n"	// 0x0
	"BEQ	loc_ff95a054\n"
	"BL	sub_ff861870\n"
	"B	loc_ff95a058\n"
"loc_ff95a054:\n"
	"BL	sub_ff9597ac\n"
"loc_ff95a058:\n"
	"LDR	r0, [r4, #28]\n"
	"ADD	r4, sp, #24\n"	// 0x18
	"ADD	r3, sp, #56\n"	// 0x38
	"MVN	r2, #1\n"	// 0x1
	"LDR	r1, =0x0\n" // was: "mov ..., #0"
	"STM	r4, {r0, r1, r2, r3}\n"
	"LDR	r2, [r6, #116]\n"
	"LDR	r3, [r6, #120]\n"
	"ADD	r1, sp, #60\n"	// 0x3c
	"ADD	r4, sp, #8\n"	// 0x8
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"STM	r4, {r0, r1, r2, r3}\n"
	"LDR	r3, =0x0\n" // was: "mov ..., #0"
	"LDR	r2, =0x40\n" // was: "mov ..., #64"
	"STRD	r2, [sp]\n"
	"LDR	r3, =0x000966d8\n" // was: "[pc, #2112]	; ff95a8dc" 
	"LDR	r2, =0x0\n" // was: "mov ..., #0"
	"LDR	r1, =0x0\n" // was: "mov ..., #0"
	"BL	sub_ffa4b708\n"
	"LDR	r0, [r6, #16]\n"
	"LDR	r1, [r6, #84]\n"
	"BL	sub_ff839b00\n" // eventproc_export_TakeSemaphore()
	"CMP	r0, #9\n"	// 0x9
	"BNE	loc_ff95a0c8\n"
"loc_ff95a0b8:\n"
	"BL	sub_ffa8d198\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"STR	r5, [r6, #56]\n"
	"B	loc_ff95a228\n"
"loc_ff95a0c8:\n"
	"LDR	r0, [sp, #56]\n"
	"CMP	r0, #0\n"	// 0x0
	"BEQ	loc_ff95a0e4\n"
"loc_ff95a0d4:\n"
	"BL	sub_ffa8d198\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"STR	r5, [r6, #56]\n"
	"B	loc_ff95a254\n"
"loc_ff95a0e4:\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_ffa4b7ac\n"
	"BL	sub_ffa4b808\n"
	"LDR	r0, =0x5\n" // was: "mov ..., #5"
	"STR	r0, [r6, #56]\n"
"loc_ff95a0f8:\n" // 3 refs
	"ADD	sp, sp, #64\n"	// 0x40
	"POP	{r4, r5, r6, r7, r8, pc}\n"
"loc_ff95a100:\n" // 2 refs
	"LDR	ip, [sp, #48]\n"
	"CMP	ip, #0\n"	// 0x0
	"BEQ	loc_ff95a2b0\n"
	"STR	r5, [r6, #44]\n"
	"LDR	r0, [r6, #92]\n"
	"LDR	r8, [r4, #12]\n"
	"CMP	r0, #0\n"	// 0x0
	"LDRNE	lr, [sp, #52]\n"
	"BNE	loc_ff95a1ac\n"
	"LDR	r0, [r4, #28]\n"
	"LDR	r1, [r4, #32]\n"
	"ADD	r3, sp, #56\n"	// 0x38
	"MVN	r2, #0\n"	// 0x0
	"ADD	lr, sp, #24\n"	// 0x18
	"STM	lr, {r0, r1, r2, r3}\n"
	"LDR	r0, [sp, #40]\n"
	"LDR	r2, [r6, #116]\n"
	"LDR	r3, [r6, #120]\n"
	"ADD	r1, sp, #60\n"	// 0x3c
	"ADD	lr, sp, #8\n"	// 0x8
	"STM	lr, {r0, r1, r2, r3}\n"
	"LDR	r3, [sp, #44]\n"
	"STR	ip, [sp]\n"
	"STR	r3, [sp, #4]\n"
	"LDMIB	r4, {r0, r1}\n"
	"LDR	r3, [sp, #52]\n"
	"MOV	r2, r8\n"
	"BL	sub_ffa4b708\n"
	"LDR	r0, [r6, #16]\n"
	"LDR	r1, [r6, #84]\n"
	"BL	sub_ff839b00\n" // eventproc_export_TakeSemaphore()
	"CMP	r0, #9\n"	// 0x9
	"BEQ	loc_ff95a0b8\n"
	"LDR	r0, [sp, #56]\n"
	"CMP	r0, #0\n"	// 0x0
	"BNE	loc_ff95a0d4\n"
	"LDR	r0, =0x1\n" // was: "mov ..., #1"
	"BL	sub_ffa4b7ac\n"
	"LDR	r0, [sp, #60]\n"
	"LDR	r1, [sp, #52]\n"
	"ADD	lr, r1, r0\n"
	"LDR	r1, [sp, #48]\n"
	"SUB	ip, r1, r0\n"
"loc_ff95a1ac:\n"
	"LDR	r2, [r6, #88]\n"
	"LDR	r0, [r4, #28]\n"
	"LDR	r1, [r4, #32]\n"
	"ADD	r3, sp, #56\n"	// 0x38
	"STR	r0, [sp, #24]\n"
	"STR	r1, [sp, #28]\n"
	"STR	r3, [sp, #36]\n"
	"STR	r2, [sp, #32]\n"
	"LDR	r2, [r6, #116]\n"
	"LDR	r3, [r6, #120]\n"
	"LDR	r0, [sp, #40]\n"
	"STR	r3, [sp, #20]\n"
	"LDR	r3, [sp, #44]\n"
	"ADD	r1, sp, #60\n"	// 0x3c
	"STR	r2, [sp, #16]\n"
	"STR	r3, [sp, #4]\n"
	"STR	r1, [sp, #12]\n"
	"STR	ip, [sp]\n"
	"STR	r0, [sp, #8]\n"
	"LDMIB	r4, {r0, r1}\n"
	"MOV	r3, lr\n"
	"MOV	r2, r8\n"
	"BL	sub_ffa4b708\n"
	"LDR	r0, [r6, #16]\n"
	"LDR	r1, [r6, #84]\n"
	"BL	sub_ff839b00\n" // eventproc_export_TakeSemaphore()
	"CMP	r0, #9\n"	// 0x9
	"BNE	loc_ff95a23c\n"
	"BL	sub_ffa8d198\n"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"STR	r5, [r6, #56]\n"
"loc_ff95a228:\n"
	"BL	sub_ffa4b7ac\n"
	"LDR	r0, =0xc\n" // was: "mov ..., #12"
	"BL	sub_ff886d0c\n"
	"LDR	r0, =0x90000\n" // was: "mov ..., #589824"
	"B	loc_ff95a264\n"
"loc_ff95a23c:\n"
	"LDR	r0, [sp, #56]\n"
	"CMP	r0, #0\n"	// 0x0
	"BEQ	loc_ff95a278\n"
	"BL	sub_ffa8d198\n"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"STR	r5, [r6, #56]\n"
"loc_ff95a254:\n"
	"BL	sub_ffa4b7ac\n"
	"LDR	r0, =0xc\n" // was: "mov ..., #12"
	"BL	sub_ff886d0c\n"
	"LDR	r0, =0xa0000\n" // was: "mov ..., #655360"
"loc_ff95a264:\n"
	"BL	sub_ff890f40\n" // eventproc_export_HardwareDefect()
	"LDR	r1, [r6, #148]!\n"
	"LDR	r0, [r6, #12]\n"
	"BLX	r1\n"
	"B	loc_ff95a0f8\n"
"loc_ff95a278:\n"
	"LDR	r0, =0x0\n" // was: "mov ..., #0"
	"BL	sub_ffa4b7ac\n"
	"LDR	r0, [sp, #52]\n"
	"LDR	r1, [sp, #60]\n"
	"BL	sub_ffa8cef0\n"
	"LDR	r0, [r6, #88]\n"
	"LDR	r3, =0x00006470\n" // <----
	"ADD	r1, r0, #1\n"	// 0x1
	"STR	r1, [r6, #88]\n"
	"STR	r3, [sp]\n"
	"LDR	r0, [sp, #60]\n"
	"SUB	r3, r3, #4\n"	// <----
	"LDR	r2, =0xf\n" // was: "mov ..., #15"
	"BL	sub_ffa8b040\n"

        //"LDR    r0, =0x6470-4\n" // added
        //"BL     set_quality\n" // added

"loc_ff95a2b0:\n"
	"LDR	r0, [r6, #92]\n"
	"ADD	r0, r0, #1\n"	// 0x1
	"STR	r0, [r6, #92]\n"
	"LDR	r1, [r6, #72]\n"
	"MUL	r0, r1, r0\n"
	"LDR	r1, [r6, #68]\n"
	"BL	sub_ffb3b51c\n"
	"MOV	r4, r0\n"
	"BL	sub_ffa8d1d0\n"
	"LDR	r1, [r6, #124]\n"
	"CMP	r1, r4\n"
	"BNE	loc_ff95a2ec\n"
	"LDR	r0, [r6, #48]\n"
	"CMP	r0, #1\n"	// 0x1
	"BNE	loc_ff95a300\n"
"loc_ff95a2ec:\n"
	"LDR	r1, [r6, #136]\n"
	"MOV	r0, r4\n"
	"BLX	r1\n"
	"STR	r4, [r6, #124]\n"
	"STR	r7, [r6, #48]\n"
"loc_ff95a300:\n"
	"STR	r7, [r6, #44]\n"
	"B	loc_ff95a0f8\n"
    );
}
*/
