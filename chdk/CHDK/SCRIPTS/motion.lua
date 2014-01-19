--[[
@title Motion Detect
@param f Trigger Threshold
@default f 25
@param p Trigger Delay (mSec)
@default p 500
]]

a=6         -- columns to split picture into 
b=6         -- rows to split picture into 
c=1         -- measure mode (Y,U,V R,G,B) – U=0, Y=1, V=2, R=3, G=4, B=5
d=300000    -- timeout (mSec) 
e=200       -- comparison interval (msec) - less than 100 will slow down other CHDK functions
g=3         -- draw grid (0=no, 1=grid, 2=sensitivity readout, 3=sensitivity readout & grid)   
h=0         -- not used in LUA - in uBasic is the variable that gets loaded with the number of cells with motion detected
i=0         -- region masking mode: 0=no regions, 1=include, 2=exclude
j=0         --      first column
k=0         --      first row
l=0         --      last column
m=0         --      last row
n=0         -- optional parameters  (1=shoot immediate)
o=2         -- pixel step
repeat
    zones = md_detect_motion( a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p)
    if( zones > 0 ) then 
        shoot() 
    end
until (false)

