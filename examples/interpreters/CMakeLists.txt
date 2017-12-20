
add_executable(oneshot_i
    oneshot_interpreter.c)
target_link_libraries(oneshot_i
    PUBLIC
    luaStdLib)

include(boost.cmake)

add_executable(boost_i
    boost_interpreter.cpp
    boost_interpreter.h)
target_link_libraries(boost_i
    PUBLIC
    luaStdLib
    boost_filesystem
    boost_system
    )
set_property(TARGET boost_i
    PROPERTY CXX_STANDARD 11)
