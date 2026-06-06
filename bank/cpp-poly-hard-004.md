---
qid: cpp-poly-hard-004
type: single
kp: [cpp-polymorphism]
difficulty: hard
answer_key: B
---

考虑以下代码：

```cpp
struct Base {
    virtual void f(int)    { /* ... */ }
    virtual void f(double) { /* ... */ }
};

struct Derived : Base {
    void f(int) override { /* ... */ }
};

Derived d;
d.f(3.14);  // ①
```

① 处的调用解析为？

A. `Base::f(double)`，因为 `Derived` 没重写它
B. `Derived::f(int)`，参数从 `double` 截断为 `int`；`Derived` 中的 `f(int)` 隐藏了基类所有同名 `f` 重载
C. 编译错误，`f(double)` 无匹配
D. 编译错误，`override` 关键字要求覆盖所有同名虚函数

## 解析

C++ 的名字查找在派生类作用域找到名字 `f` 后**立即停止**——它不会再到基类继续找重载。`Derived::f(int)` 隐藏了 `Base::f(double)` 和 `Base::f(int)`。因此 `d.f(3.14)` 只能匹配 `Derived::f(int)`，`double` 隐式转 `int`（带精度丢失警告），调用成功。要把基类的其他重载带回来，需在 `Derived` 中加 `using Base::f;`。这与覆盖（override）是两个独立机制：override 仅检查"是否真正覆盖了基类某虚函数"，并不要求把所有同名重载都覆盖。常见陷阱，写库时尤需注意。