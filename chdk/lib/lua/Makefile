topdir=../../

SKIPPLATFORMCHECK=1
SKIPINTERWORK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -mlong-calls -DCHDK_MODULE_CODE

OBJS = setjmp.o \
       lapi.o lcode.o ldebug.o ldo.o ldump.o lfunc.o lgc.o llex.o lmem.o \
       lobject.o lopcodes.o lparser.o lstate.o lstring.o ltable.o ltm.o \
       lundump.o lvm.o lzio.o \
       lauxlib.o lbaselib.o ldblib.o ltablib.o lmathlib.o limathlib.o \
	   liolib.o loslib.o lstrlib.o loadlib.o linit.o

all: liblua.a

liblua.a: $(OBJS)

check:

clean:
	rm -f $(OBJS) *.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
