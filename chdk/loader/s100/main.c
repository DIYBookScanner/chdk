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
            while (length--)
            {
                *--dst = *--src;
            }
        }
        else
        {
            while (length--)
            {
                *dst++ = *src++;
            }
        }
    }

	// resetcode here:
	// S100 100d @FF02D4E0
    asm volatile (
        "LDR     R1, =0xC0200000\n"
        "MVN     R0, #0\n"
        "STR     R0, [R1, #0x10C]\n"
        "STR     R0, [R1, #0xC]\n"
        "STR     R0, [R1, #0x1C]\n"
        "STR     R0, [R1, #0x2C]\n"
        "STR     R0, [R1, #0x3C]\n"
        "STR     R0, [R1, #0x4C]\n"
        "STR     R0, [R1, #0x5C]\n"
        "STR     R0, [R1, #0x6C]\n"
        "STR     R0, [R1, #0x7C]\n"
        "STR     R0, [R1, #0x8C]\n"
        "STR     R0, [R1, #0x9C]\n"
        "STR     R0, [R1, #0xAC]\n"
        "STR     R0, [R1, #0xBC]\n"
        "STR     R0, [R1, #0xCC]\n"
        "STR     R0, [R1, #0xDC]\n"
        "STR     R0, [R1, #0xEC]\n"
        "CMP     R4, #7\n"
        "STR     R0, [R1, #0xFC]\n"
        //"LDMEQFD SP!, {R4,PC}\n"
        "MOV     R0, #0x78\n"
        "MCR     p15, 0, R0, c1, c0\n"
        "MOV     R0, #0\n"
        "MCR     p15, 0, R0, c7, c10, 4\n"
        "MCR     p15, 0, R0, c7, c5\n"
        "MCR     p15, 0, R0, c7, c6\n"
        "MOV     R0, #0x80000006\n"
        "MCR     p15, 0, R0, c9, c1\n"
        "MCR     p15, 0, R0, c9, c1, 1\n"
        "MRC     p15, 0, R0, c1, c0\n"
        "ORR     R0, R0, #0x50000\n"
        "MCR     p15, 0, R0, c1, c0\n"
/*
        "CMP     R4, #3\n"
        "LDREQ   R1, =0x12345678\n"
        "MOV     R0, #0x80000000\n"
        "BEQ     loc_FF02D58C\n"
        "CMP     R4, #0xF\n"
        "LDREQ   R1, =0x34567812\n"
        "BEQ     loc_FF02D58C\n"
        "CMP     R4, #0x10\n"
        "BNE     loc_FF02D590\n"
        "LDR     R1, =0x45678123\n"
        "loc_FF02D58C:\n"
        "STR     R1, [R0, #0xFFC]\n"
        "loc_FF02D590:\n"
        "LDMFD   SP!, {R4,LR}\n"
        "MOV     R0, #0xFF000000\n"
*/
        // s100 loader hack to make power button short press work
        "LDR     R0, =0x12345678\n"
        "MOV     R1, #0x80000000\n"
        "STR     R0, [R1,#0xFFC]\n"
        "LDMFD   SP!, {R4,LR}\n"

        "MOV     R0, %0\n" //new jump-vector
        "BX      R0\n"
        : : "r"(MEMISOSTART) : "memory", "r0", "r1", "r2", "r3", "r4");

    while(1);
}

