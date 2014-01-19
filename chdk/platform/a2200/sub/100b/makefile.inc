#PLATFORMID=0x322A
PLATFORMID=12842

PLATFORMOS=dryos

## Force EXMEM on - not enough heap to work in low memory
#override OPT_EXMEM_MALLOC=1
#override OPT_CHDK_IN_EXMEM=1

ROMBASEADDR=0xFF810000
MAXRAMADDR=0x03ffffff

## Set up size variables for EXMEM
EXMEM_HEAP_SKIP=0x2DB400	#(0x44000000-0x43D2C000) from sub_ff885904 = size of video buffers in EXMEM area
EXMEM_BUFFER_SIZE=0xA0000	# Amount of EXMEM memory to allocate for CHDK; 40000=256KB, 80000=512KB, A0000=640kb, C0000=768KB, 100000=1MB

ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0x3C84BE0		# MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else						# 265KB=0x3CE4BE0, 512KB=0x3CA4BE0, 640KB=0x3C84BE0, 768KB=0x3C64BE0, 1MB=0x3C24BE0
MEMISOSTART=0x1698CC		# original non-exmem value
endif

NEED_ENCODED_DISKBOOT=6
KEYSYS=d4c

