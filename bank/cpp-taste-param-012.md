---
qid: cpp-taste-param-012
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: hard
answer_key: B
---

`sum_of` 需要接收一个整数数组，计算所有元素之和（只读）。从**参数传递品味**的角度，哪段最合适？

```cpp
// A
int sum_of(const std::vector<int>& v) {
    return std::accumulate(v.begin(), v.end(), 0);
}
```

```cpp
// B
int sum_of(std::span<const int> s) {
    return std::accumulate(s.begin(), s.end(), 0);
}
```

```cpp
// C
int sum_of(const int* arr, size_t count) {
    return std::accumulate(arr, arr + count, 0);
}
```

```cpp
// D
template <class Container>
int sum_of(const Container& c) {
    return std::accumulate(c.begin(), c.end(), 0);
}
```

A. A 段：`const vector<int>&` 最常见、最直接、调用方确信我有 vector。
B. B 段：`span<const int>` 能接 vector、数组、指针+size、initializer list，零拷贝。
C. C 段：C 风格指针 + size，兼容 C 和 C++，调用方不用调整数据结构。
D. D 段：模板通用性最强，任何有 begin/end 的容器都能用。

## Explanation

正确答案是 **B**。

- **A 段（差）**：`const vector<int>&` 钉死了"调用方必须有 `vector<int>`"。如果调用方有一个原生数组 `int raw[]`，就不能直接传；如果有 `std::array<int, 5>`，也不能传；如果有 `std::list<int>`，还不能传。API 的使用面被不必要地限缩了。
- **B 段（好）**：`std::span<const int>`（C++20）是数组/容器的连续片段抽象，能接 `std::vector`、`std::array`、原生数组、`const int* + size`、`std::initializer_list`；零拷贝、零分配、零分配；函数在意的是连续内存，span 恰好是这个约束在类型系统上的投影。
- **C 段（差）**：在 C++ 代码里恢复 C 风格的 `(ptr, size)` 参数对，丢失了长度类型安全（`count` 可以传负数、可以传更大值），也无法轻易和 STL 算法配合（需要 `arr + count` 手工拼 iterator pair）；更不带任何迭代器检查，纯靠调用方保证。
- **D 段（差）**：模板通用性强，但也意味着头文件 + 隐含约束多。调用方可以传 `std::list<int>`，而 `list` 不是连续内存——函数虽然能编译，但 `std::accumulate` 在 list 上用 CPU 缓存不友好。模板还在需要分立的 ABI 边界处不可行，span 没这个问题（span 是一个非模板普通类型）。

**核心识别点：**
- 连续内存的只读数组用 `std::span<const T>`（C++20），不用 `const vector<T>&`。
- `const vector<T>&` 把 API 锁定在"你必须有一个 vector"——旧 STL 时代的惯性写法。
- C 风格 `(ptr, size)` 缺乏类型安全，在 C++ 里应只留做 ABI 互操作层。
- 模板通用容器参数可以编译但对非连续容器有预期外的性能。
- `span` 是值类型（2 指针或指针+size），按值传，开销 = 两个寄存器。

**来源：** C++ Core Guidelines F.16（"span<T> for array-like parameters"）；ISO C++ committee P0122R7（span proposal）；cppreference `std::span`。
