//
// Created by wein on 12/18/17.
//

#include "tableop.h"

#include <cassert>
#include <iostream>
#include <string>


bool loadTable(struct lua_State *pState, const char *sourceCode, const char *tableName) {
    if (luaL_loadstring(pState, sourceCode) || lua_pcall(pState, 0, 0, 0)) {
        std::cout << "can not load string" << std::endl;
        return false;
    }
    lua_getglobal(pState, tableName);
    if (lua_istable(pState, -1)) {
        return true;
    }
    std::cout << "invalid table (lua_istable())" << std::endl;
    return false;
}



std::string getStringField(struct lua_State *pState, const char *name) {
    size_t len = 0;
    const char *field = nullptr;
    lua_pushstring(pState, name);
    lua_gettable(pState, -2);
    field = lua_tolstring(pState, -1, &len);
    lua_pop(pState, 1);
    if (len) {
        return field;
    }
    return "";
}


int getIntField(struct lua_State *pState, const char *name) {
    int isnum = 0;
    int result = 0;
    lua_pushstring(pState, name);
    lua_gettable(pState, -2);
    result = (int)lua_tointegerx(pState, -1, &isnum);
    lua_pop(pState, 1);
    if (isnum) {
        return result;
    }
    return 0;
}


// using the new convenient function added in Lua 5.3, lua_setfield()
double getDoubleField(struct lua_State *pState, const char *name) {
    if (lua_getfield(pState, -1, name) != LUA_TNUMBER) {
        return 0;
    }
    auto _ = (double)lua_tonumber(pState, -1);
    lua_pop(pState, 1);
    return _;
}


void demoGetStringValueFromTable(struct lua_State *pState) {
    assert(loadTable(pState, "conf = {name=\"ak47\", damage=33.3, clipSize=30}\n", "conf"));

    // the pattern shown here is that, the getters keep the lua table at index -2 while
    // pushing and popping the names of the field to and out of the stack; even if one
    // getter fail to get the expected value from the table, it should still pop the
    // field name to save space for the subsequent calls - it probably could be done in
    // a RAII fashion
    assert(std::string{"ak47"} == getStringField(pState, "name"));

    // lua_tolstring() has a protection mechanism (&len)
    assert(getStringField(pState, "_name").empty());

    // number (double) is casted to string via lua_tolstring() function
    assert(std::string{"33.3"} == getStringField(pState, "damage"));
    lua_pop(pState, -1);
}


void demoGetIntegerFromTable(struct lua_State *pState) {
    assert(loadTable(pState, "conf = {name=\"ak47\", damage=33.3, clipSize=30}\n", "conf"));
    assert(!getIntField(pState, "_name"));

    // the internal lua getter correctly identifies that, the value stored against [damage]
    // field is a float (number); however it also decides that, since the caller wants to
    // operate in integer mode, instead of rounding, it "rejects" the request
    // the way it does the mode detection is entertaining
    assert(0 == getIntField(pState, "damage"));
    assert(30 == getIntField(pState, "clipSize"));

    lua_pop(pState, -1);
}


void demoGetDoubleFromTable(struct lua_State *pState) {
    assert(loadTable(pState, "conf = {name=\"ak47\", damage=33.3, clipSize=30}\n", "conf"));
    assert(getDoubleField(pState, "damage") > 33.2);
    lua_pop(pState, -1);
}


void demoSetNamedIntegerInTable(struct lua_State *pState) {
    const char *sourceCode = "conf = {name=\"acr\"}";
    assert(loadTable(pState, sourceCode, "conf"));
    assert(!getIntField(pState, "clipSize"));

    // sets a key-value pair in the table (clipSize: 23)
    // note the order of the arguments

    // lua_pushstring(pState, "clipSize");
    // lua_pushinteger(pState, 23);
    // lua_settable(pState, -3);  // top

    // prefer new setfield() function
    lua_pushinteger(pState, 23);
    lua_setfield(pState, -2, "clipSize");
    assert(23 == getIntField(pState, "clipSize"));

    lua_pop(pState, -1);
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    demoGetStringValueFromTable(pState);
    demoGetIntegerFromTable(pState);
    demoGetDoubleFromTable(pState);
    demoSetNamedIntegerInTable(pState);

    lua_close(pState);
    return 0;
}
