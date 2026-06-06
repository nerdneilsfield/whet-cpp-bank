---
qid: cpp-taste-algo-016
type: single
kp: [cpp-containers, cpp-stl-basics]
primary_kp: cpp-containers
difficulty: medium
answer_key: B
tags: [code-taste, best-practice]
---

需要在尾部高频插入元素（100 万次 push_back），并**只**在尾部操作（不要求随机访问，不要求头部插入）。下面四个容器的选择，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v;
v.reserve(1'000'000);
for (int i = 0; i < 1'000'000; ++i) {
    v.push_back(i);
}

// B
std::deque<int> d;
for (int i = 0; i < 1'000'000; ++i) {
    d.push_back(i);
}

// C
std::list<int> lst;
for (int i = 0; i < 1'000'000; ++i) {
    lst.push_back(i);
}

// D
std::vector<int> v;
for (int i = 0; i < 1'000'000; ++i) {
    v.push_back(i);  // no reserve
}
```

A. A — vector + reserve，摊销 O(1) 且 cache 友好

B. B — deque 尾部插入无需 reserve，也很快

C. C — list 每次插入是独立节点分配

D. D — vector 无 reserve 会反复 reallocate

---

**解析：**

选 A。纯尾部插入场景，`vector` + `reserve` 提供连续内存 + 摊销 O(1) 插入 + 最优缓存局部性，是标准答案。

逐一品味为什么其他不好：

- **B**：`deque` 也擅长尾部插入（以及头部插入）。但它的内存模型是分块（chunked），即使尾部插入不频繁 reallocate，对每个元素的**遍历/随机访问**比 `vector` 慢（需要一次额外间接寻址）。题目说"只尾部操作"，`deque` 在这个场景下表现**可以**，但 `vector` 的内存更紧凑，和大小的乘数更小。

- **C**：`list` (doubly linked list) 每次 `push_back` 都做一次**独立堆分配**。100 万次独立分配 ≈ 大量 malloc 调用 + 内存碎片 + 缓存不命中。链表节点（通常 24 字节）还要额外存前后指针。尾部插入是 O(1) 但常数巨大。只有在需要**在任意位置插入而不使迭代器失效**时才用 `list`。

- **D**：没有 `reserve` 的 `vector`，每次容量不够时**重新分配并移动所有已有元素**。标准库的 growth factor 通常 1.5-2x，100 万次插入会发生约 20 次 reallocation，每次代价 O(n)。最后总复杂度仍然是 O(n) 摊销的，但 reallocation 的**延迟峰值**可能导致卡顿。

`vector` 连续内存的 cache 亲和力在**顺序访问**场景下是压倒性的优势。三种标准库实现（libstdc++/libc++/MSVC STL）里 `vector` 的尾部插入性能都显著优于 `deque` 和 `list`。

核心识别点：
- 仅尾部插入 → `vector` + `reserve`
- 头尾插入 → `deque`
- 任意位置插入（迭代器持久性） → `list`
- 不要忽视 cache 局部性——连续内存是现代 CPU 友好的
- "不写 reserve"是 performance bug，不是品味问题