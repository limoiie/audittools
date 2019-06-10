include_directories(.)

set(CMAKE_EXE_LINKER_FLAGS "/SAFESEH:NO /level='requireAdministrator'")

set(GUI_SRC_FILES
    base.h
    base/RawConfig.hpp
    base/model/ItemType.h
    base/model/table.h
    domain/AppConfig.cpp
    domain/AppConfig.h
    domain/UseCase.hpp
    domain/data/CpuData.h
    domain/data/convert/gui_converter.h
    domain/launch/LoadMod.cpp
    domain/launch/LoadMod.h
    domain/launch/LoadModRegisterDump.cpp
    domain/launch/LoadModRegisterDump.h
    domain/launch/LoadModRuntimeConfig.cpp
    domain/launch/LoadModRuntimeConfig.h
    domain/launch/LoadModPrepareEnv.cpp
    domain/launch/LoadModPrepareEnv.h
    domain/launch/LoadModInitLog.cpp
    domain/launch/LoadModInitLog.h
	)

set_property(GLOBAL PROPERTY GLOBAL_GUI_SRC_FILES ${GUI_SRC_FILES}) 

add_executable(gui main.cpp ${GUI_SRC_FILES})
target_link_libraries(gui core 
		Boost::boost Boost::filesystem
		Qt5::Core Qt5::Gui Qt5::Widgets
		Dbghelp.lib)

config_target_for_rxcpp(gui)
config_target_for_qt(gui)