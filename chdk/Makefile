topdir=./
srcdir=./

tmp:=$(shell echo "BUILD_SVNREV := $(DEF_SVN_REF)" > revision.inc)

# can override on command line or *buildconf.inc for custom subsets
CAMERA_LIST=camera_list.csv

# set date command for ZIP files - override in localbuildconf.inc if needed
#  e.g. OS/X date command does not support -R option, use GNU date (gdate) from coreutils 
ZIPDATE=date -R

include makefile.inc

BUILD_SVNREV:=$(shell svnversion -cn $(topdir) | $(ESED) 's/[0-9]*:([0-9]+)[MPS]*/\1/')
ifeq ($(BUILD_SVNREV), )
	BUILD_SVNREV:=$(DEF_SVN_REF)
endif
#for CHDK-Shell up to svn revision 1.6
ifeq ($(BUILD_SVNREV), exported)
	BUILD_SVNREV:=$(DEF_SVN_REF)
endif
ifeq ($(BUILD_SVNREV), exportiert)
	BUILD_SVNREV:=$(DEF_SVN_REF)
endif
#for CHDK-Shell svn revision 1.7
ifeq ($(BUILD_SVNREV), Unversioned directory)
	BUILD_SVNREV:=$(DEF_SVN_REF)
endif
tmp:=$(shell echo "BUILD_SVNREV := $(BUILD_SVNREV)" > revision.inc)

# CHDK folder for full package
ZIPDIRS:=$(shell ls -R CHDK | grep CHDK/ | $(ESED) 's?:?/*?')

SUBDIRS=

# SKIP_TOOLS prevents re-building tools in root level make, to speed up batch builds
ifndef SKIP_TOOLS
SUBDIRS+=tools
endif

# SKIP_MODULES prevents re-building core/modules in root level make, to speed up batch builds
ifndef SKIP_MODULES
SUBDIRS+=modules
endif

# SKIP_CHDK prevents cleaning CHDK in root level make, to speed up batch clean
ifndef SKIP_CHDK
SUBDIRS+=CHDK
endif

# Must do platform before core
SUBDIRS+=platform/$(PLATFORM) platform/$(PLATFORM)/sub/$(PLATFORMSUB)

# SKIP_CORE prevents cleaning core in root level make, to speed up batch clean
ifndef SKIP_CORE
SUBDIRS+=core
endif

# Must do this last as it builds the final .bin file
SUBDIRS+=loader/$(PLATFORM)

.PHONY: fir
fir: version firsub


firsub: all
	mkdir -p $(topdir)bin
	cp $(topdir)loader/$(PLATFORM)/main.bin $(topdir)bin/main.bin
    ifndef NOZERO100K
        ifeq ($(OSTYPE),Windows)
			zero | dd bs=1k count=100 >> $(topdir)bin/main.bin 2> $(DEVNULL)
        else
			dd if=/dev/zero bs=1k count=100 >> $(topdir)bin/main.bin 2> $(DEVNULL)
        endif
    endif
    ifdef PLATFORMOS
        ifeq ($(PLATFORMOS),vxworks)
			@echo \-\> PS.FIR
			$(PAKWIF) $(topdir)bin/PS.FIR $(topdir)bin/main.bin $(PLATFORMID) 0x01000101
        endif
        ifeq ($(PLATFORMOS),dryos)
            ifdef OPT_FI2
                ifdef FI2KEY
					@echo \-\> PS.FI2
					$(PAKFI2) $(topdir)bin/main.bin -p $(PLATFORMID) -pv $(PLATFORMOSVER) -key $(FI2KEY) -iv $(FI2IV) $(topdir)bin/PS.FI2
                else
					@echo WARNING OPT_FI2 set but FI2KEY is not! please read platform/fi2.inc.txt
                endif
            endif
        endif
    endif
    ifdef NEED_ENCODED_DISKBOOT
		@echo dance \-\> DISKBOOT.BIN ver $(NEED_ENCODED_DISKBOOT)
		$(ENCODE_DISKBOOT) $(topdir)bin/main.bin  $(topdir)bin/DISKBOOT.BIN $(NEED_ENCODED_DISKBOOT) 
		rm $(topdir)bin/main.bin
    else
		mv $(topdir)bin/main.bin  $(topdir)bin/DISKBOOT.BIN
    endif
	@echo "**** Firmware creation completed successfully"


.PHONY: upload
upload: fir
	@echo Uploading...
	cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB).FIR $(topdir)bin/PS.FIR
	/home/vitalyb/Projects/ch/libptp2-1.1.0/src/ptpcam -u -m 0xbf01 --filename $(topdir)bin/PS.FIR


infoline:
	@echo "**** GCC $(GCC_VERSION) : BUILDING CHDK-$(VER), #$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE) FOR $(PLATFORM)-$(PLATFORMSUB)"

.PHONY: version
version: FORCE
	echo "**** Build: $(BUILD_NUMBER)"


.PHONY: FORCE
FORCE:


firzip: version firzipsub


