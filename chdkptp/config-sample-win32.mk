# configurable build settings
# these can be set on the command line or in config.mk
# should IUP gui be built ?
IUP_SUPPORT=1
# should gui include CD
CD_SUPPORT=1
# enable CD "plus" context support.
# To actually render with contextplus, set gui_context_plus=true in your startup file
# this uses gdiplus on windows, better image scaling but slower / larger exe
#CD_USE_PLUS=gdiplus
# should this build include PTP/IP (wifi camera) support (not implemented yet!)
PTPIP_SUPPORT=0

# root directories of various packages, used to set subdirs below.
# Not required by main makefile
IUP_DIR=/d/devel/iup
CD_DIR=/d/devel/cd

LIBUSB_DIR=/d/devel/libusb-win32-bin-1.2.4.0
LUA_DIR=/d/devel/lua

IUP_LIB_DIR=$(IUP_DIR)/lib/mingw4
IUP_INCLUDE_DIR=$(IUP_DIR)/include

CD_LIB_DIR=$(CD_DIR)/lib
CD_INCLUDE_DIR=$(CD_DIR)/include

# for CHDK ptp.h this intentionaly uses the ROOT of the CHDK tree, to avoid header name conflicts 
# so core/ptp.h should be found relative to this
# you do not need the whole chdk source, you can just copy ptp.h
CHDK_SRC_DIR=/d/chdk/trunk

LUA_LIB_DIR=$(LUA_DIR)/lib
LUA_INCLUDE_DIR=$(LUA_DIR)/include

LIBUSB_INCLUDE_DIR=$(LIBUSB_DIR)/include
LIBUSB_LIB_DIR=$(LIBUSB_DIR)/lib/gcc

# compile with debug support 
DEBUG=1

# include svn revision in build number
#USE_SVNREV=1

# You don't need to set this unless you are doing protocol development
# if not set, included copies in the chdk_headers directory will be used
# Used to locate CHDK ptp.h and live_view.h 
# this intentionaly uses the ROOT of the CHDK tree, to avoid header name conflicts 
# so core/ptp.h should be found relative to this
#CHDK_SRC_DIR=$(TOPDIR)/chdk_headers
