---
qid: cpp-poly-multi-hard-004
type: multi
kp: [cpp-polymorphism]
difficulty: hard
answer_key: [A, B, D]
---
关于 C++11 的 `final` 关键字，以下说法正确的是哪些？

```cpp
struct Base { virtual void f(); };
struct Mid final : Base { void f() override; };       // (1)
struct Bad : Mid { };                                  // (2) ?
struct M2 : Base { void f() final; };                  // (3)
struct M3 : M2 { void f(); };                          // (4) ?
```

A. (1) 用 `final` 修饰类禁止继承；(2) 派生 `Mid` 会编译失败。
B. (3) 用 `final` 修饰虚函数禁止派生类再覆盖该函数；(4) 中 `M3::f()` 试图覆盖 `M2::f()` 会编译失败。
C. `final` 仅是文档性提示，编译器不会因此进行去虚化（devirtualization）等优化。
D. 编译器可以基于 `final` 进行去虚化优化：通过 `Mid*` 调用 `f()` 时，由于 `Mid` 已 final 且 `f` 已确定为 `Mid::f`，可直接静态调用而非虚分派。

---

**解析：**

A 正确：`class Mid final` 禁止任何派生，`struct Bad : Mid` 编译失败，是 `final` 的两种用途之一。
B 正确：`void f() final;` 禁止派生类再覆盖；`M3::f()` 试图覆盖 final 函数会被编译器拒绝。注意 final 函数仍是 virtual。
C 错误：`final` 是给编译器的强约束信号，不只是文档性。现代编译器（GCC/Clang/MSVC）会利用 final 信息消除虚函数调用开销，进行去虚化优化。
D 正确：当对象的静态类型已知是 final 类，或调用的虚函数已被声明 final，编译器可以静态决议虚函数调用（devirtualization），避免 vtable 间接跳转，提升性能。这是 final 实际带来的优化收益。