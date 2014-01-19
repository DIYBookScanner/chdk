topdir=../../

SKIPBUILDRULES=1
SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

# Add directory to find flt.h file.
HOSTCFLAGS+=-I$(topdir)modules

OBJS= myio.o elf-arm.o elfflt.o main.o

all: elf2flt$(EXE) fltdump$(EXE)

%.o: %.c
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -Wno-format -c -o $@ $<

.dep/%.d: %.c .dep
	$(HOSTCC) $(HOSTCFLAGS) -MM $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

elf2flt$(EXE): $(OBJS)
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

fltdump$(EXE): fltdump.o myio.o
	@echo $< \-\> $@
	$(HOSTCC) $(HOSTCFLAGS) -o $@ $^

clean:
	rm -f *.o elf2flt$(EXE) fltdump$(EXE)

distclean: clean

include $(topdir)bottom.inc

