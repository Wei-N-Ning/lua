
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


-- the CXX implementation is flawed
-- the raw buffer, the "userdata", is completely managed by Lua, 
-- therefore there is no chance for the CXX object destructor to run, 
-- because Lua garbage collector does not even know this buffer  
-- is "an object";
-- CXX smart pointer can't help either; the RAII idiom relies on scope, 
-- which is not how Lua GC works 
local function demoDirectoryIteratorCXX()
    local m = require "libdiriter_cxx"
    local count = 0
    
    for fname in m.open("/tmp") do
        count = count + 1
    end
    assert(count > 1)
end


local function run()
    initialize()
    
    demoDirectoryIteratorC()
    demoDirectoryIteratorCXX()
end


run()
