#include <iostream>

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <log/log.h>

namespace {

using namespace std;

GTEST_TEST(TestCommon, test_log) {
  auto const console = spdlog::stdout_color_mt("console");
  logger::info("Welcome to spdlog!");
}

}  // namespace