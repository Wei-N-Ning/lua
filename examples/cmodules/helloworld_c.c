//
// Created by wein on 12/21/17.
//


#include <lua.h>


static int getName(struct lua_State *L) {
    lua_pushstring(L, "Archvile");
    return 1;
}


int luaopen_libhelloworld_c(struct lua_State *L) {
    return 0;
}
