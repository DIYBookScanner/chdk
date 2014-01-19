--[[
@title Delayed Single Shot

@param a time delay (sec)
@default a 2
--]]

sleep(a*1000)

press("shoot_half")
repeat sleep(50) until get_shooting() == true

press("shoot_full")
sleep(500)
release("shoot_full")

repeat sleep(50) until get_shooting() == false	
release("shoot_half")

