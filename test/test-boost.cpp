#include <gtest/gtest.h>

#include <boost/algorithm/string.hpp>
#include <boost/context/fiber.hpp>
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/format.hpp>
#include <boost/locale.hpp>

#include <common/random.h>
#include <boost/filesystem/operations.hpp>

using namespace std;
using namespace boost;
using namespace locale;
using boost::convert;
using boost::lexical_cast;
using std::string;

namespace {

GTEST_TEST(TestBoost, test_string) {
  string str1(" hello, world! ");
  to_upper(str1);  // str1 == " HELLO WORLD! "
  cout << str1 << endl;
  trim(str1);  // str1 == "HELLO WORLD!"
  cout << str1 << endl;

  auto const str2 = to_lower_copy(ireplace_first_copy(
      str1, "hello", "goodbye"));  // str2 == "goodbye world!"
  cout << str2 << endl;

  string str3("hello abc-*-ABC-*-aBc goodbye");

  typedef vector<iterator_range<string::iterator> > find_vector_type;

  find_vector_type find_vec;         // #1: Search for separators
  ifind_all(find_vec, str3, "abc");  // FindVec == { [abc],[ABC],[aBc] }

  typedef vector<string> split_vector_type;

  split_vector_type split_vec;  // #2: Search for tokens
  split(split_vec, str3, is_any_of("-*"),
        token_compress_on);  // SplitVec == { "hello abc","ABC","aBc goodbye" }
}

GTEST_TEST(TestBoost, test_format) {
  cout << boost::format("writing %1%, x=%2%: %3%-th try") % "toto" % 40.23 % 50;

  cout << boost::format("(x,y) = (%+5d,%+5d) \n") % -23 % 35;
  cout << boost::format("(x,y) = (%|+5|,%|+5|) \n") % -23 % 35;
  cout << boost::format("(x,y) = (%1$+5d,%2$+5d) \n") % -23 % 35;
  cout << boost::format("(x,y) = (%|1$+5|,%|2$+5|) \n") % -23 % 35;
}

GTEST_TEST(TestBoost, test_context) {
  namespace ctx = context;
  int a;
  ctx::fiber source{[&a](ctx::fiber&& sink) {
    a = 0;
    auto b = 1;
    for (;;) {
      sink = std::move(sink).resume();
      auto const next = a + b;
      a = b;
      b = next;
    }
    // ReSharper disable once CppUnreachableCode
    return std::move(sink);
  }};
  for (auto j = 0; j < 10; ++j) {
    source = std::move(source).resume();
    std::cout << a << " ";
  }
}

GTEST_TEST(TestBoost, test_locale) {}

GTEST_TEST(TestBoost, test_convert) {
  try {
    cnv::lexical_cast const cnv;  // boost::lexical_cast-based converter

    // boost::lexical_cast standard deployment
    auto const i1 = lexical_cast<int>("123");
    // boost::convert with the default converter
    // boost::convert with an explicit converter
    auto const i3 = convert<int>("123", cnv).value();

    // boost::lexical_cast standard deployment
    auto const s1 = std::to_string(123);
    // boost::convert with the default converter
    // boost::convert with an explicit converter
    auto const s3 = convert<string>(123, cnv).value();

    GTEST_ASSERT_EQ(i1, 123);
    GTEST_ASSERT_EQ(i3, 123);
    GTEST_ASSERT_EQ(s1, "123");
    GTEST_ASSERT_EQ(s3, "123");

  } catch (std::exception const& ex) {
    // Please be aware that the conversion requests above can fail.
    // Use try'n'catch blocks to handle any exceptions thrown.
    // Ignore this at your peril!
    std::cerr << "Exception " << ex.what() << std::endl;
  }
}

GTEST_TEST(TestBoost, test_folder) {
  while (true) {
    auto const non_exist_folder_name = random_filename(10);
    auto non_exist_path = filesystem::path(non_exist_folder_name);

    if (exists(non_exist_path)) continue;

    auto const non_exist_sub_folder =
        filesystem::path(non_exist_path).append(random_filename(10));

    GTEST_ASSERT_EQ(filesystem::exists(non_exist_path), false);
    create_directories(non_exist_sub_folder);
    GTEST_ASSERT_EQ(filesystem::exists(non_exist_sub_folder), true);

    remove_all(non_exist_path);
    GTEST_ASSERT_EQ(filesystem::exists(non_exist_path), false);

    remove(non_exist_path);
    remove_all(non_exist_path);
    return;
  }
}

}  // namespace