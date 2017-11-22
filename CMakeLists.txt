cmake_minimum_required(VERSION 3.0)
project(lua C)

set(CMAKE_C_COMPILER "/usr/bin/clang-3.8")

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
