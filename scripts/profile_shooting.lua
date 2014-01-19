--[[
rem How fast can we trigger the shots? Download the jpegs afterwords
rem and check their exif data.
@title Delayed Single Shot

@param n number of images
@default a 5
--]]

repeat 
	n -= 1
	
	press("shoot_half")
	repeat sleep(50) until get_shooting() == true

	press("shoot_full")
	sleep(500)
	release("shoot_full")

	repeat sleep(50) until get_shooting() == false	
	release("shoot_half")

	until n < 1
