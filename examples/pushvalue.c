//
// Created by wein on 12/17/17.
//

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


void demoCheckStack(struct lua_State *pState) {
    // if I ask for 0xFFFFF slots, I get an assertion error
    assert(lua_checkstack(pState, 0x10));

    // high level wrapper from aux lib
    // same constraint as above
    luaL_checkstack(pState, 0x10, "not enough stack space for 0x10 slots");
}




void demoPushAndQueryValues(struct lua_State *pState) {
    int error = 0;

    const char *str = "IDFKA";
    lua_Number aDouble = 3.14;
    lua_Integer anInt = 0xDEAD;

    lua_pushnil(pState);
    assert(lua_isnil(pState, -1));
    assert(!lua_isinteger(pState, -1));
    assert(!lua_isstring(pState, -1));

    if (error) {
        fprintf(stderr, "%s\n", lua_tostring(pState, -1));
        lua_pop(pState, 1);
    }
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    demoCheckStack(pState);
    demoPushAndQueryValues(pState);

    lua_close(pState);
    return 0;
}
