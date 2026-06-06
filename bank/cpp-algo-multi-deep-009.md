---
qid: cpp-algo-multi-deep-009
type: multi
kp: [cpp-algorithms]
primary_kp: cpp-algorithms
difficulty: medium
answer_key: [A, C]
---

关于 `std::priority_queue`，下列哪些**正确**？（多选）

```cpp
std::priority_queue<int> pq;
```

A. 默认底层容器是 `std::vector`，使用 `<algorithm>` 的堆函数维持堆性质
B. 默认是 min-heap
C. 传入 `std::greater<T>` 作为比较器可得到 min-heap
D. 支持任意迭代器遍历内部所有元素

## 解析

正确选项是 A、C。priority_queue 默认底层容器是 vector，并使用标准堆操作维护堆性质；默认比较器 less 让最大元素位于 top，因此是 max-heap。传入 greater 可得到 min-heap。它是容器适配器，只暴露 push、pop、top 等接口，不提供遍历内部元素的迭代器。
