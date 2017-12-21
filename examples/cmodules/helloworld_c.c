//
// Created by wein on 12/21/17.
//


#include <lua.h>
#include <lauxlib.h>


static int getName(struct lua_State *L) {
    lua_pushstring(L, "Archvile");
    return 1;
}


static int getHealthPoints(struct lua_State *L) {
    lua_pushinteger(L, 300);
    return 1;
}


// this defines a module that encapsulates
// the functions in its own scope

static const struct luaL_Reg module[] = {
    {"getName", getName},
    {"getHealthPoints", getHealthPoints},
    
    // marks the end of the array
    {NULL, NULL}
};


int luaopen_libhelloworld_c(struct lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}
