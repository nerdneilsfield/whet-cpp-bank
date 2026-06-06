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

---

**解析：**

`std::adjacent_find` 返回**首对相邻相等元素中前一个的迭代器**（默认 `operator==`，可传谓词改成任意二元关系）。找不到返回 `last`。

例：`v[2]=3, v[3]=3`，返回 `v.begin()+2`，解引用得 `3`。复杂度 O(n)。
常用作"检测重复"或"找拐点"（传递自定义谓词如 `>`、`==` 等）。
