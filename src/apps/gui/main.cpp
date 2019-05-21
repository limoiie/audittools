#include <iostream>
#include <string>

#include <domain/launch/LoadMod.h>
#include <log/log.h>

// TODO: Move to Presenter
void load_mod_chain() {
  auto const on_result = [](std::shared_ptr<OutMessage> const& msg) {
    std::cout << msg->step << ": " << msg->message << std::endl;
  };

  auto const on_complete = []() {
    std::cout << "Complete sub load mod" << std::endl;
  };

  auto const on_error = [](std::exception_ptr const& exp) {
    try {
      std::rethrow_exception(exp);
    } catch (std::exception const& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  };

  for (auto& mod : LoadMod::load_chain()) {
    mod->invoke(on_result, on_complete, on_error);
  }

  LoadMod::load_chain();
}

auto main() -> int {
  load_mod_chain();
  return 0;
}