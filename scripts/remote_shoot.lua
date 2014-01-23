--[[
rem How fast can we trigger the shots? Download the jpegs afterwords
rem and check their exif data.
rem http://chdk.wikia.com/wiki/HDR_Fast_Shooter
@title Profile Shooting Speed

@param n number of images
@default n 5
--]]

press("shoot_half")
repeat sleep(10) until get_shooting() == true

release("shoot_half")
repeat sleep(10) until get_shooting() == false

set_aflock(1)
set_aelock(1)

local done = false
local msg
repeat 
	repeat sleep(10) until write_usb_msg('ready')
	
	repeat sleep(10); msg = read_usb_msg() until msg~=nil
	
	if msg == "shoot" then
		ecnt=get_exp_count()	
		press("shoot_full_only")
		repeat sleep(10) until (get_exp_count()~=ecnt)
		release("shoot_full_only")
	elseif msg == "exit" then
		done = true
	end
	
	until done

set_aelock(0)
set_aflock(0)

