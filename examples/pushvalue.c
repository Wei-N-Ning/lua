//
// Created by wein on 12/17/17.
//

#include <assert.h>
#include <stdio.h>
#include <stddef.h>
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




void demoPushAndQueryValueTypes(struct lua_State *pState) {
    const char *str = "IDFKA";
    lua_Number aDouble = 3.14;
    lua_Integer anInt = 0xDEAD;

    lua_pushnil(pState);
    assert(lua_isnil(pState, -1));
    assert(!lua_isinteger(pState, -1));
    assert(!lua_isstring(pState, -1));
    lua_pop(pState, 1);

    lua_pushnumber(pState, aDouble);
    assert(lua_isnumber(pState, -1));
    assert(lua_isstring(pState, -1));
    lua_pop(pState, 1);

    lua_pushstring(pState, str);
    assert(lua_isstring(pState, -1));
    lua_pop(pState, 1);
}


void demoPushAndQueryValues(struct lua_State *pState) {
    int canConvertToValue = 0;
    const char *str = "IDDQD";
    const char *oStr = NULL;
    size_t oStrLength = 0;

    lua_pushboolean(pState, 1);
    assert(1 == lua_toboolean(pState, -1));
    lua_pop(pState, 1);

    lua_pushinteger(pState, 0xDEAD);
    assert(0xDEAD == lua_tointegerx(pState, -1, &canConvertToValue));
    assert(canConvertToValue);
    lua_pop(pState, 1);

    lua_pushnumber(pState, 3.14);
    lua_tonumberx(pState, -1, &canConvertToValue);
    assert(canConvertToValue);
    lua_pop(pState, 1);

    lua_pushstring(pState, str);
    oStr = lua_tolstring(pState, -1, &oStrLength);
    assert(5 == oStrLength);
    assert(0 == strcmp(str, oStr));
    lua_pop(pState, 1);

    lua_pushstring(pState, str);
    oStr = lua_tostring(pState, -1);
    assert(0 == strcmp(str, oStr));
    lua_pop(pState, 1);
}


void demoPushAndClear(struct lua_State *pState) {
    assert(0 == lua_gettop(pState));

    for (int i=0; i < 10; ++i) {
        lua_pushinteger(pState, 0xBEEF);
    }
    assert(10 == lua_gettop(pState));

    lua_pop(pState, 1);
    assert(9 == lua_gettop(pState));

    // pop everything
    lua_pop(pState, -1);
    assert(0 == lua_gettop(pState));

    for (int i=0; i < 10; ++i) {
        lua_pushnumber(pState, 3.14);
    }
    assert(10 == lua_gettop(pState));

    // explicitly pop everything, specifying the length
    lua_pop(pState, 10);
    assert(0 == lua_gettop(pState));
}

// TODO: re-read C pointer Book about how c-string works!
// char oStrAll[] = {} will cause segfault, it has to have a length
// GCC message: stack smashing detected
void demoPushAndIterate(struct lua_State *pState) {
    int top;
    int valueType;
    size_t oStrLen;
    const char *oStr = NULL;
    char oStrAll[16] = {};
    lua_pushinteger(pState, 1);
    lua_pushnumber(pState, 3.0);
    lua_pushstring(pState, ".");
    lua_pushnumber(pState, 3.14);
    top = lua_gettop(pState);
    for (int idx = 1; idx <= top; ++idx) {
        valueType = lua_type(pState, idx);
        oStrLen = 0;
        switch (valueType) {
            case LUA_TNUMBER: {
                oStr = lua_tolstring(pState, idx, &oStrLen);
            }
            default:
                ;
        }
        if (oStrLen) {
            strcat(oStrAll, oStr);
        }
    }
    assert(0 == strcmp("13.03.14", oStrAll));
    lua_pop(pState, -1);
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    demoCheckStack(pState);
    demoPushAndQueryValueTypes(pState);
    demoPushAndQueryValues(pState);
    demoPushAndClear(pState);
    demoPushAndIterate(pState);

    lua_close(pState);
    return 0;
}
