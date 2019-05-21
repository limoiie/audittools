set(Boost_USE_STATIC_LIBS ON)

if (MSVC)
    set(BOOST_ROOT D:/Devs/Boost)
    set(BOOST_LIBRARYDIR D:/Devs/Boost/lib)
endif()

find_package(Boost 1.70 REQUIRED 
    COMPONENTS regex filesystem locale system context random)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "Cannot find boost! Make sure you have installed")
endif()