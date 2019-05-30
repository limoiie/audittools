#include <iostream>

#include <system/path.h>
#include <gtest/gtest.h>
#include <common/util_traits.h>

namespace {

using namespace std;

GTEST_TEST(TestPath, test_get_dir) {
  using res_t = Result<boost::filesystem::path, bool>;
  vector<res_t> res_list = {
      path::get_exe_dir(),    path::get_home_dir(),    path::get_windows_dir(),
      path::get_system_dir(), path::get_appdata_dir(),
  };

  for (auto const& res : res_list) {
    ASSERT_TRUE(res.valid());
    cout << res.value.string() << endl;
  }
}

GTEST_TEST(TestTrait, test_choose_jump) {
  auto const a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;
  std::vector<int> const x = { CHOOSE_JUMP1(a, b, c, d, e, f) };
  std::vector<int> const y = { CHOOSE_JUMP1_FROM_SECOND(a, b, c, d, e, f) };
  
  ASSERT_EQ(x, std::vector<int>({ a, c, e }));
  ASSERT_EQ(y, std::vector<int>({ b, d, f }));
}

}  // namespace