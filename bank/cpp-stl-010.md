---
qid: cpp-stl-010
type: single
kp: [cpp-stl-basics]
difficulty: easy
answer_key: C
---

以下代码执行后，`v.size()` 的值是多少？

```cpp
#include <vector>
std::vector<int> v = {10, 20, 30};
v.push_back(40);
```

A. `3`
B. `40`
C. `4`
D. `1`

## 解析

正确答案是 C，即 `4`。它符合题目代码/概念对应的 C++ 语言规则或标准库语义，而 A、B、D 通常来自下标、类型、生命周期、复杂度或平台保证的混淆。STL 题要关注容器语义、迭代器失效、复杂度和算法是否修改原序列；不要把所有容器都按数组模型理解。 做这类题时应先判断标准层面的语义，再考虑题目是否给出了特定平台假设。
