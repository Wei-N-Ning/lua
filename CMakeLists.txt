cmake_minimum_required(VERSION 3.0)
project(lua C)

file(GLOB HEADER_FILES ./*.h)
file(GLOB SOURCE_FILES ./*.c)

add_executable(lua
    ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(lua
    PUBLIC
    .)
target_link_libraries(lua
    m
    )

# after adding this macro, 0xFFFFFFFF is interpreted as -1 by Lua interpreter
# in 64bit mode, any number larger or equal to 0xFFFFFFFF is properly recognized as an integer
# also I can verify this by this command:
# print(string.format("0x%X", math.maxinteger))
#add_definitions(-DLUA_32BITS)
