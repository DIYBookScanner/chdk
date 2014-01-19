
MEMISOSIZE="(&_end-&_start)"
# override this on the command line or in buildconf to use PRIMARY.BIN from a different tree
# should be an absolute path
PRIMARY_ROOT=$(topdir)platform
include $(topdir)buildconf.inc
# optional local version of buildconf.inc, not in SVN so it can be used in autobuilds
# and to avoid getting accidentally included in svn diffs
# you may also set your default camera here
-include $(topdir)localbuildconf.inc
include $(topdir)version.inc
-include $(topdir)revision.inc

ifndef OPT_DE_VERSION
    VER=CHDK
    ifndef OPT_DEFAULT_LANG
        OPT_DEFAULT_LANG=english
    endif
else
    VER=CHDK_DE
    ifndef OPT_DEFAULT_LANG
        OPT_DEFAULT_LANG=german
    endif
endif

ifdef PLATFORM
  ifdef PLATFORMSUB
    MEMBASEADDR=0x1900
    include $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc
    PLFLAGS=-DMEMBASEADDR=$(MEMBASEADDR) -DMEMISOSTART=$(MEMISOSTART) -DMEMISOSIZE=$(MEMISOSIZE)
    ifdef RESTARTSTART
      PLFLAGS+=-DRESTARTSTART=$(RESTARTSTART)
    endif
    ifeq ($(PLATFORMOSVER),)
      PLATFORMOSVER=0
    endif
  endif
endif

# Used in gui_debug.c for controlling memory browser allowed address ranges
# override in platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc to set camera specific value
ifdef MAXRAMADDR
PLFLAGS+=-DMAXRAMADDR=$(MAXRAMADDR)
else
PLFLAGS+=-DMAXRAMADDR=0x1FFFFFF
endif
ifdef ROMBASEADDR
PLFLAGS+=-DROMBASEADDR=$(ROMBASEADDR)
else
PLFLAGS+=-DROMBASEADDR=0xFFC00000
endif

ifdef OPT_FI2
include $(topdir)platform/fi2.inc
endif

SILENT=SILENT

NOZERO100K=TRUE

##########################################################################
##########################################################################
##########################################################################

ESED = sed -r

# keep sort order consistent
export LC_ALL=C

ifndef OSTYPE
  HOSTPLATFORM:=$(patsubst MINGW%,MINGW,$(shell uname -s))
  ifeq ($(HOSTPLATFORM),MINGW)
    OSTYPE = Windows
    EXE = .exe
    SH = sh
    DEVNULL = NUL
	OLDSEPARATOR = \\\\
	NEWSEPARATOR = /
	SORT := $(dir $(shell which uniq.exe | sed 's_$(OLDSEPARATOR)_$(NEWSEPARATOR)_g'))/sort.exe
  else
    ifeq ($(HOSTPLATFORM),Linux)
      OSTYPE = Linux
      EXE =
      SH =
      DEVNULL = /dev/null
      SORT = sort
    else
      ifeq ($(HOSTPLATFORM),Darwin)
        OSTYPE = Darwin
        EXE =
        SH =
        DEVNULL = /dev/null
        SORT = sort
        ESED = sed -E
      else
        OSTYPE = Other
        EXE =
        SH =
        DEVNULL = /dev/null
        SORT = sort
      endif
    endif
  endif
else
  EXE =
  SH =
  DEVNULL = /dev/null
  SORT = sort
endif

##########################################################################
##########################################################################
##########################################################################

HOSTCC=gcc
HOSTCFLAGS=-g -O2 -Wall
HOSTAR=ar

PAKWIF=$(topdir)tools/pakwif$(EXE)
PAKFI2=$(topdir)tools/packfi2/fi2enc$(EXE)
ENCODE_DISKBOOT=$(topdir)tools/dancingbits$(EXE)

##########################################################################

CROSS_COMPILE=arm-elf-

CC=$(CROSS_COMPILE)gcc
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
STRIP=$(CROSS_COMPILE)strip
NM=$(CROSS_COMPILE)nm
AR=$(CROSS_COMPILE)ar
RANLIB=$(CROSS_COMPILE)ranlib
SIZE=$(CROSS_COMPILE)size

GCC_VERSION=$(shell $(CC) -dumpversion)
GCC_VERSION_MAJOR=$(firstword $(subst ., ,$(GCC_VERSION)))

