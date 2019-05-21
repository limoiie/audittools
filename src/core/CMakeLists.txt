include_directories(.)

add_library(core 
  common/random.h
  common/serialization.hpp
  common/Singleton.hpp
  common/path.cpp
  common/path.h
  common/Result.hpp
  common/str.cpp
  common/str.h
  log/log.cpp
  log/log.h
)