#!/bin/sh
# checkbinsize <sizefile> maxsize
# check the size from a file containing the output of binutils 'size' against the given value
# return 0 on success, 1 on fail
BINSIZE=`tail -1 $1 | cut -f 4`
# fixes maxsize if in hex
MAXSIZE=`printf %d $2`
if [ $MAXSIZE -lt $BINSIZE ] ; then
	echo "bin size mismatch $MAXSIZE < $BINSIZE"
	exit 1
else
	echo "bin size $BINSIZE of $MAXSIZE"
fi
exit 0
