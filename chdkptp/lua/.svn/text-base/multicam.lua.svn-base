--[[
 Copyright (C) 2010-2012 <reyalp (at) gmail dot com>
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
experimental code for shooting with multiple cameras
not optimized for best sync, lots of loose ends
usage:
!mc=require('multicam')
!mc:connect()
!mc:start()
!return mc:cmdwait('rec')
!return mc:cmdwait('preshoot')
!return mc:cmdwait('shoot')
!return mc:cmdwait('play')
!mc:cmd('exit')
]]

local mc={}
--[[
connect to all available cams
TODO add matching support
]]
function mc:connect()
	local devices = chdk.list_usb_devices()
	self.cams={}
	for i, devinfo in ipairs(devices) do
		local lcon,msg = chdku.connection(devinfo)
		-- if not already connected, try to connect
		if lcon:is_connected() then
			lcon:update_connection_info()
		else
			local status,err = lcon:connect()
			if not status then
				warnf('%d: connect failed bus:%s dev:%s err:%s\n',i,devinfo.dev,devinfo.bus,tostring(err))
			end
		end
		-- if connection didn't fail
		if lcon:is_connected() then
			printf('%d:%s bus=%s dev=%s sn=%s\n',
				i,
				lcon.ptpdev.model,
				lcon.condev.dev,
				lcon.condev.bus,
				tostring(lcon.ptpdev.serial_number))
			lcon.mc_id = string.format('%d:%s',i,lcon.ptpdev.model)
			table.insert(self.cams,lcon)
		end
	end
end

function mc:start_single(lcon)
	local status,err = lcon:script_status()
	if not status then
		warnf('%s: load script failed: %s\n',lcon.mc_id,tostring(err))
		return
	end
	-- attempt to end a running mc (otherwise script id is wrong)
	if status.run then
		warnf('%s: attempting to stop running script\n',lcon.mc_id)
		lcon:write_msg('exit')
		status,err = lcon:wait_status{
			run=false,
			timeout=250,
		}
		if not status then
			warnf('%s: status check failed: %s\n',lcon.mc_id,tostring(err))
			return
		end
		if status.timeout then
			warnf('%s: failed to end running script\n',lcon.mc_id)
			return
		end
	end

	local status,err = lcon:exec('mc.run('..util.serialize(opts)..')',{libs='multicam'})
	if not status then
		warnf('%s: load script failed: %s\n',lcon.mc_id,tostring(err))
	end
end
--[[
start the script on all cameras
]]
function mc:start(opts)
	for i,lcon in ipairs(self.cams) do
		self:start_single(lcon)
	end
end

function mc:check_errors()
	for i,lcon in ipairs(self.cams) do
		local msg,err=lcon:read_msg()
		if msg then
			if msg.type ~= 'none' then
				if msg.script_id ~= lcon:get_script_id() then
					warnf("%d: message from unexpected script %d %s\n",i,msg.script_id,chdku.format_script_msg(msg))
				elseif msg.type == 'user' then
					warnf("%d: unexpected user message %s\n",i,chdku.format_script_msg(msg))
				elseif msg.type == 'return' then
					warnf("%d: unexpected return message %s\n",i,chdku.format_script_msg(msg))
				elseif msg.type == 'error' then
					warnf('%d:%s\n',i,msg.value)
				else
					warnf("%d: unknown message type %s\n",i,tostring(msg.type))
				end
			end
		else
			warnf('%d:read_msg error %s\n',i,tostring(err))
		end
	end
end

