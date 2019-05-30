include_directories(.)

add_library(core 
  common/random.cpp
  common/random.h
  common/serialization.hpp
  common/Singleton.hpp
  common/Result.hpp
  common/str.cpp
  common/str.h
  common/util_traits.h
  log/log.cpp
  log/log.h
  system/register_dump.cpp
  system/register_dump.h
  system/path.cpp
  system/path.h
)