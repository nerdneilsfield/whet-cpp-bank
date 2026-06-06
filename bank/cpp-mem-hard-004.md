---
qid: cpp-mem-hard-004
type: single
kp: [cpp-memory-mgmt]
difficulty: hard
answer_key: C
---

关于 `std::allocator<T>` 与 `std::pmr::polymorphic_allocator<T>` 的区别，下列说法正确的是？

```cpp
std::vector<int, std::allocator<int>> v1;

std::array<std::byte, 1024> buf;
std::pmr::monotonic_buffer_resource res{buf.data(), buf.size()};
std::pmr::vector<int> v2{&res};
```

A. 两者都是值类型，且不同分配器类型的容器之间可以互换赋值
B. `polymorphic_allocator` 通过模板参数静态选择资源，与 `allocator` 一样不引入虚函数开销
C. `polymorphic_allocator` 通过**类型擦除**指向 `memory_resource` 基类指针，运行期分发；容器在传播分配器时只复制指针，可让不同后备资源的同类型容器共存
D. 标准要求 `polymorphic_allocator` 的 `allocate` 必须使用 `malloc`

## 解析

`std::allocator` 是静态多态的最小分配器，所有同类型 `vector<int>` 共享同一分配策略；不同分配器模板参数的容器是不同类型，不可直接赋值。`polymorphic_allocator` 持有 `memory_resource*`，`allocate` 经虚函数转发到具体资源（`monotonic_buffer_resource`、`unsynchronized_pool_resource` 等）。这带来运行期开销，但所有 `pmr::vector<int>` **是同一类型**，可以互相赋值、按值传参，仅在构造时绑定不同 `memory_resource`，灵活性远高于传统 allocator。A 错误：不同分配器类型容器不互换；B 与 C 矛盾，且不正确；D 标准未规定具体上游。
