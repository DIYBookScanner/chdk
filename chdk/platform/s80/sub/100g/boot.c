#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;
extern void createHook (void *pNewTcb);
extern void deleteHook (void *pTcb);

void boot();

/* "relocated" functions */
void __attribute__((naked,noinline)) h_usrInit();
void __attribute__((naked,noinline)) h_usrKernelInit();
void __attribute__((naked,noinline)) h_usrRoot();

void boot()
{

    long *canon_data_src = (void*)0xFFB1A3F0;	//
    long *canon_data_dst = (void*)0x1900; //
    long canon_data_len = 0xefe0;	//
    long *canon_bss_start = (void*)0x108E0; // just after data
    long canon_bss_len = 0xA27F0 - 0x108E0; //
    long i;

    asm volatile (			// loc_FF8100E0
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"ORR     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");

    for(i=0;i<canon_data_len/4;i++)
	canon_data_dst[i]=canon_data_src[i];

    for(i=0;i<canon_bss_len/4;i++)
	canon_bss_start[i]=0;

    asm volatile (			// loc_FF81015C
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
	"LDR	LR, [SP],#4\n"
    :::"r0");

    h_usrInit();
}


void h_usrInit()			// loc_FF811990
{
    asm volatile (
	"STR     LR, [SP,#-4]!\n"
	"BL      sub_FF81196C\n"
	"MOV     R0, #2\n"
	"MOV     R1, R0\n"
	"BL      sub_FFAFE04C\n"	// unknown_libname_889
	"BL      sub_FFAEA724\n"	// excVecInit
	"BL      sub_FF8111C4\n"
	"BL      sub_FF81172C\n"
	"LDR     LR, [SP],#4\n"
	"B       h_usrKernelInit\n"
    );
}

void  h_usrKernelInit()			//loc_FF811748 
{
    asm volatile (
	"STMFD   SP!, {R4,LR}\n"
	"SUB     SP, SP, #8\n"
	"BL      sub_FFAFE54C\n"	// classLibInit
	"BL      sub_FFB13838\n"	// taskLibInit
	"LDR     R3, =0xF874\n"
	"LDR     R2, =0x9EEA0\n"
	"LDR     R1, [R3]\n"
	"LDR     R0, =0xA21B0\n"
	"MOV     R3, #0x100\n"
	"BL      sub_FFB0C688\n"	// qInit
	"LDR     R3, =0xF834\n"
	"LDR     R0, =0x100FC\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB0C688\n"	// qInit
	"LDR     R3, =0xF8F0\n"
	"LDR     R0, =0xA2184\n"
	"LDR     R1, [R3]\n"
	"BL      sub_FFB0C688\n"
	"BL      sub_FFB183B8\n"	// workQInit
	"BL      sub_FF8112B0\n"
	"MOV     R4, #0\n"
	"MOV     R3, R0\n"
	"MOV     R12, #0x800\n"
	"LDR     R0, =h_usrRoot\n"	// h_usrRoot -> sub_FF811A70
	"MOV     R1, #0x4000\n"
	//"LDR     R2, =0xE27F0\n"	// 0xA27F0 + 0x40000
    );    
    asm volatile (
        "LDR     R2, =new_sa\n"
        "LDR     R2, [R2]\n"
    );
    asm volatile (
	"STR     R12, [SP]\n"
	"STR     R4, [SP,#4]\n"
	"BL      sub_FFB10A78\n"	// kernelInit
	"ADD     SP, SP, #8\n"
	"LDMFD   SP!, {R4,PC}\n"
    );
}

void  h_usrRoot()			// sub_FF811A70
{
    asm volatile (
	"STMFD   SP!, {R4,R5,LR}\n"
	"MOV     R5, R0\n"
	"MOV     R4, R1\n"
	"BL      sub_FF8119D4\n"
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB046C8\n"	// memInit
	"MOV     R1, R4\n"
	"MOV     R0, R5\n"
	"BL      sub_FFB05140\n"	// memPartLibInit
	//"BL      sub_FF8117EC\n"	// nullstub_1, null stub, useless
	"BL      sub_FF811708\n"
	"MOV     R0, #0x32\n"
	"BL      sub_FFB070E4\n"	// selectInit
	"BL      sub_FF811A18\n"
	"BL      sub_FF8119F8\n"
	"BL      sub_FF811A44\n"
	"BL      sub_FFB069A4\n"	// selTaskDeleteHookAdd
	"BL      sub_FF8119C8\n"
  );

    _taskCreateHookAdd(createHook);
    _taskDeleteHookAdd(deleteHook);

    drv_self_hide();

    asm volatile (
	"LDMFD   SP!, {R4,R5,LR}\n"
	"B       sub_FF811370\n"
    );
}

