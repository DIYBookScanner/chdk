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
    		while (length--)  *dst++ = *src++;
    }
    

    //ixus125/elph110hs 101a @ 0xFF025E88
    asm volatile (
      "LDR     R1, =0xC0200000 \n"
      "MVN     R0, #0 \n"
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
      // "LDMEQFD SP!, {R4,PC} \n"
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
      "LDMFD   SP!, {R4,LR}\n"    //??
      // "MOV     R0, #0xFF000000\n"
      "MOV     R0, %0\n"                  //new jump-vector
      "BX      R0 \n"
        : : "r"(MEMISOSTART) : "memory","r0","r1","r2","r3","r4"
    );
    while(1);
}
