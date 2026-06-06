---
qid: cpp-iter-009
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "40"
---

```cpp
#include <vector>
#include <iterator>
std::vector<int> v = {10, 20, 30, 40, 50};
auto it = v.begin();
std::advance(it, 3);
```

`*it` 的值是 ___。

## 解析

应填写 `40`。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
