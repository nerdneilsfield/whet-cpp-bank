---
qid: cpp-taste-algo-005
type: single
kp: [cpp-algorithms, cpp-containers, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: D
tags: [code-taste, best-practice]
---

要把两个已排序的 `vector<int>` 合并为一个已排序的 vector。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> a{1, 3, 5, 7, 9};
std::vector<int> b{2, 4, 6, 8, 10};
std::vector<int> c = a;
c.insert(c.end(), b.begin(), b.end());
std::sort(c.begin(), c.end());

// B
std::vector<int> a{1, 3, 5, 7, 9};
std::vector<int> b{2, 4, 6, 8, 10};
std::vector<int> c;
std::merge(a.begin(), a.end(),
           b.begin(), b.end(),
           std::back_inserter(c));

// C
std::vector<int> a{1, 3, 5, 7, 9};
std::vector<int> b{2, 4, 6, 8, 10};
std::vector<int> c(a.size() + b.size());
std::copy(b.begin(), b.end(), c.begin());
std::copy(a.begin(), a.end(), c.begin() + b.size());
std::sort(c.begin(), c.end());

// D
std::vector<int> a{1, 3, 5, 7, 9};
std::vector<int> b{2, 4, 6, 8, 10};
std::vector<int> c;
c.reserve(a.size() + b.size());
c.insert(c.end(), a.begin(), a.end());
c.insert(c.end(), b.begin(), b.end());
std::sort(c.begin(), c.end());
```

A. A — append + sort，最简单

B. B — merge，零手写

C. C — copy 两份到预分配空间，再 sort

D. D — reserve + insert + sort，内存最优

---

**解析：**

选 B。`std::merge` 是专门为"将两个有序范围合并为一个有序范围"设计的 algorithm。

逐一品味为什么其他版本不好：

- **A 和 D**：插入完再 `sort`，复杂度 O(n log n)。而两个序列**已经各自有序**，`merge` 只需要一次 O(n) 线性遍历就能得到结果。A 和 D 都浪费了已有的有序性信息。更重要的是：你用 `sort` 就**丢失了"我利用了输入已排序的事实"这个意图**。后来的维护者会不会把 `a` 改成无序？如果改了，`merge` 可能出问题，但 `insert+sort` 依然工作——**代码意图和实际行为之间出现了裂缝**。

- **C**：copy 两份再 sort，同样没利用有序性。而且手动计算偏移量 `c.begin() + b.size()`，容易写错还不安全。高级工程师看到手动指针偏移会警觉——它在做 container 应该自己管的事。

`merge` 要求输入范围是有序的，输出也是有序的。名字和语义完全对仗。

核心识别点：
- 两个序列已经有序 → `merge`，不要 `insert` + `sort`
- 两个序列无序、只是要拼起来 → `insert` 即可
- 需要去重合并 → `set_union`
- 需要找共同元素 → `set_intersection`
- 这些 set-algorithms 都假设输入有序

## Explanation

正确答案是 D。`std::merge` 是专门为"将两个有序范围合并为一个有序范围"设计的 algorithm。
逐一品味为什么其他版本不好： A 和 D：插入完再 `sort`，复杂度 O(n log n)。
而且手动计算偏移量 `c.begin() + b.size()`，容易写错还不安全。
