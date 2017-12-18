//
// Created by wein on 12/18/17.
//

#include "luaconfigurator.h"

#include <iostream>


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    lua_close(pState);
    return 0;
}