package.cpath = '../?.so;' .. package.cpath
local hangul = require 'hangul'
local hangul_ic = hangul.ic_new()
while true do
    local char = string.byte(io.read(1))
    hangul_ic:process(char)
    io.write(hangul.ucs4_to_utf8(hangul_ic:get_commit_string()))
end
