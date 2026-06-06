---
qid: cpp-algo-deep-025
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

下列代码用 `std::sort` 与 `std::lower_bound` 配合，但行为不一致，原因是？

```cpp
std::vector<int> v{5,2,8,1,9,3};
auto cmp = [](int a, int b){ return std::abs(a) < std::abs(b); };
std::sort(v.begin(), v.end(), cmp);
auto it = std::lower_bound(v.begin(), v.end(), 4);  // ← 默认 < 比较
```

A. `lower_bound` 不支持 lambda
B. `lower_bound` 必须使用**与排序时相同的比较器**，否则结果未定义
C. `std::sort` 不能用 lambda
D. `std::abs` 不能用于 int

---

**解析：**

二分搜索族（`lower_bound` / `upper_bound` / `equal_range` / `binary_search`）的**前提条件**是序列已按**同一比较器**有序（"is partitioned w.r.t. predicate"）。若排序用 `cmp`，搜索也必须传 `cmp`，否则前提不成立，结果未定义（不一定崩溃，可能返回错误位置）。

正确写法：

```cpp
auto it = std::lower_bound(v.begin(), v.end(), 4, cmp);
```

`std::map<K,V>::find` 也是基于其内部 `Compare`，所以自定义比较器的 `set/map` 不能用 `std::find`（用成员 `find`，O(log n)）。
