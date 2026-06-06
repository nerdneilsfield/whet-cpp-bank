---
qid: cpp-cross-pi-002
type: single
kp: [cpp-polymorphism, cpp-inheritance]
difficulty: easy
answer_key: A
---

以下代码的输出是什么？

```cpp
#include <iostream>

struct Base {
    void greet() { std::cout << "Base\n"; }
};

struct Derived : Base {
    void greet() { std::cout << "Derived\n"; }
};

int main() {
    Derived d;
    Base b = d;   // 对象切片
    b.greet();
    return 0;
}
```

A. Base  
B. Derived  
C. Base 然后 Derived  
D. 未定义行为

<!--
greet() 不是 virtual 函数，不存在动态分派。
`Base b = d` 发生对象切片：b 的静态类型是 Base，Derived 部分被截掉。
调用 b.greet() 使用静态绑定，执行 Base::greet()，输出 Base。
这是对象切片 + 非虚函数的经典陷阱。
-->

## 解析

A 正确：`Base b = d` 会发生对象切片，只保留 `Base` 子对象，`Derived` 部分被丢弃。`greet` 也不是虚函数，因此调用由静态类型 `Base` 决定，输出 `Base`。关键误区是把普通成员函数调用误认为多态分派。
