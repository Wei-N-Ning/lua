//
// Created by wein on 12/18/17.
//

#include <assert.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>


int pushIntegers(struct lua_State *pState, const int *data, int num) {
    int idx = 0;
    for (; idx < num; ++idx) {
        lua_pushinteger(pState, data[idx]);
    }
    return idx;
}


// if num is larger than the size of the stack, it will respect
// the stack size
// return the actual integers fetched (which can be different from num,
// due to the above constraint)
// remember the first stack element has the index of 1 as
// contrary to array
int fetchIntegers(struct lua_State *pState, int *oData, int num) {
    int idx = 0;
    int top = lua_gettop(pState);
    int total = top < num ? top : num;
    for (; idx < total; ++idx) {
        oData[idx] = (int)lua_tointeger(pState, idx + 1);
    }
    return idx;
}


int compareIntArrays(const int *lhs, const int *rhs, size_t num) {
    for (int idx = 0; idx < num; ++idx) {
        if (lhs[idx] != rhs[idx]) {
            return 0;
        }
    }
    return 1;
}


void prtIntArray(const int *data, size_t num) {
    for (size_t idx = 0; idx < num; ++idx) {
        printf("%d", data[idx]);
    }
    printf("\n");
}


void demoPushAndFetch(struct lua_State *pState) {
    int data[8] = {3, 1, 4, 1, 5, 9, 2, 6};
    int oData[8] = {};
    pushIntegers(pState, data, 8);

    // top is 6; index is #8
    assert(6 == lua_tointeger(pState, 8));
    assert(6 == lua_tointeger(pState, -1));

    // bottom is 3, index is #1
    assert(3 == lua_tointeger(pState, 1));

    assert(8 == fetchIntegers(pState, oData, 8));
    if (!compareIntArrays(data, oData, 8)) {
        prtIntArray(data, 8);
        prtIntArray(oData, 8);
    };
    lua_pop(pState, -1);
}


// TODO: read its implementation
// these two statements cancel the effect of each other
// lua_rotate(pState, 5, -4);
// lua_rotate(pState, 5, 4);
void demoStackRotate(struct lua_State *pState) {
    int data[8] = {3, 1, 4, 1, 5, 9, 2, 6};
    int oData[8] = {};
    pushIntegers(pState, data, 8);

    lua_pop(pState, -1);
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    luaL_openlibs(pState);

    demoPushAndFetch(pState);
    demoStackRotate(pState);

    lua_close(pState);
    return 0;
}