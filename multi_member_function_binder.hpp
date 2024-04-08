#pragma once

#include "functional"
#include "iostream"
#include "memory"

template<int HubID, typename... FuncArgs>
class MultipleMemberFunctionBinder {
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

template<int HubID, typename... FuncArgs>
std::shared_ptr<std::function<void(FuncArgs...)>> MultipleMemberFunctionBinder<HubID, FuncArgs...>::func_cb_ = nullptr;

