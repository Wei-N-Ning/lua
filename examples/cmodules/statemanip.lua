
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoSetGetGlobalRegistryField()
    local m = require "libstatemanip"
    
    -- we really should not use this function except for debugging.
    assert(m.getRegField("_PRELOAD") == debug.getregistry()["_PRELOAD"])
    
    m.setRegField("level.map", "brecourt")
    assert("brecourt" == m.getRegField("level.map"))
    
    local function foo()
    end
    m.setRegField("level.init", foo)
    assert(foo == m.getRegField("level.init"))
    
    m.setRegField("level.numplayers", 30)
    assert(30 == m.getRegField("level.numplayers"))
end


local function demoSetGetGlobalVariables()
    local m = require "libstatemanip"
        
    -- if I name the field "level_maxtime" the value can be read from a 
    -- global variable of the same name!! 
    -- this looks like a side effect to me but recall how Lua 
    -- handle scoping from the earlier chapter on variables
    m.setGlobalField("level_maxtime", 13.13)
    assert(13.13 == _G["level_maxtime"])
    assert(13.13 == level_maxtime)
    assert(13.13 == m.getGlobalField("level_maxtime"))
end


local function run()
    initialize()
    
    demoSetGetGlobalRegistryField()
    demoSetGetGlobalVariables()
end


run()
