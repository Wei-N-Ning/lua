
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
target_include_directories(helloworld_c
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS helloworld_c
    DESTINATION
    /tmp/lua/cmodules)
