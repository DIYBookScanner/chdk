--[[
 Copyright (C) 2013 <reyalp (at) gmail dot com>
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
some tests to run against the camera
--]]
local m={}

function m.make_stats(stats)
	local r={
		total=0
	}

	if #stats == 0 then
		return r
	end

	for i,v in ipairs(stats) do
		if not r.max or v > r.max then
			r.max = v
		end
		if not r.min or v < r.min then
			r.min = v
		end
		r.total = r.total + v
	end
	r.mean = r.total/#stats
	return r
end


--[[
repeatedly start scripts, measuring time
opts:{
	count=number -- number of iterations
	code=string  -- code to run
}
]]
function m.exectime(opts)
	opts = util.extend_table({count=100, code="dummy=1"},opts)
	if not con:is_connected() then
		error('not connected')
	end
	local times={}
	local tstart = ustime.new()
	for i=1,opts.count do
		local t0 = ustime.new()
		local status, err = con:exec(opts.code,{nodefaultlib=true})
		if not status then
			error('exec failed '..tostring(err))
		end
		table.insert(times,ustime.diff(t0)/1000000)
		-- wait for the script to be done
		status, err = con:wait_status{run=false}
		if not status then
			error('wait_status failed '..tostring(err))
		end
	end
	local wall_time = ustime.diff(tstart)/1000000
	local stats = m.make_stats(times)
	printf("exec %d mean %.4f min %.4f max %.4f total %.4f (%.4f/sec) wall %.4f (%.4f/sec)\n",
		opts.count,
		stats.mean,
		stats.min,
		stats.max,
		stats.total, opts.count / stats.total, 
		wall_time, opts.count / wall_time)
end

--[[
repeatedly exec code and wait for return, checking that returned value = retval
opts:{
	count=number -- number of iterations
	code=string  -- code to run, should return something
	retval=value -- value code is expected to return
}
--]]
function m.execwaittime(opts)
	opts = util.extend_table({count=100, code="return 1",retval=1},opts)
	if not con:is_connected() then
		error('not connected')
	end
	local times={}
	local tstart = ustime.new()
	for i=1,opts.count do
		local t0 = ustime.new()
		local status, err = con:execwait(opts.code,{nodefaultlib=true,poll=50})
		if not status then
			error('exec failed '..tostring(err))
		end
		if err ~= opts.retval then
			error('bad retval '..tostring(err) .. ' ~= '..tostring(opts.retval))
		end
		table.insert(times,ustime.diff(t0)/1000000)
	end
	local wall_time = ustime.diff(tstart)/1000000
	local stats = m.make_stats(times)
	printf("exec %d mean %.4f min %.4f max %.4f total %.4f (%.4f/sec) wall %.4f (%.4f/sec)\n",
		opts.count,
		stats.mean,
		stats.min,
		stats.max,
		stats.total, opts.count / stats.total, 
		wall_time, opts.count / wall_time)
end

--[[
repeatedly time memory transfers from cam
opts:{
	count=number -- number of iterations
	size=number  -- size to transfer
	addr=number  -- address to transfer from (default 0x1900)
}
]]
function m.xfermem(opts)
	opts = util.extend_table({count=100, size=1024*1024,addr=0x1900},opts)
	if not con:is_connected() then
		error('not connected')
	end
	local times={}
	local tstart = ustime.new()
	for i=1,opts.count do
		local t0 = ustime.new()
		local v,msg=con:getmem(opts.addr,opts.size)
		if not v then
			error('getmem failed '..tostring(err))
		end
		table.insert(times,ustime.diff(t0)/1000000)
	end
	local wall_time = ustime.diff(tstart)/1000000
	local stats = m.make_stats(times)
	printf("%d x %d bytes mean %.4f min %.4f max %.4f total %.4f (%d byte/sec) wall %.4f (%d byte/sec)\n",
		opts.count,
		opts.size,
		stats.mean,
		stats.min,
		stats.max,
		stats.total, opts.count*opts.size / stats.total, 
		wall_time, opts.count*opts.size / wall_time)
end

return m
