#include "lolevel.h"
#include "platform.h"
#include "core.h"

const char * const new_sa = &_end;

/* Ours stuff */
extern long wrs_kernel_bss_start;
extern long wrs_kernel_bss_end;

// Forward declarations
void CreateTask_PhySw();
void CreateTask_spytask();

void task_CaptSeqTask_my();
void task_InitFileModules_my();
void MovieRecord_Task_my();

void boot();

void taskCreateHook(int *p) { 
 p-=16;
 if (p[0]==0xFFC49B38)  p[0]=(int)task_CaptSeqTask_my;		//done
 if (p[0]==0xFFC118BC)  p[0]=(int)mykbd_task;		//done
 if (p[0]==0xFFC5FEA0)  p[0]=(int)task_InitFileModules_my;		//done
 if (p[0]==0xFFC46678)  p[0]=(int)MovieRecord_Task_my;		//done
 if (p[0]==0xFFC91194)  p[0]=(int)exp_drv_task; //done
}

void taskCreateHook2(int *p) { 
 p-=16;
 if (p[0]==0xFFC5FEA0)  p[0]=(int)task_InitFileModules_my;		//done
}

#define DEBUG_LED 0xC02200C4

void boot() { //#fs
    long *canon_data_src = (void*)0xFFEBFB4C;
    long *canon_data_dst = (void*)0x1900;
    long canon_data_len = 0xD700 - 0x1900;		// data_end - data_start
    long *canon_bss_start = (void*)0xD700;		// just after data
    long canon_bss_len = 0xA47E0 - 0xD700;

    long i;


    // Code taken from VxWorks CHDK. Changes CPU speed?
    asm volatile (
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

/*    asm volatile (
	"MRC     p15, 0, R0,c1,c0\n"
	"ORR     R0, R0, #0x1000\n"
	"BIC     R0, R0, #4\n"
	"ORR     R0, R0, #1\n"
	"MCR     p15, 0, R0,c1,c0\n"
    :::"r0");
*/

    *(int*)0x1930=(int)taskCreateHook;
    *(int*)0x1934=(int)taskCreateHook;
    *(int*)0x1938=(int)taskCreateHook2;

    // jump to init-sequence that follows the data-copy-routine
    asm volatile ("B      sub_FFC001a4_my\n");
}; //#fe

// init
void __attribute__((naked,noinline)) sub_FFC001a4_my() { //#fs
        asm volatile (
                "LDR     R0, =0xFFC0021C\n"
                "MOV     R1, #0\n"
                "LDR     R3, =0xFFC00254\n"

        "loc_FFC001B0:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001B0\n"

                "LDR     R0, =0xFFC00254\n"
                "MOV     R1, #0x4B0\n"
                "LDR     R3, =0xFFC00468\n"

        "loc_FFC001CC:\n"
                "CMP     R0, R3\n"
                "LDRCC   R2, [R0],#4\n"
                "STRCC   R2, [R1],#4\n"
                "BCC     loc_FFC001CC\n"
                "MOV     R0, #0xD2\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "MOV     R0, #0xD3\n"
                "MSR     CPSR_cxsf, R0\n"
                "MOV     SP, #0x1000\n"
                "LDR     R0, =0x6C4\n"
                "LDR     R2, =0xEEEEEEEE\n"
                "MOV     R3, #0x1000\n"

        "loc_FFC00200:\n"
                "CMP     R0, R3\n"
                "STRCC   R2, [R0],#4\n"
                "BCC     loc_FFC00200\n"

                //"BL      sub_FFC00FA0\n"
                "BL      sub_FFC00FA0_my\n"
        );
} //#fe

void __attribute__((naked,noinline)) sub_FFC00FA0_my() { //#fs
        asm volatile (
              //"STR     LR, [SP,#0xFFFFFFFC]!\n"
              "STR     LR, [SP,#-4]!\n"         // inspired by original CHDK-code
              "SUB     SP, SP, #0x74\n"
              "MOV     R0, SP\n"
              "MOV     R1, #0x74\n"
              "BL      sub_FFE58D68\n"
              "MOV     R0, #0x53000\n"
              "STR     R0, [SP,#0x74-0x70]\n"
#if defined(CHDK_NOT_IN_CANON_HEAP)
              "LDR     R0, =0xA47E0\n" // use original heap offset since CHDK is loaded in high memory
              //"LDR     R0, =0xE47E0\n" // 0xa47e0 + 0x40000, note: 0x20000 *should* have been enough, but our code was overwritten...
                                       // ...thus we push the memory pool a little more up (0x30000 = 192k)
#else
              "LDR     R0, =new_sa\n"
              "LDR     R0, [R0]\n"
#endif
              "LDR     R2, =0x279C00\n"
              "LDR     R1, =0x272968\n"
              "STR     R0, [SP,#0x74-0x6C]\n"
              "SUB     R0, R1, R0\n"
              "ADD     R3, SP, #0x74-0x68\n"
              "STR     R2, [SP,#0x74-0x74]\n"
              "STMIA   R3, {R0-R2}\n"
              "MOV     R0, #0x22\n"
              "STR     R0, [SP,#0x74-0x5C]\n"
              "MOV     R0, #0x68\n"
              "STR     R0, [SP,#0x74-0x58]\n"
              "LDR     R0, =0x19B\n"
              "MOV     R1, #0x64\n"
              //"STRD     R0, [SP,#0x74-0x54]\n"		// "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x54]\n"		// split in two single-word STRs
              "STR      R1, [SP,#0x74-0x50]\n"

              "MOV     R0, #0x78\n"
              //"STRD     R0, [SP,#0x74-0x4C]\n"		// "strd not supported by cpu" claims gcc
              "STR      R0, [SP,#0x74-0x4C]\n"		// split in two single-word STRs
              "STR      R1, [SP,#0x74-0x48]\n"

              "MOV     R0, #0\n"
              "STR     R0, [SP,#0x74-0x44]\n"
              "STR     R0, [SP,#0x74-0x40]\n"
              "MOV     R0, #0x10\n"
              "STR     R0, [SP,#0x74-0x18]\n"
              "MOV     R0, #0x800\n"
              "STR     R0, [SP,#0x74-0x14]\n"
              "MOV     R0, #0xA0\n"
              "STR     R0, [SP,#0x74-0x10]\n"
              "MOV     R0, #0x280\n"
              "STR     R0, [SP,#0x74-0x0C]\n"

              //"LDR     R1, =0xFFC04DA4\n"		// uHwSetup = 0xFFC04DA4
              "LDR     R1, =uHwSetup_my\n"		// followup to own function

              "MOV     R0, SP\n"
              "MOV     R2, #0\n"
              "BL      sub_FFC02D58\n"
              "ADD     SP, SP, #0x74\n"
              "LDR     PC, [SP],#4\n"
        );
}; //#fe

void __attribute__((naked,noinline)) uHwSetup_my() { //#fs
        asm volatile (
              "STMFD   SP!, {R4,LR}\n"
              "BL      sub_FFC0094C\n"
              "BL      sub_FFC0972C\n"		// _dmSetup // OK!
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xffc04eb8\n"		// FFC04EB8 aDmsetup // OK!
              "BLLT    sub_FFC04E98\n"		// FFC04E98  _err_init_task // OK!
              "BL      sub_FFC049C8\n"		// _termDriverInit // OK!
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EC0\n"		// aTermdriverinit // OK!
              "BLLT    sub_FFC04E98\n"		// FFC04E98  _err_init_task // OK!
              "LDR     R0, =0xFFc04ED0\n"		// a_term // OK!
              "BL      sub_FFC04AB4\n"		// _termDeviceCreate // OK!
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04ED8\n"		// aTermdevicecrea // OK!
              "BLLT    sub_FFC04E98\n"		// FFC04E98  _err_init_task // OK!
              "LDR     R0, =0xFFc04ED0\n"		// a_term // OK!
              "BL      sub_FFc03564\n"		// _stdioSetup // OK!
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EEC\n"		// aStdiosetup // OK!
              "BLLT    sub_FFC04E98\n"		// FFC04E98  _err_init_task // OK!
              "BL      sub_FFc092B4\n"		// _stdlibSetup // OK!
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04EF8\n"		// aStdlibsetup // Corrected! from 0xFFC04EEC
              "BLLT    sub_FFC04E98\n"		// FFC04E98  _err_init_task // OK!
              "BL      sub_FFC014B8\n"		// _armlib_setup // OK!
              "CMP     R0, #0\n"
              "LDRLT   R0, =0xFFC04F04\n"		// aArmlib_setup // OK!
              "BLLT    sub_FFC04E98\n"		// FFC04E98  _err_init_task // OK!
              "LDMFD   SP!, {R4,LR}\n"
              //"B       _CreateTaskStartup\n"		// FFC0CD84
              "B       CreateTask_Startup_my\n"

        );
}; //#fe

void __attribute__((naked,noinline)) CreateTask_Startup_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R3,LR}\n"
                //"BL      j_nullsub_211\n"
                "BL      sub_FFC1979C\n"
                "CMP     R0, #0\n"

                // different from a720!!!
                /*
                "LDREQ   R0, =0xC0220000\n"
                "LDREQ   R1, [R0,#0xB8]\n"
                "TSTEQ   R1, #1\n"
                "BNE     loc_FFC0DD08\n"
                */
                "BNE     loc_FFC0CDB4\n"
                "BL      sub_FFC119D8\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC0CDB4\n"
                "LDR     R1, =0xC0220000\n"

                "MOV     R0, #0x44\n"		// Corrected! from MOV     R1, #0x44
                "STR     R0, [R1,#0x4C]\n"		// Corrected! from STR     R1, [R0,#0x4C]
        "loc_FFC0CDB0:\n"
                "B       loc_FFC0CDB0\n"
        "loc_FFC0CDB4:\n"
                //"BL      j_nullsub_213\n"
                //"BL      j_nullsub_212\n"
                "BL      sub_FFC17B24\n"
                "LDR     R1, =0x2CE000\n" // Different from a720!!! (MOV     R1, #0x300000)
                "MOV     R0, #0\n"

                "BL      sub_FFC17D6C\n"
                "BL      sub_FFC17D18\n"
                "MOV     R3, #0\n"
                "STR     R3, [SP,#8-8]\n"

                //"ADR     R3, sub_FFC0CD28\n"     // Startup
                "LDR     R3, =task_Startup_my\n"      // followup to own function
                "MOV     R2, #0\n"
                "MOV     R1, #0x19\n"
                "LDR     R0, =0xFFC0CDFC\n" // aStartup, 0xFFC0CDFC (ADR     R0, aStartup)
                "BL      sub_FFC0B8E0\n" // CreateTask, 0xFFC0B8E0
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R12,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) task_Startup_my() { //#fs

        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC051BC\n"		// taskcreate_ClockSave
                "BL      sub_FFC12B3C\n"
                "BL      sub_FFC0FE14\n"
                //"BL	 j_nullsub_216\n"		// j_kbd_pwr_on_short does not exist in a580's DryOS version
                "BL      sub_FFC199A4\n"
                //"BL      sub_FFC19864\n"		// StartDiskboot
        );

        CreateTask_spytask();

        asm volatile (
                "BL      sub_FFC19B58\n"
                "BL      sub_FFC199F4\n"

                "BL      sub_FFC17064\n"
                "BL      sub_FFC19B5C\n"
                "BL      sub_FFC118F0\n"		// taskcreate_PhySw - checks buttons and acts accordingly

                "BL      sub_FFC14A34\n"		// task_ShootSeqTask
                "BL      sub_FFC19B74\n"
                //"BL    sub_FFC0FBD8\n"		// nullsub_2
                "BL      sub_FFC10DC4\n"
                "BL      sub_FFC19564\n"		// taskcreate_Bye
                "BL      sub_FFC11420\n"
                "BL      sub_FFC10CC4\n"		// taskcreate_TempCheck
                "BL      sub_FFC1A4C0\n"
                "BL      sub_FFC10C80\n"

                // modification: BL instead of B to last function to control action after its return
                "BL       sub_FFC05070\n"
                "LDMFD   SP!, {R4,PC}\n"		// restore stack to PC instead of LR to return to caller
        );
}; //#fe

