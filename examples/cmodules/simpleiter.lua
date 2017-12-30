
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoIterationFunctionC()
    local m = require "libsimpleiter_c"
    local s = ""
    
    -- forward iteration only
    s = ""
    for num in m.xrange(30, 38, 3) do
        s = s..num
    end
    assert("303336" == s)
    
    -- step has to be greater than 0; by default step is 1
    s = ""
    for num in m.xrange(30, 29, -1) do
        s = s..num
    end
    assert("" == s)
    
    s = ""
    for num in m.xrange(30, 33) do
        s = s..num
    end
    assert("303132" == s)
end


local function demoIterationFunctionCXX()
    local m = require "libsimpleiter_cxx"
    local s = ""
    
    -- same functionality but implemented in a functor (as opposed 
    -- to using POD struct)
    s = ""
    for num in m.xrange(30, 38, 3) do
        s = s..num
    end
    assert("303336" == s)
    
    s = ""
    for num in m.xrange(30, 29, -1) do
        s = s..num
    end
    assert("" == s)
    
    s = ""
    for num in m.xrange(30, 32) do
        s = s..num
    end
    assert("3031" == s)
end


local function run()
    initialize()
    
    demoIterationFunctionC()
    demoIterationFunctionCXX()
end


run()
