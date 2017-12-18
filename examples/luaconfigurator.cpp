//
// Created by wein on 12/18/17.
//

#include "luaconfigurator.h"

#include <cassert>
#include <string>


int getInteger(struct lua_State *pState, const char *name) {
    int isnum = 0;
    int result = 0;
    lua_getglobal(pState, name);
    result = (int)lua_tointegerx(pState, -1, &isnum);
    lua_pop(pState, 1);
    return result;
}


bool loadConfig(struct lua_State *pState) {
    std::string config(
        "IDKFA = 200\n"
        "IDDQD = 300\n"
        "IDNOCLIP = -400\n"
        "local function init()\n"
            "IDNOCLIP = 400\n"
        "end\n"
        "init()\n"
    );
    if (luaL_loadstring(pState, config.c_str()) || (lua_pcall(pState, 0, 0, 0))) {
        return false;
    };
    return true;
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    assert(loadConfig(pState));
    assert(200 == getInteger(pState, "IDKFA"));
    assert(300 == getInteger(pState, "IDDQD"));
    assert(400 == getInteger(pState, "IDNOCLIP"));

    lua_close(pState);
    return 0;
}