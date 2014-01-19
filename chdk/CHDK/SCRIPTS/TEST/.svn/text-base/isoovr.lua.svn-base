--[[
@title test iso override
@param a shoot
@default a 0
@range a 0 1
@param b half shoot delay
@default b 1000
]]
--[[
This script can be used to test ISO overrides, recording the resulting sv96
and delta_sv values to isoovr.csv

The values to be tested can be set in the iso_test_vals array below.

This script does NOT verify the range of ISO overrides that actually work,
it only records the values generated in the override process.

If the shoot option is, it will attempt to hold the other exposure settings
constant. This may help determine the working range from images.

Using shoot mode may cause occasional ASSERTs crashes in FsIoNotify.c due to
logging, shooting and config saving hitting filehandle limits.
]]
override_test_shoot = (a == 1)
half_shoot_delay = b

-- ISO values to test, modify to taste 
iso_test_vals = {50,60,80,100,486,800,972,3200}

iso_over_save = get_config_value(106)
iso_over_val_save = get_config_value(105)

function restore()
	set_config_value(106,iso_over_save)
	set_config_value(105,iso_val_save)
end

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

filename = 'A/ISOOVR.CSV'

function write_csv(self,vals)
	local fh = self.fh
	local tempfh
	if not self.fh then
		fh=io.open(self.fname,'ab')
		tempfh = true
	end
	if not fh then
		error('failed to open log')
	end
	fh:write(table.concat(vals,',')..'\n')
	if tempfh then
		fh:close();
	end
end

function init_log(fname,header)
	local t = {fname=fname,write=write_csv}
	t.fh = io.open(fname,'wb')
	if not t.fh then
		error('failed to open log')
	end

	t:write({'platform','build','build time'})
	local b = get_buildinfo()
	t:write({
		b.platform .. ' ' .. b.platsub,
		b.build_number..'-'..b.build_revision,
		b.build_date .. ' ' .. b.build_time
	})

	t:write(header)
	t.fh:close()
	t.fh=nil
	return t
end

function run_test(start_iso,end_iso)
	-- don't set any override for initial exposure test
	set_config_value(106,0)
	-- keep tv and AV at fixed at initial values throught test
	-- will be based on cams current ISO
	local tv,av
	if override_test_shoot then
		set_nd_filter(2) -- force ND off (if present)
		press('shoot_half')
		repeat sleep(10) until get_shooting()
		sleep(half_shoot_delay)
		if not tv then
			tv = get_tv96()
			av = get_av96()
		end
		release('shoot_half')
	end
	-- enable iso override
	set_config_value(106,1)
	local log = init_log('A/ISOOVR.CSV',{'exp','iso','sv96','sv96_m','delta_sv'})
	sleep(100)
	for i,iso in ipairs(iso_test_vals) do
		set_config_value(105,iso)
		print('test',iso)
		if override_test_shoot then
			set_tv96_direct(tv)
			set_av96_direct(av)
			set_nd_filter(2) -- force ND off
		end
		sleep(100)
		press('shoot_half')
		repeat sleep(10) until get_shooting()
		sleep(half_shoot_delay)

		log:write({get_exp_count()+1,iso,get_prop(props.SV),get_prop(props.SV_MARKET),get_prop(props.DELTA_SV)});
		sleep(100)
		if override_test_shoot then
			click('shoot_full')
			repeat sleep(10) until not get_shooting()
			sleep(500)
		else
			release('shoot_half')
		end
		sleep(100)
	end
end

run_test(a,b)
restore()
