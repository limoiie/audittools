#ifndef CORE_COMMON_LOG_H
#define CORE_COMMON_LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace logger {

  enum level_e {
    TRACE  = SPDLOG_LEVEL_TRACE, 
    DEBUG  = SPDLOG_LEVEL_DEBUG, 
    INFO   = SPDLOG_LEVEL_INFO, 
    WARN   = SPDLOG_LEVEL_WARN, 
    ERR    = SPDLOG_LEVEL_ERROR, 
    FATAL  = SPDLOG_LEVEL_CRITICAL
  };

  inline
  spdlog::level::level_enum to_spd_lvl(level_e const lvl) {
    return static_cast<spdlog::level::level_enum>(lvl);
  }

#define DEFINE_LOG_FUNCTION(LEVEL, SPD_FUNC) \
  template<typename... AN> \
  void LEVEL(AN... an) { \
    spdlog::SPD_FUNC(std::forward<AN>(an)...); \
  }

  DEFINE_LOG_FUNCTION(trace, trace)
  DEFINE_LOG_FUNCTION(debug, debug)
  DEFINE_LOG_FUNCTION(info, info)
  DEFINE_LOG_FUNCTION(warn, warn)
  DEFINE_LOG_FUNCTION(err, error)
  DEFINE_LOG_FUNCTION(fatal, critical)
  
#undef DEFINE_LOG_FUNCTION

}

#endif // CORE_COMMON_LOG_H