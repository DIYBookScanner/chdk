#include "conf.h"

//int *video_quality = &conf.video_quality;
//int *video_mode    = &conf.video_mode;


/*----------------------------------------------------------------------
	set_quality()
-----------------------------------------------------------------------*/
// TODO - check this
void  set_quality (int *x)  // -17 highest; +12 lowest
{
	if (conf.video_mode)
		*x = 12 - ((conf.video_quality-1) * (12+17) / (99-1));
}


/*----------------------------------------------------------------------
	change_video_tables()
-----------------------------------------------------------------------*/
void change_video_tables(int a, int b)
{
}


/*----------------------------------------------------------------------
	movie_record_task()
-----------------------------------------------------------------------*/
void __attribute__((naked,noinline)) movie_record_task()
{
	//FF969BC8
	asm volatile (

"		STMFD	SP!, {R2-R8,LR} \n"
"		LDR	R8, =0x2710 \n"
"		LDR	R4, =0x6B68 \n"
"		MOV	R7, #1 \n"
//"		ADR	R6, nullsub_277 \n"
"		LDR	R6, =0xFF9698B8 \n"
"		MOV	R5, #0 \n"
"loc_FF969BE0: \n"
"		LDR	R0, [R4,#0x24] \n"
"		MOV	R2, #0 \n"
"		ADD	R1, SP,	#0x4 \n"
"		BL	sub_FF839B8C \n"
"		LDR	R0, [R4,#0x2C] \n"
"		CMP	R0, #0 \n"
"		LDRNE	R0, [R4,#0xC] \n"
"		CMPNE	R0, #2 \n"
"		LDRNE	R0, [R4,#0x44] \n"
"		CMPNE	R0, #6 \n"
"		BNE	loc_FF969CF8 \n"
"		LDR	R0, [SP,#0x4] \n"
"		LDR	R1, [R0] \n"
"		SUB	R1, R1,	#2 \n"
"		CMP	R1, #0xA \n"
"		ADDLS	PC, PC,	R1,LSL#2 \n"
"		B	loc_FF969CF8 \n"
"loc_FF969C24: \n"
"		B	loc_FF969CAC \n"
"loc_FF969C28: \n"
"		B	loc_FF969CCC \n"
"loc_FF969C2C: \n"
"		B	loc_FF969CDC \n"
"loc_FF969C30: \n"
"		B	loc_FF969CE4 \n"
"loc_FF969C34: \n"
"		B	loc_FF969CB4 \n"
"loc_FF969C38: \n"
"		B	loc_FF969CEC \n"
"loc_FF969C3C: \n"
"		B	loc_FF969CBC \n"
"loc_FF969C40: \n"
"		B	loc_FF969CF8 \n"
"loc_FF969C44: \n"
"		B	loc_FF969CF4 \n"
"loc_FF969C48: \n"
"		B	loc_FF969C7C \n"
"loc_FF969C4C: \n"
"		B	loc_FF969C50 \n"
"loc_FF969C50: \n"
// jumptable FF969C1C entry 10
"		STR	R5, [R4,#0x40] \n"
"		STR	R5, [R4,#0x30] \n"
"		STR	R5, [R4,#0x34] \n"
"		STRH	R5, [R4,#6] \n"
"		STR	R6, [R4,#0xB4] \n"
"		LDR	R0, [R4,#0xC] \n"
"		ADD	R0, R0,	#1 \n"
"		STR	R0, [R4,#0xC] \n"
"		MOV	R0, #6 \n"
"		STR	R0, [R4,#0x44] \n"
"		B	loc_FF969C98 \n"
"loc_FF969C7C: \n"
// jumptable FF969C1C entry 9
"		STR	R5, [R4,#0x40] \n"
"		STR	R5, [R4,#0x30] \n"
"		STR	R6, [R4,#0xB4] \n"
"		LDR	R0, [R4,#0xC] \n"
"		ADD	R0, R0,	#1 \n"
"		STR	R0, [R4,#0xC] \n"
"		STR	R7, [R4,#0x44] \n"
"loc_FF969C98: \n"
"		LDR	R2, =0xFF968AD0 \n"
"		LDR	R1, =0xAC9B0 \n"
"		LDR	R0, =0xFF968BCC \n"
"		BL	sub_FF851604 \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CAC: \n"
// jumptable FF969C1C entry 0
"		BL	sub_FF9699E0 \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CB4: \n"
// jumptable FF969C1C entry 4
"		BL	sub_FF969320 \n"

"		LDR	R0, =0x6BEC \n"			// Added (6BF0 - 4)
"		BL	set_quality \n"			// Added ----------->

"		B	loc_FF969CF8 \n"
"loc_FF969CBC: \n"
// jumptable FF969C1C entry 6
"		LDR	R1, [R0,#0x18] \n"
"		LDR	R0, [R0,#4] \n"
"		BL	sub_FFAA9A98 \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CCC: \n"
// jumptable FF969C1C entry 1
"		LDR	R0, [R4,#0x44] \n"
"		CMP	R0, #5 \n"
"		STRNE	R7, [R4,#0x34] \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CDC: \n"
// jumptable FF969C1C entry 2
"		BL	sub_FF968F68 \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CE4: \n"
// jumptable FF969C1C entry 3
"		BL	sub_FF968C18 \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CEC: \n"
// jumptable FF969C1C entry 5
"		BL	sub_FF968A5C \n"
"		B	loc_FF969CF8 \n"
"loc_FF969CF4: \n"
// jumptable FF969C1C entry 8
"		BL	sub_FF96A128 \n"
"loc_FF969CF8: \n"
// jumptable FF969C1C default entry
// jumptable FF969C1C entry 7
"		LDR	R1, [SP,#0x4] \n"
"		MOV	R3, #0x5F0 \n"
"		STR	R5, [R1] \n"
"		STR	R3, [SP] \n"
"		LDR	R0, [R4,#0x28] \n"
"		LDR	R3, =0xFF9688C0 \n" // "MovieRecorder.c"
"		MOV	R2, R8 \n"
"		BL	sub_FF83A4E0 \n"
"		B	loc_FF969BE0 \n"

	);
}
