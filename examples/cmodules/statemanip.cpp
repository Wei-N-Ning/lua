//
// Created by wein on 12/21/17.
//

/*
 * Frequently, C functions need to keep some non-local data,
 * that is, data that outlive their invocation.
 *
 * In C, we typically use global (extern) or static variables
 * for this need.
 */


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


namespace {

int setGlobalField(lua_State *L) {
    const char *key = luaL_checkstring(L, 1);
    luaL_checkany(L, 2);
    lua_getglobal(L, "_G");
    if (!lua_istable(L, -1)) {
        return 0;
    }
    lua_pushvalue(L, 2);

    // TODO: verify the stack! Here is what I think the stack holds:
    // [ v   -1 (4)
    //   t   -2 (3)
    //   v   -3 (2)
    //   k ] -4 (1)
    lua_setfield(L, -2, key);
    return 0;
}

int getGlobalField(lua_State *L) {
    const char *key = luaL_checkstring(L, 1);
    lua_getglobal(L, "_G");
    if (!lua_istable(L, -1)) {
        return 0;  // return nil
    }
    lua_getfield(L, -1, key);
    return 1;
}

int setRegField(lua_State *L) {
    const char *key = luaL_checkstring(L, 1);
    luaL_checkany(L, 2);
    lua_pushvalue(L, 2);
    lua_setfield(L, LUA_REGISTRYINDEX, key);
    return 0;
}

int getRegField(lua_State *L) {
    const char *key = luaL_checkstring(L, 1);
    lua_getfield(L, LUA_REGISTRYINDEX, key);
    return 1;
}

const struct luaL_Reg module[] = {
    {"setRegField", setRegField},
    {"getRegField", getRegField},
    {"setGlobalField", setGlobalField},
    {"getGlobalField", getGlobalField},
    {nullptr, nullptr}
};

}


extern "C" int luaopen_libstatemanip(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}
