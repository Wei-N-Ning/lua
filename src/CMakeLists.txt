
file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES sources/*.c)

add_executable(lua
    ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(lua
    PUBLIC
    .)
target_link_libraries(lua
    m
    )

# "Small Lua" mode

#add_definitions(-DLUA_32BITS)

# after adding this definition, 0xFFFFFFFF is interpreted as -1 by Lua interpreter
# in 64bit mode, any number larger or equal to 0xFFFFFFFF is properly recognized as an integer
# also I can verify this by this command:
# print(string.format("0x%X", math.maxinteger))
