---
qid: cpp-iv-mem-010
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Google]
rubric:
  - 理解 std::allocator 的接口（allocate/deallocate/construct/destroy）
  - 知道容器模板参数接受自定义分配器（Allocator concept）
  - 能说出自定义分配器的典型场景（内存池、NUMA、共享内存、arena）
  - 理解 allocator_traits 的作用（提供缺省实现，降低实现成本）
  - 加分：提到 PMR（std::pmr，C++17）及 polymorphic_allocator 的优势（运行时多态，无模板污染）
---

# `std::allocator` 和自定义分配器的应用场景？

## 参考答案

### `std::allocator` 的作用

`std::allocator<T>` 是标准容器（`vector`、`list`、`map` 等）的**默认内存分配策略**，封装了对 `::operator new`/`::operator delete` 的调用。容器将所有内存操作委托给分配器，使内存策略可替换。

```cpp
// 标准容器默认模板参数
template <class T, class Allocator = std::allocator<T>>
class vector { ... };
```

关键接口（C++17 起部分移入 `allocator_traits`）：

```cpp
template <class T>
struct MyAllocator {
    using value_type = T;

    T* allocate(std::size_t n);              // 分配 n 个 T 的原始内存
    void deallocate(T* p, std::size_t n);    // 释放

    // construct/destroy 在 C++17 后建议通过 allocator_traits 提供默认实现
};
```

### `allocator_traits`

直接实现完整 Allocator concept 繁琐（需要各种 typedef、rebind 等）。`std::allocator_traits<A>` 为缺失的接口提供默认实现，只需实现 `allocate`/`deallocate` 和 `value_type` 即可。

```cpp
// 容器内部用 allocator_traits 调用，而非直接调用分配器
auto* p = std::allocator_traits<Alloc>::allocate(alloc_, n);
std::allocator_traits<Alloc>::construct(alloc_, p, args...);
```

### 自定义分配器：Arena/内存池示例

```cpp
#include <memory>
#include <vector>

// 简单 arena 分配器：从固定缓冲区分配，全部释放时一次性回收
template <class T>
class ArenaAllocator {
public:
    using value_type = T;

    explicit ArenaAllocator(char* buf, std::size_t size) noexcept
        : buf_(buf), end_(buf + size), cur_(buf) {}

    // rebind（让容器为不同类型使用同一 arena）
    template <class U>
    ArenaAllocator(const ArenaAllocator<U>& o) noexcept
        : buf_(o.buf_), end_(o.end_), cur_(o.cur_) {}

    T* allocate(std::size_t n) {
        std::size_t bytes = n * sizeof(T);
        // 对齐到 alignof(T)
        std::size_t align = alignof(T);
        std::uintptr_t addr = (reinterpret_cast<std::uintptr_t>(cur_) + align - 1)
                              & ~(align - 1);
        char* p = reinterpret_cast<char*>(addr);
        if (p + bytes > end_) throw std::bad_alloc{};
        cur_ = p + bytes;
        return reinterpret_cast<T*>(p);
    }

    void deallocate(T*, std::size_t) noexcept {
        // arena 策略：单个释放为空操作，整体销毁时回收
    }

    // 必须让不同类型的实例比较相等（共享同一 arena）
    template <class U>
    bool operator==(const ArenaAllocator<U>& o) const noexcept {
        return buf_ == o.buf_;
    }

    char* buf_; char* end_; char* cur_;  // public 仅为 rebind 方便
};

// 使用
int main() {
    alignas(std::max_align_t) char arena[4096];
    ArenaAllocator<int> alloc(arena, sizeof(arena));
    std::vector<int, ArenaAllocator<int>> v(alloc);
    v.push_back(1);
    v.push_back(2);
    // v 的所有内存来自 arena，零堆分配
}
```

### 典型应用场景

| 场景 | 策略 |
|------|------|
| 游戏帧内对象 | Arena：每帧分配，帧末一次性清空 |
| 网络请求上下文 | Arena：请求开始分配，请求结束整块释放 |
| NUMA 优化 | NUMA-aware 分配器，确保内存分配在指定 NUMA 节点 |
| 共享内存 IPC | 基于 `mmap` 的分配器，让多进程共享容器 |
| 嵌入式/无 OS | 静态缓冲区分配器，避免动态堆 |

### C++17 PMR（Polymorphic Memory Resource）

C++17 引入 `std::pmr` 命名空间，解决了传统自定义分配器的最大痛点——**模板参数污染**（`vector<int, MyAlloc>` 和 `vector<int>` 是不同类型，无法赋值）。

```cpp
#include <memory_resource>
#include <vector>

// pmr 容器：分配器是运行时多态，不影响类型
char buf[4096];
std::pmr::monotonic_buffer_resource arena(buf, sizeof(buf));
std::pmr::vector<int> v(&arena);   // 类型仍是 pmr::vector<int>
v.push_back(42);

// 可以赋值给另一个 pmr::vector<int>（使用不同分配器）
std::pmr::vector<int> v2 = std::move(v);
```

`pmr` 提供的标准 memory resource：
- `monotonic_buffer_resource`：只分配不释放，适合短生命周期对象
- `unsynchronized_pool_resource`：单线程内存池
- `synchronized_pool_resource`：多线程内存池
- `new_delete_resource()`：回退到全局 `new`/`delete`
