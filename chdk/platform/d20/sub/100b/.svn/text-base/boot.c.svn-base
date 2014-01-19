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
extern void task_FileWrite();

void taskHook(context_t **context) {
    task_t *tcb=(task_t*)((char*)context-offsetof(task_t, context));

	if(tcb->entry == (void*)task_PhySw)            tcb->entry = (void*)mykbd_task;
    if(tcb->entry == (void*)task_CaptSeq)           tcb->entry = (void*)capt_seq_task;
    if(tcb->entry == (void*)task_InitFileModules)   tcb->entry = (void*)init_file_modules_task;
    if(tcb->entry == (void*)task_MovieRecord)       tcb->entry = (void*)movie_record_task;
    if(tcb->entry == (void*)task_ExpDrv)            tcb->entry = (void*)exp_drv_task;
    if(tcb->entry == (void*)task_FileWrite)         tcb->entry = (void*)filewritetask;
}

//** boot  @ 0xFF00000C

void __attribute__((naked,noinline)) boot(  ) { 
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
      "MOV     R0, #0x35\n"
      "MCR     p15, 0, R0, c6, c2\n"
      "MOV     R0, #0x40000035\n"
      "MCR     p15, 0, R0, c6, c3\n"
      "MOV     R0, #0x80000017\n"
      "MCR     p15, 0, R0, c6, c4\n"
      "LDR     R0, =0xFF00002F\n"
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
      "LDR     R0, =0xFF4ACDBC\n"
      "LDR     R1, =0x471000\n"
      "LDR     R3, =0x48078C\n"
"loc_FF00013C:\n"
      "CMP     R1, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF00013C\n"
      "LDR     R0, =0xFF49EA20\n"
      "LDR     R1, =0x1900\n"
      "LDR     R3, =0xFC9C\n"
"loc_FF000158:\n"
      "CMP     R1, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF000158\n"
      "LDR     R1, =0x1716E8\n" //MEMISOSTART
      "MOV     R2, #0\n"
"loc_FF000170:\n"
      "CMP     R3, R1\n"
      "STRCC   R2, [R3], #4\n"
      "BCC     loc_FF000170\n"
//      "B       sub_FF000380\n" //original
      "B       sub_FF000380_my\n" //patched
	);
}

//** sub_FF000380_my  @ 0xFF000380 

void __attribute__((naked,noinline)) sub_FF000380_my() {

    *(int*)0x1938=(int)taskHook;            
    *(int*)0x193C=(int)taskHook;

    // Power Button detection (short press = playback mode, long press = record mode) 
    // C02200F8  d20.100b loc_ff00a6ec : C0220000 (@ff00a6f4) + 0x12C (@ff00a73c)
    // 0x262C    d20.100b loc_ff04bf70 : called by sub_FF01E5B8
    if ((*(int*) 0xC022012C) & 0x800000)          // look at power-on switch
            *(int*)(0x262C+4) = 0x200000;         // start in play mode
    else
            *(int*)(0x262C+4) = 0x100000;         // start in rec mode

asm volatile (
      "LDR     R0, =0xFF0003F8\n"
      "MOV     R1, #0\n"
      "LDR     R3, =0xFF000430\n"
"loc_FF00038C:\n"
      "CMP     R0, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF00038C\n"
      "LDR     R0, =0xFF000430\n"
      "MOV     R1, #0x4B0\n"
      "LDR     R3, =0xFF000644\n"
"loc_FF0003A8:\n"
      "CMP     R0, R3\n"
      "LDRCC   R2, [R0], #4\n"
      "STRCC   R2, [R1], #4\n"
      "BCC     loc_FF0003A8\n"
      "MOV     R0, #0xD2\n"
      "MSR     CPSR_cxsf, R0\n"
      "MOV     SP, #0x1000\n"
      "MOV     R0, #0xD3\n"
      "MSR     CPSR_cxsf, R0\n"
      "MOV     SP, #0x1000\n"
      "LDR     R0, =0x6C4\n"
      "LDR     R2, =0xEEEEEEEE\n"
      "MOV     R3, #0x1000\n"
"loc_FF0003DC:\n"
      "CMP     R0, R3\n"
      "STRCC   R2, [R0], #4\n"
      "BCC     loc_FF0003DC\n"
//      "BL      sub_FF0011D8\n"  //original
      "BL      sub_FF0011D8_my\n" //patched
	);
}

//** sub_FF0011D8_my  @ 0xFF0011D8

