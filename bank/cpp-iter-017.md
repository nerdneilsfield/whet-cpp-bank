---
qid: cpp-iter-017
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "1 2 3 4 5"
---

```cpp
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst;
std::copy(src.begin(), src.end(), std::back_inserter(dst));
for (int x : dst) std::cout << x << " ";
```

程序输出是 ___。

## Explanation

应填写 `1 2 3 4 5`。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
