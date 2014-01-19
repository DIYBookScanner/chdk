--[[
@title drawings test

@param a 1st color
@default a 160

@param b 2nd color
@default b 162

--]]

require "drawings"

print("This script will")
print("test drawings.")
print("Press any key to start.")


wait_click(0)


print("check colors")
numof_rect=300
rect_size=10
w=200
h=200
colors={"trans","black","white","red","red_dark","red_light","green","green_dark","green_light","blue","blue_dark","blue_light","grey","grey_dark","grey_light","yellow","yellow_dark","yellow_light"}


print("Press any key...")
wait_click(0)



for i=1,numof_rect do
    x=math.random(1,w)
    y=math.random(1,h)
    c=math.random(1,table.getn(colors))
    draw.add("rect",x,y,x+rect_size,y+rect_size,colors[c])
    end

draw.redraw()

print("Press any key...")
wait_click(0)

print("Will draw 2 lines")
sleep(2000)
line1=draw.add("line", 10,10,40,100,a)
line2=draw.add("line", 10,10,10,100,a)
draw.redraw()
sleep(1000)

print("Will draw 2 rectangles")
sleep(2000)
rect1=draw.add("rect", 60,60,80,90,a,2)
rect2=draw.add("rectf", 100,65,120,95,a,b,3)
draw.redraw()
sleep(1000)

print("Will draw 2 ellipses")
sleep(2000)
ellipse1=draw.add("elps", 200,100,30,40,a)
ellipse2=draw.add("elpsf", 250,80,40,30,b)
draw.redraw()
sleep(1000)

print("Will remove 1 rectangle")
sleep(2000)
draw.remove(rect1)
draw.redraw()
sleep(1000)

print("Will move 2nd rectangle")
sleep(2000)
draw.replace(rect2,"rectf", 120,75,160,108,b,a,4)
draw.redraw()
sleep(1000)

print("Will draw text")
sleep(2000)
str=draw.add("string", 150, 80, "TEXT HERE", a,b)
draw.redraw()
sleep(1000)

print("Will clear")
sleep(2000)
draw.clear()
sleep(1000)

print("Will print 2000 pixels")
print("wait...")
for i=1, 2000 do
    x=math.random(1,300)
    y=math.random(1,300)
    draw.add("pixel", x,y,a)
    end
draw.redraw()

print("If you press 'menu'")
print("it will try to draw")
print("1000 random lines")

wait_click(0)
draw.clear()
if (is_key("menu")) then
    for i=1, 1000 do
        x1=math.random(0,300)
        y1=math.random(0,300)
        x2=math.random(0,300)
        y2=math.random(0,300)
        if (math.random(0,1)==0) then c=a else c=b end
        draw.add("line",x1,y1,x2,y2,c)
        end
    draw.redraw()
    sleep(1000)
    end

print("Will clear")
sleep(2000)

draw.clear()

sleep(1000)
print("Will blinking rect")
sleep(2000)

draw.add("rectf", 120,120,200,200,a,b,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,b,a,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,a,b,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,b,a,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,a,b,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,b,a,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,a,b,10)
draw.overdraw()
sleep(500)
draw.add("rectf", 120,120,200,200,b,a,10)
draw.overdraw()



print("Press any key to end")
wait_click(0)
