//G10 loader - main.c

static void __attribute__((noreturn)) shutdown();
static void __attribute__((noreturn)) panic(int cnt);

extern long *blob_chdk_core;
extern long *blob_copy_and_reset;
extern long blob_chdk_core_size;
extern long blob_copy_and_reset_size;

#define LED_PWR 0xC0220014   // A2100IS Green - power led 
#define LED_DP  0xC0220018   // A2100IS Blue - Direct Print led 
#define LED_AF  0xC022000C   // A2100IS Red - AutoFocus led

void __attribute__((noreturn)) my_restart() 
{
//volatile long *p1 = (void*)LED_PWR;

//p1[0]=0x46;
//p2[0]=0x46;
//p3[0]=0x46;

    void __attribute__((noreturn)) (*copy_and_restart)(char *dst, char *src, long length);
    int i;

	for (i=0; i<(blob_copy_and_reset_size/sizeof(long)); i++){
	((long*)(RESTARTSTART))[i] = blob_copy_and_reset[i];
    }

    copy_and_restart = (void*)RESTARTSTART;
    copy_and_restart((void*)MEMISOSTART, (char*)blob_chdk_core, blob_chdk_core_size);
}


//#define LED_PWR 0xC02200DC      // D10 power lamp/button
//#define LED_PWR 0xC0220014      // 

static void __attribute__((noreturn)) shutdown()
{
    volatile long *p = (void*)0xC0220084;       // turned off later, so assumed to be power
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;  // led off.

    while(1);
}


static void __attribute__((noreturn)) panic(int cnt)
{
	volatile long *p=(void*)LED_AF;
	int i;

	for(;cnt>0;cnt--){
		p[0]=0x46;

		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
		p[0]=0x44;
		for(i=0;i<0x200000;i++){
			asm ("nop\n");
			asm ("nop\n");
		}
	}
	shutdown();
}
