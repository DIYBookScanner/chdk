#include "lolevel.h"
#include "platform.h"
#include "core.h"
#include "dryos31.h"
#define offsetof(TYPE, MEMBER) ((int) &((TYPE *)0)->MEMBER)

const char * const new_sa = &_end;

void CreateTask_PhySw();
void CreateTask_spytask();

extern void task_CaptSeq();
extern void task_InitFileModules();
extern void task_MovieRecord();
extern void task_ExpDrv();
extern void task_PhySw();
#if 0
extern void task_TouchPanel();
void task_TouchPanel_my(void);
#endif

void taskHook(context_t **context) {

    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	if(tcb->entry == (void*)task_PhySw)            tcb->entry = (void*)mykbd_task;
	if(tcb->entry == (void*)task_CaptSeq)          tcb->entry = (void*)capt_seq_task; 
	if(tcb->entry == (void*)task_InitFileModules)  tcb->entry = (void*)init_file_modules_task;
	if(tcb->entry == (void*)task_MovieRecord)      tcb->entry = (void*)movie_record_task;
	if(tcb->entry == (void*)task_ExpDrv)           tcb->entry = (void*)exp_drv_task;
#if 0
	if(tcb->entry == (void*)task_TouchPanel)       tcb->entry = (void*)task_TouchPanel_my;
#endif
}

//** boot  @ 0xFF81000C 

void __attribute__((naked,noinline)) boot() {
asm volatile (
      "LDR     R1, =0xC0410000\n"
      "MOV     R0, #0\n"
      "STR     R0, [R1]\n"
      "MOV     R1, #0x78\n"
      "MCR     p15, 0, R1, c1, c0\n"
      "MOV     R1, #0\n"
      "MCR     p15, 0, R1, c7, c10, 4\n"
      "MCR     p15, 0, R1, c7, c5\n"
      "MCR     p15, 0, R1, c7, c6\n"
      "MOV     R0, #0x3D\n"
      "MCR     p15, 0, R0, c6, c0\n"
      "MOV     R0, #0xC000002F\n"
      "MCR     p15, 0, R0, c6, c1\n"
      "MOV     R0, #0x33\n"
      "MCR     p15, 0, R0, c6, c2\n"
      "MOV     R0, #0x40000033\n"
      "MCR     p15, 0, R0, c6, c3\n"
      "MOV     R0, #0x80000017\n"
      "MCR     p15, 0, R0, c6, c4\n"
      "LDR     R0, =0xFF80002D\n"
      "MCR     p15, 0, R0, c6, c5\n"
      "MOV     R0, #0x34\n"
      "MCR     p15, 0, R0, c2, c0\n"
      "MOV     R0, #0x34\n"
      "MCR     p15, 0, R0, c2, c0, 1\n"
      "MOV     R0, #0x34\n"
      "MCR     p15, 0, R0, c3, c0\n"
      "LDR     R0, =0x3333330\n"
      "MCR     p15, 0, R0, c5, c0, 2\n"
      "LDR     R0, =0x3333330\n"
      "MCR     p15, 0, R0, c5, c0, 3\n"
      "MRC     p15, 0, R0, c1, c0\n"
      "ORR     R0, R0, #0x1000\n"
      "ORR     R0, R0, #4\n"
      "ORR     R0, R0, #1\n"
      "MCR     p15, 0, R0, c1, c0\n"
      "MOV     R1, #0x80000006\n"
      "MCR     p15, 0, R1, c9, c1\n"
      "MOV     R1, #6\n"
      "MCR     p15, 0, R1, c9, c1, 1\n"
      "MRC     p15, 0, R1, c1, c0\n"
      "ORR     R1, R1, #0x50000\n"
      "MCR     p15, 0, R1, c1, c0\n"
      "LDR     R2, =0xC0200000\n"
      "MOV     R1, #1\n"
      "STR     R1, [R2, #0x10C]\n"
      "MOV     R1, #0xFF\n"
      "STR     R1, [R2, #0xC]\n"
      "STR     R1, [R2, #0x1C]\n"
      "STR     R1, [R2, #0x2C]\n"
      "STR     R1, [R2, #0x3C]\n"
      "STR     R1, [R2, #0x4C]\n"
      "STR     R1, [R2, #0x5C]\n"
      "STR     R1, [R2, #0x6C]\n"
      "STR     R1, [R2, #0x7C]\n"
      "STR     R1, [R2, #0x8C]\n"
      "STR     R1, [R2, #0x9C]\n"
      "STR     R1, [R2, #0xAC]\n"
      "STR     R1, [R2, #0xBC]\n"
      "STR     R1, [R2, #0xCC]\n"
      "STR     R1, [R2, #0xDC]\n"
      "STR     R1, [R2, #0xEC]\n"
      "STR     R1, [R2, #0xFC]\n"
      "LDR     R1, =0xC0400008\n"
      "LDR     R2, =0x430005\n"
      "STR     R2, [R1]\n"
      "MOV     R1, #1\n"
      "LDR     R2, =0xC0243100\n"
      "STR     R2, [R1]\n"
      "LDR     R2, =0xC0242010\n"
      "LDR     R1, [R2]\n"
      "ORR     R1, R1, #1\n"
      "STR     R1, [R2]\n"
      "LDR     R0, =0xFFC255D8\n"
      "LDR     R1, =0x3F1000\n"
      "LDR     R3, =0x400654\n"
"loc_FF81013C:\n"
      "CMP     R1, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF81013C\n"
      "LDR     R0, =0xFFC194A0\n"
      "LDR     R1, =0x1900\n"
      "LDR     R3, =0xDA38\n"
"loc_FF810158:\n"
      "CMP     R1, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF810158\n"
      "LDR     R1, =0x15969C\n" //MEMISOSTART
      "MOV     R2, #0\n"
"loc_FF810170:\n"
      "CMP     R3, R1\n"
      "STRCC   R2, [R3], #4\n"
      "BCC     loc_FF810170\n"
//      "B       sub_FF810380 \n" //original
      "B       sub_FF810380_my \n" //patched
	);
}

