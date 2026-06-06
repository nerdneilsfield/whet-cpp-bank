---
qid: cpp-move-hard-004
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: A
---

C++17 对 RVO 与隐式移动的强制规定，以下正确的是？

```cpp
struct S { S() = default; S(const S&); S(S&&); };

S make() {
    S x;
    return x;   // ①
}

S copy = S{S{S{}}}; // ②
```

A. ① 在 C++17 中保证为 NRVO（C++17 前要求编译器在没有重载决议选择移动时才允许，现在直接要求按移动或拷贝处理），若 `S` 有移动构造且 `noexcept` 不要求则移动。② 中多层 `S{}` 包裹产生纯右值临时对象，编译器必须通过"临时量实质化"（temporary materialization）在所有后续表达式的相同纯右值管线中消除中间临时，最终仅一次 `S()` 构造
B. ① 总是拷贝，因为 `x` 是左值名字
C. ② 需要 3 次构造和 2 次移动
D. ① 是未定义行为，因为 `return x` 是左值但期望右值

## Explanation

C++17 中，`return x;` 是**隐式移动**（implicit move）候选：先考虑移动构造，若不可用则回退拷贝。但 NRVO 是优化，不保证消除副本（编译器可拒绝）。② 则不同：C++17 对纯右值（prvalue）定义了"临时量实质化"（temporary materialization）——`S{S{S{}}}` 中第一层 `S{}` 产生纯右值，它不立即创建对象（不是临时对象！）。只有当你需要地址或绑定引用时，纯右值才实质化。这里的 `S{S{S{}}}` 实质上等价于 `S obj;` ——一次默认构造，零拷贝/移动——只要类型 `S` 的构造不必为纯右值管线引入拷贝（即 `S{}` → 构造函数的不是"已有的临时对象"而是直接构造最终对象的表达式）。这是 C++17 的"保证拷贝省略"。
