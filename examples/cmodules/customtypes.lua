
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
    local ba = m.create(6)
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
    for idx = 1, m.size(ba) do
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
    
    for idx = 1, m.size(ba) do
        assert(true == m.get(ba, idx))
    end
end


local function demoResetBoolArray()
    local m = require "libcustomtypes"
    local ba = m.create(6)
    for idx = 1, m.size(ba) do
        m.set(ba, idx, "1")
    end
    m.reset(ba)
    for idx = 1, m.size(ba) do
        assert(false == m.get(ba, idx))
    end
end


-- when the given userdata is not a BitArray lua will throw an error
local function demoTypeSafety()
    local m = require "libcustomtypes"
    local ba = m.create(6)
    
    -- bad argument #1 to 'size' 
    -- (luaExamples.BitArray expected, got FILE*)
    local ok, msg = pcall(
        function()
            return m.size(io.stdin)
        end
    )
    assert(false == ok)
end


-- DO NOT RUN THIS FUNCTION!
-- to create the OO interface in Lua code by exploiting the __index 
-- meta field;
-- We cannot set the metatable of a userdata from Lua but we can 
-- get it;
-- Using C/C++ to design and expose the OO interface can enforce 
-- better encapsulation;
local function demoDesignOOInterfaceInLua()
    local m = require "libcustomtypes"
    local ba = m.create(6)
    do -- add method look up table
        local baMetatable = getmetatable(ba)
        local methodTable = {}
        baMetatable.__index = methodTable
        methodTable.set = m.set
        methodTable.get = m.get
    end
    assert(false == ba:get(1))
    ba:set(1, 1)
    assert(true == ba:get(1))
end


local function demoDesignOOInterfaceInCXX()
    local m = require "libcustomtypes"
    local ba = m.create(6)
    
    -- Lua Book P284, Remember that a:size() is equivalent to a.size(a)
    assert(6 == ba:size())
    assert(6 == ba.size(ba))
    
    assert(false == ba:get(1))
    ba:set(1, 1)
    assert(true == ba:get(1))
end


local function demoMagicMethodToStringInCXX()
    local m = require "libcustomtypes"
    local ba = m.create(13)
    
    assert("BitArray<13>" == string.format("%s", ba))
    assert("BitArray<13>" == m.toStr(ba))
end

-- DO NOT RUN THIS FUNCTION!
-- create metafields so that BitArray acts like normal Array;
-- one can use the Array semantics, a[n] on BitArray;
local function demoArraySemanticsInLua()
    local m = require "libcustomtypes"
    local ba = m.create(13)
    do
        local metatable = getmetatable(ba)
        metatable.__index = m.get
        metatable.__newindex = m.set
        metatable.__len = m.size
    end
    assert(13 == #ba)
    assert(false == ba[1])
    ba[1] = "1"
    assert(true == ba[1])
end


local function demoArraySemanticsInCXX()
    local m = require "libcustomtypes"
    local ba = m.create(13)
    assert(13 == #ba)
    
    -- array indexing is not enabled in this build
    assert(false == ba:get(13))
    ba[13] = "1"
    assert(true == ba:get(13))
end


local function run()
    initialize()
   
    demoBoolArrayCreation()
    demoSetGetBoolArrayMembers()
    demoResetBoolArray()
    
    demoTypeSafety()
    
    demoDesignOOInterfaceInCXX()
    demoMagicMethodToStringInCXX()
    
    demoArraySemanticsInCXX()
end


run()
