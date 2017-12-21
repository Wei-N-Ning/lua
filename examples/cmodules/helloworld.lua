
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoAccessGlobalFunction()
    local m = require "libhelloworld_f"
    print(m)
    print(getLabel)
    print(getLabel())
end


local function demoAccessScopedFunction()
    local m = require "libhelloworld_c"
    print(m)
end


local function run()
    initialize()
    
    demoAccessGlobalFunction()
    demoAccessScopedFunction()
end


run()
