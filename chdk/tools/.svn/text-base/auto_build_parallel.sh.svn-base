#!/bin/sh

# Read the 'camera_list.csv' file ($3) and run the
# CHDK build action ($2) using the designated
# make program ($1)
# ($4) = -noskip disable SKIP_AUTOBUILD
# - also see main Makefile
# parallel version - starts each build in a seperate session (Windows only)
while IFS=, read cam fw state copy skip
do
  if [ ${cam} != "CAMERA" ] && ( [ "$4" = "-noskip" ] || [ "${skip}" = "" ] ); then \
    if [ "${state}" != "" ]; then state=_${state}; fi; \
    start $1 -s --no-print-directory PLATFORM=${cam} PLATFORMSUB=${fw} STATE=${state} COPY_TO=${copy} SKIP_AUTOBUILD=${skip} $2 || exit 1; \
  fi;
done < $3
