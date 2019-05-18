#ifndef CORE_COMMON_SINGLETON_H
#define CORE_COMMON_SINGLETON_H

#include <memory>

template <typename T>
class Singleton {
 protected:
  Singleton() = default;
  virtual ~Singleton() = default;

 public:
  static std::shared_ptr<T> instance() {
    // NOTE: DO NOT use make_share to create the object cause
    // it's SingleTon<T> instead of make_share is a friend of T
    // ReSharper disable once CppSmartPointerVsMakeFunction
    static auto ins = std::shared_ptr<T>(new T);
    return ins;
  }

  static void release() { instance().reset(); }
};

#endif // CORE_COMMON_SINGLETON_H