//** sub_FF810380_my  @ 0xFF810380 

void __attribute__((naked,noinline)) sub_FF810380_my() {

   //http://chdk.setepontos.com/index.php/topic,4194.0.html
   *(int*)0x1934=(int)taskHook;
   *(int*)0x1938=(int)taskHook;

    // Power Button detection (short press = playback mode, long press = record mode) 
    // C02200F8  ?? power up button
    // 0x24B8    a3400 101a Found @ 0xFF8563F8
    if ((*(int*) 0xC02200F8) & 1)                 // look at power-on switch
            *(int*)(0x24B8+4) = 0x200000;         // start in play mode
    else
            *(int*)(0x24B8+4) = 0x100000;         // start in rec mode
    
asm volatile (
      "LDR     R0, =0xFF8103F8\n"
      "MOV     R1, #0\n"
      "LDR     R3, =0xFF810430\n"
"loc_FF81038C:\n"
      "CMP     R0, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF81038C\n"
      "LDR     R0, =0xFF810430\n"
      "MOV     R1, #0x4B0\n"
      "LDR     R3, =0xFF810644\n"
"loc_FF8103A8:\n"
      "CMP     R0, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF8103A8\n"
      "MOV     R0, #0xD2\n"
      "MSR     CPSR_cxsf, R0\n"
      "MOV     SP, #0x1000\n"
      "MOV     R0, #0xD3\n"
      "MSR     CPSR_cxsf, R0\n"
      "MOV     SP, #0x1000\n"
      "LDR     R0, =0x6C4\n"
      "LDR     R2, =0xEEEEEEEE\n"
      "MOV     R3, #0x1000\n"
"loc_FF8103DC:\n"
      "CMP     R0, R3\n"
      "STRCC   R2, [R0], #4\n"
      "BCC     loc_FF8103DC\n"
//      "BL      sub_FF8111D8 \n" //original
      "BL      sub_FF8111D8_my \n" //patched
	);
}

