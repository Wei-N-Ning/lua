
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local source = [[
local function main()
    print("called main()")
end
]]


local function demo()
    local m = require "liblproc"
    
    m.start(source)
    m.start(source)
    
end


local function run()
    initialize()
    
    demo()
end


run()