# -msoft-float is used per default but object files are marked as hard-float
# -fno-schedule-insns2 for this gcc bug http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38644
# technically not required for gcc >= 4.6.3, and probably not required for vxworks cams
# see http://chdk.setepontos.com/index.php?topic=8273.msg100205#msg100205
CFLAGS=-fno-inline -Os -fno-strict-aliasing -fno-schedule-insns2
# flags for gcc v4
# CFLAGS+=-mcpu=arm946e-s
# for gcc v3, we use to allow use of strd etc
ifeq ($(GCC_VERSION_MAJOR),3)
    CFLAGS+=-march=armv5te
else
    ifeq ($(GCC_VERSION_MAJOR),4)
        # TODO should be -mcpu, but breaks things ATM
        CFLAGS+=-mtune=arm946e-s
    endif
endif


CTHUMB=-mthumb
ifndef SKIPINTERWORK
CFLAGS+=-mthumb-interwork
endif
CFLAGS+=-I$(topdir)include -I$(topdir)core -I$(topdir)modules -I$(topdir)platform/$(PLATFORM) $(PLFLAGS) $(CPPFLAGS)
ifndef SKIPPLATFORMCHECK
CFLAGS+=-DPLATFORM=\"$(PLATFORM)\" -DPLATFORMSUB=\"$(PLATFORMSUB)\" -DPLATFORMID=$(PLATFORMID) -DCAMERA_$(PLATFORM)=1
endif
CFLAGS+=-DVER_$(VER) -DHDK_VERSION=\"$(VER)\" -DBUILD_NUMBER=\"$(BUILD_NUMBER)\" -DBUILD_SVNREV=\"$(BUILD_SVNREV)\"
CFLAGS+=-Wall -Wno-unused -Wno-format
LDFLAGS=-L$(topdir)lib/math -L$(topdir)lib/font
LDFLAGS+=-L$(topdir)lib/libc -L$(topdir)lib/ubasic
LDFLAGS+=-L$(topdir)platform/$(PLATFORM) -L$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)

ifdef OPT_CURVES
CFLAGS+=-DOPT_CURVES
endif

ifdef OPT_MD_DEBUG
CFLAGS+=-DOPT_MD_DEBUG
endif 

ifdef OPT_DEBUGGING
CFLAGS+=-DOPT_DEBUGGING
endif

ifdef OPT_PTP
CFLAGS+=-DOPT_PTP
endif

ifdef OPT_FORCE_LUA_CALL_NATIVE
CFLAGS+=-DOPT_FORCE_LUA_CALL_NATIVE
endif

ifdef OPT_ARAM_MALLOC
CFLAGS+=-DOPT_ARAM_MALLOC -DARAM_HEAP_START=$(ARAM_HEAP_START) -DARAM_HEAP_SIZE=$(ARAM_HEAP_SIZE)
# Only allow OPT_CHDK_IN_ARAM when OPT_ARAM_MALLOC is also defined
ifdef OPT_CHDK_IN_ARAM
CFLAGS+=-DOPT_CHDK_IN_ARAM -DCHDK_NOT_IN_CANON_HEAP
endif
endif   # OPT_ARAM_MALLOC

ifdef OPT_ARAM_TESTING
CFLAGS+=-DOPT_ARAM_TESTING
endif

ifdef OPT_EXMEM_MALLOC
CFLAGS+=-DOPT_EXMEM_MALLOC
# Only allow OPT_CHDK_IN_EXMEM when OPT_EXMEM_MALLOC is also defined
ifdef OPT_CHDK_IN_EXMEM
CFLAGS+=-DOPT_CHDK_IN_EXMEM -DCHDK_NOT_IN_CANON_HEAP
override OPT_FIRMWARE_PC24_CALL=
endif
endif   # OPT_EXMEM_MALLOC

ifdef OPT_EXMEM_TESTING
CFLAGS+=-DOPT_EXMEM_TESTING
endif

ifdef EXMEM_HEAP_SKIP
CFLAGS+=-DEXMEM_HEAP_SKIP=$(EXMEM_HEAP_SKIP)
endif

ifdef EXMEM_BUFFER_SIZE
CFLAGS+=-DEXMEM_BUFFER_SIZE=$(EXMEM_BUFFER_SIZE)
endif

ifdef OPT_FIRMWARE_PC24_CALL
CFLAGS+=-DOPT_FIRMWARE_PC24_CALL
endif

