//
// Created by wein on 12/30/17.
//

#include <dirent.h>
#include <cerrno>
#include <cstring>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


namespace {

using DirPtr = DIR *;

int iterator(lua_State *L);

int open(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    auto pDirPtr = (DirPtr *)lua_newuserdata(L, sizeof(DirPtr));
    *pDirPtr = nullptr;
    luaL_getmetatable(L, "luaExamples.Dir");
    lua_setmetatable(L, -2);
    *pDirPtr = opendir(path);
    if (*pDirPtr == nullptr) {
        luaL_error(
            L,
            "Can not open %s. Err: %s", path, strerror(errno));
    }
    lua_pushcclosure(L, iterator, 1);
    return 1;
}

int iterator(lua_State *L) {
    auto pDirPtr = (DirPtr *)lua_touserdata(L, lua_upvalueindex(1));
    auto dirPtr = *pDirPtr;
    struct dirent *entry = readdir(dirPtr);
    if (entry) {
        lua_pushstring(L, entry->d_name);
        return 1;
    }
    return 0;
}

}


static const struct luaL_Reg module[] = {
    {"open", open},

    {nullptr, nullptr}
};


extern "C" int luaopen_libdiriter(lua_State *L) {
    luaL_newmetatable(L, "luaExamples.Dir");
    luaL_newlib(L, module);
    return 1;
}
