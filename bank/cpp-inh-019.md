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

## Explanation

本题正确答案是 A, C, D。本题考查继承中的访问控制、构造析构顺序、虚函数或多继承规则，关键是区分静态类型限制和运行期动态绑定。A 项正确：“d.foo(1); // 调用 Derived::foo(int)”符合题干要求；B 项错误：“d.Base::foo(); // 不带参数调用”与题干要求或 C++ 规则不符；C 项正确：“d.foo(1.0); // 通过 using 引入的 Base::foo(double)”符合题干要求；D 项正确：“d.Base::foo(1.0); // 显式限定调用”符合题干要求。多选题常见误区是漏选同时成立的规则，或把只在特定上下文成立的说法当成普遍规则。
