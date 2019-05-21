#ifndef DOMAIN_LAUNCH_LOADMODRUNTIMECONFIG_H
#define DOMAIN_LAUNCH_LOADMODRUNTIMECONFIG_H

#include <domain/launch/LoadMod.h>
#include <boost/filesystem/path.hpp>

struct RuntimeConfigParam {
  boost::filesystem::path raw_config_path;

  explicit RuntimeConfigParam(boost::filesystem::path raw_config_path)
    : raw_config_path(std::move(raw_config_path)) {
  }
};

class LoadModRuntimeConfig final : public LoadMod {
 public:
  explicit LoadModRuntimeConfig(RuntimeConfigParam const& param);

  explicit LoadModRuntimeConfig(
    std::shared_ptr<RuntimeConfigParam> param);

 private:
  void run_imp() override;
  
  void load_and_parse_config();
  void dump_config_to_rtcfg_folder();

  std::shared_ptr<RuntimeConfigParam> param_;

};

#endif  // DOMAIN_LAUNCH_LOADMODRUNTIMECONFIG_H