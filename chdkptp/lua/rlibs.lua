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
simple library system for building remote commands
chunks of source code to be used remotely
can be used with chdku.exec
TODO some of these are duplicated with local code, but we don't yet have an easy way of sharing them
should allow loading rlib source from local files
TODO would be good to minify
TODO passing compiled chunks might be better but our lua configurations are different
]]
local rlibs = {
	libs={},
}
--[[
register{
	name='libname'
	depend='lib'|{'lib1','lib2'...}, -- already registered rlibs this one requires (cyclic deps not allowed)
	code='', -- main lib code.
}
]]
function rlibs:register(t)
	-- for convenience, single lib may be given as string
	if type(t.depend) == 'string' then
		t.depend = {t.depend}
	elseif type(t.depend) == 'nil' then
		t.depend = {}
	elseif type(t.depend) ~= 'table' then
		error('expected dependency table or string')
	end
	if type(t.code) ~= 'string' then
		error('expected code string')
	end
	if type(t.name) ~= 'string' then
		error('expected name string')
	end
	t.lines = 0 
	for c in string.gmatch(t.code,'\n') do
		t.lines = t.lines + 1
	end

	for i,v in ipairs(t.depend) do
		if not self.libs[v] then
			errf('%s missing dep %s\n',t.name,v)
		end
	end
	self.libs[t.name] = t
end

--[[
register an array of libs
]]
function rlibs:register_array(t)
	for i,v in ipairs(t) do
		self:register(v)
	end
end

--[[
add deps for a single lib
]]
function rlibs:build_single(build,name)
	local lib = self.libs[name]
	if not lib then
		errf('unknown lib %s\n',tostring(name))
	end
	-- already added
	if build.map[name] then
		return
	end
	for i,dname in ipairs(lib.depend) do
		self:build_single(build,dname)
	end
	build.map[name]=lib
	table.insert(build.list,lib)
end
--[[
return an object containing the libs with deps resolved
obj=rlibs:build('name'|{'name1','name2',...})
]]
-- helper for returned object
local function rlib_get_code(build)
	local code=""
	for i,lib in ipairs(build.list) do
		code = code .. lib.code .. '\n'
	end
	return code
end
function rlibs:build(libnames)
	-- single can be given as string, 
	-- nil is allowed, returns empty object
	if type(libnames) == 'string' or type(libnames) == 'nil' then
		libnames={libnames}
	elseif type(libnames) ~= 'table' then
		error('rlibs:build_list expected string or table for libnames')
	end
	local build={
		list={},
		map={},
		code=rlib_get_code,
	}
	for i,name in ipairs(libnames) do
		self:build_single(build,name)
	end
	return build
end
--[[
return a string containing all the required rlib code
code=rlibs:build('name'|{'name1','name2',...})
]]
function rlibs:code(names)
	local build = self:build(names)
	return build:code();
end

