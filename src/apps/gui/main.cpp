#include <iostream>
#include <rxcpp/rx.hpp>
#include <sstream>
#include <string>

namespace rx = rxcpp;

using namespace std;
using namespace std::chrono;

rxcpp::observable<std::string> create() {
  return rx::observable<>::interval<>(seconds(1))
      .take(10)
      .map([](int const count) {
        return std::to_string(count).append(" seconds");
      })
      .as_dynamic();
}

void test_return_type() {
  auto const stream = create();
  stream.subscribe(
      [](std::string const& statement) { cout << statement << endl; });
}

std::string get_pid() {
  std::stringstream ss;
  ss << std::this_thread::get_id();
  return ss.str();
}

void test() {
  std::cout << "start on " << get_pid() << std::endl;
  auto values = rxcpp::observable<>::interval(std::chrono::milliseconds(50))
                    .take(5)
                    .observe_on(rx::observe_on_event_loop())
                    .publish();
  // .publish_synchronized(rxcpp::observe_on_new_thread());
  // Subscribe from the beginning
  values.subscribe(
      [](long v) { printf("[1/%s] OnNext: %ld\n", get_pid().c_str(), v); },
      []() { printf("[1/%s] OnCompleted\n", get_pid().c_str()); });
  // Another subscription from the beginning
  values.subscribe(
      [](long v) { printf("[2/%s] OnNext: %ld\n", get_pid().c_str(), v); },
      []() { printf("[2/%s] OnCompleted\n", get_pid().c_str()); });
  // Start emitting
  values.connect();
  // Wait before subscribing
  rxcpp::observable<>::timer(std::chrono::milliseconds(75))
      .subscribe([&](long) {
        values.subscribe(
            [](long v) {
              printf("[3/%s] OnNext: %ld\n", get_pid().c_str(), v);
            },
            []() { printf("[3/%s] OnCompleted\n", get_pid().c_str()); });
      });
  // Add blocking subscription to see results
  values.as_blocking().subscribe();
}

class Obj {
 public:
  int x;
};

auto main() -> int {
  Obj obj = {};
  obj.x = 10;
  auto const p_obj = std::make_shared<Obj>(std::move(obj));
  std::cout << p_obj->x << std::endl;
  return 0;
}
