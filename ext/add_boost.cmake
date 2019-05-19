find_package(Boost 1.70 REQUIRED 
    COMPONENTS regex filesystem locale system context filesystem)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find boost! Make sure you have installed")
endif()