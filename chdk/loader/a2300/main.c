//static void __attribute__((noreturn)) shutdown();
//static void __attribute__((noreturn)) panic(int cnt);

extern long *blob_chdk_core;
extern long blob_chdk_core_size;

void __attribute__((noreturn)) my_restart()
{
	{
		long *dst = (long*)MEMISOSTART;
        const long *src = blob_chdk_core;
        long length = (blob_chdk_core_size + 3) >> 2;

		if (src < dst && dst < src + length)
        {
			/* Have to copy backwards */
            src += length;
            dst += length;
            while (length--) *--dst = *--src;
         }
         else
         	while (length--) *dst++ = *src++;
	}
	
	//a2300 found @ FF835B24
        asm volatile (
                 "LDR     R1, =0xC0200000\n"
                 "MVN     R0, #0\n"
                 "STR     R0, [R1, #0x10C] \n"
                 "STR     R0, [R1, #0xC] \n"
                 "STR     R0, [R1, #0x1C] \n"
                 "STR     R0, [R1, #0x2C] \n"
                 "STR     R0, [R1, #0x3C] \n"
                 "STR     R0, [R1, #0x4C] \n"
                 "STR     R0, [R1, #0x5C] \n"
                 "STR     R0, [R1, #0x6C] \n"
                 "STR     R0, [R1, #0x7C] \n"
                 "STR     R0, [R1, #0x8C] \n"
                 "STR     R0, [R1, #0x9C] \n"
                 "STR     R0, [R1, #0xAC] \n"
                 "STR     R0, [R1, #0xBC] \n"
                 "STR     R0, [R1, #0xCC] \n"
                 "STR     R0, [R1, #0xDC] \n"
                 "STR     R0, [R1, #0xEC] \n"
                 "CMP     R4, #7 \n"
                 "STR     R0, [R1, #0xFC] \n"
                 // "LDMEQFD SP!, {R4,PC} \n"  //Commented in sx260hs and ELPH310 port
                 "MOV     R0, #0x78 \n"
                 "MCR     p15, 0, R0, c1, c0 \n"
                 "MOV     R0, #0 \n"
                 "MCR     p15, 0, R0, c7, c10, 4 \n"
                 "MCR     p15, 0, R0, c7, c5 \n"
                 "MCR     p15, 0, R0, c7, c6 \n"
                 "MOV     R0, #0x80000006 \n"
                 "MCR     p15, 0, R0, c9, c1 \n"
                 "MCR     p15, 0, R0, c9, c1, 1 \n"
                 "MRC     p15, 0, R0, c1, c0 \n"
                 "ORR     R0, R0, #0x50000 \n"
                 "MCR     p15, 0, R0, c1, c0 \n"
                 "LDR     R0, =0x12345678 \n"
                 "MOV     R1, #0x80000000 \n"
                 "STR     R0, [R1, #0xFFC] \n"
                 // "LDR     R0, =0xFF810000 \n" //original jump-vector
                 "MOV     R0, %0\n"              // new jump-vector
                 "LDMFD   SP!, {R4,LR} \n"
                 "BX      R0 \n"
                 : : "r"(MEMISOSTART) : "memory","r0","r1","r2","r3","r4"
		);

        while(1);
}

//#define LED_PR 0xC0220120  //LED_GREEN

//static void __attribute__((noreturn)) shutdown()
//{
//    volatile long *p = (void*)LED_PR;       // turned off later, so assumed to be power
//
//    asm(
//         "MRS     R1, CPSR\n"
//         "AND     R0, R1, #0x80\n"
//         "ORR     R1, R1, #0x80\n"
//         "MSR     CPSR_cf, R1\n"
//         :::"r1","r0");
//
//    *p = 0x44;  // led off.
//
//    while(1);
//}

//static void __attribute__((noreturn)) panic(int cnt)
//{
//	volatile long *p=(void*)LED_PR;
//	int i;
//
//	for(;cnt>0;cnt--){
//		p[0]=0x46;
//
//		for(i=0;i<0x200000;i++){
//			asm ("nop\n");
//			asm ("nop\n");
//		}
//		p[0]=0x44;
//		for(i=0;i<0x200000;i++){
//			asm ("nop\n");
//			asm ("nop\n");
//		}
//	}
//	shutdown();
//}
