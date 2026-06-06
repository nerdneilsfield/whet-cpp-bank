---
qid: cpp-iv-mem-008
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Meta, 阿里]
rubric:
  - 说清 operator new 与 malloc 的关系（默认实现调用 malloc 或等价系统调用）
  - 知道 operator new 可以在全局或类级别重载
  - 重载签名正确：`void* operator new(std::size_t)`，返回 void*
  - 理解为什么要重载（内存池、统计、对齐、调试追踪）
  - 加分：说明 operator new 与 operator delete 必须配对重载，以及 sized deallocation（C++14）
---

# `operator new` 和 `malloc` 的关系？如何重载 `operator new`？

## Explanation

### 默认实现关系

`operator new` 是 C++ 的内存分配函数，其**默认实现通常直接调用 `malloc`**（或等价的底层系统调用 `sbrk`/`mmap`），再在分配失败时抛出 `std::bad_alloc`。

```
new Foo  →  operator new(sizeof(Foo))  →  malloc(n)  →  brk/mmap
               调用构造函数 ↑
```

等价关系（概念上）：

```cpp
// 默认 operator new 的参考实现
void* operator new(std::size_t n) {
    void* p = std::malloc(n);
    if (!p) throw std::bad_alloc{};
    return p;
}

void operator delete(void* p) noexcept {
    std::free(p);
}
```

关键区别：

| | `operator new` | `malloc` |
|--|----------------|----------|
| 失败行为 | 抛 `std::bad_alloc` | 返回 `nullptr` |
| 可重载 | 是（全局/类级别） | 否 |
| 调用构造函数 | 不直接调用（`new` 表达式负责） | 不调用 |
| new_handler | 支持（`std::set_new_handler`） | 不支持 |

### 为什么要重载

- **内存池**：减少系统调用，降低碎片，提升速度。
- **内存统计/调试**：追踪分配次数、未释放内存。
- **自定义对齐**：超过 `alignof(max_align_t)` 的需求（C++17 前标准不处理过对齐）。
- **平台适配**：嵌入式系统替换分配策略。

### 全局重载

```cpp
#include <cstdlib>
#include <new>
#include <cstdio>

std::size_t g_allocated = 0;

// 全局重载：影响所有 new 表达式
void* operator new(std::size_t n) {
    g_allocated += n;
    void* p = std::malloc(n);
    if (!p) throw std::bad_alloc{};
    std::fprintf(stderr, "[alloc] %zu bytes @ %p (total %zu)\n",
                 n, p, g_allocated);
    return p;
}

void operator delete(void* p) noexcept {
    std::fprintf(stderr, "[free]  @ %p\n", p);
    std::free(p);
}

// C++14 sized deallocation（优化，编译器知道大小）
void operator delete(void* p, std::size_t n) noexcept {
    g_allocated -= n;
    std::free(p);
}
```

### 类级别重载（仅影响该类）

```cpp
class PoolObject {
public:
    static void* operator new(std::size_t n) {
        return MyPool::instance().allocate(n);
    }
    static void operator delete(void* p, std::size_t n) noexcept {
        MyPool::instance().deallocate(p, n);
    }

    // 数组形式也需单独重载
    static void* operator new[](std::size_t n) {
        return MyPool::instance().allocate(n);
    }
    static void operator delete[](void* p) noexcept {
        MyPool::instance().deallocate(p);
    }
};
```

### 重要约束

1. **`operator new` 和 `operator delete` 必须配对重载**：用自定义 `new` 分配的内存必须用对应的自定义 `delete` 释放，否则 UB。
2. **不能重载 `new` 表达式本身**：只能重载 `operator new` 函数；构造函数调用是编译器行为，不可干预。
3. **异常规范**：`operator delete` 必须是 `noexcept`（C++11 起），否则编译器警告/错误。
4. **nothrow 形式**：若重载了 `void* operator new(size_t, const std::nothrow_t&) noexcept`，必须同时重载对应的 `operator delete(void*, const std::nothrow_t&) noexcept`，防止构造函数抛异常时内存泄漏。
