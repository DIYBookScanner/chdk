=Introduction=
chdkptp is a tool to access the custom PTP extension of the CHDK firmware addon for canon
cameras. 

This is an alpha version - protocol, functionality, APIs, commands, command line options 
are all subject to change.

Source is available from http://subversion.assembla.com/svn/chdkptp/
Binary snapshot builds are available from http://www.assembla.com/spaces/chdkptp/documents
Roadmap is under development in http://www.assembla.com/spaces/chdkptp/tickets
Changelog is at http://www.assembla.com/wiki/show/chdkptp/Changelog

Documentation for end users can be found in USAGE.TXT

Information about the Raspberry pi binary builds can be found in README-RASPI.TXT

For information about CHDK, see http://chdk.wikia.com/wiki/CHDK
For information about the CHDK PTP extension, see http://chdk.wikia.com/wiki/PTP_Extension

chdkptp is forked from libptp and ptpcam, as modified by mweerden, the chdkde project developers
and others. All source is released under GPL or MIT licenses

The original ptpcam source, written by Mariusz Woloszyn < emsi[A@T]ipartners.pl >
is available from http://libptp.sourceforge.net/

mweerdens modified version can be found at https://github.com/mweerden/CHDK/tree/ptp

the CHDKDE ptpcam source may be found at http://tools.assembla.com/chdkde/browser/trunk/tools/ptpcam

chdkptp includes software from several other projects, see THANKS.TXT for details.

=Dependencies=
- IUP version 3.5 http://www.tecgraf.puc-rio.br/iup/ (earlier 3.x versions may also work)
  Optional, edit config.mk to build without IUP GUI support
- CD Version 5.5 http://www.tecgraf.puc-rio.br/cd/ (earlier 5.x versions may also work)
  Optional, used for remote display
- Lua version 5.1 http://www.lua.org/
- LibUSB (libusb-win32 on windows)
- CHDK source for PTP protocol header from the appropriate branch, e.g.
  http://tools.assembla.com/chdk/browser/trunk

=Windows development environment=
Mingw with gcc 4.6+ is the primary development environment. 
All instructions below assume you are using this.
Using a mingw bash shell for development is suggested.

==Installing mingw==
http://www.mingw.org/
Download the gui installer. Install at least mingw C compiler.
C++ support is required to use CD "context plus", not required or used by default.
Msys is suggested, and may be required
http://sourceforge.net/projects/mingw/files/Installer/mingw-get-inst/

==Installing IUP libraries==
Get the mingw4 binary package of IUP, 
http://sourceforge.net/projects/iup/files/3.5/Windows%20Libraries/
file iup-3.5_Win32_mingw4_lib.zip

Note, this package has the libraries in the root, with etc/ and include/ subdirectories.
You may want to put the libraries in /lib to match the IUP recommended filesystem layout
The examples and win32 binaries are not required, but may be helpful

==Installing CD libraries==
Similar to IUP, from http://sourceforge.net/projects/canvasdraw/files/

==Installing and building Lua==
Get the lua 5.1.x source from http://www.lua.org/download.html
In a msys shell, go to the lua directory and type
make mingw
make local

NOTE:
it's very important that Lua be linked to exactly the same C runtime library
as chdkptp itself. The lbuf file routines expect to be able to fread and fwrite on
a FILE * opened by lua io.open()

This condition probably won't be met if you use a pre-compiled Lua dll on windows.
It's probably OK with a shared lua in typical linux environments. 
If in doubt, build your own Lua with the same compiler you build chdkptp with.

==Installing LibUSB development package==
TODO
describe filter driver installation
http://sourceforge.net/projects/libusb-win32/files/libusb-win32-releases/1.2.2.0/
libusb-win32-bin-1.2.2.0.zip
Unzip somewhere convenient
or is it libusb-win32-devel-filter-1.2.2.0.exe ?

=Linux development environment=
The following is based on Ubuntu 10.04, 64 bit. YMMV
Install the following packages and any required dependencies 
libusb-1.0-0
libusb-dev (may be called libusb-1.0-dev ?)
liblua5.1-0-dev
liblua5.1-0

IUP - using precompiled binaries
Download the appropriate IUP library for your platform from 
http://www.tecgraf.puc-rio.br/iup/
unpack the package
adjust the IUP_LIB_DIR and IUP_INCLUDE_DIR in config.mk
You will also need a fully working gcc environment.

CD - similar to IUP

==Building IUP and CD==
If available, using pre-compiled libraries is suggested, but some notes can be found
in README-RASPI-LIBS.TXT

=Configuring the source (all platforms)=
Edit config.mk to reflect the installation directories of the above packages and
desired compile time options
See config-sample-*.mk for examples

==Mac development==
See README-OSX.TXT

=Building=
make

=Testing your build=
chdkptp -e"exec require'tests':runall()"

This is not a comprehensive test.

=Running=
See USAGE.TXT
