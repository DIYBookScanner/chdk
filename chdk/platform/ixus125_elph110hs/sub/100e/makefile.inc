# 0x3241 Found @ 0xfff40040
PLATFORMID=12865

override OPT_EXMEM_MALLOC=1
override OPT_CHDK_IN_EXMEM=1

PLATFORMOS=dryos
PLATFORMOSVER=50

# start of firmware
ROMBASEADDR=0xFF000000

MAXRAMADDR = 0x0FFFFFFF

EXMEM_HEAP_SKIP=0x679800	#(0x50000000-0x4F986800) from sub_FF075F1C = size of video buffers in EXMEM area
EXMEM_BUFFER_SIZE=0x100000	# Amount of EXMEM memory to allocate for CHDK; 40000=256KB, 80000=512KB, A0000=640kb, C0000=768KB, 100000=1MB

# points to the start of the memory pool used by the firmware
ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0xF8867E0		# MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else
MEMISOSTART=0x180998		# original non-exmem value ixus125
endif

KEYSYS=d4c
NEED_ENCODED_DISKBOOT=8
