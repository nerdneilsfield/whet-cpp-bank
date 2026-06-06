---
qid: cpp-class-med-010
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: B
---

下列代码 `d.f(3.14);` 的行为是？

```cpp
struct Base {
    void f(int)    { std::puts("Base::f(int)"); }
    void f(double) { std::puts("Base::f(double)"); }
};

struct Derived : Base {
    using Base::f;        // (★)
    void f(const char*)   { std::puts("Derived::f(const char*)"); }
};

Derived d;
d.f(3.14);
```

A. 编译错误：`Derived` 中的 `f` 隐藏了基类所有 `f`
B. 输出 `Base::f(double)`
C. 输出 `Derived::f(const char*)`（隐式转换 `3.14` → 字符串）
D. 输出 `Base::f(int)`（隐式窄化）

---

**解析：**

派生类中定义同名函数会**隐藏**（name hiding）基类中所有同名重载——无论参数列表是否匹配。`using Base::f;` 的作用就是把基类那一组 `f` 重新引入派生类作用域，使其与派生类自己的 `f(const char*)` 共同参与重载决议。

去掉 `using` 后只剩 `Derived::f(const char*)`，`d.f(3.14)` 因 `double` 无法转换到 `const char*` 而编译错误。加上 `using` 后，重载集合包含 `f(int)`、`f(double)`、`f(const char*)` 三个候选；`3.14` 是 `double`，精确匹配 `Base::f(double)`，输出对应结果。

这是工程中"派生类只想新增一个重载、又不想丢失基类已有重载"时的标准做法。
