---
qid: cpp-lambda-med-003
type: single
kp: [cpp-lambdas]
difficulty: medium
answer_key: B
---
下列泛型 lambda（C++14）说法正确的是？

```cpp
auto add = [](auto a, auto b) { return a + b; };
```

A. `auto` 形参等价于运行时多态，每次调用动态分派
B. 编译器为每组不同的实参类型实例化一份 `operator()`，相当于模板
C. 必须在 C++17 之后才支持
D. 不能与 `std::function` 一起使用

---

**解析：**

C++14 的泛型 lambda 中，`auto` 形参语义等价于把 `operator()` 写成模板成员函数：每次以不同实参类型调用时，编译器实例化一份对应的 `operator()<T1, T2>`。是编译期机制，没有任何运行时分派开销，与 C++11 模板函数等价。它和 `std::function` 完全兼容——只要每次构造时类型固定即可。C++20 进一步引入 `[]<typename T>(T x)` 形式的显式模板形参 lambda。
