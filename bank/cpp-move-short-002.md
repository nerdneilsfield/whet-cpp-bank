---
qid: cpp-move-short-002
type: short
kp: [cpp-move-semantics]
difficulty: medium
rubric:
  - 指出 std::vector 等容器在扩容或拷贝时会判断元素类型的 move 是否 noexcept
  - 解释若 move 不是 noexcept，容器会退化为拷贝以保证强异常安全
  - 给出建议：自定义类型的移动构造/赋值应声明为 noexcept
  - 提到对性能影响（拷贝 vs 移动差距可能巨大）
---
请解释为什么自定义类型的移动构造和移动赋值通常应声明为 `noexcept`。

---

**参考答案：**

标准库容器（典型如 `std::vector` 在扩容时）在选择移动或拷贝元素时，会通过 `std::is_nothrow_move_constructible` 等 trait 判断元素的 move 是否 `noexcept`。若不是 `noexcept`，为了保证强异常安全（搬迁中途异常仍能回滚），容器会退化为拷贝，导致性能大幅下降。因此，自定义类的移动构造和移动赋值通常应标注 `noexcept`，让容器、`std::swap` 等场景能够采用更快的 move 路径。