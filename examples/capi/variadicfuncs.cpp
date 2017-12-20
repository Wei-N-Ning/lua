//
// Created by wein on 12/20/17.
//

#include "variadicfuncs.h"

#include <cstring>
#include <cassert>
#include <cstdarg>
#include <iostream>


bool loadSourceCode(struct lua_State *pState, const std::string &sourceCode) {
    if (luaL_loadstring(pState, sourceCode.c_str()) || lua_pcall(pState, 0, 0, 0)) {
        std::cout << "can not load source code: " << lua_tostring(pState, -1) << std::endl;
        return false;
    }
    return true;
}


// follow Lua Book example on P257, implemented mainly in C
// see variadicfuncscxx.cpp for C++ implementation using better
// encapsulation
bool call(struct lua_State *L, const char *func, const char *sig, ...) {
    va_list vl;
    char symbol;
    int isnum;
    int tempI;
    double tempD;
    size_t sigLength = strlen(sig);
    size_t narg = 0;
    int nres = 0;
    int toBreak = 0;

    va_start(vl, sig);
    lua_getglobal(L, func);

    // process arguments
    while ((symbol = *sig) != '\0') {
        if (toBreak) {
            break;
        }
        ++sig;
        switch (symbol) {
            case '>': {
                toBreak = 1;
                break;
            }
            case 'i': {
                lua_pushinteger(L, va_arg(vl, int));
                ++narg;
                break;
            }
            case 'f':
            case 'd':
                lua_pushnumber(L, va_arg(vl, double));
                ++narg;
                break;
            default: {
                ;
            }
        }
    }

    nres = sigLength - narg - 1;
    if (lua_pcall(L, narg, nres, 0) != 0) {
        std::cout << "an error happens in " << func
                  << ". Reason: " << lua_tostring(L, -1)
                  << std::endl;
        return false;
    }
    nres = -nres;

    // process return values
    while ((symbol = *sig) != '\0') {
        ++sig;
        switch (symbol) {
            case 'i': {
                tempI = (int)lua_tointegerx(L, nres, &isnum);
                if (!isnum) {
                    return false;
                }
                *va_arg(vl, int *) = tempI;
                break;
            }
            case 'f':
            case 'd': {
                tempD = (double)lua_tonumberx(L, nres, &isnum);
                if (!isnum) {
                    return false;
                }
                *va_arg(vl, double *) = tempD;
                break;
            }
            default: {
                ;
            }
        }
        ++nres;
    }

    va_end(vl);
    return true;
}


void initialize(struct lua_State *L) {
    std::string sourceCode{
        "function f0_0()\n"
        "   print(\"called f0_0\")\n"
        "end\n"
        "function f1_0(arg)\n"
        "   print(\"called f1_0\", arg)\n"
        "   assert(arg)\n"
        "end\n"
        "function f1_1(arg)\n"
        "   assert(arg > 0)\n"
        "   ret = 10.0 / arg\n"
        "   print(\"called f1_1\", arg, ret)\n"
        "   return ret\n"
        "end\n"
        "function f3_1(x, y, z)\n"
        "   ret = (x + y + z) / 3.0\n"
        "   print (\"called f3_1\", x, y, z, ret)\n"
        "   return ret\n"
        "end\n"
    };
    assert(loadSourceCode(L, sourceCode));
}


int main(int argc, char **argv) {
    struct lua_State *pState = luaL_newstate();
    double fresult;
    luaL_openlibs(pState);

    initialize(pState);

    assert(!call(pState, "nonexisting", ""));

    assert(call(pState, "f0_0", ""));

    assert(call(pState, "f1_0", "d", 1.0));

    assert(call(pState, "f1_1", "f>d", 2.5f, &fresult));
    assert(4 == (int)fresult);

    assert(call(pState, "f3_1", "idf>d", 10, 2.5, 2.5f, &fresult));
    assert(5 == (int)fresult);

    lua_close(pState);
    return 0;
}

