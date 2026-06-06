---
qid: cpp-class-hard-001
type: single
kp: [cpp-classes]
difficulty: hard
answer_key: B
---

关于空基类优化（EBO），以下说法正确的是？

```cpp
struct Empty {};

struct Derived : Empty {
    int x;
};

struct Composed {
    Empty e;
    int x;
};
```

A. `sizeof(Derived) == sizeof(Composed)` 恒成立，EBO 只是一种编译优化，标准不强制
B. C++20 标准保证 `Derived` 的 EBO 生效（`sizeof(Derived) == sizeof(int)`），而 `Composed` 中成员 `e` 占据至少 1 字节；多个相同空基类仍会占用不同地址导致空间浪费
C. EBO 对模板参数为空类时无效，因为模板参数不能用于继承
D. 空基类大小必定为 0，因此 `Composed` 也能享有与 `Derived` 相同的压缩效果

## 解析

标准要求最派生对象内同一类型的子对象地址互不相同，因此成员式空对象必占 ≥1 字节（填充满足对齐）。但**基类子对象**可不受此限——即允许编译器不为空基类分配任何空间（但空基类自身仍有非零大小以保持指针唯一性，EBO 让基类与派生类首个子对象共享起始地址）。`Derived` 因此大小仅 `sizeof(int)`。这一保证对标准布局类型事关重大，且被广泛应用于 `std::tuple`、`std::compressed_pair` 等标准库实现。注意：若多个空基类类型相同，它们不共享同一地址，仍会占用空间（已提议但未标准化）。C 错误：模板继承正好是 EBO 最广泛的应用场景。