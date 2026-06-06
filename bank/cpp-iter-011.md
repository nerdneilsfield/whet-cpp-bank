---
qid: cpp-iter-011
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "2"
---

```cpp
#include <vector>
std::vector<int> v = {1, 2, 3};
auto it = v.begin();
++it;
```

`*it` 的值是 ___。

## Explanation

应填写 `2`。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
