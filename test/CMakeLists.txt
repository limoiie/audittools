add_executable(test_common_cases test-hello.cpp test-log.cpp test-str.cpp)
target_link_libraries(test_common_cases core gtest_main)

add_executable(test_ext test-rxcpp.cpp test-boost.cpp)
target_link_libraries(test_ext gtest_main Boost::boost 
        Boost::regex Boost::filesystem Boost::locale Boost::system
        Boost::context Boost::filesystem)
        

config_target_for_rxcpp(test_ext)

set_target_properties(
    test_common_cases test_ext
    PROPERTIES FOLDER test
)

add_test(NAME unit_test_common COMMAND test_common_cases)
add_test(NAME unit_test_ext COMMAND test_ext)