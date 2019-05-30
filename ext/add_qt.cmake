# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Use Qt Application
set(QT_USE_QTMAIN TRUE)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)
# Process recourse files
set(CMAKE_AUTORCC ON)

set(QT_BIN_PATH "UNKNOWN-PATH" CACHE INTERNAL "Path to qmake, windeployqt, and other Qt utilities.")

# Find packages
set(CMAKE_PREFIX_PATH "D:\\Devs\\Qt\\5.12.3\\msvc2017\\lib\\cmake")
find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# Find Qt bin path
get_target_property(_qmake_location Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_path "${_qmake_location}" DIRECTORY)

set(QT_BIN_PATH "${_qt_bin_path}")

# Find windeploy
find_program(QT_WINDEPLOYQT_EXECUTABLE windeployqt
	HINTS "${_qt_bin_path}"
	DOC "Path to the windeployqt utility."
)
if("${QT_WINDEPLOYQT_EXECUTABLE}" STREQUAL "QT_WINDEPLOYQT_EXECUTABLE-NOTFOUND")
    message(FATAL_ERROR "Can not find windeployqt.exe!!")
endif()
message(STATUS "Found windeployqt: ${QT_WINDEPLOYQT_EXECUTABLE}")

# # Find lupdate
# find_program(QT_LUPDATE_EXECUTABLE lupdate
#     HINTS "${_qt_bin_path}"
# 	DOC "Path to the lupdate utility."
# )
# message(STATUS "Found lupdate: ${QT_LUPDATE_EXECUTABLE}")

# # Find lrelease
# find_program(QT_LRELEASE_EXECUTABLE lrelease
#     HINTS "${_qt_bin_path}"
# 	DOC "Path to the lrelease utility."
# )
# message(STATUS "Found lrelease: ${QT_LUPDATE_EXECUTABLE}")

# Config target compile options and feature according to platform
function(config_target_for_qt TARGET_NAME)
    # config option
    set(_wd_config $<$<CONFIG:Debug>:--debug> $<$<NOT:$<CONFIG:Debug>>:--release>)

    # add_custom_target(auto_copy_envs)
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND echo Post build ${TARGET_NAME} start:
        COMMAND set "PATH=${QT_BIN_PATH};%PATH%"
        COMMAND "${QT_WINDEPLOYQT_EXECUTABLE}" ${_wd_config} --no-compiler-runtime $<TARGET_FILE:${TARGET_NAME}>
        COMMAND echo Post build ${TARGET_NAME} done.
    )
endfunction()