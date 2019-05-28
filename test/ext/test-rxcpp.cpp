#include <iostream>
#include <string>

#include <gtest/gtest.h>
#include <rxcpp/rx.hpp>

namespace rx = rxcpp;
namespace rxu = rxcpp::util;

namespace
{
  GTEST_TEST(TestRxCpp, test_rxcpp) {
    auto get_names = []() {
      return rx::observable<>::from<std::string>("Matthew", "Aaron");
    };

    std::cout << "===== println stream of std::string =====" << std::endl;
    auto const hello_str = [&]() {
      return get_names()
        .map([](std::string n) { return "Hello, " + n + "!"; })
        .as_dynamic();
    };

    hello_str().subscribe(rxu::println(std::cout));

    std::cout << "===== println stream of std::tuple =====" << std::endl;
    auto const hello_tpl = [&]() {
      return get_names()
        .map([](std::string n) {
        return std::make_tuple("Hello, ", n, "! (", n.size(), ")");
      })
        .as_dynamic();
    };

    hello_tpl().subscribe(rxu::println(std::cout));

    hello_tpl().subscribe(rxu::print_followed_by(std::cout, " and "),
                          rxu::endline(std::cout));
  }

  GTEST_TEST(TestRxCpp, test_on_event_loop) {
    auto threads = rxcpp::observe_on_event_loop();

    auto values = rxcpp::observable<>::range(
        1);  // infinite (until overflow) stream of integers

    auto s1 = values.subscribe_on(threads).map([](int prime) {
      std::cout << "1/" << prime << ": " << std::this_thread::get_id() << std::endl;
      std::this_thread::yield();
      return std::make_tuple("1:", prime);
    });

    auto s2 = values.subscribe_on(threads).map([](int prime) {
      std::cout << "2/" << prime << ": " << std::this_thread::get_id() << std::endl;
      std::this_thread::yield();
      return std::make_tuple("2:", prime);
    });

    s1.merge(s2).take(6).observe_on(threads).as_blocking().subscribe(
        rxcpp::util::apply_to([](const char*, int) {
      std::cout << "o: " << std::this_thread::get_id() << std::endl;
      // printf("%s %d\n", s, p);
    }));
  }

}  // namespace