void __attribute__((naked,noinline)) sub_FF0011D8_my() {
asm volatile (
      "STR     LR, [SP, #-4]!\n"
      "SUB     SP, SP, #0x74\n"
      "MOV     R1, #0x74\n"
      "MOV     R0, SP\n"
      "BL      sub_0047C448\n"
      "MOV     R0, #0x57000\n"
      "STR     R0, [SP, #4]\n"
//PATCH BEGIN
#if defined(CHDK_NOT_IN_CANON_HEAP)
      "LDR     R0, =0x1716E8\n" // MEMISOSTART: Use original heap offset since CHDK is loaded in high memory 
#else
      "LDR     R0, =new_sa\n"   //otherwise use patched value
      "LDR     R0, [R0]\n"
#endif
//PATCH END
      "LDR     R2, =0x36D440\n"
      "STR     R0, [SP, #8]\n"
      "SUB     R0, R2, R0\n"
      "STR     R0, [SP, #0xC]\n"
      "MOV     R0, #0x22\n"
      "STR     R0, [SP, #0x18]\n"
      "MOV     R0, #0x7C\n"
      "STR     R0, [SP, #0x1C]\n"
      "LDR     R1, =0x375C00\n"
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
//      "LDR     R1, =0xFF004288\n"    //original
      "LDR     R1, =sub_FF004288_my\n" //patched
      "MOV     R2, #0\n"
      "MOV     R0, SP\n"
      "BL      sub_00472778\n"
      "ADD     SP, SP, #0x74\n"
      "LDR     PC, [SP], #4\n"
	);
}

//** sub_FF004288_my  @ 0xFF004288

void __attribute__((naked,noinline)) sub_FF004288_my() {
asm volatile (
      "STMFD   SP!, {R4,LR}\n"
      "BL      sub_FF000B50\n"
      "BL      sub_FF005174\n"       // BL dmSetup
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF00439C\n"    // "dmSetup"
      "BLLT    _err_init_task\n"
      "BL      sub_FF003EC0\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF0043A4\n" // "termDriverInit"
      "BLLT    _err_init_task\n"
      "LDR     R0, =0xFF0043B4\n" // "/_term"
      "BL      sub_FF003FA8\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF0043BC\n" // "termDeviceCreate"
      "BLLT    _err_init_task\n"
      "LDR     R0, =0xFF0043B4\n" // "/_term"
      "BL      sub_FF0029C8\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF0043D0\n" // "stdioSetup"
      "BLLT    _err_init_task\n"
      "BL      sub_FF004B10\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF0043DC\n" // "stdlibSetup"
      "BLLT    _err_init_task\n"
      "BL      sub_FF0016C8\n"
      "CMP     R0, #0\n"
      "LDRLT   R0, =0xFF0043E8\n" // "armlib_setup"
      "BLLT    _err_init_task\n"
      "LDMFD   SP!, {R4,LR}\n"
//      "B       sub_FF00A6BC\n" //original
      "B       taskcreate_Startup_my\n" //patch
	);
}

//** taskcreate_Startup_my  @ 0xFF00A6BC 

void __attribute__((naked,noinline)) taskcreate_Startup_my() {
asm volatile (
      "STMFD   SP!, {R3,LR}\n"
      "BL      sub_004777E0\n"
      "BL      sub_004779F8\n"
      "MOV     R3, #0\n"
      "STR     R3, [SP]\n"
//      "LDR     R3, =0xFF00A694\n"    //original
      "LDR     R3, =sub_FF00A694_my\n" //patched
      "MOV     R2, #0x200\n"
      "MOV     R1, #0x19\n"
      "LDR     R0, =0xFF00A798\n"
      "BL      _CreateTask\n"
      "MOV     R0, #0\n"
      "LDMFD   SP!, {R3,PC}\n"
	);
}

//** sub_FF00A694_my  @ 0xFF00A694 

void __attribute__((naked,noinline)) sub_FF00A694_my() {
asm volatile (
      "STMFD   SP!, {R4,LR}\n"
      "BL      sub_FF01E5B0\n"
      "BL      sub_FF01F840\n"
      "BL      sub_FF01D43C\n"
      "BL      sub_FF025FF8\n"
      "BL      sub_FF01E9F4\n"
      "BL      sub_FF01DB08\n"
      "BL      sub_FF01CBF0\n"
      "LDMFD   SP!, {R4,LR}\n"
//      "B       sub_FF00A6EC\n"  //original
      "B       sub_FF00A6EC_my\n" //patched
	);
}


//** sub_FF00A6EC_my  @ 0xFF00A6EC 

