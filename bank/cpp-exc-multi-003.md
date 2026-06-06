---
qid: cpp-exc-multi-003
type: multi
kp: [cpp-exceptions]
difficulty: medium
answer_key: [A, B, C]
---
以下操作中，**哪些可能抛出异常**？（多选）

A. `new T()`（默认）可能抛 `std::bad_alloc`。
B. `dynamic_cast<T&>(ref)` 转换失败时抛 `std::bad_cast`。
C. `std::vector::at(i)` 越界访问时抛 `std::out_of_range`。
D. `delete p`（默认）会抛 `std::bad_alloc`。

---

**解析：**

A 正确：内存分配失败默认抛 `bad_alloc`，除非使用 `std::nothrow`。
B 正确：引用形式的 `dynamic_cast` 失败抛 `bad_cast`。
C 正确：`at()` 越界一定抛异常。
D 错误：`delete` 调用析构和释放内存，标准要求 `operator delete` 是 `noexcept` 的（析构函数也应 `noexcept`）。