static void __attribute__((noreturn)) shutdown();
static void __attribute__((noreturn)) panic(int cnt);

extern long *blob_chdk_core;
extern long *blob_copy_and_reset;
extern long blob_chdk_core_size;
extern long blob_copy_and_reset_size;


void __attribute__((noreturn)) my_restart() 
{
    void __attribute__((noreturn)) (*copy_and_restart)(char *dst, char *src, long length);//declara referência à função
    int i;

	
    for (i=0;i<(blob_copy_and_reset_size/sizeof(long));i++){
	((long*)(RESTARTSTART))[i] = blob_copy_and_reset[i];
    }

    copy_and_restart = (void*)RESTARTSTART;//a função foi copiada para cá
    copy_and_restart((void*)MEMISOSTART, (char*)blob_chdk_core, blob_chdk_core_size);//agora chama a dita cuja
}

#define LED_PR 0xc0220088   //vide entry.S

static void __attribute__((noreturn)) shutdown()
{
    volatile long *p = (void*)0xc02200a0;
        
    asm(
         "MRS     R1, CPSR\n"
         "AND     R0, R1, #0x80\n"
         "ORR     R1, R1, #0x80\n"
         "MSR     CPSR_cf, R1\n"
         :::"r1","r0");
        
    *p = 0x44;

    while(1);
}


static void __attribute__((noreturn)) panic(int cnt)
{
	volatile long *p=(void*)LED_PR;
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
