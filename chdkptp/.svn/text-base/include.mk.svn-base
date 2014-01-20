HOSTPLATFORM:=$(patsubst MINGW%,MINGW,$(shell uname -s))
ifeq ($(HOSTPLATFORM),MINGW)
OSTYPE=Windows
EXE=.exe
# Note may be freetype6 depending on your CD version, zlib requried for 5.5 and later
CD_FREETYPE_LIB=freetype z
else
ifeq ($(HOSTPLATFORM),Linux)
OSTYPE=Linux
EXE= 
CD_FREETYPE_LIB=freetype z
endif
endif

#extra suffix to add to executable name
EXE_EXTRA=

CC=gcc
CFLAGS=-DCHDKPTP_OSTYPE=\"$(OSTYPE)\" -Wall
LDFLAGS=
#LD=ld

#default lib names, can be overridden in config
LUA_LIB=lua
IUP_LIB=iup
IUP_LUA_LIB=iuplua51
LIBUSB_LIB=usb

CD_LIB=cd
CD_LUA_LIB=cdlua51
IUP_CD_LIB=iupcd
IUP_CD_LUA_LIB=iupluacd51
CD_PLUS_LIB=cdcontextplus cdluacontextplus51
GDI_PLUS_LIBS=gdiplus stdc++
#see config-sample-*.mk
-include $(TOPDIR)/config.mk

ifdef DEBUG
CFLAGS+=-g
LDFLAGS+=-g
else
CFLAGS+=-O2
endif

# use included headers if not specified
ifndef CHDK_SRC_DIR
CHDK_SRC_DIR=$(TOPDIR)/chdk_headers
endif

ifeq ("$(CD_USE_PLUS)","gdiplus")
CD_PLUS_SYS_LIBS=$(GDI_PLUS_LIBS)
endif
# TODO not tested
ifeq ("$(CD_USE_PLUS)","cairo")
CD_PLUS_LIB+=cairo cdcairo cdx11
endif

DEP_DIR=.dep

.PHONY: all
all: all-recursive

all-recursive:
	@for i in $(SUBDIRS); do \
		$(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" || exit 1; \
	done

.PHONY: clean
clean: clean-one clean-recursive

.PHONY: cleand
cleand: cleand-one clean-one cleand-recursive

clean-one:
	rm -f $(EXES) *.o

cleand-one:
	rm -f $(DFILES)

%.o: %.c
	$(CC) -MMD $(CFLAGS) -c -o $@ $<
	@if [ ! -d $(DEP_DIR) ] ; then mkdir $(DEP_DIR) ; fi; \
		cp $*.d $(DEP_DIR)/$*.d; \
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
				-e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $(DEP_DIR)/$*.d; \
			rm -f $*.d

clean-recursive:
	@for i in $(SUBDIRS); do \
		echo \>\> Cleaning in $(FOLDER)$$i; \
		$(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" clean || exit 1; \
	done

cleand-recursive:
	@for i in $(SUBDIRS); do \
		echo \>\> Cleaning dep in $(FOLDER)$$i; \
		$(MAKE) -C $$i FOLDER="$(FOLDER)$$i/" cleand || exit 1; \
	done

