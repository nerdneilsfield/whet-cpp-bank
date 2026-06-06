---
qid: cpp-iv-smart-001
type: short
kp: [cpp-interview]
difficulty: medium
tags: [腾讯, 字节跳动]
rubric:
  - 控制块（control block）的内存布局：强引用计数、弱引用计数、删除器、分配器
  - shared_ptr 内部含两个指针：裸指针 + 控制块指针
  - 强引用计数归零触发对象析构，弱引用计数归零才释放控制块本身
  - 引用计数使用原子操作（std::atomic）保证并发安全
  - make_shared 将对象与控制块合并为一次内存分配
---

# Q: `shared_ptr` 的引用计数如何实现？控制块（control block）里有什么？

## Explanation

`shared_ptr` 并不在指针对象本身内部存储引用计数，而是维护一个**堆上的控制块（control block）**，`shared_ptr` 实例内部持有两个指针：

```
┌──────────────────────────────┐
│  shared_ptr<T>               │
│  ┌──────────────┐            │
│  │ T* ptr       │  → 指向被管理对象
│  │ ControlBlock*│  → 指向控制块
│  └──────────────┘            │
└──────────────────────────────┘

┌──────────────────────────────────────┐
│  ControlBlock                        │
│  ┌──────────────────────────────┐    │
│  │ atomic<long> use_count   (强) │    │
│  │ atomic<long> weak_count  (弱) │    │
│  │ Deleter      deleter         │    │
│  │ Allocator    allocator       │    │
│  └──────────────────────────────┘    │
└──────────────────────────────────────┘
```

**控制块包含的字段：**

| 字段 | 说明 |
|------|------|
| `use_count`（强引用计数） | 当前有多少个 `shared_ptr` 共享该对象 |
| `weak_count`（弱引用计数） | 当前有多少个 `weak_ptr` + 1（加 1 是为了让控制块在 `weak_ptr` 存在时不被提前销毁） |
| `Deleter` | 自定义删除器，默认 `delete` |
| `Allocator` | 用于分配/释放控制块自身的内存 |

**生命周期逻辑：**

```cpp
// 拷贝构造：强引用计数 +1
shared_ptr<T> p2 = p1;  // use_count: 1 → 2

// 析构：强引用计数 -1
{
    shared_ptr<T> p3 = p1;
}   // use_count: 2 → 1，对象未释放

// 最后一个 shared_ptr 析构：
// use_count → 0 → 调用 deleter 销毁被管理对象
// weak_count 不为 0 时，控制块依然存活
// weak_count → 0 时，控制块才被释放（deallocate）
```

**原子操作保证引用计数线程安全：**

```cpp
// 伪代码，实际在 <memory> 实现中
void _Decref() noexcept {
    if (--_Uses == 0) {       // atomic fetch_sub
        _Destroy();           // 销毁对象
        if (--_Weaks == 0)    // atomic fetch_sub
            _Delete_this();   // 释放控制块
    }
}
```

**关键结论：**
- 控制块是唯一的，所有共享同一对象的 `shared_ptr` 都指向同一个控制块。
- `use_count()` 调用返回的是原子读，但不能用于同步（值在你读到后可能立刻变化）。
- `make_shared<T>()` 将对象本身与控制块合并在一次 `new` 中分配，减少一次堆分配，同时提升 cache locality。
