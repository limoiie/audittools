#include <gtest/gtest.h>

// ReSharper disable once CppUnusedIncludeDirective
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

#include <common/serialization.hpp>
#include <common/random.h>

using namespace std;

namespace {

struct Obj {
  std::vector<int> nums;
  std::string name;
  int age{};

  friend bool operator==(Obj const& lhs, Obj const& rhs) {
    return lhs.nums == rhs.nums && lhs.name == rhs.name && lhs.age == rhs.age;
  }

  template <class Archive>
  void serialize(Archive& ar) {
    ar(CEREAL_NVP(nums), CEREAL_NVP(name), CEREAL_NVP(age));
  }
};

GTEST_TEST(TestJson, test_string_stream) {
  Obj obj;
  obj.nums = {1, 3, 9};
  obj.name = "James";
  obj.age = 101;

  auto const serialization = serialize::json::dump(obj);
  Obj obj_fake;
  serialize::json::load(serialization, obj_fake);

  GTEST_ASSERT_EQ(obj, obj_fake);
}

GTEST_TEST(TestJson, test_file_stream) {
  auto const test_filename = random_filename(10, "test", ".json");
  boost::filesystem::path const test_file(test_filename);

  Obj obj;
  obj.nums = {1, 3, 9};
  obj.name = "James";
  obj.age = 101;

  serialize::json::dump_file(test_file, obj);
  Obj obj_fake;
  serialize::json::load_file(test_file, obj_fake);

  GTEST_ASSERT_EQ(obj, obj_fake);
  GTEST_ASSERT_EQ(true, boost::filesystem::remove(test_file));
}

}  // namespace