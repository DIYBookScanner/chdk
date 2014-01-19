// A2100IS 1.00A
/*
###########################################################
###########################################################
#############[ COMPLETED 100% NOT TESTED !! ]##############
###########################################################
###########################################################
*/

/*
ROM:FFC49078                 BL      _sub_FFCFB874__SsPrePreSeq.c__2097152 ; - first routine from chain



// 95% the same for D10: void __attribute__((naked,noinline)) sub_FF934548_my() {
// This one referenced by :
//ROM:FFC49350                 BL      _sub_FFCFC7D4__SsCaptureSeq.c__0 ; LOCATION: SsCaptureSeq.c:0
// which is referenced by original:
//ROM:FFC49034                 BL      sub_FFC492A4

ROM:FFCFC7D4                 STMFD   SP!, {R0-R8,LR}
ROM:FFCFC7D8                 MOV     R4, R0
ROM:FFCFC7DC                 BL      _sub_FFCFD3A8__SsShootEvent.c__60 ; LOCATION: SsShootEvent.c:60
ROM:FFCFC7E0                 MOVL    R1, 0xFFFFFFFF



Hook should be here!!!!
ROM:FFC492A4 sub_FFC492A4:

ROM:FFC49354                 MOV     R5, R0
<<HERE>>>
ROM:FFC49358                 BL      sub_FFC4BBF8
ROM:FFC4935C                 BL      sub_FFC4BC40
ROM:FFC49360                 BL      sub_FFC4BC80

*/


#include "lolevel.h"
#include "platform.h"
#include "core.h"

static long *nrflag = (long*) 0x5B10; 		// A2100 ROM:FFCFC85C                 LDR     R3, =0x5B10

#include "../../../generic/capt_seq.c"

// correct 100%
void __attribute__((naked,noinline)) sub_FFCFC7D4_my() {
asm volatile(
	"STMFD   SP!, {R0-R8,LR}\n"
	"MOV     R4, R0\n"
	"BL      sub_FFCFD3A8\n"//__SsShootEvent.c__60 ; LOCATION: SsShootEvent.c:60\n"
	"MOV     R1, #0xFFFFFFFF\n"
	"BL      sub_FFC51418\n"
	"LDR     R5, =0x5B08\n"
	"LDR     R0, [R5,#0xC]\n"
	"CMP     R0, #0\n"
	"BNE     loc_FFCFC824\n"
	"MOV     R1, #1\n"
	"MOV     R0, #0\n"
	"BL      sub_FFC16C10\n"//__KernelMisc.c__31 ; LOCATION: KernelMisc.c:31\n"
	"STR     R0, [R5,#0xC]\n"
	"MOV     R3, #0\n"
	"STR     R3, [SP]\n"
	"LDR     R3, =0xFFCFC2E0\n"//__SsCaptureSeq.c__155\n"
	"LDR     R0, =0xFFCFCA44\n"// ; "ShutterSoundTask"\n"
	"MOV     R2, #0x400\n"
	"MOV     R1, #0x17\n"
	"BL      sub_FFC16BDC\n" //KernelCreateTask\n"// ; LOCATION: KernelMisc.c:19\n"
"loc_FFCFC824:\n"//                            ; CODE XREF: _sub_FFCFC7D4__SsCaptureSeq.c__0+20j
	"MOV     R2, #4\n"
	"ADD     R1, SP, #8\n"
	"MOV     R0, #0x8A\n"
	"BL      sub_FFC59250\n" //PT_GetPropertyCaseString_0\n"// ; LOCATION: PropertyCase.c:0\n"
	"TST     R0, #1\n"
	"LDRNE   R1, =0x3AE\n"
	"LDRNE   R0, =0xFFCFC54C\n"// ; "SsCaptureSeq.c"\n"
	"BLNE    sub_FFC0B284\n" // DebugAssert\n"
	"LDR     R7, =0x12278\n"
	"LDR     R8, =0x121BC\n"
	"LDRSH   R1, [R7,#0xE]\n"
	"LDR     R0, [R8,#0x84]\n"
	"BL      sub_FFCC34C4\n"
	"BL      sub_FFC32C08\n"//__Thermometer.c__0 ; LOCATION: Thermometer.c:0\n"
	"LDR     R3, =0x5B10\n"
	"STRH    R0, [R4,#0x9C]\n"
	"SUB     R2, R3, #4\n"
	"STRD    R2, [SP]\n"
	"MOV     R1, R0\n"
	"LDRH    R0, [R8,#0x54]\n"
	"LDRSH   R2, [R7,#0xC]\n"
	"SUB     R3, R3, #8\n"
	"BL      sub_FFCFD98C\n"
"	BL      wait_until_remote_button_is_released\n"  // +
"	BL      capt_seq_hook_set_nr\n"                  // +   
	"LDR     PC, =0xFFCFC880\n" // continue on FW\n"

);
}
// correct 100%
void __attribute__((naked,noinline)) sub_FFC492A4_my() {
asm volatile(
	"STMFD   SP!, {R3-R5,LR}\n"
	"LDR     R4, [R0,#0xC]\n"
	"LDR     R0, [R4,#8]\n"
	"ORR     R0, R0, #1\n"
	"STR     R0, [R4,#8]\n"
	"MOV     R0, #2\n"
	"BL      sub_FFC44F9C\n"
	"BL      sub_FFC49814\n"
	"MOV     R0, R4\n"
	"BL      sub_FFC49B4C\n"
	"MOV     R0, R4\n"
	"BL      sub_FFCFB4E4\n"
	"CMP     R0, #0\n"
	"MOV     R0, R4\n"
	"BEQ     loc_FFC492FC\n"
	"BL      sub_FFCFB570\n" //__SsPrePreSeq.c__0 ; LOCATION: SsPrePreSeq.c:0\n"
	"TST     R0, #1\n"
	"MOVNE   R2, R4\n"
	"LDMNEFD SP!, {R3-R5,LR}\n"
	"MOVNE   R1, #1\n"
	"BNE     sub_FFC47488\n" //__SsShootCtrl.c__0 ; LOCATION: SsShootCtrl.c:0\n"
	"B       loc_FFC49300\n"
"loc_FFC492FC:\n" //                            ; CODE XREF: sub_FFC492A4+38j
	"BL      sub_FFCFB534\n"
"loc_FFC49300:\n" //                            ; CODE XREF: sub_FFC492A4+54j
	"MOV     R0, #0\n"
	"STR     R0, [SP]\n"
	"LDR     R0, =0xFFC493A4\n"
	"MOV     R2, #2\n"
	"LDRH    R0, [R0,#0x8E]\n"
	"MOV     R1, SP\n"
	"CMP     R0, #3\n"
	"LDRNE   R0, [R4,#0xC]\n"
	"CMPNE   R0, #1\n"
	"MOVHI   R0, #1\n"
	"STRHI   R0, [SP]\n"
	"LDR     R0, =0x123\n"
	"BL      sub_FFC59148\n" // PT_GetPropertyCaseString\n" // ; LOCATION: PropertyCase.c:0\n"
	"BL      sub_FFD1D460\n"
	"BL      sub_FFC593E0\n" //__PropertyCase.c__0 ; LOCATION: PropertyCase.c:0\n"
	"STR     R0, [R4,#0x18]\n"
	"MOV     R0, R4\n"
	"BL      sub_FFCFC70C\n" //__SsCaptureSeq.c__1 ; LOCATION: SsCaptureSeq.c:1\n"
	"BL      sub_FFCFD23C\n" //__SsShootLib.c__488 ; LOCATION: SsShootLib.c:488\n"
	"MOV     R0, R4\n"
//	"BL      sub_FFCFC7D4\n" //__SsCaptureSeq.c__0 ; LOCATION: SsCaptureSeq.c:0

	
	"BL      sub_FFCFC7D4_my\n" 				// ---------->
	"MOV     R5, R0\n"
	"	BL      capt_seq_hook_raw_here\n"      	// + 
	"BL      sub_FFC4BBF8\n"
	"BL      sub_FFC4BC40\n"
	"BL      sub_FFC4BC80\n"
	"MOV     R2, R4\n"
	"MOV     R1, #1\n"
	"MOV     R0, R5\n"
	"BL      sub_FFC47488\n" //__SsShootCtrl.c__0 ; LOCATION: SsShootCtrl.c:0\n"
	"BL      sub_FFCFCA70\n"
	"CMP     R0, #0\n"
	"LDRNE   R0, [R4,#8]\n"
	"ORRNE   R0, R0, #0x2000\n"
	"STRNE   R0, [R4,#8]\n"
	"LDMFD   SP!, {R3-R5,PC}\n"
);

}

