#include <iostream>

#include <gtest/gtest.h>

#include <common/str.h>

namespace {

using namespace std;

GTEST_TEST(TestStr, test_convert) {
  std::string const ansi_string = "众里寻他千百度";
  std::wstring const unic_string = L"众里寻他千百度";
  
  auto unic_string_res =
      ansi_to_unicode(ansi_string, str::ansi_encoding_e::UTF8);
  GTEST_ASSERT_EQ(unic_string_res.has_error(), false);
  GTEST_ASSERT_EQ(unic_string_res.value, unic_string);

  auto ansi_string_res =
      unicode_to_ansi(unic_string, str::ansi_encoding_e::UTF8);
  GTEST_ASSERT_EQ(ansi_string_res.has_error(), false);
  GTEST_ASSERT_EQ(ansi_string_res.value, ansi_string);
}

}  // namespace