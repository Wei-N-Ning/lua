
#file(GLOB HEADER_FILES include/*.h)
#file(GLOB SOURCE_FILES sources/*.c)
#
#add_executable(lua
#    ${HEADER_FILES} ${SOURCE_FILES})
#target_include_directories(lua
#    PUBLIC
#    include)
#target_link_libraries(lua
#    m
#    )

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
    )
target_link_libraries(luaStdLib
    PUBLIC
    luaAuxLib)
