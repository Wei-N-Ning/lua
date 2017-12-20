
add_executable(interpreter interpreter.c)
target_link_libraries(interpreter
    PUBLIC
    luaStdLib)


add_executable(printline printline.c)
target_link_libraries(printline
    PUBLIC
    luaStdLib)


add_executable(pushvalue pushvalue.c)
target_link_libraries(pushvalue
    PUBLIC
    luaStdLib)



add_executable(stackop stackop.c)
target_link_libraries(stackop
    PUBLIC
    luaStdLib)


add_executable(errorhandling errorhandling.c)
target_link_libraries(errorhandling
    PUBLIC
    luaStdLib)


add_executable(luaconfigurator
    luaconfigurator.h
    luaconfigurator.cpp)
set_target_properties(luaconfigurator
    PROPERTIES
    CXX_STANDARD 11)
target_link_libraries(luaconfigurator
    PUBLIC
    luaStdLib)


add_executable(tableop
    tableop.cpp
    tableop.h)
set_target_properties(tableop
    PROPERTIES
    CXX_STANDARD 11)
target_link_libraries(tableop
    PUBLIC
    luaStdLib)


add_executable(callluafuncs
    callluafuncs.cpp
    callluafuncs.h)
set_target_properties(callluafuncs
    PROPERTIES
    CXX_STANDARD 11)
target_link_libraries(callluafuncs
    PUBLIC
    luaStdLib)


add_executable(variadicfuncs
    variadicfuncs.cpp
    variadicfuncs.h)
set_target_properties(variadicfuncs
    PROPERTIES
    CXX_STANDARD 11)
target_link_libraries(variadicfuncs
    PUBLIC
    luaStdLib)


add_executable(variadicfuncscxx
    variadicfuncscxx.cpp
    variadicfuncscxx.h)
set_target_properties(variadicfuncscxx
    PROPERTIES
    CXX_STANDARD 11)
target_link_libraries(variadicfuncscxx
    PUBLIC
    luaStdLib)
