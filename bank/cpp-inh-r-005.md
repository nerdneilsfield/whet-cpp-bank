---
qid: cpp-inh-r-005
type: single
kp: [cpp-inheritance]
difficulty: easy
answer_key: "D"
---

## 题目

阅读以下代码，程序输出是什么？

```cpp
#include <iostream>

class Base {
public:
    void foo(int x)    { std::cout << "Base::foo(int) " << x << std::endl; }
    void foo(double x) { std::cout << "Base::foo(double) " << x << std::endl; }
};

class Derived : public Base {
public:
    using Base::foo;              // 将 Base 的所有 foo 引入作用域
    void foo(int x) { std::cout << "Derived::foo(int) " << x << std::endl; }
};

int main() {
    Derived d;
    d.foo(1);       // (1)
    d.foo(1.5);     // (2)
}
```

A. 两次都输出 `Derived::foo(int) ...`
B. (1) 输出 `Base::foo(int) 1`，(2) 输出 `Derived::foo(int) 1`
C. 编译错误：`foo` 有歧义
D. (1) 输出 `Derived::foo(int) 1`，(2) 输出 `Base::foo(double) 1.5`

## 解析

`using Base::foo` 将 `Base` 的两个 `foo` 重载引入 `Derived` 的作用域，与 `Derived::foo(int)` 共同形成重载集。(1) `d.foo(1)` 精确匹配 `Derived::foo(int)`；(2) `d.foo(1.5)` 精确匹配 `Base::foo(double)`，因为 `Derived` 没有 `foo(double)` 重载。若没有 `using` 声明，`Base::foo` 会被隐藏，(2) 将转换为 `int` 调用 `Derived::foo(int)`。
