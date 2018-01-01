
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


add_library(helloworld_cxx SHARED
    helloworld_cxx.cpp)
set_property(TARGET helloworld_cxx
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(helloworld_cxx
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS helloworld_cxx
    DESTINATION
    /tmp/lua/cmodules)


add_library(helloworld_boost SHARED
    helloworld_boost.cpp)
set_property(TARGET helloworld_boost
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(helloworld_boost
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
target_link_libraries(helloworld_boost
    PUBLIC
    boost_filesystem
    boost_system)
install(TARGETS helloworld_boost
    DESTINATION
    /tmp/lua/cmodules)


add_test(
    NAME luaExamples::CMODULES::helloworld
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/helloworld.lua
)


add_library(tablemanip SHARED
    tablemanip.cpp)
set_property(TARGET tablemanip
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(tablemanip
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS tablemanip
    DESTINATION
    /tmp/lua/cmodules)
add_test(
    NAME luaExamples::CMODULES::tablemanip
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/tablemanip.lua
)


add_library(statemanip SHARED
    statemanip.cpp)
set_property(TARGET statemanip
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(statemanip
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS statemanip
    DESTINATION
    /tmp/lua/cmodules)
add_test(
    NAME luaExamples::CMODULES::statemanip
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/statemanip.lua
)


add_library(customtypes SHARED
    customtypes.cpp)
set_property(TARGET customtypes
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(customtypes
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS customtypes
    DESTINATION
    /tmp/lua/cmodules)
add_test(
    NAME luaExamples::CMODULES::customtypes
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/customtypes.lua
)


add_library(simpleiter_c SHARED
    simpleiter_c.c)
target_include_directories(simpleiter_c
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS simpleiter_c
    DESTINATION
    /tmp/lua/cmodules)


add_library(simpleiter_cxx SHARED
    simpleiter_cxx.cpp)
set_property(TARGET simpleiter_cxx
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(simpleiter_cxx
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS simpleiter_cxx
    DESTINATION
    /tmp/lua/cmodules)


add_test(
    NAME luaExamples::CMODULES::simpleiter
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/simpleiter.lua
)


add_library(diriter_c SHARED
    diriter_c.c)
target_include_directories(diriter_c
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS diriter_c
    DESTINATION
    /tmp/lua/cmodules)


add_library(diriter_cxx SHARED
    diriter_cxx.cpp)
set_property(TARGET diriter_cxx
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(diriter_cxx
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS diriter_cxx
    DESTINATION
    /tmp/lua/cmodules)


add_test(
    NAME luaExamples::CMODULES::diriter
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/diriter.lua
)


add_library(tasks SHARED
    tasks.cpp)
set_property(TARGET tasks
    PROPERTY
    CXX_STANDARD 11)
target_include_directories(tasks
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
install(TARGETS tasks
    DESTINATION
    /tmp/lua/cmodules)


add_test(
    NAME luaExamples::CMODULES::tasks
    COMMAND lua5.3 ${CMAKE_SOURCE_DIR}/examples/cmodules/tasks.lua
)


add_library(lproc SHARED
    lproc.cpp)
set_target_properties(lproc
    PROPERTIES
    CXX_STANDARD 11
    POSITION_INDEPENDENT_CODE ON)
target_include_directories(lproc
    PUBLIC
    ${CMAKE_SOURCE_DIR}/src/include/luaBase
    ${CMAKE_SOURCE_DIR}/src/include/luaCore)
target_link_libraries(lproc
    PUBLIC
    pthread)
install(TARGETS lproc
    DESTINATION
    /tmp/lua/cmodules)

