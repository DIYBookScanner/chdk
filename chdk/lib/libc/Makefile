topdir=../../

# Makefile for platform independent 'libc' library
# Code copied from GCC for linking modules without including GCC library

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB)

OBJS = thumb1_case.o

all: libc.a

libc.a: $(OBJS)

clean:
	rm -f $(OBJS) libc.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
