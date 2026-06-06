---
qid: cpp-stl-012
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: A
---

以下哪段代码正确地用范围 for 遍历 `std::vector<int>` 并打印每个元素？

```cpp
std::vector<int> v = {1, 2, 3};
```

A. `for (int x : v) { std::cout << x << "\n"; }`
B. `for (int x in v) { std::cout << x << "\n"; }`
C. `for (int i = 0; i < v; i++) { std::cout << v << "\n"; }`
D. `foreach (int x : v) { std::cout << x << "\n"; }`

## 解析

正确答案是 A，即 `for (int x : v) { std::cout << x << "\n"; }`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 B、C、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
