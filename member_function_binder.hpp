#pragma once

#include "functional"
#include "iostream"
#include "memory"

template<typename... FuncArgs>
class MemberFunctionBinder {
public:
  using FuncType = std::shared_ptr<std::function<void(FuncArgs...)>>;
  static void CallbackFunc(FuncArgs... args) {
    if (func_cb_) {
      (*func_cb_)(args...);
    } else {
      std::cout << "callback is empty" << std::endl;
    }
  }

  static void RegisterCb(FuncType func) {
    func_cb_ = func;
  }

  static FuncType func_cb_;
};

// C++11的静态变量需要在类外初始化
template<typename... FuncArgs>
std::shared_ptr<std::function<void(FuncArgs...)>> MemberFunctionBinder<FuncArgs...>::func_cb_ = nullptr;