ifdef OPT_DBG_LUA_ASSERT
CFLAGS+=-DOPT_DBG_LUA_ASSERT
endif

ifdef OPT_WARNINGS
     ifeq ($(GCC_VERSION_MAJOR),3)
           CFLAGS+=-Wwrite-strings -Wsign-compare -Wunused -Wno-unused-parameter
           HOSTCFLAGS+=-Wwrite-strings -Wsign-compare -Wunused -Wno-unused-parameter
     endif
     ifeq ($(GCC_VERSION_MAJOR),4)
           CFLAGS+=-Wextra -fdiagnostics-show-option -Wno-missing-field-initializers -Wunused -Wno-unused-parameter
           #HOSTCFLAGS+=-Wextra -fdiagnostics-show-option -Wno-missing-field-initializers -Wunused -Wno-unused-parameter
     endif
endif

ifdef OPT_EXPIRE_TEST
# convert +n days to unix-ish timestamp
EXPIRE_TIME:=$(shell expr `date +%s` + $(OPT_EXPIRE_TEST) '*' 86400)
CFLAGS+= -DOPT_EXPIRE_TEST=$(EXPIRE_TIME)
endif
##########################################################################

.PHONY: default
default: all

ifndef SKIPBUILDRULES

# rule for building .o from .c in the same directory
%.o: %.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<

# rule for building .o from .c in the same directory - forces THUMB build
%.thm.o: %.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) $(CTHUMB) -nostdinc -c -o $@ $<

# rule for building .o from .c in the 'core' directory
%.o: $(topdir)core/%.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<

# rule for building .o from .c in the 'core' directory - forces THUMB build
%.thm.o: $(topdir)core/%.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) $(CTHUMB) -nostdinc -c -o $@ $<

# rule for building .o from .c in the 'modules' directory
%.o: $(topdir)modules/%.c
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
	
# rule for building .o from .S in the same directory
%.o: %.S
	@echo $< \-\> $@
	$(CC) $(CFLAGS) -nostdinc -c -o $@ $<
	
# rule for building .a
%.a:
	@echo $^ \-\> $@
	$(AR) rcs $@ $^

%.bin: %.elf
	@echo $< \-\> $@
	$(OBJDUMP) -j .text -j .rodata.str1.1 -j .data -j .bss -z -d -r -f -h $< > $@.dump
	$(OBJCOPY) -O binary $< $@

%.elf:
	@echo \-\> $@
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LDFLAGS) $(LDOPTS)
	( $(NM) $@ | grep ' U ' > $@.syms ) && exit 1 || exit 0

.dep/%.d: %.c .dep
	$(CC) $(CFLAGS) -M $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

.dep/%.d: %.S .dep
	$(CC) $(CFLAGS) -M $< > $@.$$$$; \
	    sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	    rm -f $@.$$$$

endif

.PHONY: all
all: all-recursive

.PHONY: clean
clean: clean-recursive

.PHONY: distclean
distclean: distclean-recursive

.dep:
	mkdir .dep

clean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Cleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" clean || exit 1; \
	done

distclean-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Distcleaning in $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" distclean || exit 1; \
	done

all-recursive:
ifndef SKIPPLATFORMCHECK
ifndef PLATFORM
	$(error PLATFORM has not been defined. Specify the PLATFORM to build on the command line or in localbuildconf.inc)
endif
ifndef PLATFORMSUB
	$(error PLATFORMSUB has not been defined. Specify the PLATFORMSUB to build on the command line or in localbuildconf.inc)
endif
endif
	@for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

depend-recursive:
	@for i in $(SUBDIRS); do \
	    echo \>\> Entering to $(FOLDER)$$i; \
	    $(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" depend || exit 1; \
	    echo \<\< Leaving $(FOLDER)$$i; \
	done

ifdef SILENT
.SILENT:
endif


# Define empty recipes for source files (including the makefiles)
# to prevent make from trying implicit rules to create them. Speeds up build process
Makefile: ;
makefile: ;
$(topdir)makefile.inc: ;
$(topdir)buildconf.inc: ;
$(topdir)localbuildconf.inc: ;
$(topdir)version.inc: ;
$(topdir)revision.inc: ;
$(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc: ;
$(topdir)platform/fi2.inc: ;
*.c: ;
*.txt: ;
*.sh: ;
reversebytes.S: ;
callfunc.S: ;
setjmp.S: ;
stubs_min.S: ;
stubs_entry_2.S: ;

