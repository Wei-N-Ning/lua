//
// Created by wein on 12/17/17.
//
// this example reduces the contents of "barebone.c" to
// contain the execution of only one lua statement,
// a print() statement
//
// I should see the following string shows up in stdout
//
// there is a cow 1337
//
// This example offers a good start to investigate how lua state works

#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int main(int argc, char **argv) {
    char buff[255] = "print(\"there is a cow 1337\")";
    int error;
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);
    error = luaL_loadstring(pState, buff) || lua_pcall(pState, 0, 0, 0);
    if (error) {
        fprintf(stderr, "%s\n", lua_tostring(pState, -1));
        lua_pop(pState, 1);
    }
    lua_close(pState);
    return 0;
}
