#include <gtest/gtest.h>

#include <system/path.h>
#include <common/random.h>
#include <gui/domain/AppConfig.h>
#include <common/serialization.hpp>
#include <gui/base/RawConfig.hpp>

namespace
{

  auto const kTestConfigTemplate = R"({
      "value0": {
          "config_folder_": "~\\config",
          "log_folder_": "!\\log",
          "tool_folder_": ".\\tool",
          "log_mainer_": {
              "log_to_console": true,
              "log_to_file": true,
              "log_level": 1
          },
          "log_daemon_": {
              "log_to_console": false,
              "log_to_file": false,
              "log_level": 4
          },
          "log_master_": {
              "log_to_console": false,
              "log_to_file": false,
              "log_level": 4
          },
          "log_queuer_": {
              "log_to_console": false,
              "log_to_file": false,
              "log_level": 4
          },
          "log_worker_": {
              "log_to_console": false,
              "log_to_file": false,
              "log_level": 4
          },
          "log_sinker_": {
              "log_to_console": false,
              "log_to_file": false,
              "log_level": 4
          },
          "heartbeat_": 1000,
          "heartbeat_timeout_": 10000,
          "master_idle_timeout_": 20000,
          "system_idle_timeout_": 2000,
          "worker_working_timeout_": 180000,
          "worker_num_": 2
      }
})";

  GTEST_TEST(TestAppConfig, test_config) {
    auto const temp_raw_config_path = random_filename(10, "test_raw", ".json");
    std::ofstream fs(temp_raw_config_path);
    fs << kTestConfigTemplate;
    fs.close();

    AppConfigParser::config(temp_raw_config_path);

    ASSERT_EQ(AppConfig::instance()->heartbeat(),
              static_cast<unsigned long>(1000));

    ASSERT_EQ(
            AppConfig::instance()->config_folder(),
            path::get_home_dir().value.append(APP_NAME).append("config"));

    ASSERT_EQ(
        AppConfig::instance()->log_folder(),
        path::get_appdata_dir().value.append(APP_NAME).append("log"));

    ASSERT_EQ(AppConfig::instance()->tool_folder(),
              path::get_exe_dir().value.append("tool"));

    boost::filesystem::remove(temp_raw_config_path);
  }

}  // namespace