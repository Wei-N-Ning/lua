//
// Created by wein on 12/20/17.
//

#include "callluafuncs.h"

#include <cassert>
#include <iostream>
#include <string>


bool loadSourceCode(struct lua_State *pState, const std::string &sourceCode) {
    if (luaL_loadstring(pState, sourceCode.c_str()) || lua_pcall(pState, 0, 0, 0)) {
        std::cout << "can not load source code: " << lua_tostring(pState, -1) << std::endl;
        return false;
    }
    return true;
}


// call the Lua function init()
bool init(struct lua_State *pState) {
    lua_getglobal(pState, "init");
    auto result = lua_pcall(pState, 0, 0, 0);
    if (result == LUA_OK) {
        return true;
    }
    std::cout << "error running function 'init':" << lua_tostring(pState, -1)
              << std::endl;
    return false;
}


// call the Lua function operate()
int operate(struct lua_State *pState, int arg) {
    int isnum = 0;
    int result = 0;

    // note the order of arguments
    // note also the parameters passed to lua_pcall()
    lua_getglobal(pState, "operate");
    lua_pushinteger(pState, arg);

    //                          num_arg num_result msg_func
    auto ret = lua_pcall(pState, 1,      1,         0);
    if (ret == LUA_OK) {
        result = (int)lua_tointegerx(pState, -1, &isnum);
        if (isnum) {
            return result;
        }
    }
    std::cout << "an error happened in operate(): "
              << lua_tostring(pState, -1) << std::endl;
    return 0;
}


void demoCallLuaFunction(struct lua_State *pState) {

    // function(s) defined here must have global visibility, i.e. they can not be
    // local function; doing so will cause the subsequent call to getglobal to fail
    std::string sourceCode{
        "counter = 0\n"
        "function init()\n"
        "   for i = 1, 5 do\n"
        "       counter = counter + 1\n"
        "   end\n"
        "end\n"
        "function operate(arg)\n"
        "   return counter * arg\n"
        "end\n"
    };
    assert(loadSourceCode(pState, sourceCode));
    assert(init(pState));
    assert(10 == operate(pState, 2));
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    demoCallLuaFunction(pState);

    lua_close(pState);
    return 0;
}

