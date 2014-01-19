@title Intervalometer
@param a = interval (sec)
@default a 15
 
do
    s = get_tick_count
	shoot
    sleep a*1000 - (get_tick_count - s)
until ( 0 )


