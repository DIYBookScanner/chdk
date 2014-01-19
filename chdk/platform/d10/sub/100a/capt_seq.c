#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "conf.h"

static long *nrflag = (long*)(0x64E8); // 0x64F0-8 from sub_FF934548

#include "../../../generic/capt_seq.c"


void __attribute__((naked,noinline)) sub_FF934548_my() {
	asm volatile (
"                STMFD   SP!, {R0-R8,LR}\n"
"                MOV     R4, R0\n"
"                BL      sub_FF9352A0\n" // SsShootEvent.c 60
"                MVN     R1, #0\n"
"                BL      sub_FF869BF4\n"
"                LDR     R5, =0x64E8\n"
"                LDR     R0, [R5,#0xC]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF934598\n"
"                MOV     R1, #1\n"
"                MOV     R0, #0\n"
"                BL      sub_FF827478\n" // KernelMisc.c 31
"                STR     R0, [R5,#0xC]\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                LDR     R3, =0xFF934004\n" // SsCaptureSeq.c 155
"                LDR     R0, =0xFF9347C8\n" // "ShutterSoundTask"
"                MOV     R2, #0x400\n"
"                MOV     R1, #0x17\n"
"                BL      sub_FF827444\n" // KernelCreateTask
"loc_FF934598:\n"
"                MOV     R2, #4\n"
"                ADD     R1, SP, #8\n"
"                MOV     R0, #0x8A\n"
"                BL      sub_FF871CCC\n" // GetPropertyCase
"                TST     R0, #1\n"
"                LDRNE   R1, =0x3AE\n"
"                LDRNE   R0, =0xFF93429C\n" // "SsCaptureSeq.c"
"                BLNE    sub_FF81B284\n" // DebugAssert
"                LDR     R8, =0x1441C\n"
"                LDR     R7, =0x14358\n"
"                LDRSH   R1, [R8,#0xE]\n"
"                LDR     R0, [R7,#0x8C]\n"
"                BL      sub_FF8F68C8\n"
"                BL      sub_FF8497D0\n" // GetCCDTemperature
"                LDR     R3, =0x64F0\n"
"                STRH    R0, [R4,#0x9C]\n"
"                SUB     R2, R3, #4\n"
"                STRD    R2, [SP]\n"
"                MOV     R1, R0\n"
"                LDRH    R0, [R7,#0x5C]\n"
"                LDRSH   R2, [R8,#0xC]\n"
"                SUB     R3, R3, #8\n"
"                BL      sub_FF9368B4\n"
"                BL      wait_until_remote_button_is_released\n" // untested!
"                BL      capt_seq_hook_set_nr\n"
"                B       sub_FF9345F4\n" // -> continue in firmware
	);
}

void __attribute__((naked,noinline)) sub_FF861320_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                LDR     R4, [R0,#0xC]\n"
"                LDR     R6, =0x14358\n"
"                LDR     R0, [R4,#8]\n"
"                MOV     R5, #0\n"
"                ORR     R0, R0, #1\n"
"                STR     R0, [R4,#8]\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                MOVEQ   R0, #2\n"
"                BLEQ    sub_FF85C65C\n"
"                BL      sub_FF861854\n"
"                LDR     R0, [R6,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF8613D0\n"
"                MOV     R0, #0\n"
"                BL      sub_FF935130\n"
"                MOV     R0, R4\n"
"                BL      sub_FF861BA4\n"
"                MOV     R0, R4\n"
"                BL      sub_FF933130\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF8613A0\n"
"                BL      sub_FF935170\n"
"                MOV     R0, R4\n"
"                BL      sub_FF933214\n" // SsPrePreSeq.c 0
"                TST     R0, #1\n"
"                MOVNE   R2, R4\n"
"                LDMNEFD SP!, {R4-R6,LR}\n"
"                MOVNE   R1, #1\n"
"                BNE     sub_FF85F284\n" // SsShootCtrl.c 0
"                B       loc_FF8613AC\n"
"loc_FF8613A0:\n"
"                MOV     R0, R4\n"
"                BL      sub_FF9331B0\n"
"                BL      sub_FF935170\n"
"loc_FF8613AC:\n"
"                MOV     R0, R4\n"
"                BL      sub_FF860A18\n"
"                MOV     R0, R4\n"
"                BL      sub_FF934460\n" // SsCaptureSeq.c 1
"                BL      sub_FF934FC0\n" // SsShootLib.c 488
"                MOV     R0, R4\n"
"                BL      sub_FF934548_my\n" // SsCaptureSeq.c -> nr setup
"                MOV     R5, R0\n"
"                B       loc_FF8613E0\n"
"loc_FF8613D0:\n"
"                LDR     R0, =0x2AA0\n"
"                LDR     R0, [R0,#0x10]\n"
"                CMP     R0, #0\n"
"                MOVNE   R5, #0x1D\n"
"loc_FF8613E0:\n"
"                BL      capt_seq_hook_raw_here\n"
"                BL      sub_FF8640F4\n"
"                BL      sub_FF86413C\n"
"                BL      sub_FF86417C\n"
"                MOV     R2, R4\n"
"                MOV     R1, #1\n"
"                MOV     R0, R5\n"
"                BL      sub_FF85F284\n" // SsShootCtrl.c 0
"                BL      sub_FF9347F4\n"
"                CMP     R0, #0\n"
"                LDRNE   R0, [R4,#8]\n"
"                ORRNE   R0, R0, #0x2000\n"
"                STRNE   R0, [R4,#8]\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
    );
}

