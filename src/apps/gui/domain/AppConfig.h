#ifndef DOMAIN_SHUTDOWN_APPCONFIG_H
#define DOMAIN_SHUTDOWN_APPCONFIG_H

#include <boost/filesystem/path.hpp>

#include <base/RawConfig.hpp>
#include <common/Singleton.hpp>
#include <common/serialization.hpp>

// TODO: move this out of gui
#define APP_NAME "AuditTools"
#define CFG_NAME "RuntimeConfig.json"

class AppConfig final : public Singleton<AppConfig> {
  friend class Singleton<AppConfig>;
  friend class AppConfigParser;
  friend class cereal::access;

public:
  static std::string app_name() {
    return std::string(APP_NAME);
  }

  boost::filesystem::path config_folder() const {
    return boost::filesystem::path(raw_config_->config_folder_);
  }

  boost::filesystem::path log_folder() const {
    return boost::filesystem::path(raw_config_->log_folder_);
  }

  boost::filesystem::path tool_folder() const {
    return boost::filesystem::path(raw_config_->tool_folder_);
  }

  boost::filesystem::path app_log_file() const {
    return boost::filesystem::path(raw_config_->log_folder_).append(app_name());
  }

  boost::filesystem::path config_file() const {
    return config_folder().append(CFG_NAME);
  }

  LogConfig const& log_mainer() const { return raw_config_->log_mainer_; }

  LogConfig const& log_daemon() const { return raw_config_->log_daemon_; }

  LogConfig const& log_master() const { return raw_config_->log_master_; }

  LogConfig const& log_queuer() const { return raw_config_->log_queuer_; }

  LogConfig const& log_worker() const { return raw_config_->log_worker_; }

  LogConfig const& log_sinker() const { return raw_config_->log_sinker_; }

  unsigned long heartbeat() const { return raw_config_->heartbeat_; }

  unsigned long heartbeat_timeout() const {
    return raw_config_->heartbeat_timeout_;
  }

  unsigned long master_idle_timeout() const {
    return raw_config_->master_idle_timeout_;
  }

  unsigned long system_idle_timeout() const {
    return raw_config_->system_idle_timeout_;
  }

  unsigned long worker_working_timeout() const {
    return raw_config_->worker_working_timeout_;
  }

  unsigned worker_num() const { return raw_config_->worker_num_; }

private:
  template <class Archive>
  void serialize(Archive& archive) {
    archive(raw_config_);
  }

  std::shared_ptr<RawConfig> raw_config_;

};

class AppConfigParser final {
public:
  /**
   * \brief Load raw configuration and process it with runtime info.
   * NOTE: Main app will call this function to parse the raw config that
   * user inputs, then process it with more runtime info to get a full
   * configuration. And also the main app should also dump %class AppConfig
   * to somewhere so that the other apps could just load from it to reach
   * an agreement.
   * \param raw_cfg_file Contains serialization of %class RawConfig
   */
  static void config(boost::filesystem::path const& raw_cfg_file);

  /**
   * \brief Load configuration from json file. This will throw exception
   * if there is something wrong.
   * NOTE: Other apps (like worker, daemon, etc) should call this function
   * instead of %function config() to load config, since the main app will
   * do that stuff for them.
   * \param cfg_file Contains serialization of %class AppConfig
   */
  static void load(boost::filesystem::path const& cfg_file);

private:
  static void load_raw_config(
      boost::filesystem::path const& raw_cfg_file);

  static void parse_raw_cfg();
};

#endif  // DOMAIN_SHUTDOWN_APPCONFIG_H