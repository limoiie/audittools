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
# Download and unpack googletest at configure time

# decrepted, replaced by git submodule
#configure_file(${AUDITTOOLS_DIR}/ext/google-test/GoogleTest.txt.in 
#        ${BINARY_EXT_DIR}/googletest-download/CMakeLists.txt)

#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#        RESULT_VARIABLE result
#        WORKING_DIRECTORY ${BINARY_EXT_DIR}/googletest-download )
#if(result)
#    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
#endif()
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#        RESULT_VARIABLE result
#        WORKING_DIRECTORY ${BINARY_EXT_DIR}/googletest-download )
#if(result)
#    message(FATAL_ERROR "Build step for googletest failed: ${result}")
#endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${AUDITTOOLS_DIR}/ext/googletest
        ${BINARY_EXT_DIR}/ext/googletest-build
        EXCLUDE_FROM_ALL
        )

set_target_properties( 
    gtest gtest_main
    PROPERTIES FOLDER ext/googletest
)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()

add_definitions(
        -DGTEST_DONT_DEFINE_TEST=1
        )