rlibs:register_array{
--[[
mostly duplicated from util.serialize
global defaults can be changed from code
]]
{
	name='serialize',
	code=[[
serialize_r = function(v,opts,r,seen,depth)
	local vt = type(v)
	if vt == 'nil' or  vt == 'boolean' or vt == 'number' then
		table.insert(r,tostring(v))
		return
	end
	if vt == 'string' then
		table.insert(r,string.format('%q',v))
		return 
	end
	if vt == 'table' then
		if not depth then
			depth = 1
		end
		if depth >= opts.maxdepth then
			error('serialize: max depth')
		end
		if not seen then
			seen={}
		elseif seen[v] then 
			if opts.err_cycle then
				error('serialize: cycle')
			else
				table.insert(r,'"cycle:'..tostring(v)..'"')
				return 
			end
		end
		seen[v] = true;
		table.insert(r,'{')
		for k,v1 in pairs(v) do
			if opts.pretty then
				table.insert(r,'\n'..string.rep(' ',depth))
			end
			if type(k) == 'string' and string.match(k,'^[_%a][%a%d_]*$') then
				table.insert(r,k)
			else
				table.insert(r,'[')
				serialize_r(k,opts,r,seen,depth+1)
				table.insert(r,']')
			end
			table.insert(r,'=')
			serialize_r(v1,opts,r,seen,depth+1)
			table.insert(r,',')
		end
		if opts.pretty then
			table.insert(r,'\n'..string.rep(' ',depth-1))
		end
		table.insert(r,'}')
		return
	end
	if opts.err_type then
		error('serialize: unsupported type ' .. vt, 2)
	else
		table.insert(r,'"'..tostring(v)..'"')
	end
end
serialize_defaults = {
	maxdepth=10,
	err_type=true,
	err_cycle=true,
	pretty=false,
}
function serialize(v,opts)
	if opts then
		for k,v in pairs(serialize_defaults) do
			if not opts[k] then
				opts[k]=v
			end
		end
	else
		opts=serialize_defaults
	end
	local r={}
	serialize_r(v,opts,r)
	return table.concat(r)
end
]],
},
--[[
mt_inherit from util
]]
{
	name='mt_inherit',
	code=[[
function mt_inherit(t,base)
	local mt={
		__index=function(table, key)
			return base[key]
		end
	}
	setmetatable(t,mt)
	return t
end
]],
},
--[[
extend_table from util
note deep will fail unless you include extend_table_r
]]
{
	name='extend_table',
	code=[[
function extend_table(target,source,deep)
	if type(target) ~= 'table' then
		error('extend_table: target not table')
	end
	if source == nil then
		return target
	end
	if type(source) ~= 'table' then 
		error('extend_table: source not table')
	end
	if source == target then
		error('extend_table: source == target')
	end
	if deep then
		return extend_table_r(target, source)
	else 
		for k,v in pairs(source) do
			target[k]=v
		end
		return target
	end
end
]],
},
--[[
recursive version of extend_table
not meant to be used on its own 
depends are intentially weird, requiring this will pull in extend_table
]]
{
	name='extend_table_r',
	depend='extend_table',
	code=[[
extend_table_max_depth = 10
function extend_table_r(target,source,seen,depth) 
	if not seen then
		seen = {}
	end
	if not depth then
		depth = 1
	end
	if depth > extend_table_max_depth then
		error('extend_table: max depth');
	end
	-- a source could have refernces to the target, don't want to do that
	seen[target]=true
	if seen[source] then
		error('extend_table: cycles');
	end
	seen[source]=true
	for k,v in pairs(source) do
		if type(v) == 'table' then
			if type(target[k]) ~= 'table' then
				target[k] = {}
			end
			extend_table_r(target[k],v,seen,depth+1)
		else
			target[k]=v
		end
	end
	return target
end
]],
},
-- override default table serialization for messages
{
	name='serialize_msgs',
	depend='serialize',
	code=[[
	usb_msg_table_to_string=serialize
]],
},
--[[
serialize mem use testing
]]
--!return con:execwait([[return sertest({a='a',b='b',t={1,2,3,{test='the quick brown fox',1,2,3,4,5,6,7,8,9,10,11,1 2,13,14,14},{}}},serialize)]],{libs={'serialize_msgs','sertest'}})
{
	name='sertest',
	depend='serialize_msgs',
	code=[[
function memstats(name)
	local t={
		name=name,
		count=collectgarbage('count')
	}
	local m=get_meminfo()
	t.free_size=m.free_size
	t.free_block_max_size=m.free_block_max_size
	return t
end

function sertest(data,func)
	collectgarbage('collect')
	local t={
		memstats('before')
	}
	t.r=func(data)
	table.insert(t,memstats('after'))
	collectgarbage('collect')
	table.insert(t,memstats('collect'))
	return t
end
]],
},

--[[
join a path with / as needed
]]
{
	name='joinpath',
	code=[[
function joinpath(...)
	local parts={...}
	if #parts < 2 then
		error('joinpath requires at least 2 parts',2)
	end
	local r=parts[1]
	for i = 2, #parts do
		local v = string.gsub(parts[i],'^/','')
		if not string.match(r,'/$') then
			r=r..'/'
		end
		r=r..v
	end
	return r
end
]],
},
--[[
basename_cam from fsutil
]]
{
	name='basename',
	code=[[
function basename(path)
	if not path then
		return nil
	end
	if path == 'A/' then
		return nil
	end
	local s,e,bn=string.find(path,'([^/]+)/?$')
	if not s then
		return nil
	end
	if sfx and string.len(sfx) < string.len(bn) then
		if string.sub(bn,-string.len(sfx)) == sfx then
			bn=string.sub(bn,1,string.len(bn) - string.len(sfx))
		end
	end
	return bn
end
]],
},
--[[
dirname_cam from fsutil
note A/ is ambiguous
]]
{
	name='dirname',
	code=[[
function dirname(path)
	if not path then
		return nil
	end
	if path == 'A/' then
		return path
	end
	-- remove trailing blah/?
	dn=string.gsub(path,'[^/]+/*$','')
	-- invalid, 
	if dn == '' then
		return nil
	end
	-- remove any trailing /
	dn = string.gsub(dn,'/*$','')
	if dn == 'A' then
		return 'A/'
	end
	-- all /, invalid
	if dn == '' then
		return nil
	end
	return dn
end
]],
},
--[[
splitpath_cam from util
]]
{
	name='splitpath',
	depend={'basename','dirname'},
	code=[[
	local parts={}
function splitpath(path)
	while true do
		local part=basename(path)
		path = dirname(path)
		table.insert(parts,1,part)
		if path == 'A/' then
			table.insert(parts,1,path)
			return parts
		end
		if path == nil then
			return parts
		end
	end
end
]],
},
--[[
make multiple levels of directories, as needed
modified from fsutil
]]
{
	name='mkdir_m',
	depend={'splitpath','joinpath'},
	code=[[
function mkdir_m(path)
	local st = os.stat(path)
	if st then
		if st.is_dir then
			return true
		end
		return false,'path exists, not directory'
	end
	local parts = splitpath(path)
	local p=parts[1]
	for i=2, #parts do
		p = joinpath(p,parts[i])
		local st = os.stat(p)
		if not st then
			local status,err = os.mkdir(p)
			if not status then
				return false,err
			end
		elseif not st.is_dir then
			return false,'path exists, not directory'
		end
	end
	return true
end
]],
},
--[[
function to batch stuff in groups of messages
each batch is sent as a numeric array
b=msg_batcher{
	batchsize=num, -- items per batch
	batchpause=num -- sleep after each batch, to allow client to empty queue, default=unset=none
	batchgc=string -- 'collect' or 'step', if set, collectgarbage is called with this on each flush
	timeout=num, -- message timeout
	dbgmem=bool --  return memory info in data._dbg
}
TODO should check free memory and force collect/flush if low, but bad for cameras without firmware meminfo
call
b:write(value) adds items and sends when batch size is reached
b:flush() sends any remaining items
]]
{
	name='msg_batcher',
	depend={'serialize_msgs','extend_table'},
	code=[[
function msg_batcher(opts)
	local t = extend_table({
		batchsize=50,
		batchgc='step',
		timeout=100000,
	},opts)
	t.data={}
	t.n=0
	if t.dbgmem then
		t.init_free = get_meminfo().free_block_max_size
		t.init_count = collectgarbage('count')
	end
	t.write=function(self,val)
		self.n = self.n+1
		self.data[self.n]=val
		if self.n >= self.batchsize then
			return self:flush()
		end
		return true
	end
	t.flush = function(self)
		if self.n > 0 then
			if self.dbgmem then
				local count=collectgarbage('count')
				local free=get_meminfo().free_block_max_size
				self.data._dbg=string.format("count %d (%d) free %d (%d)",
					count, count - self.init_count, free, self.init_free-free)
			end
			if not write_usb_msg(self.data,self.timeout) then
				return false
			end
			self.data={}
			self.n=0
			if self.batchgc then
				collectgarbage(self.batchgc)
			end
			if self.batchpause then
				sleep(self.batchpause)
			end
		end
		return true
	end
	return t
end
]],
},
--[[
retrieve a directory listing of names, batched in messages
]]
{
	name='ls_simple',
	depend='msg_batcher',
	code=[[
function ls_simple(path)
	local b=msg_batcher()
	local t,err=os.listdir(path)
	if not t then
		return false,err
	end
	for i,v in ipairs(t) do
		if not b:write(v) then
			return false
		end
	end
	return b:flush()
end
]],
},
--[[
object to aid interating over files and directories
status,err=fs_iter.run({paths},opts)
opts={
	callback=function(self)
	end_callback=function(self,status,msg)
	listall=bool -- pass to os.listdir; currently broken, stat on . or .. fails
	-- users may add their own methods or members
})
self in callbacks is the fs_iter object, merged with opts
callback is called on each file/directory 
must return true to continue processing, or false optionally followed by an error message on error
the following are available to callback
self.cur={
	st=<stat information>
	full=<full path and filename as string>
	path=<array of {initial path, path components recursed into,..., name}>
	name=<basename>
}
in the case of the root directory full='A/' and name='A/'
self.rpath an array of path elements representing the directories recursed into
self:depth() depth of recursion, 0 for initial paths
self:can_recurse() to check if the current items is valid to recurse into
self:recurse() to recurse into a directory
]]
{
	name='fs_iter',
	depend={'serialize_msgs','joinpath','basename','mt_inherit','extend_table'},
	code=[[
fs_iter={}

function fs_iter:depth()
	return #self.rpath
end

function fs_iter:can_recurse()
	if not self.cur.st.is_dir or self.cur.name == '.' or self.cur.name == '..' then
		return false
	end
	return true
end

function fs_iter:recurse()
	if not self:can_recurse() then
		return false
	end
	table.insert(self.rpath,self.cur.path[#self.cur.path])
	local save_cur = self.cur
	local status,err = self:singledir()
	self.cur = save_cur
	table.remove(self.rpath)
	return status,err
end

function fs_iter:singleitem(path)
	local st,err=os.stat(path)
	if not st then
		return false,err
	end
	self.cur={st=st,full=path}
	if path == 'A/' then
		self.cur.name = 'A/'
	else
		self.cur.name = basename(path)
	end
	if #self.rpath == 0 then
		self.cur.path = {path}
	else
		self.cur.path = {unpack(self.rpath)}
		table.insert(self.cur.path,self.cur.name)
	end
	return self:callback()
end

function fs_iter:singledir()
	local cur_dir = self.cur.full
	local t,err=os.listdir(cur_dir,self.listall)
	if not t then
		return false,err
	end
	for i,name in ipairs(t) do
		local status, err = self:singleitem(joinpath(cur_dir,name))
		if not status then
			return false,err
		end
	end
	return true
end

function fs_iter:end_callback(status,msg)
	return status,msg
end

function fs_iter.run(paths,opts)
	local t=extend_table({},opts)
	mt_inherit(t,fs_iter)

	for i,path in ipairs(paths) do
		t.rpath={}
		local status,err=t:singleitem(path)
		if not status then
			return t:end_callback(false,err)
		end
	end
	return t:end_callback(true)
end
]],
},
--[[
process directory tree with matching
status,err = find_files(paths,opts,func)
paths=<array of paths to process>
opts={
	fmatch='<pattern>', -- match on full path of files, default any (NOTE can match on filename with /<match>$)
	dmatch='<pattern>', -- match on names of directories, default any 
	rmatch='<pattern>', -- recurse into directories matching, default any 
	dirs=true, -- pass directories to func. otherwise only files sent to func, but dirs are still recursed
	dirsfirst=false, -- process directories before contained files
	maxdepth=100, -- maxium depth of directories to recurse into, 0=just process paths passed in, don't recurse
	martians=bool, -- process non-file, not directory items (vol label,???) default false
	batchsize=20, -- passed to msg_batcher, if used
}
func defaults to batching the full path of each file
unless dirsfirst is set, directories will be recursed into before calling func on the containing directory
TODO
match on stat fields (newer, older etc)
match by path components e.g. /foo[ab]/bar/.*%.lua
]]
{
	depend={'fs_iter','msg_batcher','extend_table'},
	name='find_files',
	code=[[
function find_files_all_fn(di,opts)
	return di:ff_bwrite(di.cur)
end

function find_files_fullname_fn(di,opts)
	return di:ff_bwrite(di.cur.full)
end

function find_files(paths,opts,func)
	if not func then
		func=find_files_fullname_fn
	end
	opts=extend_table({
		dirs=true,
		dirsfirst=false,
		maxdepth=100,
		batchsize=20,
	},opts)

	return fs_iter.run(paths,{
		ff_check_match=function(self,opts)
			if self.cur.st.is_file then
				return not opts.fmatch or string.match(self.cur.full,opts.fmatch)
			end
			if self.cur.st.is_dir then
				return not opts.dmatch or string.match(self.cur.full,opts.dmatch)
			end
			if opts.martians then
				return true
			end
			return false
		end,
		ff_bwrite=function(self,data)
			if not self.ff_batcher then
				self.ff_batcher = msg_batcher({
					batchsize=opts.batchsize,
					batchpause=opts.batchpause,
					batchgc=opts.batchgc,
					dbgmem=opts.dbgmem})
			end
			return self.ff_batcher:write(data)
		end,
		ff_bflush=function(self)
			if not self.ff_batcher then
				return true
			end
			return self.ff_batcher:flush()
		end,
		ff_func=func,
		ff_item=function(self,opts)
			if not self:ff_check_match(opts) then
				return true
			end
			return self:ff_func(opts)
		end,
		callback=function(self)
			if self.cur.st.is_dir then
				if opts.dirs and opts.dirsfirst then
					local status,err = self:ff_item(opts)
					if not status then
						return false,err
					end
				end
				if self:depth() < opts.maxdepth and self:can_recurse() then
					if not opts.rmatch or string.match(self.cur.name,opts.rmatch) then
						local status,err = self:recurse()
						if not status then
							return false,err
						end
					end
				end
				if opts.dirs and not opts.dirsfirst then
					local status,err = self:ff_item(opts)
					if not status then
						return false,err
					end
				end
			else
				local status,err = self:ff_item(opts)
				if not status then
					return false,err
				end
			end
			return true
		end,
		end_callback=function(self,status,err)
			if not status then
				self:ff_bflush()
				return false,err
			end
			return self:ff_bflush()
		end
	})
end
]],
},
--[[
camera side support for mdownload
]]
{
	depend={'find_files'},
	name='ff_mdownload',
	code=[[
function ff_mdownload_fn(self,opts)
	if #self.rpath == 0 and self.cur.st.is_dir then
		return true
	end
	return self:ff_bwrite(self.cur)
end

function ff_mdownload(paths,opts)
	return find_files(paths,opts,ff_mdownload_fn)
end
]],
},
--[[
camera side support for mdelete
]]
{
	depend={'find_files'},
	name='ff_mdelete',
	code=[[
function ff_mdelete_fn(self,opts)
	local status,msg
	if self.cur.full == 'A/' or (opts.skip_topdirs and self.cur.st.is_dir == true and #self.rpath == 0) then
		return self:ff_bwrite({file=self.cur.full,status=true,msg='skipped'})
	end
	if not opts.pretend then
		status,msg=os.remove(self.cur.full)
		if not status and not opts.ignore_errors then
			self:ff_bwrite({file=self.cur.full,status=status,msg=msg})
			return false, msg
		end
	else
		status=true
	end
	return self:ff_bwrite({file=self.cur.full,status=status,msg=msg})
end

function ff_mdelete(paths,opts)
	return find_files(paths,opts,ff_mdelete_fn)
end
]],
},
--[[
TODO rework this to a general iterate over directory function
sends file listing as serialized tables with write_usb_msg
returns true, or false,error message
opts={
	stat=bool|{table}|'/'|'*',
	listall=bool, 
	msglimit=number,
	match="pattern",
	dirsonly=bool
}
stat
	false/nil, return an array of names without stating at all
	'/' return array of names, with / appended to dirs
	'*" return array of stat results, plus name="name"
	{table} return stat fields named in table (TODO not implemented)
msglimit
	maximum number of items to return in a message
	each message will contain a table with partial results
	default 50
match
	pattern, file names matching with string.match will be returned
listall 
	passed as second arg to os.listdir
dirsonly
    only list directories, error if path is a file

may run out of memory on very large directories,
msglimit can help but os.listdir itself could use all memory
TODO message timeout is not checked
]]
{
	name='ls',
	depend={'msg_batcher','joinpath'},
	code=[[
function ls(path,opts_in)
	local opts={
		msglimit=50,
		msgtimeout=100000,
		dirsonly=true
	}
	if opts_in then
		for k,v in pairs(opts_in) do
			opts[k]=v
		end
	end
	local st, err = os.stat(path)
	if not st then
		return false, err
	end

	local b=msg_batcher{
		batchsize=opts.msglimit,
		timeout=opts.msgtimeout
	}

	if not st.is_dir then
		if opts.dirsonly then
			return false, 'not a directory'
		end
		if opts.stat == '*' then
			st.name=path
			b:write(st)
		else
			b:write(path)
		end
		b:flush()
		return true
	end

	local t,msg=os.listdir(path,opts.listall)
	if not t then
		return false,msg
	end
	for i,v in ipairs(t) do
		if not opts.match or string.match(v,opts.match) then
			if opts.stat then
				local st,msg=os.stat(joinpath(path,v))
				if not st then
					return false,msg
				end
				if opts.stat == '/' then
					if st.is_dir then
						b:write(v .. '/')
					else 
						b:write(v)
					end
				elseif opts.stat == '*' then
					st.name=v
					b:write(st)
				end
			else
				b:write(v)
			end
		end
	end
	b:flush()
	return true
end
]],
},
--[[
support for cli shoot command, set exposure params
TODO could check that ISO mode gets set, esp for 1.2 which ignores unknown values
]]
{
	name='rlib_shoot_common',
	code=[[
function rlib_shoot_init_exp(opts)
	if opts.tv then
		set_tv96_direct(opts.tv)
	end
	if opts.sv then
		set_sv96(opts.sv)
	end
	if opts.isomode then
		set_iso_mode(opts.isomode)
	end
	if opts.av then
		set_av96_direct(opts.av)
	end
	if opts.nd then
		set_nd_filter(opts.nd)
	end
end
]],
},
{
	name='rlib_shoot',
	depend={'rlib_shoot_common'}, -- note require serialize_msgs if info
	code=[[
function rlib_shoot(opts)
	local rec,vid = get_mode()
	if not rec then
		return false,'not in rec mode'
	end

	rlib_shoot_init_exp(opts)

	local save_raw
	if opts.raw then
		save_raw=get_raw()
		set_raw(opts.raw)
	end
	local save_dng
	if opts.dng then
		save_dng=get_config_value(226)
		set_config_value(226,opts.dng)
	end
	shoot()
	local r
	if opts.info then
		r = {
			dir=get_image_dir(),
			exp=get_exp_count(),
			raw=(get_raw() == 1),
		}
		if r.raw then
			r.raw_in_dir = (get_config_value(35) == 1)
			r.raw_pfx = get_config_value(36)
			r.raw_ext = get_config_value(37)
			r.dng = (get_config_value(226) == 1)
			if r.dng then
				r.use_dng_ext = (get_config_value(234) == 1)
			end
		end
	else
		r=true
	end
	if save_raw then
		set_raw(save_raw)
	end
	if save_dng then
		set_config_value(226,save_dng)
	end
	return r
end
	]],
},
--[[
TODO temp - should be integrated into above
support for cli remote capture shoot command
starts shoot, doesn't wait for it to finish
]]
{
	name='rs_shoot_init',
	code=[[
function rs_init(opts)
	local rec,vid = get_mode()
	if not rec then
		return false,'not in rec mode'
	end
	if type(init_usb_capture) ~= 'function' then
		return false, 'usb capture not supported'
	end
	if bitand(get_usb_capture_support(),opts.fformat) ~= opts.fformat then
		return false, 'unsupported format'
	end
	if not init_usb_capture(opts.fformat,opts.lstart,opts.lcount) then
		return false, 'init failed'
	end
	if opts.cap_timeout then
		set_usb_capture_timeout(opts.cap_timeout)
	end
	if opts.cont then
		if get_prop(require'propcase'.DRIVE_MODE) ~= 1 then
			return false, 'not in continuous mode'
		end
		if opts.cont <= 0 then
			return false, 'invalid shot count'
		end
	end
	return true
end
]],
},
{
	name='rs_shoot',
	depend={'rlib_shoot_common'},
	-- TODO cont doesn't handle exposure counter wrap!
	code=[[
function rs_shoot_single()
	shoot()
end
function rs_shoot_cont(opts)
	local last = get_exp_count() + opts.cont
	press('shoot_half')
	repeat
		m=read_usb_msg(10)
	until get_shooting() or m == 'stop'
	if m == 'stop' then
		release('shoot_half')
		return
	end
	sleep(20)
	press('shoot_full')
	repeat
		m=read_usb_msg(10)
	until get_exp_count() >= last or m == 'stop'
	release('shoot_full')
end
function rs_shoot(opts)
	rlib_shoot_init_exp(opts)
	if opts.cont then
		rs_shoot_cont(opts)
	else
		rs_shoot_single()
	end
end
]],
},
--[[
search memory for an aligned 32 bit word
mem_search_word{
	start:number
	last:number
	count:number
	val:number
}
]]
{
	name='mem_search_word',
	depend={'msg_batcher'},
	code=[[
function mem_search_word(opts)
	if type(opts) ~= 'table' then
		error('missing opts')
	end
	local start = tonumber(opts.start)
	local last 
	if opts.count then
		last = start + (tonumber(opts.count)-1)*4
	else
		last = tonumber(opts.last)
	end
	local val = tonumber(opts.val)
	if not start or not last or last < start or not val then
		error('bad opts')
	end
	set_yield(-1,100)
	local b=msg_batcher()
	for i=start,last,4 do
		local v = peek(i)
		if v == val then
			if not b:write(i) then
				error('write failed')
			end
		end
	end
	b:flush()
end
]]
},
--[[
a simple long lived script for interactive testing
example
!return con:exec('msg_shell:run()',{libs='msg_shell'})
putm exec message="hello world"
putm exec print(message)
]]
{
	name='msg_shell',
	code=[[
msg_shell={}
msg_shell.done=false
msg_shell.sleep=10
msg_shell.read_msg_timeout=10000
msg_shell.cmds={
	quit=function(msg)
		msg_shell.done=true
	end,
	echo=function(msg)
		if write_usb_msg(msg) then
			print("ok")
		else 
			print("fail")
		end
	end,
	exec=function(msg)
		local f,err=loadstring(string.sub(msg,5));
		if f then 
			local r={f()} -- pcall would be safer but anything that yields will fail
			for i, v in ipairs(r) do
				write_usb_msg(v)
			end
		else
			write_usb_msg(err)
			print("loadstring:"..err)
		end
	end,
	pcall=function(msg)
		local f,err=loadstring(string.sub(msg,6));
		if f then 
			local r={pcall(f)}
			for i, v in ipairs(r) do
				write_usb_msg(v)
			end
		else
			write_usb_msg(err)
			print("loadstring:"..err)
		end
	end,
}
msg_shell.idle = function()
	sleep(msg_shell.sleep)
end
msg_shell.run=function(self)
	repeat 
		local msg=read_usb_msg(self.read_msg_timeout)
		if msg then
			local cmd = string.match(msg,'^%w+')
			if type(self.cmds[cmd]) == 'function' then
				self.cmds[cmd](msg)
			elseif type(self.default_cmd) == 'function' then
				self.default_cmd(msg)
			else
				print('undefined command: '..cmd)
			end
		else
			self.idle()
		end
	until self.done
end
]],
},
}
return rlibs
