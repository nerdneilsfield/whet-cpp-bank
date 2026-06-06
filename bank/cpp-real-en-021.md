---
qid: cpp-real-en-021
type: single
kp: [cpp-classes, cpp-memory-mgmt]
primary_kp: cpp-classes
difficulty: easy
answer_key: D
tags: [interview-real, interviewbit]
---
什么是 RAII（Resource Acquisition Is Initialization）原则？为什么它被认为是 C++ 中的最佳实践？

A. RAII 要求在程序启动时一次性申请所有需要的资源
B. RAII 是指在构造函数中延迟初始化，在析构函数中不做清理
C. RAII 禁止在构造函数中抛出异常
D. RAII 将资源的生命周期与对象的生命周期绑定（构造时获取、析构时释放），确保资源在异常或提前返回时也能被正确释放

---

**解析：**

RAII（资源获取即初始化）是 C++ 的核心设计范式：
- 资源（内存、文件句柄、互斥锁、数据库连接等）在对象构造函数中获取。
- 资源在对象析构函数中释放。
- 由于 C++ 保证局部对象的析构函数在离开作用域时（包括异常栈展开时）被自动调用，资源释放得到自动保证。

优点：异常安全、无资源泄漏、代码简洁（不用手动配对 `new`/`delete` 或 `lock`/`unlock`）。典型应用：`std::unique_ptr`、`std::lock_guard`、`std::ifstream` 等均基于 RAII 设计。

**来源：** InterviewBit "C++ Interview Questions" — RAII