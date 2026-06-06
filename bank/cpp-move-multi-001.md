---
qid: cpp-move-multi-001
type: multi
kp: [cpp-move-semantics]
difficulty: medium
answer_key: [A, D]
---
关于移动操作何时被调用，**哪些说法是正确的**？（多选）

A. 返回局部变量（无 RVO）时可能触发移动而非拷贝。
B. 对所有类调用 `std::move(v)` 后，一定触发移动构造。
C. 按值返回时，移动操作只适用于有移动构造函数的类型。
D. 移动构造函数被 `noexcept` 声明的类，标准库容器在重新分配时会优先选择移动。

---

**解析：**

A 正确：C++11 后，返回局部对象时先尝试移动，再尝试拷贝。
B 错误：`std::move` 只是将值转成右值引用，实际是否移动取决于接收者的构造函数。
C 错误：即使无移动构造函数，按值返回会退化到拷贝（或 RVO）。
D 正确：`std::vector` 等容器在 `noexcept` 移动构造时选择移动而非拷贝。