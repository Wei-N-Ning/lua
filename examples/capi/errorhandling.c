//
// Created by wein on 12/18/17.
//

#include <assert.h>
#include <stdio.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


int code(struct lua_State *pState) {
    return 1111;
}

void demoRunCodeInProtectedMode(struct lua_State *pState) {
    int ret = 0;
    lua_pushcfunction(pState, code);
    ret = lua_pcall(pState, 0, 0, 0);
    if (ret != 0) {
        printf("error in code()\n");
    }
}


int main(int argc, char **arv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    demoRunCodeInProtectedMode(pState);

    lua_close(pState);
    return 0;
}