//
// Created by wein on 12/17/17.
//
// Lua Book P238:
//
// The header file lua.h declares the basic functions provided by Lua.
// It includes functions
// to create a new Lua environment,
// to invoke Lua functions,
// to read and write global variables in the environment,
// to register new functions to be called by Lua, and so on.
// Everything declared in lua.h has a lua_ prefix (e.g., lua_pcall).
//
// The header file lauxlib.h declares the functions provided by the
// auxiliary library (auxlib).
// All its declarations start with luaL_ (e.g., luaL_loadstring).
// The auxiliary library uses the basic API provided by lua.h to provide
// a higher abstraction level, in particular with abstractions used
// by the standard libraries.
//
// The header file lualib.h declares functions to open the libraries.
// The function luaL_openlibs opens all standard libraries.


#include <stdio.h>
#include <string.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>


int main(int argc, char **argv) {

    // the size of the buffer determines how many "lines" the interpreter will get
    // from stdin; if this value is small (such as 8), this statement:
    // print("there is a cow 1337")
    // is broken into multiple lines, each of which contains invalid syntax.
    char buff[255];
    int error;
    struct lua_State *pState = luaL_newstate();

    // without Lua Standard Libraries, the interpreter can NOT understand nothing.
    luaL_openlibs(pState);

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