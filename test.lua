local hangul = require 'hangul'
local hangul_ic = hangul.ic_new()
print(hangul_ic:process(string.byte('a')))
print(hangul_ic:process(string.byte('k')))
print(hangul_ic:process(string.byte('s')))
print(hangul_ic:flush())
