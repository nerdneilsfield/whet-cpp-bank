---
qid: cpp-mem-multi-004
type: multi
kp: [cpp-memory-mgmt]
difficulty: medium
answer_key: [A, B, D]
---
关于 RAII（Resource Acquisition Is Initialization），**哪些说法是正确的**？（多选）

A. RAII 利用对象生命周期来管理资源，析构函数负责释放。
B. RAII 在异常抛出时仍能正确释放资源（栈展开时局部对象会被析构）。
C. RAII 要求资源类型必须是堆分配的。
D. `std::lock_guard` 是 RAII 风格的典型例子。

---

**解析：**

A 正确：RAII 的核心思想是用对象生命周期绑定资源生命周期。
B 正确：异常安全的关键之一，栈展开会析构所有完成构造的局部对象。
C 错误：RAII 与资源是否堆分配无关，可管理文件句柄、锁、网络连接等任意资源。
D 正确：`lock_guard` 构造时加锁，析构时解锁，是经典 RAII 案例。

## 解析

正确答案是 A、B、D。RAII 用对象析构释放资源，异常栈展开时也会析构已构造的局部对象，因此有利于异常安全；`std::lock_guard` 是构造加锁、析构解锁的典型例子。C 错在 RAII 可管理任意资源，不限于堆内存。 这类题的关键是区分语法形式、对象生命周期和所有权语义：语法看似相近时，应先判断谁拥有资源、表达式值类别是什么，以及标准是否保证该行为；不要根据实现习惯或表面写法推断答案。
