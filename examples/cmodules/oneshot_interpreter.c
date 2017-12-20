#include <math.h>
#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


static int l_sin(struct lua_State *L) {
    int isnum;
    double d = lua_tonumberx(L, 1, &isnum);
    if (!isnum) {
        return 0;
    }
    lua_pushnumber(L, sin(d));
    return 1;
}


int main(int argc, char **argv) {
    char buff[255];
    int error;
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);
    lua_pushcfunction(pState, l_sin);
    lua_setglobal(pState, "oneshot");
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