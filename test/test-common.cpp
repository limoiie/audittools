#include <iostream>

#include <common/path.h>
#include <gtest/gtest.h>

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

}  // namespace