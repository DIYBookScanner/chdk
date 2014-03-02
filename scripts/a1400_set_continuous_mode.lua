--[[
Authors: nafraf
         kariluoma

lua native calls need to be enabled 
(Main Menu -> Miscallaneous -> Enable Lua Native Calls?)
]]

--[[
@title Set a1400 to continuous mode over chdkptp
]]


function enter_shoot_mode()
    if ( get_mode() == false ) then
        set_record(1)
        while ( get_mode() == false ) do sleep(100) end
    end
    sleep(1000)
end

--main program
    if ( get_config_value(119) == 0 ) then 
        printf("Failed : Lua Native Calls not enabled") 
        return
    end 

    enter_shoot_mode()
    call_event_proc("UI.CreatePublic")
    set_capture_mode(2)
    call_event_proc("PTM_SetCurrentItem",0x8002,2)
    call_event_proc("PTM_SetCurrentItem",0x800D,1)
