--[[
rem How fast can we trigger the shots? Download the jpegs afterwords
rem and check their exif data.
@title Profile Shooting Speed

@param n number of images
@default a 5
--]]

repeat 
	n = n - 1
	
	press("shoot_half")
	repeat sleep(10) until get_shooting() == true

	click("shoot_full")

	repeat sleep(10) until get_shooting() == false	
	release("shoot_half")

	until n < 1
