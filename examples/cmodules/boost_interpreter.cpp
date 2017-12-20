//
// Created by wein on 12/20/17.
//

#include "boost_interpreter.h"

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>


static int exists(struct lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    int ret{boost::filesystem::exists(path)};
    lua_pushinteger(L, ret);
    return 1;
}


static int isfile(struct lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    int ret{boost::filesystem::is_regular_file(path)};
    lua_pushinteger(L, ret);
    return 1;
}


static int listdir(struct lua_State *L) {
    const char *path = luaL_checkstring(L, 1);
    std::stringstream errorMessage{};

    if (!boost::filesystem::is_directory(path)) {

        // this is one naive way to handle the soft exception,
        // but I can do better than that, see the next block
        //
        // std::cerr << "Not a directory: " << path << std::endl;
        // return 0;

        // follow the Lua function return pattern;
        // honorable mentioning: Golang
        //
        // result, err = listdir("/abc")
        // print(err)
        // Not a directory: /abc
        // print(result)
        // nil

        errorMessage << "Not a directory: " << path;
        lua_pushnil(L);
        lua_pushstring(L, errorMessage.str().c_str());
        return 2;
    }

    boost::filesystem::directory_iterator di{path};
    boost::filesystem::directory_iterator end{};

    lua_newtable(L);
    for (int idx = 1; di != end; ++di, ++idx) {
        lua_pushinteger(L, idx);
        lua_pushstring(L, di->path().c_str());
        lua_settable(L, -3);  // will pop the above values
    }

    return 1;
}


int main(int argc, char **argv) {
    char buff[255];
    int error;
    struct lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    lua_pushcfunction(L, exists);
    lua_setglobal(L, "exists");
    lua_pushcfunction(L, isfile);
    lua_setglobal(L, "isfile");
    lua_pushcfunction(L, listdir);
    lua_setglobal(L, "listdir");
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadstring(L, buff) || lua_pcall(L, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
    lua_close(L);
    return 0;
}
