--[[
 Copyright (C) 2010-2011 <reyalp (at) gmail dot com>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2 as
  published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
]]

--[[
stats collector for live view
]]
local stats={
	t_start_frame = ustime.new(),
	t_end_frame = ustime.new(),
	t_start_xfer = ustime.new(),
	t_end_xfer = ustime.new(),
	t_start_draw = ustime.new(),
	t_end_draw = ustime.new(),
	t_start = ustime.new(),
	t_stop = ustime.new(),
}
function stats:init_counters()
	self.count_xfer = 0
	self.count_frame = 0
	self.xfer_last = 0
	self.xfer_total = 0
end

stats:init_counters()

function stats:start()
	if self.run then
		return
	end
	self:init_counters()
	self.t_start:get()
	self.run = true
end
function stats:stop()
	if not self.run then
		return
	end
	self.run = false
	self.t_stop:get()
end

function stats:start_frame()
	self.t_start_frame:get()
	self.count_frame = self.count_frame + 1
end

function stats:end_frame()
	self.t_end_frame:get()
end
function stats:start_xfer()
	self.t_start_xfer:get()
	self.count_xfer = self.count_xfer + 1
end
function stats:end_xfer(bytes)
	self.t_end_xfer:get()
	self.xfer_last = bytes
	self.xfer_total = self.xfer_total + bytes
end
function stats:get()
	local run
	local t_end
	-- TODO a rolling average would be more useful
	local fps_avg = 0
	local frame_time =0
	local bps_avg = 0
	local xfer_time = 0
	local bps_last = 0

	if self.run then
		run = "yes"
		t_end = self.t_end_frame
	else
		run = "no"
		t_end = self.t_stop
	end
	local tsec = (t_end:diffms(self.t_start)/1000)
	if tsec == 0 then
		tsec = 1 
	end
	if self.count_frame > 0 then
		fps_avg = self.count_frame/tsec
		frame_time = self.t_end_frame:diffms(self.t_start_frame)
	end
	if self.count_xfer > 0 then
		-- note this includes time between timer ticks
		bps_avg = self.xfer_total/tsec
		xfer_time = self.t_end_xfer:diffms(self.t_start_xfer)
		-- instananeous
		bps_last = self.xfer_last/xfer_time*1000
	end
	-- TODO this rapidly spams lua with lots of unique strings
	return string.format(
[[Running: %s
FPS avg: %0.2f
Frame last ms: %d
T/P avg kb/s: %d
Xfer last ms: %d
Xfer kb: %d
Xfer last kb/s: %d]],
		run,
		fps_avg,
		frame_time,
		bps_avg/1024,
		xfer_time,
		self.xfer_last/1024,
		bps_last/1024)
end

return stats