function mc:init_sync_single(lcon,lt0,rt0)
	local ticks={}
	local sends={}
	--printf('lt0 %d rt0 %d\n',lt0,rt0)
	for i=1,10 do
		local tsend = ustime.new()
		local diff = ustime.diffms(lt0)
		local status,err=lcon:write_msg('tick')
		sends[i] = ustime.diffms(tsend)
		if status then
			local expect = rt0 + diff
			local status,msg=lcon:wait_msg({
					mtype='user',
					msubtype='table',
					munserialize=true,
			})
			if status then
				printf('%s: send %d diff %d pred=%d r=%d delta=%d\n',
					lcon.mc_id,
					sends[i],
					diff,
					expect,
					msg.status,
					expect-msg.status)
				table.insert(ticks,expect-msg.status)
			else
				warnf('sync_single wait_msg failed: %s\n',err)
			end
		else
			warnf('sync_single write_msg failed: %s\n',err)
		end
		sys.sleep(50) -- don't want messages to get queued
	end
-- average difference between predicted and returned time in test
-- large |value| implies initial from init_sync was an exteme
	local tickoff = util.table_amean(ticks)
-- msend average time to complete a send, accounts for a portion of latency
-- not clear what this includes, or how much is spent in each direction
	local msend = util.table_amean(sends)
	printf('%s: mean offset %f (%d)\n',lcon.mc_id,tickoff,#ticks)
	printf('%s: mean send %f (%d)\n',lcon.mc_id,msend,#sends)
	lcon.mc_sync = {
		lt0=lt0, -- base local time
		rt0=rt0, -- base remote time obtained at lt0 + latency
		tickoff=tickoff,
		msend=msend,
		-- adjusted base remote time 
		rtadj = rt0 - tickoff - msend/2,
	}
	--local t0=ustime.new()
	for i=1,10 do
		local expect = self:get_sync_tick(lcon,ustime.new(),100)
		local status,err=lcon:write_msg(string.format('synctick %d',expect))
		if status then
			local status,msg=lcon:wait_msg({
					mtype='user',
					msubtype='table',
					munserialize=true,
			})
			if status then
				printf('%s: expect=%d r=%d d=%d %s\n',
					lcon.mc_id,
					expect,
					msg.status,
					expect-msg.status,
					msg.msg)
			else
				warnf('%s: sync_single wait_msg failed: %s\n',lcon.mc_id,msg)
			end
		else
			warnf('%s: sync_single write_msg failed: %s\n',lcon.mc_id,err)
		end
		sys.sleep(50) -- don't want messages to get queued
	end
end
--[[
initialize values to allow all cameras to execute a given command as close as possible to the same real time
]]
function mc:init_sync()
	self.min_sync_delay = 0 -- minimum time required to send to all cams
	for i,lcon in ipairs(self.cams) do
		local t0=ustime.new()
		local status,err=lcon:write_msg('tick')
		if status then
			local status,msg=lcon:wait_msg({
				mtype='user',
				msubtype='table',
				munserialize=true,
			})
			if status then
				self:init_sync_single(lcon,t0,msg.status)
				-- TODO mean send time might not be enough
				self.min_sync_delay = self.min_sync_delay + lcon.mc_sync.msend 
			else
				warnf('%d:wait_msg failed: %s\n',i,tostring(msg))
			end
		else
			warnf('%d:write_msg failed: %s\n',i,tostring(err))
		end
	end
	printf('minimum sync delay %d\n',self.min_sync_delay)
end

function mc:get_single_status(lcon,cmd,r)
	local status,err = lcon:script_status()
	if not status then
		r.failed = true
		r.err = err
		return
	end
	if status.msg then
		local status,msg=lcon:read_msg_strict({
			mtype='user',
			msubtype='table',
			munserialize=true
		})
		if not status then
			r.failed = true
			r.err = msg
			return 
		end
		-- TODO it would be good to skip over any stale status messages
		if msg.cmd ~= cmd then
			r.failed = true
			r.err = 'status from unexpected cmd:'..tostring(msg.cmd)
		end
		r.done = true
		r.status = msg
		return
	elseif status.run == false then
		-- not running, no messages waiting
		r.failed = true
		r.err = 'script not running'
		return
	end
end
--[[
wait until all cameras have returned a status message for 'cmd' or timed out
]]
function mc:wait_status_msg(cmd,opts)
	opts = util.extend_table({
		timeout=10000,
		initwait=10,
		poll=250,
	},opts)
	if opts.initwait then
		sys.sleep(opts.initwait)
	end
	local results={}
	for i,lcon in ipairs(self.cams) do
		results[i] = {
			failed=false,
			done=false,
		}
	end
	local tstart=ustime.new()
	local tpoll=ustime.new()
	while true do
		local complete = 0
		tpoll:get()
		for i,lcon in ipairs(self.cams) do
			local r = results[i]
			if r.failed or r.done then
				complete = complete + 1
			else
				self:get_single_status(lcon,cmd,r)
			end
		end
		if complete == #self.cams then
			return true, results
		end
		if ustime.diffms(tstart) > opts.timeout then
			return false, results, 'timeout'
		end
		local poll = opts.poll - ustime.diffms(tpoll)
		if poll > 0 then
			sys.sleep(opts.poll)
		end
	end
end
--[[
get camera tick matching tstart + syncat
<camera base time> + <tstart - local base time> + syncat
]]
function mc:get_sync_tick(lcon,tstart,syncat)
	return lcon.mc_sync.rtadj + ustime.diffms(tstart,lcon.mc_sync.lt0) + syncat
end
function mc:flushmsgs()
	for i,lcon in ipairs(self.cams) do
		lcon:flushmsgs()
	end
end
--[[
send command
opts {
	wait=bool - expect / wait for status message
	arg=string
	flushmsgs=bool - flush any pending messages
	syncat=<ms> -- number of ms after now command should execute (TODO accept a ustime)
	--
}
if syncat is set, sends a synchronized command
to execute at approximately local issue time + syncat
command must accept a camera tick time as it's argument (e.g. shoot)
]]
function mc:cmd(cmd,opts)
	local tstart = ustime.new()
	opts=util.extend_table({},opts)
	if opts.flushmsgs then
		self:flushmsgs()
	end
	local sendcmd = cmd
	for i,lcon in ipairs(self.cams) do
		local status,err
		if opts.syncat then
			sendcmd = string.format('%s %d',cmd,self:get_sync_tick(lcon,tstart,opts.syncat))
		end
		local status,err = lcon:write_msg(sendcmd)
		printf('%s:%s\n',lcon.mc_id,sendcmd)
		if not status then
			warnf('%s: send %s cmd failed: %s\n',lcon.mc_id,tostring(sendcmd),tostring(err))
		end
	end
	if not opts.wait then
		return true
	end

	-- to match remote command name
	local cmdname=string.match(cmd,'^(%w+)')

	return self:wait_status_msg(cmdname,opts)
end

function mc:cmdwait(cmd,opts)
	opts = util.extend_table({wait=true},opts)
	return self:cmd(cmd,opts)
end

function mc:print_cmd_status(status,results)
	if status then
		printf("ok\n")
	else
		printf("errors\n")
	end
	if results then
		for i,v in ipairs(results) do
			printf('%d: %s\n',i,tostring(util.serialize(v,{pretty=true})))
		end
	end
end
function mc:testshots(opts) 
	opts = util.extend_table({ nshots=1 },opts)
	if not self.min_sync_delay then
		warnf('sync not initialized\n')
		return
	end
	self:flushmsgs()
	if not opts.synctime or opts.synctime < self.min_sync_delay then
		opts.synctime = self.min_sync_delay + 50
	end
	if opts.defexp then
		opts.tv = 768
		opts.sv = 672
	end
	local init_cmds = {}
	local init_cmd
	if opts.tv then
		table.insert(init_cmds,string.format('set_tv96_direct(%d)',opts.tv))
	end
	if opts.sv then
		table.insert(init_cmds,string.format('set_sv96(%d)',opts.sv))
	end
	if #init_cmds > 0 then
		init_cmd = 'call '..table.concat(init_cmds,';')
	end
	for i=1,opts.nshots do
		self:print_cmd_status(self:cmdwait('call return get_exp_count()'))
		if init_cmd then
			self:print_cmd_status(self:cmdwait(init_cmd))
		end
		self:print_cmd_status(self:cmdwait('preshoot'))
		local t=ustime.new()
		self:cmd('shoot',{syncat=opts.synctime})
		sys.sleep(opts.synctime - 60)
		for j=1,25 do
			printf('%d %d\n',i,ustime.diffms(t)-opts.synctime)
			sys.sleep(20)
		end
		self:print_cmd_status(self:wait_status_msg('shoot'))
		self:print_cmd_status(self:cmdwait('call return get_exp_count()'))
		sys.sleep(500)
	end
end

--[[
remote script
waits in a loop for messages
most commands return status with messages of the form
{
	cmd=<command name>
	status=<status|return value>
	msg=<error message>
}
commands
	rec: switch to record
	play: switch to playback
	preshoot: press shoot half and wait for get_shooting
	shoot [ms]: wait [ms], press shoot full, wait for get_shooting
	tick: return the value of get_tick_count
	exit: end script
]]
local function init()
	chdku.rlibs:register({
		name='multicam',
		depend={'extend_table','serialize_msgs'},
		code=[[
mc={
	mode_sw_timeout=1000,
	preshoot_timeout=5000,
	shoot_complete_timeout=5000,
	msg_timeout=100000,
	shoot_hold=10,
}

cmds={}

-- wait, sleeping <wait> ms until <func> returns <value> or timeout hit
function wait_timeout(func,value,wait,timeout,msg)
	if not msg then
		msg = 'timeout'
	end
	while func() ~= value do
		sleep(wait)
		timeout = timeout - wait
		if wait <= 0 then
			write_status(false,msg)
			return false
		end
	end
	write_status(true)
	return true
end

function write_status(status,msg)
	write_usb_msg({
		status=status,
		msg=msg,
		cmd=mc.cmd,
	},mc.status_msg_timeout)
end

function wait_tick(synctick)
	if synctick then
		-- current chdk builds sleep an extra 20ms on top of requested amount
		local s=synctick - get_tick_count() - 20
		if s >= 10 then
			sleep(s)
		end
	end
end

function cmds.rec()
	switch_mode_usb(1)
	return wait_timeout(get_mode,true,100,mc.mode_sw_timeout)
end
function cmds.play()
	switch_mode_usb(0)
	return wait_timeout(get_mode,false,100,mc.mode_sw_timeout)
end
function cmds.preshoot()
	press('shoot_half')
	local status=wait_timeout(get_shooting,true,10,mc.preshoot_timeout)
	if not status then
		release('shoot_half')
	end
	return status,msg
end

function cmds.shoot()
	wait_tick(tonumber(mc.args))
	press('shoot_full')
	sleep(mc.shoot_hold)
	release('shoot_full')
	return wait_timeout(get_shooting,false,100,mc.shoot_complete_timeout,'get_shooting timeout')
end

function cmds.tick()
	write_status(get_tick_count())
end

function cmds.synctick()
	t=get_tick_count()
	wait_tick(tonumber(mc.args))
	write_status(get_tick_count(),string.format('start %d',t))
end

function cmds.exit()
	mc.done = true
end

function cmds.call()
	local f,err=loadstring(mc.args)
	if f then 
		write_status({f()})
	else
		write_status(false,err)
	end
end

function cmds.pcall()
	local f,err=loadstring(mc.args)
	if f then 
		local r={pcall(f)}
		if not r[1] then
			write_status(false,r)
		else
			write_status(r)
		end
	else
		write_status(false,err)
	end
end

function mc.run(opts)
	extend_table(mc,opts)
	set_yield(-1,-1)
	repeat 
		local msg=read_usb_msg(mc.msg_timeout)
		if msg then
			mc.cmd,mc.args=string.match(msg,'^(%w+)%s*(.*)')
			if type(cmds[mc.cmd]) == 'function' then
				cmds[mc.cmd]()
			else
				write_status(false,'unknown')
			end
		end
	until mc.done
end
]]})
end
init()

return mc
