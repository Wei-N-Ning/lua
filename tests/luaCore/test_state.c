//
// Created by wein on 12/17/17.
//
// NOTE: state creation is wrapped by luaAuxLib for convenience
//

#include <lstate.h>
#include <lauxlib.h>

#include <tinyCUnit.h>


TINYTEST CreateState_Expect_() {
    struct lua_State *pState = luaL_newstate();
}


int main(int argc, char **argv) {
    AddTinyTest(CreateState_Expect_);
    return RUN_ALL_TESTS();
}