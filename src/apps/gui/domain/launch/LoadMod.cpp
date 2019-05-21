#include <domain/launch/LoadMod.h>

#include <domain/launch/LoadModPrepareEnv.h>
#include <domain/launch/LoadModRuntimeConfig.h>
#include <domain/launch/LoadModInitLog.h>
#include <domain/AppConfig.h>

auto const kInitLogParamLoader = [](InitLogParam* param) {
  param->logger_name = AppConfig::instance()->app_name();
  param->config = AppConfig::instance()->log_mainer();
  param->log_file = AppConfig::instance()->app_log_file();
};

std::vector<std::shared_ptr<LoadMod>> LoadMod::load_chain() {
  std::vector<std::shared_ptr<LoadMod>> mods = {
    std::make_shared<LoadModRuntimeConfig>(RuntimeConfigParam("./config.json")),
    std::make_shared<LoadModPrepareEnv>(PrepareEnvParam()),
    std::make_shared<LoadModInitLog>(InitLogParam(kInitLogParamLoader))
  };
  return mods;
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
