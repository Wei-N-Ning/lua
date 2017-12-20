//
// Created by wein on 12/20/17.
//

#include "boost_interpreter.h"

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



int main(int argc, char **argv) {
    char buff[255];
    int error;
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);
    lua_pushcfunction(pState, exists);
    lua_setglobal(pState, "exists");
    lua_pushcfunction(pState, isfile);
    lua_setglobal(pState, "isfile");
    while (fgets(buff, sizeof(buff), stdin) != NULL) {
        error = luaL_loadstring(pState, buff) || lua_pcall(pState, 0, 0, 0);
        if (error) {
            fprintf(stderr, "%s\n", lua_tostring(pState, -1));
            lua_pop(pState, 1);
        }
    }
    lua_close(pState);
    return 0;
}
