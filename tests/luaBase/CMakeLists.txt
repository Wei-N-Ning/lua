add_executable(test_all test_all.c)
target_link_libraries(test_all tinyCUnit luaBase)
add_test(NAME lua::base COMMAND test_all)
