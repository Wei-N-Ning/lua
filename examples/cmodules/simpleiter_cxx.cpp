//
// Created by wein on 12/30/17.
//

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


namespace {

class Xrange {
public:
    explicit Xrange(int start, int end, int step);
    int next (lua_State *L);
private:
    int end = 0;
    int step = 0;
    int v = 0;
};

Xrange::Xrange(int start, int end, int step)
: end(end), step(step), v(start) {
}

int Xrange::next(lua_State *L) {
    if (v >= end) {
        return 0;
    }
    lua_pushinteger(L, v);
    v += step;
    return 1;
}

int _xrangeImpl(lua_State *L) {
    auto pXr = (Xrange *)lua_touserdata(L, lua_upvalueindex(1));
    return pXr->next(L);
}

int xrange(lua_State *L) {
    auto start = (int)luaL_checkinteger(L, 1);
    auto end = (int)luaL_checkinteger(L, 2);
    int isnum;
    int step{(int)lua_tointegerx(L, 3, &isnum)};
    if (!(isnum && step > 0)) {
        step = 1;
    }
    auto pXr = (Xrange *)lua_newuserdata(L, sizeof(Xrange));
    *pXr = Xrange(start, end, step);
    lua_pushcclosure(L, _xrangeImpl, 1);
    return 1;
}

}

const struct luaL_Reg module[] = {
    {"xrange", xrange},

    {nullptr, nullptr}
};

extern "C" int luaopen_libsimpleiter_cxx(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}
