---
qid: cpp-algo-fill-deep-004
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["O(n)", "Θ(n)", "线性", "linear"]
---

`std::nth_element(first, nth, last)` 在平均情况下的时间复杂度是 _______（请以大 O 记号或汉字描述给出答案）。

---

**解析：**

`std::nth_element` 采用 **introselect**（基于 quickselect，最坏切到 median-of-medians 或 heapselect），**平均 O(n)**，最坏 O(n)（标准 C++17 后保证最坏线性）。

执行后：
- 位置 `nth` 上的元素 = 整个范围排序后第 `(nth - first)` 个元素
- `[first, nth)` 元素都 ≤ `*nth`
- `[nth, last)` 元素都 ≥ `*nth`
- 两侧内部**不排序**

典型应用：求"第 k 小"、求中位数；比 `std::sort` 的 O(n log n) 更优。要顺便求"前 k 个有序"应用 `partial_sort`，复杂度 O(n log k)。
