
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


local function demoAccessScopedCXXFunction()
    local t = nil
    local err = nil
    local m = require "libhelloworld_cxx"
    t, err = m.newCreature(1)
    assert(t == nil)
    t, err = m.newCreature("lich")
    assert(t == nil)
    t, err = m.newCreature("dwarf")
    assert("hp, damage, skill" == table.concat(t, ', '))
    t, err = m.newCreature("orc")
    assert("hp, damage" == table.concat(t, ', '))
end


local function demoAccessBoostFunction()
    local m = require "libhelloworld_boost"
    assert(m.exists("/tmp"))
    assert(m.isfile("/bin/sh"))
end


local function run()
    initialize()
    
    demoAccessGlobalFunction()
    demoAccessScopedFunction()
    demoAccessScopedCXXFunction()
    demoAccessBoostFunction()
end


run()