firzipsub: infoline clean firsub
	@echo \-\> $(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip
	rm -f $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)$(BUILD_SVNREV)$(STATE).zip
	LANG=C echo -e "CHDK-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:$(BUILD_NUMBER)-$(BUILD_SVNREV) date:`$(ZIPDATE)`" | \
		zip -9jz $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
    ifdef PLATFORMOS
        ifeq ($(PLATFORMOS),vxworks)
			zip -9j $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/PS.FIR > $(DEVNULL)
			rm -f $(topdir)bin/PS.FIR
        endif
        ifeq ($(PLATFORMOS),dryos)
            ifdef OPT_FI2
                ifdef FI2KEY
					zip -9j $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/PS.FI2 > $(DEVNULL)
					rm -f $(topdir)bin/PS.FI2
                endif
            endif
        endif
    endif
	zip -9 $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)CHDK/MODULES/* > $(DEVNULL)
    # if COPY_TO is defined then copy this camera/firmware version to the copied firmware version
    # Define COPY_TO in $(topdir)/platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc of the source
    # firmware version that needs to be copied to another firmware version
	# For the case where one CHDK version applies to two or more other Canon firmware version place all the
	# 'copy to' firmware versions together seperated by ':' - e.g. "a2000,100c,BETA,100a:100b,"
    ifdef COPY_TO
		@echo "**** Copying duplicate Firmwares"
		$(foreach COPY_PLATFORMSUB, $(subst :, ,$(COPY_TO)), \
			cp $(topdir)bin/$(VER)-$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/$(VER)-$(PLATFORM)-$(COPY_PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip ; \
		)
    endif
	rm -f $(topdir)bin/DISKBOOT.BIN


firzipsubcomplete: infoline clean firsub
	@echo \-\> $(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip
	rm -f $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip
	@echo \-\> $(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip
	rm -f $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip
	LANG=C echo -e "CHDK-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE) date:`$(ZIPDATE)`" | \
	zip -9jz $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
	LANG=C echo -e "CHDK-$(VER) for $(PLATFORM) fw:$(PLATFORMSUB) build:$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE) date:`$(ZIPDATE)`" | \
	zip -9jz $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/DISKBOOT.BIN > $(DEVNULL)
	$(foreach ZIPDIR, $(ZIPDIRS), \
		zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)$(ZIPDIR) > $(DEVNULL) ; \
	)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)CHDK/syscurves.CVF      > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)doc/changelog.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)doc/changelog.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)tools/vers.req  > $(DEVNULL)
	cat $(topdir)doc/1_intro.txt  $(topdir)platform/$(PLATFORM)/notes.txt $(topdir)doc/2_installation.txt $(topdir)doc/3_faq.txt $(topdir)doc/4_urls.txt $(topdir)doc/5_gpl.txt $(topdir)doc/6_ubasic_copyright.txt > $(topdir)doc/readme.txt
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)doc/readme.txt  > $(DEVNULL)
	zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)doc/readme.txt  > $(DEVNULL)
	zip -9 $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)CHDK/MODULES/*  > $(DEVNULL)

    ifdef PLATFORMOS
        ifeq ($(PLATFORMOS),vxworks)
			zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)bin/PS.FIR > $(DEVNULL)
			zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/PS.FIR > $(DEVNULL)
			rm -f $(topdir)bin/PS.FIR
        endif
        ifeq ($(PLATFORMOS),dryos)
            ifdef OPT_FI2
                ifdef FI2KEY
					zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)bin/PS.FI2 > $(DEVNULL)
					zip -9j $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/PS.FI2 > $(DEVNULL)
					rm -f $(topdir)bin/PS.FI2
                endif
            endif
        endif
    endif
    # if COPY_TO is defined then copy this camera/firmware version to the copied firmware version
    # Define COPY_TO in $(topdir)/platform/$(PLATFORM)/sub/$(PLATFORMSUB)/makefile.inc of the source
    # firmware version that needs to be copied to another firmware version
	# For the case where one CHDK version applies to two or more other Canon firmware version place all the
	# 'copy to' firmware versions together seperated by ':' - e.g. "a2000,100c,BETA,100a:100b,"
    ifdef COPY_TO
		@echo "**** Copying duplicate Firmwares"
		$(foreach COPY_PLATFORMSUB, $(subst :, ,$(COPY_TO)), \
			cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip $(topdir)bin/$(PLATFORM)-$(COPY_PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)-full$(STATE).zip ; \
			cp $(topdir)bin/$(PLATFORM)-$(PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip $(topdir)bin/$(PLATFORM)-$(COPY_PLATFORMSUB)-$(BUILD_NUMBER)-$(BUILD_SVNREV)$(STATE).zip ; \
		)
    endif
	rm -f $(topdir)bin/DISKBOOT.BIN

print-missing-dump:
	if [ ! -s $(PRIMARY_ROOT)/$(PLATFORM)/sub/$(PLATFORMSUB)/PRIMARY.BIN ] ; then \
		echo "missing primary for $(PLATFORM) $(PLATFORMSUB)" ; \
	fi

rebuild-stubs:
	if [ -s $(PRIMARY_ROOT)/$(PLATFORM)/sub/$(PLATFORMSUB)/PRIMARY.BIN ] ; then \
		echo "rebuild stubs for $(PLATFORM)-$(PLATFORMSUB)" ;\
		$(MAKE) -C $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB) stubs_entry.S bin_compat.h ;\
	else \
		echo "!!! missing primary for $(PLATFORM)-$(PLATFORMSUB)"; \
	fi

# for batch builds, build tools for vx and dryos once, instead of once for every firmware
alltools:
	$(MAKE) -C tools clean all

# for batch builds, build modules once, instead of once for every firmware
allmodules:
	$(MAKE) -C modules clean all
	$(MAKE) -C CHDK clean all

# note assumes PLATFORMOS is always in same case!
os-camera-list-entry:
	echo $(PLATFORM),$(PLATFORMSUB),$(subst _,,$(STATE)),$(COPY_TO),$(SKIP_AUTOBUILD) >> camera_list_$(PLATFORMOS).csv

# define targets to batch build all cameras & firmware versions
# list of cameras/firmware versions is in 'camera_list.csv'
# each row in 'camera_list.csv' has 5 entries:
# - camera (mandatory)         :- name of camera to build
# - firmware (mandatory)       :- firmware version to build
# - beta status (optional)     :- set to BETA for cameras still in beta status
# - copy to (optional)         :- if this firmware version can also be used for another version on the same
#                                 camera define the alternate firmware here. see COPY_TO comments above.
# - skip auto build (optional) :- any value in this column will exclude the camera/firmware from the auto build

batch: version
	SKIP_TOOLS=1 SKIP_MODULES=1 SKIP_CHDK=1 sh tools/auto_build.sh $(MAKE) firsub $(CAMERA_LIST) -noskip
	@echo "**** Summary of memisosizes"
	cat $(topdir)bin/caminfo.txt
	rm -f $(topdir)bin/caminfo.txt   > $(DEVNULL)

batch-zip: version alltools allmodules
	SKIP_TOOLS=1 SKIP_MODULES=1 SKIP_CHDK=1 sh tools/auto_build.sh $(MAKE) firzipsub $(CAMERA_LIST)
	@echo "**** Summary of memisosizes"
	cat $(topdir)bin/caminfo.txt
	rm -f $(topdir)bin/caminfo.txt   > $(DEVNULL)

batch-zip-complete: version alltools allmodules
	SKIP_TOOLS=1 SKIP_MODULES=1 SKIP_CHDK=1 sh tools/auto_build.sh $(MAKE) firzipsubcomplete $(CAMERA_LIST)
	@echo "**** Summary of memisosizes"
	cat $(topdir)bin/caminfo.txt
	rm -f $(topdir)bin/caminfo.txt   > $(DEVNULL)

# note, this will include cameras with SKIP_AUTOBUILD set
os-camera-lists:
	echo 'CAMERA,FIRMWARE,BETA_STATUS,COPY_TO,SKIP_AUTOBUILD' > camera_list_dryos.csv
	echo 'CAMERA,FIRMWARE,BETA_STATUS,COPY_TO,SKIP_AUTOBUILD' > camera_list_vxworks.csv
	sh tools/auto_build.sh $(MAKE) os-camera-list-entry $(CAMERA_LIST) -noskip

# make sure each enabled firmware/sub has a PRIMARY.BIN
# Note this will not fail, just prints all the missing ones
batch-print-missing-dumps:
	sh tools/auto_build.sh $(MAKE) print-missing-dump $(CAMERA_LIST) -noskip

# rebuild all the stubs_entry.S files    
batch-rebuild-stubs: alltools
	sh tools/auto_build.sh $(MAKE) rebuild-stubs $(CAMERA_LIST) -noskip

# rebuild all the stubs_entry.S files    
# parallel version, starts each camera/firmware version build in a seperate session
# Note:- Windows only, this will use all available CPU and a fair amount of memory
#        but will rebuild much faster on a machine with many CPU cores
batch-rebuild-stubs-parallel: alltools
	sh tools/auto_build_parallel.sh $(MAKE) rebuild-stubs $(CAMERA_LIST) -noskip

batch-clean:
	$(MAKE) -C tools clean
	$(MAKE) -C core clean
	$(MAKE) -C modules clean
	$(MAKE) -C CHDK clean
	SKIP_CORE=1 SKIP_MODULES=1 SKIP_CHDK=1 SKIP_TOOLS=1 sh tools/auto_build.sh $(MAKE) clean $(CAMERA_LIST) -noskip

run-code-gen:
	$(MAKE) -C tools code_gen$(EXE)
	$(MAKE) -C $(topdir)platform/$(PLATFORM)/sub/$(PLATFORMSUB) run-code-gen

batch-run-code-gen:
	$(MAKE) -C tools code_gen$(EXE)
	SKIP_CORE=1 SKIP_MODULES=1 SKIP_CHDK=1 SKIP_TOOLS=1 sh tools/auto_build.sh $(MAKE) run-code-gen $(CAMERA_LIST) -noskip
