//
// Created by wein on 12/16/17.
//

#include <stdlib.h>

#include <lzio.h>

#include <tinyCUnit.h>


TINYTEST FillBuffer_NullBuffer_ExpectEOZ() {

    // DONT DO THAT
    // see examples/...
    // I can not skip the omnipresent lua stack and lua state

    // struct Zio z;
    // ASSERT_EQ(EOZ, luaZ_fill(&z));
}


int main(int argc, char **argv) {
    AddTinyTest(FillBuffer_NullBuffer_ExpectEOZ);
    return RUN_ALL_TESTS();
}
