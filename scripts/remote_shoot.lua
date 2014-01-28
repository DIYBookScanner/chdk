--[[
@title Remote Shoot over CHDKPTP
--]]

press('shoot_half')
repeat sleep(10) until get_shooting() == true

set_aflock(1)
set_aelock(1)

release('shoot_half')
repeat sleep(10) until get_shooting() == false

local done = false
local msg
repeat 
	repeat sleep(10) until write_usb_msg('ready')
	
	repeat sleep(10); msg = read_usb_msg() until msg~=nil
	
	if msg == 'shoot' then
		ecnt=get_exp_count()	
		press('shoot_full_only')
		repeat sleep(10) until (get_exp_count()~=ecnt)
		release('shoot_full_only')
	elseif msg == 'ping' then
		repeat sleep(10) until write_usb_msg('pong')
	elseif msg == 'exit' then
		done = true
	end
	
	until done

set_aelock(0)
set_aflock(0)

