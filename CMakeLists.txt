cmake_minimum_required(VERSION 3.0)
project(lua)

enable_testing()

add_subdirectory(src)

add_subdirectory(tests/utilities)
add_subdirectory(tests/luaBase)
add_subdirectory(tests/luaCore)

add_subdirectory(examples)