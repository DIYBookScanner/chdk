#include "lolevel.h"
#include "platform.h"
#include "core.h"

#define NR_ON (2)
#define NR_OFF (1)
#define NR_AUTO (0)

static long *nrflag = (long*)0x5c5c;

#include "../../../generic/capt_seq.c"

/*
from debug strings:
[0x5c58]: defect correct setting (0=according to table, 1=off, 2=normal, 3=long)
[0x5c5c]: darksub setting (0=according to table, 1=off, 2=on)
*/

/*
void __attribute__((naked,noinline)) sub_FF9460CC_my()
{
	asm volatile (
"                STMFD   SP!, {R4,R5,LR}\n"
"                MOV     R0, R0,LSL#16\n"
"                MOV     R4, R1,LSL#16\n"
"                MOV     R4, R4,ASR#16\n"
"                MOV     R0, R0,LSR#16\n"
"                MOV     R5, R2,LSL#16\n"
"                BL      sub_FF945FD8\n"
"                MOV     R1, R4\n"
"                BL      sub_FF946024\n"
"                MOV     R5, R5,ASR#16\n"
"                MOV     R4, R0\n"
"                MOV     R0, R5\n"
"                BL      sub_FF946078\n"
"                LDR     R3, =0x5C5C\n"
"                LDR     R2, =0x5C18\n"
"                LDR     R3, [R3]\n" // dark frame sub setting
"                ADD     R0, R0, R4,LSL#2\n"
"                LDR     R0, [R2,R0,LSL#2]\n"
"                CMP     R3, #0\n"
"                BIC     R2, R0, #1\n"
"                BEQ     loc_FF946130\n"
"                CMP     R3, #1\n"
"                MOVEQ   R0, R2\n"
"                CMP     R3, #2\n"
"                ORREQ   R0, R0, #1\n"
"loc_FF946130:\n"
"                LDR     R3, =0x5C58\n"
"                LDR     R1, [R3]\n" // defect correct setting
"                CMP     R1, #0\n"
"                BIC     R2, R0, #6\n"
"                LDEQMFD SP!, {R4,R5,PC}\n"
"                CMP     R1, #1\n"
"                MOVEQ   R0, R2\n"
"                ORR     R3, R0, #2\n"
"                CMP     R1, #2\n"
"                BIC     R3, R3, #4\n"
"                MOVEQ   R0, R3\n"
"                ORR     R2, R0, #6\n"
"                CMP     R1, #3\n"
"                MOVEQ   R0, R2\n"
"                LDMFD   SP!, {R4,R5,PC}\n"
	);
}
*/