//** sub_FF8111D8_my  @ 0xFF8111D8 

void __attribute__((naked,noinline)) sub_FF8111D8_my() {
asm volatile (
      "STR     LR, [SP, #-4]!\n"
      "SUB     SP, SP, #0x74\n"
      "MOV     R1, #0x74\n"
      "MOV     R0, SP\n"
      "BL      sub_003FC448\n" //RAM
      "MOV     R0, #0x57000\n"
      "STR     R0, [SP, #4]\n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
      "LDR     R0, =0x15969C\n" // MEMISOSTART: Use original heap offset since CHDK is loaded in high memory 
#else
      "LDR     R0, =new_sa \n"	    //otherwise use patched value
      "LDR     R0, [R0] \n"
#endif
      "LDR     R2, =0x2ED440\n"
      "STR     R0, [SP, #8]\n"
      "SUB     R0, R2, R0\n"
      "STR     R0, [SP, #0xC]\n"
      "MOV     R0, #0x22\n"
      "STR     R0, [SP, #0x18]\n"
      "MOV     R0, #0x7C\n"
      "STR     R0, [SP, #0x1C]\n"
      "LDR     R1, =0x2F5C00\n"
      "LDR     R0, =0x1CD\n"
      "STR     R1, [SP]\n"
      "STR     R0, [SP, #0x20]\n"
      "MOV     R0, #0x96\n"
      "STR     R2, [SP, #0x10]\n"
      "STR     R1, [SP, #0x14]\n"
      "STR     R0, [SP, #0x24]\n"
      "STR     R0, [SP, #0x28]\n"
      "MOV     R0, #0x64\n"
      "STR     R0, [SP, #0x2C]\n"
      "MOV     R0, #0\n"
      "STR     R0, [SP, #0x30]\n"
      "STR     R0, [SP, #0x34]\n"
      "MOV     R0, #0x10\n"
      "STR     R0, [SP, #0x5C]\n"
      "MOV     R0, #0x800\n"
      "STR     R0, [SP, #0x60]\n"
      "MOV     R0, #0xA0\n"
      "STR     R0, [SP, #0x64]\n"
      "MOV     R0, #0x280\n"
      "STR     R0, [SP, #0x68]\n"
//      "LDR     R1, =0xFF814288 \n" //original
      "LDR     R1, =sub_FF814288_my \n" //patched
      "MOV     R2, #0\n"
      "MOV     R0, SP\n"
      "BL      sub_003F2778 \n" //RAM
      "ADD     SP, SP, #0x74\n"
      "LDR     PC, [SP], #4\n"
	);
}

//** sub_FF814288_my  @ 0xFF814288 

void __attribute__((naked,noinline)) sub_FF814288_my() {
asm volatile (
      "STMFD   SP!, {R4,LR}\n"
      "BL      sub_FF810B50\n"
      "BL      sub_FF815174\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF81439C \n" // "dmSetup"
      "BLLT    _err_init_task \n" 
      "BL      sub_FF813EC0\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF8143A4 \n" // "termDriverInit"
      "BLLT    _err_init_task \n"
      "LDR     R0, =0xFF8143B4 \n" // "/_term"
      "BL      sub_FF813FA8\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF8143BC \n" // "termDeviceCreate"
      "BLLT    _err_init_task \n"
      "LDR     R0, =0xFF8143B4 \n" //  "/_term"
      "BL      sub_FF8129C8\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF8143D0 \n" // "stdioSetup"
      "BLLT    _err_init_task \n"
      "BL      sub_FF814B10\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF8143DC \n" // "stdlibSetup"
      "BLLT    _err_init_task \n"
      "BL      sub_FF8116C8\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF8143E8 \n" // "armlib_setup"
      "BLLT    _err_init_task \n"
      "LDMFD   SP!, {R4,LR}\n"
//      "B       sub_FF81A6A8 \n" //original
      "B       sub_FF81A6A8_my \n" //patched
	);
}


//** sub_FF81A6A8_my  @ 0xFF81A6A8 

