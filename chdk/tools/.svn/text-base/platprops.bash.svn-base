#!/bin/bash
SVN=svn
name=`basename $0`

function error_exit {
	echo "$name error: $1" >&2
	exit 1
}
function info_msg {
	echo "$name: $1" >&2
}

function warn {
	echo "$name warning: $1" >&2
}

function usage {
	[ "$1" ] && warn "$1"
	cat >&2 <<EOF
set svn properties on a new port
usage:
	$name [options] {platform}
options:
	-pretend: echo instead of doing
EOF
	exit 1
}

arg="$1"
pretend=""
while [ ! -z "$arg" ] ; do
	case $arg in
	-pretend)
		pretend="yes"
	;;
	-*)
		usage "unknown option $arg"
	;;
	*)
		if [ -z "$plat" ] ; then
			plat="$arg"
		else
			usage "bad arg $arg"
		fi
	;;
	esac
	shift
	arg="$1"
done

if [ -z "$plat" ] ; then
	error_exit "missing platform"
fi

if [ ! -d "platform/$plat" ] ; then
	error_exit "bad platform $plat"
fi

svn="svn"
if [ ! -z "$pretend" ] ; then
	svn="echo $svn"
fi

prop=`svn pg svn:ignore loader/d10`
$svn ps svn:ignore "$prop" "loader/$plat" 
if [ -d "loader/$plat/resetcode" ] ; then
	$svn ps svn:ignore "$prop" "loader/$plat/resetcode" 
fi

prop=`svn pg svn:ignore platform/d10`
$svn ps svn:ignore "$prop" "platform/$plat" 

prop=`svn pg svn:ignore platform/d10/sub/100a`
find platform/$plat/sub/* -maxdepth 0 -type d -exec $svn ps svn:ignore "$prop" {} \;

find loader/$plat -name '*.[chSs]' -type f -exec $svn ps svn:eol-style native {} \;
find platform/$plat \( -name '*.[chSs]' -o -name '*.csv' -o -name 'code_gen.txt' \) -type f -exec $svn ps svn:eol-style native {} \;

find loader/$plat -name '[Mm]ake*' -type f \! -iwholename '*/.svn*' -exec $svn ps svn:eol-style LF {} \;
find platform/$plat -name '[Mm]ake*' -type f \! -iwholename '*/.svn*' -exec $svn ps svn:eol-style LF {} \;
