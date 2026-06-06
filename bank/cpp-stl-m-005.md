---
qid: cpp-stl-m-005
type: multi
kp: [cpp-stl-basics]
difficulty: easy
answer_key: [A, C, D]
---

关于 `std::sort`，下列哪些说法正确？（选择所有正确项）

A. `std::sort` 定义在头文件 `<algorithm>` 中
B. `std::sort` 保证稳定排序（相等元素的相对顺序不变）
C. `std::sort` 可以接受自定义比较函数作为第三个参数
D. `std::sort` 的平均时间复杂度为 O(n log n)

## 解析

正确选项是 A（`std::sort` 定义在头文件 `<algorithm>` 中）、C（`std::sort` 可以接受自定义比较函数作为第三个参数）、D（`std::sort` 的平均时间复杂度为 O(n log n)），它们符合本题涉及的 C++ 规则。B（`std::sort` 保证稳定排序（相等元素的相对顺序不变）） 的关键问题在于混淆了相关概念或把实现细节当成语言保证。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 多选题要逐项判断，不能因为某个说法在常见平台上成立就认为它是标准规则。
