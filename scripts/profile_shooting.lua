--[[
rem How fast can we trigger the shots? Download the jpegs afterwords
rem and check their exif data.
rem http://chdk.wikia.com/wiki/HDR_Fast_Shooter
@title Profile Shooting Speed

@param n number of images
@default a 5
--]]

press("shoot_half")
repeat sleep(10) until get_shooting() == true

release("shoot_half")
repeat sleep(10) until get_shooting() == false

set_aflock(1)
set_aelock(1)

repeat 
	n = n - 1
	
	press("shoot_full_only")
	repeat sleep(10) until get_shooting() == true	
	
	release("shoot_full_only")
	repeat sleep(10) until get_shooting() == false
	
	until n < 1

set_aelock(0)
set_aflock(0)
