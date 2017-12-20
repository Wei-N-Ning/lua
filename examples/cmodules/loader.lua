
function displayCPath()
    --~ /usr/local/lib/lua/5.3/?.so
    --~ /usr/lib/x86_64-linux-gnu/lua/5.3/?.so
    --~ /usr/lib/lua/5.3/?.so
    --~ /usr/local/lib/lua/5.3/loadall.so
    --~ ./?.so

    for k in string.gmatch(package.cpath, "[^;]+") do
        print(k)
    end
end


local function run()
    package.cpath = package.cpath..";/tmp/luaExamples/cmodules/?.so"
    displayCPath()
    
    local m = require "liboneshot"
    print(m)
end


run()
