--[[
@title Set a1400 to continuous mode over chdkptp
]]
capmode=require("capmode")

-- try and set to continuous mode
local c = (get_drive_mode() == 1)

local r = 3 -- retry r times
while not c and (r > 0) do
	r = r - 1
	rec,vid,mode = get_mode()
	if not rec then
		switch_mode_usb(1)
		sleep(1000)
		rec,vid,mode = get_mode()
	end
	if rec and (capmode.get_name() == "AUTO") then
		-- written for a1400
		click("up")
		sleep(100)
	end
	if rec and (capmode.get_name() == "LIVE") then
		-- written for a1400
		click("set")
		sleep(500)
		click("right")
		sleep(500)
		click("up")
		sleep(1000)
		click("set")
		sleep(500)
	end
	if rec and (capmode.get_name() == "P") then
		-- written for a1400
		click("set")
		sleep(500)
		click("down")
		sleep(1000)
		click("down")
		sleep(1000)
		click("down")
		sleep(1000)
		click("down")
		sleep(1000)
		click("right")
		sleep(500)
		click("down")
		sleep(1000)
		click("set")
		sleep(500)
	end
	c = (get_drive_mode() == 1)
end
