cmake_minimum_required(VERSION 3.0)
project(lua C)

enable_testing()

add_subdirectory(src)

add_subdirectory(tests/utilities)
add_subdirectory(tests/luaBase)