void __attribute__((naked,noinline)) task_CaptSeqTask_my() {
	asm volatile (
"                STMFD   SP!, {R3-R9,LR}\n"
"                LDR     R6, =0x2AA0\n"
"                LDR     R4, =0x14358\n"
"                MOV     R9, #1\n"
"                MOV     R7, #0\n"
"loc_FF860F48:\n"
"                LDR     R0, [R6,#4]\n"
"                MOV     R2, #0\n"
"                MOV     R1, SP\n"
"                BL      sub_FF826C30\n" // KerQueue.c 0
"                TST     R0, #1\n"
"                BEQ     loc_FF860F74\n"
"                LDR     R1, =0x588\n"
"                LDR     R0, =0xFF860A98\n" // aSsshoottask_c
"                BL      sub_FF81B284\n" // DebugAssert
"                BL      sub_FF81B23C\n" // eventproc_export_ExitTask
"                LDMFD   SP!, {R3-R9,PC}\n"
"loc_FF860F74:\n"
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x1E\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FF8611FC\n"
"                B       loc_FF861004\n"
"                B       loc_FF861068\n"
"                B       loc_FF8610A4\n"
"                B       loc_FF8610B8\n"
"                B       loc_FF8610B0\n"
"                B       loc_FF8610C0\n"
"                B       loc_FF8610C8\n"
"                B       loc_FF8610D0\n"
"                B       loc_FF861128\n"
"                B       loc_FF861150\n"
"                B       loc_FF861134\n"
"                B       loc_FF861140\n"
"                B       loc_FF861148\n"
"                B       loc_FF861158\n"
"                B       loc_FF861160\n"
"                B       loc_FF861168\n"
"                B       loc_FF861170\n"
"                B       loc_FF861178\n"
"                B       loc_FF861180\n"
"                B       loc_FF861188\n"
"                B       loc_FF861190\n"
"                B       loc_FF861198\n"
"                B       loc_FF8611A4\n"
"                B       loc_FF8611AC\n"
"                B       loc_FF8611B8\n"
"                B       loc_FF8611C0\n"
"                B       loc_FF8611C8\n"
"                B       loc_FF8611D0\n"
"                B       loc_FF8611D8\n"
"                B       loc_FF8611E4\n"
"                B       loc_FF861208\n"
"loc_FF861004:\n"
// jumptable FF860F80 entry 0
"                BL      sub_FF861864\n" // SsPrepareSeq.c 0
// only do quick press hack if overrides are active
"                BL      captseq_hack_override_active\n" // returns 1 if tv or sv override in effect
"                STR     R0,[SP,#-4]!\n" // push return value
"                BL      shooting_expo_param_override\n"  // +
"                BL      sub_FF85ED58\n"
"                LDR     R0,[SP],#4\n" // pop override hack
"                CMP     R0, #1\n"     // +
"                MOVEQ   R0, #0\n"     // +
"                STREQ   R0, [R4,#0x24]\n"  // fixes overrides behavior at short shutter press
"                LDRNE   R0, [R4,#0x24]\n" // modified NE
"                CMPNE   R0, #0\n"         // modified NE
"                BEQ     loc_FF861208\n"
"                BL      sub_FF860774\n"
"                MOV     R5, R0\n"
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BEQ     loc_FF86104C\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FF8659A4\n"
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#0x10]\n"
"                LDRNE   R0, [R5,#8]\n"
"                ORRNE   R0, R0, #0x40000000\n"
"                STRNE   R0, [R5,#8]\n"
"                BNE     loc_FF861208\n"
"loc_FF86104C:\n"
"                MOV     R0, R5\n"
"                BL      sub_FF860A18\n"
"                MOV     R0, R5\n"
"                BL      sub_FF934548_my\n" // SsCaptureSeq.c 0 -> nr setup (quick press)
"                TST     R0, #1\n"
"                STRNE   R9, [R6,#0x10]\n"
"                B       loc_FF861208\n"
"loc_FF861068:\n"
// jumptable FF860F80 entry 1
// TODO this doesn't look like entry 1 on sd990
"                LDR     R0, [R4,#0x24]\n"
"                CMP     R0, #0\n"
"                BNE     loc_FF861094\n"
"                MOV     R0, #0xC\n"
"                BL      sub_FF8659A4\n"
"                TST     R0, #1\n"
"                LDRNE   R0, [SP]\n"
"                MOVNE   R1, #1\n"
"                LDRNE   R2, [R0,#0xC]\n"
"                MOVNE   R0, #1\n"
"                BNE     loc_FF861120\n"
"loc_FF861094:\n"
"                LDR     R0, [SP]\n"
"                BL      sub_FF861320_my\n" // looks equivalent to sd990 sub_FF8662E0
"loc_FF86109C:\n"
"                STR     R7, [R4,#0x24]\n"
"                B       loc_FF861208\n"
"loc_FF8610A4:\n"
// jumptable FF860F80 entry 2
"                MOV     R0, #1\n"
"                BL      sub_FF861A7C\n" // SsPrepareSeq.c 0
"                B       loc_FF861208\n"
"loc_FF8610B0:\n"
// jumptable FF860F80 entry 4
"                BL      sub_FF8614AC\n"
"                B       loc_FF86109C\n"
"loc_FF8610B8:\n"
// jumptable FF860F80 entry 3
"                BL      sub_FF861844\n" // SsPrepareSeq.c 4
"                B       loc_FF86109C\n"
"loc_FF8610C0:\n"
// jumptable FF860F80 entry 5
"                BL      sub_FF86184C\n"
"                B       loc_FF861208\n"
"loc_FF8610C8:\n"
// jumptable FF860F80 entry 6
"                BL      sub_FF86199C\n" // SsPrepareSeq.c 960
"                B       loc_FF86112C\n"
"loc_FF8610D0:\n"
// jumptable FF860F80 entry 7
"                LDR     R5, [R0,#0xC]\n"
"                BL      sub_FF861854\n"
"                MOV     R0, R5\n"
"                BL      sub_FF93351C\n" // SsPrePreSeq.c 505
"                TST     R0, #1\n"
"                MOV     R8, R0\n"
"                BNE     loc_FF861110\n"
"                BL      sub_FF871E5C\n" // PropertyCase.c 0
"                STR     R0, [R5,#0x18]\n"
"                MOV     R0, R5\n"
"                BL      sub_FF934460\n" // SsCaptureSeq.c 1
"                MOV     R0, R5\n"
"                BL      sub_FF934850\n" // SsCaptureSeq.c 4
"                MOV     R8, R0\n"
"                LDR     R0, [R5,#0x18]\n"
"                BL      sub_FF872070\n" // PropertyCase.c 0
"loc_FF861110:\n"
"                BL      sub_FF861844\n" // SsPrepareSeq.c 4
"                MOV     R2, R5\n"
"                MOV     R1, #9\n"
"                MOV     R0, R8\n"
"loc_FF861120:\n"
"                BL      sub_FF85F284\n" // SsShootCtrl.c 0
"                B       loc_FF861208\n"
"loc_FF861128:\n"
// jumptable FF860F80 entry 8
"                BL      sub_FF8619FC\n" // SsPrepareSeq.c 0
"loc_FF86112C:\n"
"                BL      sub_FF85ED58\n"
"                B       loc_FF861208\n"
"loc_FF861134:\n"
// jumptable FF860F80 entry 10
"                LDR     R0, [R4,#0x54]\n"
"                BL      sub_FF861E10\n" // SsMovieRec.c 184
"                B       loc_FF861208\n"
"loc_FF861140:\n"
// jumptable FF860F80 entry 11
"                BL      sub_FF8620B8\n" // SsMovieRec.c 2
"                B       loc_FF861208\n"
"loc_FF861148:\n"
// jumptable FF860F80 entry 12
"                BL      sub_FF86214C\n" // SsMovieRec.c 43
"                B       loc_FF861208\n"
"loc_FF861150:\n"
// jumptable FF860F80 entry 9
"                BL      sub_FF861844\n" // SsPrepareSeq.c 4
"                B       loc_FF861208\n"
"loc_FF861158:\n"
// jumptable FF860F80 entry 13
"                BL      sub_FF93373C\n"
"                B       loc_FF861208\n"
"loc_FF861160:\n"
// jumptable FF860F80 entry 14
"                BL      sub_FF933924\n"
"                B       loc_FF861208\n"
"loc_FF861168:\n"
// jumptable FF860F80 entry 15
"                BL      sub_FF9339B4\n" // SsExpCompSeq.c 105
"                B       loc_FF861208\n"
"loc_FF861170:\n"
// jumptable FF860F80 entry 16
"                BL      sub_FF933A68\n"
"                B       loc_FF861208\n"
"loc_FF861178:\n"
// jumptable FF860F80 entry 17
"                MOV     R0, #0\n"
"                B       loc_FF86119C\n"
"loc_FF861180:\n"
// jumptable FF860F80 entry 18
"                BL      sub_FF933DC4\n"
"                B       loc_FF861208\n"
"loc_FF861188:\n"
// jumptable FF860F80 entry 19
"                BL      sub_FF933E54\n" // SsMFSeq.c 110
"                B       loc_FF861208\n"
"loc_FF861190:\n"
// jumptable FF860F80 entry 20
"                BL      sub_FF933F14\n" // SsMFSeq.c 177
"                B       loc_FF861208\n"
"loc_FF861198:\n"
// jumptable FF860F80 entry 21
"                MOV     R0, #1\n"
"loc_FF86119C:\n"
"                BL      sub_FF933C8C\n"
"                B       loc_FF861208\n"
"loc_FF8611A4:\n"
// jumptable FF860F80 entry 22
"                BL      sub_FF861BFC\n"
"                B       loc_FF861208\n"
"loc_FF8611AC:\n"
// jumptable FF860F80 entry 23
"                BL      sub_FF861C9C\n"
"                BL      sub_FF824A48\n"
"                B       loc_FF861208\n"
"loc_FF8611B8:\n"
// jumptable FF860F80 entry 24
"                BL      sub_FF933B24\n"
"                B       loc_FF861208\n"
"loc_FF8611C0:\n"
// jumptable FF860F80 entry 25
"                BL      sub_FF933B90\n" // SsChgExpSeq.c 0
"                B       loc_FF861208\n"
"loc_FF8611C8:\n"
// jumptable FF860F80 entry 26
"                BL      sub_FF86408C\n"
"                B       loc_FF861208\n"
"loc_FF8611D0:\n"
// jumptable FF860F80 entry 27
"                BL      sub_FF8640F4\n"
"                B       loc_FF861208\n"
"loc_FF8611D8:\n"
// jumptable FF860F80 entry 28
"                BL      sub_FF864150\n"
"                BL      sub_FF864110\n"
"                B       loc_FF861208\n"
"loc_FF8611E4:\n"
// jumptable FF860F80 entry 29
"                MOV     R0, #1\n"
"                BL      sub_FF935130\n"
"                LDRH    R0, [R4,#0x98]\n"
"                CMP     R0, #4\n"
"                BLNE    sub_FF8643BC\n" // SsLiveFunc.c 780
"                B       loc_FF861208\n"
"loc_FF8611FC:\n"
// jumptable FF860F80 default entry
"                LDR     R1, =0x6C9\n"
"                LDR     R0, =0xFF860A98\n" // aSsshoottask_c
"                BL      sub_FF81B284\n" // DebugAssert
"loc_FF861208:\n"
// jumptable FF860F80 entry 30
"                LDR     R0, [SP]\n"
"                LDR     R1, [R0,#4]\n"
"                LDR     R0, [R6]\n"
"                BL      sub_FF869BC0\n"
"                LDR     R5, [SP]\n"
"                LDR     R0, [R5,#8]\n"
"                CMP     R0, #0\n"
"                LDREQ   R1, =0x12B\n"
"                LDREQ   R0, =0xFF860A98\n" // aSsshoottask_c
"                BLEQ    sub_FF81B284\n" // DebugAssert
"                STR     R7, [R5,#8]\n"
"                B       loc_FF860F48\n"
    );
}

