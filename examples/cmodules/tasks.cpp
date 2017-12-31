//
// Created by wein on 12/31/17.
//

#include <cstdio>
#include <cstdlib>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace {

int executeStatelessTasks(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    auto numTasks = luaL_len(L, 1);
    for (int idx = 1; idx <= numTasks; ++idx) {
        lua_geti(L, 1, idx);
        luaL_checktype(L, 2, LUA_TFUNCTION);
        lua_call(L, 0, 0);
    }
    return 0;
}

const struct luaL_Reg module[]{
    {"executeStatelessTasks", executeStatelessTasks},

    {nullptr, nullptr}
};

}

extern "C" int luaopen_libtasks(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}
