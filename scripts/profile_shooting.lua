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

set_aflock(1)
set_aelock(1)

release("shoot_half")
repeat sleep(10) until get_shooting() == false

press("shoot_full_only")
repeat 
	n = n - 1
	
	ecnt=get_exp_count()	
	repeat sleep(10) until (get_exp_count()~=ecnt)
		
	until n < 1
	
release("shoot_full_only")
set_aelock(0)
set_aflock(0)