/*
void __attribute__((naked,noinline)) sub_FF942DB8_my()
{
	asm volatile (
"                STMFD   SP!, {R4-R8,LR}\n"
"                LDR     R6, =0xFF941E68\n"
"                SUB     SP, SP, #4\n"
"                MOV     R8, #0\n"
"                LDR     R3, =0x5AF4\n"
"                LDR     R2, [R3]\n"
"                LDRH    R1, [R2,#2]\n"
"                CMP     R1, #1\n"
"                BNE     loc_FF942DF0\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                LDR     R1, [R2,#8]\n"
"                CMP     R1, #1\n"
"                BHI     loc_FF942E24\n"
"loc_FF942DF0:\n"
"                LDR     R3, =0x5AF0\n"
"                LDR     R2, [R3]\n"
"                LDRH    R1, [R2]\n"
"                CMP     R1, #9\n"
"                LDR     R5, =0xFF941E18\n"
"                BNE     loc_FF942E28\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                LDR     R1, [R2,#8]\n"
"                LDR     R3, =0xFF941E40\n"
"                CMP     R1, #1\n"
"                MOVHI   R5, R3\n"
"                B       loc_FF942E28\n"
"loc_FF942E24:\n"
"                MOV     R5, R6\n"
"loc_FF942E28:\n"
"                LDR     R7, =0x5B0C\n"
"                LDR     R3, [R7]\n"
"                MOV     R12, #0\n"
"                TST     R3, #1\n"
"                MOV     R0, R12\n"
"                MOVNE   R3, R6\n"
"                MOVEQ   R3, R5\n"
"                LDR     R1, =0xFF941D60\n"
"                MOV     R2, R0\n"
"                STR     R12, [SP]\n"
"                BL      sub_FF8B525C\n"
"                ANDS    R4, R0, #1\n"
"                BEQ     loc_FF942E70\n"
"                LDR     R2, =0x5AFC\n"
"                MOV     R3, #1\n"
"                STR     R3, [R2]\n"
"                MOV     R8, #0x1D\n"
"                B       loc_FF942F54\n"
"loc_FF942E70:\n"
"                LDR     R3, [R7]\n"
"                TST     R3, #1\n"
"                BEQ     loc_FF942EB0\n"
"                MOV     R0, #0x24\n"
"                MOV     R1, R4\n"
"                MOV     R6, R5\n"
"                BL      sub_FF999528\n"
"                BL      sub_FF8B5218\n"
"                MOV     R1, R4\n"
"                MOV     R0, R6\n"
"                BL      sub_FF8B53FC\n"
"                ANDS    R1, R0, #1\n"
"                MOVNE   R8, #1\n"
"                BNE     loc_FF942F54\n"
"                MOV     R0, #0x25\n"
"                BL      sub_FF999528\n"
"loc_FF942EB0:\n"
"                MOV     R1, #0\n"
"                LDR     R0, =0xFF941DFC\n"
"                BL      sub_FFA59594\n"
"                LDR     R3, =0x5AF4\n"
"                LDR     R2, [R3]\n"
"                LDRH    R1, [R2,#2]\n"
"                CMP     R1, #1\n"
"                BNE     loc_FF942EE4\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                LDR     R1, [R2,#8]\n"
"                CMP     R1, #1\n"
"                BHI     loc_FF942F18\n"
"loc_FF942EE4:\n"
"                LDR     R3, =0x675C0\n"
"                MOV     R1, #8\n"
"                MOV     R2, #0x1380\n"
"                LDR     R0, [R3]\n"
"                ADD     R2, R2, R1\n"
"                BL      sub_FF94E4B8\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF942F18\n"
"                MOV     R2, #0x4F0\n"
"                LDR     R0, =0xFF942D60\n"
"                LDR     R1, =0xFF941950\n"
"                ADD     R2, R2, #5\n"
"                BL      sub_FF814C10\n"
"loc_FF942F18:\n"
"                LDR     R3, =0x5B0C\n"
"                LDR     R3, [R3]\n"
"                TST     R3, #4\n"
"                BEQ     loc_FF942F3C\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                LDR     R0, [R2,#0x10]\n"
"                BL      sub_FF91FCF8\n"
"                B       loc_FF942F54\n"
"loc_FF942F3C:\n"
"                TST     R3, #2\n"
"                BEQ     loc_FF942F54\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                LDR     R0, [R2,#0x10]\n"
"                BL      sub_FF91FCC4\n"
"loc_FF942F54:\n"
"                MOV     R0, R8\n"
"                ADD     SP, SP, #4\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
	);
}
*/

void __attribute__((naked,noinline)) sub_FF94195C_my()
{
	asm volatile (
"                STMFD   SP!, {R4,R5,LR}\n"
"                BL      sub_FF98A60C\n"
"                LDR     R5, =0x5B14\n"
"                LDR     R3, =0x5B10\n"
"                MOV     R2, #0x1C\n"
"                LDR     R1, [R3]\n"
"                MOV     R0, R5\n"
"                BL      sub_FFABC0A0\n" // memcpy
"                BL      sub_FF82CF00\n"
"                LDR     R4, =0x5B30\n"
"                MOV     R3, R0\n"
"                LDR     R12, [R4]\n"
"                MOV     R2, #0x154\n"
"                TST     R3, #1\n"
"                LDR     R1, =0xFF941950\n" // CaptSeq.c
"                ADD     R2, R2, #3\n"
"                LDR     R0, =0xFF941918\n" // !( (((ERROR_T)( m_pCaptInfo->hPropertyCase ))&1) == 1 )
"                STR     R3, [R12,#4]\n"
"                BEQ     loc_FF9419AC\n"
"                BL      sub_FF814C10\n" // debugassert
"loc_FF9419AC:\n"
"                BL      sub_FFA484D8\n"
"                LDR     R2, [R4]\n"
"                LDR     R3, =0x5AF4\n"
"                STRH    R0, [R2,#0x14]\n"
"                LDR     R1, [R3]\n"
"                LDRH    R0, [R1,#0x10]\n"
"                LDRSH   R1, [R2,#0x14]\n"
"                LDRSH   R2, [R5,#8]\n"
	"BL      capt_seq_hook_set_nr\n" // +
"                BL      sub_FF9460CC\n" // nr and defect correct settings read
"                LDR     R3, =0x5AF0\n"
"                LDR     R2, [R3]\n"
"                LDR     R1, [R2,#4]\n"
"                LDR     R2, =0x5B0C\n"
"                CMP     R1, #2\n"
"                STR     R0, [R2]\n" // evaluated nr & defect correct setting stored here [5b0c]
"                MOVEQ   R3, #0\n"
"                STREQ   R3, [R2]\n"
"                LDMFD   SP!, {R4,R5,PC}\n"
	);
}

