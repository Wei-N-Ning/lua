//
// Created by wein on 12/21/17.
//

#include <boost/filesystem.hpp>


extern "C" {

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

static int exists(struct lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    int ret{boost::filesystem::exists(path)};
    lua_pushinteger(L, ret);
    return 1;
}

static int isfile(struct lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    int ret{boost::filesystem::is_regular_file(path)};
    lua_pushinteger(L, ret);
    return 1;
}

static const struct luaL_Reg module [] = {
    {"exists", exists},
    {"isfile", isfile},

    {nullptr, nullptr}
};

int luaopen_libhelloworld_boost(struct lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}

}