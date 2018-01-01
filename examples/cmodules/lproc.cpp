//
// Created by wein on 1/1/18.
//
// Implement "Lua Process" example from Lua Book P290
//

#include <cstring>
#include <pthread.h>

extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

extern "C" int luaopen_liblproc(lua_State *L);

namespace {

typedef struct Proc {
    lua_State *L;
    pthread_t thread;
    pthread_cond_t cond;
    const char *channel;
    struct Proc *previous;
    struct Proc *next;
} Proc;

Proc *waitsend = nullptr;
Proc *waitreceive = nullptr;
pthread_mutex_t kernel_access = PTHREAD_MUTEX_INITIALIZER;
void *ll_thread (void *arg);

Proc *getself(lua_State *L) {
    lua_getfield(L, LUA_REGISTRYINDEX, "_SELF");
    auto p = (Proc *)lua_touserdata(L, -1);
    lua_pop(L, 1);
    return p;
}

void movevalues(lua_State *send, lua_State *rec) {
    int n = lua_gettop(send);
    luaL_checkstack(rec, n, "too many results");
    for (int i = 2; i <= n; ++n) {
        lua_pushstring(rec, lua_tostring(send, i));
    }
}

Proc *searchmatch(const char *channel, Proc **list) {
    for (auto node = *list; bool(node); node = node->next) {
        if (strcmp(channel, node->channel) != 0) {
            continue;
        }
        // remove node from list
        if (*list == node) {
            *list = (node->next == node) ? nullptr : node->next;
        }
        node->previous->next = node->next;
        node->next->previous = node->previous;
        return node;
    }
    return nullptr;
}

void waitonlist(lua_State *L, const char *channel, Proc **list) {
    Proc *p = getself(L);
    if (*list) {
        p->previous = (*list)->previous;
        p->previous->next = p;
        p->next = *list;
        p->next->previous = p;
    } else {
        *list = p;
        p->next = p;
        p->previous = p;
    }
    p->channel =  channel;
    do {
        pthread_cond_wait(&p->cond, &kernel_access);
    } while (p->channel);
}

void *ll_thread (void *arg) {
    auto L = (lua_State *)arg;
    luaL_openlibs(L);
    luaL_requiref(L, "liblproc", luaopen_liblproc, 1);
    lua_pop(L, 1);
    auto self = (Proc *)lua_newuserdata(L, sizeof(Proc));
    lua_setfield(L, LUA_REGISTRYINDEX, "_SELF");
    self->L = L;
    self->thread = pthread_self();
    self->channel = nullptr;
    pthread_cond_init(&self->cond, nullptr);
    if (lua_pcall(L, 0, 0, 0) != 0) {
        fprintf(stderr, "thread error: %s", lua_tostring(L, -1));
    }
    pthread_cond_destroy(&getself(L)->cond);
    lua_close(L);
    return nullptr;
}

int start(lua_State *L) {
    const char *chunk = luaL_checkstring(L, 1);
    pthread_t thread;
    lua_State *L1 = luaL_newstate();
    if (!L1) {
        luaL_error(L, "unable to create new state");
    }
    if (luaL_loadstring(L1, chunk) != 0) {
        luaL_error(L, "error in thread body: %s", lua_tostring(L1, -1));
    }
    if (pthread_create(&thread, nullptr, ll_thread, L1) != 0) {
        luaL_error(L, "unable to create new pthread");
    }
    pthread_detach(thread);
    return 0;
}

int send(lua_State *L) {
    const char *channel = luaL_checkstring(L, 1);
    pthread_mutex_lock(&kernel_access);
    auto p = searchmatch(channel, &waitreceive);
    if (p) {
        movevalues(L, p->L);
        p->channel = nullptr;
        pthread_cond_signal(&p->cond);
    } else {
        waitonlist(L, channel, &waitsend);
    }
    pthread_mutex_unlock(&kernel_access);
    return 0;
}

int receive(lua_State *L) {
    const char *channel = luaL_checkstring(L, 1);
    lua_settop(L, 1);
    pthread_mutex_lock(&kernel_access);
    auto p = searchmatch(channel, &waitsend);
    if (p) {
        movevalues(p->L, L);
        p->channel = nullptr;
        pthread_cond_signal(&p->cond);
    } else {
        waitonlist(L, channel, &waitreceive);
    }
    pthread_mutex_unlock(&kernel_access);
    return lua_gettop(L) - 1;
}

int exit(lua_State *L) {
    pthread_exit(nullptr);
    return 0;
}

const struct luaL_Reg module[] = {
    {"start", start},
    {"send", send},
    {"receive", receive},
    {"exit", exit},
    {nullptr, nullptr}
};

}  // end of anonymous namespace

extern "C" int luaopen_liblproc(lua_State *L) {
    luaL_newlib(L, module);
    return 1;
}

