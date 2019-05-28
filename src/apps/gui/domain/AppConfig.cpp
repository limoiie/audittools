#include <system/path.h>
#include <domain/AppConfig.h>

static void format_path(std::string& path);

void AppConfigParser::config(boost::filesystem::path const& raw_cfg_file) {
  load_raw_config(raw_cfg_file);
  parse_raw_cfg();
}

void AppConfigParser::load(boost::filesystem::path const& cfg_file) {
  auto const app_cfg = AppConfig::instance();
  serialize::json::load_file(cfg_file, *app_cfg);
}

void AppConfigParser::load_raw_config(
    boost::filesystem::path const& raw_cfg_file) {
  auto app_cfg = AppConfig::instance();
  app_cfg->raw_config_ = RawConfig::instance();
  serialize::json::load_file(raw_cfg_file, *app_cfg->raw_config_);
}

void AppConfigParser::parse_raw_cfg() {
  auto const app_cfg = AppConfig::instance();
  format_path(app_cfg->raw_config_->log_folder_);
  format_path(app_cfg->raw_config_->tool_folder_);
  format_path(app_cfg->raw_config_->config_folder_);
}

static void format_path(std::string& path) {
  auto res = make_result(boost::filesystem::path(), true);
  switch (path.front()) {
    case '!':
      res = path::get_appdata_dir();
      path = res.value.append(APP_NAME).append(path.substr(1)).string();
      break;
    case '.':
      res = path::get_exe_dir();
      path = res.value.append(path.substr(1)).string();
      break;
    case '~':
      res = path::get_home_dir();
      path = res.value.append(APP_NAME).append(path.substr(1)).string();
      break;
    default:
      break;
  }
}
