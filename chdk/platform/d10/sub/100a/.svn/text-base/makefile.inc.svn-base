#31BC 12732
PLATFORMID=12732

PLATFORMOS=dryos

ROMBASEADDR=0xff810000

# Set up size variables for EXMEM
EXMEM_HEAP_SKIP=0xFD200	#(0x44000000-0x43F02E00) from sub_FF86CAA8 = size of video buffers in EXMEM area (?)
EXMEM_BUFFER_SIZE=0x300000	# Amount of EXMEM memory to allocate for CHDK = 3MB

MAXRAMADDR=0x03FFFFFF # 64 mb

# Set up size variables for AgentRAM
override OPT_ARAM_MALLOC=1
override OPT_CHDK_IN_ARAM=1
ARAM_HEAP_START=0x34e000
ARAM_HEAP_SIZE=0x32000

ifdef OPT_CHDK_IN_ARAM
MEMISOSTART=$(ARAM_HEAP_START)
else
ifdef OPT_CHDK_IN_EXMEM
MEMISOSTART=0x3C02DE0		# MAXRAMADDR+1 - EXMEM_HEAP_SKIP - EXMEM_BUFFER_SIZE - 32 (exmem allocates 64 bytes extra, 32 before and 32 after block allocated)
else
MEMISOSTART=0x146A2C
endif
endif

# type of diskboot encoding: undefined = none; 1 = original; 2 = sx200, d10; 3 = ixus200...
NEED_ENCODED_DISKBOOT=2
# type of FI2 encoding
KEYSYS=d4

PLATFORMOSVER=31