// tested! Works!
void __attribute__((naked,noinline)) capt_seq_task() { 
// A2100 - Routine starts at ROM:FFC48F48 ; LOCATION: SsShootTask.c:13
asm volatile(
	 "STMFD   SP!, {R3-R7,LR}\n"
	 "LDR     R7, =0x121BC\n"
	 "LDR     R6, =0x2818\n"
"loc_FFC48F54:\n" //                            
	 "LDR     R0, [R6,#4]\n"
	 "MOV     R2, #0\n"
	 "MOV     R1, SP\n"
	 "BL      sub_FFC163C8\n" //KerQueue.c__0 ; LOCATION: KerQueue.c:0
	 "TST     R0, #1\n"
	 "BEQ     loc_FFC48F80\n"
	 "LDR     R1, =0x588\n"
	 "LDR     R0, =0xFFC48B50\n"
	 "BL      sub_FFC0B284\n" // DebugAssert\n"
	 "BL      sub_FFC0B23C\n" // eventproc_export_ExitTask\n"// ; LOCATION: KerTask.c:0
	 "LDMFD   SP!, {R3-R7,PC}\n"

"loc_FFC48F80:\n" //                            
	 "LDR     R0, [SP]\n"
	 "LDR     R1, [R0]\n"
	 "CMP     R1, #0x1D\n"
	 "ADDLS   PC, PC, R1,LSL#2\n"
	 "B       loc_FFC4917C\n"
"loc_FFC48F94:\n" //                            
	 "B       loc_FFC4900C\n"
"loc_FFC48F98:\n" //                            
	 "B       loc_FFC49014\n"
"loc_FFC48F9C:\n" //                            
	 "B       loc_FFC4903C\n"
"loc_FFC48FA0:\n" //                            
	 "B       loc_FFC49050\n"
"loc_FFC48FA4:\n" //                            
	 "B       loc_FFC49048\n"
"loc_FFC48FA8:\n" //                            
	 "B       loc_FFC49058\n"
"loc_FFC48FAC:\n" //                            
	 "B       loc_FFC49060\n"
"loc_FFC48FB0:\n" //                            
	 "B       loc_FFC4906C\n"
"loc_FFC48FB4:\n" //                            
	 "B       loc_FFC490C4\n"
"loc_FFC48FB8:\n" //                            
	 "B       loc_FFC49050\n"
"loc_FFC48FBC:\n" //                            
	 "B       loc_FFC490CC\n"
"loc_FFC48FC0:\n" //                            
	 "B       loc_FFC490D8\n"
"loc_FFC48FC4:\n" //                            
	 "B       loc_FFC490E0\n"
"loc_FFC48FC8:\n" //                            
	 "B       loc_FFC490E8\n"
"loc_FFC48FCC:\n" //                            
	 "B       loc_FFC490F0\n"
"loc_FFC48FD0:\n" //                            
	 "B       loc_FFC490F8\n"
"loc_FFC48FD4:\n" //                            
	 "B       loc_FFC49100\n"
"loc_FFC48FD8:\n" //                            
	 "B       loc_FFC49108\n"
"loc_FFC48FDC:\n" //                            
	 "B       loc_FFC49114\n"
"loc_FFC48FE0:\n" //                            
	 "B       loc_FFC4911C\n"
"loc_FFC48FE4:\n" //                            
	 "B       loc_FFC49124\n"
"loc_FFC48FE8:\n" //                            
	 "B       loc_FFC4912C\n"
"loc_FFC48FEC:\n" //                            
	 "B       loc_FFC49134\n"
"loc_FFC48FF0:\n" //                            
	 "B       loc_FFC49140\n"
"loc_FFC48FF4:\n" //                            
	 "B       loc_FFC49148\n"
"loc_FFC48FF8:\n" //                            
	 "B       loc_FFC49150\n"
"loc_FFC48FFC:\n" //                            
	 "B       loc_FFC49158\n"
"loc_FFC49000:\n" //                            
	 "B       loc_FFC49160\n"
"loc_FFC49004:\n" //                            
	 "B       loc_FFC4916C\n"
"loc_FFC49008:\n" //                            
	 "B       loc_FFC49188\n"
"loc_FFC4900C:\n" //                            
	 "BL      sub_FFC49824\n" //SsPrepareSeq.c__0
	 "	BL  shooting_expo_param_override\n"  			// +    
	 "B       loc_FFC49064\n"
// copied over from SX10 don't know if we need it yet
//  this code added to avoid some incorrect behavior if overrides are used.
//  but it can cause some unexpected side effects. In this case, remove this code!
"	MOV     R0, #0\n"
"	STR     R0, [R4,#0x24]\n"  // fixes overrides  behavior at short shutter press
//  end of code

"loc_FFC49014:\n" //                            
	 "MOV     R0, #0xC\n"
	 "BL      sub_FFC4D334\n"
	 "TST     R0, #1\n"
	 "LDR     R0, [SP]\n"
	 "MOVNE   R1, #1\n"
	 "LDRNE   R2, [R0,#0xC]\n"
	 "MOVNE   R0, #1\n"
	 "BNE     loc_FFC490BC\n"
//	 "BL      sub_FFC492A4\n" // -------->
	 "BL      sub_FFC492A4_my\n" // -------->
//	 	"	BL      capt_seq_hook_raw_here\n"      	// +    
	 "B       loc_FFC49188\n"

"loc_FFC4903C:\n" //                            
	 "MOV     R0, #1\n"
	 "BL      sub_FFC49A30\n" //SsPrepareSeq.c__0 ; LOCATION: SsPrepareSeq.c:0
	 "B       loc_FFC49188\n"
"loc_FFC49048:\n" //                            
	 "BL      sub_FFC49488\n"
	 "B       loc_FFC49188\n"
"loc_FFC49050:\n" //                            
	 "BL      sub_FFC49804\n"
	 "B       loc_FFC49188\n"
"loc_FFC49058:\n" //                            
	 "BL      sub_FFC4980C\n"
	 "B       loc_FFC49188\n"
"loc_FFC49060:\n" //                            
	 "BL      sub_FFC49950\n" //SsPrepareSeq.c__960
"loc_FFC49064:\n" //                            
	 "BL      sub_FFC47040\n"
	 "B       loc_FFC49188\n"
"loc_FFC4906C:\n" //                            
	 "LDR     R4, [R0,#0xC]\n"
	 "BL      sub_FFC49814\n"
	 "MOV     R0, R4\n"
	 "BL      sub_FFCFB874\n" //SsPrePreSeq.c__2097152 ; LOCATION: SsPrePreSeq.c:2097152
	 "TST     R0, #1\n"
	 "MOV     R5, R0\n"
	 "BNE     loc_FFC490AC\n"
	 "BL      sub_FFC593E0\n" //PropertyCase.c__0 ; LOCATION: PropertyCase.c:0
	 "STR     R0, [R4,#0x18]\n"
	 "MOV     R0, R4\n"
	 "BL      sub_FFCFC70C\n" //SsCaptureSeq.c__1 ; LOCATION: SsCaptureSeq.c:1
	 "MOV     R0, R4\n"\
	 "BL      sub_FFCFCACC\n" //SsCaptureSeq.c__4 ; LOCATION: SsCaptureSeq.c:4
	 "MOV     R5, R0\n"
	 "LDR     R0, [R4,#0x18]\n"
	 "BL      sub_FFC595F4\n" //PropertyCase.c__0 ; LOCATION: PropertyCase.c:0
"loc_FFC490AC:\n" //                            
	 "BL      sub_FFC49804\n"
	 "MOV     R2, R4\n"
	 "MOV     R1, #9\n"
	 "MOV     R0, R5\n"
"loc_FFC490BC:\n" //                            
	 "BL      sub_FFC47488\n" //SsShootCtrl.c__0 ; LOCATION: SsShootCtrl.c:0
	 "B       loc_FFC49188\n"
"loc_FFC490C4:\n" //                            
	 "BL      sub_FFC499B0\n" //SsPrepareSeq.c__0
	 "B       loc_FFC49064\n"
"loc_FFC490CC:\n" //                            
	 "LDR     R0, [R7,#0x4C]\n"
	 "BL      sub_FFC49D40\n" //SsMovieRec.c__184 ; LOCATION: SsMovieRec.c:184
	 "B       loc_FFC49188\n"
"loc_FFC490D8:\n" //                            
	 "BL      sub_FFC49FE8\n" //SsMovieRec.c__2
	 "B       loc_FFC49188\n"
"loc_FFC490E0:\n" //                            
	 "BL      sub_FFC4A07C\n" //SsMovieRec.c__43
	 "B       loc_FFC49188\n"
"loc_FFC490E8:\n" //                            
	 "BL      sub_FFCFBA94\n"
	 "B       loc_FFC49188\n"
"loc_FFC490F0:\n" //                            
	 "BL      sub_FFCFBC74\n"
	 "B       loc_FFC49188\n"
"loc_FFC490F8:\n" //                            
	 "BL      sub_FFCFBD04\n" //SsExpCompSeq.c__105
	 "B       loc_FFC49188\n"
"loc_FFC49100:\n" //                            
	 "BL      sub_FFCFBDAC\n"
	 "B       loc_FFC49188\n"
"loc_FFC49108:\n" //                            
	 "MOV     R0, #0\n"
	 "BL      sub_FFCFBF68\n"
	 "B       loc_FFC49188\n"
"loc_FFC49114:\n" //                            
	 "BL      sub_FFCFC0A0\n"
	 "B       loc_FFC49188\n"
"loc_FFC4911C:\n" //                            
	 "BL      sub_FFCFC130\n" //SsMFSeq.c__110
	 "B       loc_FFC49188\n"
"loc_FFC49124:\n" //                            
	 "BL      sub_FFCFC1F0\n" //SsMFSeq.c__177
	 "B       loc_FFC49188\n"
"loc_FFC4912C:\n" //                            
	 "BL      sub_FFC49B98\n"
	 "B       loc_FFC49188\n"
"loc_FFC49134:\n" //                            
	 "BL      sub_FFC49BC4\n"
	 "BL      sub_FFC14638\n"
	 "B       loc_FFC49188\n"
"loc_FFC49140:\n" //                            
	 "BL      sub_FFCFBE68\n"
	 "B       loc_FFC49188\n"
"loc_FFC49148:\n" //                            
	 "BL      sub_FFCFBEAC\n" //SsChgExpSeq.c__0
	 "B       loc_FFC49188\n"
"loc_FFC49150:\n" //                            
	 "BL      sub_FFC4BB9C\n"
	 "B       loc_FFC49188\n"
"loc_FFC49158:\n" //                            
	 "BL      sub_FFC4BBF8\n"
	 "B       loc_FFC49188\n"
"loc_FFC49160:\n" //                            
	 "BL      sub_FFC4BC54\n"
	 "BL      sub_FFC4BC14\n"
	 "B       loc_FFC49188\n"
"loc_FFC4916C:\n" //                            
	 "LDRH    R0, [R7,#0x90]\n"
	 "CMP     R0, #4\n"
	 "BLNE    sub_FFC4BEC0\n" //SsLiveFunc.c__780 ; LOCATION: SsLiveFunc.c:780
	 "B       loc_FFC49188\n"
"loc_FFC4917C:\n" //                            
	 "LDR     R1, =0x6C9\n"
	 "LDR     R0, =0xFFC48B50\n"
	 "BL      sub_FFC0B284\n" // DebugAssert\n"
"loc_FFC49188:\n" //                            
	 "LDR     R0, [SP]\n"
	 "LDR     R1, [R0,#4]\n"
	 "LDR     R0, [R6]\n"
	 "BL      sub_FFC513E4\n"
	 "LDR     R4, [SP]\n"
	 "LDR     R0, [R4,#8]\n"
	 "CMP     R0, #0\n"
	 "LDREQ   R1, =0x12B\n"
	 "LDREQ   R0, =0xFFC48B50\n"// ; "SsShootTask.c"
	 "BLEQ    sub_FFC0B284\n" // DebugAssert\n"
	 "MOV     R0, #0\n"
	 "STR     R0, [R4,#8]\n"
	 "B       loc_FFC48F54\n"
);
}


