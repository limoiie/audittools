# test core
add_executable(test_core_cases test-log.cpp test-str.cpp
		test-serialization.cpp test-common.cpp)
target_link_libraries(test_core_cases core gtest_main
		Boost::boost Boost::filesystem Boost::random)

# test extension
add_executable(test_ext test-rxcpp.cpp test-boost.cpp)
target_link_libraries(test_ext gtest_main Boost::boost 
        Boost::regex Boost::filesystem Boost::locale Boost::system
        Boost::context)
config_target_for_rxcpp(test_ext)

# test apps/gui
set(GUI_FOLDER ${AUDITTOOLS_DIR}/src/apps/gui)
set(GUI_ABS_SRC_FILES)
get_property(_GUI_SRC_FILES GLOBAL PROPERTY "GLOBAL_GUI_SRC_FILES")
foreach(SRC_FILE ${_GUI_SRC_FILES})
	list(APPEND GUI_ABS_SRC_FILES ${GUI_FOLDER}/${SRC_FILE})
endforeach()

include_directories(${GUI_FOLDER})
add_executable(test_gui ${GUI_ABS_SRC_FILES} gui/test-config.cpp)
target_link_libraries(test_gui core gtest_main
		Boost::boost Boost::filesystem)
config_target_for_rxcpp(test_gui)

# misc
set_target_properties(
    test_core_cases test_ext test_gui
    PROPERTIES FOLDER test
)

add_test(NAME unit_test_common COMMAND test_core_cases)
add_test(NAME unit_test_ext COMMAND test_ext)