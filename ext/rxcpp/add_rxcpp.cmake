# COMMENTED BY LIMO: to bulid google-test on windows with cygwin need
# -std=gnu++11 instead of -std=c++11. so I changed the source code in
# cmake-build-debug/googletest-src/CMakeLists.txt to build google-test
# with -std=gnu++11 instead of -std=c++11. and since I have change the
# google-test source code, I comment the following codes to avoid git
# sychronizing with the remote.
#
# NOTE: if you want to download or update google-test source code, you
# need to uncommend the following code and the code in
# cmake-build-debug/googletest-src/CMakeLists.txt
#
# Download and unpack rxcpp at configure time

configure_file(${AUDITTOOLS_DIR}/ext/rxcpp/RxCpp.txt.in 
        ${BINARY_EXT_DIR}/rxcpp-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${BINARY_EXT_DIR}/rxcpp-download )
if(result)
    message(FATAL_ERROR "CMake step for rxcpp failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${BINARY_EXT_DIR}/rxcpp-download )
if(result)
    message(FATAL_ERROR "Build step for rxcpp failed: ${result}")
endif()


# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${BINARY_EXT_DIR}/rxcpp-src
        ${BINARY_EXT_DIR}/rxcpp-build
        EXCLUDE_FROM_ALL
        )

# TODO: need include header directory?

include(${BINARY_EXT_DIR}/rxcpp-src/projects/CMake/shared.cmake)

# config target compile options and feature according to platform
function(config_target_for_rxcpp, TARGET_NAME)
        target_compile_options(${TARGET_NAME} PUBLIC ${RX_COMPILE_OPTIONS})
        target_compile_features(${TARGET_NAME} PUBLIC ${RX_COMPILE_FEATURES})
        target_include_directories(${TARGET_NAME}
                PUBLIC ${RX_SRC_DIR} ${RX_CATCH_DIR}
                )
        target_link_libraries(${TARGET_NAME} ${CMAKE_THREAD_LIBS_INIT})        
endfunction()