--[[
@title textbox test
]]

-- Test user input using text box
-- parameters are:
--      text box title
--      prompt
--      initial value of string (user can edit this)
--      maximum length allowed for input
f = textbox("Text Box Title", "Enter some text", "", 20)

print(f)
