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
--]]

local cli = {
	cmds={},
	names={},
	finished = false,
	source_level = 0, -- number of nested execfile calls
}
--[[
info printf - message to be printed at normal verbosity
]]
cli.infomsg = util.make_msgf( function() return prefs.cli_verbose end, 1)
cli.dbgmsg = util.make_msgf( function() return prefs.cli_verbose end, 2)

--[[
get command args of the form -a[=value] -bar[=value] .. [wordarg1] [wordarg2] [wordarg...]
--]]
local argparser = { }
cli.argparser = argparser

-- trim leading spaces
function argparser:trimspace(str)
	local s, e = string.find(str,'^[%c%s]*')
	return string.sub(str,e+1)
end
--[[
get a 'word' argument, either a sequence of non-white space characters, or a quoted string
inside " \ is treated as an escape character
return word, end position on success or false, error message
]]
function argparser:get_word(str)
	local result = ''
	local esc = false
	local qchar = false
	local pos = 1
	while pos <= string.len(str) do
		local c = string.sub(str,pos,pos)
		-- in escape, append next character unconditionally
		if esc then
			result = result .. c
			esc = false
		-- inside double quote, start escape and discard backslash
		elseif qchar == '"' and c == '\\' then
			esc = true
		-- character is the current quote char, close quote and discard
		elseif c == qchar then
			qchar = false
		-- not hit a space and not inside a quote, end
		elseif not qchar and string.match(c,"[%c%s]") then
			break
		-- hit a quote and not inside a quote, enter quote and discard
		elseif not qchar and c == '"' or c == "'" then
			qchar = c
		-- anything else, copy
		else
			result = result .. c
		end
		pos = pos + 1
	end
	if esc then
		return false,"unexpected \\"
	end
	if qchar then
		return false,"unclosed " .. qchar
	end
	return result,pos
end

function argparser:parse_words(str)
	local words={}
	str = self:trimspace(str)
	while string.len(str) > 0 do
		local w,pos = self:get_word(str)
		if not w then
			return false,pos -- pos is error string
		end
		table.insert(words,w)
		str = string.sub(str,pos)
		str = self:trimspace(str)
	end
	return words
end

--[[
parse a command string into switches and word arguments
switches are in the form -swname[=value]
word arguments are anything else
any portion of the string may be quoted with '' or ""
inside "", \ is treated as an escape
on success returns table with args as array elements and switches as named elements
on failure returns false, error
defs defines the valid switches and their default values. Can also define default values of numeric args
TODO enforce switch values, number of args, integrate with help
]]
function argparser:parse(str)
	-- default values
	local results=util.extend_table({},self.defs)
	local words,errmsg=self:parse_words(str)
	if not words then
		return false,errmsg
	end
	for i, w in ipairs(words) do
		-- look for -name
		local s,e,swname=string.find(w,'^-(%a[%w_-]*)')
		-- found a switch
		if s then		
			if type(self.defs[swname]) == 'nil' then
				return false,'unknown switch '..swname
			end
			local swval
			-- no value
			if e == string.len(w) then
				swval = true
			elseif string.sub(w,e+1,e+1) == '=' then
				-- note, may be empty string but that's ok
				swval = string.sub(w,e+2)
			else
				return false,"invalid switch value "..string.sub(w,e+1)
			end
			results[swname]=swval
		else
			table.insert(results,w)
		end
	end
	return results
end

-- a default for comands that want the raw string
argparser.nop = {
	parse =function(self,str)
		return str
	end
}

function argparser.create(defs)
	local r={ defs=defs }
	return util.mt_inherit(r,argparser)
end

cli.cmd_proto = {
	get_help = function(self)
		local namestr = self.names[1]
		if #self.names > 1 then
			namestr = namestr .. " (" .. self.names[2]
			for i=3,#self.names do
				namestr = namestr .. "," .. self.names[i]
			end
			namestr = namestr .. ")"
		end
		return string.format("%-12s %-12s: - %s\n",namestr,self.arghelp,self.help)
	end,
	get_help_detail = function(self)
		local msg=self:get_help()
		if self.help_detail then
			msg = msg..self.help_detail..'\n'
		end
		return msg
	end,
}

cli.cmd_meta = {
	__index = function(cmd, key)
		return cli.cmd_proto[key]
	end,
	__call = function(cmd,...)
		return cmd:func(...)
	end,
}

function cli:add_commands(cmds)
	for i = 1, #cmds do
		cmd = cmds[i]
		table.insert(self.cmds,cmd)
		if not cmd.arghelp then
			cmd.arghelp = ''
		end
		if not cmd.args then
			cmd.args = argparser.nop
		end
		for _,name in ipairs(cmd.names) do
			if self.names[name] then
				warnf("duplicate command name %s\n",name)
			else
				self.names[name] = cmd
			end
		end
		setmetatable(cmd,cli.cmd_meta)
	end
end

function cli:prompt()
	if con:is_connected() then
		local script_id = con:get_script_id()
		if script_id then
			printf("con %d> ",script_id)
		else
			printf("con> ")
		end
	else
		printf("___> ")
	end
end

-- execute command given by a single line
-- returns status,message
-- message is an error message or printable value
function cli:execute(line)
	-- single char shortcuts
	local s,e,cmd = string.find(line,'^[%c%s]*([!.#=])[%c%s]*')
	if not cmd then
		s,e,cmd = string.find(line,'^[%c%s]*([%w_]+)[%c%s]*')
	end
	if s then
		local args = string.sub(line,e+1)
		if self.names[cmd] then
			local status,msg
			args,msg = self.names[cmd].args:parse(args)
			if not args then
				return false,msg
			end
			local cstatus
			local t0=ustime.new()
			con:reset_counters()
			cstatus,status,msg = xpcall(
				function()
					return self.names[cmd](args)
				end,
				util.err_traceback)
			local tdiff = ustime.diff(t0)/1000000;
			if prefs.cli_time then
				printf("time %.4f\n",tdiff)
			end
			if prefs.cli_xferstats then
				local xferstats = con:get_counters();
				local rbps,wbps
				if tdiff == 0 then
					rbps = "-"
					wbps = "-"
				else
					-- note these are based on total command execution time, not just transfer
					rbps = string.format("%d",xferstats.read/tdiff)
					wbps = string.format("%d",xferstats.write/tdiff)
				end
				printf("r %d %s/s w %d %s/s\n",xferstats.read,rbps,xferstats.write,wbps)
			end
			if not cstatus then
				return false,status
			end
			if not status and not msg then
				msg=cmd .. " failed"
			end
			return status,msg
		else 
			return false,string.format("unknown command '%s'\n",cmd)
		end
	elseif string.find(line,'[^%c%s]') then
		return false, string.format("bad input '%s'\n",line)
	end
	-- blank input is OK
	return true,""
