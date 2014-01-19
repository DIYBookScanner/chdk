--[[
rem How fast can we trigger the shots? Download the jpegs afterwords
rem and check their exif data.
@title Profile Shooting Speed

@param n number of images
@default a 5
--]]

press("shoot_half")

repeat 
	n = n - 1
	
	repeat sleep(10) until get_shooting() == true
	click("shoot_full")
	
	until n < 1

release("shoot_half")
