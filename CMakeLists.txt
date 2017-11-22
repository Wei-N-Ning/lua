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
