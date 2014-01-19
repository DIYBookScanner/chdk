@title Motion Detect
@param f Trigger Threshold
@default f 25
@param p Trigger Delay (mSec)
@default p 500

a=6 
b=6 
c=1 
d=300000 
e=200 
g=3
h=0
i=0  
j=0 
k=0 
l=0
m=0
n=0 
o=2

do
    md_detect_motion a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p
    if( h > 0 ) then 
	shoot 
    endif
until (0)

