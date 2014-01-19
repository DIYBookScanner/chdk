topdir=../../

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -DCHDK_MODULE_CODE

OBJS = font_8x16.o rbf_font.o

all: libfont.a

libfont.a: $(OBJS)

font_8x16.o: font_8x16.c codepages.h font_8x16_uni_packed.h

font_8x16_uni_packed.h: font_8x16_uni.h $(topdir)tools/font_8x16_pack$(EXE)
	$(topdir)tools/font_8x16_pack$(EXE) > font_8x16_uni_packed.h

clean:
	rm -f $(OBJS) *.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
