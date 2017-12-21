
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoAccessGlobalFunction()
    local m = require "libhelloworld_f"
    assert("hello world" == getLabel())
end


local function demoAccessScopedFunction()
    local m = require "libhelloworld_c"
    assert("Archvile" == m.getName())
    assert(300 == m.getHealthPoints())
end


local function run()
    initialize()
    
    demoAccessGlobalFunction()
    demoAccessScopedFunction()
end


run()
