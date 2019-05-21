#include <domain/launch/LoadModInitLog.h>

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>

#include <log/log.h>

using namespace spdlog::sinks;

InitLogParam::InitLogParam(std::function<void(InitLogParam*)> const& loader)
  : loader_(loader) {
}

LoadModInitLog::LoadModInitLog(InitLogParam const& param)
  : param_(std::make_shared<InitLogParam>(param)) {
}

LoadModInitLog::LoadModInitLog(std::shared_ptr<InitLogParam> param)
  : param_(std::move(param)) {
}

void LoadModInitLog::run_imp() {
  param_->loader_(param_.get());
  init_log();
}

void LoadModInitLog::init_log() {
  std::vector<std::shared_ptr<sink>> sinks;
  if (param_->config.log_to_console) {
    sinks.push_back(std::make_shared<stderr_color_sink_mt>());

    log(std::string("Config log to console"));
  }
  if (param_->config.log_to_file) {
    sinks.push_back(std::make_shared<daily_file_sink_mt>(
      param_->log_file.string(), 23, 59));

    log(std::string("Config log to file: ").append(param_->log_file.string()));
  }

  auto const logger =
    std::make_shared<spdlog::logger>(param_->logger_name, sinks.begin(), sinks.end());

  logger->set_level(to_spd_lvl(param_->config.log_level));
  log(std::string("Log level: ").append(std::to_string(param_->config.log_level)));

  set_default_logger(logger);
}
