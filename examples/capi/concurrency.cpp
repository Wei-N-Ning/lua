//
// Created by wein on 1/1/18.
//


#include <cassert>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}


void demoMoveValuesBetweenTwoStacks(lua_State *L) {
    lua_State *L1 = lua_newthread(L);
    lua_pushinteger(L, 0xDEAD);
    lua_pushinteger(L1, 0xBEAF);
    lua_xmove(L1, L, 1);
    /*
     * 3: 0xBEAF (top/-1)
     * 2: 0xDEAD
     * 1: L1
     */
    assert(0xDEAD == luaL_checkinteger(L, 2));
    assert(0xBEAF == luaL_checkinteger(L, 3));
    assert(3 == lua_gettop(L));
    assert(0xBEAF == luaL_checkinteger(L, -1));
    assert(0 == lua_gettop(L1));
}


int main(int argc, char **argv) {
    struct lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    demoMoveValuesBetweenTwoStacks(L);

    lua_close(L);
    return 0;
}

