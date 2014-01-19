rem MD tuning - for use with MD AF assist LED tuning
@title MD Tune

@param a Columns
@default a 6
@range a 1 32
@param b Rows
@default b 4
@range b 1 32
@param c Threshold (0-255)
@default c 10
@range c 0 255
@param d Compare Interval (ms)
@default d 7
@param h Pixel Step (pixels)
@default h 6
@param f Channel (U,Y,V,R,G,B)
@default f 1
@values f U Y V R G B
@param n Timeout (10s of seconds)
@default n 30
@param e Trigger Delay (0.1 sec)
@default e 5
@param i Masking (0=No 1=Mask 2=Use)
@default i 0
@range i 0 2
@param j -      Mask Columns Left
@default j 0
@range j 0 32
@param k -      Mask Columns Right
@default k 0
@range k 0 32
@param l -      Mask Rows    Top
@default l 0
@range l 0 32
@param m -      Mask Rows    Bottom
@default m 0
@range m 0 32
@param o Shoot enabled?
@default o 0
@range o 0 1
@param v Grid?
@default v 0
@range v 0 3
@param w AF on delay (x10ms)
@default w 10
@param z AF on time (x10ms)
@default z 2

if j>a then j=a
if k>a then k=a
if l>b then l=b
if m>b then m=b
if g<0 then g=0
if f=0 then print "Channel: U chroma"
if f=1 then print "Channel: Luminance"
if f=2 then print "Channel: V chroma"
if f=3 then print "Channel: Red"
if f=4 then print "Channel: Green"
if f=5 then print "Channel: Blue"
if n<1 then n=1
e=e*100
g=g*1000
n=n*10000

rem turn on AF LED testing
md_af_led_control w*10 z*10

P=get_mode
if P=1 then goto "PlayModeError"

if o=0 then goto "test_md"

print "MD test, shooting"
N=0
do
  t=0
  do
    press "shoot_half"
    do
      P=get_shooting
    until P=1
    md_detect_motion a, b, f, n, d, c, v, t, i, j+1, l+1, a-k, b-m, 9, h, e
  until t>0
  release "shoot_full"  
  do
    P=get_shooting
  until P<>1
  N=N+1
  print t, "cells, trigger ", N
until 0

:test_md
print "MD test, no shooting."
N=0
do
  t=0
  do
    md_detect_motion a, b, f, n, d, c, v, t, i, j+1, l+1, a-k, b-m, 0, h, e
  until t>0
  N=N+1
  print t, "cells, trigger ", N
until 0

:PlayModeError
  print "Not in REC mode, exiting."
end

:restore
  rem turn off AF LED testing
  md_af_led_control 0 0
end
