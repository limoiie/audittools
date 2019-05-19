#include <gtest/gtest.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/sequence_traits.hpp>
#include <boost/context/fiber.hpp>
#include <boost/convert.hpp>
#include <boost/convert/lexical_cast.hpp>
#include <boost/format.hpp>
#include <boost/locale.hpp>
#include <boost/core/noncopyable.hpp>

#include <fstream>

using namespace std;
using namespace boost;
using namespace boost::locale;
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

  string str2 = to_lower_copy(ireplace_first_copy(
      str1, "hello", "goodbye"));  // str2 == "goodbye world!"
  cout << str2 << endl;

  string str3("hello abc-*-ABC-*-aBc goodbye");

  typedef vector<iterator_range<string::iterator> > find_vector_type;

  find_vector_type FindVec;         // #1: Search for separators
  ifind_all(FindVec, str3, "abc");  // FindVec == { [abc],[ABC],[aBc] }

  typedef vector<string> split_vector_type;

  split_vector_type SplitVec;  // #2: Search for tokens
  split(SplitVec, str3, is_any_of("-*"),
        token_compress_on);  // SplitVec == { "hello abc","ABC","aBc goodbye" }
}

GTEST_TEST(TestBoost, test_format) {
  cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 %
              50;

  cout << boost::format("(x,y) = (%+5d,%+5d) \n") % -23 % 35;
  cout << boost::format("(x,y) = (%|+5|,%|+5|) \n") % -23 % 35;
  cout << boost::format("(x,y) = (%1$+5d,%2$+5d) \n") % -23 % 35;
  cout << boost::format("(x,y) = (%|1$+5|,%|2$+5|) \n") % -23 % 35;
}

GTEST_TEST(TestBoost, test_context) {
  namespace ctx = boost::context;
  int a;
  ctx::fiber source{[&a](ctx::fiber&& sink) {
    a = 0;
    int b = 1;
    for (;;) {
      sink = std::move(sink).resume();
      int next = a + b;
      a = b;
      b = next;
    }
    return std::move(sink);
  }};
  for (int j = 0; j < 10; ++j) {
    source = std::move(source).resume();
    std::cout << a << " ";
  }
}

GTEST_TEST(TestBoost, test_locale) {}

GTEST_TEST(TestBoost, test_convert) {
  try {
    boost::cnv::lexical_cast cnv;  // boost::lexical_cast-based converter

    // boost::lexical_cast standard deployment
    int i1 = lexical_cast<int>("123");
    // boost::convert with the default converter
    int i2 = convert<int>("123").value();
    // boost::convert with an explicit converter
    int i3 = convert<int>("123", cnv).value();

    // boost::lexical_cast standard deployment
    string s1 = lexical_cast<string>(123);
    // boost::convert with the default converter
    string s2 = convert<string>(123).value();
    // boost::convert with an explicit converter
    string s3 = convert<string>(123, cnv).value();

    GTEST_ASSERT_EQ(i1, 123);
    GTEST_ASSERT_EQ(i2, 123);
    GTEST_ASSERT_EQ(i3, 123);
    GTEST_ASSERT_EQ(s1, "123");
    GTEST_ASSERT_EQ(s2, "123");
    GTEST_ASSERT_EQ(s3, "123");

  } catch (std::exception const& ex) {
    // Please be aware that the conversion requests above can fail.
    // Use try'n'catch blocks to handle any exceptions thrown.
    // Ignore this at your peril!
    std::cerr << "Exception " << ex.what() << std::endl;
  }
}

GTEST_TEST(TestBoost, test_folder) {

}

}  // namespace