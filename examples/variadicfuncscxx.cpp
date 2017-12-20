//
// Created by wein on 12/20/17.
//

#include "variadicfuncscxx.h"

#include <cassert>
#include <iostream>


bool loadSourceCode(struct lua_State *pState, const char *sourceCode) {
    if (luaL_loadstring(pState, sourceCode) || lua_pcall(pState, 0, 0, 0)) {
        std::cout << "can not load source code: " << lua_tostring(pState, -1) << std::endl;
        return false;
    }
    return true;
}


void showError(struct lua_State *L, const char *msg) {
    std::cout << msg << " " << lua_tostring(L, -1) << std::endl;
    lua_pop(L, -1); // pop error
}


void initialize(struct lua_State *L) {
    const char *sourceCode =\
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
            "end\n";
    assert(loadSourceCode(L, sourceCode));
}


class CallMaker {
public:
    explicit CallMaker(struct lua_State *L);
    template<typename ... Args> bool process(const char *func, Args ... args);
    bool process(const char *func);
private:

    // insert this object between function arguments and function return values
    class SEPARATOR {};

    template<typename T> bool processArg(const T &val);
    template<typename T> bool processRet(const T &ret);
    bool loadFunc(const char *func);
    void reset();

    struct lua_State *L = nullptr;
    int nargs = 0;
    int nrets = 0;
    bool doneProcessArgs = false;
};


CallMaker::CallMaker(struct lua_State *L)
: L(L) {
}


void CallMaker::reset() {
    nargs = 0;
    nrets = 0;
    doneProcessArgs = false;
}


template<typename ... Args> bool CallMaker::process(const char *func, Args... args) {
    reset();
    if (!loadFunc(func)) {
        return false;
    }
    auto _ = {processArg(args)...};
    auto ret = lua_pcall(L, nargs, nrets, 0) == LUA_OK;
    if (!ret) {
        showError(L, func);
    }
    return ret;
}


bool CallMaker::process(const char *func) {
    reset();
    if (!loadFunc(func)) {
        return false;
    }
    auto ret = lua_pcall(L, nargs, nrets, 0) == LUA_OK;
    if (!ret) {
        showError(L, func);
    }
    return ret;
}


template<typename T>
bool CallMaker::processArg(const T &val) {
    return false;
}


template<> bool CallMaker::processArg(const SEPARATOR &val) {
    doneProcessArgs = true;
    return false;
}


template<> bool CallMaker::processArg(const double &val) {
    lua_pushnumber(L, val);
    ++nargs;
    return false;
}


template<> bool CallMaker::processArg(const float &val) {
    lua_pushnumber(L, val);
    ++nargs;
    return false;
}


template<> bool CallMaker::processArg(const int &val) {
    lua_pushinteger(L, val);
    ++nargs;
    return false;
}


template<typename T>
bool CallMaker::processRet(const T &ret) {
    return false;
}


bool CallMaker::loadFunc(const char *func) {
    if (lua_getglobal(L, func)) {
        return true;
    }
    std::cout << "can not find function: " << func
              << std::endl;
    return false;
}


// parsing return values using variadic template is not as easy as using
// C's variadic function;
//
// the latter allows the implementer to process the arg-list in two passes:
// one pass for function arguments;
// one pass for function return values;
//
// however using the C++'s initializer_list pattern the implementer has to
// process ALL the arguments in one pass
void demoCallVariadicFunction(struct lua_State *L) {
    CallMaker cm{L};

    assert(!cm.process("some"));

    assert(cm.process("f0_0"));

    assert(cm.process("f1_0", 2.5));
}


int main(int argc, char **argv) {
    struct lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    initialize(L);
    demoCallVariadicFunction(L);

    lua_close(L);
    return 0;
}