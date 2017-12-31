
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoDirectoryIteratorC()
    local m = require "libdiriter_c"
    local count = 0
    
    for fname in m.open("/tmp") do
        count = count + 1
    end
    assert(count > 1)
end


local function demoDirectoryIteratorCXX()
    local m = require "libdiriter_cxx"
    print(m)
end


local function run()
    initialize()
    
    demoDirectoryIteratorC()
    demoDirectoryIteratorCXX()
end


run()
