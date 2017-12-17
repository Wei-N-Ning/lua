
add_executable(interpreter interpreter.c)
target_link_libraries(interpreter
    PUBLIC
    luaStdLib)


add_executable(printline printline.c)
target_link_libraries(printline
    PUBLIC
    luaStdLib)
