include_directories(.)

set(SRC_FILES main.cpp)

add_executable(gui ${SRC_FILES})

target_link_libraries(gui core)