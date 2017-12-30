
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoIteration()
    local m = require "libdiriter"
    
    for fname in m.open("/tmp") do
    end
end


local function run()
    initialize()
    
    demoIteration()
end


run()
