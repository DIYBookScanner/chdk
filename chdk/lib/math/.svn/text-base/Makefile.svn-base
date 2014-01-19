topdir=../../

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -DCHDK_MODULE_CODE

OBJS = d2d.o wrapper.o

all: libmath.a

libmath.a: $(OBJS)

d2d.o: d2d.c fdlibm.h

clean:
	rm -f $(OBJS) *.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