void __attribute__((naked,noinline)) sub_ff943074_my()
{
	asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                LDR     R3, =0x5AF0\n"
"                LDR     R2, [R3]\n"
"                CMP     R2, #0\n"
"                BEQ     loc_FF9430B8\n"
"                LDR     R3, =0x5B10\n"
"                LDR     R2, [R3]\n"
"                CMP     R2, #0\n"
"                BEQ     loc_FF9430B8\n"
"                LDR     R3, =0x5AF4\n"
"                LDR     R2, [R3]\n"
"                CMP     R2, #0\n"
"                BEQ     loc_FF9430B8\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                CMP     R2, #0\n"
"                BNE     loc_FF9430CC\n"
"loc_FF9430B8:\n"
"                MOV     R2, #0x520\n"
"                LDR     R0, =0xff942f98\n" // "m_pSettingForPrepare != ((VOID*)0) &&..."
"                LDR     R1, =0xff941950\n" // "CaptSeq.c"
"                ADD     R2, R2, #2\n"
"                BL      sub_FF814C10\n"
"loc_FF9430CC:\n"
"                BL      sub_FF9417D0\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF943108\n"
"                LDR     R3, =0x5B10\n"
"                LDR     R2, [R3]\n"
"                LDR     R1, [R2,#4]\n"
"                CMP     R1, #0\n"
"                BEQ     loc_FF943108\n"
"                LDR     R0, =0xff943020\n" //"\r\nCaptSeq::ChargeNotCompleted!!"
"                BL      sub_FFAC016C\n"
"                LDR     R0, =0xff943040\n" //"\r\nCaptSeq::WaitingStrobeCharge..."
"                BL      sub_FFAC016C\n"
"                BL      sub_FF941804\n"
"                LDR     R0, =0xff943064\n" //"Completed!!\r\n"
"                BL      sub_FFAC016C\n"
"loc_FF943108:\n"
"                LDR     R3, =0x675BC\n"
"                MVN     R4, #0\n"
"                LDR     R0, [R3]\n"
"                MOV     R1, R4\n"
"                BL      sub_FF821CB4\n"
"                LDR     R3, =0x675C0\n"
"                MOV     R1, R4\n"
"                LDR     R0, [R3]\n"
"                BL      sub_FF821CB4\n"
	//before take
	"BL      shooting_expo_param_override\n"  // +
	
"                LDR     R3, =0x5B00\n"
"                LDR     R3, [R3]\n"
"                CMP     R3, #1\n"
"                CMPNE   R3, #3\n"
"                BEQ     loc_FF94317C\n"
"                CMP     R3, #4\n"
"                BEQ     loc_FF94317C\n"
"                LDR     R3, =0x5AF4\n"
"                LDR     R2, [R3]\n"
"                LDRH    R1, [R2,#2]\n"
"                CMP     R1, #1\n"
"                BNE     loc_FF943178\n"
"                LDR     R3, =0x5B30\n"
"                LDR     R2, [R3]\n"
"                LDR     R1, [R2,#8]\n"
"                CMP     R1, #1\n"
"                BLS     loc_FF943178\n"
"                BL      sub_FF942110\n"
"                B       loc_FF94317C\n"
"loc_FF943178:\n"
"                BL      sub_FF942740\n"
"loc_FF94317C:\n"
"                BL      sub_FF942A28\n"
"                MOV     R4, R0\n"
"                TST     R4, #1\n"
"                BEQ     loc_FF9431C0\n"
"                LDR     R6, =0x5B44\n"
"                LDR     R2, [R6]\n"
"                CMP     R2, #0\n"
"                BEQ     loc_FF9431AC\n"
"                LDR     R3, =0x5B48\n"
"                LDR     R1, [R3]\n"
"                MOV     LR, PC\n"
"                MOV     PC, R2\n"
"loc_FF9431AC:\n"
"                LDR     R5, =0x675B8\n"
"                MOV     R1, #2\n"
"                LDR     R0, [R5]\n"
"                BL      sub_FF821B20\n"
"                B       loc_FF9431C8\n"
"loc_FF9431C0:\n"
"                LDR     R6, =0x5B44\n"
"                LDR     R5, =0x675B8\n"
"loc_FF9431C8:\n"
"                BL      sub_FF94195C_my\n" //-> some NR-related stuff inside (read)
"                LDR     R3, =0x5B34\n"
"                LDR     R2, [R3]\n" // seems to be 0xff940914 so far
"                CMP     R2, #0\n"
"                BEQ     loc_FF9431F0\n"
"                LDR     R3, =0x5B38\n"
"                MOV     R0, R4\n"
"                LDR     R1, [R3]\n"
"                MOV     LR, PC\n"
"                MOV     PC, R2\n" //R0 is 0xff945214 after this (so far)
"loc_FF9431F0:\n"
"                BL      sub_FF942C24\n"
"                BL      sub_FF942D10\n"
"                BL      sub_FF942DB8\n" // expo, apply nr and defect correct stuff (takes most time)
/*
execution times for the untouched routine (sub_FF942DB8):
4s expo w/NR takes 8480ms (if ticks are 1ms)
2s expo w/NR 4480ms
short expo 470ms
*/
	"BL capt_seq_hook_raw_here\n" // + seems to be a better place, no dng/jpg corruption so far
"                LDR     R2, [R6]\n" // 0xff94089c so far (launches resize/jpeg compression process, at least i guess so)
"                CMP     R2, #0\n"
"                BEQ     loc_FF943218\n"
"                LDR     R3, =0x5B48\n"
"                LDR     R1, [R3]\n"
"                MOV     LR, PC\n"
"                MOV     PC, R2\n" // R0 is 0xff945800 after this so far
"loc_FF943218:\n"
//	"BL capt_seq_hook_raw_here\n" //bad place for this, dng routine clashes with the camera's resize/jpegcompress process which reuses the only raw buffer
"                LDR     R0, [R5]\n"
"                MOV     R1, #2\n"
"                LDMFD   SP!, {R4-R6,LR}\n"
"                B       sub_FF821B20\n"
	);
}


