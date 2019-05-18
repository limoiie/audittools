#pragma once

#include <string>

#include <cereal/archives/json.hpp>
#include <cereal/cereal.hpp>

#include <log/log.h>
#include <common/Singleton.hpp>

struct LogConfig {
  bool log_to_console{false};
  bool log_to_file{false};
  logger::level_e log_level{logger::level_e::ERR};

  template <class Archive>
  void serialize(Archive& archive) {
    archive(CEREAL_NVP(log_to_console), CEREAL_NVP(log_to_file),
            CEREAL_NVP(log_level));
  }
};

/**
 * NOTE: You should use AppConfig to access the config instead of
 * this class. This class will parse user's config file and AppConfig
 * will process it with more necessary actions according to the
 * runtime environment.
 */
class RawCofnig final : Singleton<RawCofnig> {
  friend class Singleton<RawCofnig>;
  friend class AppConfig;

  std::string config_folder_;
  std::string log_folder_;
  std::string tool_folder_;

  LogConfig log_daemon_;
  LogConfig log_master_;
  LogConfig log_queuer_;
  LogConfig log_worker_;
  LogConfig log_sinker_;

  unsigned long heartbeat_;
  unsigned long heartbeat_timeout_;
  unsigned long master_idle_timeout_;
  unsigned long system_idle_timeout_;
  unsigned long worker_working_timeout_;

  unsigned worker_num_;

  template <class Archive>
  void serialize(Archive& archive) {
    archive(CEREAL_NVP(config_folder_), CEREAL_NVP(log_folder_),
            CEREAL_NVP(tool_folder_), CEREAL_NVP(log_daemon_),
            CEREAL_NVP(log_master_), CEREAL_NVP(log_queuer_),
            CEREAL_NVP(log_worker_), CEREAL_NVP(log_sinker_),
            CEREAL_NVP(heartbeat_), CEREAL_NVP(heartbeat_timeout_),
            CEREAL_NVP(master_idle_timeout_), CEREAL_NVP(system_idle_timeout_),
            CEREAL_NVP(worker_working_timeout_), CEREAL_NVP(worker_num_));
  }
};