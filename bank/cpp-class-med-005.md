---
qid: cpp-class-med-005
type: single
kp: [cpp-classes]
difficulty: medium
answer_key: A
---

下列利用 `mutable` 做惰性缓存的代码，关于其线程安全性，最准确的描述是？

```cpp
class Matrix {
    std::vector<double> data_;
    mutable double      cached_norm_ = -1;
public:
    double norm() const {
        if (cached_norm_ < 0)
            cached_norm_ = compute_norm();   // 修改 mutable 成员
        return cached_norm_;
    }
};
```

A. 单线程下合法；多线程同时调用 `norm()` 是数据竞争（UB），需自行加锁或用原子量
B. 因为 `mutable` 已隐含 `atomic`，多线程安全
C. 因为 `norm()` 是 `const`，标准保证多线程下安全
D. 编译错误，`const` 函数中不能修改任何成员

---

**解析：**

`mutable` 仅取消 `const` 对该成员的写保护，让缓存写入在语法上通过；它**不提供任何同步语义**，更不会自动变成 `std::atomic`。

C++11 后标准库对"标准类型的 `const` 成员函数"给出弱保证：被记为 const 的操作应当是逻辑线程安全的（[res.on.data.races]）。但这只是对**标准库实现**的契约，用户自己写的 `const` 函数若内部通过 `mutable` 改了数据，就由用户负责同步。本例两个线程都可能同时进入 `if` 并写 `cached_norm_`，构成数据竞争，是未定义行为。

正确做法：把 `cached_norm_` 改为 `std::atomic<double>` 或 `std::optional` + `std::mutex`，或使用 `std::call_once`。

## Explanation

正确答案为 A，因为“单线程下合法；多线程同时调用 `norm()` 是数据竞争（UB），需自行加锁或用原子量”符合题干所问的 C++ 规则或代码执行结果。B、C、D 项分别混淆了相近概念、错误语法或不会发生的执行路径。常见误区是凭直觉看关键字，而没有按标准规则和代码顺序逐步判断。类与对象题要区分默认访问权限、对象生命周期、静态成员、const 成员函数和初始化规则。
