#include <domain/launch/LoadMod.h>

#include <domain/launch/LoadModRegisterDump.h>
#include <domain/launch/LoadModPrepareEnv.h>
#include <domain/launch/LoadModRuntimeConfig.h>
#include <domain/launch/LoadModInitLog.h>
#include <domain/AppConfig.h>

#include <system/path.h>

auto const kInitLogParamLoader = [](InitLogParam* param) {
  param->logger_name = AppConfig::instance()->app_name();
  param->config = AppConfig::instance()->log_mainer();
  param->log_file = AppConfig::instance()->app_log_file();
};

// TODO: Move to a dependency inject cpp
std::vector<std::shared_ptr<LoadMod>> LoadMod::load_chain() {
  auto const temp_dir = path::get_temp_dir();
  if (temp_dir.has_error())
    throw std::runtime_error(std::string("Cannot get temp folder!"));

  return std::vector<std::shared_ptr<LoadMod>> {
    std::make_shared<LoadModRegisterDump>(RegisterDumpParam(temp_dir.value, APP_NAME)),
    std::make_shared<LoadModRuntimeConfig>(RuntimeConfigParam("./config.json")),
    std::make_shared<LoadModPrepareEnv>(PrepareEnvParam()),
    std::make_shared<LoadModInitLog>(InitLogParam(kInitLogParamLoader))
  };
}

void LoadMod::run() noexcept {
  try {
    run_imp();
  } catch (std::exception const&) {
    on_error_(std::current_exception());
    return;
  }

  on_complete_();
}

void LoadMod::log(std::string msg) {
  on_result_(make_result(std::move(msg)));
}

std::shared_ptr<OutMessage> LoadMod::make_result(std::string message) {
  return std::make_shared<OutMessage>(step_++, std::move(message));
}
