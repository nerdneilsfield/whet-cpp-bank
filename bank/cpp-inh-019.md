---
qid: cpp-inh-019
type: multi
kp: [cpp-inheritance]
difficulty: easy
answer_key: [A, C, D]
---

以下代码中，哪些语句能编译通过？

```cpp
struct Base {
    void foo(int x) { }
    void foo(double x) { }
};
struct Derived : public Base {
    void foo(int x) { }       // 隐藏基类所有 foo
    using Base::foo;          // 引入基类 foo
};

Derived d;
```

A. `d.foo(1);`          // 调用 Derived::foo(int)
B. `d.Base::foo();`     // 不带参数调用
C. `d.foo(1.0);`        // 通过 using 引入的 Base::foo(double)
D. `d.Base::foo(1.0);`  // 显式限定调用
