---
qid: cpp-algo-deep-014
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码用 `std::adjacent_find` 查找第一对相邻相等的元素，结果是？

```cpp
std::vector<int> v{1, 2, 3, 3, 4, 5, 5};
auto it = std::adjacent_find(v.begin(), v.end());
std::cout << (it - v.begin()) << " " << *it;
```

A. `0 1`
B. `5 5`（找到位置 5 的 5）
C. `2 3`（返回**第一对**相邻相等的**前一个**位置，即 v[2]==v[3]==3）
D. 编译错误

## Explanation

正确答案是 C：std::adjacent_find 返回第一对相邻相等元素中前一个元素的迭代器。序列中第一对是 v[2] 和 v[3] 的 3，因此输出下标 2 和值 3。误区是以为它返回后一项或最后一对；只有完全找不到相邻相等元素时才返回 end。
