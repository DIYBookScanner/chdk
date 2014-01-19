topdir=../

SKIPPLATFORMCHECK=1
SKIPINTERWORK=1

include $(topdir)makefile.inc

SUBDIRS=$(topdir)lib/lua $(topdir)lib/ubasic $(topdir)lib/armutil $(topdir)lib/math
SUBDIRS+=$(topdir)lib/lang $(topdir)lib/font $(topdir)lib/core $(topdir)lib/libc

OBJ_ISDIGIT=
ifeq ($(GCC_VERSION_MAJOR),3)
    OBJ_ISDIGIT+= $(topdir)lib/libc/issmth.o
endif

CFLAGS+=$(CTHUMB) -mlong-calls -DCHDK_MODULE_CODE -fno-reorder-functions

# warning: library order matters!
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,0x24 -r -Wl,-d

# Only build modules files here. Platform independant code to be linked to core CHDK should be in libraries (above)
# to avoid 'long_call' overhead
FLTS=fselect.flt edgeovr.flt curves.flt mpopup.flt palette.flt grids.flt mdetect.flt zebra.flt \
     _dng.flt benchm.flt calend.flt 4wins.flt mastmind.flt reversi.flt sokoban.flt _rawop.flt \
     txtread.flt memview.flt modinsp.flt tetris.flt snake.flt sudoku.flt _tbox.flt _osd_le.flt \
     _hexbox.flt ubasic.flt lua.flt cpuinfo.flt useredit.flt eyefi.flt histo.flt

all: $(FLTS)

%.o: games/%.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<

%.flt: $(topdir)lib/libc/libc.a
	@echo \-\> $@
	mkdir -p .o
	$(CC) $(CFLAGS) -o .o/$*.elf -Wl,--start-group $^ $(LDLIBS) -Wl,--end-group $(LDFLAGS) $(LDOPTS)
#	$(OBJDUMP) -j .text -j .rodata.str1.1 -j .data -j .bss -z -d -r -f -h .o/$*.elf >.o/$*.elf.dump
#	$(topdir)/tools/elf2flt/elf2flt$(EXE) .o/$*.elf $@ -e -f -h -r -s -iexportlist.inc -!$(topdir)/tools/elf2flt/stoplist.txt >$@.dump
	$(topdir)/tools/elf2flt/elf2flt$(EXE) .o/$*.elf $@ -iexportlist.inc -!$(topdir)/tools/elf2flt/stoplist.txt > $(DEVNULL)

nothumb.o: nothumb.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -marm -nostdinc -c -o $@ $<

reversebytes.o: reversebytes.S
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -marm -nostdinc -c -o $@ $<

cpuinfo_arm.o: cpuinfo_arm.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -marm -nostdinc -c -o $@ $<

calend.flt: gui_calendar.o
_tbox.flt: gui_tbox.o
_hexbox.flt: gui_hexbox.o
benchm.flt: gui_bench.o
memview.flt: gui_debug.o
palette.flt: gui_palette.o
mpopup.flt: gui_mpopup.o
txtread.flt: gui_read.o
edgeovr.flt: edgeoverlay.o bitvector.o $(OBJ_ISDIGIT)
zebra.flt: zebra.o
histo.flt: histogram.o
curves.flt: curves.o
mdetect.flt: motion_detector.o
grids.flt: gui_grid.o
modinsp.flt: module_inspector.o
_dng.flt: dng.o reversebytes.o
_rawop.flt: raw_merge.o reversebytes.o
_osd_le.flt: gui_osd_edit.o
fselect.flt: gui_fselect.o nothumb.o
useredit.flt: user_menu_edit.o

4wins.flt: gui_4wins.o
mastmind.flt: gui_mastermind.o
reversi.flt: gui_reversi.o
tetris.flt: gui_tetris.o
snake.flt: gui_snake.o
sokoban.flt: gui_sokoban.o
sudoku.flt: gui_sudoku.o

gui_calendar.o: gui_calendar.c simple_module.c
gui_bench.o: gui_bench.c simple_module.c
eyefi.o: eyefi.c simple_module.c

gui_4wins.o: games/gui_4wins.c games/simple_game.c
gui_mastermind.o: games/gui_mastermind.c games/simple_game.c
gui_reversi.o: games/gui_reversi.c games/simple_game.c
gui_tetris.o: games/gui_tetris.c games/simple_game.c
gui_snake.o: games/gui_snake.c games/simple_game.c

cpuinfo.o: simple_module.c

ubasic.flt: ubasic.o script_key_funcs.o $(topdir)lib/ubasic/libubasic.a
lua.flt: luascript.o script_key_funcs.o script_shoot_hook.o cordic_math.o dbg_dump.o $(topdir)lib/lua/liblua.a

cpuinfo.flt: cpuinfo.o cpuinfo_arm.o 

eyefi.flt: eyefi.o md5.o sha1.o

clean:
	rm -f *.o .o/*.* *.flt *.dump

distclean: clean
#	rm -f *.flt

include $(topdir)bottom.inc
