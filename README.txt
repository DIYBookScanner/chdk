Tried to use 'git svn' erghh no luck. I'll just check in the .svn folders
to git...

Checked out chdk (https://tools.assembla.com/svn/chdk/trunk) at rev 3319. 
Unmarred code lives in the git-branch 'vendor'.

Note: you will need an older subversion client to work with upstream svn.

Prerequistes:
You'll need a cross compiler...
Info: http://chdk.wikia.com/wiki/Compiling_CHDK_under_Linux
Known good cross builder (debian 6 - sid): http://pastebin.com/hvG5nkQj

To build chdk for the a1400:
$ cd chdk
$ make PLATFORM=a1400 PLATFORMSUB=100b fir

To install it:
$ #TODO
