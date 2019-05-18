include_directories(.)

set(SRC_FILES main.cpp 
    base/RawConfig.hpp
    domain/AppConfig.hpp
    domain/UseCase.hpp
    domain/launch/LoadMod.h
    domain/launch/PrepareRuntimeFolderAndConfig.cpp
    domain/launch/PrepareRuntimeFolderAndConfig.h
	)

add_executable(gui ${SRC_FILES})
target_link_libraries(gui core)

config_target_for_rxcpp(gui)