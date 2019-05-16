cmake_minimum_required(VERSION 3.10)
project(audittools)

# to use google-test on windows with cygwin, we need use -std=gnu++11
# instead of -std=c++11
add_definitions(-std=gnu++11)

set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

set(AUDITTOOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# the dependency direction is:
# test -> apps -> libs -> core -> ext
include(${AUDITTOOLS_DIR}/ext/prepare_ext.cmake)

include_directories(${AUDITTOOLS_DIR}/src/core)
add_subdirectory(src/core)
include_directories(${AUDITTOOLS_DIR}/src/libs)
add_subdirectory(src/libs)
include_directories(${AUDITTOOLS_DIR}/src/apps)
add_subdirectory(src/apps)

add_subdirectory(test)