
add_library(helloworld_f SHARED
    helloworld_f.c)
target_link_libraries(helloworld_f
    PUBLIC
    luaBase)
install(TARGETS helloworld_f
    DESTINATION
    /tmp/lua/cmodules)


add_library(helloworld_c SHARED
    helloworld_c.c)
target_link_libraries(helloworld_c
    PUBLIC
    luaBase)
install(TARGETS helloworld_c
    DESTINATION
    /tmp/lua/cmodules)
