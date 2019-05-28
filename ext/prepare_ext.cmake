set(BINARY_EXT_DIR ${CMAKE_CURRENT_BINARY_DIR}/ext)
file(MAKE_DIRECTORY ${BINARY_EXT_DIR})

include(${AUDITTOOLS_DIR}/ext/add_boost.cmake)
include(${AUDITTOOLS_DIR}/ext/add_googletest.cmake)
include(${AUDITTOOLS_DIR}/ext/add_rxcpp.cmake)
include(${AUDITTOOLS_DIR}/ext/add_spdlog.cmake)
include(${AUDITTOOLS_DIR}/ext/add_cereal.cmake)
include(${AUDITTOOLS_DIR}/ext/add_sqlitecpp.cmake)