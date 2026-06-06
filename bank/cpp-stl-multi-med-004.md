---
qid: cpp-stl-multi-med-004
type: multi
kp: [cpp-stl-basics]
difficulty: medium
answer_key: [A, B, D]
---
关于容器选择的依据，**哪些说法是正确的**？（多选）

A. 需要频繁在头部插入/删除时，`std::deque` 优于 `std::vector`。
B. 需要有序存储且频繁范围查询时，`std::set` 优于 `std::unordered_set`。
C. 所有容器中最快的遍历永远是 `std::vector`。
D. 需要稳定迭代器（插入后不失效）时应优先考虑 `std::list`。

---

**解析：**

A 正确：`deque` 在头部和尾部分别插入 O(1)。
B 正确：有序容器支持迭代范围（`lower_bound/upper_bound`）。
C 错误：遍历性能取决于数据规模与操作模式；`std::array` 或 `std::vector` 通常最快，但不能绝对化。
D 正确：`list` 的插入不影响已有迭代器。