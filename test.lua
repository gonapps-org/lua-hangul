local hangul = require 'hangul'
local hangul_ic = hangul.ic_new()
print(hangul_ic:process(97))
print(hangul_ic:process(107))
print(hangul_ic:process(115))
print(hangul_ic:flush())
