--[[
@title Intervalometer
@param a = interval (sec)
@default a 15
--]]
repeat
    start = get_tick_count()
	shoot()
    sleep(a*1000 - (get_tick_count() - start))
until ( false )