void CreateTask_spytask() { //#fs
        _CreateTask("SpyTask", 0x19, 0x2000, core_spytask, 0);

}; //#fe

void __attribute__((naked,noinline)) task_InitFileModules_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "BL      sub_FFC58A28\n"
                "LDR     R5, =0x5006\n"
                "MOVS    R4, R0\n"
                "MOVNE   R1, #0\n"
                "MOVNE   R0, R5\n"
                "BLNE    sub_FFC5BEC4\n"		// PostLogicalEventToUI
                "BL      sub_FFC58A54_my\n"		// Continue to SDHC-hook here!

                "BL      core_spytask_can_start\n"		// CHDK: Set "it's-save-to-start"-Flag for spytask (safe?)

                "CMP     R4, #0\n"
                "MOVEQ   R0, R5\n"
                "LDMEQFD SP!, {R4-R6,LR}\n"
                "MOVEQ   R1, #0\n"
                "BEQ     sub_FFC5BEC4\n"		// PostLogicalEventToUI (cameralog "LogicalEvent...", it's save to run this after spytask has started)
                "LDMFD   SP!, {R4-R6,PC}\n"
         );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC58A54_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4,LR}\n"
                "BL      sub_FFC3D588_my\n"		// Continue to SDHC-hook here
                "LDR     R4, =0x5580\n"
                "LDR     R0, [R4,#4]\n"
                "CMP     R0, #0\n"
                "BNE     loc_FFC58A84\n"
                "BL      sub_FFC66B30\n"
                "BL      sub_FFCDE71C\n"
                "BL      sub_FFC66B30\n"
                "BL      sub_FFC3AF78\n"
                "BL      sub_FFC66B40\n"
                "BL      sub_FFCDE7E8\n"
        "loc_FFC58A84:\n"
                "MOV     R0, #1\n"
                "STR     R0, [R4]\n"
                "LDMFD   SP!, {R4,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3D588_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "MOV     R6, #0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3D048\n"
                "LDR     R4, =0xFE6C\n"
                "MOV     R5, #0\n"
                "LDR     R0, [R4,#0x38]\n"
                "BL      sub_FFC3DA7C\n"
                "CMP     R0, #0\n"
                "LDREQ   R0, =0x2828\n"
                "STREQ   R5, [R0,#0x10]\n"
                "STREQ   R5, [R0,#0x14]\n"
                "STREQ   R5, [R0,#0x18]\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3D088\n"		// uMounter (u=unknown, just to prevent misunderstandings)
                "MOV     R0, R6\n"
                "BL      sub_FFC3D3C4_my\n"		// Continue to SDHC-hook here!
                "MOV     R5, R0\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3D430\n"
                "LDR     R1, [R4,#0x3C]\n"
                "AND     R2, R5, R0\n"
                "CMP     R1, #0\n"
                "MOV     R0, #0\n"
                "MOVEQ   R0, #0x80000001\n"
                "BEQ     loc_FFC3D61C\n"
                "LDR     R3, [R4,#0x2C]\n"
                "CMP     R3, #2\n"
                "MOVEQ   R0, #4\n"
                "CMP     R1, #5\n"
                "ORRNE   R0, R0, #1\n"
                "BICEQ   R0, R0, #1\n"
                "CMP     R2, #0\n"
                "BICEQ   R0, R0, #2\n"
                "ORREQ   R0, R0, #0x80000000\n"
                "BICNE   R0, R0, #0x80000000\n"
                "ORRNE   R0, R0, #2\n"
        "loc_FFC3D61C:\n"
                "STR     R0, [R4,#0x40]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3D3C4_my() { //#fs
        asm volatile (
                "STMFD   SP!, {R4-R6,LR}\n"
                "LDR     R5, =0x2828\n"
                "MOV     R6, R0\n"
                "LDR     R0, [R5,#0x14]\n"
                "CMP     R0, #0\n"
                "MOVNE   R0, #1\n"
                "LDMNEFD SP!, {R4-R6,PC}\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R6\n"
                "LDR     R0, =0xFE6C\n"
                "ADD     R4, R0, R1,LSL#2\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC3D154_my\n"		// Continue to SDHC-hook here!
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "LDR     R0, [R4,#0x38]\n"
                "MOV     R1, R6\n"
                "BL      sub_FFC3D2BC\n"
                "CMP     R0, #0\n"
                "LDMEQFD SP!, {R4-R6,PC}\n"
                "MOV     R0, R6\n"
                "BL      sub_FFC3CC50\n"
                "CMP     R0, #0\n"
                "MOVNE   R1, #1\n"
                "STRNE   R1, [R5,#0x14]\n"
                "LDMFD   SP!, {R4-R6,PC}\n"
        );
}; //#fe

