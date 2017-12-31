
local function initialize()
    package.cpath = package.cpath..";/tmp/lua/cmodules/?.so"
end


local function demoIdentifyLuaFunctions()
    local m = require "libtasks"
    
    local tasks = {
        function()
            print("task runner rocks!")
        end,
        
        function() 
            print("gpu boss!")
        end,
        
        function()
            print("sort in linear time!")
        end,
        
        function()
            print("the end...")
        end
    }
    
    m.executeStatelessTasks(tasks)
end


local function run()
    initialize()
    
    demoIdentifyLuaFunctions()
end


run()
