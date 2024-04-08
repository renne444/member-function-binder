#include "functional"
#include "iostream"
#include "member_function_binder.hpp"
#include "memory"
#include "multi_member_function_binder.hpp"
using namespace std;

void cb1(int v) { cout << "cb1: " << v << endl; }
void cb2(double v) { cout << "cb2: " << v << endl; }

// When different types of templates are expanded, the compiler generates
// multiple copies of the template. Consequently, static variables are also
// duplicated. We can use MemberFunctionBinder<Args...> to binding a function
// value when we do not have multiple same type of function.
//
// To achieve multiple instances of the same type of member function, we can use
// MultipleMemberFunctionBinder<int, Args...>. By varying the binding number,
// the compiler expands the template into distinct copies based on that number

int main() {
  // sample for single member function binder
  MemberFunctionBinder<int>::RegisterCb(make_shared<function<void(int)>>(cb1));
  MemberFunctionBinder<int>::CallbackFunc(10);

  MemberFunctionBinder<double>::RegisterCb(
      make_shared<function<void(double)>>(cb2));
  MemberFunctionBinder<double>::CallbackFunc(20.5);
  MemberFunctionBinder<unsigned>::CallbackFunc(1); // print "callback is empty"

  // sample for multiple member function binder
  MultipleMemberFunctionBinder<1, int>::RegisterCb(
      make_shared<function<void(int)>>(cb1));
  MultipleMemberFunctionBinder<1, int>::CallbackFunc(10);

  MultipleMemberFunctionBinder<2, int>::CallbackFunc(
      30); // print "callback is empty" because the binder with binding number 2
           // have not been registered
}

/**
cb1: 10
cb2: 20.5
callback is empty
cb1: 10
callback is empty
*/