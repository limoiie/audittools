add_executable(test_common_cases test-hello.cpp test-log.cpp)
target_link_libraries(test_common_cases core gtest_main)

add_executable(test_rxcpp test-rxcpp.cpp)
target_link_libraries(test_rxcpp gtest_main)
config_target_for_rxcpp(test_rxcpp)

set_target_properties( 
    test_common_cases test_rxcpp
    PROPERTIES FOLDER test
)

add_test(NAME unit_test_common COMMAND test_common_cases)
add_test(NAME unit_test_ext COMMAND test_rxcpp)