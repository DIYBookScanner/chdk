topdir=../../

include $(topdir)makefile.inc

LDLIBS=
LDOPTS=-nostdlib -Wl,--allow-shlib-undefined -Wl,--no-define-common,-EL,-T,$(topdir)tools/link-boot.ld
LDOPTS+=-Wl,-N,-Ttext,$(MEMBASEADDR)

CPPFLAGS+=-I.

CORE_FILE=$(topdir)core/main.bin

CPPFLAGS+=-DCORE_FILE=\"$(CORE_FILE)\"

all: main.bin

main.bin: main.elf
main.elf: entry.o main.o blobs.o
blobs.o: $(CORE_FILE) blobs.S

clean:
	rm -f *.o *.bin *.elf *.dump *.elf.syms

distclean: distclean-recursive
	rm -f *.o *.bin *.elf *.dump *.elf.syms

include $(topdir)bottom.inc
