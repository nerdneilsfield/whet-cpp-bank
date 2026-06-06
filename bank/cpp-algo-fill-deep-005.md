---
qid: cpp-algo-fill-deep-005
type: fill
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: ["std::stable_partition", "stable_partition", "std::ranges::stable_partition"]
---

要按谓词把容器划分为两部分，并**保持每部分中元素的相对顺序**，应使用算法 _______。

---

**解析：**

`std::stable_partition(first, last, pred)` 保证两组内部元素相对顺序与原序列一致：

- 复杂度：在有足够辅助内存时 O(n)；否则 O(n log n)
- 返回新中间分界点的迭代器

对比：`std::partition` **非稳定**，平均 O(n)，常数项更小。

实际选择：
- 顺序无所谓 → `std::partition`
- 必须保序 → `std::stable_partition`

类似命名规律也适用于 `sort`/`stable_sort`。
