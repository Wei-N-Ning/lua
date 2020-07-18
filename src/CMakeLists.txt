
# "Small Lua" mode

#add_definitions(-DLUA_32BITS)

# after adding this definition, 0xFFFFFFFF is interpreted as -1 by Lua interpreter
# in 64bit mode, any number larger or equal to 0xFFFFFFFF is properly recognized as an integer
# also I can verify this by this command:
# print(string.format("0x%X", math.maxinteger))


add_library(luaBase INTERFACE)
target_include_directories(luaBase
    INTERFACE
    include/luaBase)

file(GLOB __LUACORE_HEADER_FILES include/luaCore/*.h)
file(GLOB __LUACORE_SOURCE_FILES sources/luaCore/*.c)
add_library(luaCore STATIC
    ${__LUACORE_HEADER_FILES}
    ${__LUACORE_SOURCE_FILES})
set_target_properties(luaCore
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
target_include_directories(luaCore
    PUBLIC
    include/luaCore)
target_link_libraries(luaCore
    PUBLIC
    m
    luaBase
    ${CMAKE_DL_LIBS})
target_compile_definitions(luaCore PUBLIC
    -DLUA_USE_POSIX -DLUA_USE_DLOPEN
    )

add_library(luaStdLib STATIC
    sources/luaStdLib/lbaselib.c
    sources/luaStdLib/liolib.c
    sources/luaStdLib/lbitlib.c
    sources/luaStdLib/ldblib.c
    sources/luaStdLib/lcorolib.c
    sources/luaStdLib/lmathlib.c
    sources/luaStdLib/loadlib.c
    sources/luaStdLib/ltablib.c
    sources/luaStdLib/lutf8lib.c
    sources/luaStdLib/lstrlib.c
    sources/luaStdLib/loslib.c
    sources/luaStdLib/linit.c
    )
set_target_properties(luaStdLib
    PROPERTIES
    POSITION_INDEPENDENT_CODE ON)
target_link_libraries(luaStdLib
    PUBLIC
    luaCore
    ${CMAKE_DL_LIBS})
target_compile_definitions(luaStdLib PUBLIC
    -DLUA_USE_POSIX -DLUA_USE_DLOPEN
    )

add_executable(luawein
    sources/apps/lua.c)
target_link_libraries(luawein
    PUBLIC
    luaCore
    luaStdLib
    ${CMAKE_DL_LIBS})
target_compile_definitions(luawein PUBLIC
    -DLUA_USE_POSIX -DLUA_USE_DLOPEN
    )
