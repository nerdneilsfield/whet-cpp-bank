---
qid: cpp-iv-smart-005
type: short
kp: [cpp-interview]
difficulty: hard
tags: [腾讯, Google]
rubric:
  - 引用计数操作（增减）是原子的，对多线程安全
  - 同一个 shared_ptr 实例被多线程同时读写不安全（ptr 和控制块两个字段非原子更新）
  - 被管理的对象本身没有任何线程安全保证
  - 正确做法：每个线程持有独立的 shared_ptr 拷贝，共享只读；写操作需额外同步
  - std::atomic<shared_ptr<T>>（C++20）提供真正的原子 shared_ptr
---

# Q: `shared_ptr` 是线程安全的吗？引用计数本身 vs 管理的对象？

## Explanation

`shared_ptr` 的线程安全性分三个层次，必须分开讨论：

### 层次一：引用计数操作——线程安全

控制块中的 `use_count` 和 `weak_count` 使用 `std::atomic` 实现，增减操作在多线程下是安全的：

```cpp
// 多个线程各自持有同一对象的 shared_ptr 拷贝，析构时安全
auto sp = std::make_shared<int>(42);

std::thread t1([sp]{ /* 拷贝构造，use_count++ 原子 */ });
std::thread t2([sp]{ /* 析构，use_count-- 原子 */ });
// OK：引用计数不会竞态损坏
```

### 层次二：同一个 shared_ptr 实例——不安全

`shared_ptr` 对象本身包含**两个字段**（裸指针 + 控制块指针），对同一个 `shared_ptr` 实例的并发读写不是原子的：

```cpp
auto sp = std::make_shared<int>(42);

// 危险！两线程同时修改同一个 sp 实例
std::thread t1([&sp]{ sp = std::make_shared<int>(1); }); // 写
std::thread t2([&sp]{ auto p = sp; });                   // 读

// t1 修改 sp.ptr_ 和 sp.ctrl_ 是两步，t2 可能读到半更新状态
// → 数据竞争，UB
```

**正确做法：** 每个线程使用独立的 `shared_ptr` 拷贝（按值传递），只有引用计数变化，不共享 `shared_ptr` 实例本身。

```cpp
// 安全：各线程有自己的 shared_ptr 副本
std::thread t1([sp]{ auto local = sp; /* 只增/减引用计数 */ });
std::thread t2([sp]{ auto local = sp; });
```

### 层次三：被管理的对象——完全不安全

`shared_ptr` 对管理的对象没有提供任何同步，访问 `*sp` 与访问裸指针无异：

```cpp
auto sp = std::make_shared<std::vector<int>>();

std::thread t1([sp]{ sp->push_back(1); });   // 写
std::thread t2([sp]{ sp->push_back(2); });   // 写
// 数据竞争！需要外部互斥锁保护
```

### 汇总表

| 操作 | 线程安全？ |
|------|-----------|
| 多线程各持一份 `shared_ptr` 拷贝，并发析构 | ✅ 安全（原子引用计数） |
| 多线程并发读同一个 `shared_ptr` 实例 | ✅ 安全 |
| 多线程并发读写同一个 `shared_ptr` 实例 | ❌ 不安全，需互斥锁 |
| 多线程并发读写 `*sp`（被管理对象） | ❌ 不安全，需外部同步 |

### C++20：`std::atomic<std::shared_ptr<T>>`

```cpp
#include <atomic>
std::atomic<std::shared_ptr<int>> asp = std::make_shared<int>(0);

// 真正的原子替换，无数据竞争
asp.store(std::make_shared<int>(1));
auto copy = asp.load();
```

C++20 之前可用 `std::atomic_load` / `std::atomic_store` 全局函数（已弃用但有效）。
