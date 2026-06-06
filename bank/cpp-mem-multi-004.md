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
