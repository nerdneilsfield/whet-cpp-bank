---
qid: cpp-iter-015
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: B
---

```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {10, 20, 30, 40, 50};
auto it = std::next(v.begin(), 2);
```

`*it` 的值是？

A. 20
B. 30
C. 40
D. 10

## Explanation

正确答案是 B，对应“30”。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。其他选项容易混淆相关概念：A 项“20”不满足题干要求；C 项“40”不满足题干要求；D 项“10”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
