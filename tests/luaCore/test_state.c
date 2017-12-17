//
// Created by wein on 12/17/17.
//
// NOTE: state creation is wrapped by luaAuxLib for convenience
//

#include <lstate.h>
#include <lauxlib.h>

#include <tinyCUnit.h>


TINYTEST NewState_ExpectNotNull() {
    struct lua_State *pState = luaL_newstate();
    ASSERT_TRUE(pState);
    lua_close(pState);
}


int main(int argc, char **argv) {
    AddTinyTest(NewState_ExpectNotNull);
    return RUN_ALL_TESTS();
}