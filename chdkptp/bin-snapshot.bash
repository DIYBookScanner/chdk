#!/bin/bash
# build a snapshot zip 
name=`basename "$0"`
function warn {
	echo "$name warning: $1" >&2
}

function usage {
	[ "$1" ] && warn "$1"
	cat >&2 <<EOF
make a binary snapshot
usage:
	$name [options]
options:
	-debug: build debug and don't strip
        -gui: build gui and cli executables (assumes config.mk set up)

EOF
	exit 1
}

arg="$1"
debug=""
while [ ! -z "$arg" ] ; do
	case $arg in
	-debug)
		debug=1
	;;
	-gui)
		gui=1
	;;
	*)
		usage "unknown option $arg"
	;;
	esac
	shift
	arg="$1"
done

OSTYPE=`uname -o`
if [ "$OSTYPE" = "Msys" ] ; then
	OS="win32"
	EXE=".exe"
else 
	OS=`uname -sm | sed -e 's/ /-/'`
	EXE=""
fi
REV=`svnversion  . | sed -e 's/:/-/'`
if [ -z "$debug" ] ; then
	ZIPNAME="chdkptp-r$REV-$OS.zip"
else
	ZIPNAME="chdkptp-r$REV-$OS-dbg.zip"
fi

echo $ZIPNAME
if [ -f "$ZIPNAME" ] ; then
	rm -f "$ZIPNAME"
fi

PROGS=chdkptp$EXE
make DEBUG="$debug" clean all
if [ ! -z "$gui" ] ; then
	make DEBUG="$debug" GUI=1 clean all
	PROGS="$PROGS chdkptp_gui$EXE"
fi

if [ -z "$debug" ] ; then
	strip $PROGS
fi


zip "$ZIPNAME" $PROGS chdkptp-sample.sh \
	lua/*.lua \
	lua/extras/*.lua \
	README.TXT USAGE.TXT COPYING THANKS.TXT \
	README-RASPI.TXT README-RASPI-LIBS.TXT README-OSX.TXT
