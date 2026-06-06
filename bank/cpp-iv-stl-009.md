---
qid: cpp-iv-stl-009
type: short
kp: [cpp-interview]
difficulty: hard
tags: [Meta, 腾讯]
rubric:
  - 说清 SSO 的核心思想：短字符串直接存在对象内部的固定缓冲区，不堆分配
  - 说出典型 SSO 阈值（15~22 字节，视实现而定）
  - 解释 SSO 节省的代价：省去 malloc/free、省去 cache miss、sizeof(string) 通常 24~32 字节
  - 说出 SSO 的 union 实现方式（短模式 vs 长模式共用内存布局）
  - 说出 SSO 对移动语义的影响（短字符串移动后原对象非空，移后源仍有效）
---

# `std::string` 的 SSO（小字符串优化）是什么？

### 问题

什么是 `std::string` 的小字符串优化（Small String Optimization，SSO）？它是如何实现的？为什么短字符串不需要堆分配？有哪些副作用需要注意？

## Explanation

### SSO 的核心思想

标准库的 `std::string` 实现（GCC libstdc++、Clang libc++、MSVC STL 均支持）中，当字符串长度不超过某个阈值时，不在堆上分配内存，而是直接将字符数据存储在 `std::string` 对象自身的内部缓冲区（栈上或对象内联空间）中。这避免了 `malloc` / `free` 的开销以及随之而来的缓存不友好。

### 内存布局（以 libc++ 为例）

`std::string` 对象通常占 24 字节（64 位系统）。内部用一个 `union` 区分两种模式：

```
长字符串模式（heap）:
  [pointer to heap data (8B)] [size (8B)] [capacity | flag (8B)]

短字符串模式（SSO）:
  [inline buffer (22B)] [size (1B)] [flag bit in last byte]
```

最后 1 个字节的最高位（或某个标志位）区分当前是长模式还是短模式。`sizeof(std::string) == 24`（libc++）或 `32`（libstdc++）。

- **libc++**：SSO 阈值 ≤ 22 字节（可存 22 个字符 + `\0`）。
- **libstdc++**：SSO 阈值 ≤ 15 字节（对象 32 字节，内联 buffer 15 + 1）。
- **MSVC STL**：SSO 阈值 ≤ 15 字节。

### 为什么短字符串不堆分配

1. **`malloc` 有固定开销**：一次堆分配约 50~200 ns，SSO 直接访问对象内存 < 1 ns。
2. **内存局部性**：对象和字符数据在同一缓冲区，访问不跨缓存行。
3. **现实数据分布**：大量字符串（标识符、枚举名、短路径）在 15 字节以内，SSO 命中率高。

### 对移动语义的影响

长字符串的移动（`std::move`）只需转移堆指针，O(1) 且移后源为空字符串。

**短字符串的移动必须拷贝内联 buffer**（因为数据就在对象里，没有指针可以"偷走"），所以：
- 短字符串的移动代价 = 拷贝代价（约 24/32 字节 memcpy）。
- 移动后**原对象仍然有效**（值为有效但未指定的状态，通常为空串）。

这是一个重要的实现细节：对短字符串不要期望移动"一定比拷贝快"。

### 实践影响

```cpp
std::string s = "hello";           // SSO，无堆分配
std::string t = "this is a longer string that exceeds SSO limit"; // 堆分配

// 检查是否发生堆分配（非标准，debug 用）
// 若 s.data() 地址在 &s 附近 → SSO 生效
```

当字符串频繁拷贝/创建时，SSO 是性能关键路径上的重要优化；涉及内存分析时，注意 SSO 对象不会在 heap profiler 中留下记录，但会在栈帧上占用空间。
