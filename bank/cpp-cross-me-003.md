---
qid: cpp-cross-me-003
type: single
kp: [cpp-memory-mgmt, cpp-exceptions]
difficulty: easy
answer_key: A
---

# 题目

下面两段代码，哪段**会发生内存泄漏**？

**版本 X（裸 new）**
```cpp
void bar() {
    int* p = new int(42);
    throw std::runtime_error("fail");
    delete p;   // 永远不会执行
}
```

**版本 Y（RAII）**
```cpp
void bar() {
    auto p = std::make_unique<int>(42);
    throw std::runtime_error("fail");
    // unique_ptr 析构自动 delete
}
```

A. 仅版本 X 泄漏

B. 仅版本 Y 泄漏

C. 两者都泄漏

D. 两者都不泄漏

---

## Explanation

- **版本 X**：`new` 之后抛出异常，`delete p` 所在行永远不会被执行，堆内存泄漏。
- **版本 Y**：`unique_ptr` 是栈对象，栈展开时析构函数被调用，`delete` 自动执行，无泄漏。

选 **A**。这是 RAII 的核心价值：将资源释放绑定到对象生命周期，而非代码路径。
