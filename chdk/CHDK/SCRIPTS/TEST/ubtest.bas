@title ubasic functionality test
@param a interactive
@default a 1
@param b sleep between tests sec/10
@default b 5
rem test various ubasic commands

b=b*100

rem fail flag
f=0

rem output to CHDK/LOGS/LOG_0001.TXT
print_screen 1
print "test plat", get_platform_id, "pset",get_propset

print "sleep/tick test"
s=get_tick_count
sleep 500
t=get_tick_count
r=t-s
print "start",s,"end",t,"dif",r
rem per line yield means we might not be exactly 500
if r < 500 or r > 550 then
	gosub "set_fail"
	print "failed"
endif

rem key input test
if a <> 1 then goto "keyin_done"

rem note not all keys are valid on all cameras
print "key test - set to end"
do
	wait_click 1000
    if is_key "up"        then print "up"
    if is_key "down"      then print "down"
    if is_key "left"      then print "left"
    if is_key "right"     then print "right"
    if is_key "remote"    then print "remote"
    if is_key "display"   then print "disp"
    if is_key "menu"      then print "menu"
    if is_key "set"       then print "set"
    if is_key "erase"     then print "erase"
    if is_key "zoom_in"   then print "zoom in"
    if is_key "zoom_out"  then print "zoom out"
    if is_key "mode"      then print "mode"
    if is_key "help"      then print "help"
    if is_key "video"     then print "video"
    if is_key "playback"  then print "playback"
until is_key "set"

sleep b

:keyin_done
print "key press test"
rem opening menu and moving up and down should be safe and work everywhere
press "menu"
sleep 50
release "menu"
sleep 1000
click "down"
sleep 1000
click "up"
sleep 1000
click "menu"
sleep b

rem mode switch test
if get_mode=1 then
	print "try to switch to rec"
	c=0
	set_record 1
	while get_mode=1 and c < 20
		sleep 100
		c = c  + 1
	wend
	if c = 20 then
		print "switching to rec failed"
rem can't continue if not rec
		gosub "set_fail"
		goto "the_end"
	endif
else
	print "already in rec"
endif

rem TODO some cameras need additional sleep between play->rec and mode switch (g12, ?)
sleep 1000

c = get_capture_mode
print "current mode ",c

if c <> 2 then
rem I think all cameras have P (might be called manual)
	print "try switch to P"
	set_capture_mode 2
	print "new mode", get_capture_mode
	if get_capture_mode <> 2 then
		gosub "set_fail"
	endif
endif
rem TODO should switch to A (1) and back to P to test mode switching

n=get_exp_count
print "exp_count", n
rem half shot and read exposure values
c = 0
press "shoot_half"
while get_shooting <> 1 and c < 30 
	sleep 100
	c = c + 1
wend
if c = 30 then
	print "halfshoot failed"
	gosub "set_fail"
endif
p=get_av96
s=get_sv96
t=get_tv96
print "Av", p, "Sv", s, "Tv", t
print "shot - default",get_exp_count + 1
press "shoot_full"
sleep 50
release "shoot_full"
release "shoot_half"

while get_shooting <> 0 
	sleep 100
wend

rem a little more to make sure shooting is really done
sleep 500

print "exp_count", get_exp_count
n=n+1
if n <> get_exp_count then
	print "exp count or shot fail"
	gosub "set_fail"
endif

rem if auto Tv > 1/250, use -2 stop otherwise +2
if t > 768 then
	print "shoot Tv-2",get_exp_count + 1
	set_tv96_direct t-192
else
	print "shoot Tv+2",get_exp_count + 1
	set_tv96_direct t+192
endif
shoot

sleep b

rem if out Sv > 200, use -2 stop, otherwise +2
if s > 576 then
	print "shoot Sv-2",get_exp_count + 1

	set_sv96 s-192
else
	print "shoot Sv+2",get_exp_count + 1
	set_sv96 s+192
endif
shoot

sleep b

rem get nd filter - 0=no ND, iris assumed; 1=nd, no iris; 2=both
if get_nd_present = 0 or get_nd_present = 2 then
rem TODO valid ranges depend on zoom hard to tell what to use
	print "cam has iris"
endif

if get_nd_present > 0 then
	print "shoot ND in",get_exp_count + 1
	set_nd_filter 1
	shoot

	sleep b

	print "shoot ND out",get_exp_count + 1
	set_nd_filter 2
	shoot

	sleep b
endif

goto "the_end"

rem subs
:set_fail
	f=f+1
	return

rem final cleanup
:the_end
if f > 0 then
	print "failed ",f
else
	print "ok"
endif
print_screen 0
rem this should not appear in the log

print "done"

