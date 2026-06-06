---
qid: cpp-bp-perf-001
type: single
kp: [cpp-stl-basics]
difficulty: medium
answer_key: B
---

以下两段代码功能相同，但性能差异巨大：

```cpp
// A
std::vector<int> a;
for (int i = 0; i < 1'000'000; ++i)
    a.push_back(i);

// B
std::vector<int> b;
b.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i)
    b.push_back(i);
```

A 慢于 B 的主要原因是什么？

A. push_back 本身比 emplace_back 慢
B. 不 reserve 时容器多次扩容（每次 *2 增长），每次扩容都重新分配 + 移动现有元素，共 O(N) 总搬移成本
C. push_back 检查越界比 reserve 慢
D. 多线程缓存一致性问题

---

## Explanation

`std::vector` 容量增长策略一般是几何增长（GCC libstdc++ 是 2 倍，Clang libc++ 是 2 倍，MSVC 是 1.5 倍）。push 100 万次需要约 log2(1M) ≈ 20 次扩容。每次扩容：
1. 分配新内存（大约是当前 size 的 2 倍）
2. 把现有元素 move/copy 到新内存
3. 释放旧内存

虽然总 push_back 的**摊销复杂度**仍是 O(1)，但**实际总分配字节**约为 2N、**总搬移操作**约为 2N。对 trivial 类型（int）影响约 2-5 倍；对非 trivial 类型（如 `std::string`、对象数组），因为 move/copy 不是 memcpy，可能慢 10 倍以上。

`reserve` 一次性分配 N 个 int 的空间，杜绝了所有扩容，**O(1) 次内存分配，0 次搬移**。

注意：
- 如果不确定大小，不应过度 `reserve` 太大（浪费内存）
- `resize` ≠ `reserve`：resize 会**默认构造** N 个元素，reserve 只分配不构造
- C 错误，push_back 不做越界检查（vector::at 才做）
- D 是无关项

正确做法：循环 push 之前，**已知或可估容量**就 reserve。这是最便宜也最有效的优化之一。
