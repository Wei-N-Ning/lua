//
// Created by wein on 12/31/17.
//


#include <dirent.h>
#include <cerrno>
#include <cstdio>
#include <cstring>
#include <memory>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

namespace {

class Dir {
public:
    /*
     * wrapping C open() function
     */
    bool open(const char *path);
    void close();
    bool isValid();

    /*
     * This method manipulates Lua state, pushing the file name to
     * its stack;
     *
     * @return bool: return false if there is no file name to fetch,
     * this is to tell the caller that no string has been pushed to
     * the stack
     */
    bool getNextFname(lua_State *L);

private:
    DIR *dir = nullptr;
};

bool Dir::open(const char *path) {
    dir = opendir(path);
    return bool(dir);
}

bool Dir::isValid() {
    return dir != nullptr;
}

bool Dir::getNextFname(lua_State *L) {
    if (isValid()) {
        struct dirent *entry = readdir(dir);
        if (entry) {
            lua_pushstring(L, entry->d_name);
            return true;
        }
    }
    return false;
}

void Dir::close() {
    if (dir) {
        printf("calling Dir::close()\n");
        closedir(dir);
    }
}

int iterator(lua_State *L) {
    auto pDir = (Dir *)lua_touserdata(L, lua_upvalueindex(1));
    return pDir->getNextFname(L) ? 1 : 0;
}

int open(lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    auto pDir = (Dir *)lua_newuserdata(L, sizeof(Dir));
    if (!pDir->open(path)) {
        luaL_error(
            L,
            "Can not open %s: %s", path, strerror(errno));
    }
    lua_pushcclosure(L, iterator, 1);
    return 1;
}

const struct luaL_Reg module[]{
    {"open", open},

    {nullptr, nullptr}
};

}

extern "C" int luaopen_libdiriter_cxx(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}
