---
qid: cpp-taste-algo-009
type: single
kp: [cpp-algorithms, cpp-containers, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
tags: [code-taste, best-practice]
---

从 vector<int> 中找出**中位数**（n 为奇数）。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
auto median = [&v]() -> int {
    std::vector<int> c = v;
    std::sort(c.begin(), c.end());
    return c[c.size() / 2];
}();

// B
std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
auto it = v.begin() + v.size() / 2;
std::ranges::nth_element(v, it);
int median = *it;

// C
std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
int median = 0;
for (auto x : v) median = std::midpoint(median, x);

// D
std::vector<int> v{3, 1, 4, 1, 5, 9, 2};
std::priority_queue<int> max_heap(v.begin(), v.end());
for (int i = 0; i < v.size() / 2; ++i) max_heap.pop();
int median = max_heap.top();
```

A. A — 拷贝 + sort，最安全不修改原容器

B. B — nth_element 精确找第 k 大，O(n) 不排序

C. C — midpoint 累积，函数式

D. D — 最大堆弹出半数，直观

---

**解析：**

选 B。中位数问题是 `nth_element` 的经典应用场景——"找一个元素，使得它在排序后的正确位置"，而不需要排完整。

逐一品味为什么其他版本不好：

- **A**：拷贝副本再 sort，O(n log n) 时间 + O(n) 额外空间。当 vector 很大时，分配和拷贝的开销不可忽略。而且如果原 vector 是只读的，确实需要副本，但题目没有说原 vector 不能修改。用更多的时间和空间做了算法上不需要的事。

- **C**：`std::midpoint` 是 C++20 新增的**数值安全平均**函数，但它计算的是两个数的中点，不是统计学中位数。把整个序列反复 mid-point 没有意义——它不是中位数。

- **D**：最大堆构造是 O(n)，但弹出 k = n/2 次要 O(n log n)。和 sort 的复杂度一样，内存开销更大，代码也更长。`nth_element` 是专门为此场景设计的——平均 O(n)，一次调用解决问题。

`nth_element` 保证第 n 个位置的元素是排序后会在那个位置的元素，前面都是小于等于它的，后面都是大于等于它的。这是部分排序中的"最优解"——只找一个位置。

核心识别点：
- 找中位数/分位数 → `nth_element`（或 `ranges::nth_element`）
- 找前 k 个最小且排序 → `partial_sort`
- 全排序 → `sort`（杀鸡用牛刀）
- 中位数不是平均数，数清楚再选 algorithm

## Explanation

正确答案是 B。中位数问题是 `nth_element` 的经典应用场景——"找一个元素，使得它在排序后的正确位置"，而不需要排完整。
D：最大堆构造是 O(n)，但弹出 k = n/2 次要 O(n log n)。
当 vector 很大时，分配和拷贝的开销不可忽略。
