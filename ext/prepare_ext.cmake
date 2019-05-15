set(BINARY_EXT_DIR ${CMAKE_CURRENT_BINARY_DIR}/ext)
file(MAKE_DIRECTORY ${BINARY_EXT_DIR})

include(${AUDITTOOLS_DIR}/ext/google-test/add_googletest.cmake)