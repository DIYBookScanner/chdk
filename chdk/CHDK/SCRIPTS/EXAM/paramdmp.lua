--[[ 
@param a autonumber paramNNN.log
@range a 0 1
@default a 1

dump parameters from internal flash memory
NOTE:
parameter ids may vary between cameras, so scripts
using them will not be portable
--]]
autonumber = (a==1)

if autonumber then
	local pfx = 'A/param'
	for i=0,999 do
		local fn = string.format('%s%03d.log',pfx,i)
		if not os.stat(fn) then
			filename = fn
			break
		end
	end
	if not filename then
		error('no available filenames!')
	end
else
	filename = "A/paramdmp.log"
end
logfile,err=io.open(filename,"wb")

if not logfile then
	error('failed to open '..tostring(filename)..': ' .. tostring(err))
end

print(string.format('dump %d param %s',get_flash_params_count(),filename))

for i=0,get_flash_params_count()-1 do
	s,n = get_parameter_data(i)
	logfile:write(i,": ")
	if s then
		-- string as hex
		for j=1,s:len() do
			logfile:write(string.format("0x%02x ",s:byte(j)))
		end
		-- string quoted
		logfile:write(string.format("[%q]",s))
		-- as number, if available
		if n then
			logfile:write(string.format(" 0x%x %d",n,n))
		end
	else
		logfile:write("nil")
	end
	logfile:write("\n")
end
logfile:close()

