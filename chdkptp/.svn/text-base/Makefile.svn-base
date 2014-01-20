TOPDIR=.
include include.mk

ifdef USE_SVNREV
SVNREV=$(shell svnversion -n |sed -r -e's/^([0-9]+:)?([0-9]+)[MSP]?/\2/')
ifeq ("$(SVNREV)","")
SVNREV=0
endif
else
SVNREV=0
endif

ifeq ($(OSTYPE),Windows)
SYS_LIBS=ws2_32 kernel32
IUP_SYS_LIBS=comctl32 ole32 gdi32 comdlg32
endif

ifeq ("$(PTPIP_SUPPORT)","1")
CFLAGS +=-DCHDKPTP_PTPIP=1
PTPIP_SRCS=sockutil.c
# ws2_32 already included
endif
# PTPIP

ifeq ($(OSTYPE),Linux)
# need 32 bit libs to do this
#TARGET_ARCH=-m32
endif

LINK_LIBS=$(LUA_LIB) $(LIBUSB_LIB)

ifdef LUA_LIB_DIR
LIB_PATHS+=-L$(LUA_LIB_DIR)
endif
ifdef LUA_INCLUDE_DIR
INC_PATHS+=-I$(LUA_INCLUDE_DIR)
endif

ifdef LIBUSB_LIB_DIR
LIB_PATHS+=-L$(LIBUSB_LIB_DIR)
endif
ifdef LIBUSB_INCLUDE_DIR
INC_PATHS+=-I$(LIBUSB_INCLUDE_DIR)
endif

ifeq ("$(IUP_SUPPORT)","1")
ifdef IUP_LIB_DIR
LIB_PATHS+=-L$(IUP_LIB_DIR)
endif
ifdef IUP_INCLUDE_DIR
INC_PATHS+=-I$(IUP_INCLUDE_DIR)
endif
CFLAGS+=-DCHDKPTP_IUP=1
SYS_LIBS+=$(IUP_SYS_LIBS)

# CD only usable with IUP
ifeq ("$(CD_SUPPORT)","1")
ifdef CD_LIB_DIR
LIB_PATHS+=-L$(CD_LIB_DIR)
endif
ifdef CD_INCLUDE_DIR
INC_PATHS+=-I$(CD_INCLUDE_DIR)
endif
CFLAGS+=-DCHDKPTP_CD=1
SYS_LIBS+=$(IUP_SYS_LIBS)
LINK_LIBS=$(IUP_LUA_LIB) $(IUP_CD_LUA_LIB) $(CD_LUA_LIB) $(LUA_LIB) $(IUP_CD_LIB) $(CD_LIB) $(IUP_LIB) $(LIBUSB_LIB) $(CD_FREETYPE_LIB)
ifeq ($(OSTYPE),Windows)
SYS_LIBS+=winspool
endif
ifdef CD_USE_PLUS
SYS_LIBS+=$(CD_PLUS_SYS_LIBS)
LINK_LIBS+=$(CD_PLUS_LIB)
CFLAGS+=-DCHDKPTP_CD_PLUS=1
# TODO static/dynamic should be a top level option.
# This is required if you want to build a standalone context+ executable, otherwise libstdc++ and libgcc are dynamic
ifeq ($(OSTYPE),Windows)
LDFLAGS+=-static
endif
endif
else
LINK_LIBS=$(IUP_LUA_LIB) $(LUA_LIB) $(IUP_LIB) $(LIBUSB_LIB)
endif
# iup
endif

INC_PATHS+=-I$(CHDK_SRC_DIR)

CFLAGS+=$(INC_PATHS) -DCHDKPTP_BUILD_NUM=$(SVNREV) -DCHDKPTP_REL_DESC="\"alpha\""

LDFLAGS+=$(LIB_PATHS) $(patsubst %,-l%,$(LINK_LIBS) $(SYS_LIBS)) 

SUBDIRS=lfs

CHDKPTP_EXE=chdkptp$(EXE_EXTRA)$(EXE)

EXES=$(CHDKPTP_EXE)

all: $(EXES)

SRCS=properties.c ptp.c chdkptp.c lbuf.c liveimg.c rawimg.c luautil.c $(PTPIP_SRCS)
OBJS=$(SRCS:.c=.o)

$(CHDKPTP_EXE): $(OBJS)
	$(CC) -o $@ lfs/lfs.o $^ $(LDFLAGS)


# temp for PTP/IP test code
ifeq ($(OSTYPE),Windows)
NET_LIBS=-lws2_32
else
NETLIBS=
endif
ptpip$(EXE): ptpip.c sockutil.c
	$(CC) $(CFLAGS) -o $@ $^ $(NET_LIBS)

include bottom.mk
