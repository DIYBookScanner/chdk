topdir=../../

SKIPPLATFORMCHECK=1
SKIPINTERWORK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -mlong-calls -DCHDK_MODULE_CODE

OBJS = camera_functions.o tokenizer.o ubasic.o

all: libubasic.a

libubasic.a: $(OBJS)

UBASIC_TEST_CFLAGS=-g -Wall -DUBASIC_TEST -DCAMERA_$(PLATFORM) -DPLATFORMID=$(PLATFORMID) -I$(topdir)platform/$(PLATFORM)
ifdef UBASIC_DEBUG
	UBASIC_TEST_CFLAGS+=-DDEBUG=1
endif

check:
	gcc $(UBASIC_TEST_CFLAGS) -o ubasic_test$(EXE) $(OBJS:.o=.c) run-ubasic.c

clean:
	rm -f $(OBJS) *.a ubasic_test$(EXE)

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
