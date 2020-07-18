cmake_minimum_required(VERSION 3.16)

project(LuaWein LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

set(Boost_NO_SYSTEM_PATHS TRUE)
set(Boost_USE_STATIC_LIBS TRUE)
set(BOOST_ROOT ${PROJECT_SOURCE_DIR}/vendor/boost-1.72.0)

find_package(Boost REQUIRED
    COMPONENTS system filesystem)

add_subdirectory(src)

add_subdirectory(tests/utilities)
add_subdirectory(tests/luaBase)
add_subdirectory(tests/luaCore)

add_subdirectory(examples)
