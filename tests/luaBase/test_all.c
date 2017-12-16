//
// Created by wein on 12/16/17.
//

#include <lua.h>

#include <tinyCUnit.h>


TINYTEST ExpectLuaGlobalMacros() {
    ASSERT_EQ(0, LUA_OK);
}


int main(int argc, char **argv) {
    AddTinyTest(ExpectLuaGlobalMacros);
    return RUN_ALL_TESTS();
}