#include <iostream>
#include <rxcpp/rx.hpp>
#include <string>

namespace rx = rxcpp;

using namespace std;
using namespace std::chrono;

int main() {
  auto const stream = rx::observable<>::interval<>(seconds(1))
                          .take(10)
                          .map([](int const count) {
                            return std::to_string(count).append(" seconds");
                          });
  stream.subscribe(
      [](std::string const& statement) { cout << statement << endl; });
  return 0;
}
