#pragma once

#include <exception>
#include <functional>
#include <memory>
#include <utility>

class Void {};

struct OnCompleteEmpty {
  void operator()() const {
    // no implement
  }
};

struct OnErrorIgnore {
  void operator()(std::exception_ptr) const {
    // no implement
  }
};

template <class Out = Void, class In = Void>
class UseCase {
 public:
  using OnResult = std::function<void(std::shared_ptr<Out>)>;
  using OnComplete = std::function<void()>;
  using OnError = std::function<void(std::exception_ptr)>;

  UseCase() = default;

  virtual ~UseCase() = default;

  explicit UseCase(In param) : param_(std::make_shared<In>(std::move(param))) {}

  explicit UseCase(std::shared_ptr<In> param) : param_(std::move(param)) {}

  UseCase(UseCase const& other)
    : on_result_(other.on_result_)
  , on_complete_(other.on_complete_)
  , on_error_(other.on_error_)
  , param_(other.param_) {
  }

  UseCase(UseCase&& other) noexcept
    : on_result_(std::move(other.on_result_))
  , on_complete_(std::move(other.on_complete_))
  , on_error_(std::move(other.on_error_))
  , param_(std::move(other.param_)) {
  }

  UseCase& operator=(UseCase const& other) {
    if (this == &other)
      return *this;
    on_result_ = other.on_result_;
    on_complete_ = other.on_complete_;
    on_error_ = other.on_error_;
    param_ = other.param_;
    return *this;
  }

  UseCase& operator=(UseCase&& other) noexcept {
    if (this == &other)
      return *this;
    on_result_ = std::move(other.on_result_);
    on_complete_ = std::move(other.on_complete_);
    on_error_ = std::move(other.on_error_);
    param_ = std::move(other.param_);
    return *this;
  }

  virtual void invoke(OnResult const& on_result,
                      OnComplete const& on_complete = OnCompleteEmpty(),
                      OnError const& on_error = OnErrorIgnore()) {
    on_result_ = on_result;
    on_complete_ = on_complete;
    on_error_ = on_error;

    run();
  }

 protected:
  virtual void run() noexcept = 0;

  OnResult on_result_;
  OnComplete on_complete_;
  OnError on_error_;

  std::shared_ptr<In> param_;
};