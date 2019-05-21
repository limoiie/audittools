#include <domain/launch/LoadModPrepareEnv.h>

#include <boost/filesystem/path.hpp>

#include <domain/AppConfig.h>

LoadModPrepareEnv::LoadModPrepareEnv(PrepareEnvParam const& param)
  : param_(std::make_shared<PrepareEnvParam>(param)) {
}

LoadModPrepareEnv::LoadModPrepareEnv(std::shared_ptr<PrepareEnvParam> param)
  : param_(std::move(param)) {
}

void LoadModPrepareEnv::run_imp() { create_runtime_folders(); }

void LoadModPrepareEnv::create_runtime_folders() {
  auto const config = AppConfig::instance();

  auto name_folders =
    std::vector<std::pair<std::string, boost::filesystem::path>>({
      {"config", config->config_folder()},
      {"log", config->log_folder()},
      {"tool", config->tool_folder()}
    });

  for (auto const& name_folder : name_folders) {
    if (exists(name_folder.second) && is_directory(name_folder.second)) {
      log(std::string("Prepared folder for ").append(name_folder.first));
    } else {
      if (!create_directories(name_folder.second))
        throw std::runtime_error(
            std::string("Cannot create folder for ").append(name_folder.first));
      
      log(std::string("Create folder for ").append(name_folder.first));
    }
  }
}
