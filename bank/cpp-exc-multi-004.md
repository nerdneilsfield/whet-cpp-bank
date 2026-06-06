---
qid: cpp-exc-multi-004
type: multi
kp: [cpp-exceptions]
difficulty: medium
answer_key: [A, B, D]
---
关于 RAII 在异常安全中的角色，**哪些说法是正确的**？（多选）

A. RAII 保证栈展开时已构造对象会被析构，从而释放资源。
B. `std::lock_guard`、`std::unique_ptr` 等都是异常安全的 RAII 工具。
C. RAII 能自动避免所有资源泄漏，无论代码如何编写。
D. 应避免在析构函数中抛出异常，否则在栈展开时会调用 `std::terminate`。

---

**解析：**

A 正确：栈展开会析构所有完成构造的局部对象。
B 正确：标准库提供的典型 RAII 工具。
C 错误：仍需正确使用；裸 new/delete、绕过 RAII 仍可能泄漏。
D 正确：栈展开期间再抛异常会触发 `std::terminate`。