// Should be OK, not tested yet!
void __attribute__((naked,noinline)) exp_drv_task(  ) { 
asm volatile (
	"STMFD   SP!, {R4-R8,LR}\n"
	"SUB     SP, SP, #0x20\n"
	"LDR     R8, =0xBB8\n"
	"LDR     R7, =0x38C8\n"
	"LDR     R5, =0x16D18\n"
	"MOV     R0, #0\n"
	"ADD     R6, SP, #0x10\n"
	"STR     R0, [SP,#0xC]\n"

"loc_FFC7DE10:\n"
	"LDR     R0, [R7,#0x20]\n"
	"MOV     R2, #0\n"
	"ADD     R1, SP, #0x1C\n"
	"BL      sub_FFC163C8\n" //KerQueue.c__0 ; LOCATION: KerQueue.c:0\n"
	"LDR     R0, [SP,#0xC]\n"

	"CMP     R0, #1\n"
	"BNE     loc_FFC7DE5C\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R0, [R0]\n"
	"CMP     R0, #0x13\n"
	"CMPNE   R0, #0x14\n"
	"CMPNE   R0, #0x15\n"
	"CMPNE   R0, #0x16\n"
	"BEQ     loc_FFC7DF78\n"
	"CMP     R0, #0x28\n"
	"BEQ     loc_FFC7DF50\n"
	"ADD     R1, SP, #0xC\n"
	"MOV     R0, #0\n"
	"BL      sub_FFC7DDA0\n" //ExpDrv.c__512 ; LOCATION: ExpDrv.c:512\n"

"loc_FFC7DE5C:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R1, [R0]\n"
	"CMP     R1, #0x2D\n"
	"BNE     loc_FFC7DE8C\n"
	"LDR     R0, [SP,#0x1C]\n"
	"BL      sub_FFC7F0A4\n" //ExpDrv.c__280 ; LOCATION: ExpDrv.c:280\n"
	"LDR     R0, [R7,#0x1C]\n"
	"MOV     R1, #1\n"
	"BL      sub_FFC513E4\n"
	"BL      sub_FFC0B23C\n" //eventproc_export_ExitTask ; LOCATION: KerTask.c:0\n"
	"ADD     SP, SP, #0x20\n"
	"LDMFD   SP!, {R4-R8,PC}\n"

"loc_FFC7DE8C:\n"
	"CMP     R1, #0x2C\n"
	"BNE     loc_FFC7DEA8\n"
	"LDR     R2, [R0,#0x88]!\n"
	"LDR     R1, [R0,#4]\n"
	"MOV     R0, R1\n"
	"BLX     R2\n"
	"B       loc_FFC7E3A0\n"
"loc_FFC7DEA8:\n"
	"CMP     R1, #0x26\n"
	"BNE     loc_FFC7DEF8\n"
	"LDR     R0, [R7,#0x1C]\n"
	"MOV     R1, #0x80\n"
	"BL      sub_FFC51418\n"
	"LDR     R0, =0xFFC7A77C\n"
	"MOV     R1, #0x80\n"
	"BL      sub_FFCF1498\n" //IrisController.c__74 ; LOCATION: IrisController.c:74\n"
	"LDR     R0, [R7,#0x1C]\n"
	"MOV     R2, R8\n"
	"MOV     R1, #0x80\n"
	"BL      sub_FFC51324\n" //KerFlag.c__0 ; LOCATION: KerFlag.c:0\n"
	"TST     R0, #1\n"
	"LDRNE   R1, =0xDC6\n"
	"BNE     loc_FFC7DF3C\n"
"loc_FFC7DEE4:\n"
	"LDR     R1, [SP,#0x1C]\n"
	"LDR     R0, [R1,#0x8C]\n"
	"LDR     R1, [R1,#0x88]\n"
	"BLX     R1\n"
	"B       loc_FFC7E3A0\n"
"loc_FFC7DEF8:\n"
	"CMP     R1, #0x27\n"
	"BNE     loc_FFC7DF48\n"
	"ADD     R1, SP, #0xC\n"
	"BL      sub_FFC7DDA0\n" //ExpDrv.c__512 ; LOCATION: ExpDrv.c:512\n"
	"LDR     R0, [R7,#0x1C]\n"
	"MOV     R1, #0x100\n"
	"BL      sub_FFC51418\n"
	"LDR     R0, =0xFFC7A78C\n"
	"MOV     R1, #0x100\n"
	"BL      sub_FFCF1720\n" //IrisController.c__160 ; LOCATION: IrisController.c:160\n"
	"LDR     R0, [R7,#0x1C]\n"
	"MOV     R2, R8\n"
	"MOV     R1, #0x100\n"
	"BL      sub_FFC51324\n" //KerFlag.c__0 ; LOCATION: KerFlag.c:0\n"
	"TST     R0, #1\n"
	"BEQ     loc_FFC7DEE4\n"
	"MOV     R1, #0xDD0\n"
"loc_FFC7DF3C:\n"
	"LDR     R0, =0xFFC7ADBC\n"
	"BL      sub_FFC0B284\n"
	"B       loc_FFC7DEE4\n"
"loc_FFC7DF48:\n"
	"CMP     R1, #0x28\n"
	"BNE     loc_FFC7DF60\n"
"loc_FFC7DF50:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"ADD     R1, SP, #0xC\n"
	"BL      sub_FFC7DDA0\n" //ExpDrv.c__512 ; LOCATION: ExpDrv.c:512\n"
	"B       loc_FFC7DEE4\n"
"loc_FFC7DF60:\n"
	"CMP     R1, #0x2B\n"
	"BNE     loc_FFC7DF78\n"
	"BL      sub_FFC6D29C\n" //Shutter.c__2 ; LOCATION: Shutter.c:2\n"
	"BL      sub_FFC6DF28\n" //ImgPixel.c__0 ; LOCATION: ImgPixel.c:0\n"
	"BL      sub_FFC6DA60\n" //ImgGain.c__0 ; LOCATION: ImgGain.c:0\n"
	"B       loc_FFC7DEE4\n"
"loc_FFC7DF78:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"MOV     R4, #1\n"
	"LDR     R1, [R0]\n"
	"CMP     R1, #0x11\n"
	"CMPNE   R1, #0x12\n"
	"BNE     loc_FFC7DFE8\n"
	"LDR     R1, [R0,#0x7C]\n"
	"ADD     R1, R1, R1,LSL#1\n"
	"ADD     R1, R0, R1,LSL#2\n"
	"SUB     R1, R1, #8\n"
	"LDMIA   R1, {R2-R4}\n"
	"STMIA   R6, {R2-R4}\n"
	"BL      sub_FFC7C854\n" //ExpDrv.c__2 ; LOCATION: ExpDrv.c:2\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R1, [R0,#0x7C]\n"
	"LDR     R3, [R0,#0x88]\n"
	"LDR     R2, [R0,#0x8C]\n"
	"ADD     R0, R0, #4\n"
	"BLX     R3\n"
	"LDR     R0, [SP,#0x1C]\n"
	"BL      sub_FFC7F45C\n" //ExpDrv.c__0 ; LOCATION: ExpDrv.c:0\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R1, [R0,#0x7C]\n"
	"LDR     R3, [R0,#0x90]\n"
	"LDR     R2, [R0,#0x94]\n"
	"ADD     R0, R0, #4\n"
	"BLX     R3\n"
	"B       loc_FFC7E2E0\n"
"loc_FFC7DFE8:\n"
	"CMP     R1, #0x13\n"
	"CMPNE   R1, #0x14\n"
	"CMPNE   R1, #0x15\n"
	"CMPNE   R1, #0x16\n"
	"BNE     loc_FFC7E0A0\n"
	"ADD     R3, SP, #0xC\n"
	"MOV     R2, SP\n"
	"ADD     R1, SP, #0xC\n"
	"BL      sub_FFC7CA98\n" //ExpDrv.c__0 ; LOCATION: ExpDrv.c:0\n"
	"CMP     R0, #1\n"
	"MOV     R4, R0\n"
	"CMPNE   R4, #5\n"
	"BNE     loc_FFC7E03C\n"
	"LDR     R0, [SP,#0x1C]\n"
	"MOV     R2, R4\n"
	"LDR     R1, [R0,#0x7C]!\n"
	"LDR     R12, [R0,#0xC]!\n"
	"LDR     R3, [R0,#4]\n"
	"MOV     R0, SP\n"
	"BLX     R12\n"
	"B       loc_FFC7E074\n"
"loc_FFC7E03C:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"CMP     R4, #2\n"
	"LDR     R3, [R0,#0x8C]\n"
	"CMPNE   R4, #6\n"
	"BNE     loc_FFC7E088\n"
	"LDR     R12, [R0,#0x88]\n"
	"MOV     R0, SP\n"
	"MOV     R2, R4\n"
	"MOV     R1, #1\n"
	"BLX     R12\n"
	"LDR     R0, [SP,#0x1C]\n"
	"MOV     R2, SP\n"
	"ADD     R1, SP, #0xC\n"
	"BL      sub_FFC7DAC0\n" //ExpDrv.c__0 ; LOCATION: ExpDrv.c:0\n"
"loc_FFC7E074:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R2, [SP,#0xC]\n"
	"MOV     R1, R4\n"
	"BL      sub_FFC7DD40\n" //ExpDrv.c__2 ; LOCATION: ExpDrv.c:2\n"
	"B       loc_FFC7E2E0\n"
"loc_FFC7E088:\n"
	"LDR     R1, [R0,#0x7C]\n"
	"LDR     R12, [R0,#0x88]\n"
	"ADD     R0, R0, #4\n"
	"MOV     R2, R4\n"
	"BLX     R12\n"
	"B       loc_FFC7E2E0\n"
"loc_FFC7E0A0:\n"
	"CMP     R1, #0x22\n"
	"CMPNE   R1, #0x23\n"
	"BNE     loc_FFC7E0EC\n"
	"LDR     R1, [R0,#0x7C]\n"
	"ADD     R1, R1, R1,LSL#1\n"
	"ADD     R1, R0, R1,LSL#2\n"
	"SUB     R1, R1, #8\n"
	"LDMIA   R1, {R2-R4}\n"
	"STMIA   R6, {R2-R4}\n"
	"BL      sub_FFC7BDE0\n" //ExpDrv.c__0 ; LOCATION: ExpDrv.c:0\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R1, [R0,#0x7C]\n"
	"LDR     R3, [R0,#0x88]\n"
	"LDR     R2, [R0,#0x8C]\n"
	"ADD     R0, R0, #4\n"
	"BLX     R3\n"
	"LDR     R0, [SP,#0x1C]\n"
	"BL      sub_FFC7C0D0\n" //ExpDrv.c__0 ; LOCATION: ExpDrv.c:0\n"
	"B       loc_FFC7E2E0\n"
"loc_FFC7E0EC:\n"
	"ADD     R1, R0, #4\n"
	"LDMIA   R1, {R2,R3,R12}\n"
	"STMIA   R6, {R2,R3,R12}\n"
	"LDR     R1, [R0]\n"
	"CMP     R1, #0x25\n"
	"ADDLS   PC, PC, R1,LSL#2\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E108:\n"
	"B       loc_FFC7E1A0\n"
"loc_FFC7E10C:\n"
	"B       loc_FFC7E1A0\n"
"loc_FFC7E110:\n"
	"B       loc_FFC7E1A8\n"
"loc_FFC7E114:\n"
	"B       loc_FFC7E1B0\n"
"loc_FFC7E118:\n"
	"B       loc_FFC7E1B0\n"
"loc_FFC7E11C:\n"
	"B       loc_FFC7E1B0\n"
"loc_FFC7E120:\n"
	"B       loc_FFC7E1A0\n"
"loc_FFC7E124:\n"
	"B       loc_FFC7E1A8\n"
"loc_FFC7E128:\n"
	"B       loc_FFC7E1B0\n"
"loc_FFC7E12C:\n"
	"B       loc_FFC7E1B0\n"
"loc_FFC7E130:\n"
	"B       loc_FFC7E1C8\n"
"loc_FFC7E134:\n"
	"B       loc_FFC7E1C8\n"
"loc_FFC7E138:\n"
	"B       loc_FFC7E2B4\n"
"loc_FFC7E13C:\n"
	"B       loc_FFC7E2BC\n"
"loc_FFC7E140:\n"
	"B       loc_FFC7E2BC\n"
"loc_FFC7E144:\n"
	"B       loc_FFC7E2BC\n"
"loc_FFC7E148:\n"
	"B       loc_FFC7E2BC\n"
"loc_FFC7E14C:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E150:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E154:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E158:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E15C:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E160:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E164:\n"
	"B       loc_FFC7E1B8\n"
"loc_FFC7E168:\n"
	"B       loc_FFC7E1C0\n"
"loc_FFC7E16C:\n"
	"B       loc_FFC7E1C0\n"
"loc_FFC7E170:\n"
	"B       loc_FFC7E1D4\n"
"loc_FFC7E174:\n"
	"B       loc_FFC7E1D4\n"
"loc_FFC7E178:\n"
	"B       loc_FFC7E1DC\n"
"loc_FFC7E17C:\n"
	"B       loc_FFC7E20C\n"
"loc_FFC7E180:\n"
	"B       loc_FFC7E23C\n"
"loc_FFC7E184:\n"
	"B       loc_FFC7E26C\n"
"loc_FFC7E188:\n"
	"B       loc_FFC7E29C\n"
"loc_FFC7E18C:\n"
	"B       loc_FFC7E29C\n"
"loc_FFC7E190:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E194:\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E198:\n"
	"B       loc_FFC7E2A4\n"
"loc_FFC7E19C:\n"
	"B       loc_FFC7E2AC\n"
"loc_FFC7E1A0:\n"
	"BL      sub_FFC7AC68\n" //ExpDrv.c__2\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E1A8:\n"
	"BL      sub_FFC7AEDC\n" //ExpDrv.c__0\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E1B0:\n"
	"BL      sub_FFC7B0E0\n" //ExpDrv.c__1016\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E1B8:\n"
	"BL      sub_FFC7B348\n" //ExpDrv.c__2\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E1C0:\n"
	"BL      sub_FFC7B53C\n" //ExpDrv.c__0\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E1C8:\n"
	"BL      sub_FFC7B7CC_my\n" // _ExpDrv.c__2\n"  // ------>
	"MOV     R4, #0\n"
	"B       loc_FFC7E2C0\n"
	//"LDR 	 PC, =0xFFC7E1D4\n" // Continue at FW ------>
	"loc_FFC7E1D4:\n"
	"BL      sub_FFC7B908\n" //ExpDrv.c__0\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E1DC:\n"
	"LDRH    R1, [R0,#4]\n"
	"STRH    R1, [SP,#0x10]\n"
	"LDRH    R1, [R5,#2]\n"
	"STRH    R1, [SP,#0x12]\n"
	"LDRH    R1, [R5,#4]\n"
	"STRH    R1, [SP,#0x14]\n"
	"LDRH    R1, [R5,#6]\n"
	"STRH    R1, [SP,#0x16]\n"
	"LDRH    R1, [R0,#0xC]\n"
	"STRH    R1, [SP,#0x18]\n"
	"BL      sub_FFC7F118\n" //ExpDrv.c__2 ; LOCATION: ExpDrv.c:2\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E20C:\n"
	"LDRH    R1, [R0,#4]\n"
	"STRH    R1, [SP,#0x10]\n"
	"LDRH    R1, [R5,#2]\n"
	"STRH    R1, [SP,#0x12]\n"
	"LDRH    R1, [R5,#4]\n"
	"STRH    R1, [SP,#0x14]\n"
	"LDRH    R1, [R5,#6]\n"
	"STRH    R1, [SP,#0x16]\n"
	"LDRH    R1, [R5,#8]\n"
	"STRH    R1, [SP,#0x18]\n"
	"BL      sub_FFC7F278\n" //ExpDrv.c__2 ; LOCATION: ExpDrv.c:2\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E23C:\n"
	"LDRH    R1, [R5]\n"
	"STRH    R1, [SP,#0x10]\n"
	"LDRH    R1, [R0,#6]\n"
	"STRH    R1, [SP,#0x12]\n"
	"LDRH    R1, [R5,#4]\n"
	"STRH    R1, [SP,#0x14]\n"
	"LDRH    R1, [R5,#6]\n"
	"STRH    R1, [SP,#0x16]\n"
	"LDRH    R1, [R5,#8]\n"
	"STRH    R1, [SP,#0x18]\n"
	"BL      sub_FFC7F324\n" //ExpDrv.c__0 ; LOCATION: ExpDrv.c:0\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E26C:\n"
	"LDRH    R1, [R5]\n"
	"STRH    R1, [SP,#0x10]\n"
	"LDRH    R1, [R5,#2]\n"
	"STRH    R1, [SP,#0x12]\n"
	"LDRH    R1, [R5,#4]\n"
	"STRH    R1, [SP,#0x14]\n"
	"LDRH    R1, [R5,#6]\n"
	"STRH    R1, [SP,#0x16]\n"
	"LDRH    R1, [R0,#0xC]\n"
	"STRH    R1, [SP,#0x18]\n"
	"BL      sub_FFC7F3C4\n" //ExpDrv.c__32 ; LOCATION: ExpDrv.c:32\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E29C:\n"
	"BL      sub_FFC7BBA8\n" //ExpDrv.c__1744\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E2A4:\n"
	"BL      sub_FFC7C1D4\n" //ExpDrv.c__10\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E2AC:\n"
	"BL      sub_FFC7C40C\n" //ExpDrv.c__2176\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E2B4:\n"
	"BL      sub_FFC7C584\n" //ExpDrv.c__2\n"
	"B       loc_FFC7E2C0\n"
"loc_FFC7E2BC:\n"
	"BL      sub_FFC7C71C\n" //ExpDrv.c__128\n"
"loc_FFC7E2C0:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R1, [R0,#0x7C]\n"
	"LDR     R3, [R0,#0x88]\n"
	"LDR     R2, [R0,#0x8C]\n"
	"ADD     R0, R0, #4\n"
	"BLX     R3\n"
	"CMP     R4, #1\n"
	"BNE     loc_FFC7E328\n"
///////////////
//"LDR			PC, =0xFFC7E2E0\n" // -------->

"loc_FFC7E2E0:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"MOV     R2, #0xC\n"
	"LDR     R1, [R0,#0x7C]\n"
	"ADD     R1, R1, R1,LSL#1\n"
	"ADD     R0, R0, R1,LSL#2\n"
	"SUB     R4, R0, #8\n"
	"LDR     R0, =0x16D18\n"
	"ADD     R1, SP, #0x10\n"
	"BL      sub_FFE6CE04\n"
	"LDR     R0, =0x16D24\n"
	"MOV     R2, #0xC\n"
	"ADD     R1, SP, #0x10\n"
	"BL      sub_FFE6CE04\n"
	"LDR     R0, =0x16D30\n"
	"MOV     R2, #0xC\n"
	"MOV     R1, R4\n"
	"BL      sub_FFE6CE04\n"
	"B       loc_FFC7E3A0\n"
"loc_FFC7E328:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"LDR     R0, [R0]\n"
	"CMP     R0, #0xB\n"
	"BNE     loc_FFC7E370\n"
	"MOV     R3, #0\n"
	"STR     R3, [SP]\n"
	"MOV     R3, #1\n"
	"MOV     R2, #1\n"
	"MOV     R1, #1\n"
	"MOV     R0, #0\n"
	"BL      sub_FFC7AA70\n"
	"MOV     R3, #0\n"
	"STR     R3, [SP]\n"
	"MOV     R3, #1\n"
	"MOV     R2, #1\n"
	"MOV     R1, #1\n"
	"MOV     R0, #0\n"
	"B       loc_FFC7E39C\n"
"loc_FFC7E370:\n"
	"MOV     R3, #1\n"
	"MOV     R2, #1\n"
	"MOV     R1, #1\n"
	"MOV     R0, #1\n"
	"STR     R3, [SP]\n"
	"BL      sub_FFC7AA70\n"
	"MOV     R3, #1\n"
	"MOV     R2, #1\n"
	"MOV     R1, #1\n"
	"MOV     R0, #1\n"
	"STR     R3, [SP]\n"
"loc_FFC7E39C:\n"
	"BL      sub_FFC7ABB0\n"
"loc_FFC7E3A0:\n"
	"LDR     R0, [SP,#0x1C]\n"
	"BL      sub_FFC7F0A4\n" //__ExpDrv.c__280 ; LOCATION: ExpDrv.c:280\n"
	"B       loc_FFC7DE10\n"


); }
void __attribute__((naked,noinline)) sub_FFC7B7CC_my(  ) { 
asm volatile (
	"STMFD   SP!, {R4-R8,LR}\n" //
	"LDR     R7, =0x38C8\n"
	"MOV     R4, R0\n"
	"LDR     R0, [R7,#0x1C]\n"
	"MOV     R1, #0x3E\n"
	"BL      sub_FFC51418\n"
	"LDRSH   R0, [R4,#4]\n"
	"MOV     R2, #0\n"
	"MOV     R1, #0\n"
	"BL      sub_FFC7A800\n"
	"MOV     R6, R0\n"
	"LDRSH   R0, [R4,#6]\n"
	"BL      sub_FFC7A910\n"
	"LDRSH   R0, [R4,#8]\n"
	"BL      sub_FFC7A968\n"
	"LDRSH   R0, [R4,#0xA]\n"
	"BL      sub_FFC7A9C0\n"
	"LDRSH   R0, [R4,#0xC]\n"
	"BL      sub_FFC7AA18\n"
	"MOV     R5, R0\n"
	"LDR     R0, [R4]\n"
	"LDR     R8, =0x16D30\n"
	"CMP     R0, #0xB\n"
	"MOVEQ   R6, #0\n"
	"MOVEQ   R5, #0\n"
	"BEQ     loc_FFC7B85C\n"
	"CMP     R6, #1\n"
	"BNE     loc_FFC7B85C\n"
	"LDRSH   R0, [R4,#4]\n"
	"LDR     R1, =0xFFC7A76C\n"
	"MOV     R2, #2\n"
	"BL      sub_FFCF15EC\n" // __IrisController.c__117 ; LOCATION: IrisController.c:117\n"
	"STRH    R0, [R4,#4]\n"
	"MOV     R0, #0\n"
	"STR     R0, [R7,#0x28]\n"
	"B       loc_FFC7B864\n"
"loc_FFC7B85C:\n"//                            ; CODE XREF: _sub_FFC7B7CC__ExpDrv.c__2+64j
	"LDRH    R0, [R8]\n"
	"STRH    R0, [R4,#4]\n"
"loc_FFC7B864:\n"//                            ; CODE XREF: _sub_FFC7B7CC__ExpDrv.c__2+8Cj
	"CMP     R5, #1\n"
	"LDRNEH  R0, [R8,#8]\n"
	"BNE     loc_FFC7B880\n"
	"LDRSH   R0, [R4,#0xC]\n"
	"LDR     R1, =0xFFC7A7F0\n"
	"MOV     R2, #0x20\n"
	"BL      sub_FFC7F0D4\n"
"loc_FFC7B880:\n"//                            ; CODE XREF: _sub_FFC7B7CC__ExpDrv.c__2+A0j
	"STRH    R0, [R4,#0xC]\n"
	"LDRSH   R0, [R4,#6]\n"
	"BL      sub_FFC6D00C_my\n" // _Shutter.c__320 ; ---->\n"
	"LDR     PC,=0xFFC7B88C\n" // Go back to PC -----> \n"

);
}
void __attribute__((naked,noinline)) sub_FFC6D00C_my(  ) { 
asm volatile (
	"STMFD   SP!, {R4-R6,LR}\n"
	"LDR     R5, =0x35BC\n"
	"MOV     R4, R0\n"
	"LDR     R0, [R5,#4]\n"
	"CMP     R0, #1\n"
	"MOVNE   R1, #0x140\n"
	"LDRNE   R0, =0xFFC6CE10\n" //  ; "Shutter.c"\n"
	"BLNE    sub_FFC0B284\n"
	"CMN     R4, #0xC00\n"
	"LDREQSH R4, [R5,#2]\n"
	"CMN     R4, #0xC00\n"
	"LDREQ   R1, =0x146\n"
	"LDREQ   R0, =0xFFC6CE10\n" //  ; "Shutter.c"\n"
	"STRH    R4, [R5,#2]\n"
	"BLEQ    sub_FFC0B284\n"
"                BL      apex2us\n" // <------ Custom stop function 
	"LDR		PC, =0xFFC6D048\n" // Jump back to FW ------> 
);
}
