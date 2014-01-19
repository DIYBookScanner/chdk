topdir=../

SKIPPLATFORMCHECK=1

include $(topdir)makefile.inc

ifndef OPT_DE_VERSION
LOGO=logo.dat
else
LOGO=logo_de.dat
endif

GENLUA=LUALIB/GEN/propset1.lua LUALIB/GEN/propset2.lua LUALIB/GEN/propset3.lua LUALIB/GEN/propset4.lua LUALIB/GEN/propset5.lua LUALIB/GEN/propset6.lua \
  	   LUALIB/GEN/modelist.lua \
       LUALIB/GEN/cnf_core.lua LUALIB/GEN/cnf_osd.lua LUALIB/GEN/cnf_user.lua LUALIB/GEN/cnf_gps.lua
       
# generate some lua files from CHDK source
all: $(GENLUA)
	@echo "copy" $(LOGO)
	mkdir -p DATA
	cp $(LOGO) DATA/$(LOGO)
	@echo "copy modules"
	mkdir -p MODULES
	rm -f MODULES/*
	cp $(topdir)modules/*.flt MODULES

LUALIB/GEN/propset1.lua:  $(topdir)include/propset1.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset2.lua:  $(topdir)include/propset2.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset3.lua:  $(topdir)include/propset3.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset4.lua:  $(topdir)include/propset4.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset5.lua:  $(topdir)include/propset5.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/propset6.lua:  $(topdir)include/propset6.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_propset_lua.sed < $< > $@

LUALIB/GEN/modelist.lua:  $(topdir)include/modelist.h
	@echo "->" $@
	sed -n -f  $(topdir)tools/gen_modelist_lua.sed < $< > $@

LUALIB/GEN/cnf_core.lua: $(topdir)core/conf.c $(topdir)tools/gen_conf_lua$(EXE)
	@echo "->" $@
	$(topdir)tools/gen_conf_lua$(EXE) $(topdir)core/conf.c conf_info 1000 > $@

LUALIB/GEN/cnf_osd.lua: $(topdir)core/conf.c $(topdir)tools/gen_conf_lua$(EXE)
	@echo "->" $@
	$(topdir)tools/gen_conf_lua$(EXE) $(topdir)core/conf.c osd_conf_info 2000 > $@

LUALIB/GEN/cnf_user.lua: $(topdir)core/conf.c $(topdir)tools/gen_conf_lua$(EXE)
	@echo "->" $@
	$(topdir)tools/gen_conf_lua$(EXE) $(topdir)core/conf.c user_menu_conf_info 3000 > $@

LUALIB/GEN/cnf_gps.lua: $(topdir)core/conf.c $(topdir)tools/gen_conf_lua$(EXE)
	@echo "->" $@
	$(topdir)tools/gen_conf_lua$(EXE) $(topdir)core/conf.c gps_conf_info 4000 > $@

clean:
	rm -f $(GENLUA)
	rm -f DATA/$(LOGO)
	rm -f MODULES/*.flt

include $(topdir)bottom.inc
