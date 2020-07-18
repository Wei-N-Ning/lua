
add_executable(oneshot_i
    oneshot_interpreter.c)
target_link_libraries(oneshot_i
    PUBLIC
    luaStdLib)

add_executable(boost_i
    boost_interpreter.cpp
    boost_interpreter.h)
target_include_directories(boost_i PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(boost_i
    PRIVATE
    luaStdLib
    ${Boost_LIBRARIES}
    )
set_property(TARGET boost_i
    PROPERTY CXX_STANDARD 11)
