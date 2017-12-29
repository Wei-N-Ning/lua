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

/*
 * Lua provides a basic type specifically for this task, called userdata.
 * A userdata offers a raw memory area, with no predefined operations
 * in Lua, which we can use to store anything.
 */
typedef struct BitArray {
    int size;
    unsigned int values[1];  // the segments (WORDs)
} BitArray;


using BitArrayPtr = BitArray *;

namespace {

/*
 * @return number of bytes required to store the given number
 * of Boolean values
 */
size_t getSize(int numBits) {
    return sizeof(BitArray) + I_WORD(numBits - 1) * sizeof(unsigned int);
}


#define getBitArraySafe(L) \
    (BitArrayPtr)luaL_checkudata(L, 1, "luaExamples.BitArray")


/*
 * Validate and retrieve the 1st and 2nd arguments that are passed to
 * BitArray's setter getter functions, which are:
 * - a pointer to a BitArray struct (userdata)
 * - an index
 *
 * @param L: lua state
 * @param o_pBitArray: an output parameter, to hold the pointer to the user
 * data
 * @param o_idx: an output parameter, to hold the value of the index, note
 * that C array index starts from 0 hence the first bit in the BitArray is
 * member [0] in the C array
 */
void retrieveArguments(lua_State *L, BitArrayPtr &o_pBitArray, int &o_idx) {
    auto pBitArray = getBitArraySafe(L);
    luaL_argcheck(L, pBitArray != nullptr, 1, "expect BitArray");
    auto idx = (int) luaL_checkinteger(L, 2) - 1;
    luaL_argcheck(L, 0 <= idx && idx < pBitArray->size, 2, "index out of range");
    o_pBitArray = pBitArray;
    o_idx = idx;
}


/*
 * iterate over all the segments in bytes; set each byte to 0
 */
void resetBoolArray(BitArrayPtr pBitArray) {
    if (pBitArray->size > 0) {
        for (int begin = 0, end = I_WORD(pBitArray->size - 1);
             begin <= end;
             ++begin) {
            pBitArray->values[begin] = 0;
        }
    }
}


/*
 * The usual method to distinguish one type of userdata from another is
 * to create a unique metatable for that type.
 * Every time we create a userdata, we mark it with the corresponding
 * metatable; every time we get a userdata, we check whether it has the
 * right metatable. Because Lua code cannot change the metatable of a
 * userdata, it cannot deceive these checks.
 */
int create(lua_State *L) {
    int numBits{(int) luaL_checkinteger(L, 1)};
    luaL_argcheck(L, numBits > 1, 1, "invalid bit array size (must be greater than 1)");
    size_t numBytes = getSize(numBits);
    auto pBitArray = (BitArrayPtr) lua_newuserdata(L, numBytes);
    pBitArray->size = numBits;
    resetBoolArray(pBitArray);
    luaL_getmetatable(L, "luaExamples.BitArray");

    // state of the stack:
    // -1 metatable
    // -2 userdata

    // pops a table from the stack and sets it as the metatable
    // of the object at the given index
    lua_setmetatable(L, -2);
    return 1;
}


int size(lua_State *L) {
    auto pBitArray = getBitArraySafe(L);
    luaL_argcheck(L, pBitArray != nullptr, 1, "expect BitArray");
    lua_pushinteger(L, pBitArray->size);
    return 1;
}


int reset(lua_State *L) {
    auto pBitArray = getBitArraySafe(L);
    luaL_argcheck(L, pBitArray != nullptr, 1, "expect BitArray");
    resetBoolArray(pBitArray);
    return 0;
}


int set(lua_State *L) {
    int idx;
    BitArrayPtr pBitArray{nullptr};
    retrieveArguments(L, pBitArray, idx);

    // any lua value that can be casted to boolean
    luaL_checkany(L, 3);
    if (lua_toboolean(L, 3)) {
        //                 segment     offset(mask)
        // e.g. 0001000
        pBitArray->values[I_WORD(idx)] |= I_BIT(idx);
    } else {
        // e.g. 1110111, bitwise negate
        pBitArray->values[I_WORD(idx)] &= ~I_BIT(idx);
    }
    return 0;
}


int get(lua_State *L) {
    int idx;
    BitArrayPtr pBitArray{nullptr};
    retrieveArguments(L, pBitArray, idx);
    // segment * offset(mask)
    // e.g. segment: 00 00 01 00 [01 00 00 00] 00 01 00 01
    //       offset:              01 00 00 00
    //       result: not 0

    // NOTE: do not cast the result value to C++'s bool!
    // recall that Lua API uses integer to represent boolean type
    // void lua_pushboolean (lua_State *L, int b)
    auto result = pBitArray->values[I_WORD(idx)] & I_BIT(idx);
    lua_pushboolean(L, result);
    return 1;
}

}


static const struct luaL_Reg module[] = {
    {"create", create},
    {"size", size},
    {"set", set},
    {"get", get},
    {"reset", reset},

    // not providing this "poisonous bill" will cause Lua
    // interpreter to segfault
    {nullptr, nullptr}
};


int luaopen_libcustomtypes(lua_State *L) {
    luaL_newmetatable(L, "luaExamples.BitArray");
    luaL_newlib(L, module);
    return 1;
}


}