void __attribute__((naked,noinline)) sub_FF81A6A8_my() {
asm volatile (
      "STMFD   SP!, {R4,LR}\n"
      "BL      sub_FF82EB0C\n"
//      "BL      loc_FF81A6BC \n" // original taskcreate_Startup
      "BL      taskcreate_Startup_my \n" //patched taskcreate_Startup
      "MOV     R0, #0\n"
      "LDMFD   SP!, {R4,PC}\n"
	);
}

//** taskcreate_Startup_my  @ 0xFF81A6BC 

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
      "STMFD   SP!, {R3-R7,LR}\n"
      "BL      sub_FF835B90\n"
      "LDR     R6, =0xC0220000\n"
      "MOVS    R4, R0\n"
      "MOV     R5, #1\n"
      "BNE     loc_FF81A70C\n"
      "BL      sub_FF830568\n"
      "CMP     R0, #0\n"
      "BEQ     loc_FF81A70C\n"
      "LDR     R0, [R6, #0xFC]\n"
      "BIC     R1, R5, R0\n"
      "LDR     R0, [R6, #0xF8]\n"
      "BIC     R0, R5, R0\n"
      "ORRS    R2, R0, R1\n"
      "BNE     loc_FF81A71C\n"
      "BL      sub_FF82E1C8\n"
      "MOV     R0, #0x44\n"
      "STR     R0, [R6, #0x12C]\n"
      "BL      sub_FF82E2E4\n"
"loc_FF81A708:\n"
      "B       loc_FF81A708\n"
"loc_FF81A70C:\n"
      "LDR     R0, [R6, #0xF8]\n"
      "LDR     R1, [R6, #0xFC]\n"
      "BIC     R0, R5, R0\n"
      "BIC     R1, R5, R1\n"
"loc_FF81A71C:\n"
      "MOV     R3, #0\n"
      "MOV     R2, R4\n"
//      "BL      sub_FF82EB14 \n" // StartUp mode detection. We must remove this for power-on mode handling to work
      "BL      sub_FF82EB10\n"
      "BL      sub_003F77E0 \n" //RAM
      "LDR     R1, =0x34E000\n"
      "MOV     R0, #0\n"
      "BL      sub_FF8341C8\n"
      "BL      sub_003F79F8 \n" //RAM
      "MOV     R3, #0\n"
      "STR     R3, [SP]\n"
//      "LDR     R3, =0xFF81A638 \n" //original
      "LDR     R3, =task_Startup_my \n" //patched
      "MOV     R2, #0\n"
      "MOV     R1, #0x19\n"
      "LDR     R0, =0xFF81A770\n"
      "BL      _CreateTask \n"
      "MOV     R0, #0\n"
      "LDMFD   SP!, {R3-R7,PC}\n"
	);
}


//** task_Startup_my  @ 0xFF81A638 

void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
      "STMFD   SP!, {R4,LR}\n"
      "BL      sub_FF8148C8\n"
      "BL      sub_FF82FC34\n"
      "BL      sub_FF82DE60\n"
      "BL      sub_FF835BD8\n"
      "BL      sub_FF835DC4\n"
      "BL      sub_FF82CC5C\n"
      "BL      sub_FF82D824\n"
//      "BL      sub_FF835C6C \n" //disable Diskboot.bin
      "BL      sub_FF835F44\n"
      "BL      sub_FF836110\n"
      "BL      sub_FF835F08\n"
      "BL      sub_FF835DF4\n"
      "BL      sub_FF8340FC\n"
      "BL      sub_FF836118\n"
      "BL     CreateTask_spytask \n"		//added to create the Spytask
//      "BL      sub_FF82E9B0 \n" //original taskcreate_PhySw()
      "BL     taskcreatePhySw_my \n"		// patched taskcreate_PhySw()
      "BL      sub_FF832390\n"
      "BL      sub_FF836130\n"
      "BL      sub_FF82B9D8\n"
      "BL      sub_FF82C520\n"
      "BL      sub_FF83594C\n"
      "BL      sub_FF82CB4C\n"
      "BL      sub_FF82C4BC\n"
      "BL      sub_FF835F34\n"
      "BL      sub_FF836C88\n"
      "BL      sub_FF82C480\n"
      "LDMFD   SP!, {R4,LR}\n"
      "B       sub_FF8149E8\n"
	);
}