void __attribute__((naked,noinline)) sub_FF00A6EC_my() {
asm volatile (
      "STMFD   SP!, {R3-R7,LR}\n"
      "BL      sub_FF025D94\n"
      "LDR     R6, =0xC0220000\n"
      "MOVS    R4, R0\n"
      "MOV     R5, #1\n"
      "BNE     loc_FF00A73C\n"
      "BL      sub_FF020174\n"
      "CMP     R0, #0\n"
      "BEQ     loc_FF00A73C\n"
      "LDR     R0, [R6, #0x128]\n"
      "BIC     R1, R5, R0\n"
      "LDR     R0, [R6, #0x12C]\n"
      "BIC     R0, R5, R0\n"
      "ORRS    R2, R0, R1\n"
      "BNE     loc_FF00A74C\n"
      "BL      sub_FF01D7EC\n"
      "MOV     R0, #0x44\n"
      "STR     R0, [R6, #0x1C]\n"
      "BL      sub_FF01D9DC\n"
"loc_FF00A738:\n"
      "B       loc_FF00A738\n"
"loc_FF00A73C:\n"
      "LDR     R0, [R6, #0x12C]\n"
      "LDR     R1, [R6, #0x128]\n"
      "BIC     R0, R5, R0\n"
      "BIC     R1, R5, R1\n"
"loc_FF00A74C:\n"
      "MOV     R3, #0\n"
      "MOV     R2, R4\n"
//      "BL      sub_FF01E5B8\n" We must remove this for power-on mode handling to work
      "BL      sub_FF01E5B4\n"
      "BL      sub_004777E0\n"
      "LDR     R1, =0x3CE000\n"
      "MOV     R0, #0\n"
      "BL      sub_FF024374\n"
      "BL      sub_004779F8\n"
      "MOV     R3, #0\n"
      "STR     R3, [SP]\n"
//      "LDR     R3, =0xFF00A638\n" //original
      "LDR     R3, =task_Startup_my \n" //patch
      "MOV     R2, #0\n"
      "MOV     R1, #0x19\n"
      "LDR     R0, =0xFF00A7AC\n"
      "BL      _CreateTask\n"
      "MOV     R0, #0\n"
      "LDMFD   SP!, {R3-R7,PC}\n"
	);
}


//** task_Startup_my  @ 0xFF00A638

void __attribute__((naked,noinline)) task_Startup_my() {
asm volatile (
      "STMFD   SP!, {R4,LR}\n"
      "BL      sub_FF0048C8\n"
      "BL      sub_FF025E0C\n"
//      "BL      sub_FF025EA0\n"  //Disable diskboot.bin??
      "BL      sub_FF026154\n"
      "BL      sub_FF026320\n"
      "BL      sub_FF026148\n"
      "BL      sub_FF026028\n"
      "BL      sub_FF0242A8\n"
      "BL      sub_FF026328\n"
      "BL      CreateTask_spytask\n" //patch
//      "BL      sub_FF01E454\n"  //physw
      "BL      taskcreatePhySw_my\n" //patch
      "BL      sub_FF021FD8\n"
      "BL      sub_FF026340\n"
      "BL      sub_FF01BA14\n"
      "BL      sub_FF01C55C\n"
      "BL      sub_FF025B04\n"
      "BL      sub_FF01CB94\n"
      "BL      sub_FF01C4F8\n"
      "BL      sub_FF02614C\n"
      "BL      sub_FF026FF8\n"
      "BL      sub_FF01C4BC\n"
      "LDMFD   SP!, {R4,LR}\n"
      "B       sub_FF0049E8\n"
	);
}

//** taskcreatePhySw_my  @ 0xFF01E454

void __attribute__((naked,noinline)) taskcreatePhySw_my() {
asm volatile (
      "STMFD   SP!, {R3-R5,LR}\n"
      "LDR     R4, =0x1C30\n"
      "LDR     R0, [R4, #4]\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF01E488\n"
      "MOV     R3, #0\n"
      "STR     R3, [SP]\n"
//      "LDR     R3, =0xFF01E420\n" //original
      "LDR     R3, =task_PhySw\n"    //patched
//      "MOV     R2, #0x800\n"      //original
      "MOV     R2, #0x2000\n"        // stack size for new task_PhySw so we don't have to do stack switch
      "MOV     R1, #0x17\n"
      "LDR     R0, =0xFF01E6B0\n"
      "BL      sub_00477A50\n"
      "STR     R0, [R4, #4]\n"
"loc_FF01E488:\n"
      "BL      sub_FF078570\n"
      "BL      sub_FF0200C4\n"
      "CMP     R0, #0\n"
      "BNE     loc_FF01E4A4\n"
      "LDR     R1, =0x33DE0\n"
      "MOV     R0, #0\n"
      "BL      sub_FF0784E0\n"
"loc_FF01E4A4:\n"
      "LDMFD   SP!, {R3-R5,PC}\n"
	);
}

void CreateTask_spytask() {
    _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);
};


//** init_file_modules_task  @ 0xFF083918 

void __attribute__((naked,noinline)) init_file_modules_task(  ) { 
asm volatile (
      "STMFD   SP!, {R4-R6,LR}\n"
      "BL      sub_FF07AB30\n"
      "LDR     R5, =0x5006\n"
      "MOVS    R4, R0\n"
      "MOVNE   R1, #0\n"
      "MOVNE   R0, R5\n"
      "BLNE    _PostLogicalEventToUI\n"
      "BL      sub_FF07AB64\n"
      "BL      core_spytask_can_start\n" //Safe to start
      "CMP     R4, #0\n"
      "LDMNEFD SP!, {R4-R6,PC}\n"
      "MOV     R0, R5\n"
      "LDMFD   SP!, {R4-R6,LR}\n"
      "MOV     R1, #0\n"
      "B       _PostLogicalEventToUI\n"
	);
}
