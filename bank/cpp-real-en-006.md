---
qid: cpp-real-en-006
type: multi
kp: [cpp-casting, cpp-types]
primary_kp: cpp-casting
difficulty: medium
answer_key: ["A", "C", "D"]
tags: [interview-real, interviewbit]
---
C++ 四种类型转换运算符中，以下哪些说法是正确的？（多选）

A. `static_cast` 用于编译期类型转换，如 `int` 转 `float`、`void*` 转具体指针
B. `dynamic_cast` 可用于任意两个不相关类型之间的转换
C. `const_cast` 只能用于移除或添加 `const` / `volatile` 限定符
D. `reinterpret_cast` 最危险，用于任意指针/引用之间按位重新解释，不保证可移植性
E. `dynamic_cast` 如果失败，对指针返回 `nullptr`，对引用抛出 `std::bad_cast` 异常

---

**解析：**

四种转换各有用途：
- **`static_cast`**：编译期安全检查的类型转换。适用于数值类型间转换、派生类→基类（向上转型、向下转型不检查）。
- **`dynamic_cast`**：运行时安全检查，只能用于多态类型（有虚函数的类）。向下转型时检查类型信息，失败返回 `nullptr`（指针）或抛 `std::bad_cast`（引用）。
- **`const_cast`**：只修改 `const` / `volatile` 限定。用于调用 old-style API 等少数场景。修改原本定义为 `const` 的对象是 UB。
- **`reinterpret_cast`**：按位重新解释内存内容。最危险的转换，移植性差，通常用于与硬件交互（如 memory-mapped I/O）。

**来源：** InterviewBit "C++ Interview Questions" — Type Casting