static int jogdial_is_stopped = 0;

void set_jogdial_is_stopped () {
    extern int jogdial_stopped; // from kbd.c
    if (jogdial_stopped == 0)
        jogdial_is_stopped = 0;
    else
        jogdial_is_stopped = 1;
}

void __attribute__((naked,noinline)) sub_FF965FA8_my() { //
    asm volatile (
        "MOV R1, #0\n"
    "sub_FF965FB8_my:\n"
        "LDR R2, =jogdial_is_stopped\n"
        "LDR R2, [R2]\n"
        "CMP R2, #0\n"
        "BEQ sub_FF965FB8\n"                // emit control events only when not in ALT mode
        "BX  LR\n"
    );
}

void __attribute__((naked,noinline)) task_JogDial_my() { // sub_FF8287A8_my
asm volatile (
      "    STMFD   SP!, {R4-R11,LR} \n" 
      "    MOV     R7, #0x240000 \n" 
      "    MOV     R9, #0x80000000 \n" 
      "    ADD     R7, R7, #0x400 \n" 
      "    LDR     R10, =0x11A70 \n" 
      "    LDR     R8, =0x11A72 \n" 
      "    LDR     R11, =0x11A74 \n" 
      "    MOV     R9, R9, ASR #0xF \n" 
      "    ADD     R7, R7, #0xC0000004 \n" 
"loc_FF8287CC:\n"
      "    LDR     R3, =0x11A64 \n" 
      "    MOV     R1, #0 \n" 
      "    LDR     R0, [R3] \n" 
      "    BL      sub_FF820F74 \n"         // TakeSemaphore
      "    MOV     R0, #0x28 \n" 
      "    BL      _SleepTask \n" 
      "BL set_jogdial_is_stopped\n"         // +
      "    LDR     R12, [R7] \n" 
      "    MOV     R3, #0x204 \n" 
      "    ADD     R3, R3, #0xC0000000 \n" 
      "    ADD     R3, R3, #0x240000 \n" 
      "    AND     R12, R12, R9 \n" 
      "    MOV     R12, R12, LSR #0x10 \n" 
      "    LDR     R2, [R3] \n" 
      "    MOV     R1, R12, LSL #0x10 \n" 
      "    LDRSH   R3, [R8] \n" 
      "    AND     R2, R2, R9 \n" 
      "    MOV     R1, R1, ASR #0x10 \n" 
      "    MOV     R2, R2, LSR #0x10 \n" 
      "    CMP     R1, R3 \n" 
      "    STRH    R2, [R11] \n" 
      "    STRH    R12, [R10] \n" 
      "    BEQ     loc_FF82898C \n" 
      "    BLE     loc_FF828850 \n" 
      "    LDRSH   R2, [R10] \n" 
      "    LDRSH   R3, [R8] \n" 
      "    RSB     R1, R3, R2 \n" 
      "    CMP     R1, #0xFF \n" 
      "    RSBGT   R3, R2, R3 \n" 
      "    ADDGT   R5, R3, #0x10000 \n" 
      "    BGT     loc_FF828874 \n" 
      "    MOV     R5, R1 \n" 
      "    MOV     R4, #1 \n" 
      "    B       loc_FF828878 \n" 
"loc_FF828850:\n"
      "    LDRSH   R2, [R8] \n" 
      "    LDRSH   R3, [R10] \n" 
      "    RSB     R1, R3, R2 \n" 
      "    CMP     R1, #0xFF \n" 
      "    RSBGT   R3, R2, R3 \n" 
      "    ADDGT   R5, R3, #0x10000 \n" 
      "    MOVGT   R4, #1 \n" 
      "    BGT     loc_FF828878 \n" 
      "    MOV     R5, R1 \n" 
"loc_FF828874:\n"
      "    MOV     R4, #0 \n" 
"loc_FF828878:\n"
      "    CMP     R5, #1 \n" 
      "    MOV     R12, #1 \n" 
      "    BNE     loc_FF8288E4 \n" 
      "    LDR     R3, =0x11A76 \n" 
      "    LDR     LR, =0x11A70 \n" 
      "    LDR     R6, =0x11A74 \n" 
      "    LDRSH   R0, [R3] \n" 
      "    LDRSH   R2, [LR] \n" 
      "    LDRSH   R1, [R8] \n" 
      "    LDRSH   R3, [R6] \n" 
      "    RSB     R2, R1, R2 \n" 
      "    RSB     R3, R0, R3 \n" 
      "    CMP     R2, R3 \n" 
      "    BNE     loc_FF8288E4 \n" 
      "    MOV     R3, #0x204 \n" 
      "    ADD     R3, R3, #0xC0000000 \n" 
      "    MOV     R5, #0 \n" 
      "    MOV     R1, R12 \n" 
      "    MOV     R2, #2 \n" 
      "    ADD     R3, R3, #0x240000 \n" 
      "    STR     R2, [R7] \n" 
      "    STRH    R5, [LR] \n" 
      "    STR     R1, [R7] \n" 
      "    STRH    R5, [R6] \n" 
      "    STR     R2, [R3] \n" 
      "    STR     R1, [R3] \n" 
      "    MOV     R12, R5 \n" 
"loc_FF8288E4:\n"
      "    CMP     R12, #0 \n" 
      "    BEQ     loc_FF828978 \n" 
      "    LDR     R3, =0x11A84 \n" 
      "    LDR     R1, [R3] \n" 
      "    CMP     R1, #0 \n" 
      "    BEQ     loc_FF828928 \n" 
      "    LDR     R2, =0x1FDC \n" 
      "    MOV     R6, R4, LSL #2 \n" 
      "    LDR     R3, [R6, R2] \n" 
      "    CMP     R3, R1 \n" 
      "    BEQ     loc_FF828938 \n" 
      "    MOV     R4, #0xB00 \n" 
      "    ADD     R0, R4, #1 \n" 
      "    BL      sub_FF965FA8_my \n"      // -> spec case of sub_FF965FB8 (with R1=0)
      "    ADD     R0, R4, #0x80000001 \n" 
      "    BL      sub_FF965FA8_my \n"      // ->
      "    B       loc_FF828938 \n" 
"loc_FF828928:\n"
      "    MOV     R0, #0xB00 \n" 
      "    ADD     R0, R0, #0x80000001 \n" 
      "    BL      sub_FF965FA8_my \n"      // ->
      "    MOV     R6, R4, LSL #2 \n" 
"loc_FF828938:\n"
      "    LDR     R4, =0x1FDC \n" 
      "    LDR     R2, =0x11A84 \n" 
      "    LDR     R3, [R6, R4] \n" 
      "    MOV     R1, R5 \n" 
      "    STR     R3, [R2] \n" 
      "    MOV     R0, R3 \n" 
      "    BL      sub_FF965FB8_my \n"      // ->
      "    LDR     R3, =0x1FD0 \n" 
      "    LDR     R2, [R3] \n" 
      "    CMP     R2, #0 \n" 
      "    BEQ     loc_FF828978 \n" 
      "    LDR     R1, [R6, R4] \n" 
      "    MOV     R2, R5 \n" 
      "    LDR     R0, =0xFF828788 \n" 
      "    LDRSH   R3, [R10] \n" 
      "    BL      sub_FFB007A8 \n"         // printf
"loc_FF828978:\n"
      "    LDR     R3, =0x11A76 \n" 
      "    LDRH    R2, [R11] \n" 
      "    STRH    R2, [R3] \n" 
      "    LDRH    R3, [R10] \n" 
      "    STRH    R3, [R8] \n" 
"loc_FF82898C:\n"
      "    MOV     R2, #0x240000 \n" 
      "    MOV     R3, #0xC0000000 \n" 
      "    ADD     R2, R2, #0x400 \n" 
      "    ADD     R3, R3, #0x240000 \n" 
      "    MOV     R0, #0 \n" 
      "    ADD     R2, R2, #0xC0000008 \n" 
      "    MOV     R1, #1 \n" 
      "    STR     R0, [R3, #0x400] \n" 
      "    STR     R1, [R2] \n" 
      "    LDR     R3, =0x11A78 \n" 
      "    LDR     R0, [R3] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FF8287CC \n" 
      "    BL      _SleepTask \n" 
      "    B       loc_FF8287CC \n" 
    );
}