void __attribute__((naked,noinline)) sub_FFC3D154_my() { //#fs  ; Partition table parse takes place here. => SDHC-boot
        asm volatile (
                "STMFD   SP!, {R4-R8,LR}\n"
                "MOV     R8, R0\n"
                "MOV     R0, #0x17\n"
                "MUL     R1, R0, R1\n"
                "LDR     R0, =0xFE6C\n"
                "MOV     R6, #0\n"
                "ADD     R7, R0, R1,LSL#2\n"
                "LDR     R0, [R7,#0x3C]\n"
                "MOV     R5, #0\n"
                "CMP     R0, #6\n"
                "ADDLS   PC, PC, R0,LSL#2\n"
                "B       loc_FFC3D2A0\n"
        "loc_FFC3D184:\n"
                "B       loc_FFC3D1B8\n"
        "loc_FFC3D188:\n"
                "B       loc_FFC3D1A0\n"
        "loc_FFC3D18C:\n"
                "B       loc_FFC3D1A0\n"
        "loc_FFC3D190:\n"
                "B       loc_FFC3D1A0\n"
        "loc_FFC3D194:\n"
                "B       loc_FFC3D1A0\n"
        "loc_FFC3D198:\n"
                "B       loc_FFC3D298\n"
        "loc_FFC3D19C:\n"
                "B       loc_FFC3D1A0\n"
        "loc_FFC3D1A0:\n"
                "MOV     R2, #0\n"
                "MOV     R1, #0x200\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC52BD4\n"
                "MOVS    R4, R0\n"
                "BNE     loc_FFC3D1C0\n"
        "loc_FFC3D1B8:\n"
                "MOV     R0, #0\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        "loc_FFC3D1C0:\n"
                "LDR     R12, [R7,#0x4C]\n"
                "MOV     R3, R4\n"
                "MOV     R2, #1\n"
                "MOV     R1, #0\n"
                "MOV     R0, R8\n"
                
                //"BLX     R12\n"		// !! Workaround !!
                "MOV     LR, PC\n"		// gcc won't compile "BLX R12" nor "BL R12".
                "MOV     PC, R12\n"		// workaround: make your own "BL" and hope we don't need the change to thumb-mode
                
                "CMP     R0, #1\n"
                "BNE     loc_FFC3D1EC\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC52D14\n"
                "B       loc_FFC3D1B8\n"
        
       "loc_FFC3D1EC:\n"
                "MOV     R0, R8\n"
                "BL      sub_FFCFB2F0\n"		// Add FAT32 autodetect-code after this line
                "MOV   R1, R4\n"		//  pointer to MBR in R1
                "BL    mbr_read_dryos\n"		//  total sectors count in R0 before and after call
                
                // Start of DataGhost's FAT32 autodetection code
                // Policy: If there is a partition which has type W95 FAT32, use the first one of those for image storage
                // According to the code below, we can use R1, R2, R3 and R12.
                // LR wasn't really used anywhere but for storing a part of the partition signature. This is the only thing
                // that won't work with an offset, but since we can load from LR+offset into LR, we can use this to do that :)
                "MOV     R12, R4\n"              // Copy the MBR start address so we have something to work with
                "MOV     LR, R4\n"               // Save old offset for MBR signature
                "MOV     R1, #1\n"               // Note the current partition number
                "B       dg_sd_fat32_enter\n"    // We actually need to check the first partition as well, no increments yet!
        "dg_sd_fat32:\n"                         
                "CMP     R1, #4\n"               // Did we already see the 4th partition?
                "BEQ     dg_sd_fat32_end\n"      // Yes, break. We didn't find anything, so don't change anything.
                "ADD     R12, R12, #0x10\n"      // Second partition
                "ADD     R1, R1, #1\n"           // Second partition for the loop
        "dg_sd_fat32_enter:\n"                   
                "LDRB    R2, [R12, #0x1BE]\n"    // Partition status
                "LDRB    R3, [R12, #0x1C2]\n"    // Partition type (FAT32 = 0xB)
                "CMP     R3, #0xB\n"             // Is this a FAT32 partition?
                "CMPNE   R3, #0xC\n"             // Not 0xB, is it 0xC (FAT32 LBA) then?
                "BNE     dg_sd_fat32\n"          // No, it isn't.
                "CMP     R2, #0x00\n"            // It is, check the validity of the partition type
                "CMPNE   R2, #0x80\n"            
                "BNE     dg_sd_fat32\n"          // Invalid, go to next partition
                                                 // This partition is valid, it's the first one, bingo!
                "MOV     R4, R12\n"              // Move the new MBR offset for the partition detection.
                
           "dg_sd_fat32_end:\n"
                // End of DataGhost's FAT32 autodetection code                
                
                "LDRB    R1, [R4,#0x1C9]\n"		// Continue with firmware
                "LDRB    R3, [R4,#0x1C8]\n"
                "LDRB    R12, [R4,#0x1CC]\n"
                "MOV     R1, R1,LSL#24\n"
                "ORR     R1, R1, R3,LSL#16\n"
                "LDRB    R3, [R4,#0x1C7]\n"
                "LDRB    R2, [R4,#0x1BE]\n"
                //"LDRB    LR, [R4,#0x1FF]\n"		// replaced, see below
                "ORR     R1, R1, R3,LSL#8\n"
                "LDRB    R3, [R4,#0x1C6]\n"
                "CMP     R2, #0\n"
                "CMPNE   R2, #0x80\n"
                "ORR     R1, R1, R3\n"
                "LDRB    R3, [R4,#0x1CD]\n"
                "MOV     R3, R3,LSL#24\n"
                "ORR     R3, R3, R12,LSL#16\n"
                "LDRB    R12, [R4,#0x1CB]\n"
                "ORR     R3, R3, R12,LSL#8\n"
                "LDRB    R12, [R4,#0x1CA]\n"
                "ORR     R3, R3, R12\n"
                //"LDRB    R12, [R4,#0x1FE]\n"		// replaced, see below
                
                "LDRB    R12, [LR,#0x1FE]\n"		// New! First MBR signature byte (0x55)
                "LDRB    LR, [LR,#0x1FF]\n"		//      Last MBR signature byte (0xAA)

                "MOV     R4, #0\n"
                "BNE     loc_FFC3D274\n"
                "CMP     R0, R1\n"
                "BCC     loc_FFC3D274\n"
                "ADD     R2, R1, R3\n"
                "CMP     R2, R0\n"
                "CMPLS   R12, #0x55\n"
                "CMPEQ   LR, #0xAA\n"
                "MOVEQ   R6, R1\n"
                "MOVEQ   R5, R3\n"
                "MOVEQ   R4, #1\n"
        "loc_FFC3D274:\n"
                "MOV     R0, #3\n"
                "BL      sub_FFC52D14\n"
                "CMP     R4, #0\n"
                "BNE     loc_FFC3D2AC\n"
                "MOV     R6, #0\n"
                "MOV     R0, R8\n"
                "BL      sub_FFCFB2F0\n"
                "MOV     R5, R0\n"
                "B       loc_FFC3D2AC\n"
        "loc_FFC3D298:\n"
                "MOV     R5, #0x40\n"
                "B       loc_FFC3D2AC\n"
        "loc_FFC3D2A0:\n"        
                "MOV     R1, #0x374\n"
                "LDR     R0, =0xFFC3D148\n"		// Mounter.c
                "BL      sub_FFC0BDB8\n"		// DebugAssert
        "loc_FFC3D2AC:\n"
                "STR     R6, [R7,#0x44]!\n"
                "MOV     R0, #1\n"
                "STR     R5, [R7,#4]\n"
                "LDMFD   SP!, {R4-R8,PC}\n"
        );
}; //#fe
