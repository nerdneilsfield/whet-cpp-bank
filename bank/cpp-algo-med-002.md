---
qid: cpp-algo-med-002
type: single
kp: [cpp-algorithms]
difficulty: medium
answer_key: B
---

下列两个调用在功能上有什么本质区别？

```cpp
std::vector<int> v = {1, 3, 5, 7, 9};
auto a = std::binary_search(v.begin(), v.end(), 5);   // (1)
auto b = std::lower_bound  (v.begin(), v.end(), 5);   // (2)
```

A. 两者完全等价，`binary_search` 是 `lower_bound != end() && *lower_bound == x` 的别名
B. `binary_search` 返回 `bool`，只回答"在不在"；`lower_bound` 返回**位置**——第一个不小于 `x` 的迭代器，可能等于 `end()`，等于 `end()` 或 `*it != x` 都表示"不在"
C. `lower_bound` 比 `binary_search` 慢一倍，因为它需要返回精确位置
D. `lower_bound` 要求容器排序，`binary_search` 不要求

---

**解析：**

`std::binary_search` 和 `std::lower_bound` 都要求输入区间按比较器有序，复杂度都是 O(log n) 比较次数（对 random-access iterator）。区别在返回值与用途：

- `binary_search` 返回 `bool`：仅回答"是否存在等价元素"。不告诉位置。
- `lower_bound` 返回 `iterator`：指向**第一个不小于** `x` 的位置。判断"是否存在"需额外比较：`it != end() && !(x < *it)`（或 `*it == x`）。
- `upper_bound` 类似，返回**第一个大于** `x` 的位置。

`lower_bound` 是更基础的原语，可推出 `binary_search`、`equal_range`、`insert` 的插入位置等。性能上两者数量级相同，但 `binary_search` 在某些实现里会调用 `lower_bound` 然后比较一次，常数稍大。

实战中，如果只是"判断在不在"，写 `binary_search` 表意更清；如果要"找出位置以便插入或读取关联值"（典型的有序 `vector<pair>` 当作 map 用），用 `lower_bound`。常见 bug：忘了 `it != end()` 的判空，对 `*end()` 解引用是 UB。
