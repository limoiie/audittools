add_executable(test_common_cases test-hello.cpp)
target_link_libraries(test_common_cases core gtest_main)

add_test(NAME unit_test_common COMMAND test_common_cases)