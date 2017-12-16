
add_executable(test_lzio test_lzio.c)
target_link_libraries(test_lzio luaCore tinyCUnit)
add_test(NAME lua::core::lzio COMMAND test_lzio)

add_executable(test_state test_state.c)
target_link_libraries(test_state luaCore tinyCUnit)
add_test(NAME lua::core::state COMMAND test_state)


