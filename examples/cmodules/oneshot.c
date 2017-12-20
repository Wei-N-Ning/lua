//
// Created by wein on 12/20/17.
//
// C functions that take one argument and return one value
//

#include <math.h>

#include <lua.h>


static int l_sin(struct lua_State *L) {
    int isnum;
    double d = lua_tonumberx(L, 1, &isnum);
    if (!isnum) {
        return 0;
    }
    lua_pushnumber(L, sin(d));
    return 1;
}

