---
qid: cpp-real-nk-011
type: single
kp: [cpp-memory-mgmt]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: C
tags: [interview-real, nowcoder]
---

```cpp
auto p1 = std::make_shared<int>(42);
auto p2 = std::shared_ptr<int>(new int(42));
```

关于这两种构造方式，**错误**的是：

A. `make_shared` 只需要一次内存分配（对象 + 控制块一起），new + shared_ptr 需要两次分配
B. `make_shared` 创建的对象内存可能直到 `weak_ptr` 也清零才会被释放
C. `make_shared` 可以支持自定义删除器（custom deleter）
D. `make_shared` 不能用于 `private` 构造函数的类

---

**解析：**

A **对**：`make_shared` 把控制块和被管理对象放在**同一块内存**中，一次 `new`。`new + shared_ptr<T>(ptr)` 是先 new 对象，再 new 控制块。

B **对**：因为对象和控制块同块内存，必须等控制块被所有 weak_ptr 释放才能释放。如果对象很大且 weak_ptr 长期存在，会延迟对象内存释放。

C **错**：`make_shared` 不支持自定义删除器，因为它需要使用默认 delete。如要自定义删除器只能用 `shared_ptr<T>(ptr, deleter)`。

D **对**：`make_shared` 不是友元，无法访问 private 构造函数。常见技巧是用 PassKey idiom 或继承 + `enable_shared_from_this`。

**来源：** 卡码笔记 C++ 智能指针专题 / Effective Modern C++ Item 21