//** taskcreatePhySw_my  @ 0xFF82E9B0 

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
      "STMFD   SP!, {R3-R5,LR}\n"
      "LDR     R4, =0x1C18\n"
      "LDR     R0, [R4, #4]\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF82E9E4\n"
      "MOV     R3, #0\n"
      "STR     R3, [SP]\n"
//      "LDR     R3, =0xFF82E97C \n"
      "LDR     R3, =mykbd_task \n" //patched  task_PhySw
//      "MOV     R2, #0x800 \n"
      "MOV     R2, #0x2000 \n" // stack size for new task_PhySw so we don't have to do stack switch
      "MOV     R1, #0x17\n"
      "LDR     R0, =0xFF82EC0C\n"
      "BL      sub_003F7A50\n"
      "STR     R0, [R4, #4]\n"
"loc_FF82E9E4:\n"
      "BL      sub_FF880638\n"
      "BL      sub_FF8304B8\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF82EA00\n"
      "LDR     R1, =0x31BCC\n"
      "MOV     R0, #0\n"
      "BL      sub_FF8805A8\n"
"loc_FF82EA00:\n"
      "LDMFD   SP!, {R3-R5,PC}\n"
	);
}

void CreateTask_spytask() {

        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);                        
};

//** init_file_modules_task  @ 0xFF88A668 

void __attribute__((naked,noinline)) init_file_modules_task(  ) { 
asm volatile (
      "STMFD   SP!, {R4-R6,LR}\n"
      "BL      sub_FF882BA4\n"
      "LDR     R5, =0x5006\n"
      "MOVS    R4, R0\n"
      "MOVNE   R1, #0\n"
      "MOVNE   R0, R5\n"
      "BLNE    _PostLogicalEventToUI \n"
      "BL      sub_FF882BD0\n"
      "BL	   core_spytask_can_start \n" //added CHDK: Set "it's-safe-to-start"-Flag for spytask
      "CMP     R4, #0\n"
      "LDMNEFD SP!, {R4-R6,PC}\n"
      "MOV     R0, R5\n"
      "LDMFD   SP!, {R4-R6,LR}\n"
      "MOV     R1, #0\n"
      "B       _PostLogicalEventToUI \n"
	);
}

