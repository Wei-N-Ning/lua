
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoBoolArrayCreation()
    local m = require "libcustomtypes"
    local ok, msg = pcall(
        function ()
            return m.create(-10)
        end
    )
    assert(false == ok)  -- bit array size must be greater than 1
    
    -- lua_newuserdata() will put the struct on #1 on stack
    -- NOTE: one can not inspect userdata using dir()-like method
    local ba = m.create(13)
    assert(13 == m.size(ba))
end


local function demoSetGetBoolArrayMembers()
    local m = require "libcustomtypes"
    local ba = m.create(13)
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
    
    -- the getter function validates the first two arguments in the
    -- same way
    ok, err = pcall(
        function()
            m.set(ba, 999)
        end
    )
    assert(false == ok)
    
    -- test the getter function, retrieving the initial state of the 
    -- bits
    for idx = 1, 6 do
        assert(false == m.get(ba, idx))
    end
    
    -- the setter implicitly creates a boolean value based on the second
    -- argument; Lua value object has a field that indicates the boolean 
    -- state of this value
    m.set(ba, 1, true)
    m.set(ba, 2, 1)
    m.set(ba, 3, 1.0)
    m.set(ba, 4, "1")
    m.set(ba, 5, {1})
    m.set(ba, 6, ba)
    
    for idx = 1, 6 do
        assert(true == m.get(ba, idx))
    end
end


local function demoResetBoolArray()
    local m = require "libcustomtypes"
    local ba = m.create(6)
    for idx = 1, 6 do
        m.set(ba, idx, "1")
    end
    m.reset(ba)
    for idx = 1, 6 do
        assert(false == m.get(ba, idx))
    end
end


local function run()
    initialize()
   
    demoBoolArrayCreation()
    demoSetGetBoolArrayMembers()
    demoResetBoolArray()
end


run()
