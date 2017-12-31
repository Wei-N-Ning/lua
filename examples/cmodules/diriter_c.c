//
// Created by wein on 12/30/17.
//

#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


/*
 * In this simple case, the bag of custom data contains only one
 * pointer; in other cases this bag may hold many fields, see
 * customtypes.cpp example
 */
typedef DIR * DirPtr;

static int iterator(lua_State *L);

static int destructor(lua_State *L) {
    DirPtr dirPtr = *(DirPtr *)lua_touserdata(L, 1);
    printf("calling destructor\n");
    if (dirPtr) {
        printf("closing directory\n");
        closedir(dirPtr);
    }
    return 0;
}


/*
 * see my note: Lua C module function scoping and runtime issue
 * There is a good reason to keep each exported function internal(ly linked)
 */
static int open(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    DirPtr *pDirPtr = (DirPtr *)lua_newuserdata(L, sizeof(DirPtr));
    *pDirPtr = NULL;
    luaL_getmetatable(L, "luaExamples.Dir");
    lua_setmetatable(L, -2);
    *pDirPtr = opendir(path);
    if (*pDirPtr == NULL) {
        luaL_error(
            L,
            "Can not open %s: %s", path, strerror(errno));
    }
    lua_pushcclosure(L, iterator, 1);
    return 1;
}

static int iterator(lua_State *L) {
    DirPtr *pDirPtr = (DirPtr *)lua_touserdata(L, lua_upvalueindex(1));
    DirPtr dirPtr = *pDirPtr;
    struct dirent *entry = readdir(dirPtr);
    if (entry) {
        lua_pushstring(L, entry->d_name);
        return 1;
    }
    return 0;
}

static const struct luaL_Reg module[] = {
    {"open", open},

    {NULL, NULL}
};

int luaopen_libdiriter_c(lua_State *L) {
    luaL_newmetatable(L, "luaExamples.Dir");
    lua_pushcfunction(L, destructor);
    lua_setfield(L, -2, "__gc");

    luaL_newlib(L, module);
    return 1;
}
