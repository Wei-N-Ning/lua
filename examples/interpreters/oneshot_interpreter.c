#include <math.h>
#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


double getNumberNaive(struct lua_State *L) {
    int isnum;
    double d = lua_tonumberx(L, 1, &isnum);
    if (!isnum) {
        return 0;
    }
    return d;
}


// The auxiliary library helps us with this task.
// The function luaL_checknumber checks whether a
// given argument is a number:
// in case of error, it throws an informative error message;
// otherwise, it returns the number.
double getNumber(struct lua_State *L) {
    return luaL_checknumber(L, 1);
}


static int l_sin(struct lua_State *L) {
    double d = getNumber(L);
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