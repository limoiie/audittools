#ifndef DOMAIN_LAUNCH_LOADMODINITLOG_H
#define DOMAIN_LAUNCH_LOADMODINITLOG_H

#include <base/RawConfig.hpp>
#include <domain/launch/LoadMod.h>
#include <boost/filesystem/path.hpp>

struct InitLogParam {
  friend class LoadModInitLog;

  std::string logger_name;
  LogConfig config;
  boost::filesystem::path log_file;

  /**
   * \brief Some config values have not been prepared yet, so you need use loader 
   * to load the values just before running this Mod
   * \param loader 
   */
  explicit InitLogParam(std::function<void(InitLogParam*)> const& loader);

private:
  std::function<void(InitLogParam*)> loader_;

};

class LoadModInitLog final : public LoadMod {
public:
  explicit LoadModInitLog(InitLogParam const& param);
  explicit LoadModInitLog(std::shared_ptr<InitLogParam> param);

private:
  void run_imp() override;
  void init_log();

  std::shared_ptr<InitLogParam> param_;
};

#endif // DOMAIN_LAUNCH_LOADMODINITLOG_H