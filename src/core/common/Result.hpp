#ifndef CORE_COMMON_RESULT_H
#define CORE_COMMON_RESULT_H

#include <exception>

template <class ErrType>
bool dose_this_mean_error(ErrType const& err) {
  // ReSharper disable once CppStaticAssertFailure
  static_assert(false,
                "You need to override dose_this_mean_error for this ErrType!");
  return false;
};

template <class ValType, class ErrType>
struct Result {
  ValType value;
  ErrType error;

  Result(ValType const& value, ErrType const& error)
      : value(value), error(error) {}

  Result(ValType&& value, ErrType&& error)
      : value(std::forward<ValType>(value)),
        error(std::forward<ErrType>(error)) {}

  bool valid() const { return !has_error(); }
  bool has_error() const { return dose_this_mean_error(error); }
};

template <class ValType, class ErrType>
Result<ValType, ErrType> make_result(ValType const& val, ErrType const& err) {
  return Result<ValType, ErrType>(val, err);
}

template <class ValType, class ErrType>
Result<ValType, ErrType> make_result(ValType&& val, ErrType&& err) {
  return Result<ValType, ErrType>(std::forward<ValType>(val),
                                  std::forward<ErrType>(err));
}

template <>
inline bool dose_this_mean_error<int>(int const& err) {
  return err != 0;
}

template <>
inline bool dose_this_mean_error<bool>(bool const& err) {
  // true means there is an error
  return err;
}

template <>
inline bool dose_this_mean_error<std::exception_ptr>(
    std::exception_ptr const& err) {
  return err.operator bool();
}

#endif  // CORE_COMMON_RESULT_H