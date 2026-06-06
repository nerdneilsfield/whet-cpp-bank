---
qid: cpp-iter-r-002
type: fill
kp: [cpp-iterators]
difficulty: easy
answer_key: "30"
---

### 题目

阅读以下代码，输出是什么？

```cpp
#include <vector>
#include <iterator>
#include <iostream>

int main() {
    std::vector<int> v = {10, 20, 30, 40, 50};
    auto it = v.begin();
    std::advance(it, 2);
    std::cout << *it << std::endl;
}
```

输出为：___

## Explanation

应填写 `30`。本题考查迭代器类别、失效规则或迭代移动语义，关键是看容器操作后原迭代器是否仍指向有效元素。该答案能与题干中的代码上下文、声明形式或输出结果精确匹配，因此既要关注语法位置，也要关注类型和值的含义。常见误区是写出近似形式但改变了指针/引用/捕获/格式化等语义，导致编译失败或结果不同。
