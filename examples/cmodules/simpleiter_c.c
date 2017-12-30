//
// Created by wein on 12/30/17.
//

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


typedef struct Range {
    int start;
    int end;
    int step;
} RangeT;

typedef RangeT * RangePtr;


static int _xrangeImpl(lua_State *L) {
    RangePtr pRange = (RangePtr)lua_touserdata(L, lua_upvalueindex(1));
    int v = pRange->start;
    if (v >= pRange->end) {
        return 0;
    }
    v += pRange->step;
    lua_pushinteger(L, pRange->start);
    pRange->start = v;
    return 1;
}


static int xrange(lua_State *L) {
    int start = (int)luaL_checkinteger(L, 1);
    int end = (int)luaL_checkinteger(L, 2);
    int step;
    int isnum = 0;
    step = (int)lua_tointegerx(L, 3, &isnum);
    if (isnum && step > 0) {
        ;
    } else {
        step = 1;
    }
    RangePtr pRange = (RangePtr)lua_newuserdata(L, sizeof(RangeT));
    pRange->start = start;
    pRange->end = end;
    pRange->step = step;
    lua_pushcclosure(L, _xrangeImpl, 1);
    return 1;
}


static const struct luaL_Reg module[] = {
    {"xrange", xrange},

    {NULL, NULL}
};


int luaopen_libsimpleiter_c(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}


