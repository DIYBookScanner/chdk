--[[
module for converting between numbers and binary strings
usage:
bs=require('binstr')
wbdata=bs.unpack(get_prop_str(0x10d,0x1c)) -- return propset 3 white balance as 7 ints
]]

local binstr = {}
--[[
convert number or array of numbers into a binary string
size specifies the number of bytes to use from each number, default 4
]]
binstr.pack = function(val,size)
	if size == nil then
		size = 4
	elseif size < 1 or size > 4 then
		error('invalid size')
	end
	if type(val) ~= 'table' then
		val = {tonumber(val)}
	end
	local bytes = {}
	for i,num in ipairs(val) do
		for j = 1, size do
			table.insert(bytes,bitand(num,0xFF))
			num = bitshru(num,8)
		end
	end
	return string.char(unpack(bytes))
end

--[[
read a single number of the specified size from str
defaults to 4 bytes at start
does not handle negative pos
does not sign extend < 32 bit size
]]
binstr.getnum = function(str,size,pos) 
	if pos == nil then
		pos = 1
	elseif pos < 1 then
		error('invalid pos')
	end
	if size == nil then
		size = 4
	elseif size > 4 or size < 1 then
		error('invalid size')
	end
	local e = pos + size - 1
	if string.len(str) < e then
		return
	end
	local bytes = {string.byte(str,pos,e)}
	local num = 0
	for i=1,#bytes do
		num = bitor(num,bitshl(bytes[i],8*(i-1)))
	end
	return num
end

--[[
convert a string to an array of numbers
size specifies the size of the numbers in the packed array, default 4
]]
binstr.unpack = function(str,size)
	if size == nil then
		size = 4
	elseif size < 1 or size > 4 then
		error('invalid size')
	end
	if type(str) ~= 'string' then
		error('expected string')
	end
	if (string.len(str)/size)*size ~= string.len(str) then
		error('string lenght not multiple of size')
	end
	local i = 1
	local r = {}
	while i <= string.len(str) do
		table.insert(r,binstr.getnum(str,size,i))
		i = i+size
	end
	return r
end

return binstr