#if 0
void __attribute__((naked,noinline)) task_TouchPanel_my(  ) {
asm volatile (
      "    STMFD   SP!, {R3-R7,LR} \n" 
      "    MOV     R0, #0 \n" 
      "    LDR     R1, =0xC0221000 \n" 
      "    MOV     R4, R0 \n" 
      "    STR     R0, [SP] \n" 
      "    MOV     R0, #0xB \n" 
      "    STR     R0, [R1, #0x314] \n" 
      "    MOV     R0, #0x1C \n" 
      "    SUB     R1, R1, #0x1E000 \n" 
      "    STR     R0, [R1, #0x40] \n" 
      "    MOV     R3, #0 \n" 
      "    LDR     R2, =0xFF858DD0 \n" 
      "    MOV     R1, #0x55 \n" 
      "    MOV     R0, R3 \n" 
      "    BL      sub_003F67BC \n" 
      "    BL      sub_FF85966C \n" 
      "    LDR     R5, =0x25A8 \n" 
      "    MOV     R1, #0x10 \n" 
      "    LDR     R0, [R5, #0x20] \n" 
      "    BL      sub_003FACA0 \n" 
      "    MOV     R6, #7 \n" 
"loc_FF859268:\n"
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R2, #0 \n" 
      "    MOV     R1, #0x17 \n" 
      "    BL      sub_003FAAC8 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRNE   R0, =0xFF858E04 \n" 
      "    MOVNE   R1, #0x31C \n" 
      "    BLNE    sub_003F6AFC \n" 
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R1, SP \n" 
      "    BL      sub_003FACD8 \n" 
      "    CMP     R0, #0 \n" 
      "    LDRNE   R1, =0x31D \n" 
      "    LDRNE   R0, =0xFF858E04 \n" 
      "    BLNE    sub_003F6AFC \n" 
      "    LDR     R0, [SP] \n" 
      "    TST     R0, #1 \n" 
      "    BEQ     loc_FF8592E8 \n" 
      "    LDR     R0, [R5, #4] \n" 
      "    CMP     R0, #7 \n" 
      "    BEQ     loc_FF8592C4 \n" 
      "    BL      sub_FF87D9D0 \n" 
      "    STR     R6, [R5, #4] \n" 
"loc_FF8592C4:\n"
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R1, #5 \n" 
      "    BL      sub_003FACA0 \n" 
      "    BL      sub_FF858E2C \n" 
      "    MOV     R4, #0 \n" 
      "    BL      sub_FF85966C \n" 
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R1, #0x80000000 \n" 
      "    BL      sub_003FAC6C \n" 
"loc_FF8592E8:\n"
      "    LDR     R0, [SP] \n" 
      "    TST     R0, #2 \n" 
      "    BEQ     loc_FF859318 \n" 
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R1, #2 \n" 
      "    BL      sub_003FACA0 \n" 
      "    CMP     R4, #0 \n" 
      "    BNE     loc_FF859268 \n" 
      "    LDR     R0, =0xBB8 \n" 
      "    BL      sub_FF858C2C \n" 
      "    MOV     R4, #1 \n" 
      "    BL      sub_FF859798 \n" 
"loc_FF859318:\n"
      "    LDR     R0, [SP] \n" 
      "    TST     R0, #0x10 \n" 
      "    BEQ     loc_FF859360 \n" 
      "    LDR     R0, [R5, #4] \n" 
      "    CMP     R0, #7 \n" 
      "    BEQ     loc_FF859338 \n" 
      "    BL      sub_FF87D9D0 \n" 
      "    STR     R6, [R5, #4] \n" 
"loc_FF859338:\n"
      "    BL      sub_FF85966C \n" 
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R1, #0x14 \n" 
      "    BL      sub_003FACA0 \n" 
      "    CMP     R4, #0 \n" 
      "    BEQ     loc_FF859268 \n" 
      "    BL      sub_FF8591CC_my \n" // ->
      "    LDR     R0, [R5, #0xC] \n" 
      "    CMP     R0, #0 \n" 
      "    BLNE    sub_FF859774 \n" 
"loc_FF859360:\n"
      "    LDR     R0, [SP] \n" 
      "    TST     R0, #4 \n" 
      "    BEQ     loc_FF859268 \n" 
      "    STR     R6, [R5, #4] \n" 
      "    LDR     R0, [R5, #0x20] \n" 
      "    MOV     R1, #4 \n" 
      "    BL      sub_003FACA0 \n" 
      "    CMP     R4, #0 \n" 
      "    BEQ     loc_FF859268 \n" 
      "    BL      sub_FF8591CC_my \n" // ->
      "    LDR     R0, [R5, #0xC] \n" 
      "    CMP     R0, #0 \n" 
      "    BLNE    sub_FF859774 \n" 
      "    B       loc_FF859268 \n" 
    );
}

void __attribute__((naked,noinline)) sub_FF8591CC_my(  ) {
asm volatile (
      "    LDR     R1, =0x25A8 \n" 
      "    LDR     R0, [R1, #0xC] \n" 
      "    CMP     R0, #0 \n" 
      "    BEQ     loc_FF8591F8 \n" 
      "    CMP     R0, #1 \n" 
      "    BEQ     sub_FF858F90_my \n" // ->
      "    CMP     R0, #2 \n" 
      "    BEQ     sub_FF8590B4_my \n" // ->
      "    LDRNE   R1, =0x307 \n" 
      "    LDRNE   R0, =0xFF858E04 \n" 
      "    BNE     sub_003F6AFC \n" 
"loc_FF8591F8:\n"
      "    LDR     R0, =0xC0220000 \n" 
      "    LDR     R0, [R0, #0x2C] \n" 
      "    TST     R0, #1 \n" 
      "    BNE     sub_FF859798 \n" 
      "    MOV     R0, #1 \n" 
      "    STR     R0, [R1, #0xC] \n" 
      "    BX      LR \n" 
    );
}


