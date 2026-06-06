---
qid: cpp-taste-algo-002
type: single
kp: [cpp-algorithms, cpp-containers, cpp-stl-basics]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: C
tags: [code-taste, best-practice]
---

要从 1000 万个整数中找到最小的 5 个。下面四个写法功能相同，哪个最有 C++ 味？

```cpp
// A
std::vector<int> v(10'000'000);
// ... fill v ...
std::sort(v.begin(), v.end());
std::vector<int> top5(v.begin(), v.begin() + 5);

// B
std::vector<int> v(10'000'000);
// ... fill v ...
std::nth_element(v.begin(), v.begin() + 5, v.end());
std::vector<int> top5(v.begin(), v.begin() + 5);
std::sort(top5.begin(), top5.end());

// C
std::vector<int> v(10'000'000);
// ... fill v ...
std::partial_sort(v.begin(), v.begin() + 5, v.end());
std::vector<int> top5(v.begin(), v.begin() + 5);

// D
std::vector<int> v(10'000'000);
// ... fill v ...
std::priority_queue<int> pq;
for (auto x : v) {
    pq.push(-x);
    if (pq.size() > 5) pq.pop();
}
std::vector<int> top5;
while (!pq.empty()) {
    top5.push_back(-pq.top());
    pq.pop();
}
```

A. A — sort 最清晰，后面再截取

B. B — nth_element 更快，排完前 5 个也排序了

C. C — partial_sort 一步到位，语义最明确

D. D — 堆选择 O(n log k)，数据量大时最优

---

**解析：**

选 C。面对"找前 k 个最小元素"这种需求，`partial_sort` 的名字就是意图本身。

逐一品味为什么其他版本不好：

- **A**：`sort` 整个数组 O(n log n)。当只需要前 5 个时，剩下的 9999995 个元素也是在白白排序。这是"大炮打蚊子"。

- **B**：`nth_element` 确实只做部分排序（O(n)），但它的承诺是"第 k 个位置的元素刚好是第 k 小的"，前 k-1 个元素只保证"不大于"第 k 个，并不排序。所以下面还得额外 `sort` 一次。两步做一件事，不如 `partial_sort` 一步到位。

- **D**：堆选择，复杂度 O(n log k)。当 k 很小时（k=5），这是个不错的选择。但问题在于你要对元素取负再塞进去实现最小堆——这种"符号反转"是脏技巧，代码可读性显著下降。`partial_sort` 在内部也用了堆（heap_select），但封装得干干净净。D 的写法暴露了不该暴露的实现细节。

`partial_sort` 的语义是："把最小的 k 个元素放到前面，并且保证它们有序"。名字就告诉你它在做什么。k 远小于 n 时，它的内部实现也是堆选 + 排序，复杂度 O(n log k) 和 D 一样好，但代码更干净。

核心识别点：
- 问"前 k 个 **已排序**" → `partial_sort`
- 问"第 k 个"或"分两组" → `nth_element`（更轻量，不保证前段有序）
- 问"全排" → `sort`（杀鸡用牛刀）
- 不到万不得已，不信手写堆

## Explanation

正确答案是 C。面对"找前 k 个最小元素"这种需求，`partial_sort` 的名字就是意图本身。
D：堆选择，复杂度 O(n log k)。
当 k 很小时（k=5），这是个不错的选择。
