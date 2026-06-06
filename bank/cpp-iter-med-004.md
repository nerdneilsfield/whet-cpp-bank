---
qid: cpp-iter-med-004
type: single
kp: [cpp-iterators]
difficulty: medium
answer_key: B
---

下列代码中 `std::distance` 的时间复杂度是？

```cpp
std::list<int> lst(1'000'000);
auto first = lst.begin();
auto last  = lst.end();
auto n = std::distance(first, last);
```

A. O(1)，所有标准容器的 `distance` 都是常数时间
B. O(n)，`list::iterator` 是 bidirectional iterator，没有 `-` 运算符
C. O(log n)，标准库内部用二分加速
D. 编译错误：`distance` 只能用于 random-access iterator

---

**解析：**

`std::distance(first, last)` 的复杂度取决于迭代器分类：

- **random-access iterator**（`vector`、`deque`、`array`、C 数组）：直接 `last - first`，O(1)。
- **其他所有分类**（bidirectional、forward、input）：必须用循环 `while (first != last) { ++first; ++count; }`，O(n)。

`std::list::iterator` 是 bidirectional iterator，没有 `operator-`，所以走的是 O(n) 路径——对一百万元素的 list 调一次 `distance` 就是百万次指针解引用与递增。

这是 "list 看似无害实则昂贵" 的典型坑：`if (std::distance(lst.begin(), it) > k)` 这样的代码会让一段本应 O(1) 的判断退化为 O(n)。C++20 ranges 引入了 `sized_range` 概念让 `std::ranges::distance` 能优先调用 `size()`，对 list 是 O(1)，但前提是用 `std::ranges::distance(lst)` 而不是 `(begin, end)` 形式。

## Explanation

正确答案是 B，对应“O(n)，list::iterator 是 bidirectional iterator，没有 - 运算符”。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。其他选项容易混淆相关概念：A 项“O(1)，所有标准容器的 distance 都是常数时间”不满足题干要求；C 项“O(log n)，标准库内部用二分加速”不满足题干要求；D 项“编译错误：distance 只能用于 random-access iterator”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
