---
qid: cpp-move-multi-002
type: multi
kp: [cpp-move-semantics]
difficulty: medium
answer_key: [A, B]
---
关于 `std::move` 的正确使用，**哪些说法是正确的**？（多选）

A. `std::move` 是一个无运行时开销的类型转换（实质是 `static_cast`）。
B. 对 `const` 对象使用 `std::move` 不会触发移动构造，仍是拷贝。
C. 在 `return std::move(local);` 中显式 `std::move` 总能提升性能。
D. `std::move(x)` 后，`x` 不再可用，访问就是未定义行为。

---

**解析：**

A 正确：`std::move` 本质就是 `static_cast<T&&>`，没有运行时代价。
B 正确：`std::move(const T&)` 得到 `const T&&`，匹配不到非 const 的移动构造，退化为拷贝。
C 错误：返回局部变量时显式 `std::move` 反而会阻止 NRVO，往往降低性能。
D 错误：被移后对象处于「合法但未指定」状态，仍可赋值、析构，并非未定义行为。