void __attribute__((naked,noinline)) sub_FF858F90_my(  ) {
asm volatile (
      "    STMFD   SP!, {R3-R7,LR} \n" 
      "    LDR     R6, =0xC0220000 \n" 
      "    LDR     R0, [R6, #0x2C] \n" 
      "    TST     R0, #1 \n" 
      "    BNE     loc_FF8590AC \n" 
      "    LDR     R1, =0x25D4 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_FF858C8C \n" 
      "    LDR     R4, =0x25D4 \n" 
      "    LDR     R5, =0x3FF \n" 
      "    LDRH    R0, [R4, #6] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R2, R5, R0, LSR #5 \n" 
      "    LDRH    R0, [R4, #4] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R1, R5, R0, LSR #5 \n" 
      "    LDRH    R0, [R4, #2] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R0, R5, R0, LSR #5 \n" 
      "    BL      sub_FF858DB4 \n" 
      "    CMP     R0, #0x1F40 \n" 
      "    BGT     loc_FF859058 \n" 
      "    LDR     R0, =0x2710 \n" 
      "    BL      sub_FF858C2C \n" 
      "    LDR     R0, [R6, #0x2C] \n" 
      "    SUB     R6, R4, #0x2C \n" 
      "    TST     R0, #1 \n" 
      "    BNE     loc_FF85905C \n" 
      "    ADD     R1, R4, #0 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_FF858C8C \n" 
      "    LDRH    R0, [R4, #6] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R2, R5, R0, LSR #5 \n" 
      "    LDRH    R0, [R4, #4] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R1, R5, R0, LSR #5 \n" 
      "    LDRH    R0, [R4, #2] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R0, R5, R0, LSR #5 \n" 
      "    BL      sub_FF858DB4 \n" 
      "    CMP     R0, #0x1F40 \n" 
      "    BGT     loc_FF859058 \n" 
      "    BL      sub_FF858E74_my \n" // ->
      "    MOV     R0, #3 \n" 
      "    STR     R0, [R6, #0x10] \n" 
      "    MOV     R0, #2 \n" 
      "    STR     R0, [R6, #0xC] \n" 
      "    MVN     R0, #0x8000 \n" 
      "    STRH    R0, [R4] \n" 
"loc_FF859058:\n"
      "    LDMFD   SP!, {R3-R7,PC} \n" 
"loc_FF85905C:\n"
      "    LDR     R0, [R6, #0x14] \n" 
      "    CMP     R0, #0 \n" 
      "    LDRNE   R0, =0xFF8591C4 \n" 
      "    BLNE    sub_FF8117C8 \n" 
      "    LDRH    R0, [R4, #6] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R3, R5, R0, LSR #5 \n" 
      "    STR     R3, [SP] \n" 
      "    LDRH    R0, [R4, #4] \n" 
      "    LDR     R12, [R6, #0x18] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R3, R5, R0, LSR #5 \n" 
      "    LDRH    R0, [R4, #2] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R2, R5, R0, LSR #5 \n" 
      "    LDRH    R0, [R4] \n" 
      "    BIC     R0, R0, #0x8000 \n" 
      "    EOR     R1, R5, R0, LSR #5 \n" 
      "    MOV     R0, #0 \n" 
      "    BLX     R12 \n" 
"loc_FF8590AC:\n"
      "    BL      sub_FF858E2C \n" 
      "    LDMFD   SP!, {R3-R7,PC} \n" 
    );
}