end

function cli:execfile(filename) 
	if cli.source_level == prefs.cli_source_max then
		return false, 'too many nested source calls'
	end
	cli.source_level = cli.source_level + 1
	local fh, err = io.open(filename,'rb')
	if not fh then 
		return false, 'failed to open file: '..tostring(err)
	end
	-- empty file is OK
	local status = true
	local lnum = 1
	for line in fh:lines() do
		local msg
		status, msg = self:execute(line)
		self:print_status(status,msg)
		-- TODO pref to continue on errors
		if self.finished or not status then
			break
		end
		lnum = lnum + 1
	end
	fh:close()
	cli.source_level = cli.source_level - 1
	if not status then
		return false, string.format('error on line %d',lnum)
	end
	return true
end

function cli:print_status(status,msg) 
	if not status then
		errf("%s\n",tostring(msg))
	elseif msg and string.len(msg) ~= 0 then
		printf("%s",msg)
		if string.sub(msg,-1,-1) ~= '\n' then
			printf("\n")
		end
	end
	return status,msg
end

function cli:run()
	self:prompt()
	for line in io.lines() do
		self:print_status(self:execute(line))
		if self.finished then
			break
		end
		self:prompt()
	end
end

-- update gui for cli commands
-- TODO should be a generic event system
function cli:connection_status_change()
	if gui then
		gui.update_connection_status()
	end
end

function cli:mode_change()
	if gui then
		gui.update_mode_list()
	end
end

--[[
process options common to shoot and remoteshoot
]]
function cli:get_shoot_common_opts(args)
	if not con:is_connected() then
		return false, 'not connected'
	end
	if not util.in_table({'s','a','96'},args.u) then
		return false,"invalid units"
	end
	local opts={}
	if args.u == 's' then
		if args.av then
			opts.av=exp.f_to_av96(args.av)
		end
		if args.sv then
			opts.sv=exp.iso_to_sv96(args.sv)
		end
		if args.tv then
			local n,d = string.match(args.tv,'^([%d]+)/([%d.]+)$')
			if n then
				n = tonumber(n)
				d = tonumber(d)
				if not n or not d or n == 0 or d == 0 then
					return false, 'invalid tv fraction'
				end
				opts.tv = exp.shutter_to_tv96(n/d)
			else
				n = tonumber(args.tv)
				if not n then
					return false, 'invalid tv value'
				end
				opts.tv = exp.shutter_to_tv96(n)
			end
		end
	elseif args.u == 'a' then
		if args.av then
			opts.av = util.round(args.av*96)
		end
		if args.sv then
			opts.sv = util.round(args.sv*96)
		end
		if args.tv then
			opts.tv = util.round(args.tv*96)
		end
	else
		if args.av then
			opts.av=tonumber(args.av)
		end
		if args.sv then
			opts.sv=tonumber(args.sv)
		end
		if args.tv then
			opts.tv=tonumber(args.tv)
		end
	end
	if args.isomode then
		if opts.sv then
			return false,'set sv or isomode, not both!'
		end
		opts.isomode = tonumber(args.isomode)
	end
	if args.nd then
		local val = ({['in']=1,out=2})[args.nd]
		if not val then
			return false,'invalid ND state '..tostring(args.nd)
		end
		opts.nd = val
	end

	-- hack for CHDK override bug that ignores APEX 0
	-- only used for CHDK 1.1 (API 2.4 and earlier)
	if  opts.tv == 0 and not con:is_ver_compatible(2,5) then
		opts.tv = 1
	end
	return opts
end

