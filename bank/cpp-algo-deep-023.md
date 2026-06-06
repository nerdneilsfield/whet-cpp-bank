---
qid: cpp-algo-deep-023
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: B
---

下列代码输出是？

```cpp
std::vector<int> v{1,3,5,7,4,9,11};
auto it = std::is_sorted_until(v.begin(), v.end());
std::cout << (it - v.begin()) << " " << *it;
```

A. `0 1`
B. `4 4`（前 4 个有序，下标 4 处的 4 破坏顺序）
C. `7` （整个向量长度）
D. `3 7`

---

**解析：**

`std::is_sorted_until(first, last, cmp = less)` 返回**第一个破坏顺序的元素**的迭代器：找最长有序前缀 `[first, it)`，使得 `it == last` 表示完全有序。

本例 `1 3 5 7` 升序，下一个 `4 < 7` 打破升序，返回指向 `4` 的迭代器，下标 4。

相关：`std::is_sorted` 返回 bool；`is_sorted_until` 是它的更详细版本，常用于诊断或部分处理。