// FF89DC5C
void __attribute__((naked,noinline)) exp_drv_task() {
	asm volatile (
"                STMFD   SP!, {R4-R8,LR}\n"
"                SUB     SP, SP, #0x20\n"
"                LDR     R8, =0xBB8\n"
"                LDR     R7, =0x3D08\n"
"                LDR     R5, =0x18FAC\n"
"                MOV     R0, #0\n"
"                ADD     R6, SP, #0x10\n"
"                STR     R0, [SP,#0xC]\n"
"loc_FF89DC7C:\n"                            // ExpDrv Main loop
"                LDR     R0, [R7,#0x20]\n"
"                MOV     R2, #0\n"
"                ADD     R1, SP, #0x1C\n"
"                BL      sub_FF826C30\n" // KerQueue.c 0
"                LDR     R0, [SP,#0xC]\n"
"                CMP     R0, #1\n"
"                BNE     loc_FF89DCC8\n"
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R0, [R0]\n"
"                CMP     R0, #0x13\n"
"                CMPNE   R0, #0x14\n"
"                CMPNE   R0, #0x15\n"
"                CMPNE   R0, #0x16\n"
"                BEQ     loc_FF89DDE4\n"
"                CMP     R0, #0x28\n"
"                BEQ     loc_FF89DDBC\n"
"                ADD     R1, SP, #0xC\n"
"                MOV     R0, #0\n"
"                BL      sub_FF89DC0C\n" // ExpDrv.c 512
"loc_FF89DCC8:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x2D\n"
"                BNE     loc_FF89DCF8\n"
"                LDR     R0, [SP,#0x1C]\n"
"                BL      sub_FF89EF14\n" // ExpDrv.c 280
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R1, #1\n"
"                BL      sub_FF869BC0\n"
"                BL      sub_FF81B23C\n" // eventproc_export_ExitTask
"                ADD     SP, SP, #0x20\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
"loc_FF89DCF8:\n"
"                CMP     R1, #0x2C\n"
"                BNE     loc_FF89DD14\n"
"                LDR     R2, [R0,#0x88]!\n"
"                LDR     R1, [R0,#4]\n"
"                MOV     R0, R1\n"
"                BLX     R2\n"
"                B       loc_FF89E20C\n"
"loc_FF89DD14:\n"
"                CMP     R1, #0x26\n"
"                BNE     loc_FF89DD64\n"
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R1, #0x80\n"
"                BL      sub_FF869BF4\n"
"                LDR     R0, =0xFF89A570\n"
"                MOV     R1, #0x80\n"
"                BL      sub_FF928074\n" // IrisController.c 74
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R2, R8\n"
"                MOV     R1, #0x80\n"
"                BL      sub_FF869B00\n" // KerFlag.c 0
"                TST     R0, #1\n"
"                LDRNE   R1, =0xDD2\n"
"                BNE     loc_FF89DDA8\n"
"loc_FF89DD50:\n"
"                LDR     R1, [SP,#0x1C]\n"
"                LDR     R0, [R1,#0x8C]\n"
"                LDR     R1, [R1,#0x88]\n"
"                BLX     R1\n"
"                B       loc_FF89E20C\n"
"loc_FF89DD64:\n"
"                CMP     R1, #0x27\n"
"                BNE     loc_FF89DDB4\n"
"                ADD     R1, SP, #0xC\n"
"                BL      sub_FF89DC0C\n" // ExpDrv.c 512
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R1, #0x100\n"
"                BL      sub_FF869BF4\n"
"                LDR     R0, =0xFF89A580\n"
"                MOV     R1, #0x100\n"
"                BL      sub_FF9282FC\n" // IrisController.c 160
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R2, R8\n"
"                MOV     R1, #0x100\n"
"                BL      sub_FF869B00\n" // KerFlag.c 0
"                TST     R0, #1\n"
"                BEQ     loc_FF89DD50\n"
"                LDR     R1, =0xDDC\n"
"loc_FF89DDA8:\n"
"                LDR     R0, =0xFF89ABB0\n" // "expdrv.c"
"                BL      _DebugAssert\n"
"                B       loc_FF89DD50\n"
"loc_FF89DDB4:\n"
"                CMP     R1, #0x28\n"
"                BNE     loc_FF89DDCC\n"
"loc_FF89DDBC:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                ADD     R1, SP, #0xC\n"
"                BL      sub_FF89DC0C\n" // ExpDrv.c 512
"                B       loc_FF89DD50\n"
"loc_FF89DDCC:\n"
"                CMP     R1, #0x2B\n"
"                BNE     loc_FF89DDE4\n"
"                BL      sub_FF88D090\n" // Shutter.c 2
"                BL      sub_FF88DD1C\n" // ImgPixel.c 0
"                BL      sub_FF88D854\n" // ImgGain.c 0
"                B       loc_FF89DD50\n"
"loc_FF89DDE4:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                MOV     R4, #1\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x11\n"
"                CMPNE   R1, #0x12\n"
"                BNE     loc_FF89DE54\n"
"                LDR     R1, [R0,#0x7C]\n"
"                ADD     R1, R1, R1,LSL#1\n"
"                ADD     R1, R0, R1,LSL#2\n"
"                SUB     R1, R1, #8\n"
"                LDMIA   R1, {R2-R4}\n"
"                STMIA   R6, {R2-R4}\n"
"                BL      sub_FF89C648\n" // ExpDrv.c 2
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R1, [R0,#0x7C]\n"
"                LDR     R3, [R0,#0x88]\n"
"                LDR     R2, [R0,#0x8C]\n"
"                ADD     R0, R0, #4\n"
"                BLX     R3\n"
"                LDR     R0, [SP,#0x1C]\n"
"                BL      sub_FF89F2CC\n" // ExpDrv.c 0
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R1, [R0,#0x7C]\n"
"                LDR     R3, [R0,#0x90]\n"
"                LDR     R2, [R0,#0x94]\n"
"                ADD     R0, R0, #4\n"
"                BLX     R3\n"
"                B       loc_FF89E14C\n"
"loc_FF89DE54:\n"
"                CMP     R1, #0x13\n"
"                CMPNE   R1, #0x14\n"
"                CMPNE   R1, #0x15\n"
"                CMPNE   R1, #0x16\n"
"                BNE     loc_FF89DF0C\n"
"                ADD     R3, SP, #0xC\n"
"                MOV     R2, SP\n"
"                ADD     R1, SP, #0x10\n"
"                BL      sub_FF89C88C\n" // ExpDrv.c 0
"                CMP     R0, #1\n"
"                MOV     R4, R0\n"
"                CMPNE   R4, #5\n"
"                BNE     loc_FF89DEA8\n"
"                LDR     R0, [SP,#0x1C]\n"
"                MOV     R2, R4\n"
"                LDR     R1, [R0,#0x7C]!\n"
"                LDR     R12, [R0,#0xC]!\n"
"                LDR     R3, [R0,#4]\n"
"                MOV     R0, SP\n"
"                BLX     R12\n"
"                B       loc_FF89DEE0\n"
"loc_FF89DEA8:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                CMP     R4, #2\n"
"                LDR     R3, [R0,#0x8C]\n"
"                CMPNE   R4, #6\n"
"                BNE     loc_FF89DEF4\n"
"                LDR     R12, [R0,#0x88]\n"
"                MOV     R0, SP\n"
"                MOV     R2, R4\n"
"                MOV     R1, #1\n"
"                BLX     R12\n"
"                LDR     R0, [SP,#0x1C]\n"
"                MOV     R2, SP\n"
"                ADD     R1, SP, #0x10\n"
"                BL      sub_FF89D8E8\n" // ExpDrv.c 0
"loc_FF89DEE0:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R2, [SP,#0xC]\n"
"                MOV     R1, R4\n"
"                BL      sub_FF89DBAC\n" // ExpDrv.c 2
"                B       loc_FF89E14C\n"
"loc_FF89DEF4:\n"
"                LDR     R1, [R0,#0x7C]\n"
"                LDR     R12, [R0,#0x88]\n"
"                ADD     R0, R0, #4\n"
"                MOV     R2, R4\n"
"                BLX     R12\n"
"                B       loc_FF89E14C\n"
"loc_FF89DF0C:\n"
"                CMP     R1, #0x22\n"
"                CMPNE   R1, #0x23\n"
"                BNE     loc_FF89DF58\n"
"                LDR     R1, [R0,#0x7C]\n"
"                ADD     R1, R1, R1,LSL#1\n"
"                ADD     R1, R0, R1,LSL#2\n"
"                SUB     R1, R1, #8\n"
"                LDMIA   R1, {R2-R4}\n"
"                STMIA   R6, {R2-R4}\n"
"                BL      sub_FF89BBD4\n" // ExpDrv.c 0
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R1, [R0,#0x7C]\n"
"                LDR     R3, [R0,#0x88]\n"
"                LDR     R2, [R0,#0x8C]\n"
"                ADD     R0, R0, #4\n"
"                BLX     R3\n"
"                LDR     R0, [SP,#0x1C]\n"
"                BL      sub_FF89BEC4\n" // ExpDrv.c 0
"                B       loc_FF89E14C\n"
"loc_FF89DF58:\n"
"                ADD     R1, R0, #4\n"
"                LDMIA   R1, {R2,R3,R12}\n"
"                STMIA   R6, {R2,R3,R12}\n"
"                LDR     R1, [R0]\n"
"                CMP     R1, #0x25\n"
"                ADDLS   PC, PC, R1,LSL#2\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E00C\n"
"                B       loc_FF89E00C\n"
"                B       loc_FF89E014\n"
"                B       loc_FF89E01C\n"
"                B       loc_FF89E01C\n"
"                B       loc_FF89E01C\n"
"                B       loc_FF89E00C\n"
"                B       loc_FF89E014\n"
"                B       loc_FF89E01C\n"
"                B       loc_FF89E01C\n"
"                B       loc_FF89E034\n"
"                B       loc_FF89E034\n"
"                B       loc_FF89E120\n"
"                B       loc_FF89E128\n"
"                B       loc_FF89E128\n"
"                B       loc_FF89E128\n"
"                B       loc_FF89E128\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E024\n"
"                B       loc_FF89E02C\n"
"                B       loc_FF89E02C\n"
"                B       loc_FF89E040\n"
"                B       loc_FF89E040\n"
"                B       loc_FF89E048\n"
"                B       loc_FF89E078\n"
"                B       loc_FF89E0A8\n"
"                B       loc_FF89E0D8\n"
"                B       loc_FF89E108\n"
"                B       loc_FF89E108\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E12C\n"
"                B       loc_FF89E110\n"
"                B       loc_FF89E118\n"
"loc_FF89E00C:\n"
// jumptable FF89DF6C entries 0,1,6
"                BL      sub_FF89AA5C\n" // ExpDrv.c 2
"                B       loc_FF89E12C\n"
"loc_FF89E014:\n"
// jumptable FF89DF6C entries 2,7
"                BL      sub_FF89ACD0\n" // ExpDrv.c 0
"                B       loc_FF89E12C\n"
"loc_FF89E01C:\n"
// jumptable FF89DF6C entries 3-5,8,9
"                BL      sub_FF89AED4\n" // ExpDrv.c 1016
"                B       loc_FF89E12C\n"
"loc_FF89E024:\n"
// jumptable FF89DF6C entry 23
"                BL      sub_FF89B13C\n" // ExpDrv.c 2
"                B       loc_FF89E12C\n"
"loc_FF89E02C:\n"
// jumptable FF89DF6C entries 24,25
"                BL      sub_FF89B330\n" // ExpDrv.c 0
"                B       loc_FF89E12C\n"
"loc_FF89E034:\n"
// jumptable FF89DF6C entries 10,11
"                BL      sub_FF89B5C0_my\n" // ExpDrv.c 2 ->
"                MOV     R4, #0\n"
"                B       loc_FF89E12C\n"
"loc_FF89E040:\n"
// jumptable FF89DF6C entries 26,27
"                BL      sub_FF89B6FC\n" // ExpDrv.c 0
"                B       loc_FF89E12C\n"
"loc_FF89E048:\n"
// jumptable FF89DF6C entry 28
"                LDRH    R1, [R0,#4]\n"
"                STRH    R1, [SP,#0x10]\n"
"                LDRH    R1, [R5,#2]\n"
"                STRH    R1, [SP,#0x12]\n"
"                LDRH    R1, [R5,#4]\n"
"                STRH    R1, [SP,#0x14]\n"
"                LDRH    R1, [R5,#6]\n"
"                STRH    R1, [SP,#0x16]\n"
"                LDRH    R1, [R0,#0xC]\n"
"                STRH    R1, [SP,#0x18]\n"
"                BL      sub_FF89EF88\n" // ExpDrv.c 2
"                B       loc_FF89E12C\n"
"loc_FF89E078:\n"
// jumptable FF89DF6C entry 29
"                LDRH    R1, [R0,#4]\n"
"                STRH    R1, [SP,#0x10]\n"
"                LDRH    R1, [R5,#2]\n"
"                STRH    R1, [SP,#0x12]\n"
"                LDRH    R1, [R5,#4]\n"
"                STRH    R1, [SP,#0x14]\n"
"                LDRH    R1, [R5,#6]\n"
"                STRH    R1, [SP,#0x16]\n"
"                LDRH    R1, [R5,#8]\n"
"                STRH    R1, [SP,#0x18]\n"
"                BL      sub_FF89F0E8\n" // ExpDrv.c 2
"                B       loc_FF89E12C\n"
"loc_FF89E0A8:\n"
// jumptable FF89DF6C entry 30
"                LDRH    R1, [R5]\n"
"                STRH    R1, [SP,#0x10]\n"
"                LDRH    R1, [R0,#6]\n"
"                STRH    R1, [SP,#0x12]\n"
"                LDRH    R1, [R5,#4]\n"
"                STRH    R1, [SP,#0x14]\n"
"                LDRH    R1, [R5,#6]\n"
"                STRH    R1, [SP,#0x16]\n"
"                LDRH    R1, [R5,#8]\n"
"                STRH    R1, [SP,#0x18]\n"
"                BL      sub_FF89F194\n" // ExpDrv.c 0
"                B       loc_FF89E12C\n"
"loc_FF89E0D8:\n"
// jumptable FF89DF6C entry 31
"                LDRH    R1, [R5]\n"
"                STRH    R1, [SP,#0x10]\n"
"                LDRH    R1, [R5,#2]\n"
"                STRH    R1, [SP,#0x12]\n"
"                LDRH    R1, [R5,#4]\n"
"                STRH    R1, [SP,#0x14]\n"
"                LDRH    R1, [R5,#6]\n"
"                STRH    R1, [SP,#0x16]\n"
"                LDRH    R1, [R0,#0xC]\n"
"                STRH    R1, [SP,#0x18]\n"
"                BL      sub_FF89F234\n" // ExpDrv.c 32
"                B       loc_FF89E12C\n"
"loc_FF89E108:\n"
// jumptable FF89DF6C entries 32,33
"                BL      sub_FF89B99C\n" // ExpDrv.c 1744
"                B       loc_FF89E12C\n"
"loc_FF89E110:\n"
// jumptable FF89DF6C entry 36
"                BL      sub_FF89BFC8\n" // ExpDrv.c 10
"                B       loc_FF89E12C\n"
"loc_FF89E118:\n"
// jumptable FF89DF6C entry 37
"                BL      sub_FF89C200\n" // ExpDrv.c 2176
"                B       loc_FF89E12C\n"
"loc_FF89E120:\n"
// jumptable FF89DF6C entry 12
"                BL      sub_FF89C378\n" // ExpDrv.c 2
"                B       loc_FF89E12C\n"
"loc_FF89E128:\n"
// jumptable FF89DF6C entries 13-16
"                BL      sub_FF89C510\n" // ExpDrv.c 128
"loc_FF89E12C:\n"
// jumptable FF89DF6C default entry
// jumptable FF89DF6C entries 17-22,34,35
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R1, [R0,#0x7C]\n"
"                LDR     R3, [R0,#0x88]\n"
"                LDR     R2, [R0,#0x8C]\n"
"                ADD     R0, R0, #4\n"
"                BLX     R3\n"
"                CMP     R4, #1\n"
"                BNE     loc_FF89E194\n"
"loc_FF89E14C:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                MOV     R2, #0xC\n"
"                LDR     R1, [R0,#0x7C]\n"
"                ADD     R1, R1, R1,LSL#1\n"
"                ADD     R0, R0, R1,LSL#2\n"
"                SUB     R4, R0, #8\n"
"                LDR     R0, =0x18FAC\n"
"                ADD     R1, SP, #0x10\n"
"                BL      sub_FFACBD60\n"
"                LDR     R0, =0x18FB8\n"
"                MOV     R2, #0xC\n"
"                ADD     R1, SP, #0x10\n"
"                BL      sub_FFACBD60\n"
"                LDR     R0, =0x18FC4\n"
"                MOV     R2, #0xC\n"
"                MOV     R1, R4\n"
"                BL      sub_FFACBD60\n"
"                B       loc_FF89E20C\n"
"loc_FF89E194:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                LDR     R0, [R0]\n"
"                CMP     R0, #0xB\n"
"                BNE     loc_FF89E1DC\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                MOV     R3, #1\n"
"                MOV     R2, #1\n"
"                MOV     R1, #1\n"
"                MOV     R0, #0\n"
"                BL      sub_FF89A864\n"
"                MOV     R3, #0\n"
"                STR     R3, [SP]\n"
"                MOV     R3, #1\n"
"                MOV     R2, #1\n"
"                MOV     R1, #1\n"
"                MOV     R0, #0\n"
"                B       loc_FF89E208\n"
"loc_FF89E1DC:\n"
"                MOV     R3, #1\n"
"                MOV     R2, #1\n"
"                MOV     R1, #1\n"
"                MOV     R0, #1\n"
"                STR     R3, [SP]\n"
"                BL      sub_FF89A864\n"
"                MOV     R3, #1\n"
"                MOV     R2, #1\n"
"                MOV     R1, #1\n"
"                MOV     R0, #1\n"
"                STR     R3, [SP]\n"
"loc_FF89E208:\n"
"                BL      sub_FF89A9A4\n"
"loc_FF89E20C:\n"
"                LDR     R0, [SP,#0x1C]\n"
"                BL      sub_FF89EF14\n" // ExpDrv.c 280
"                B       loc_FF89DC7C\n" // -> ExpDrv Main loop
    );
}
void __attribute__((naked,noinline)) sub_FF89B5C0_my()
{
	asm volatile (
"                STMFD   SP!, {R4-R8,LR}\n"
"                LDR     R7, =0x3D08\n"
"                MOV     R4, R0\n"
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R1, #0x3E\n"
"                BL      sub_FF869BF4\n"
"                LDRSH   R0, [R4,#4]\n"
"                MOV     R2, #0\n"
"                MOV     R1, #0\n"
"                BL      sub_FF89A5F4\n"
"                MOV     R6, R0\n"
"                LDRSH   R0, [R4,#6]\n"
"                BL      sub_FF89A704\n"
"                LDRSH   R0, [R4,#8]\n"
"                BL      sub_FF89A75C\n"
"                LDRSH   R0, [R4,#0xA]\n"
"                BL      sub_FF89A7B4\n"
"                LDRSH   R0, [R4,#0xC]\n"
"                BL      sub_FF89A80C\n"
"                MOV     R5, R0\n"
"                LDR     R0, [R4]\n"
"                LDR     R8, =0x18FC4\n"
"                CMP     R0, #0xB\n"
"                MOVEQ   R6, #0\n"
"                MOVEQ   R5, #0\n"
"                BEQ     loc_FF89B650\n"
"                CMP     R6, #1\n"
"                BNE     loc_FF89B650\n"
"                LDRSH   R0, [R4,#4]\n"
"                LDR     R1, =0xFF89A560\n"
"                MOV     R2, #2\n"
"                BL      sub_FF9281C8\n" // IrisController.c 117
"                STRH    R0, [R4,#4]\n"
"                MOV     R0, #0\n"
"                STR     R0, [R7,#0x28]\n"
"                B       loc_FF89B658\n"
"loc_FF89B650:\n"
"                LDRH    R0, [R8]\n"
"                STRH    R0, [R4,#4]\n"
"loc_FF89B658:\n"
"                CMP     R5, #1\n"
"                LDRNEH  R0, [R8,#8]\n"
"                BNE     loc_FF89B674\n"
"                LDRSH   R0, [R4,#0xC]\n"
"                LDR     R1, =0xFF89A5E4\n"
"                MOV     R2, #0x20\n"
"                BL      sub_FF89EF44\n"
"loc_FF89B674:\n"
"                STRH    R0, [R4,#0xC]\n"
"                LDRSH   R0, [R4,#6]\n"
"                BL      sub_FF88CE00_my\n" // Shutter.c 320 ->
"                LDR     PC,=0xFF89B680\n" // -> jump back to firmware
/*
"                LDRSH   R0, [R4,#8]\n"
"                MOV     R1, #1\n"
"                BL      sub_FF88D54C\n" // ImgGain.c 288
"                MOV     R1, #0\n"
"                ADD     R0, R4, #8\n"
"                BL      sub_FF88D5D4\n" // ImgGain.c 0
"                LDRSH   R0, [R4,#0xE]\n"
"                BL      sub_FF896064\n" // BrtCrct.c 560
"                LDR     R4, =0xBB8\n"
"                CMP     R6, #1\n"
"                BNE     loc_FF89B6CC\n"
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R2, R4\n"
"                MOV     R1, #2\n"
"                BL      sub_FF869B00\n" // KerFlag.c 0
"                TST     R0, #1\n"
"                LDRNE   R1, =0x583\n"
"                LDRNE   R0, =0xFF89ABB0\n" // "ExpDrv.c"
"                BLNE    _DebugAssert\n"
"loc_FF89B6CC:\n"
"                CMP     R5, #1\n"
"                LDMNEFD SP!, {R4-R8,PC}\n"
"                LDR     R0, [R7,#0x1C]\n"
"                MOV     R2, R4\n"
"                MOV     R1, #0x20\n"
"                BL      sub_FF869B00\n" // KerFlag.c 0
"                TST     R0, #1\n"
"                LDRNE   R1, =0x588\n"
"                LDRNE   R0, =0xFF89ABB0\n" // "ExpDrv.c"
"                LDMNEFD SP!, {R4-R8,LR}\n"
"                BNE     _DebugAssert\n"
"                LDMFD   SP!, {R4-R8,PC}\n"
*/
    );
}
void __attribute__((naked,noinline)) sub_FF88CE00_my() {
	asm volatile (
"                STMFD   SP!, {R4-R6,LR}\n"
"                LDR     R5, =0x39FC\n"
"                MOV     R4, R0\n"
"                LDR     R0, [R5,#4]\n"
"                CMP     R0, #1\n"
"                MOVNE   R1, #0x140\n"
"                LDRNE   R0, =0xFF88CC04\n" // "shutter.c"
"                BLNE    _DebugAssert\n"
"                CMN     R4, #0xC00\n"
"                LDREQSH R4, [R5,#2]\n"
"                CMN     R4, #0xC00\n"
"                LDREQ   R1, =0x146\n"
"                LDREQ   R0, =0xFF88CC04\n" // "shutter.c"
"                STRH    R4, [R5,#2]\n"
"                BLEQ    _DebugAssert\n"
"                MOV     R0, R4\n"
"                BL      apex2us\n"
"                LDR     PC, =0xFF88CE44\n" // -> jump back to to firmware
/*
"                MOV     R4, R0\n"
//"                BL      nullsub_190\n"
"                MOV     R0, R4\n"
"                BL      sub_FF8C7954\n"
"                TST     R0, #1\n"
"                LDRNE   R1, =0x14B\n"
"                LDMNEFD SP!, {R4-R6,LR}\n"
"                LDRNE   R0, =0xFF88CC04\n" // "shutter.c"
"                BNE     _DebugAssert\n"
"                LDMFD   SP!, {R4-R6,PC}\n"
*/
    );
}

