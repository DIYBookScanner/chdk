IUP and CD compiled for raspberry pi, raspbian hard float 
Binaries to support chdkptp http://www.assembla.com/wiki/show/chdkptp

For information about IUP, see
http://www.tecgraf.puc-rio.br/iup/
http://www.tecgraf.puc-rio.br/cd/

These are pretty much untested, and the IUP build is missing a
few libs (not required for chdkptp)

Build notes:
I managed to build the gui for raspberry pi. Since there was some trial and error and I didn't restart from the beginning with each change, the notes that follow may not be complete.

I did this using the raspbian distro announced here http://www.raspberrypi.org/archives/1605, most of it should apply to building the libs on other Debian based distros, on pi or pc.

Add  the following packages (in addition to the ones required to build chdkptp without gui)
libx11-dev
libxpm-dev
libxmu-dev
libxft-dev
libgtk2.0-dev
libgl1-mesa-dev
libwebkitgtk-dev
libglu1-mesa-dev
libncurses5-dev

These are mostly from the list found at http://www.tecgraf.puc-rio.br/iup/en/building.htm except
- I left out the motif related ones, since I don't care about motif.
- libglu1-mesa-dev was not mentioned, but is required for GL support.
- libncurses5-dev was not mentioned, but was required for something in iup.
libwebkitgtk-dev may have been a mistake, since I couldn't get the iupweb component to build and ended up commenting it out. From what I could tell, USE_PKGCONFIG=Yes giving the wrong location.

Get and extract the IM, CD and IUP sources:
wget http://sourceforge.net/projects/imtoolkit/files/3.8/Docs%20and%20Sources/im-3.8_Sources.tar.gz
wget http://sourceforge.net/projects/canvasdraw/files/5.5.1/Docs%20and%20Sources/cd-5.5.1_Sources.tar.gz
wget http://sourceforge.net/projects/iup/files/3.6/Docs%20and%20Sources/iup-3.6_Sources.tar.gz
tar -xzf im-3.8_Sources.tar.gz
tar -xzf cd-5.5.1_Sources.tar.gz
tar -xzf iup-3.6_Sources.tar.gz

Note, I used the liblua5.1-0-dev package to provide lua. This caused me some problems, it might be better to build lua along with the rest of the libs. In this case, you'd probably also want to link chkdptp with the locally built instead of the debian package.

Now build the libraries in this order IM, CD, IUP
The documentation mentions that you can build individual libraries. However, for IM and CD, it's not immediately clear which are needed to support IUP, so I just tried to build everything, running make in the top level src directory.

To the distro lua package, the following needs to be set
export LUA_SUFFIX=
export LUA_INC=/usr/include/lua5.1

IM built with just 
make 

CD
needs to be built with 
make USE_PKGCONFIG=Yes
to find the correct GTK stuff

IUP
I had multiple problems with this one.
Edit the to level makefile to remove iupweb from do_all
create the following symlink to allow the distro installed lua lib to be found
ln -s /usr/lib/arm-linux-gnueabihf/liblua5.1.a /usr/lib/liblua.a
In srcconsole/Makefile, comment out the @$(TECMAKE_CMD) USE_LUA52=Yes in the iuplua5 target

in the IUP directory
make USE_PKGCONFIG=Yes

Only building the iup libraries actually needed by chdkptp would probably be a smarter approach.

chdkptp doesn't currently use IM, but some of the CD and IUP stuff depends on it. It might be possible to build whats needed for chdkptp without IM.

