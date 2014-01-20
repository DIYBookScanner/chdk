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
--[[
very quick and dirty test framework for some lua functions
]]
-- module
local m={}
-- tests
local t={}
-- assert with optional level for line numbers
local function tas(cond,msg,level)
	if not level then 
		level = 3
	end
	if cond then
		return
	end
	error(msg,level)
end

local function spoof_fsutil_ostype(name)
	fsutil.ostype = function()
		return name
	end
end
local function unspoof_fsutil_ostype()
	fsutil.ostype = sys.ostype
end

t.argparser = function()
	local function get_word(val,eword,epos) 
		local word,pos = cli.argparser:get_word(val)
		tas(word == eword,tostring(word) .. ' ~= '..tostring(eword))
		tas(pos == epos,tostring(pos) .. "~= "..tostring(epos))
	end
	get_word('','',1)
	get_word('whee','whee',5)
	get_word([["whee"]],'whee',7)
	get_word([['whee']],'whee',7)
	get_word([[\whee\]],[[\whee\]],7)
	get_word("whee foo",'whee',5)
	get_word([["whee\""]],[[whee"]],9)
	get_word([['whee\']],[[whee\]],8)
	get_word("'whee ",false,[[unclosed ']])
	get_word([["whee \]],false,[[unexpected \]])
	get_word('wh"e"e','whee',7)
	get_word('wh""ee','whee',7)
	get_word([[wh"\""ee]],[[wh"ee]],9)
end

t.dirname = function()
	assert(fsutil.dirname('/')=='/')
	assert(fsutil.dirname('//')=='/')
	assert(fsutil.dirname('/a/b/')=='/a')
	assert(fsutil.dirname('//a//b//')=='//a')
	assert(fsutil.dirname()==nil)
	assert(fsutil.dirname('a')=='.')
	assert(fsutil.dirname('')=='.')
	assert(fsutil.dirname('/a')=='/')
	assert(fsutil.dirname('a/b')=='a')

	spoof_fsutil_ostype('Windows')
	assert(fsutil.dirname('c:\\')=='c:/')
	assert(fsutil.dirname('c:')=='c:')
	unspoof_fsutil_ostype()
end

t.basename = function()
	assert(fsutil.basename('foo/bar')=='bar')
	assert(fsutil.basename('foo/bar.txt','.txt')=='bar')
	assert(fsutil.basename('foo/bar.TXT','.txt')=='bar')
	assert(fsutil.basename('foo/bar.TXT','.txt',{ignorecase=false})=='bar.TXT')
	assert(fsutil.basename('bar')=='bar')
	assert(fsutil.basename('bar/')=='bar')
	spoof_fsutil_ostype('Windows')
	assert(fsutil.basename('c:/')==nil)
	assert(fsutil.basename('c:/bar')=='bar')
	unspoof_fsutil_ostype()
end

t.basename_cam = function()
	assert(fsutil.basename_cam('A/')==nil)
	assert(fsutil.basename_cam('A/DISKBOOT.BIN')=='DISKBOOT.BIN')
	assert(fsutil.basename_cam('bar/')=='bar')
end

t.dirname_cam = function()
	assert(fsutil.dirname_cam('A/')=='A/')
	assert(fsutil.dirname_cam('A/DISKBOOT.BIN')=='A/')
	assert(fsutil.dirname_cam('bar/')==nil)
	assert(fsutil.dirname_cam('A/CHDK/SCRIPTS')=='A/CHDK')
end

t.splitjoin_cam = function()
	assert(fsutil.joinpath(unpack(fsutil.splitpath_cam('A/FOO'))) == 'A/FOO')
	assert(fsutil.joinpath(unpack(fsutil.splitpath_cam('foo/bar/mod'))) == 'foo/bar/mod')
end

t.joinpath = function()
	assert(fsutil.joinpath('/foo','bar')=='/foo/bar')
	assert(fsutil.joinpath('/foo/','bar')=='/foo/bar')
	assert(fsutil.joinpath('/foo/','/bar')=='/foo/bar')
	assert(fsutil.joinpath('/foo/','bar','/mod')=='/foo/bar/mod')
	spoof_fsutil_ostype('Windows')
	assert(fsutil.joinpath('/foo\\','/bar')=='/foo\\bar')
	unspoof_fsutil_ostype()
end

t.fsmisc = function()
	spoof_fsutil_ostype('Windows')
	assert(fsutil.joinpath(unpack(fsutil.splitpath('d:/foo/bar/mod'))) == 'd:/foo/bar/mod')
	-- assert(fsutil.joinpath(unpack(fsutil.splitpath('d:foo/bar/mod'))) == 'd:foo/bar/mod')
	unspoof_fsutil_ostype()
	assert(fsutil.joinpath(unpack(fsutil.splitpath('/foo/bar/mod'))) == '/foo/bar/mod')
	assert(fsutil.joinpath(unpack(fsutil.splitpath('foo/bar/mod'))) == './foo/bar/mod')
end

t.ustime = function()
	local t=os.time()
	local t0=ustime.new(t,600000)
	local t1=ustime.new(t+1,500000)
	assert(ustime.diff(t1,t0)==900000)
end

t.lbuf = function()
	local s="hello world"
	local l=lbuf.new(s)
	assert(s:len() == l:len())
	assert(s == l:string())
	assert(s:sub(0,100) == l:string(0,100))
	assert(l:string(-5)=='world')
	assert(l:string(1,5)=='hello')
	assert(l:string(nil,5)=='hello')
	assert(l:string(100,200)==s:sub(100,200))
	assert(l:byte(0)==s:byte(0))
	assert(l:byte(5)==s:byte(5))
	local t1 = {l:byte(-5,100)}
	local t2 = {s:byte(-5,100)}
	assert(#t1 == #t2)
	for i,v in ipairs(t2) do
		assert(t1[i]==t2[i])
	end
	local l2=l:sub()
	assert(l2:string() == l:string())
	l2 = l:sub(-5)
	assert(l2:string()=='world')
	l2 = l:sub(1,5)
	assert(l2:string()=='hello')
	l2 = l:sub(100,101)
	assert(l2:len()==0)
	assert(l2:string()=='')
	l=lbuf.new(100)
	assert(l:len()==100)
	assert(l:byte()==0)
	s=""
	l=lbuf.new(s)
	assert(l:len()==0)
	assert(l:byte()==nil)
	assert(l:string()=="")
end

t.lbufi = function()
	-- TODO not endian aware
	local l=lbuf.new('\001\000\000\000\255\255\255\255')
	assert(l:get_i32()==1)
	assert(l:get_i16()==1)
	assert(l:get_i8()==1)
	assert(l:get_i32(10)==nil)
	assert(l:get_i32(5)==nil)
	assert(l:get_i16(4)==-1)
	assert(l:get_i32(4,10)==-1)
	assert(l:get_u32()==1)
	assert(l:get_u16()==1)
	assert(l:get_i32(4)==-1)
	assert(l:get_u8(4)==0xFF)
	assert(l:get_i8(4)==-1)
	assert(l:get_u32(4)==0xFFFFFFFF)
	assert(l:get_u32(1)==0xFF000000)
	assert(l:get_u16(3)==0xFF00)
	local t={l:get_i32(0,100)}
	assert(#t == 2)
	assert(t[1] == 1)
	assert(t[2] == -1)
	local l=lbuf.new('\001\000\000\000\000\255\255\255\255')
	assert(l:get_i32(1)==0x000000)
	local t={l:get_u32(0,3)}
	assert(#t == 2)
	assert(t[1] == 1)
	assert(t[2] == 0xFFFFFF00)
	local l=lbuf.new(string.rep('\001',256))
	local t={l:get_u32(4,-1)}
	assert(#t == 63)
	local l=lbuf.new(8)
	l:set_u32(0,0xFEEDBABE,0xDEADBEEF)
	local t={l:get_u32(0,2)}
	assert(#t == 2)
	assert(t[1] == 0xFEEDBABE)
	assert(t[2] == 0xDEADBEEF)
	local t={l:get_u16(0,4)}
	assert(t[1] == 0xBABE)
	assert(t[2] == 0xFEED)
	assert(t[3] == 0xBEEF)
	assert(t[4] == 0xDEAD)
	l:set_i16(0,-1)
	l:set_u16(2,0xDEAD)
	local t={l:get_u16(0,2)}
	assert(t[1] == 0xFFFF)
	assert(t[2] == 0xDEAD)
	local l=lbuf.new(5)
	l:set_i32(0,-1,42)
	local t={l:get_i32(0,2)}
	assert(#t == 1)
	assert(t[1] == -1)
	local l=lbuf.new(16)
	assert(l:fill("a")==16)
	assert(l:get_u8()==string.byte('a'))
	local l2=lbuf.new(4)
	assert(l2:fill("hello world")==4)
	assert(l:fill(l2,100,1)==0)
	assert(l:fill(l2,1,2)==8)
	assert(l:string(2,9)=="hellhell")
	assert(l:string()=="ahellhellaaaaaaa")
	assert(l:fill(l2,14,20)==2)
end

t.lbufutil = function()
	-- TODO doesn't exercise file loading
	local lbu=require'lbufutil'
	local b=lbu.wrap(lbuf.new('\001\000\000\000\255\255\255\255hello world\000\002\000\000\000'))
	b:bind_i32('first')
	b:bind_i32('second')
	b:bind_u32('second_u',4)
	b:bind_sz('str',12)
	b:bind_rw_i32('last')
	assert(b.first==1)
	assert(b.second==-1)
	assert(b.second_u==0xFFFFFFFF)
	assert(b.str=="hello world")
	assert(b.last==2)
	b.last = 3
	assert(b.last==3)
	b:bind_seek('set',0)
	b:bind_i32('s1')
	assert(b.s1==1)
	assert(b:bind_seek() == 4) -- return current pos
	assert(b:bind_seek(4) == 8) -- cur +4
	assert(b:bind_seek('end') == b._lb:len()) -- length
	assert(b:bind_seek('end',-4) == b._lb:len()-4)
	b:bind_seek('set',0)
	b:bind_i8('i8_1')
	assert(b.i8_1==1)
	b:bind_seek('set',4)
	b:bind_i8('i8_2')
	assert(b.i8_2==-1)
	b:bind_u8('u8_1')
	assert(b.u8_1==0xFF)
end

t.lbuff = function()
	local l=lbuf.new('hello world')
	local f=io.open('lbuftest.dat','wb')
	l:fwrite(f)
	f:close()
	l2=lbuf.new(l:len())
	f=io.open('lbuftest.dat','rb')
	l2:fread(f)
	f:close()
	assert(l:string()==l2:string())
	f=io.open('lbuftest.dat','wb')
	l:fwrite(f,6)
	f:close()
	f=io.open('lbuftest.dat','rb')
	l2:fread(f,0,5)
	f:close()
	assert(l2:string()=='world world')
	f=io.open('lbuftest.dat','wb')
	l:fwrite(f,6,2)
	f:close()
	f=io.open('lbuftest.dat','rb')
	l2:fread(f,9,2)
	f:close()
	assert(l2:string()=='world worwo')
	os.remove('lbuftest.dat')
end

t.compare = function()
	assert(util.compare_values_subset({1,2,3},{1}))
	assert(util.compare_values_subset({1},{1,2,3})==false)
	local t1={1,2,3,t={a='a',b='b',c='c'}}
	local t2=util.extend_table({},t1)
	assert(util.compare_values(t1,t2))
	assert(util.compare_values(true,true))
	assert(util.compare_values(true,1)==false)
	-- TODO test error conditions
end

t.serialize = function()
	local s="this \n is '\" a test"
	local t1={1,2,3,t={a='a',b='b',c='c'},s=s}
	assert(util.compare_values(t1,util.unserialize(util.serialize(t1))))
	assert(s == util.unserialize(util.serialize(s)))
	assert(true == util.unserialize(util.serialize(true)))
	assert(nil == util.unserialize(util.serialize(nil)))
	-- TODO test error conditions
end

t.round = function()
	assert(util.round(0)==0)
	assert(util.round(0.4)==0)
	assert(util.round(-0.4)==0)
	assert(util.round(0.5)==1)
	assert(util.round(-0.5)==-1)
	assert(util.round(1.6)==2)
	assert(util.round(-1.6)==-2)
end

t.extend_table = function()
	local tsub={ka='a',kb='b','one','two'}
	local t={1,2,3,tsub=tsub}
	assert(util.compare_values(util.extend_table({},t),t))
	assert(util.compare_values_subset(util.extend_table({'a','b','c','d'},t),t))
	assert(util.compare_values(util.extend_table({},t,{deep=true}),t))
	assert(util.compare_values(util.extend_table({},t,{keys={1,2}}),{1,2}))
	assert(util.compare_values(util.extend_table({},t,{keys={1,2,'tsub'}}),{1,2,tsub=tsub}))
	assert(not util.compare_values(util.extend_table({},t,{keys={1,2,'tsub'}}),t))
	assert(util.compare_values(util.extend_table({a='a'},t,{keys={1,2,'a'}}),{1,2,a='a'}))
end

t.bit_util = function()
	local b=util.bit_unpack(0)
	assert(#b==31)
	assert(b[0] == 0)
	assert(b[1] == 0)
	assert(b[31] == 0)
	assert(util.bit_packu(b) == 0)
	local b=util.bit_unpack(0x80000000)
	assert(b[0] == 0)
	assert(b[31] == 1)
	assert(util.bit_packu(b) == 0x80000000)
	assert(util.bit_packu(util.bit_unpack(15,2)) == 7)
	assert(util.bit_packstr(util.bit_unpackstr('hello world')) == 'hello world')
	local v=util.bit_packu({[0]=1,0,1})
	assert(v==5)
	local v=util.bit_packstr({[0]=1,0,0,0,1,1})
	assert(v=='1')
	local b=util.bit_unpackstr('hello world')
	local b2 = {[0]=1,0,0,0,1,1}
	for i=0,#b2 do
		table.insert(b,b2[i])
	end
	assert(util.bit_packstr(b)=='hello world1')
end

function m:run(name)
	-- TODO side affects galore
	printf('%s:start\n',name)
	status,msg = xpcall(t[name],util.err_traceback)
	printf('%s:',name)
	if status then
		printf('ok\n')
	else
		printf('failed %s\n',msg)
	end
end

function m:runall()
	for k,v in pairs(t) do
		self:run(k)
	end
end

return m
