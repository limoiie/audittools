#include <domain/launch/PrepareRuntimeFolderAndConfig.h>

#include <stdexcept>
#include <utility>
#include <vector>

PrepareRuntimeForlderAndConfig::PrepareRuntimeForlderAndConfig(
    PrepareRuntimeFolderAndConfig const& param)
    : param_(std::make_shared<PrepareRuntimeFolderAndConfig>(param)) {}

PrepareRuntimeForlderAndConfig::PrepareRuntimeForlderAndConfig(
    std::shared_ptr<PrepareRuntimeFolderAndConfig> param)
    : param_(std::move(param)) {}

void PrepareRuntimeForlderAndConfig::run() noexcept {
  try {
    load_and_parse_config();
    create_runtime_folders();
    dump_parsed_config_to_runtime_config_folder();
  } catch (std::exception const&) {
    on_error_(std::current_exception());
  }
  on_complete_();
}

void PrepareRuntimeForlderAndConfig::load_and_parse_config() {

}

void PrepareRuntimeForlderAndConfig::create_runtime_folders() {
  /*auto name_folders = std::vector<std::pair<std::string, path_t>>(
      {{"config", param_->app_config->get_config_folder()},
       {"log", param_->app_config->get_log_folder()},
       {"tool", param_->app_config->get_tool_folder()}});

  for (auto const& name_folder : name_folders) {
    if (!folder::create(name_folder.second))
      throw std::runtime_error(
          std::string("Cannot create folder for ").append(name_folder.first));

    on_result_(make_result("Create folder for {}"));
  }*/
}

void PrepareRuntimeForlderAndConfig::dump_parsed_config_to_runtime_config_folder() {
  // param_->app_config->dump()
}
