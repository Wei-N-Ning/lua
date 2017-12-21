//
// Created by wein on 12/21/17.
//

#include <lua.h>


static int getLabel(struct lua_State *L) {
    lua_pushstring(L, "hello world");
    return 1;
}


// this is one quick way to register a C function;
// once the shared library is imported in Lua,
// a global function called getLabel() will be
// callable from the Lua source code;
// see helloworld.lua for Lua source code

int luaopen_libhelloworld_f(struct lua_State *L) {
    lua_pushcfunction(L, getLabel);
    lua_setglobal(L, "getLabel");
    return 1;
}
