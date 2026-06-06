---
qid: cpp-real-ali-004
type: single
kp: [cpp-memory-mgmt, cpp-cpp11]
primary_kp: cpp-memory-mgmt
difficulty: hard
answer_key: D
tags: [interview-real, alibaba]
---
关于 `std::shared_ptr` 的引用计数实现，以下说法正确的是：

A. shared_ptr 的引用计数存储在堆上的独立对象中，与所指对象同一内存块
B. 引用计数是原子操作，因此 shared_ptr 的拷贝和析构在多线程下完全不需要加锁
C. make_shared 比直接 new 慢，因为它需要额外分配 control block
D. shared_ptr 的 control block 包含引用计数和 weak 计数，make_shared 将二者与对象分配在同一块内存中

---

**解析：**

选 D。shared_ptr 的 control block（控制块）包含：
- `ref_count`（引用计数）：追踪 shared_ptr 个数
- `weak_count`（弱引用计数）：追踪 weak_ptr 个数（不是 weak_ptr 的实际数量，而是扩展引用计数，用于控制 control block 自身何时释放）
- deleter、allocator 等（可选）

**make_shared 是一次分配**：`T* p = new T(args)` + `control_block* cb = new control_block` 是两次堆分配。`make_shared(args)` 将对象和 control block 分配在同一块内存中，**减少一次堆分配**。

A 错在"与所指对象同一内存块"——通常不是，因为对象本身和 control block 是分开的（除非 make_shared）。B 错在"完全不需要加锁"——引用计数是原子操作（通常是 atomic<int>），保证了 ref_count 的线程安全，但不保证所指对象本身的线程安全。C 错在 make_shared 比直接 new 快（少一次分配），而非慢。

注意 control block 的内存布局：

```
make_shared 的布局:
[  对象内存  | ref_count | weak_count | ... ]
            ↑            ↑
            同一块堆内存，一次分配

直接 new shared_ptr:
[  对象内存  ]  ← 一次分配
[ ref_count | weak_count | ... ]  ← 另一次分配
```

**来源：** 阿里 C++ 后端面试追问（参考：cppreference、Effective Modern C++）