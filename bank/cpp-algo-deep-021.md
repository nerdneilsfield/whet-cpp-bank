---
qid: cpp-algo-deep-021
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: C
---

下列代码哪段**编译错误**？

```cpp
std::list<int> lst{3,1,4,1,5,9,2,6};
std::vector<int> vec{3,1,4,1,5,9,2,6};

// (1) std::sort(vec.begin(), vec.end());
// (2) std::sort(lst.begin(), lst.end());
// (3) lst.sort();
```

A. 只有 (1) 错误
B. 只有 (3) 错误
C. 只有 (2) 错误
D. 全部正确

---

**解析：**

`std::sort` 要求 **RandomAccessIterator**，而 `std::list::iterator` 是 BidirectionalIterator——(2) 编译错误。

`std::list`（以及 `std::forward_list`）提供成员函数 `lst.sort()`，使用归并排序，O(n log n)，对节点指针重链而不移动元素值。

类似地，`std::list::remove / remove_if / unique / merge / reverse / splice` 都是成员版本，比通用算法更高效（指针操作）。

记忆：通用 `<algorithm>` 算法的迭代器类别要求很重要：`sort` 要 RA，`partition` 要 Forward，`reverse` 要 Bidirectional，`find` 要 Input。
