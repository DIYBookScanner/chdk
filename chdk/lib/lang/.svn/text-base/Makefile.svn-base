topdir=../../

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -DCHDK_MODULE_CODE

OBJS = lang.o lang_str.o fileutil.o

all: liblang.a

liblang.a: $(OBJS)

lang_str.o: lang_str.c lang_str.h $(topdir)core/gui_lang.h

lang_str.h: $(topdir)tools/makelang$(EXE) $(topdir)CHDK/LANG/english.lng $(topdir)CHDK/LANG/$(OPT_DEFAULT_LANG).lng
	@echo $< \-\> $@
	$(topdir)tools/makelang$(EXE) $(topdir)CHDK/LANG/english.lng $(topdir)CHDK/LANG/$(OPT_DEFAULT_LANG).lng > lang_str.h

clean:
	rm -f $(OBJS) *.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc

