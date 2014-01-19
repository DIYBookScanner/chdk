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
	//FF986A84
	asm volatile (
"	STMFD	SP!, {R2-R10,LR} \n"               
"	LDR	R6, =0xFF985FB0\n" //nullsub
"	LDR	R7, =0xFF9864C0 \n"                  
"	LDR	R4, =0x6E80 \n"                      
"	LDR	R9, =0x6C7 \n"                       
"	LDR	R10, =0x2710 \n"                     
"	MOV	R8, #1 \n"                           
"	MOV	R5, #0 \n"                           
"loc_FF986AA4:\n"
"	LDR	R0, [R4, #0x24] \n"                  
"	MOV	R2, #0 \n"                           
"	ADD	R1, SP, #4 \n"                       
"	BL	sub_FF83A27C \n"                      
"	LDR	R0, [R4, #0x2C] \n"                  
"	CMP	R0, #0 \n"                           
"	LDRNE	R0, [R4, #0xC] \n"                 
"	CMPNE	R0, #2 \n"                         
"	LDRNE	R0, [R4, #0x44] \n"                
"	CMPNE	R0, #6 \n"                         
"	BNE	loc_FF986BC8 \n"                     
"	LDR	R0, [SP, #4] \n"                     
"	LDR	R1, [R0] \n"                         
"	SUB	R1, R1, #2 \n"                       
"	CMP	R1, #0xB \n"                         
"	ADDCC	PC, PC, R1, LSL #2 \n"             
"	B	loc_FF986BC8 \n"                       
"	B	loc_FF986B78 \n"                       
"	B	loc_FF986B9C \n"                       
"	B	loc_FF986BAC \n"                       
"	B	loc_FF986BB4 \n"                       
"	B	loc_FF986B80 \n"                       
"	B	loc_FF986BBC \n"                       
"	B	loc_FF986B8C \n"                       
"	B	loc_FF986BC8 \n"                       
"	B	loc_FF986BC4 \n"                       
"	B	loc_FF986B44 \n"                       
"	B	loc_FF986B14 \n"                       
"loc_FF986B14:\n"
// jumptable FF986AE0 entry 10
"	STR	R5, [R4, #0x40] \n"                  
"	STR	R5, [R4, #0x30] \n"                  
"	STR	R5, [R4, #0x34] \n"                  
"	STRH	R5, [R4, #6] \n"                    
"	STR	R6, [R4, #0xB4] \n"                  
"	STR	R7, [R4, #0xD0] \n"                  
"	LDR	R0, [R4, #0xC] \n"                   
"	ADD	R0, R0, #1 \n"                       
"	STR	R0, [R4, #0xC] \n"                   
"	MOV	R0, #6 \n"                           
"	STR	R0, [R4, #0x44] \n"                  
"	B	loc_FF986B64 \n"                       
"loc_FF986B44:\n"
// jumptable FF986AE0 entry 9
"	STR	R5, [R4, #0x40] \n"                  
"	STR	R5, [R4, #0x30] \n"                  
"	STR	R6, [R4, #0xB4] \n"                  
"	STR	R7, [R4, #0xD0] \n"                  
"	LDR	R0, [R4, #0xC] \n"                   
"	ADD	R0, R0, #1 \n"                       
"	STR	R0, [R4, #0xC] \n"                   
"	STR	R8, [R4, #0x44] \n"                  
"loc_FF986B64:\n"
"	LDR	R2, =0xFF985790 \n"                  
"	LDR	R1, =0xB3218 \n"                     
"	LDR	R0, =0xFF9858A4 \n"                  
"	BL	sub_FF8540E4 \n"                      
"	B	loc_FF986BC8 \n"                       
"loc_FF986B78:\n"
// jumptable FF986AE0 entry 0
"	BL	sub_FF986110 \n"                      
"	B	loc_FF986BC8 \n"                       
"loc_FF986B80:\n"
// jumptable FF986AE0 entry 4
"	LDR	R1, [R4, #0xD0] \n"                  
"	BLX	R1 \n"                               

"		LDR	R0, =0x6F04 \n"			// Added (6F08 - 4)
"		BL	set_quality \n"			// Added ----------->

"	B	loc_FF986BC8 \n"                       
"loc_FF986B8C:\n"
// jumptable FF986AE0 entry 6
"	LDR	R1, [R0, #0x18] \n"                  
"	LDR	R0, [R0, #4] \n"                     
"	BL	sub_FFAD9FE8 \n"                      
"	B	loc_FF986BC8 \n"                       
"loc_FF986B9C:\n"
// jumptable FF986AE0 entry 1
"	LDR	R0, [R4, #0x44] \n"                  
"	CMP	R0, #5 \n"                           
"	STRNE	R8, [R4, #0x34] \n"                
"	B	loc_FF986BC8 \n"                       
"loc_FF986BAC:\n"
// jumptable FF986AE0 entry 2
"	BL	sub_FF985C40 \n"                      
"	B	loc_FF986BC8 \n"                       
"loc_FF986BB4:\n"
// jumptable FF986AE0 entry 3
"	BL	sub_FF9858F0 \n"                      
"	B	loc_FF986BC8 \n"                       
"loc_FF986BBC:\n"
// jumptable FF986AE0 entry 5
"	BL	sub_FF98571C \n"                      
"	B	loc_FF986BC8 \n"                       
"loc_FF986BC4:\n"
// jumptable FF986AE0 entry 8
"	BL	sub_FF987028 \n"                      
"loc_FF986BC8:\n"
// jumptable FF986AE0 default entry
// jumptable FF986AE0 entry 7
"	LDR	R1, [SP, #4] \n"                     
"	LDR	R3, =0xFF985558 \n" // "MovieRecorder.c"
"	STR	R5, [R1] \n"                         
"	STR	R9, [SP] \n"                         
"	LDR	R0, [R4, #0x28] \n"                  
"	MOV	R2, R10 \n"                          
"	BL	sub_FF83ABF4 \n"                      
"	B	loc_FF986AA4 \n"                       
	);
}
