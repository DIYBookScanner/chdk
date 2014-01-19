topdir=../../

# Makefile for platform independent 'core' library
# builds code from core and modules that only needs to be compiled once across all camera/firmware versions

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

CFLAGS+=$(CTHUMB) -DCHDK_MODULE_CODE

OBJS = gui_batt.o gui_space.o gui_usb.o gui_mbox.o gps.o gui_script.o gui_menu.o gui_user_menu.o
OBJS+= suba.o levent.o console.o gps_math.o live_view.o ptp.o action_stack.o script.o
OBJS+= usb_input.o usb_module.o usb_remote.o autoiso.o
OBJS+= $(topdir)modules/exportlist.inc module_load.o modules.o

all: libcore.a

libcore.a: $(OBJS)

$(topdir)modules/exportlist.inc:  $(topdir)modules/module_exportlist.c
	@echo $< \-\> $@
	$(topdir)tools/makeexport$(EXE) $(topdir)modules/module_exportlist.c $(topdir)modules/module_exportlist.h $(topdir)/modules/exportlist.inc $(topdir)modules/module_hashlist.h

module_load.o: $(topdir)modules/module_load.c $(topdir)modules/module_load.h $(topdir)modules/module_exportlist.h $(topdir)modules/module_hashlist.h

clean:
	rm -f $(OBJS) *.a

distclean: clean
	rm -f $(OBJS:.o=.d)

include $(topdir)bottom.inc
