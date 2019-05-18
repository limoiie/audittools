#pragma once

#include <domain/UseCase.hpp>

struct OutMessage {
  unsigned step;
  std::string message;

  OutMessage(unsigned const step, std::string message)
      : step(step), message(std::move(message)) {}
};

/**
 * \brief Derive this class to do special initialization before 
 * app actually runs. NOTE this UseCase has a Void InType, which
 * does not means you cannot pass a param to the mod. You can,
 * and also you should, handle the param in each separate derive
 * classes, so that we can store all the LoadMods into a list.
 */
class LoadMod : public UseCase<OutMessage, Void> {
 protected:
  using OutType = OutMessage;
  using InType = Void;

 public:
  explicit LoadMod()
      : UseCase<OutType, InType>(Void()) {}

 protected:
  void run() noexcept override = 0;

  auto make_result(std::string message) {
    auto const out_message =
        std::make_shared<OutMessage>(step_++, std::move(message));
    return out_message;
  }

 private:
  unsigned step_{0};
};
