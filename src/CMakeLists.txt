
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

add_library(luaAuxLib STATIC
    include/luaAuxLib/lauxlib.h
    sources/luaAuxLib/lauxlib.c)
target_include_directories(luaAuxLib
    PUBLIC
    include/luaAuxLib)
target_link_libraries(luaAuxLib
    PUBLIC
    luaBase)

file(GLOB __LUACORE_HEADER_FILES include/luaCore/*.h)
file(GLOB __LUACORE_SOURCE_FILES sources/luaCore/*.c)
add_library(luaCore STATIC
    ${__LUACORE_HEADER_FILES}
    ${__LUACORE_SOURCE_FILES})
target_include_directories(luaCore
    PUBLIC
    include/luaCore)
target_link_libraries(luaCore
    PUBLIC
    luaBase
    luaAuxLib)

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
target_link_libraries(luaStdLib
    PUBLIC
    luaAuxLib)

add_executable(lua
    sources/apps/lua.c)
target_link_libraries(lua
    PUBLIC
    luaCore
    luaStdLib
    m)
