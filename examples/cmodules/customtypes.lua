
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoBoolArrayCreation()
    local m = require "libcustomtypes"
    local ok, msg = pcall(
        function ()
            return m.createBoolArray(-10)
        end
    )
    assert(false == ok)  -- bit array size must be greater than 1
    
    -- lua_newuserdata() will put the struct on #1 on stack
    local ba = m.createBoolArray(13)
    
end


local function demoSetBoolArrayMember()
    local m = require "libcustomtypes"
    local ba = m.createBoolArray(13)
    local ok = false
    local err = ""
    
    -- demonstrate the effect of lua_touserdata() and luaL_argcheck()
    -- the latter checks whether the former returns a non-null pointer
    ok, err = pcall(
        function()
            m.set(1)
        end
    )
    assert(false == ok)
    
    -- check whether the member index is legit (from 1 to n)
    ok, err = pcall(
        function()
            m.set(ba, 0)
        end
    )
    assert(false == ok)
    
end


local function run()
    initialize()
   
    demoBoolArrayCreation()
    demoSetBoolArrayMember()
end


run()
