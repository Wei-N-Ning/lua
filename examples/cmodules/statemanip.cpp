//
// Created by wein on 12/21/17.
//

/*
 * Frequently, C functions need to keep some non-local data,
 * that is, data that outlive their invocation.
 *
 * In C, we typically use global (extern) or static variables
 * for this need.
 */


extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}


extern "C" int luaopen_libstatemanip(lua_State *L) {
    return 0;
}
