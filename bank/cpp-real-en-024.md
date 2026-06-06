---
qid: cpp-real-en-024
type: single
kp: [cpp-memory-mgmt, cpp-cpp11]
primary_kp: cpp-memory-mgmt
difficulty: medium
answer_key: B
tags: [interview-real, interviewbit]
---
关于 C++ 智能指针 `std::unique_ptr`、`std::shared_ptr` 和 `std::weak_ptr`，以下说法正确的是？

A. `std::unique_ptr` 允许多个指针共享同一对象
B. `std::shared_ptr` 使用引用计数管理生命周期，`std::weak_ptr` 通过弱引用打破循环引用
C. `std::weak_ptr` 可以直接解引用访问对象
D. `std::unique_ptr` 的拷贝和移动都是允许的

---

**解析：**

- **`std::unique_ptr`**：独占所有权，不可拷贝，只能移动。轻量级，无额外开销。应在大多数场景优先使用。
- **`std::shared_ptr`**：共享所有权，引用计数管理。可拷贝（递增计数），开销稍大（需要原子操作维护计数）。当最后一个 `shared_ptr` 销毁时释放对象。
- **`std::weak_ptr`**：弱引用，不增加引用计数。用于观察对象是否存活，解决 `shared_ptr` 循环引用导致的泄漏。需要通过 `lock()` 获取 `shared_ptr` 后才能访问对象（可能为空）。

```cpp
std::weak_ptr<int> wp = std::make_shared<int>(42);
if (auto sp = wp.lock()) {  // 检查对象是否仍存活
    std::cout << *sp;
}
```

**来源：** InterviewBit "C++ Interview Questions" — Smart Pointers