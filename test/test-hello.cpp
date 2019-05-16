#include <iostream>

#include <common/hello.h>
#include <gtest/gtest.h>

namespace {

using namespace std;

GTEST_TEST(TestCommon, test_hello) {
  print_hello();
}

}  // namespace