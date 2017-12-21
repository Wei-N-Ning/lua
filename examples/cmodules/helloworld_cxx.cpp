//
// Created by wein on 12/21/17.
//


#include <map>
#include <string>
#include <sstream>
#include <vector>


namespace {

using AttrNamesV = std::vector<std::string>;
using CreToAttrNamesM = std::map<std::string,AttrNamesV>;

AttrNamesV attrNamesByCreaure(const std::string &cre) {
    CreToAttrNamesM m{};
    m["elf"] =   {"hp", "mp", "damage"};
    m["dwarf"] = {"hp",       "damage", "skill"};
    m["orc"] =   {"hp",       "damage"};
    return m[cre];
}

}


extern "C" {

#include <lua.h>
#include <lauxlib.h>

// require creature type
static int newCreature(struct lua_State *L) {
    const char *cre = luaL_checkstring(L, 1);
    std::stringstream ss;
    auto attrNames = attrNamesByCreaure(cre);
    if (attrNames.empty()) {
        lua_pushnil(L);
        ss << "Creature: " << cre << " has no attribute.";
        lua_pushstring(L, ss.str().c_str());
        return 2;
    }
    lua_newtable(L);
    int idx = 1;
    for (const auto &an : attrNames) {
        lua_pushinteger(L, idx);
        lua_pushstring(L, an.c_str());
        lua_settable(L, -3);
        ++idx;
    }
    return 1;
}

static const struct luaL_Reg module[] = {
    {"newCreature", newCreature},
    {nullptr, nullptr}
};

int luaopen_libhelloworld_cxx(struct lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}

}