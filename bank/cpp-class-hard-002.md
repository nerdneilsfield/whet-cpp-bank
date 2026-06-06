---
qid: cpp-class-hard-002
type: single
kp: [cpp-classes]
difficulty: hard
answer_key: D
---

以下代码输出什么？

```cpp
#include <iostream>
struct Base {
    Base() { show(); }
    virtual void show() const { std::cout << "Base\n"; }
};

struct Derived : Base {
    Derived() : Base() { show(); }
    void show() const override { std::cout << "Derived\n"; }
};

int main() {
    Derived d;
}
```

A. `Base\nDerived\n`
B. `Derived\nDerived\n`
C. `Derived\nBase\n`
D. `Base\nDerived\nDerived`

## 解析

这是 C++ 面试经典陷阱的变体。`Derived` 构造时，先调用 `Base()`，此时 `Derived` 的 vptr 指向 `Base` 的虚表（`Derived` 本身的初始化尚未开始），因此虚函数 `show()` 调用的是基类版本——输出 `Base`。`Base()` 完成后，`Derived` 初始化其成员，接着执行 `Derived` 构造函数体中的 `show()`，此时 vptr 已指向 `Derived` 的虚表，故输出 `Derived`。`main` 中的 `Derived d;` 只触发一道构造序列，不会在构造函数体外额外调用一次。**注意**：本题的 `Derived::Derived()` 构造函数体中的 `show()` 是一个额外的显式调用，所以总计两次输出，而非通常所见的两阶段构造的"调用一次"。因此最终输出两条：`Base` 和 `Derived`。陷阱在于部分读者会忽略 `Derived()` 函数体内的 `show()`，从而误选 A。