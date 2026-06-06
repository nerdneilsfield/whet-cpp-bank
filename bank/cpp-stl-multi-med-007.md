---
qid: cpp-stl-multi-med-007
type: multi
kp: [cpp-algorithms]
difficulty: medium
answer_key: [A, B, C]
---
关于 `std::lower_bound` 与 `std::find` 在**已排序**区间上的对比，**哪些说法是正确的**？（多选）

```cpp
std::vector<int> v{1, 3, 5, 7, 9};
auto it1 = std::find(v.begin(), v.end(), 5);
auto it2 = std::lower_bound(v.begin(), v.end(), 5);
auto it3 = std::lower_bound(v.begin(), v.end(), 6);
```

A. 对随机访问区间，`std::lower_bound` 的时间复杂度是 O(log n)，`std::find` 是 O(n)
B. `std::lower_bound` 要求区间相对于查找值已按比较器**分块有序**（已按 `<` 排序即可），否则结果未定义
C. 当目标值不存在时，`std::lower_bound` 返回**第一个不小于该值**的位置；`std::find` 返回 `end()`
D. `std::lower_bound` 的复杂度始终是 O(log n)，**与迭代器类别无关**

---

**解析：**

A 正确：二分查找 O(log n)，线性查找 O(n)。
B 正确：`lower_bound` 需要区间按比较器排序（实际上更弱：按比较器 partitioned）；否则结果未定义。
C 正确：`lower_bound(v, 6)` 返回指向 `7` 的迭代器；`find` 找不到则返回 `end()`。
D 错误：`lower_bound` 的**比较次数**始终是 O(log n)，但若迭代器是非随机访问（如 `std::list`，但 `list` 自己的 `forward_iterator` 也可工作于 `lower_bound`），则**前进 n/2 步**仍是 O(n) 步数，总复杂度退化为 O(n)。所以复杂度与迭代器类别相关。

## Explanation

A、B、C 正确：在已按比较器分块有序的区间上，`lower_bound` 返回第一个不小于目标的位置，随机访问迭代器下比较/定位效率通常优于线性 `find`。若区间不满足排序或 partition 前提，结果没有意义。常见误区是只记住 `lower_bound` 的 O(log n) 比较次数，却忽略非随机访问迭代器上移动步数可能仍是线性的。
