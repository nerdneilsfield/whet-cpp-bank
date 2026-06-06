---
qid: cpp-scope-med-003
type: single
kp: [cpp-scope-linkage]
difficulty: medium
answer_key: A
---

名字隐藏（name hiding）在继承中的行为。以下代码输出是？

```cpp
#include <iostream>

struct Base {
    void f(int) { std::cout << "Base::f(int)\n"; }
    void f(double) { std::cout << "Base::f(double)\n"; }
};

struct Derived : Base {
    void f(double) { std::cout << "Derived::f(double)\n"; }
};

int main() {
    Derived d;
    d.f(42);
}
```

A. `Derived::f(double)`（int 被隐式转换到 double）
B. `Base::f(int)`（编译器选择最匹配的重载）
C. 编译失败，因为 `f(int)` 被隐藏后不存在
D. `Base::f(int)` 因为 int 比 double 更匹配

---

**解析：**

C++ 的名字查找规则：在 `Derived` 的作用域中先找到 `f`（名字 `f` 在派生类中找到了），**立即停止查找**，不再考虑 `Base` 的作用域。即使派生类中只有 `f(double)` 而参数是 `int`，也不会去基类中找 `f(int)` 更好的匹配。

因此结果：通过隐式转换 `int→double` 调用 `Derived::f(double)`。如果派生类中定义的是 `f(int)` 而传入 `double`，会发生截断；如果是 `f(double)` 传入 `int`，则隐式提升。

这个规则容易让新手意外：明明 Base 有更匹配的重载，却被隐藏了。解决方案是用 `using Base::f;` 将基类的重载引入派生类的作用域。