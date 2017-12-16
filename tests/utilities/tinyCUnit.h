//
// Created by wein on 12/15/17.
//

#ifndef TINYCUNIT_H
#define TINYCUNIT_H

#include <assert.h>
#include <stdio.h>

#ifndef MAXTESTNUM
#define MAXTESTNUM 255
#endif


struct TinyTest_T {
    const char *name;
    void (*pFunc)();
};


static struct TinyTest_T *INVALID = 0;
static struct TinyTest_T tinyTests[MAXTESTNUM];


struct TinyTest_T *nextTinyCase() {
    struct TinyTest_T *pTT = tinyTests;
    for (int i = 0; i < MAXTESTNUM; ++i, ++pTT) {
        if (!pTT->pFunc) {
            return pTT;
        }
    }
    return INVALID;
}


void addTinyTest(const char *name, void (*pFunc)()) {
    struct TinyTest_T *pTT = nextTinyCase();
    if (pTT) {
        pTT->name = name;
        pTT->pFunc = pFunc;
    }
}


int RUN_ALL_TESTS() {
    struct TinyTest_T *pTT = tinyTests;
    int i = 0;
    for (; i < MAXTESTNUM; ++i, ++pTT) {
        if (!pTT->pFunc) {
            break;
        }
        printf("---- test case: %s ----\n", pTT->name);
        pTT->pFunc();
    }
    printf("Run %d tests\n", i);
    return 0;
}


#define AddTinyTest(x) addTinyTest(#x, &x)

#define TINYTEST void

#define ASSERT_EQ(x, y) assert(x == y)
#define ASSERT_NE(x, y) assert(x != y)
#define ASSERT_TRUE(x) assert(x)
#define ASSERT_FALSE(x) assert(!x)


#endif //TINYCUNIT_H
