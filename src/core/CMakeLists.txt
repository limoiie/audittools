include_directories(.)

add_library(core 
  common/hello.h
  common/hello.cpp
  common/Singleton.hpp
  common/Path.cpp
  common/Path.h
  common/Result.hpp
  common/str.cpp
  common/str.h
  log/log.cpp
  log/log.h
)