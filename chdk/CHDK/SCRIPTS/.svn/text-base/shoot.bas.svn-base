@title Delayed Single Shot
@param a time delay (sec)
@default a 2

sleep a*1000 

press "shoot_half"

do 
  sleep 50
until get_shooting = 1

press "shoot_full"
sleep 500
release "shoot_full"

do
   sleep 50
until get_shooting = 1	

release "shoot_half"

