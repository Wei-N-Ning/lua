
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

