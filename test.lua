local hangul = require 'hangul'
local hangul_ic = hangul.ic_new()
while true do
    local char = string.byte(io.read(1))
    if char ~= '\n' then
        hangul_ic:process(char)
    end
    print(hangul.ucs4_to_utf8(hangul_ic:get_preedit_string()))
end
