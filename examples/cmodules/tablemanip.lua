


local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoCallMapArrayFunction()
    local m = require "libtablemanip"
    local t = {}
    for i = 100, 103 do
        t[#t + 1] = i
    end
    local function reduce(x)
        return x / 10
    end
    m.mapArray(t, reduce)
    assert("10.0,10.1,10.2,10.3" == table.concat(t, ','))
end


local function run()
    initialize()
    
    demoCallMapArrayFunction()
end


run()
