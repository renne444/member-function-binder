# Member Function Binder

## 背景

在老旧的库中经常有需要传入函数指针的接口，因此这个接口往往需要传入一个全局函数。但定义过多的全局函数并不符合C++的编码规范，是比较差的实现。因此，我写了两个方法，专门用于绑定全局函数和成员函数。

## 原理

它的根本原理是利用了模板展开时，静态变量也会被展开多份的特点。制作了一系列由全局函数触发，然后调用成员函数的观察者。

当我们注册一个参数为全局函数指针的函数，我们不能用成员函数的根本原因在于成员函数需要传入this或实例指针。我利用了模板展开时，静态变量会展开成多份的特点，能针对每个实例展开多一个新的成员函数。

MemberFunctionBinder类，能针对每种不同的函数参数类型，映射到注册的function类型的函数。这个function函数可以利用bind函数传入一个成员函数；

MultipleMemberFunctionBinder类，则针对MemberFunctionBinder类无法处理的多个相同类型的function到binder，增加了一个int的模板用于区分不同的binder，从而实现相同的函数参数展开成不同的模板类，生成不同的静态变量。

## 用法

MemberFunctionBinder应该传入函数参数为模板，比如对于cb1函数，则应该传入int为参数（参数个数不限制）。在执行注册后，执行回调函数则能调用到cb函数。

函数根据参数类型区分，所以当用到unsigned类型为模板时，由于之前还没在unsigned类型上注册过函数。所以会输出callback is empty

```cpp
void cb1(int v) { cout << "cb1: " << v << endl; }
void cb2(double v) { cout << "cb2: " << v << endl; }

int main() {
  // sample for single member function binder
  MemberFunctionBinder<int>::RegisterCb(make_shared<function<void(int)>>(cb1));
  MemberFunctionBinder<int>::CallbackFunc(10);
  MemberFunctionBinder<double>::RegisterCb(
      make_shared<function<void(double)>>(cb2));
  MemberFunctionBinder<double>::CallbackFunc(20.5);
  MemberFunctionBinder<unsigned>::CallbackFunc(1); // print "callback is empty"
}
```

MultipleMemberFunctionBinder针对的是有多个相同类型函数的注册的，能加入一个id区分不同的注册函数。注册不同的id可以指向不同的全局函数

```c++
// sample for multiple member function binder
MultipleMemberFunctionBinder<1, int>::RegisterCb(
    make_shared<function<void(int)>>(cb1));
MultipleMemberFunctionBinder<1, int>::CallbackFunc(10);

MultipleMemberFunctionBinder<2, int>::CallbackFunc(30);
// print "callback is empty" because the binder with binding number 2
// have not been registered
```
