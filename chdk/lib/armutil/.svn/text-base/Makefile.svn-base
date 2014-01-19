topdir=../../

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

OBJS = callfunc.o reboot.o cache.o

OBJS_ALL = $(OBJS)

all: libarmutil.a

libarmutil.a: $(OBJS)

clean:
	rm -f $(OBJS_ALL) *.a

distclean: clean
	rm -f $(OBJS_ALL:.o=.d)

include $(topdir)bottom.inc
