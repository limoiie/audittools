#include <domain/launch/LoadModRuntimeConfig.h>

#include <domain/AppConfig.h>
#include <stdexcept>
#include <utility>
#include <vector>

LoadModRuntimeConfig::LoadModRuntimeConfig(RuntimeConfigParam const& param)
  : param_(std::make_shared<RuntimeConfigParam>(param)) {
}

LoadModRuntimeConfig::LoadModRuntimeConfig(
    std::shared_ptr<RuntimeConfigParam> param)
  : param_(std::move(param)) {
}

void LoadModRuntimeConfig::run_imp() {
  load_and_parse_config();
  dump_config_to_rtcfg_folder();
}

void LoadModRuntimeConfig::load_and_parse_config() {
  try {
    AppConfigParser::config(param_->raw_config_path);
    log(std::string("Load raw config: ").append(param_->raw_config_path.string()));
  } catch (std::exception const& e) {
    throw std::domain_error(
        std::string("Fail to parse raw config: ").append(e.what()));
  }
}

void LoadModRuntimeConfig::dump_config_to_rtcfg_folder() {
  serialize::json::dump_file(AppConfig::instance()->config_file(),
                             AppConfig::instance().operator*());

  log(std::string("Dump config to: ")
      .append(AppConfig::instance()->config_file().string()));
}
