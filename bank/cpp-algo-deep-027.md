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

---

**解析：**

`std::lower_bound` 只要求 **ForwardIterator**，所以能用于 `list`。它内部做二分但需要"前进 k 步"，在 forward/bidirectional 迭代器上是 O(k) 的，**总移动次数仍为 O(n)**——虽然比较次数仍是 O(log n)。

因此在链表上做二分**没有性能优势**，对于查找应直接用 O(n) 的 `find` 或换数据结构（`std::set`、`std::map`）。

随机访问迭代器（`vector`、`array`、`deque`）上才有真正的 O(log n) 总开销。`std::set::find` 是 O(log n)（基于红黑树）。
