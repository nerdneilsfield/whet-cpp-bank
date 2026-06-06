---
qid: cpp-algo-deep-027
type: single
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: hard
answer_key: B
---

`std::lower_bound` 用在 `std::list`（双向链表）上的复杂度是？

```cpp
std::list<int> lst{1,2,3,4,5,6,7,8,9};
auto it = std::lower_bound(lst.begin(), lst.end(), 5);
```

A. O(log n)，与 vector 相同
B. **比较次数** O(log n)，但**迭代器步进总次数**仍为 O(n)
C. O(n²)
D. 编译错误，`lower_bound` 要求随机访问

## 解析

正确答案是 B：lower_bound 可用于 list，因为它只要求前向迭代器，并不强制随机访问。它的比较次数仍是对数级，但在链表上前进迭代器需要逐个移动，因此总步进次数是 O(n)。误区是把“二分比较次数”直接等同于整体运行时间，忽略了迭代器类别的成本。
