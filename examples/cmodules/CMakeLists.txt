
add_library(oneshot SHARED
    oneshot.c)
target_link_libraries(oneshot
    PUBLIC
    luaBase)
install(TARGETS oneshot DESTINATION /tmp/luaExamples/cmodules)


add_executable(oneshot_i
    oneshot_interpreter.c)
target_link_libraries(oneshot_i
    PUBLIC
    luaStdLib)
