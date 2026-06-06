---
qid: cpp-iter-014
type: single
kp: [cpp-iterators]
difficulty: easy
answer_key: D
---

以下代码存在什么问题？

```cpp
#include <vector>
std::vector<int> v = {1, 2, 3};
auto it = v.begin();
v.push_back(4);
std::cout << *it << std::endl;
```

A. 语法错误，无法编译
B. `push_back` 后 `it` 自动更新，输出 4
C. 输出 1，完全正确
D. 未定义行为：`push_back` 可能导致重新分配，`it` 已失效

## 解析

正确答案是 D，对应“未定义行为：pushback 可能导致重新分配，it 已失效”。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。其他选项容易混淆相关概念：A 项“语法错误，无法编译”不满足题干要求；B 项“pushback 后 it 自动更新，输出 4”不满足题干要求；C 项“输出 1，完全正确”不满足题干要求。常见误区是只凭关键字判断，而没有结合完整声明、表达式求值结果或 C++ 语义限制。
