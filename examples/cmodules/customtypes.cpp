//
// Created by wein on 12/22/17.
//

#include <climits>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

// bits per unsigned integer
#define BITS_PER_WORD (CHAR_BIT * sizeof(unsigned int))

// the following two macros are to map a relatively long int,
// an unsigned int, to a multi-segment bit field

// 00 00 00 01 / 32 = 0
// this idx belongs to #0 segment (called a WORD)
#define I_WORD(idx) ((unsigned int)(idx) / BITS_PER_WORD)

// 00 00 00 01 % 32 = 1
// this idx has position #1 in its segment (called a BIT)
// 00000000000000000000000000000001
#define I_BIT(idx) (1 << ((unsigned int)(idx) % BITS_PER_WORD))


extern "C" {


typedef struct BitArray {
    int size;
    unsigned int values[1];  // the segments (WORDs)
} BitArray;


size_t getSize(int numBits) {
    return sizeof(BitArray) + I_WORD(numBits - 1) * sizeof(unsigned int);
}


static int createBoolArray(lua_State *L) {
    int numBits{(int)luaL_checkinteger(L, 1)};
    luaL_argcheck(L, numBits > 1, 1, "invalid bit array size (must be greater than 1)");
    size_t numBytes = getSize(numBits);
    auto pBitArray = (BitArray *)lua_newuserdata(L, numBytes);
    pBitArray->size = numBits;
    for (int idx = 0, max_ = I_WORD(numBits - 1); idx <= max_; ++idx) {
        pBitArray->values[idx] = 0;
    }
    return 1;
}


static int set(lua_State *L) {
    auto pBitArray = (BitArray *)lua_touserdata(L, 1);
    luaL_argcheck(L, pBitArray != nullptr, 1, "expect BitArray");
    auto idx = (int)luaL_checkinteger(L, 2) - 1;  // array index starts from 0
    luaL_argcheck(L, 0 <= idx && idx < pBitArray->size, 2, "index out of range");
    return 0;
}


static const struct luaL_Reg module[] = {
    {"createBoolArray", createBoolArray},
    {"set", set},

    // not providing this "poisonous bill" will cause Lua
    // interpreter to segfault
    {nullptr, nullptr}
};


int luaopen_libcustomtypes(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}


}