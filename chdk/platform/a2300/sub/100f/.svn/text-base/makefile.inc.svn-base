# 0x324a Found @ 0xfff40040
PLATFORMID=12874

override OPT_EXMEM_MALLOC=1
override OPT_CHDK_IN_EXMEM=1

PLATFORMOS=dryos
PLATFORMOSVER=50

EXMEM_HEAP_SKIP=0x2DB400	#(0x44000000-0x43D24C00) from sub_FF879854 = size of video buffers in EXMEM area 
EXMEM_BUFFER_SIZE=0x100000	# Amount of EXMEM memory to allocate for CHDK; 40000=256KB, 80000=512KB, A0000=640kb, C0000=768KB, 100000=1MB

# points to the start of the memory pool used by the firmware
ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0x3C24BE0		# MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32(0x20) (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else			# 265KB=0x3CE4BE0, 512KB=0x3CA4BE0, 640KB=0x3C84BE0, 768KB=0x3C64BE0, 1MB=0x3C24BE0
MEMISOSTART=0x1585F0		# original non-exmem value
endif

# start of firmware
ROMBASEADDR=0xFF810000

MAXRAMADDR = 0x03ffffff

NEED_ENCODED_DISKBOOT=8
KEYSYS=d4c
