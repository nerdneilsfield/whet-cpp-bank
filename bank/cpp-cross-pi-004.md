---
qid: cpp-cross-pi-004
type: single
kp: [cpp-polymorphism, cpp-inheritance]
difficulty: easy
answer_key: B
---

以下代码运行时会发生什么？

```cpp
#include <iostream>

struct Base {
    ~Base() { std::cout << "~Base\n"; }     // 非 virtual
};

struct Derived : Base {
    int* buf;
    Derived() : buf(new int[100]) {}
    ~Derived() { delete[] buf; std::cout << "~Derived\n"; }
};

int main() {
    Base* p = new Derived();
    delete p;   // 通过 Base* 删除
    return 0;
}
```

A. 输出 `~Derived` 然后 `~Base`，无问题  
B. 只输出 `~Base`，`~Derived` 未调用，buf 泄漏（未定义行为）  
C. 编译错误  
D. 输出 `~Base` 然后 `~Derived`

<!--
Base 的析构函数不是 virtual。
delete p（Base*）时，静态绑定到 Base::~Base()，不会调用 Derived::~Derived()。
buf 指向的堆内存未被释放 → 资源泄漏。
这是未定义行为（UB）；最常见的表现是只打印 ~Base。
修复：将 Base 的析构函数声明为 virtual。
-->

## 解析

B 正确：通过 `Base*` 删除实际为 `Derived` 的对象，但 `Base` 析构函数不是 virtual，标准上是未定义行为。常见表现是只调用 `~Base`，`~Derived` 不执行，`buf` 泄漏。关键误区是只看输出而忽略 UB；正确设计是给多态基类虚析构函数。
