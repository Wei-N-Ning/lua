
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function run()
    initialize()
    
end


run()