cli:add_commands{
	{
		names={'help','h'},
		arghelp='[cmd]|[-v]',
		args=argparser.create{v=false},
		help='help on [cmd] or all commands',
		help_detail=[[
 help -v gives full help on all commands, otherwise as summary is printed
]],
		func=function(self,args) 
			cmd = args[1]
			if cmd and cli.names[cmd] then
				return true, cli.names[cmd]:get_help_detail()
			end
			if cmd then
				return false, string.format("unknown command '%s'\n",cmd)
			end
			msg = ""
			for i,c in ipairs(cli.cmds) do
				if args.v then
					msg = msg .. c:get_help_detail()
				else
					msg = msg .. c:get_help()
				end
			end
			return true, msg
		end,
	},
	{
		names={'#'},
		help='comment',
		func=function(self,args) 
			return true
		end,
	},
	{
		names={'exec','!'},
		help='execute local lua',
		arghelp='<lua code>',
		help_detail=[[
 Execute lua in chdkptp. 
 The global variable con accesses the current CLI connection.
 Return values are printed in the console.
]],
		func=function(self,args) 
			local f,r = loadstring(args)
			if f then
				r={xpcall(f,util.err_traceback)}
				if not r[1] then 
					return false, string.format("call failed:%s\n",r[2])
				end
				local s
				local sopts={pretty=true,err_type=false,err_cycle=false,forceint=false,fix_bignum=false}
				if #r > 1 then
					s='=' .. serialize(r[2],sopts)
					for i = 3, #r do
						s = s .. ',' .. serialize(r[i],sopts)
					end
				end
				return true, s
			else
				return false, string.format("compile failed:%s\n",r)
			end
		end,
	},
	{
		names={'set'},
		help='show or set option',
		arghelp='[-v|-c] [option[=value]]',
		args=argparser.create{
			v=false,
			c=false,
		},

		help_detail=[[
 Use set with no options to see a list
  -v show desciption when showing value
  -c output as set command
]],
		func=function(self,args) 
			local mode
			if args.v then
				mode='full'
			end
			if args.c then
				mode='cmd'
			end
			if #args == 0 then	
				local r={}
				for name,pref in prefs._each() do
					local status, desc = prefs._describe(name,mode)
					-- desc will be error if we somehow get invalid in here
					table.insert(r,desc)
				end
				return true,table.concat(r,'\n')
			end
			if #args > 1 then
				return false, 'unexpected args'
			end
			local name,value = string.match(args[1],'^([%a_][%w%a_]+)=(.*)$')
			if not name then
				return prefs._describe(args[1],mode)
			end
			return prefs._set(name,value)
		end,
	},
	{
		names={'quit','q'},
		help='quit program',
		func=function() 
			cli.finished = true
			return true,"bye"
		end,
	},
	{
		names={'source'},
		help='execute cli commands from file',
		arghelp='<file>',
		args=argparser.create{ },
		func=function(self,args) 
			return cli:execfile(args[1])
		end,
	},
	{
		names={'lua','.'},
		help='execute remote lua',
		arghelp='<lua code>',
		help_detail=[[
 Execute Lua code on the camera.
 Returns immediately after the script is started.
 Return values or error messages can be retrieved with getm after the script is completed.
]],
		func=function(self,args) 
			return con:exec(args)
		end,
	},
	{
		names={'getm'},
		help='get messages',
		func=function(self,args) 
			local msgs=''
			local msg,err
			while true do
				msg,err=con:read_msg()
				if type(msg) ~= 'table' then 
					return false,msgs..err
				end
				if msg.type == 'none' then
					return true,msgs
				end
				msgs = msgs .. chdku.format_script_msg(msg) .. "\n"
			end
		end,
	},
	{
		names={'putm'},
		help='send message',
		arghelp='<msg string>',
		func=function(self,args) 
			return con:write_msg(args)
		end,
	},
	{
		names={'luar','='},
		help='execute remote lua, wait for result',
		arghelp='<lua code>',
		help_detail=[[
 Execute Lua code on the camera, waiting for the script to end.
 Return values or error messages are printed after the script completes.
]],
		func=function(self,args) 
			local rets={}
			local msgs={}
			local status,err = con:execwait(args,{rets=rets,msgs=msgs})
			if not status then
				return false,err
			end
			local r=''
			for i=1,#msgs do
				r=r .. chdku.format_script_msg(msgs[i]) .. '\n'
			end
			for i=1,table.maxn(rets) do
				r=r .. chdku.format_script_msg(rets[i]) .. '\n'
			end
			return true,r
		end,
	},
	{
		names={'killscript'},
		help='kill running remote script',
		args=argparser.create{
			noflush=false,
			force=false,
		},
		arghelp='[-noflush][-force][-nowait]',
		help_detail=[[
 Terminate any runnings script on the camera
   -noflush: don't discard script messages
   -force: force kill even if camera does not support (crash / memory leaks likely!)
]],
		func=function(self,args) 
			if not con:is_ver_compatible(2,6) then
				if not args.force then
					return false,'camera does not support clean kill, use -force if you are sure'
				end
				warnf("camera does not support clean kill, crashes likely\n")
			end
			-- execute an empty script with kill options set
			-- wait ensures it will be all done
			local flushmsgs = not args.noflush;
			local status,err = con:exec("",{
					flush_cam_msgs=flushmsgs,
					flush_host_msgs=flushmsgs,
					clobber=true})
			if not status then
				return false, err
			end
			-- use standalone wait_status because we don't want execwait message handling
			status, err = con:wait_status{run=false}
			if not status then
				return false, err
			end
			return true
		end,
	},
	{
		names={'rmem'},
		help='read memory',
		args=argparser.create{i32=false}, -- word
		arghelp='<address> [count] [-i32[=fmt]]',
		help_detail=[[
 Dump <count> bytes or words starting at <address>
  -i32 display as 32 bit words rather than byte oriented hex dump
  -i32=<fmt> use printf format string fmt to display
]],
		func=function(self,args) 
			local addr = tonumber(args[1])
			local count = tonumber(args[2])
			if not addr then
				return false, "bad args"
			end
			if not count then
				count = 1
			end
			if args.i32 then
				count = count * 4
			end

			local r,msg = con:getmem(addr,count)
			if not r then
				return false,msg
			end

			if args.i32 then
				local fmt
				if type(args.i32) == 'string' then
					fmt = args.i32
				end
				r=util.hexdump_words(r,addr,fmt)
			else
				r=util.hexdump(r,addr)
			end
			return true, string.format("0x%08x %u\n",addr,count)..r
		end,
	},
	{
		names={'list'},
		help='list devices',
		help_detail=[[
 Lists all recognized PTP devices in the following format on success
  <status><num>:<modelname> b=<bus> d=<device> v=<usb vendor> p=<usb pid> s=<serial number>
 or on error
  <status><num> b=<bus> d=<device> ERROR: <error message>
 status values
  * connected, current target for CLI commands (con global variable)
  + connected, not CLI target
  - not connected
  ! error querying status
 serial numbers are not available from all models
]],
		func=function() 
			local msg = ''
			-- TODO usb only, will not show connected PTP/IP
			local devs = chdk.list_usb_devices()
			for i,desc in ipairs(devs) do
				local lcon = chdku.connection(desc)
				local tempcon = false
				local con_status = "+"
				local status,err
				if not lcon:is_connected() then
					tempcon = true
					con_status = "-"
					status,err = lcon:connect()
				else
					-- existing con wrapped in new object won't have info set
					status,err = lcon:update_connection_info()
				end

				if status then
					if con_status == '+' and lcon._con == con._con then
						con_status = "*"
					end

					msg = msg .. string.format("%s%d:%s b=%s d=%s v=0x%x p=0x%x s=%s\n",
												con_status, i,
												tostring(lcon.ptpdev.model),
												lcon.condev.bus, lcon.condev.dev,
												tostring(lcon.condev.vendor_id),
												tostring(lcon.condev.product_id),
												tostring(lcon.ptpdev.serial_number))
				else
					-- use the requested dev/bus here, since the lcon data may not be set
					msg = msg .. string.format('!%d: b=%s d=%s ERROR: %s\n',i,desc.bus, desc.dev,tostring(err))
				end
				if tempcon then
					lcon:disconnect()
				end
			end
			return true,msg
		end,
	},
	{
		names={'upload','u'},
		help='upload a file to the camera',
		arghelp="[-nolua] <local> [remote]",
		args=argparser.create{nolua=false},
		help_detail=[[
 <local>  file to upload
 [remote] destination
   If not specified, file is uploaded to A/
   If remote is a directory or ends in / uploaded to remote/<local file name>
 -nolua   skip lua based checks on remote
   Allows upload while running script
   Prevents detecting if remote is a directory
 Some cameras have problems with paths > 32 characters
 Dryos cameras do not handle non 8.3 filenames well
]],
		func=function(self,args) 
			local src = args[1]
			if not src then
				return false, "missing source"
			end
			if lfs.attributes(src,'mode') ~= 'file' then
				return false, 'src is not a file: '..src
			end

			local dst_dir
			local dst = args[2]
			-- no dst, use filename of source
			if dst then
				dst = fsutil.make_camera_path(dst)
				if string.find(dst,'[\\/]$') then
					-- trailing slash, append filename of source
					dst = string.sub(dst,1,-2)
					if not args.nolua then
						local st,err = con:stat(dst)
						if not st then
							return false, 'stat dest '..dst..' failed: ' .. err
						end
						if not st.is_dir then
							return false, 'not a directory: '..dst
						end
					end
					dst = fsutil.joinpath(dst,fsutil.basename(src))
				else
					if not args.nolua then
						local st = con:stat(dst)
						if st and st.is_dir then
							dst = fsutil.joinpath(dst,fsutil.basename(src))
						end
					end
				end
			else
				dst = fsutil.make_camera_path(fsutil.basename(src))
			end

			local msg=string.format("%s->%s\n",src,dst)
			local r, msg2 = con:upload(src,dst)
			if msg2 then
				msg = msg .. msg2
			end
			return r, msg
		end,
	},
	{
		names={'download','d'},
		help='download a file from the camera',
		arghelp="[-nolua] <remote> [local]",
		args=argparser.create{nolua=false},
		help_detail=[[
 <remote> file to download
 	A/ is prepended if not present
 [local]  destination
   If not specified, the file will be downloaded to the current directory
   If a directory, the file will be downloaded into it
 -nolua   skip lua based checks on remote
   Allows download while running script
]],

		func=function(self,args) 
			local src = args[1]
			if not src then
				return false, "missing source"
			end
			local dst = args[2]
			if not dst then
				-- no dest, use final component of source path
				dst = fsutil.basename(src)
			elseif string.match(dst,'[\\/]+$') then
				-- explicit / treat it as a directory
				dst = fsutil.joinpath(dst,fsutil.basename(src))
				-- and check if it is
				local dst_dir = fsutil.dirname(dst)
				-- TODO should create it
				if lfs.attributes(dst_dir,'mode') ~= 'directory' then
					return false,'not a directory: '..dst_dir
				end
			elseif lfs.attributes(dst,'mode') == 'directory' then
				-- if target is a directory download into it
				dst = fsutil.joinpath(dst,fsutil.basename(src))
			end

			src = fsutil.make_camera_path(src)
			if not args.nolua then
				local src_st,err = con:stat(src)
				if not src_st then
					return false, 'stat source '..src..' failed: ' .. err
				end
				if not src_st.is_file then
					return false, src..' is not a file'
				end
			end
			local msg=string.format("%s->%s\n",src,dst)
			local r, msg2 = con:download(src,dst)
			if msg2 then
				msg = msg .. msg2
			end
			return r, msg
		end,
	},
	{
		names={'mdownload','mdl'},
		help='download file/directories from the camera',
		arghelp="[options] <remote, remote, ...> <target dir>",
		args=argparser.create{
			fmatch=false,
			dmatch=false,
			rmatch=false,
			nodirs=false,
			maxdepth=100,
			pretend=false,
			nomtime=false,
			batchsize=20,
			dbgmem=false,
			overwrite='y',
		},
		help_detail=[[
 <remote...> files/directories to download
 <target dir> directory to download into
 options:
   -fmatch=<pattern> download only file with path/name matching <pattern>
   -dmatch=<pattern> only create directories with path/name matching <pattern>
   -rmatch=<pattern> only recurse into directories with path/name matching <pattern>
   -nodirs           only create directories needed to download file  
   -maxdepth=n       only recurse into N levels of directory
   -pretend          print actions instead of doing them
   -nomtime          don't preserve modification time of remote files
   -batchsize=n      lower = slower, less memory used
   -dbgmem           print memory usage info
   -overwrite=<str>  overwrite existing files (y|n|old)
 note <pattern> is a lua pattern, not a filesystem glob like *.JPG
]],

		func=function(self,args) 
			if #args < 2 then
				return false,'expected source(s) and destination'
			end
			local dst=table.remove(args)
			local srcs={}
			for i,v in ipairs(args) do
				srcs[i]=fsutil.make_camera_path(v)
			end
			-- TODO some of these need translating, so can't pass direct
			local opts={
				fmatch=args.fmatch,
				dmatch=args.dmatch,
				rmatch=args.rmatch,
				dirs=not args.nodirs,
				maxdepth=tonumber(args.maxdepth),
				pretend=args.pretend,
				mtime=not args.nomtime,
				batchsize=tonumber(args.batchsize),
				dbgmem=args.dbgmem,
			}

			local overwrite_opts={
				n=false,
				y=true,
				old=function(lcon,lopts,finfo,st,src,dst)
--					local tr = chdku.ts_cam2pc(finfo.st.mtime)
--					printf("remote %s local %s\n",os.date('%c',tr),os.date('%c',st.modification))
					return chdku.ts_cam2pc(finfo.st.mtime) > st.modification
				end,
			}
			if type(args.overwrite) == 'string' then
				local ow = overwrite_opts[args.overwrite]
				if ow == nil then
					return false,'unrecognized overwrite option '..args.overwrite
				end
				opts.overwrite = ow
			else
				return false,'unrecognized overwrite option '..tostring(args.overwrite)
			end
			return con:mdownload(srcs,dst,opts)
		end,
	},
	{
		names={'mupload','mup'},
		help='upload file/directories to the camera',
		arghelp="[options] <local, local, ...> <target dir>",
		args=argparser.create{
			fmatch=false,
			dmatch=false,
			rmatch=false,
			nodirs=false,
			maxdepth=100,
			pretend=false,
			nomtime=false,
		},
		help_detail=[[
 <local...> files/directories to upload
 <target dir> directory to upload into
 options:
   -fmatch=<pattern> upload only file with path/name matching <pattern>
   -dmatch=<pattern> only create directories with path/name matching <pattern>
   -rmatch=<pattern> only recurse into directories with path/name matching <pattern>
   -nodirs           only create directories needed to upload file 
   -maxdepth=n       only recurse into N levels of directory
   -pretend          print actions instead of doing them
   -nomtime          don't preserve local modification time
 note <pattern> is a lua pattern, not a filesystem glob like *.JPG
]],

		func=function(self,args) 
			if #args < 2 then
				return false,'expected source(s) and destination'
			end
			local dst=fsutil.make_camera_path(table.remove(args))
			local srcs={}
			-- args has other stuff in it, copy array parts
			srcs={unpack(args)}
			-- TODO some of these need translating, so can't pass direct
			local opts={
				fmatch=args.fmatch,
				dmatch=args.dmatch,
				rmatch=args.rmatch,
				dirs=not args.nodirs,
				maxdepth=tonumber(args.maxdepth),
				pretend=args.pretend,
				mtime=not args.nomtime,
			}
			return con:mupload(srcs,dst,opts)
		end,
	},
	{
		names={'delete','rm'},
		help='delete file/directories from the camera',
		arghelp="[options] <target, target,...>",
		args=argparser.create{
			fmatch=false,
			dmatch=false,
			rmatch=false,
			nodirs=false,
			maxdepth=100,
			pretend=false,
			ignore_errors=false,
			skip_topdirs=false,
		},
		help_detail=[[
 <target...> files/directories to remote
 options:
   -fmatch=<pattern> upload only file with names matching <pattern>
   -dmatch=<pattern> only delete directories with names matching <pattern>
   -rmatch=<pattern> only recurse into directories with names matching <pattern>
   -nodirs           don't delete drictories recursed into, only files
   -maxdepth=n       only recurse into N levels of directory
   -pretend          print actions instead of doing them
   -ignore_errors    don't abort if delete fails, continue to next item
   -skip_topdirs     don't delete directories given in command line, only contents
 note <pattern> is a lua pattern, not a filesystem glob like *.JPG
]],

		func=function(self,args) 
			if #args < 1 then
				return false,'expected at least one target'
			end
			-- args has other stuff in it, copy array parts
			local tgts={}
			for i,v in ipairs(args) do
				tgts[i]=fsutil.make_camera_path(v)
			end
			-- TODO some of these need translating, so can't pass direct
			local opts={
				fmatch=args.fmatch,
				dmatch=args.dmatch,
				rmatch=args.rmatch,
				dirs=not args.nodirs,
				maxdepth=tonumber(args.maxdepth),
				pretend=args.pretend,
				ignore_errors=args.ignore_errors,
				skip_topdirs=args.skip_topdirs,
			}
			-- TODO use msg_handler to print as they are deleted instead of all at the end
			local results,err = con:mdelete(tgts,opts)
			if not results then
				return false,err
			end
			for i,v in ipairs(results) do
				-- TODO success should not be displayed at low verbosity
				printf("%s: ",v.file)
				if v.status then
					printf('OK')
				else
					printf('FAILED')
				end
				if v.msg then
					printf(": %s",v.msg)
				end
				printf('\n')
			end
			return true
		end,
	},
	{
		names={'mkdir'},
		help='create directories on camera',
		arghelp="<directory>",
		args=argparser.create{ },
		help_detail=[[
 <directory> directory to create. Intermediate directories will be created as needed
]],
		func=function(self,args)
			if #args ~= 1 then
				return false,'expected exactly one arg'
			end
			return con:mkdir_m(fsutil.make_camera_path(args[1]))
		end
	},
	{
		names={'version','ver'},
		help='print API and program versions',
		args=argparser.create{ p=false},
		arghelp="[-p]",
		help_detail=[[
 -p print program version
]],
		func=function(self,args) 
			local host_ver = string.format("host:%d.%d cam:",chdku.apiver.MAJOR,chdku.apiver.MINOR)
			local status = true
			local r
			if con:is_connected() then
				-- TODO could just use con cached versions
				local cam_major, cam_minor = con:camera_api_version()
				if cam_major then
					r = host_ver .. string.format("%d.%d",cam_major,cam_minor)
				else
					status = false
					r =  host_ver .. string.format("error %s",cam_minor)
				end 
			else
				r = host_ver .. "not connected"
			end
			if args.p then
				r = string.format('chdkptp %d.%d.%d-%s built %s %s\n%s',
									chdku.ver.MAJOR,chdku.ver.MINOR,chdku.ver.BUILD,chdku.ver.DESC,
									chdku.ver.DATE,chdku.ver.TIME,r)
			end
			return status,r
		end,
	},
	{
		names={'connect','c'},
		help='connect to device',
		arghelp="[-b=<bus>] [-d=<dev>] [-p=<pid>] [-s=<serial>] [model] | -h=host [-p=port]",
		args=argparser.create{
			b='.*',
			d='.*',
			p=false,
			s=false,
			h=false,
		},
		
		help_detail=[[
 If no options are given, connects to the first available device.
 <pid> is the USB product ID, as a decimal or hexadecimal number.
 All other options are treated as a Lua pattern. For alphanumerics, this is a case sensitive substring match.
 If the serial or model are specified, a temporary connection will be made to each device
 If <model> includes spaces, it must be quoted.
 If multiple devices match, the first matching device will be connected.
]],
		func=function(self,args) 
			local match = {}
			local opt_map = {
				b='bus',
				d='dev',
				p='product_id',
				s='serial_number',
				[1]='model',
			}
			for k,v in pairs(opt_map) do
				-- TODO matches expect nil
				if type(args[k]) == 'string' then
					match[v] = args[k]
				end
--				printf('%s=%s\n',v,tostring(args[k]))
			end

			if con:is_connected() then
				con:disconnect()
			end

			-- ptp/ip ignore other options
			-- TODO should warn
			local lcon
			if args.h then
				if not args.p then
					args.p = nil
				end
				lcon = chdku.connection({host=args.h,port=args.p})
			else
				if match.product_id and not tonumber(match.product_id) then
					return false,"expected number for product id"
				end
				local devices = chdk.list_usb_devices()
				for i, devinfo in ipairs(devices) do
					lcon = nil
					if chdku.match_device(devinfo,match) then
						lcon = chdku.connection(devinfo)
						-- if we are looking for model or serial, need to connect to the dev to check
						if match.model or match.serial_number then
							local tempcon = false
							cli.dbgmsg('model check %s %s\n',tostring(match.model),tostring(match.serial_number))
							if not lcon:is_connected() then
								lcon:connect()
								tempcon = true
							else
								lcon:update_connection_info()
							end
							if not lcon:match_ptp_info(match) then
								if tempcon then
									lcon:disconnect()
								end
								lcon = nil
							end
						end
						if lcon then
							break
						end
					end
				end
			end
			local status, err
			if lcon then
				con = lcon
				if not con:is_connected() then
					status, err = con:connect()
				end
				if con:is_connected() then
					cli.infomsg('connected: %s, max packet size %d\n',con.ptpdev.model,con.ptpdev.max_packet_size)
					status = true
				end
			else 
				status = false
				err = "no matching devices found"
			end
			cli:connection_status_change()
			return status,err
		end,
	},
	{
		names={'reconnect','r'},
		help='reconnect to current device',
		-- NOTE camera may connect to a different device,
		-- will detect and fail if serial, model or pid don't match
		func=function(self,args) 
			local status, err = con:reconnect()
			cli:connection_status_change()
			return status,err
		end,
	},
	{
		names={'disconnect','dis'},
		help='disconnect from device',
		func=function(self,args) 
			local status, err = con:disconnect()
			cli:connection_status_change()
			return status,err
		end,
	},
	{
		names={'ls'},
		help='list files/directories on camera',
		args=argparser.create{l=false},
		arghelp="[-l] [path]",
		func=function(self,args) 
			local listops
			local path=args[1]
			path = fsutil.make_camera_path(path)
			if args.l then
				listopts = { stat='*' }
			else
				listopts = { stat='/' }
			end
			listopts.dirsonly=false
			local list,msg = con:listdir(path,listopts)
			if type(list) == 'table' then
				local r = ''
				if args.l then
					-- alphabetic sort TODO sorting/grouping options
					chdku.sortdir_stat(list)
					for i,st in ipairs(list) do
						local name = st.name
						local size = st.size
						if st.is_dir then
							name = name..'/'
							size = '<dir>'
						else
						end
						r = r .. string.format("%s %10s %s\n",os.date('%c',chdku.ts_cam2pc(st.mtime)),tostring(size),name)
					end
				else
					table.sort(list)
					for i,name in ipairs(list) do
						r = r .. name .. '\n'
					end
				end

				return true,r
			end
			return false,msg
		end,
	},
	{
		names={'reboot'},
		help='reboot the camera',
		arghelp="[options] [file]",
		args=argparser.create({
			wait=3500,
			norecon=false,
		}),
		help_detail=[[
 file: Optional file to boot.
  Must be an unencoded binary or for DryOS only, an encoded .FI2
  Format is assumed based on extension
  If not set, firmware boots normally, loading diskboot.bin if configured
 options:
   -norecon  don't try to reconnect
   -wait=<N> wait N ms before attempting to reconnect, default 3500
]],
		func=function(self,args) 
			local bootfile=args[1]
			if bootfile then
				bootfile = fsutil.make_camera_path(bootfile)
				bootfile = string.format("'%s'",bootfile)
			else
				bootfile = ''
			end
			-- sleep and disconnect to avoid later connection problems on some cameras
			-- clobber because we don't care about memory leaks
			local status,err=con:exec('sleep(1000);reboot('..bootfile..')',{clobber=true})
			if not status then
				return false,err
			end
			if args.norecon then
				return true
			end
			return con:reconnect({wait=args.wait})
		end,
	},
	{
		names={'dumpframes'},
		help='dump camera display frames to file',
		arghelp="[options] [file]",
		args=argparser.create({
			count=5,
			wait=100,
			novp=false,
			nobm=false,
			nopal=false,
			quiet=false,
		}),
		help_detail=[[
 file: optional output file name, defaults to chdk_<pid>_<date>_<time>.lvdump
 options:
   -count=<N> number of frames to dump
   -wait=<N>  wait N ms between frames
   -novp      don't get viewfinder data
   -nobm      don't get ui overlay data
   -nopal     don't get palette for ui overlay
   -quiet     don't print progress
]],
		func=function(self,args) 
			local dumpfile=args[1]
			local what = 0
			if not args.novp then
				what = 1
			end
			if not args.nobm then
				what = what + 4
				if not args.nopal then
					what = what + 8
				end
			end
			if what == 0 then
				return false,'nothing selected'
			end
			local status,err
			if not con:live_is_api_compatible() then
				return false,'incompatible api'
			end
			status, err = con:live_dump_start(dumpfile)
			if not status then
				return false,err
			end
			for i=1,args.count do
				if not args.quiet then
					printf('grabbing frame %d\n',i)
				end
				status, err = con:live_get_frame(what)
				if not status then
					break
				end
				status, err = con:live_dump_frame()
				if not status then
					break
				end
				sys.sleep(args.wait)
			end
			con:live_dump_end()
			if status then
				err = string.format('%d bytes recorded to %s\n',tonumber(con.live.dump_size),tostring(con.live.dump_fn))
			end
			return status,err
		end,
	},
	{
		names={'shoot'},
		help='shoot a picture with specified exposure',
		arghelp="[options]",
		args=argparser.create({
			u='s',
			tv=false,
			sv=false,
			av=false,
			isomode=false,
			nd=false,
			raw=false,
			dng=false,
			pretend=false,
			nowait=false,
			dl=false,
			rm=false,
		}),
		-- TODO allow setting destinations and filetypes for -dl
		help_detail=[[
 options:
   -u=<s|a|96>
      s   standard units (default)
      a   APEX
      96  APEX*96
   -tv=<v>    shutter speed. In standard units both decimal and X/Y accepted
   -sv=<v>    ISO value. In standard units, Canon "real" ISO
   -av=<v>    Aperature value. In standard units, f number
   -isomode=<v> ISO mode, must be ISO value in Canon UI, shooting mode must have manual ISO
   -nd=<in|out> set ND filter state
   -raw[=1|0] Force raw on or off, defaults to current camera setting
   -dng[=1|0] Force DNG on or off, implies raw if on, default current camera setting
   -pretend   print actions instead of running them
   -nowait    don't wait for shot to complete
   -dl        download shot file(s)
   -rm        remove file after shooting
  Any exposure paramters not set use camera defaults
]],
		func=function(self,args) 
			local opts,err = cli:get_shoot_common_opts(args)
			if not opts then
				return false,err
			end
			-- allow -dng
			if args.dng == true then
				args.dng = 1
			end
			if args.dng then
				opts.dng = tonumber(args.dng)
				if opts.dng == 1 then
					-- force raw on if dng. TODO complain if raw/dng mismatch?
					args.raw = 1
				end
			end
			-- allow -raw to turn raw on
			if args.raw == true then
				args.raw=1
			end
			if args.raw then
				opts.raw=tonumber(args.raw)
			end
			if args.rm or args.dl then
				if args.nowait then
					return false, "can't download or remove with nowait"
				end
				opts.info=true
			end
			local cmd=string.format('rlib_shoot(%s)',util.serialize(opts))
			if args.pretend then
				return true,cmd
			end
			if args.nowait then
				return con:exec(cmd,{libs={'rlib_shoot'}})
			end

			local status,rstatus,rerr = con:execwait('return '..cmd,{libs={'serialize_msgs','rlib_shoot'}})

			if not status then
				return false,rstatus
			end
			if not rstatus then
				return false, rerr
			end
			if not (args.dl or args.rm) then
				return true
			end

			local info = rstatus

			local jpg_path = string.format('%s/IMG_%04d.JPG',info.dir,info.exp)
			local raw_path

			if info.raw then
				-- TODO
				-- get_config_value only returns indexes
				-- chdk versions might change these
				local pfx_list = {[0]="IMG", "CRW", "SND"}
				local ext_list = {[0]="JPG", "CRW", "CR2", "THM", "WAV"}
				local raw_dir
				local raw_ext
				local raw_pfx
				if info.raw_in_dir then
					raw_dir = info.dir
				else
					raw_dir = 'A/DCIM/100CANON'
				end
				if info.dng and info.use_dng_ext then
					raw_ext = 'DNG'
				else
					raw_ext = ext_list[info.raw_ext]
					if not raw_ext then
						raw_ext = 'RAW'
					end
				end
				raw_pfx = pfx_list[info.raw_pfx]
				if not raw_pfx then
					raw_pfx = 'RAW_'
				end
				raw_path = string.format('%s/%s_%04d.%s',raw_dir,raw_pfx,info.exp,raw_ext)
			end
			-- TODO some delay may be required between shot and dl start
			if args.dl then
				cli:print_status(cli:execute('download '..jpg_path))
				if raw_path then
					cli:print_status(cli:execute('download '..raw_path))
				end
			end
			if args.rm then
				cli:print_status(cli:execute('rm -maxdepth=0 '..jpg_path))
				if raw_path then
					cli:print_status(cli:execute('rm -maxdepth=0 '..raw_path))
				end
			end
			return true
		end,
	},
	-- TODO this should be combined with the shoot command,
	-- or at least make the syntax / options consistent
	{
		names={'remoteshoot','rs'},
		help='shoot and download without saving to SD (requires CHDK 1.2)',
		arghelp="[local] [options]",
		args=argparser.create{
			u='s',
			tv=false,
			sv=false,
			av=false,
			isomode=false,
			nd=false,
			jpg=false,
			raw=false,
			dng=false,
			dnghdr=false,
			s=false,
			c=false,
			cont=false,
			badpix=false,
		},
		help_detail=[[
 [local]       local destination directory or filename (w/o extension!)
 options:
   -u=<s|a|96>
      s   standard units (default)
      a   APEX
      96  APEX*96
   -tv=<v>    shutter speed. In standard units both decimal and X/Y accepted
   -sv=<v>    ISO value. In standard units, Canon "real" ISO
   -av=<v>    Aperature value. In standard units, f number
   -isomode=<v> ISO mode, must be ISO value in Canon UI, shooting mode must have manual ISO
   -nd=<in|out> set ND filter state
   -jpg         jpeg, default if no other options (not supported on all cams)
   -raw         framebuffer dump raw
   -dng         DNG format raw
   -dnghdr      save DNG header to a seperate file, ignored with -dng
   -s=<start>   first line of for subimage raw
   -c=<count>   number of lines for subimage
   -cont=<num>  shoot num shots in continuous mode
   -badpix[=n]  interpolate over pixels with value <= n, default 0, (dng only)
]],
		func=function(self,args)
			local dst = args[1]
			local dst_dir
			if dst then
				if string.match(dst,'[\\/]+$') then
					-- explicit / treat it as a directory
					-- and check if it is
					dst_dir = string.sub(dst,1,-2)
					if lfs.attributes(dst_dir,'mode') ~= 'directory' then
						cli.dbgmsg('mkdir %s\n',dst_dir)
						local status,err = fsutil.mkdir_m(dst_dir)
						if not status then
							return false,err
						end
					end
					dst = nil
				elseif lfs.attributes(dst,'mode') == 'directory' then
					dst_dir = dst
					dst = nil
				end
			end

			local opts,err = cli:get_shoot_common_opts(args)
			if not opts then
				return false,err
			end

			util.extend_table(opts,{
				fformat=0,
				lstart=0,
				lcount=0,
			})
			-- fformat required for init
			if args.jpg then
				opts.fformat = opts.fformat + 1
			end
			if args.dng then
				opts.fformat = opts.fformat + 6
			else
				if args.raw then
					opts.fformat = opts.fformat + 2
				end
				if args.dnghdr then
					opts.fformat = opts.fformat + 4
				end
			end
			-- default to jpeg TODO won't be supported on cams without raw hook
			if opts.fformat == 0 then
				opts.fformat = 1
				args.jpg = true
			end

			if args.badpix and not args.dng then
				util.warnf('badpix without dng ignored\n')
			end

			if args.s or args.c then
				if args.dng or args.raw then
					if args.s then
						opts.lstart = tonumber(args.s)
					end
					if args.c then
						opts.lcount = tonumber(args.c)
					end
				else
					util.warnf('subimage without raw ignored\n')
				end
			end
			if args.cont then
				opts.cont = tonumber(args.cont)
			end
			local opts_s = serialize(opts)
			cli.dbgmsg('rs_init\n')
			local status,rstatus,rerr = con:execwait('return rs_init('..opts_s..')',{libs={'rs_shoot_init'}})
			if not status then
				return false,rstatus
			end
			if not rstatus then
				return false,rerr
			end

			cli.dbgmsg('rs_shoot\n')
			-- TODO script errors will not get picked up here
			local status,err = con:exec('rs_shoot('..opts_s..')',{libs={'rs_shoot'}})
			-- rs_shoot should not initialize remotecap if there's an error, so no need to uninit
			if not status then
				return false,err
			end

			local rcopts={}
			if args.jpg then
				rcopts.jpg=chdku.rc_handler_file(dst_dir,dst)
			end
			if args.dng then
				if args.badpix == true then
					args.badpix = 0
				end
				local dng_info = {
					lstart=opts.lstart,
					lcount=opts.lcount,
					badpix=args.badpix,
				}
				rcopts.dng_hdr = chdku.rc_handler_store(function(chunk) dng_info.hdr=chunk.data end)
				rcopts.raw = chdku.rc_handler_raw_dng_file(dst_dir,dst,'dng',dng_info)
			else
				if args.raw then
					rcopts.raw=chdku.rc_handler_file(dst_dir,dst)
				end
				if args.dnghdr then
					rcopts.dng_hdr=chdku.rc_handler_file(dst_dir,dst)
				end
			end

			local nshots
			-- TOOO add options for repeated shots not in cont mode
			if opts.cont then
				shot_count = opts.cont
			else
				shot_count = 1
			end
			local status,err
			local shot = 1
			repeat 
				cli.dbgmsg('get data %d\n',shot)
				status,err = con:capture_get_data(rcopts)
				if not status then
					warnf('capture_get_data error %s\n',tostring(err))
					break
				end
				shot = shot + 1
			until shot > shot_count or not status
			if opts.cont and not status then
				cli.dbgmsg('sending stop message\n')
				con:write_msg('stop')
			end

			local t0=ustime.new()
			-- wait for shot script to end or timeout
			local wstatus,werr=con:wait_status{
				run=false,
				timeout=30000,
			}
			if not wstatus then
				warnf('error waiting for shot script %s\n',tostring(werr))
			elseif wstatus.timeout then
				warnf('timed out waiting for shot script\n')
			end
			cli.dbgmsg("script wait time %.4f\n",ustime.diff(t0)/1000000)

			local ustatus, uerr = con:exec('init_usb_capture(0)') -- try to uninit
			-- if uninit failed, combine with previous status
			if not ustatus then
				uerr = 'uninit '..tostring(uerr)
				status = false
				if err then
					err = err .. ' ' .. uerr
				else 
					err = uerr
				end
			end
			return status, err
		end,
	},
	{
		names={'rec'},
		help='switch camera to shooting mode',
		func=function(self,args) 
			local status,rstatus,rerr = con:execwait([[
if not get_mode() then
	switch_mode_usb(1)
	local i=0
	while not get_mode() and i < 300 do
		sleep(10)
		i=i+1
	end
	if not get_mode() then
		return false, 'switch failed'
	end
	return true
end
return false,'already in rec'
]])
			cli:mode_change()
			if not status then
				return false,rstatus
			end
			return rstatus,rerr
		end,
	},
	{
		names={'play'},
		help='switch camera to playback mode',
		func=function(self,args) 
			local status,rstatus,rerr = con:execwait([[
if get_mode() then
	switch_mode_usb(0)
	local i=0
	while get_mode() and i < 300 do
		sleep(10)
		i=i+1
	end
	if get_mode() then
		return false, 'switch failed'
	end
	return true
end
return false,'already in play'
]])
			cli:mode_change()
			if not status then
				return false,rstatus
			end
			return rstatus,rerr
		end,
	},
}

prefs._add('cli_time','boolean','show cli execution times')
prefs._add('cli_xferstats','boolean','show cli data transfer stats')
prefs._add('cli_verbose','number','control verbosity of cli',1)
prefs._add('cli_source_max','number','max nested source calls',10)
return cli