void __attribute__((naked,noinline)) capt_seq_task() //@ff944904 in ixus30
{//THE CODE USES STRANGE JUMP TABLE! (starts at 0x5b50)
/* the table in ROM:
ffadb6f0: 	ff9425a4
ffadb6f4: 	ff943074
ffadb6f8: 	ff9427fc
ffadb6fc: 	ff942498
ffadb700: 	ff943604
ffadb704: 	ff94394c
ffadb708: 	ff943be8
ffadb70c: 	ff943d8c
ffadb710: 	ff943fcc
ffadb714: 	ff94419c
ffadb718: 	ff94429c
ffadb71c: 	ff944320
ffadb720: 	ff944588
ffadb724: 	ff94463c*/
    asm volatile (
"                STMFD   SP!, {R4,R5,LR}\n"
"                SUB     SP, SP, #4\n"
//patching the jumptable
" LDR R4, =0x5b50\n" //+
" LDR R5, =sub_ff943074_my\n" //+
" STR R5, [R4, #4]\n" //+
//patching finished
"                MOV     R5, SP\n"
"                B       loc_FF944934\n"
"loc_FF944914:\n"
"                LDR     R12, [SP]\n"
"                CMP     R12, #0xD\n"
"                BLS     loc_FF944928\n"
"                BL      sub_FF814C10\n"
"                LDR     R12, [SP]\n"
" loc_FF944928:\n"
" STMFD   SP!, {R0}\n" //+
" MOV R0, R12\n" //+
" BL set_shooting_status\n" //+ (shooting status hack)
" LDMFD   SP!, {R0}\n" //+
"                LDR     R3, =0x5B50\n"
"                MOV     LR, PC\n"
"                LDR     PC, [R3,R12,LSL#2]\n"
"loc_FF944934:\n"
"                LDR     R3, =0x675C4\n"
"                MOV     R12, #0\n"
"                LDR     R4, =0x5AFC\n"
"                MOV     R2, R12\n"
"                MOV     R1, R5\n"
"                LDR     R0, [R3]\n"
"                STR     R12, [R4]\n"
"                BL      sub_FF822320\n"
"                MOV     R2, #0x7B0\n"
"                TST     R0, #1\n"
"                LDR     R1, =0xff941950\n" // "CaptSeq.c"
"                ADD     R2, R2, #5\n"
"                LDR     R0, =0xff9448ec\n" // "ReqID < CAPTSEQ_REQ_MAX"
"                BEQ     loc_FF944914\n"
"                BL      sub_FF823B44\n"
"                ADD     SP, SP, #4\n"
"                LDMFD   SP!, {R4,R5,PC}\n"
    );
}
