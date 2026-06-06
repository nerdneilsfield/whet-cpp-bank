---
qid: cpp-algo-deep-024
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: D
---

下列代码用 `std::lexicographical_compare` 比较两个数组，结果是？

```cpp
std::vector<int> a{1, 2, 3};
std::vector<int> b{1, 2, 3, 0};
bool less = std::lexicographical_compare(
    a.begin(), a.end(), b.begin(), b.end());
std::cout << less;
```

A. `0`（false，因为前缀相同）
B. `0`，因为 `a` 短的反而"大"
C. `1`，因为元素和小
D. `1`，前缀相同时**短的字典序更小**

---

**解析：**

`std::lexicographical_compare(f1,l1,f2,l2)` 按字典序判断序列 1 是否**严格小于**序列 2：

- 找第一个不相等位置，比较两元素
- 若一方耗尽且另一方还有元素，**短者为小**

本例 `a` 是 `b` 的前缀且更短，故 `a < b`，返回 `true`。

C++20 起提供 `std::lexicographical_compare_three_way`（飞船操作符版本）返回 `std::strong_ordering`，支持现代三向比较。