void __attribute__((naked,noinline)) sub_FF8590B4_my(  ) {
asm volatile (
"loc_FF8590B4:\n"
      "    STMFD   SP!, {R3-R9,LR} \n" 
      "    LDR     R7, =0xC0220000 \n" 
      "    LDR     R0, [R7, #0x2C] \n" 
      "    LDR     R5, =0x25A8 \n" 
      "    TST     R0, #1 \n" 
      "    LDR     R0, [R5, #0x10] \n" 
      "    LDR     R6, =0x2710 \n" 
      "    SUB     R0, R0, #1 \n" 
      "    BEQ     loc_FF8590EC \n" 
      "    CMP     R0, #0 \n" 
      "    STR     R0, [R5, #0x10] \n" 
      "    LDMEQFD SP!, {R3-R9,LR} \n" 
      "    BEQ     sub_FF858E2C \n" 
      "    B       loc_FF859110 \n" 
"loc_FF8590EC:\n"
      "    LDR     R4, =0x25D4 \n" 
      "    LDR     R8, =0x7FFF \n" 
      "    MOV     R1, #3 \n" 
      "    CMP     R0, #2 \n" 
      "    STR     R1, [R5, #0x10] \n" 
      "    BCS     loc_FF85911C \n" 
      "    LDRH    R0, [R4] \n" 
      "    CMP     R0, R8 \n" 
      "    BNE     loc_FF8591A0 \n" 
"loc_FF859110:\n"
      "    MOV     R0, R6 \n" 
      "    LDMFD   SP!, {R3-R9,LR} \n" 
      "    B       sub_FF858C2C \n" 
"loc_FF85911C:\n"
      "    LDR     R1, =0x25D4 \n" 
      "    MOV     R0, #0 \n" 
      "    BL      sub_FF858C8C \n" 
      "    MOV     R0, R6 \n" 
      "    BL      sub_FF858C2C \n" 
      "    LDR     R0, [R7, #0x2C] \n" 
      "    TST     R0, #1 \n" 
      "    BEQ     loc_FF8591A0 \n" 
      "    LDR     R0, [R5, #0x14] \n" 
      "    CMP     R0, #0 \n" 
      "    LDRNE   R0, =0xFF8591C4 \n" 
      "    BLNE    sub_FF8117C8 \n" 
      "    LDRH    R0, [R4, #6] \n" 
      "    BIC     R1, R0, #0x8000 \n" 
      "    LDR     R0, =0x3FF \n" 
      "    EOR     R3, R0, R1, LSR #5 \n" 
      "    STR     R3, [SP] \n" 
      "    LDRH    R1, [R4, #4] \n" 
      "    LDR     R12, [R5, #0x18] \n" 
      "    BIC     R1, R1, #0x8000 \n" 
      "    EOR     R3, R0, R1, LSR #5 \n" 
      "    LDRH    R1, [R4, #2] \n" 
      "    BIC     R1, R1, #0x8000 \n" 
      "    EOR     R2, R0, R1, LSR #5 \n" 
      "    LDRH    R1, [R4] \n" 
      "    BIC     R1, R1, #0x8000 \n" 
      "    EOR     R1, R0, R1, LSR #5 \n" 
      "    MOV     R0, #0 \n" 
      "    BLX     R12 \n" 
      "    LDR     R0, [R5, #0x10] \n" 
      "    SUB     R0, R0, #1 \n" 
      "    STR     R0, [R5, #0x10] \n" 
      "    LDMFD   SP!, {R3-R9,PC} \n" 
"loc_FF8591A0:\n"
      "    BL      sub_FF858E74_my \n" // ->
      "    STRH    R8, [R4] \n" 
      "    LDMFD   SP!, {R3-R9,PC} \n" 
    );
}

void __attribute__((naked,noinline)) sub_FF858E74_my(  ) {
asm volatile (
      "    STMFD   SP!, {R4,R5,LR} \n"
      "    BL      chdk_process_touch \n"
      "    LDMFD   SP!, {R4,R5,LR} \n"
      "    CMP     R0, #0 \n"
      "    BXNE    LR \n"
      "    LDR     PC, =0xFF858E74 \n"  // Continue in firmware
);
}
#endif
