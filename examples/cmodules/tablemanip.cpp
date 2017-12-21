//
// Created by wein on 12/21/17.
//

extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

}

namespace {

int mapArray(lua_State *L) {
    luaL_checktype(L, 1, LUA_TTABLE);
    luaL_checktype(L, 2, LUA_TFUNCTION);

    auto n = luaL_len(L, 1);
    for (int idx = 1; idx <= n; ++idx) {
        // push the function, #2 to top
        // [ f
        //   table ]
        lua_pushvalue(L, 2);

        // get idx-th element from table at #1, push it to top
        lua_geti(L, 1, idx);

        // stack at this moment:
        // [ element
        //   f
        //   table ]
        // call f(element) -> n, push n to top,
        // removing element and f from the stack
        lua_call(L, 1, 1);

        // stack at this moment:
        // [ n
        //   table ]
        // removing n from the stack
        lua_seti(L, 1, idx);
    }

    return 0;
}

const struct luaL_Reg module [] = {
    {"mapArray", mapArray},
    {nullptr, nullptr}
};

}


extern "C" int luaopen_libtablemanip(struct lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}
