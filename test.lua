local hangul = require 'hangul'
local hangul_ic = hangul.ic_new()
print(hangul_ic:process(string.byte('a')))
print(hangul_ic:process(string.byte('k')))
print(hangul_ic:process(string.byte('s')))
local result = hangul_ic:flush()
print(hangul.ucs4_to_utf8(result))

