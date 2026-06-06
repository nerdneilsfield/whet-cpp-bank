---
qid: cpp-stl-multi-med-005
type: multi
kp: [cpp-algorithms]
difficulty: medium
answer_key: [A, C]
---
关于 `std::sort` 的要求和特性，**哪些说法是正确的**？（多选）

A. `std::sort` 要求迭代器类型为随机访问迭代器，因此不能直接对 `std::list` 排序
B. `std::sort` 是稳定排序，相等元素的相对顺序一定保持不变
C. 比较器必须满足**严格弱序**（strict weak ordering），即不能同时使 `comp(a,b)` 与 `comp(b,a)` 都为真
D. C++ 标准保证 `std::sort` 的**最坏**时间复杂度为 O(n log n)

---

**解析：**

A 正确：`std::sort` 要求随机访问迭代器，`list`、`forward_list` 的迭代器达不到此要求；要对 `list` 排序应使用成员函数 `list::sort()`。
B 错误：`std::sort` 通常实现为内省排序（IntroSort），**不保证稳定**；要稳定排序应使用 `std::stable_sort`。
C 正确：严格弱序要求反对称（`comp(a,b)` 与 `comp(b,a)` 不可同真）、传递性等。违反时是未定义行为，常见于使用 `<=` 而非 `<` 作比较时。
D 错误：C++ 标准（C++11 及之后）仅要求 `std::sort` **平均**复杂度为 O(n log n)，并未在标准层面强制最坏复杂度。绝大多数实现（IntroSort）实际能做到最坏 O(n log n)，但这是实现选择而非标准保证。

## Explanation

A、C 正确：`std::sort` 需要随机访问迭代器，链表应使用自己的 `list::sort()`。比较器必须满足严格弱序，否则排序算法的前提被破坏。常见误区是认为 `std::sort` 稳定；需要保持等价元素相对顺序时应使用 `std::stable_sort`。
