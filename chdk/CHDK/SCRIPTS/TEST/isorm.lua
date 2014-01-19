--[[
@title test real vs market ISO
@param a min ISO
@default a 80
@param b max ISO
@default b 3200
@param c half shoot delay
@default c 1000
@param d test MIN-100
@default d 0
@range d 0 1
]]

--[[
This script tries to set the ISO mode to each available ISO setting and logs the
corresponding "real" and "market" sv96 values to A/ISORM.CSV

The min and max should be set to the lowest and highest values available in the 
Canon UI.

Use the logged values to define
CAM_SV96_MARKET_LOW
CAM_SV96_REAL_LOW 
CAM_SV96_MARKET_OFFSET
in platform_camera.h

See http://chdk.setepontos.com/index.php?topic=10341.0 for discussion

On some cameras (those with an ISO dial?), setting the ISO mode propcase does not work
reliably. On these cameras, the process should be done manually by setting each ISO mode
using the canon UI, half pressing until the props update, and recording the prop values

CHDK ISO overrides and auto-ISO should be disabled before running the script.

The test MIN-100 options will record single ISO unit steps from the min value to 100
This should not normally be needed.
]]

half_shoot_delay = c
test_low_vals = (d == 1)

capmode=require'capmode'
props=require'propcase'
if not get_mode() then
	print('switching to rec')
	set_record(1)
	while not get_mode() do sleep(100) end
end
sleep(1000)
-- switch to P, should exist on all cams and have manual ISO
capmode.set('P')
sleep(500)
if capmode.get_name() ~= 'P' then
	error('switch to P failed')
end

function write_csv(fh,vals)
	-- TODO doesn't try to quote
	fh:write(table.concat(vals,',')..'\n')
end

function log_iso_values(fh,iso)
	set_prop(props.ISO_MODE,iso)
	print('test',iso)
	sleep(100)
	press('shoot_half')
	repeat sleep(10) until get_shooting()
	sleep(half_shoot_delay)
	write_csv(fh,{iso,get_prop(props.SV),get_prop(props.SV_MARKET)});
	release('shoot_half')
	sleep(100)
end

function init_log(fname)
	local fh=io.open(fname,'wb')
	if not fh then
		error('failed to open log')
	end
	write_csv(fh,{'platform','build','build time'})
	local b = get_buildinfo()
	write_csv(fh,{
		b.platform .. ' ' .. b.platsub,
		b.build_number..'-'..b.build_revision,
		b.build_date .. ' ' .. b.build_time
	})

	write_csv(fh,{'iso','sv96','sv96_m'})
	return fh
end

function run_test(start_iso,end_iso)
	local fh = init_log('A/ISORM.CSV')
	local iso = start_iso
	-- treat first step as special, assume remaining double
	if iso < 100 then
		-- test in 1 unit increments for sub 100 values
		if test_low_vals then
			while iso < 100 do
				log_iso_values(fh,iso)
				iso = iso + 1
			end
		else
			log_iso_values(fh,iso)
			iso = 100
		end
	end
	while iso <= end_iso do
		log_iso_values(fh,iso)
		iso = iso * 2
	end
	fh:close()
end
run_test(a,b)
