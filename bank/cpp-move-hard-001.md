---
qid: cpp-move-hard-001
type: single
kp: [cpp-move-semantics]
difficulty: hard
answer_key: C
---

以下哪项正确解释了 `noexcept` 移动构造函数对 `std::vector` 重分配行为的影响？

```cpp
struct Movable {
    Movable(Movable&&) noexcept;
};

struct MaybeThrow {
    MaybeThrow(MaybeThrow&&);
};
```

A. `vector` 重分配时对每个元素调用移动构造；`MaybeThrow` 的移动若不标记 `noexcept`，编译器会用拷贝构造回退以避免异常不安全，但实际仍可能自动推断为 `noexcept`
B. `noexcept` 使 `vector` 在重分配时使用 `memcpy`，速度更快
C. C++ 标准规定：`vector` 重分配时，若元素类型的移动构造不是 `noexcept`，则改用拷贝构造来提供**强异常安全**保证——一旦中途抛异常，已移动的元素无法恢复到原位置
D. `noexcept` 不影响 `vector` 行为，仅影响类型特性，移动异常由调用方捕获

## Explanation

关键在**强异常安全保证**：`vector<T>::reserve`/`push_back` 需要保证如果操作中抛异常，容器必须保持原始状态不变。若移动构造是 `non-noexcept`，移动过程中抛异常会导致部分元素已被移动（原位置为空或已析构），无法回滚。因此 `std::vector` 在重分配时，通过 `std::move_if_noexcept` 选择：如果移动是 `noexcept`，调用移动构造；否则调用拷贝构造（拷贝抛异常不会破坏原数据）。`MaybeThrow` 的真实异常行为可能比声明的 noexcept 更复杂，但标准只看声明——没标记 `noexcept` 就按 `non-noexcept` 处理。B 错：用拷贝而非 `memcpy`；A 不准确：标准不自动推断。
