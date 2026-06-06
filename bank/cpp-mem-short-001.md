---
qid: cpp-mem-short-001
type: short
kp: [cpp-memory-mgmt]
difficulty: medium
rubric:
  - 明确指出 RAII 全称（Resource Acquisition Is Initialization）
  - 解释通过构造函数获取资源、析构函数释放资源的原则
  - 至少给一个具体例子（lock_guard / unique_ptr / fstream）
  - 提到异常安全或栈展开保障资源释放
---
请解释 C++ 中的 RAII 原则，以及它如何保证资源不泄漏。

---

**参考答案：**

RAII 全称 Resource Acquisition Is Initialization，核心思想是将资源生命周期绑定到对象生命周期：构造函数获取资源（内存、文件句柄、锁等），析构函数负责释放。由于 C++ 保证局部对象在作用域结束时一定调用析构函数（即使发生异常导致栈展开），资源就不会泄漏。典型例子有 `std::lock_guard` 在构造时加锁、析构时解锁，`std::unique_ptr` 在析构时 `delete`，`std::fstream` 在析构时关闭文件。这使得即使中途抛出异常，资源也能安全释放，因此 RAII 是 C++ 异常安全编程的基石。

## Explanation

RAII 是把资源生命周期绑定到对象生命周期：构造函数获取资源，析构函数释放资源。局部对象离开作用域时会自动析构，异常栈展开时也一样，因此资源释放路径不会依赖手写的每个 `return` 或 `catch`。常见误区是只想到内存；RAII 同样适用于锁、文件、socket 等资源。
