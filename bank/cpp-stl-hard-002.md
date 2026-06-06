---
qid: cpp-stl-hard-002
type: single
kp: [cpp-stl-basics]
difficulty: hard
answer_key: C
---

`std::string` 的小字符串优化（SSO）阈值与行为，下列正确的是？

```cpp
std::string s1 = "hi";           // 短
std::string s2 = "this is a very long string that exceeds SSO capacity";
```

A. `std::string` 不使用 SSO，总是在堆上分配
B. SSO 阈值由 `std::char_traits::length` 的编译期决定，所有实现都是 15 字节
C. SSO 的实现细节是未指定的，但 libstdc++ 和 libc++ 都使用内嵌缓冲区（如 `union`），阈值通常为 15（GCC libstdc++）或 22 字节（Clang libc++）；超出该长度才堆分配
D. SSO 只在 C++17 后可用

## Explanation

SSO（Small String Optimization）是 C++11 起各标准库的优选实现策略（标准不要求但实践中广泛采用）。核心设计：`std::string` 在栈上维护一个 `union`，内含指针、长度、容量以及一个"内嵌字符缓冲区"——当字符串长度 ≤ 预设阈值时，直接存在栈缓冲区中，避免堆分配。阈值因实现而异：
- libstdc++（GCC）：通常 15 字节（加上 `\0` 用满 16 字节对齐的栈空间）
- libc++（Clang）：通常 22 字节（利用更长对齐）
- MSVC：类似 libstdc++

SSO 是为什么短字符串操作远快于长字符串操作的关键原因，也是为什么 `std::string` 交换/移动操作在不同实现下有不同开销的因素之一。
