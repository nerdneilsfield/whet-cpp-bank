---
qid: cpp-move-multi-004
type: multi
kp: [cpp-move-semantics]
difficulty: medium
answer_key: [A, B, D]
---
关于 `noexcept` 移动构造带来的好处，**哪些说法是正确的**？（多选）

A. `std::vector` 在扩容时若移动构造是 `noexcept`，使用移动而非拷贝。
B. `noexcept` 的移动构造有助于保证容器操作的强异常安全。
C. `noexcept(false)` 的移动构造在所有标准库中都不会被使用。
D. 自定义类型若希望被 STL 高效移动，应将移动构造声明为 `noexcept`。

---

**解析：**

A 正确：这是 `move_if_noexcept` 的典型用法。
B 正确：移动若可能抛异常，会破坏 vector 扩容的强异常保证，故标准库回退到拷贝。
C 错误：仍会被使用（如直接调用），只是某些容器操作会回退到拷贝。
D 正确：未声明 noexcept 的移动构造往往导致 STL 退化为拷贝，性能受损。