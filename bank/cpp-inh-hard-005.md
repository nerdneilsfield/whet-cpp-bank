---
qid: cpp-inh-hard-005
type: single
kp: [cpp-inheritance]
difficulty: hard
answer_key: D
---

设计一个不打算被多态使用的基类：

```cpp
struct NonPoly {
    ~NonPoly() = default;         // 非虚
    void doSomething();
};

struct Child : NonPoly {
    ~Child() { /* releases resource */ }
};

NonPoly* p = new Child{};
delete p;                          // ①
```

关于 ① 处行为，下列说法正确的是？

A. C++17 起编译器要求基类必须有虚析构，本代码编译失败
B. `delete p` 调用 `NonPoly::~NonPoly()` 后调用全局 `operator delete`，由于子对象大小相同所以安全
C. `Child` 的析构未被调用，但内存释放正确，因此仅资源泄漏，不构成未定义行为
D. 通过基类指针 `delete` 派生类对象时，若基类无虚析构则行为未定义（除非派生类无需额外清理且大小一致）；本例中 `Child` 析构未被调用，且行为未定义

## Explanation

C++ 标准明确：通过基类指针 `delete` 一个**多态使用**的派生类对象，若基类析构非虚，则行为未定义。这是因为不仅 `Child` 的析构不会运行（资源泄漏），还可能在底层 `operator delete` 中传入错误的大小（若子对象类型与最派生类型大小不同，库可能崩溃）。即使两者大小相同，标准也直接定义为 UB——不能依赖"看起来工作了"。因此对任何打算多态使用的基类，应使析构虚化；若**确实**不打算多态使用，则应设为 `protected` 非虚析构以从语法上阻止 `delete p` 这种调用。
